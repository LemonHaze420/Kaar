#ifndef _INCLUDE_CELL_
#define _INCLUDE_CELL_
/**************************************************************************************
 * Cellule de bloc sur 16bits (256 par bloc)
 **************************************************************************************/
#include "System.h"


/*
 *	CCell
 */
class CCell
{
public:
	// 8 attributs maxi
	enum ECellType
	{
		E_CELL_TYPENONE,		// passe pas
		E_CELL_TYPEGROUND,		// passe
		E_CELL_TYPEMOUNTAIN,	// passe mais dur
		E_CELL_TYPESWAMP,	// passe mais dur
		E_CELL_TYPEWATER,	// nage
		E_CELL_TYPEICE	// glisse
	};
	// 6 couches d'évènement
	enum EEventID
	{
		E_CELL_EVENTID0,
		E_CELL_EVENTID1,
		E_CELL_EVENTID2,
		E_CELL_EVENTID3,
		E_CELL_EVENTID4,
		E_CELL_EVENTID5
	};
	T_WORD biAltitude_m:7;	// Altitude des cellules entre -256& +255 codée /4
	ECellType biType_m:3;
	T_UWORD biEvent_m:6;

	void GetAltitude(CMeshObj* cpMeshObj_p,T_3DVALUE tX_p,T_3DVALUE tY_p);

private:
	T_3DVALUE Max(T_3DVALUE tA_p,T_3DVALUE tB_p) {return (tA_p>tB_p)?tA_p:tB_p;}

	T_BOOL PointInSegment(CVector<T_3DVALUE>* cpP0_p,CVector<T_3DVALUE>* cpP1_p,CVector<T_3DVALUE>* cpM_p);
	T_3DVALUE AltitudeInSegment(CVector<T_3DVALUE>* cpP0_p,CVector<T_3DVALUE>* cpP1_p,CVector<T_3DVALUE>* cpM_p);
	T_BOOL PointInFace(CVector<T_3DVALUE>* cpP0_p,CVector<T_3DVALUE>* cpP1_p,CVector<T_3DVALUE>* cpP2_p,CVector<T_3DVALUE>* cpM_p);
	T_3DVALUE AltitudeInFace(CVector<T_3DVALUE>* cpP0_p,CVector<T_3DVALUE>* cpP1_p,CVector<T_3DVALUE>* cpP2_p,CVector<T_3DVALUE>* cpM_p);
}; /* CCell */


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif


