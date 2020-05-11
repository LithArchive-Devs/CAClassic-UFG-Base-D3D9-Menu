/*!
Base engine header file
*/

//#include "Files.h"

#ifndef __ENGINE_H__
#define __ENGINE_H__

#pragma warning (disable:4786) // No truncation warnings, please..

/*!
Platform configuration
*/

#ifndef __PLATFORM_H__
#include "platform.h"
#endif

/*!
Main includes
*/

#ifndef __LTBASETYPES_H__
#include "ltbasetypes.h"
#endif

#ifndef __LTBASEDEFS_H__
#include "ltbasedefs.h"
#endif

/*!
Interfaces
*/
#ifndef __ILTINSTREAM_H__
#include "iltinstream.h"
#endif

#ifndef __ILTOUTSTREAM_H__
#include "iltoutstream.h"
#endif


class cEngine
{
public:
	cEngine();

	bool ValidPointer( void* p )
	{ 
		return !IsBadReadPtr( p, 4 ) && p;
	}

//	void SetLocalPlayerPosition( D3DXVECTOR3 Pos );
	//float FindDistance(D3DXVECTOR3 my,D3DXVECTOR3 other,PlayerInfo* pPlayer,PlayerInfo* pLocal);
	//bool WorldToScreen(LPDIRECT3DDEVICE9 pDevice, PlayerInfo* pPlayer, D3DXVECTOR3* Pos);
	//bool WorldToScreen( D3DXVECTOR3 Pos, D3DXVECTOR3 *Screen );

	//////////////////////////////////////////////////////////////////////////
	//							Class Pointers								//
	//////////////////////////////////////////////////////////////////////////
	/*
	cPlayerMgr* GetPlayerMgr()
	{
		return pPlayerManager;
	}

	LocalInfo* GetLocal()
	{
		return pLocal;
	}

	cLTModel* GetLTModel()
	{
		return pLTModel;
	}

	cGameClientShell* GetGameClientShell()
	{
		return pGameClientShell;
	}
	

private:

	//////////////////////////////////////////////////////////////////////////
	//																		//
	//////////////////////////////////////////////////////////////////////////

	cGameClientShell*	pGameClientShell;
	cPlayerMgr*			pPlayerManager;
	cLTModel*			pLTModel;
	LocalInfo*			pLocal;

	DWORD				dwClientFxEntry;
	*/
};

extern class cEngine* engine;


#endif //!__ENGINE_H__
