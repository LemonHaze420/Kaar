#ifndef _INCLUDE_WORLD_
#define _INCLUDE_WORLD_
/**************************************************************************************
 * Description World=ensemble d'instance de zone
 **************************************************************************************/
#include "System.h"
#include "ZoneInst.h"
#include "List.h"
#include "Character.h"


/*
 *	CWorld
 */
class CWorld
{
public:
	T_UWORD uwXSize_m;
	T_UWORD uwYSize_m;
	CZoneInst* cpZoneInst_m;
	CList<CCharacter> cListCharacter_m;
	T_ULONG ulNbCharacter_m;

	CWorld();
	CWorld(T_UWORD uwXSize_p,T_UWORD uwYSize_p);
	~CWorld();

	CWorld& operator=(CWorld& crWorld_p);


	/* InRange */
	T_BOOL InRange(T_3DVALUE tX_p,T_3DVALUE tY_p)
	{
		if(tX_p<0.0f || tY_p>0.0f || tX_p>=uwXSize_m*CZone::E_ZONE_SIZE*256 || tY_p<=-uwYSize_m*CZone::E_ZONE_SIZE*256)
			return false;
		return true;
	} /* InRange */


	/* GetXZone */
	T_UWORD GetXZone(T_3DVALUE tX_p)
	{
		return T_UWORD(tX_p/T_3DVALUE(CZone::E_ZONE_SIZE*256));
	} /* GetXZone */


	/* GetYZone */
	T_UWORD GetYZone(T_3DVALUE tY_p)
	{
		return T_UWORD(-tY_p/T_3DVALUE(CZone::E_ZONE_SIZE*256));
	} /* GetYZone */


	/* GetZoneIndex */
	T_ULONG GetZoneIndex(T_UWORD uwX_p,T_UWORD uwY_p)
	{	
		return uwX_p+uwXSize_m*uwY_p;
	} /* GetZoneIndex */

	
	/* GetZoneIndex */
	T_ULONG GetZoneIndex(T_3DVALUE tX_p,T_3DVALUE tY_p)
	{	
		return GetZoneIndex(GetXZone(tX_p),GetYZone(tY_p));
	} /* GetZoneIndex */


	/* GetZoneInst */
	CZoneInst* GetZoneInst(T_3DVALUE tX_p,T_3DVALUE tY_p)
	{	
		return &cpZoneInst_m[GetZoneIndex(tX_p,tY_p)];
	} /* GetZoneInst */


	/* GetZoneInst */
	CZoneInst* GetZoneInst(T_UWORD uwX_p,T_UWORD uwY_p)
	{	
		return &cpZoneInst_m[GetZoneIndex(uwX_p,uwY_p)];
	} /* GetZoneInst */


	/* GetXPosition */
	static T_3DVALUE GetXPosition(T_UWORD uwXZone_p,T_UWORD uwXBloc_p,T_UWORD uwXCell_p)
	{
		return T_3DVALUE(uwXZone_p*CZone::E_ZONE_SIZE*256+uwXBloc_p*256+uwXCell_p*16+8);
	} /* GetXPosition */


	/* GetYPosition */
	static T_3DVALUE GetYPosition(T_UWORD uwYZone_p,T_UWORD uwYBloc_p,T_UWORD uwYCell_p)
	{
		return -T_3DVALUE(uwYZone_p*CZone::E_ZONE_SIZE*256+uwYBloc_p*256+uwYCell_p*16+8);
	} /* GetYPosition */
}; /* CWorld */


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif


