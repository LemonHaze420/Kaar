#ifndef _INCLUDE_NPCHAR_
#define _INCLUDE_NPCHAR_
/**************************************************************************************
 *	Non Playable character
 **************************************************************************************/
#include "System.h"
#include "Character.h"
#include "IA.h"

/*
 *	CNPChar 
 */
class CNPChar
{
public:
	enum ENPCharState
	{
		E_NPCHAR_GARDE,
		E_NPCHAR_GOHOME,
		E_NPCHAR_DEAD
	};
	static CList<CNPChar> cListNPChar_m;
	static T_UWORD uwWorld_m;
	static CWorld* cpWorld_m;
	CCharacter* cpCharacter_m;

	CNPChar() {};
	CNPChar(CCharacter* cpCharacter_p,CIA::EIAState eState_p);
	~CNPChar();

	CNPChar& operator=(CNPChar& crNPChar_p);
	
	void MoveTo(CPt<T_3DVALUE>* cpPosition_p);
	void MoveTo(T_LONG lDXCell,T_LONG lDYCell);
	void Update();


	static void Get(T_UWORD uwWorld_p);
	static void New(CCharacter* cpCharacter_p,CIA::EIAState eState_p);
	static void Release();
	static void Play();
	static void Draw();
	static void DrawSel();

private:
	CIA* cpIA_m;
	CIA::EIAState eState_m;
	T_BOOL bFall_m;
	T_BOOL bFalled_m;

	void CreateIA();
}; /* CNPChar */


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif


