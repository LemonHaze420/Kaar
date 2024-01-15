#ifndef _INCLUDE_GAME_
#define _INCLUDE_GAME_
/**************************************************************************************
 * 
 **************************************************************************************/
#include "Player.h"


/*
 *	CGame
 */
class CGame
{
public:
	static CPlayer* cpPlayer_m;

	CGame();
	~CGame();

	void Start(T_UWORD uwWorld_p=0);
	void ReStart(T_UWORD uwWorld_p=0);
	void Update();
	void Draw(T_BOOL bDebug_p=false);
}; /* CGame */


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif


