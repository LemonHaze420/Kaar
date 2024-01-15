#ifndef _INCLUDE_PLAYER_
#define _INCLUDE_PLAYER_
/**************************************************************************************
 * 
 **************************************************************************************/
#include "System.h"
#include "Univers.h"
#include "WorldView.h"
#include "PChar.h"
#include "World.h"
#include "Character.h"


/*
 *	CPlayer
 */
class CPlayer
{
public:
	enum EPlayerMaxPChar
	{
		E_PLAYER_MAXPCHAR=6
	};

	static CUnivers* CPlayer::cpUnivers_m;
	static CWorldView* CPlayer::cpWorldView_m;

	static CPChar* cppPChar_m[E_PLAYER_MAXPCHAR];
	static T_UWORD uwNbPChar_m;
	static T_UWORD uwCurPChar_m;
	static CPChar* cpCurPChar_m;
	static T_UWORD uwCurWorld_m;
	static CWorld* cpCurWorld_m;
	static CCharacter* cpCurCharacter_m;

	CPlayer(char* chpName_p);
	~CPlayer();

	static void Get(T_UWORD uwWorld_p);
	static void Release();

	static void Update();
	static void Draw(T_BOOL bDebug_p);
	static void DrawSel();
	static void SetActive(T_UWORD uwPChar_p);
}; /* CPlayer */


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif

