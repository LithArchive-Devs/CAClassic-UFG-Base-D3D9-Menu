#include "Main.h"

#define ADDR_LTCLIENT		0x378206B8//0x3781D678//0x37817698//0x3783DD48
#define ADDR_SENDTOSERVER	0x476450//0x476430//0x4763B0//0x474040

DWORD JMPBACK_ADDY = ADDR_SENDTOSERVER + 0x7;

CLTClient* g_LTClient;
CCommonLT* g_CommonLT;

char buffer[100];

typedef unsigned int( __stdcall *tSendToServer )( ILTMessage_Read *Message, unsigned int Flags );
tSendToServer pSendToServer;

unsigned int( __stdcall *OriginalS2S )( ILTMessage_Read *Message, unsigned int Flags );

#define Detour_Type_0xE9  1
#define Detour_Type_0xB8  2
#define Detour_Type_0x68  3

int s2sIndex = 0;

LPDIRECT3DDEVICE9 m_pD3Ddev; 
LPD3DXFONT Directx_Font;

DWORD * VTable;

DWORD dwEndscene_hook, dwEndscene_ret, dwPresent_hook, dwPresent_ret, dwDIP_hook, dwDIP_ret;

BYTE EndSceneOpCodes[6];
BYTE PresentOpCodes[5];

BYTE SendToServerOpCodes[7];

#define dir_log XorStr<0x38,19,0x5A83D1B0>("\x7B\x03\x66\x6E\x7A\x7A\x61\x6C\x72\x12\x1D\x0F\x0B\x02\x68\x33\x30\x3D"+0x5A83D1B0).s

ofstream outfile;

bool nFont;

int MenuIndex;
int MenuShow = false;
int MenuX = 150;
int MenuY = 300;

class cSDK;
class cDirectX;
class cMenu;

cSDK* pSDK;
cDirectX* pDirectX;
cMenu *pMenu;

class cSDK
{
public:
	VOID ModifyOpCode(PVOID dwAdd, void *val, int bytes);
	BOOL CompareOpCode(PVOID dwAdd, PVOID dwAdd2, int bytes);
	HINSTANCE nGetModuleHandle(LPCSTR szModule);
	BOOL bCompare(const BYTE* pData, const BYTE* bMask, const char* szMask);
	VOID *DetourCreate(BYTE *src, CONST BYTE *dst, CONST INT len);
	DWORD CreateDetour(DWORD dwThread,DWORD dwAdress,INT dwType,DWORD dwSize);
	BOOL GameReadyForHook(LPCSTR Module1,LPCSTR Module2,LPCSTR Module3);
	VOID HideModule( HINSTANCE hModule );
	VOID __cdecl log(const char *fmt, ...);
	DWORD FindPattern( DWORD dwStart, DWORD dwLen, BYTE* pszPatt, char pszMask[] );
};


DWORD cSDK::FindPattern( DWORD dwStart, DWORD dwLen, BYTE* pszPatt, char pszMask[] )
{
	unsigned int i = NULL;
	int iLen = strlen( pszMask ) - 1;

	for( DWORD dwRet = dwStart; dwRet < dwStart + dwLen; dwRet++ )
	{
		if( *(BYTE*)dwRet == pszPatt[i] || pszMask[i] == '?' )
		{
			if( pszMask[i+1] == '\0' )
				return( dwRet - iLen );
			i++;
		} 
		else 
			i = NULL;
	}
	return NULL;
}

VOID cSDK::log(const char *fmt, ...)
{
	outfile.open(dir_log, ios::app);
	va_list va_alist;
	char buffer[1024] = {0};
	va_start( va_alist, fmt );
	vsnprintf(buffer+strlen(buffer), sizeof(buffer) - strlen(buffer), fmt, va_alist );
	va_end( va_alist );
	outfile << buffer;
	outfile.close();

	return;
}

VOID cSDK::ModifyOpCode(PVOID dwAdd, void *val, int bytes)
{
    DWORD d, ds;  
    VirtualProtect(dwAdd, bytes, PAGE_EXECUTE_READWRITE, &d);
    memcpy(dwAdd, val, bytes);   
    VirtualProtect(dwAdd,bytes,d,&ds);
}

BOOL cSDK::CompareOpCode(PVOID dwAdd, PVOID dwAdd2, int bytes)
{
	DWORD d, ds;
	int Matches;
    VirtualProtect(dwAdd, bytes, PAGE_EXECUTE_READWRITE, &d);
	Matches = memcmp(dwAdd,dwAdd2,bytes);
	VirtualProtect(dwAdd,bytes,d,&ds);
	return (Matches == 0) ? true : false;
}

HINSTANCE cSDK::nGetModuleHandle(LPCSTR szModule) 
{
    HINSTANCE hModule = NULL;
    if(!(hModule = GetModuleHandle(szModule))) 
        hModule = LoadLibrary(szModule);
    return hModule;
}

BOOL cSDK::bCompare(const BYTE* pData, const BYTE* bMask, const char* szMask)
{
    for(;*szMask;++szMask,++pData,++bMask)
        if(*szMask=='x' && *pData!=*bMask)   return 0;
    return (*szMask) == NULL;
}

VOID* cSDK::DetourCreate(BYTE *src, CONST BYTE *dst, CONST INT len){
		BYTE *jmp = (BYTE *)malloc(len + 5);
		DWORD dwback;
		VirtualProtect(src, len, PAGE_READWRITE, &dwback);
		memcpy(jmp, src, len);
		jmp += len;
		jmp[0] = 0xE9;
		*(DWORD *)(jmp + 1) = (DWORD)(src + len - jmp) - 5;
		src[0] = 0xE9;
		*(DWORD *)(src + 1) = (DWORD)(dst - src) - 5;
		for(INT i = 5; i < len; i++) src[i] = 0x90;
		VirtualProtect(src, len, dwback, &dwback);

		return(jmp - len);
}

BOOL cSDK::GameReadyForHook(LPCSTR Module1,LPCSTR Module2,LPCSTR Module3)
{
	if((GetModuleHandle(Module1) != NULL) && (GetModuleHandle(Module2) != NULL)
     && GetModuleHandle(Module3) != NULL )
        return true;
    return false;
}

VOID cSDK::HideModule( HINSTANCE hModule )
 {
 	DWORD dwPEB_LDR_DATA = 0;
 
 	_asm
 	{
 		pushad;
 		pushfd;
 		mov eax, fs:[30h]					// PEB
 		mov eax, [eax+0Ch]					// PEB->ProcessModuleInfo
 		mov dwPEB_LDR_DATA, eax				// Save ProcessModuleInfo
 
 InLoadOrderModuleList:
 		mov esi, [eax+0Ch]					// ProcessModuleInfo->InLoadOrderModuleList[FORWARD]
 		mov edx, [eax+10h]					//  ProcessModuleInfo->InLoadOrderModuleList[BACKWARD]
 
 LoopInLoadOrderModuleList: 
 		lodsd								//  Load First Module
		mov esi, eax		    			//  ESI points to Next Module
 		mov ecx, [eax+18h]		    		//  LDR_MODULE->BaseAddress
 		cmp ecx, hModule		    		//  Is it Our Module ?
 		jne SkipA		    		    	//  If Not, Next Please (@f jumps to nearest Unamed Lable @@:)
 		mov ebx, [eax]						//  [FORWARD] Module 
 		mov ecx, [eax+4]    		    	//  [BACKWARD] Module
 		mov [ecx], ebx						//  Previous Module's [FORWARD] Notation, Points to us, Replace it with, Module++
 		mov [ebx+4], ecx					//  Next Modules, [BACKWARD] Notation, Points to us, Replace it with, Module--
		jmp InMemoryOrderModuleList			//  Hidden, so Move onto Next Set
 SkipA:
 		cmp edx, esi						//  Reached End of Modules ?
 		jne LoopInLoadOrderModuleList		//  If Not, Re Loop
 
 InMemoryOrderModuleList:
 		mov eax, dwPEB_LDR_DATA				//  PEB->ProcessModuleInfo
 		mov esi, [eax+14h]					//  ProcessModuleInfo->InMemoryOrderModuleList[START]
 		mov edx, [eax+18h]					//  ProcessModuleInfo->InMemoryOrderModuleList[FINISH]
 
 LoopInMemoryOrderModuleList: 
 		lodsd
 		mov esi, eax
 		mov ecx, [eax+10h]
 		cmp ecx, hModule
 		jne SkipB
 		mov ebx, [eax] 
 		mov ecx, [eax+4]
 		mov [ecx], ebx
 		mov [ebx+4], ecx
 		jmp InInitializationOrderModuleList
 SkipB:
 		cmp edx, esi
 		jne LoopInMemoryOrderModuleList
 
 InInitializationOrderModuleList:
 		mov eax, dwPEB_LDR_DATA				     //  PEB->ProcessModuleInfo
 		mov esi, [eax+1Ch]						 //  ProcessModuleInfo->InInitializationOrderModuleList[START]
 		mov edx, [eax+20h]						 //  ProcessModuleInfo->InInitializationOrderModuleList[FINISH]
 
 LoopInInitializationOrderModuleList: 
 		lodsd
 		mov esi, eax		
 		mov ecx, [eax+08h]
 		cmp ecx, hModule		
 		jne SkipC
 		mov ebx, [eax] 
 		mov ecx, [eax+4]
 		mov [ecx], ebx
 		mov [ebx+4], ecx
 		jmp Finished
 SkipC:
 		cmp edx, esi
 		jne LoopInInitializationOrderModuleList
 
 Finished:
 		popfd;
 		popad;
 	}
 }


class cDirectX
{
public:
	VOID Dx9Hook( LPCSTR D3D9 );
	VOID DrawText(LPDIRECT3DDEVICE9 pDevice, INT x, INT y, DWORD color, CHAR *text);
};

VOID cDirectX::Dx9Hook( LPCSTR D3D9 )
{

    DWORD hD3D = NULL;

    while (!hD3D) hD3D = (DWORD)pSDK->nGetModuleHandle(D3D9);
    DWORD pDevice = pSDK->FindPattern(hD3D, 0x128000, (PBYTE)"\xC7\x06\x00\x00\x00\x00\x89\x86\x00\x00\x00\x00\x89\x86", "xx????xx????xx");
	pSDK->ModifyOpCode(&VTable, (VOID *)(pDevice + 2), 4);

	dwEndscene_hook = VTable[42] + 0x2A;
    dwEndscene_ret = dwEndscene_hook + 0x6;

	dwPresent_hook    = ( VTable[17] + 0x7 );
	dwPresent_ret = dwPresent_hook + 0x6;

	dwDIP_hook      = ( VTable[82] + 0x2A );
}

VOID cDirectX::DrawText(LPDIRECT3DDEVICE9 pDevice, INT x, INT y, DWORD color, CHAR *text){
	RECT rect;
	SetRect(&rect, x, y, x, y);
	Directx_Font->DrawText(NULL, text, -1, &rect, DT_LEFT | DT_NOCLIP, color);
}


class cMenu
{
public:
	cMenu(char* title,bool status)
	{
		this->title = title;
		this->status = status;
	}

	char* title;
	bool status;

	VOID AddItems();
	VOID Navigate();
	VOID DoHacks();
};

vector<cMenu> MainMenu;

VOID cMenu::AddItems()
{

	MainMenu.push_back(cMenu("Activate S2S",false));
	MainMenu.push_back(cMenu("Respawn",false));
}

VOID cMenu::Navigate()
{
	if(GetAsyncKeyState(VK_INSERT)&1)
	{
		MenuShow = !MenuShow;
		Sleep(100);
	}
	if(GetAsyncKeyState(VK_UP)&1 && MenuIndex > 0)
		MenuIndex--;
	if(GetAsyncKeyState(VK_DOWN)&1 && (unsigned int)MenuIndex < MainMenu.size() -1)
		MenuIndex++;
	if(GetAsyncKeyState(VK_LEFT)&1 && MainMenu[MenuIndex].status == true)
		MainMenu[MenuIndex].status = false;
	if(GetAsyncKeyState(VK_RIGHT)&1 && MainMenu[MenuIndex].status == false)
		MainMenu[MenuIndex].status = true;
}


VOID cMenu::DoHacks()
{
	if(MainMenu[1].status == true)
	{
		pSendToServer = (tSendToServer)ADDR_SENDTOSERVER;
		g_LTClient = *(CLTClient**)ADDR_LTCLIENT;
		g_CommonLT = g_LTClient->Common();
		if(engine->ValidPointer(g_LTClient))
		{
			CAutoMessage Msg;
			Msg.Writeuint8(113);
			Msg.Writeuint8(1);
			Msg.Writeuint32(1);
			pSendToServer(Msg.Read(), MESSAGE_GUARANTEED);
		}
	}

	/*
	if(MainMenu[1].status == true)
	{
		pSendToServer = (tSendToServer)ADDR_SENDTOSERVER;
		g_LTClient = *(CLTClient**)ADDR_LTCLIENT;
		g_CommonLT = g_LTClient->Common();
		if(engine->ValidPointer(g_LTClient))
		{
			CAutoMessage Msg;
			Msg.Writeuint8(113);
			Msg.Writeuint8(1);
			Msg.Writeuint32(1);
			pSendToServer(Msg.Read(), MESSAGE_GUARANTEED);
		}
	}
	*/
}