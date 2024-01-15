#ifndef _INCLUDE_BLOCVIEW_
#define _INCLUDE_BLOCVIEW_
/**************************************************************************************
 * Vue des 9 blocs courant
 **************************************************************************************/
#include "BlocItem.h"
#include "World.h"


/*
 *	CBlocView
 */
class CBlocView
{
public:
	enum EBlocViewSize
	{
		E_BLOCVIEW_SIZE=5,	//9
		E_BLOCVIEW_SIZE2=E_BLOCVIEW_SIZE*E_BLOCVIEW_SIZE,
		E_BLOCVIEW_CENTER=12
	};
	CBlocItem* cpBlocItem_m;

	CBlocView();

	void Update(CWorld* cpWorld_p,T_FLOAT fXC_p,T_FLOAT fYC_p);
	void Draw();

private:
	// Tableau des blocs visibles
	CBlocItem cpBlocItem0_m[E_BLOCVIEW_SIZE2];
	CBlocItem cpBlocItem1_m[E_BLOCVIEW_SIZE2];

	void Set(CWorld* cpWorld_p,T_UWORD uwIndex_p,T_FLOAT fX_p,T_FLOAT fY_p);
}; /* CBlocView */


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif


