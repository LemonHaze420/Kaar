#ifndef _INCLUDE_WORLDPOS_
#define _INCLUDE_WORLDPOS_
/**************************************************************************************
 * 
 **************************************************************************************/
#include "System.h"
#include "Univers.h"
#include "World.h"
#include "ZoneInst.h"
#include "BlocInst.h"
#include "Cell.h"


/*
 *	CWorldPos
 */
class CWorldPos
{
public:
	T_UWORD uwWorld_m;
	T_3DVALUE tX_m;
	T_3DVALUE tZ_m;
	CWorld* cpWorld_m;
	CZoneInst* cpZoneInst_m;
	CBlocInst* cpBlocInst_m;
	CCell* cpCell_m;

	CWorldPos():
		uwWorld_m(0),
		tX_m(0.0f),
		tZ_m(0.0f),
		cpWorld_m(0),
		cpZoneInst_m(0),
		cpBlocInst_m(0),
		cpCell_m(0)
	{
	}

	CWorldPos(T_UWORD uwWorld_p,T_3DVALUE tX_p,T_3DVALUE tZ_p)
	{
		Set(uwWorld_p,tX_p,tZ_p);
	}

	void Set(T_UWORD uwWorld_p,T_3DVALUE tX_p,T_3DVALUE tZ_p)
	{
		uwWorld_m=uwWorld_p;
		tX_m=tX_p;
		tZ_m=tZ_p;
		cpWorld_m=&CUnivers::cpWorld_m[uwWorld_m];
		if(cpWorld_m!=0 && cpWorld_m->InRange(tX_m,tZ_m))
		{
			cpZoneInst_m=cpWorld_m->GetZoneInst(tX_m,tZ_m);
			cpBlocInst_m=cpZoneInst_m->GetBlocInst(tX_m,tZ_m);
			cpCell_m=cpBlocInst_m->GetCell(tX_p,tZ_p);
		}
		else
		{
			cpZoneInst_m=0;
			cpBlocInst_m=0;
			cpCell_m=0;
		}
	}

	T_3DVALUE GetAltitude()
	{
		if(cpZoneInst_m!=0 && cpBlocInst_m!=0)
			return T_3DVALUE(cpZoneInst_m->wAltitude_m+cpBlocInst_m->cBlocPos_m.biAltitude_m*64+cpCell_m->biAltitude_m*4);
		return 0.0f;
	}
}; /* CWorldPos */


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif


