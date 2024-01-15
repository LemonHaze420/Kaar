#include "BlocItem.h"


/*
 *	CBlocItem::CBlocItem
 */
CBlocItem::CBlocItem():
	cpZoneInst_m(0),
	cpBlocInst_m(0),
	cpMeshObj_m(0)
{
} /* CBlocItem::CBlocItem */


/*
 *	CBlocItem::Set
 */
void CBlocItem::Set(CZoneInst* cpZoneInst_p,CBlocInst* cpBlocInst_p)
{
	cpZoneInst_m=cpZoneInst_p;
	cpBlocInst_m=cpBlocInst_p;

	if(cpBlocInst_m==0)
		return;

	// Assign instance de mesh
	cpMeshObj_m=cpBlocInst_m->cpMeshInst_m;
} /* CBlocItem::Set */


/*
 *	CBlocItem::Draw
 */
void CBlocItem::Draw()
{
	if(cpZoneInst_m==0 || cpBlocInst_m==0)
		return;

	C3dTransformation *cpRepTrans;
	cpMeshObj_m->GetRepTransRef(&cpRepTrans);

	CVector<T_FLOAT> cVec;
	cVec.Set(D_PI/2,D_PI/2,3*D_PI/2);
	cpRepTrans->SetRot(&cVec);
	
	cVec.Set(
		T_FLOAT(cpZoneInst_m->uwX_m*CZone::E_ZONE_SIZE*256+cpBlocInst_m->cBlocPos_m.biX_m*256+128),
		T_FLOAT(cpZoneInst_m->wAltitude_m+cpBlocInst_m->cBlocPos_m.biAltitude_m*64),
		T_FLOAT(-cpZoneInst_m->uwY_m*CZone::E_ZONE_SIZE*256-cpBlocInst_m->cBlocPos_m.biY_m*256-128));
	cpRepTrans->SetTrans(&cVec);

	cpMeshObj_m->InvalidateRepCache();
	cpMeshObj_m->Evaluate();
} /* CBlocItem::Draw */


