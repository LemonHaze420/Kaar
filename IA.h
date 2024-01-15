#ifndef _INCLUDE_IA_
#define _INCLUDE_IA_
/**************************************************************************************
 * 
 **************************************************************************************/
#include "System.h"


class CIA
{
public:
	enum EIAState
	{
		E_IA_GARDE,
		E_IA_GOHOME,
		E_IA_DEAD,
		E_IA_ATTACK,
		E_IA_SEARCH
	};

	virtual EIAState UpdateGarde()=0;
	virtual EIAState UpdateDead()=0;
	virtual EIAState UpdateGoHome()=0;
	virtual EIAState UpdateAttack()=0;
	virtual EIAState UpdateSearch()=0;
};


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif

