#ifndef _INCLUDE_ZONEVIEW_
#define _INCLUDE_ZONEVIEW_
/**************************************************************************************
 * 
 **************************************************************************************/
#include "ZoneItem.h"
#include "BlocView.h"
#include "World.h"


/*
 *	CZoneView
 */
class CZoneView
{
public:
	CBlocView cBlocView_m;

	CZoneView();
	~CZoneView();

	void Update(CWorld* cpWorld_p,T_FLOAT fXC_p,T_FLOAT fYC_p);
	void Draw();

private:
	enum EZoneViewSize
	{
		E_ZONEVIEW_SIZE=4
	};
	// Tableau des Zones visibles
	CZoneItem cpZoneItem0_m[E_ZONEVIEW_SIZE];
	CZoneItem cpZoneItem1_m[E_ZONEVIEW_SIZE];
	CZoneItem* cpZoneItem_m;

	void Set(CWorld* cpWorld_p,T_FLOAT fX_p,T_FLOAT fY_p);
	void FlipRelease();
}; /* CZoneView */


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif


