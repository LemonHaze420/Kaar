#ifndef _INCLUDE_BLOCINST_
#define _INCLUDE_BLOCINST_
/**************************************************************************************
 * Description instance bloc = pointeur sur bloc 3D + altitude
 **************************************************************************************/
#include "System.h"
#include "Ref.h"
#include "Bloc.h"
#include "Cell.h"


class CZone;


/*
 *	CBlocInst
 */
class CBlocInst:public CRef
{
public:
	// Taille en cases de grille 
	enum EBlocInstCellSize
	{
		E_BLOCINST_CELLSIZE=16,
		E_BLOCINST_CELLSIZE2=E_BLOCINST_CELLSIZE*E_BLOCINST_CELLSIZE
	};
	CCell cpCell_m[E_BLOCINST_CELLSIZE2];
	CBloc* cpBloc_m;
	CBlocPos cBlocPos_m;

	CMeshObj* cpMeshInst_m;

	CBlocInst();	// Constructeur vide pour tableau
	~CBlocInst();

	void Set(CBloc* cpBloc_p,CBlocPos* cpBlocPos_p);
	void InitCell();

	/* GetXCell */
	T_UWORD GetXCell(T_3DVALUE tX_p)
	{
		return T_UWORD(tX_p/16.0f)%E_BLOCINST_CELLSIZE;
	} /* GetXCell */


	/* GetYCell */
	T_UWORD GetYCell(T_3DVALUE tY_p)
	{
		return T_UWORD(-tY_p/16.0f)%E_BLOCINST_CELLSIZE;
	} /* GetYCell */


	/* GetCellIndex */
	T_ULONG GetCellIndex(T_UWORD uwX_p,T_UWORD uwY_p)
	{
		return uwX_p+E_BLOCINST_CELLSIZE*uwY_p;
	} /* GetCellIndex */


	/* GetCellIndex */
	T_ULONG GetCellIndex(T_3DVALUE tX_p,T_3DVALUE tY_p)
	{	
		return GetCellIndex(GetXCell(tX_p),GetYCell(tY_p));
	} /* GetCellIndex */


	/* GetCell */
	CCell* GetCell(T_3DVALUE tX_p,T_3DVALUE tY_p)
	{	
		return &cpCell_m[GetCellIndex(tX_p,tY_p)];
	} /* GetCell */


	/* GetCell */
	CCell* GetCell(T_UWORD uwX_p,T_UWORD uwY_p)
	{	
		return &cpCell_m[GetCellIndex(uwX_p,uwY_p)];
	} /* GetCell */

private:
	// Virtual pure de CRef
	virtual void Init();
	virtual void Shut();
}; /* CBlocInst */


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif


