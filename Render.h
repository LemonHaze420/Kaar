#ifndef _INCLUDE_RENDER_
#define _INCLUDE_RENDER_
/**************************************************************************************
 * 
 **************************************************************************************/
#include "System.h"


/*
 *	CRender
 */
class CRender
{
public:
	CRender(CPt<T_2DVALUE>* cpSize_p);
	~CRender();

	void SetPos(CPt<T_2DVALUE>* cpPos_p);

private:
	CPt<T_2DVALUE> cSize_m;
}; /* CRender */


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif


