#ifndef _INCLUDE_CHARPOS_
#define _INCLUDE_CHARPOS_
/**************************************************************************************
 * 
 **************************************************************************************/
#include "System.h"
#include "ZoneInst.h"
#include "BlocInst.h"
#include "Cell.h"
#include "BlocItem.h"


class CWorld;


/*
 *	CCharPos
 */
class CCharPos
{
public:
	enum ECharPosFlag
	{
		E_CHARPOS_NONE=0x0,
		E_CHARPOS_ALTITUDEFREE=0x01,
		E_CHARPOS_ROTATE=0x02,
		E_CHARPOS_ALL=0x03
	};
	T_UWORD uwWorld_m;
	T_UWORD uwXZone_m;
	T_UWORD uwYZone_m;
	T_UWORD uwXBloc_m:2;
	T_UWORD uwYBloc_m:2;
	T_UWORD uwXCell_m:4;
	T_UWORD uwYCell_m:4;
	CWorld *cpWorld_m;
	CZoneInst* cpZoneInst_m;
	CBlocInst* cpBlocInst_m;
	CCell* cpCell_m;
	CBlocItem* cpBlocItem_m;
	CVector<T_3DVALUE> cPosition_m;
	CVector<T_3DVALUE> cToGo_m;
	T_MATHANVALUE tAngle_m;
	T_MATHANVALUE tToAngle_m;
	T_3DVALUE tAltitude_m;		// De 0 à 256


	CCharPos();
	void Set(T_3DVALUE tAltitude_p,T_UWORD uwWorld_p,T_UWORD uwXZone_p,T_UWORD uwYZone_p,T_UWORD uwXBloc_p,T_UWORD uwYBloc_p,T_UWORD uwXCell_p,T_UWORD uwYCell_p);
	void StartAltitude();
	T_BOOL Update(T_3DVALUE tSpeed_p,ECharPosFlag eFlag_p=E_CHARPOS_NONE);

private:
	T_DATE tPrevTime_m;

}; /* CCharPos */


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif

