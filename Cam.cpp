#include "Cam.h"

// Angle vue
#define D_CAMFIXANGLE -1.3f
//#define D_CAMFIXANGLE -D_PI/2.0f

#define D_CAMFIXALTITUDE -450.0f
//#define D_CAMFIXALTITUDE -1500.0f


/*
 *	CCam::CCam
 */
CCam::CCam()
{
	CSystem::cp3d_m->CreateCamera(CSystem::cpMath_m,&cpCamera_m);
	CSystem::cpMath_m->CreateMatrix(&cpMatrix_m);
	cPosition_m.Set(0.0f,D_CAMFIXALTITUDE,0.0f);
	cRot_m.Set(D_CAMFIXANGLE,0.0f,0.0f);
	Update();
	GetDeltaFromTarget();
} /* CCam::CCam */


/*
 *	CCam::~CCam
 */
CCam::~CCam()
{
	DELETE cpCamera_m;
	DELETE cpMatrix_m;
} /* CCam::CCam */


/*
 *	CCam::GetXPos
 */
T_3DVALUE CCam::GetXPos()
{
	return -cPosition_m.tX+cDelta_m.tX;
} /* CCam::GetXPos */


/*
 *	CCam::GetYPos
 */
T_3DVALUE CCam::GetYPos()
{
	return -cPosition_m.tZ+cDelta_m.tZ;
} /* CCam::GetYPos */


/*
 *	CCam::GetAltitude
 */
T_3DVALUE CCam::GetAltitude()
{
	return -cPosition_m.tY+cDelta_m.tY;
} /* CCam::GetAltitude */


/*
 *	CCam::SetRot
 */
void CCam::SetRot(T_FLOAT fX_p,T_FLOAT fY_p)
{
	cRot_m.Set(D_CAMFIXANGLE+fX_p,fY_p,0.0f);
} /* CCam::SetRot */


/*
 *	CCam::SetPos
 */
void CCam::SetPos(T_FLOAT fH_p)
{
	cPosition_m.tY=D_CAMFIXALTITUDE+fH_p;
} /* CCam::SetPos */


/*
 *	CCam::Update
 */
void CCam::Update()
{
	cpMatrix_m->GenXYZ((CVector<T_MATHANVALUE> *)&cRot_m);
	cpMatrix_m->SetTrans(&cPosition_m);
	cpCamera_m->SetMatrixRef(cpMatrix_m);	// TODO ISNEEDED?
	cpCamera_m->UpdateFromMatrixRef();

	cpCamera_m->SetFustrum(100,4000,D_PI/4,CSystem::cpVp_m);
	CSystem::cpVp_m->SetXYRenderRatio(cpCamera_m);

	CSystem::cpCtx_m->SetCameraRef(cpCamera_m);
} /* CCam::Update */


/*
 *	CCam::GetDeltaFromTarget
 */
void CCam::GetDeltaFromTarget()
{
	CPt<T_3DVALUE> cPt(0.0f,0.0f);
	CVector<T_3DVALUE> cpWorldSeg[2];
	cpCamera_m->GetWorldSegmentFromNormScreenCoord(&cPt,cpWorldSeg);

	T_3DVALUE tAlpha=cpWorldSeg[0].tY/(cpWorldSeg[0].tY-cpWorldSeg[1].tY);
	cDelta_m.tX=-(tAlpha*(cpWorldSeg[1].tX-cpWorldSeg[0].tX)+cpWorldSeg[0].tX);
	cDelta_m.tZ=(tAlpha*(cpWorldSeg[1].tZ-cpWorldSeg[0].tZ)+cpWorldSeg[0].tZ);
	cDelta_m.tY=D_CAMFIXALTITUDE;
} /* CCam::GetDeltaFromTarget */


/*
 *	CCam::SetTarget
 */
void CCam::SetTarget(CVector<T_3DVALUE>* cpPosition_p)
{
	cTarget_m=*cpPosition_p;
	cPosition_m.tX=-cpPosition_p->tX+cDelta_m.tX;
	cPosition_m.tY=-cpPosition_p->tY+cDelta_m.tY;
	cPosition_m.tZ=-cpPosition_p->tZ+cDelta_m.tZ;
} /* CCam::SetTarget */


/*
 *	CCam::Get3dPos
 *
void CCam::Get3dPos(CPt<T_2DVALUE>* cp2dPosition_p,CVector<T_3DVALUE>* cp3dPosition_p)
{
	CPt<T_3DVALUE> cPt;
	T_3DVALUE tYHalfSize=T_3DVALUE(CScreen::cSize_m.tY/2);
	cPt.Set((T_3DVALUE(cp2dPosition_p->tX)-tYHalfSize)/tYHalfSize,-(T_3DVALUE(cp2dPosition_p->tY)-tYHalfSize)/tYHalfSize);
	CVector<T_3DVALUE> cpWorldSeg[2];
	cpCamera_m->GetWorldSegmentFromNormScreenCoord(&cPt,cpWorldSeg);

	T_3DVALUE tAlpha=cpWorldSeg[0].tY/(cpWorldSeg[0].tY-cpWorldSeg[1].tY);
	cp3dPosition_p->tX=tAlpha*(cpWorldSeg[1].tX-cpWorldSeg[0].tX)+cpWorldSeg[0].tX;
	cp3dPosition_p->tZ=tAlpha*(cpWorldSeg[1].tZ-cpWorldSeg[0].tZ)+cpWorldSeg[0].tZ;
	cp3dPosition_p->tY=0.0f;

	CWorld* cpWorld=&CKaar::cpUnivers_m->cpWorld_m[CKaar::cpGame_m->cpCharacter_m->uwWorld_m];
	CZoneInst* cpZoneInst=cpWorld->GetZoneInst(cp3dPosition_p->tX,cp3dPosition_p->tZ);
	CBlocInst* cpBlocInst=(cpZoneInst!=0)?cpZoneInst->GetBlocInst(cp3dPosition_p->tX,cp3dPosition_p->tZ):0;
	if(cpBlocInst!=0)
		cp3dPosition_p->tY+=cpBlocInst->GetCellAltitude(cp3dPosition_p->tX,cp3dPosition_p->tZ);
} /* CCam::Get3dPos */



