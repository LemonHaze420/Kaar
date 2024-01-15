#ifndef _INCLUDE_PCHAR_
#define _INCLUDE_PCHAR_
/**************************************************************************************
 *	Playable character
 **************************************************************************************/
#include "System.h"
#include "Character.h"


/*
 *	CPChar 
 */
class CPChar
{
public:
	CCharacter* cpCharacter_m;

	CPChar(CCharacter* cpCharacter_p);
	~CPChar();

	void Update();
	void Draw();
	void DrawSel();

	void MoveTo(CPt<T_2DVALUE>* cp2dPosition_p);
	void MoveTo(T_LONG lDXCell,T_LONG lDYCell);
	void GetInTo(CPt<T_2DVALUE>* cp2dPosition_p);

private:
	void Get3dPos(CPt<T_2DVALUE>* cp2dPosition_p,CVector<T_3DVALUE>* cp3dPosition_p);
	CCharacter* Get3dChar(CPt<T_2DVALUE>* cp2dPosition_p,T_BOOL bPChar_p=false);
	void Set3dPChar(CPt<T_2DVALUE>* cp2dPosition_p);
	T_BOOL AttackTo(CPt<T_2DVALUE>* cp2dPosition_p);
}; /* CPChar */


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif

