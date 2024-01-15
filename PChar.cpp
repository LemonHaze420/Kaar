#include "PChar.h"
#include "Player.h"
#include "WorldPos.h"
#include "Screen.h"
#include "Cursor.h"
#include "Interface.h"
#include "Sound.h"


/*
 *	CPChar::CPChar
 */
CPChar::CPChar(CCharacter* cpCharacter_p):
	cpCharacter_m(cpCharacter_p)
{
	cpCharacter_m->AddRef();
} /* CPChar::CPChar */


/*
 *	CPChar::~CPChar
 */
CPChar::~CPChar()
{
	cpCharacter_m->Release();
} /* CPChar::~CPChar */


/*
 *	CPChar::Update
 */
void CPChar::Update()
{
	cpCharacter_m->Update();
} /* CPChar::Update */


/*
 *	CPChar::Draw
 */
void CPChar::Draw()
{
	cpCharacter_m->Draw();
} /* CPChar::Draw */


/*
 *	CPChar::DrawSel
 */
void CPChar::DrawSel()
{
	cpCharacter_m->DrawSel();
} /* CPChar::DrawSel */


/*
 *	CPChar::GetInTo
 */
void CPChar::GetInTo(CPt<T_2DVALUE>* cp2dPosition_p)
{
	Set3dPChar(cp2dPosition_p);
} /* CPChar::GetInTo */

/*
 *	CPChar::MoveTo
 */
void CPChar::MoveTo(CPt<T_2DVALUE>* cp2dPosition_p)
{
	if(AttackTo(cp2dPosition_p))
		return;

	CVector<T_3DVALUE>* cpToGo=&cpCharacter_m->cCharPos_m.cToGo_m;
	Get3dPos(cp2dPosition_p,cpToGo);

	CWorld* cpWorld=CPlayer::cpCurWorld_m;
	T_3DVALUE tXSize=T_3DVALUE(cpWorld->uwXSize_m*1024);
	T_3DVALUE tYSize=T_3DVALUE(cpWorld->uwYSize_m*1024);

	if(cpToGo->tX<520.0f)
		cpToGo->tX=520.0f;
	if(cpToGo->tX>tXSize-520.0f)
		cpToGo->tX=tXSize-520.0f;

	if(cpToGo->tZ>-520.0f)
		cpToGo->tZ=-520.0f;
	if(cpToGo->tZ<520.0f-tYSize)
		cpToGo->tZ=520.0f-tYSize;
} /* CPChar::MoveTo */


/*
 *	CPChar::MoveTo
 */
void CPChar::MoveTo(T_LONG lDXCell,T_LONG lDYCell)
{
	CVector<T_3DVALUE>* cpToGo=&cpCharacter_m->cCharPos_m.cToGo_m;
	cpToGo->Set(
		cpCharacter_m->cCharPos_m.cPosition_m.tX+T_3DVALUE(lDXCell*16),
		0.0f,
		cpCharacter_m->cCharPos_m.cPosition_m.tZ-T_3DVALUE(lDYCell*16));
	CWorldPos cWorldPos(CPlayer::uwCurWorld_m,cpToGo->tX,cpToGo->tZ);
	cpToGo->tY=cWorldPos.GetAltitude()+cpCharacter_m->cCharPos_m.tAltitude_m;

	CWorld* cpWorld=CPlayer::cpCurWorld_m;
	T_3DVALUE tXSize=T_3DVALUE(cpWorld->uwXSize_m*1024);
	T_3DVALUE tYSize=T_3DVALUE(cpWorld->uwYSize_m*1024);

	if(cpToGo->tX<520.0f)
		cpToGo->tX=520.0f;
	if(cpToGo->tX>tXSize-520.0f)
		cpToGo->tX=tXSize-520.0f;

	if(cpToGo->tZ>-520.0f)
		cpToGo->tZ=-520.0f;
	if(cpToGo->tZ<520.0f-tYSize)
		cpToGo->tZ=520.0f-tYSize;
} /* CPChar::MoveTo */


/*
 *	CPChar::AttackTo
 */
T_BOOL CPChar::AttackTo(CPt<T_2DVALUE>* cp2dPosition_p)
{
	CCharacter* cpAttackCharacter=Get3dChar(cp2dPosition_p);
	if(cpAttackCharacter==0)
		return false;

	if(!cpCharacter_m->bMissile_m)
	{
		// Déclenchement de l'attack
		cpCharacter_m->fTireness_m-=10.0f;
		if(cpCharacter_m->fTireness_m<=0.0f)
			cpCharacter_m->fTireness_m=0.0f;
		else
		{
			CSound::cpFireLaunch_m->Play(CSound::cpCtrl_m);

			cpCharacter_m->cMissilePos_m.cToGo_m=cpAttackCharacter->cCharPos_m.cPosition_m;
			cpCharacter_m->cMissilePos_m.cPosition_m=cpCharacter_m->cCharPos_m.cPosition_m;
			cpCharacter_m->bMissile_m=true;
			cpCharacter_m->bMissileEnd_m=false;
			cpCharacter_m->cpModelInst_m->cpPartObjSmoke_m->SetState(CParticleObj::E_PARTICLEOBJSTATE_ON,CSystem::tTime_m);
			cpCharacter_m->cMissilePos_m.cToGo_m.tY+=8;
			cpCharacter_m->cMissilePos_m.cPosition_m.tY+=cpCharacter_m->cpModelInst_m->cpModel_m->tRadius_m/2.0f;
			cpCharacter_m->cMissilePos_m.tAltitude_m=0;
		}

		cpAttackCharacter->SetSel(CInterface::uwRed_m);
		// Orientation
		CVector<T_3DVALUE> cVec=cpAttackCharacter->cCharPos_m.cPosition_m-cpCharacter_m->cCharPos_m.cPosition_m;
		T_3DVALUE t2DLen=T_3DVALUE(sqrt(double(cVec.tX*cVec.tX+cVec.tZ*cVec.tZ)));
		if(t2DLen!=0.0f)
		{
			cVec.Set(cVec.tX/t2DLen,0.0f,cVec.tZ/t2DLen);

			T_MATHANVALUE tAngle;
			tAngle=acos(double(cVec.tZ));
			if(cVec.tX>0)
				tAngle=D_PI*2.0f-tAngle;
			cpCharacter_m->cCharPos_m.tToAngle_m=tAngle;
		}
		// Stop mvt
		cpCharacter_m->cCharPos_m.cToGo_m=cpCharacter_m->cCharPos_m.cPosition_m;
	}
	return true;
} /* CPChar::AttackTo */



/*
 *	CPChar::Get3dPos
 */
void CPChar::Get3dPos(CPt<T_2DVALUE>* cp2dPosition_p,CVector<T_3DVALUE>* cp3dPosition_p)
{
	CPt<T_3DVALUE> cPt;
	T_3DVALUE tYHalfSize=T_3DVALUE(CScreen::cSize_m.tY/2);
	cPt.Set((T_3DVALUE(cp2dPosition_p->tX)-tYHalfSize)/tYHalfSize,-(T_3DVALUE(cp2dPosition_p->tY)-tYHalfSize)/tYHalfSize);
	CVector<T_3DVALUE> cpWorldSeg[2];
	CPlayer::cpWorldView_m->cpCam_m->cpCamera_m->GetWorldSegmentFromNormScreenCoord(&cPt,cpWorldSeg);

	T_3DVALUE tYSegLen=cpWorldSeg[0].tY-cpWorldSeg[1].tY;
	T_3DVALUE tXSegLen=cpWorldSeg[0].tX-cpWorldSeg[1].tX;
	T_3DVALUE tZSegLen=cpWorldSeg[0].tZ-cpWorldSeg[1].tZ;

	T_3DVALUE tDelta=4.0f/tYSegLen;
	T_3DVALUE tXDelta=tDelta*tXSegLen;
	T_3DVALUE tZDelta=tDelta*tZSegLen;

	T_3DVALUE tX=cpWorldSeg[0].tX;
	T_3DVALUE tZ=cpWorldSeg[0].tZ;

	T_3DVALUE tBest=4096.0f;
	CVector<T_3DVALUE> cBest;

	// Quel est la cellule de la map la plus proche de notre segment
	T_UWORD uwWorld=cpCharacter_m->cCharPos_m.uwWorld_m;

	for(T_3DVALUE tY=cpWorldSeg[0].tY;tY>cpWorldSeg[1].tY;tY-=4.0f)
	{
		CWorldPos cWorldPos(uwWorld,tX,tZ);

		T_3DVALUE tAltitude=cWorldPos.GetAltitude();
		if(fabs(tY-tAltitude)<tBest)
		{
			cBest.Set(tX,tY,tZ);
			tBest=fabs(tY-tAltitude);
			if(tBest<4.0f)
				break;
		}
		tX-=tXDelta;
		tZ-=tZDelta;
	}
	if(tBest==4096.0f)
	{
		T_3DVALUE tAlpha=cpWorldSeg[0].tY/(cpWorldSeg[0].tY-cpWorldSeg[1].tY);
		cp3dPosition_p->tX=tAlpha*(cpWorldSeg[1].tX-cpWorldSeg[0].tX)+cpWorldSeg[0].tX;
		cp3dPosition_p->tZ=tAlpha*(cpWorldSeg[1].tZ-cpWorldSeg[0].tZ)+cpWorldSeg[0].tZ;
		CWorldPos cWorldPos(uwWorld,cp3dPosition_p->tX,cp3dPosition_p->tZ);
		cp3dPosition_p->tY=cWorldPos.GetAltitude()+cpCharacter_m->cCharPos_m.tAltitude_m;
	}
	else
	{
		cp3dPosition_p->tX=cBest.tX;
		cp3dPosition_p->tZ=cBest.tZ;
		CWorldPos cWorldPos(uwWorld,cp3dPosition_p->tX,cp3dPosition_p->tZ);
		cp3dPosition_p->tY=cWorldPos.GetAltitude()+cpCharacter_m->cCharPos_m.tAltitude_m;
	}
} /* CPChar::Get3dPos */


/*
 *	CPChar::Get3dChar
 */
CCharacter* CPChar::Get3dChar(CPt<T_2DVALUE>* cp2dPosition_p,T_BOOL bPChar_p)
{
	CPt<T_3DVALUE> cPt;
	T_3DVALUE tYHalfSize=T_3DVALUE(CScreen::cSize_m.tY/2);
	cPt.Set((T_3DVALUE(cp2dPosition_p->tX)-tYHalfSize)/tYHalfSize,-(T_3DVALUE(cp2dPosition_p->tY)-tYHalfSize)/tYHalfSize);
	CVector<T_3DVALUE> cpWorldSeg[2];
	CPlayer::cpWorldView_m->cpCam_m->cpCamera_m->GetWorldSegmentFromNormScreenCoord(&cPt,cpWorldSeg);

	T_3DVALUE tYSegLen=cpWorldSeg[0].tY-cpWorldSeg[1].tY;
	T_3DVALUE tXSegLen=cpWorldSeg[0].tX-cpWorldSeg[1].tX;
	T_3DVALUE tZSegLen=cpWorldSeg[0].tZ-cpWorldSeg[1].tZ;

	T_3DVALUE tDelta=4.0f/tYSegLen;
	T_3DVALUE tXDelta=tDelta*tXSegLen;
	T_3DVALUE tZDelta=tDelta*tZSegLen;

	T_3DVALUE tX=cpWorldSeg[0].tX;
	T_3DVALUE tZ=cpWorldSeg[0].tZ;

	// Quel est le perso de la map la plus proche de notre segment
	CWorld* cpWorld=&CUnivers::cpWorld_m[cpCharacter_m->cCharPos_m.uwWorld_m];
	CCharacter* cpCharacter=0;
	T_3DVALUE tBestLen=4096.0f;

	for(T_3DVALUE tY=cpWorldSeg[0].tY;tY>cpWorldSeg[1].tY;tY-=4.0f)
	{
		for(CCharacter* cp=cpWorld->cListCharacter_m.FindFirst();cp!=0;cp=cpWorld->cListCharacter_m.FindNext())
		{
			if(cp==cpCharacter_m)
				continue;
			if(cp->bDead_m || cp->wLife_m<=0)
				continue;
			if(bPChar_p && cp->eType_m==CCharacter::E_CHARACTER_NPC)
				continue;

			CVector<T_3DVALUE>* cpPosition=&cp->cCharPos_m.cPosition_m;
			if(tY<cpPosition->tY || tY>=cpPosition->tY+4.0f)
				continue;
/*			T_3DVALUE tRadius=cp->cpModelInst_m->cpModel_m->tRadius_m;
			if(tX>cpPosition->tX-tRadius && 
				tX<cpPosition->tX+tRadius && 
				tZ>cpPosition->tZ-tRadius && 
				tZ<cpPosition->tZ+tRadius)
*/			if(tX>cp->cCorner_m[0].tX && tX<cp->cCorner_m[3].tX &&
				tZ<cp->cCorner_m[0].tZ && tZ>cp->cCorner_m[3].tZ)
			{
//				T_3DVALUE tLen=T_3DVALUE(sqrt(double((tX-cpPosition->tX-tRadius)*(tX-cpPosition->tX-tRadius)+(tZ-cpPosition->tZ-tRadius)*(tZ-cpPosition->tZ-tRadius))));
				T_3DVALUE tLen=T_3DVALUE(sqrt(double((tX-cpPosition->tX)*(tX-cpPosition->tX)+(tZ-cpPosition->tZ)*(tZ-cpPosition->tZ))));
				if(tLen<tBestLen)
				{
					tBestLen=tLen;
					cpCharacter=cp;
				}
			}
		}
		tX-=tXDelta;
		tZ-=tZDelta;
	}
	return cpCharacter;
} /* CPChar::Get3dChar */


/*
 *	CPChar::Set3dPChar
 */
void CPChar::Set3dPChar(CPt<T_2DVALUE>* cp2dPosition_p)
{
	CCharacter* cp=Get3dChar(cp2dPosition_p,true);
	if(cp==0)
		return;
	
//	cp->SetSel(CInterface::uwGreen_m);
	CCursor::WaitNoClick();

	if(cp==CPlayer::cpCurCharacter_m)
		return;

	for(T_UWORD uw=0;uw<CPlayer::uwNbPChar_m;uw++)
	{
		if(CPlayer::cppPChar_m[uw]->cpCharacter_m==cp)
			break;
	}
	CPlayer::SetActive(uw);
} /* CPChar::Set3dPChar */

