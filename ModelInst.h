#ifndef _INCLUDE_MODELINST_
#define _INCLUDE_MODELINST_
/**************************************************************************************
 *
 **************************************************************************************/
#include "System.h"
#include "Model.h"
#include "DivHea\crpasmok.h"

#include "CrSprSha.h"


/*
 *	CModelInst
 */
class CModelInst
{
public:
	CModel* cpModel_m;
	CMeshObj* cpMeshInst_m;
	CAnimationMgrObj* cpAnMgrObj_m;
	CParticleObj* cpPartObjSmoke_m;
	CParticleObj* cpPartObjImpact_m;
	CParticleObjCallbackSmoke* cpParticleObjCallbackSmoke_m;
	CParticleObjCallbackSmoke* cpParticleObjCallbackImpact_m;


	CModelInst(T_UWORD uwModel_p);
	~CModelInst();

	void Draw(CVector<T_3DVALUE>* cpPosition_p,T_MATHANVALUE tAngle_p,T_UWORD uwShadow_p,T_BOOL bDead_p);
	void DrawMissile(CVector<T_3DVALUE>* cpPosition_p);
	void DrawImpact(CVector<T_3DVALUE>* cpPosition_p);

private:
	CSprShadow cShad_m;
	CMeshObj* GetMeshShadow(T_3DVALUE tX_p,T_3DVALUE tY_p);
	void ComputeShadow(CVector<T_3DVALUE>* cpPosition_p,T_MATHANVALUE tAngle_p,T_UWORD uwShadow_p,T_BOOL bDead_p);
}; /* CModelInst */


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif

