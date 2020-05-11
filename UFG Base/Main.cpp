#include "DirectX.h"
#include "Poly.h"

cPoly poly;

bool callOnce = true;
bool callDetour = true;

DWORD __stdcall zFuck(LPVOID)
{
	Sleep(3000);	

	pMenu->AddItems();

	while(1)
	{
		if(pSDK->GameReadyForHook(/*d3d9.dll*/XorStr<0x48,9,0x5068D684>("\x2C\x7A\x2E\x72\x62\x29\x22\x23"+0x5068D684).s,/*ClientFX.fxd*/XorStr<0x1C,13,0x12155DFA>("\x5F\x71\x77\x7A\x4E\x55\x64\x7B\x0A\x43\x5E\x43"+0x12155DFA).s,/*CShell.dll*/XorStr<0x5B,11,0xE1B475B9>("\x18\x0F\x35\x3B\x33\x0C\x4F\x06\x0F\x08"+0xE1B475B9).s) && callOnce == true)
		{
			pDirectX->Dx9Hook(XorStr<0xBA,9,0xC2F83E61>("\xDE\x88\xD8\x84\x90\xDB\xAC\xAD"+0xC2F83E61).s);
			pSDK->ModifyOpCode((void *)EndSceneOpCodes, (void *)"\x89\x65\xF0\x8B\x75\x08", 6);

			if(pSDK->CompareOpCode((void *)EndSceneOpCodes, (void *)dwEndscene_hook, 6))
			{
				pSDK->DetourCreate((PBYTE)dwEndscene_hook, (PBYTE)MyEndscene,6);
			}
			callOnce = false;
		}

		
		if(MainMenu[0].status == true && callDetour == true)
		{
			callDetour = false;
			OriginalS2S = (unsigned int(__stdcall*)(ILTMessage_Read *Message, unsigned int Flags ))pSDK->DetourCreate((PBYTE)ADDR_SENDTOSERVER,(PBYTE)HookedFunction, 7);
			//pSDK->log(XorStr<0x63,48,0x55BC6643>("\x30\x10\x04\x12\x12\x1B\x49\x50\x4B\x24\x02\x01\x04\x15\x15\x52\x20\x46\x26\x56\x31\x0D\x17\x19\x0F\x15\x12\x10\x44\xA0\xB1\xFA\xA6\xB4\xB7\xFE\xA7\xA5\xB7\xAA\xBB\xF4\xA8\xBE\xBD\xE8\x9B"+0x55BC6643).s, ADDR_SENDTOSERVER, HookedFunction );
			pSDK->ModifyOpCode((LPVOID)0x3750CF87,"\xEB",1);
			pSDK->ModifyOpCode((LPVOID)0x374BDEFC,"\x90\x90\x90\x90",4);
		
		}

		pMenu->Navigate();
		pMenu->DoHacks();
	}
    return NULL;
}

int __stdcall DllMain(HINSTANCE hinstDLL, DWORD dwReason, LPVOID lpvReserved)
{
	DisableThreadLibraryCalls(hinstDLL);
    switch( dwReason )
    {
		case 1:
			//poly.DestroyAndMorphSection( hinstDLL,XorStr<0xEE,6,0xA733FF0C>("\xC0\x86\x9E\x98\x86"+0xA733FF0C).s );
			CreateThread(NULL, NULL, &zFuck, NULL, NULL, NULL);
			//pSDK->log(XorStr<0x9F,34,0xC1DC16C8>("\xCC\xD4\xC0\xD6\xD6\xD7\x85\x9C\x87\xEC\xE5\xE6\x8B\xED\xD9\xDA\xCE\xD3\xD9\xD7\xD7\x94\xC1\xD9\x97\xC8\xCB\xD5\xD8\xD9\xCE\xCD\xB5"+0xC1DC16C8).s);
        break;
    }
    return 1;
}