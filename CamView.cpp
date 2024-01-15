#include "CamView.h"
#include "Game.h"
#include "WorldPos.h"


CCam* CCamView::cpCam_m;
CVector<T_3DVALUE> CCamView::cPosition_m;
CVector<T_3DVALUE> CCamView::cToGo_m;
T_DATE CCamView::tPrevTime_m;


/*
 *	CCamView::CCamView
 */
CCamView::CCamView()
{
	cpCam_m=NEW CCam;
	cPosition_m.Set(520.0f,E_CAMVIEW_ALTITUDE,-520.0f);
	cToGo_m.Set(520.0f,E_CAMVIEW_ALTITUDE,-520.0f);
} /* CCamView::CCamView */


/*
 *	CCamView::~CCamView
 */
CCamView::~CCamView()
{
	DELETE cpCam_m;
} /* CCamView::~CCamView */


/*
 *	CCamView::UpdateTarget
 */
void CCamView::UpdateTarget(CVector<T_3DVALUE>* cpPosition_p)
{
	cpCam_m->SetTarget(cpPosition_p);
	cpCam_m->Update();
} /* CCamView::UpdateTarget */


/*
 *	CCamView::UpdateGoTo
 */
T_BOOL CCamView::UpdateGoTo(T_UWORD uwWorld_p,CVector<T_3DVALUE>* cpToGo_p)
{
	T_DATE tDifTime=CSystem::tTime_m-tPrevTime_m;
	tPrevTime_m=CSystem::tTime_m;
	T_FLOAT tTimeFactor=1.0f;//tDifTime/40.0f;

	if(cpToGo_p!=0)
		cToGo_m=*cpToGo_p;

	CVector<T_3DVALUE> cMove=cToGo_m-cPosition_m;
	T_3DVALUE tLen=T_3DVALUE(sqrt(double(cMove.tX*cMove.tX+cMove.tZ*cMove.tZ)));
	T_BOOL bReturn;
	if(tLen<=4.0f)
	{
		bReturn=true;
		cMove.Set(0.0f,0.0f,0.0f);
	}
	else
	{
		bReturn=false;
		cMove.Set(cMove.tX/tLen,0.0f,cMove.tZ/tLen);
	}

	cMove*=8.0f*tTimeFactor;
	cPosition_m+=cMove;

	CWorldPos cWorldPos(uwWorld_p,cPosition_m.tX,cPosition_m.tZ);
	cPosition_m.tY+=(cWorldPos.GetAltitude()+E_CAMVIEW_ALTITUDE-cPosition_m.tY)/4.0f;

	cpCam_m->SetTarget(&cPosition_m);
	cpCam_m->Update();
	return bReturn;
} /* CCamView::UpdateGoTo */

