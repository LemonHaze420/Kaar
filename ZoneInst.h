#ifndef _INCLUDE_ZONEINST_
#define _INCLUDE_ZONEINST_
/**************************************************************************************
 * Description instance zone = pointeur sur zone + attribut géographique
 **************************************************************************************/
#include "System.h"
#include "Ref.h"
#include "Zone.h"
#include "BlocInst.h"
#include "LandInst.h"


/*
 *	CZoneInst
 */
class CZoneInst:public CRef
{
public:
	enum EZoneInstGeo
	{
		E_ZONEINST_GEOHUMAIN,
		E_ZONEINST_GEONOMAREG,
		E_ZONEINST_GEOUERG
	};
	CZone* cpZone_m;	// Pointeur sur zone de construction
	T_UWORD uwX_m;	// Coordonnée univers de la zone
	T_UWORD uwY_m;
	T_WORD wAltitude_m;

	EZoneInstGeo eZoneGeo_m;

	CBlocInst cpBlocInst_m[CZone::E_ZONE_SIZE2];
	CLandInst* cpLandInst_m;
	T_UWORD uwNbLandInst_m;


	CZoneInst();
	~CZoneInst();

	CZoneInst& operator=(CZoneInst& crZoneInst_p);		

	void Set(CZone* cpZone_p,T_UWORD uwX_p,T_UWORD uwY_p,T_WORD wAltitude_p,EZoneInstGeo eZoneGeo_p);
	void Set(CZone* cpZone_p,T_UWORD uwSet_p,T_UWORD uwX_p,T_UWORD uwY_p,T_WORD wAltitude_p,EZoneInstGeo eZoneGeo_p);


	/* GetXBloc */
	T_UWORD GetXBloc(T_3DVALUE tX_p)
	{
		return T_UWORD(tX_p/256.0f)%CZone::E_ZONE_SIZE;
	} /* GetXBloc */


	/* GetYBloc */
	T_UWORD GetYBloc(T_3DVALUE tY_p)
	{
		return T_UWORD(-tY_p/256.0f)%CZone::E_ZONE_SIZE;
	} /* GetYBloc */


	/* GetBlocIndex */
	T_ULONG GetBlocIndex(T_UWORD uwX_p,T_UWORD uwY_p)
	{
		return uwX_p+CZone::E_ZONE_SIZE*uwY_p;
	} /* GetBlocIndex */


	/* GetBlocIndex */
	T_ULONG GetBlocIndex(T_3DVALUE tX_p,T_3DVALUE tY_p)
	{	
		return GetBlocIndex(GetXBloc(tX_p),GetYBloc(tY_p));
	} /* GetBlocIndex */


	/* GetBlocInst */
	CBlocInst* GetBlocInst(T_3DVALUE tX_p,T_3DVALUE tY_p)
	{	
		return &cpBlocInst_m[GetBlocIndex(tX_p,tY_p)];
	} /* GetBlocInst */


	/* GetBlocInst */
	CBlocInst* GetBlocInst(T_UWORD uwX_p,T_UWORD uwY_p)
	{	
		return &cpBlocInst_m[GetBlocIndex(uwX_p,uwY_p)];
	} /* GetBlocInst */

private:
	// Virtual pure de CRef
	virtual void Init();
	virtual void Shut();
}; /* CZoneInst */


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif

