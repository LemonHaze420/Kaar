#include "WorldView.h"
#include "Univers.h"
#include "Player.h"


CZoneView* CWorldView::cpZoneView_m;
CSun* CWorldView::cpSun_m;
CCellView* CWorldView::cpCellView_m;
CPlayer* CWorldView::cpPlayer_m;



CSun::CSun():
	cpLight_m(0)
{
/*	CSystem::cp3d_m->CreateLight(&cpLight_m);
	cpLight_m->SetLightType(CLight::E_LIGHTTYPE_POINT);

	CVector<T_3DVALUE> cLightPos;
	cLightPos.Set(0,0,0);
	cpLight_m->SetLightPos(&cLightPos);

	cpLight_m->SetLightRange(0);

	cpLight_m->SetLightFlags(CLight::F_LIGHT_COLOR);
	CColor cColor;
	cColor.White();
	cpLight_m->SetLightColor(&cColor);
*/
}
CSun::~CSun()
{
//	DELETE cpLight_m;
}


/*
 *	CWorldView::CWorldView
 */
CWorldView::CWorldView(CPlayer* cpPlayer_p)
{
	cpZoneView_m=NEW CZoneView;
	cpCellView_m=NEW CCellView[E_WORLDVIEW_CELLSIZE2];
	cpPlayer_m=cpPlayer_p;
	// TODO LIGHT
	cpSun_m=NEW CSun();
} /*CWorldView::CWorldView */


/*
 *	CWorldView::~CWorldView
 */
CWorldView::~CWorldView()
{
	DELETE []cpCellView_m;
	DELETE cpZoneView_m;
	// TODO LIGHT
	DELETE cpSun_m;
} /* CWorldView::~CWorldView */


/*
 *	CWorldView::Update
 */
void CWorldView::Update(CVector<T_3DVALUE>* cpPosition_p)
{
/*	static T_UWORD uwLight=0;
	cpSun_m->cpLight_m->SetLightRange(uwLight);
	if(uwLight<3000)
		uwLight+=32;
*/
	if(cpPosition_p==0)
	{
		T_ULONG ulXSize=cpPlayer_m->cpCurWorld_m->uwXSize_m*1024;
		T_ULONG ulYSize=cpPlayer_m->cpCurWorld_m->uwYSize_m*1024;
		static T_3DVALUE tAngle;
		static T_3DVALUE tDiameter=0.01f;
		tDiameter+=0.01f;
		CVector<T_3DVALUE> cVec;
		cVec.tX=(ulXSize+ulXSize*cos(tAngle)*tDiameter)/2;
		cVec.tZ=(ulYSize+ulYSize*sin(tAngle)*cos(tAngle/3)*tDiameter)/-2;
		tAngle+=0.02f;
		if(tDiameter>=1.0f)
			tDiameter=0.01f;

		UpdateGoTo(cpPlayer_m->uwCurWorld_m,&cVec);
		cpZoneView_m->Update(cpPlayer_m->cpCurWorld_m,cPosition_m.tX,cPosition_m.tZ);
//		cpSun_m->cpLight_m->SetLightPos(&cPosition_m);
	}
	else
	{
		cPosition_m=*cpPosition_p;
		UpdateTarget(cpPosition_p);
		cpZoneView_m->Update(cpPlayer_m->cpCurWorld_m,cpPosition_p->tX,cpPosition_p->tZ);
//		cpSun_m->cpLight_m->SetLightPos(cpPosition_p);
	}
} /* CWorldView::Update */


/*
 *	CWorldView::Draw
 */
void CWorldView::Draw(T_BOOL bDebug_p)
{
	// TODO LIGHT
//	CSystem::cpCtx_m->AddLight(cpSun_m->cpLight_m);
	CSystem::cpCtx_m->ComputeLightAndFog();

	if(bDebug_p)
		DrawDebug(12);
	else 
		cpZoneView_m->Draw();
} /* CWorldView::Update */



/*
 *	CWorldView::DrawDebug
 */
void CWorldView::DrawDebug(T_UWORD uwBloc_p)
{
	CVector<T_3DVALUE> cVec;
	CBlocItem* cpBlocItem=&cpZoneView_m->cBlocView_m.cpBlocItem_m[uwBloc_p];
	if(cpBlocItem->cpBlocInst_m==0 || cpBlocItem->cpZoneInst_m==0)
		return;

	CZoneInst* cpZoneInst=cpBlocItem->cpZoneInst_m;
	CBlocInst* cpBlocInst=cpBlocItem->cpBlocInst_m;
	
	cVec.Set(
		T_3DVALUE(cpZoneInst->uwX_m*CZone::E_ZONE_SIZE*256+cpBlocInst->cBlocPos_m.biX_m*256),
		T_3DVALUE(cpZoneInst->wAltitude_m+cpBlocInst->cBlocPos_m.biAltitude_m*64),
		T_3DVALUE(-cpZoneInst->uwY_m*CZone::E_ZONE_SIZE*256-cpBlocInst->cBlocPos_m.biY_m*256));

	T_UWORD uw=0;
	for(T_UWORD uwY=0;uwY<E_WORLDVIEW_CELLSIZE;uwY++)
		for(T_UWORD uwX=0;uwX<E_WORLDVIEW_CELLSIZE;uwX++,uw++)
		{
			T_3DVALUE tAltitude=T_3DVALUE(cpBlocInst->cpCell_m[uw].biAltitude_m*4);
			cpCellView_m[uw].Draw(cVec.tX+T_3DVALUE(uwX*16),cVec.tY+tAltitude,cVec.tZ-T_3DVALUE(uwY*16));
		}
} /* CWorldView::DrawDebug */



