#include "BlocInst.h"


/*
 *	CBlocInst::CBlocInst
 */
CBlocInst::CBlocInst():
	cpBloc_m(0),
	cpMeshInst_m(0)
{
} /* CBlocInst::CBlocInst */


/*
 *	CBlocInst::~CBlocInst
 */
CBlocInst::~CBlocInst()
{
	if(cpMeshInst_m!=0)
		DELETE cpMeshInst_m;
} /* CBlocInst::~CBlocInst */


/*
 *	CBlocInst::Set
 */
void CBlocInst::Set(CBloc* cpBloc_p,CBlocPos* cpBlocPos_p)
{
	cpBloc_m=cpBloc_p;
	cBlocPos_m=*cpBlocPos_p;
} /* CBlocInst::Set */


/*
 *	CBlocInst::InitCell
 */
void CBlocInst::InitCell()
{
	T_UWORD uw=0;
	for(T_UWORD uwY=0;uwY<E_BLOCINST_CELLSIZE;uwY++)
		for(T_UWORD uwX=0;uwX<E_BLOCINST_CELLSIZE;uwX++,uw++)
		{
			cpCell_m[uw].GetAltitude(
			cpBloc_m->cpMeshObj_m,
			T_3DVALUE(uwX*16)-128.0f+8.0f,
			T_3DVALUE(uwY*16)-128.0f+8.0f);
		}
} /* CBlocInst::InitCell */


/*
 *	CBlocInst::Init
 */
void CBlocInst::Init() 
{
	cpBloc_m->AddRef();
	cpBloc_m->cpMeshObj_m->CreateInstance(0,&cpMeshInst_m);

	CAnimationMgrObj *cpAnMgrObj;
	cpMeshInst_m->GetAnimMgrObjRef(&cpAnMgrObj);
	cpAnMgrObj->SetCurrentAnimation(0,0);
	cpMeshInst_m->Evaluate();
} /* CBlocInst::Init */


/*
 *	CBlocInst::Shut
 */
void CBlocInst::Shut() 
{
	if(cpMeshInst_m!=0)
	{
		DELETE cpMeshInst_m;
		cpMeshInst_m=0;
	}
	cpBloc_m->Release();
} /* CBlocInst::Shut */


/*
 *	CBlocInst::GetCellAltitude
 *
T_WORD CBlocInst::GetCellAltitude(T_FLOAT fX_p,T_FLOAT fY_p)
{
	// Coordonnée de la cellule dans le bloc
	T_UWORD uwXCell=T_UWORD((fX_p)/E_BLOCINST_CELLSIZE)%E_BLOCINST_CELLSIZE;
	T_UWORD uwYCell=T_UWORD((-fY_p)/E_BLOCINST_CELLSIZE)%E_BLOCINST_CELLSIZE;

	T_UWORD uwIndexCell=uwXCell+uwYCell*E_BLOCINST_CELLSIZE;
	return cpCell_m[uwIndexCell].biAltitude_m*4;
} /* CBlocInst::GetCellAltitude */


/*
 *	CBlocInst::GetCell
 *
CCell* CBlocInst::GetCell(T_FLOAT fX_p,T_FLOAT fZ_p)
{
	T_UWORD uwXCell=T_UWORD(fX_p/E_BLOCINST_CELLSIZE)%E_BLOCINST_CELLSIZE;
	T_UWORD uwYCell=T_UWORD(-fZ_p/E_BLOCINST_CELLSIZE)%E_BLOCINST_CELLSIZE;

	T_UWORD uwIndexCell=uwXCell+uwYCell*E_BLOCINST_CELLSIZE;
	return &cpCell_m[uwIndexCell];
} /* CBlocInst::GetCell */

