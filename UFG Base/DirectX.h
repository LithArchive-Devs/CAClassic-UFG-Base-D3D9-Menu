#include "SDK.h"

const D3DCOLOR Red      = D3DCOLOR_ARGB(255, 255, 000, 000);
const D3DCOLOR White    = D3DCOLOR_ARGB(255,255,255,255);
const D3DCOLOR Blue = D3DCOLOR_ARGB(255,0,174,255);

DWORD CreateDetour(DWORD dwThread,DWORD dwAdress,DWORD dwType,DWORD dwSize)
{
	DWORD dwDetour,dwProtect,i;
	if (dwAdress&&dwThread&&dwSize>= dwSize)
	{
		dwDetour = (DWORD)VirtualAlloc(0,dwSize+dwSize,0x1000,0x40);
		if (dwDetour&&VirtualProtect((VOID*)dwAdress,dwSize,0x40,&dwProtect))
		{
			for (i=0;i<dwSize;i++) 
			{
				*(BYTE*)(dwDetour+i)=*(BYTE*)(dwAdress+i);
			}
			switch (dwType)
			{
			    case Detour_Type_0xE9:
				{
				    *(BYTE*)(dwDetour+dwSize+0)=0xE9;
				    *(DWORD*)(dwDetour+dwSize+1)=(dwAdress-dwDetour-dwSize);
	    		            *(BYTE*)(dwAdress+0)=0xE9;
				    *(DWORD*)(dwAdress+1)=(dwThread-dwAdress-dwSize);
				}
				break;
				case Detour_Type_0xB8:
				{
				    *(BYTE*)(dwDetour+dwSize+0)=0xB8;
				    *(DWORD*)(dwDetour+dwSize+1)=(dwAdress+dwSize);
				    *(WORD*)(dwDetour+dwSize+5)=0xE0FF; 
				    *(BYTE*)(dwAdress+0)=0xB8;            
				    *(DWORD*)(dwAdress+1)=(dwThread);
				    *(WORD*)(dwAdress+5)=0xE0FF; 
				}
				break;
				case Detour_Type_0x68:
				{
				    *(BYTE*)(dwDetour+dwSize+0)=0x68;
				    *(DWORD*)(dwDetour+dwSize+1)=(dwAdress+dwSize);
				    *(WORD*)(dwDetour+dwSize+5)=0xC3; 
				    *(BYTE*)(dwAdress+0)=0x68;            
				    *(DWORD*)(dwAdress+1)=(dwThread);
				    *(WORD*)(dwAdress+5)=0xC3; 
				}
				break;
			}
			VirtualProtect((VOID*)dwAdress,dwSize,dwProtect,&dwProtect);
			VirtualProtect((VOID*)dwDetour,dwSize+dwSize,0x20,&dwProtect);
	    	        return dwDetour;
		}
	}
	Sleep(10);
	return (0);
}

int playerRankHackID = 30;
int playerCharacterHackID = 23;

unsigned int __stdcall HookedFunction(ILTMessage_Read *Message, unsigned int Flags )
{
		__asm
		{
			pushad
		}
	
		uint messageID  = Message->Readuint8();
        uint size       = Message->Size();

		if( messageID == 114 )
		{

			CAutoMessage characterMsg;
			characterMsg.Writeuint8( 114 );
			for( int i = 0; i < (Message->Size() /*size in bits*/ / sizeof(uint8));i++)
			{
			int backupID = Message->Readuint8(); // backup the original id

			if( i == 15 && GetAsyncKeyState(VK_F11))
				backupID = 25; // set the id to our id( character )
			else if( i == 18 && GetAsyncKeyState(VK_F10) )
				backupID = 23; // set the id to our id( rank )

			characterMsg.Writeuint8( backupID ); // 
			}

			return g_LTClient->SendToServer( characterMsg.Read(),Flags );
		}



		__asm
		{
			popad
		}

	return OriginalS2S(Message,Flags);
}

void RenderMenu()
{
	pDirectX->DrawTextA(m_pD3Ddev,MenuX - 20,MenuY - 20,Blue,XorStr<0x39,32,0xD3CA0ED6>("\x6E\x6D\x6C\x12\x68\x70\x79\x01\x08\x10\x04\x05\x08\x0F\x09\x0F\x67\x09\x04\x01\x6D\x1D\x7D\x03\x71\x1E\x1C\x13\x12\x13\x05"+0xD3CA0ED6).s);


	for(unsigned int i = 0; i <= MainMenu.size() - 1;i++)
	{
		char *status = (MainMenu[i].status == true) ? " On" : " Off";

		if(MenuIndex == i)
		{
			pDirectX->DrawTextA(m_pD3Ddev,MenuX,MenuY + (12 * i),Blue,MainMenu[i].title);
			pDirectX->DrawTextA(m_pD3Ddev,MenuX + 100,MenuY + (12 * i),Blue,status);
		}
		else
		{
			pDirectX->DrawTextA(m_pD3Ddev,MenuX,MenuY + (12 * i),White,MainMenu[i].title);
			pDirectX->DrawTextA(m_pD3Ddev,MenuX  + 100,MenuY + (12 * i),White,status);
		}
	}

	//sprintf(buffer,"%d",s2sIndex);

	pDirectX->DrawTextA(m_pD3Ddev,MenuX,MenuY + 100,White,buffer);
}

__declspec(naked) void MyEndscene( )
{
    __asm 
    {
        mov dword ptr ss:[ebp - 0x10], esp
        mov esi, dword ptr ss:[ebp + 0x8]
		mov m_pD3Ddev, esi
        pushad
    }

	if(Directx_Font){
		Directx_Font->Release();
		Directx_Font = NULL;
		nFont = FALSE;
	}

	if(!nFont){
		D3DXCreateFont(m_pD3Ddev, 14, 0,FW_SEMIBOLD,0, 0, DEFAULT_CHARSET, OUT_TT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE,"Arial", &Directx_Font);
		nFont = TRUE;
	}

	if(MenuShow)
	{
		RenderMenu();
	}

    __asm 
    {
        popad
        jmp dwEndscene_ret
    }

}

__declspec(naked) void DIP()
{
	static LPDIRECT3DDEVICE9 pDevice;
	static D3DPRIMITIVETYPE pType;
	static D3DPRIMITIVETYPE nBaseVertIndex;
	static D3DPRIMITIVETYPE nMinIndex;
	static D3DPRIMITIVETYPE nNumVertices;
	static D3DPRIMITIVETYPE nStartIndex;
	static D3DPRIMITIVETYPE nPrimitiveCount;

	__asm
	{
		mov dword ptr ss:[ebp-10],esp

		mov esi, dword ptr ss:[ebp+0x8]
		mov pDevice, esi

		mov esi, dword ptr ss:[ebp+0x0C]
		mov pType, esi

		mov esi, dword ptr ss:[ebp+0x10]
		mov nBaseVertIndex, esi
		mov esi, dword ptr ss:[ebp+0x14]
		mov nMinIndex, esi
		mov esi, dword ptr ss:[ebp+0x18]
		mov nNumVertices, esi

		mov esi, dword ptr ss:[ebp+0x1C]
		mov nStartIndex, esi

		mov esi, dword ptr ss:[ebp+0x20]
		mov nPrimitiveCount,esi
	}

	if(pDevice)


	__asm
	{
		jmp dwDIP_ret
	}
}

__declspec(naked) void MyPresent()
{
	static LPDIRECT3DDEVICE9 pDevice;

	__asm
	{
		//mov dword ptr ss:[ebp-10],esp
		mov esi, dword ptr ss:[ebp+0x8]
		mov pDevice, esi
	}

	__asm
	{
		jmp dwPresent_ret
	}
}