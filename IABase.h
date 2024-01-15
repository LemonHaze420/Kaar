#ifndef _INCLUDE_IABASE_
#define _INCLUDE_IABASE_
/**************************************************************************************
 * 
 **************************************************************************************/
#include "IA.h"
#include "System.h"
#include "Character.h"
#include "Path.h"

class CIABase:public CIA
{
public:
	CIABase(CCharacter* cpCharacter_p);

	virtual CIA::EIAState UpdateGarde();
	virtual CIA::EIAState UpdateDead();
	virtual CIA::EIAState UpdateGoHome();
	virtual CIA::EIAState UpdateAttack();
	virtual CIA::EIAState UpdateSearch();

private:
	CCharacter* cpCharacter_m;
	T_UWORD uwPath_m;
	T_UWORD uwStep_m;
	CPathPos cPathPos_m;
	T_DATE tDate_m;
};


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif

