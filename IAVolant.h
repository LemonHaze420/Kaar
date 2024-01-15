#ifndef _INCLUDE_IAVOLANT_
#define _INCLUDE_IAVOLANT_
/**************************************************************************************
 * 
 **************************************************************************************/
#include "IA.h"
#include "System.h"
#include "Character.h"
#include "Path.h"

class CIAVolant:public CIA
{
public:
	CIAVolant(CCharacter* cpCharacter_p);

	virtual CIA::EIAState UpdateGarde();
	virtual CIA::EIAState UpdateDead();
	virtual CIA::EIAState UpdateGoHome();
	virtual CIA::EIAState UpdateAttack();
	virtual CIA::EIAState UpdateSearch();

private:
	CCharacter* cpCharacter_m;
	CCharacter* cpAttackCharacter_m;
	T_UWORD uwPath_m;
	T_UWORD uwStep_m;
	CPathPos cPathPos_m;
	T_DATE tDate_m;

	CCharacter* GetAttackCharacter(T_3DVALUE tDist_p);

};


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif

