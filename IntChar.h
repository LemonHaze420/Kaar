#ifndef _INCLUDE_INTCHAR_
#define _INCLUDE_INTCHAR_
/**************************************************************************************
 * 
 **************************************************************************************/
#include "System.h"


/*
 *	CIntChar
 */
class CIntChar
{
public:
	enum EIntCharElmt
	{
		E_INTCHAR_LIFE=0x01,
		E_INTCHAR_TIRENESS=0x02,
		E_INTCHAR_MOVIE=0x04,
		E_INTCHAR_ALL=0x07
	};

	CIntChar();
	~CIntChar();

	void Update(T_FLAGS tElmt_p=E_INTCHAR_ALL);
	void UpdateP();

private:
	T_UWORD uwMovieAnim_m;
	T_DATE tStartDate_m;
	T_DATE tMovieStartDate_m;
	CBmFrameObj* cpJauge_m;
}; /* CIntChar */


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif

