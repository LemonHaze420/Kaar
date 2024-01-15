#include "Character.h"
#include "Univers.h"
#include "Player.h"
#include "Interface.h"
#include "Screen.h"
#include "System.h"
#include "Sound.h"


#define D_CHARACTER_SELSIZE 8

/*
 *	CCharacter::CCharacter
 */
CCharacter::CCharacter():
	uwModel_m(0),
	eType_m(ECharacterType(0)),
	chpName_m(0),
	wLife_m(0),
	uwTireness_m(0),
	fTireness_m(0.0f),
	tTireUpdate_m(0),
	cpModelInst_m(0),
	uwSelSize_m(D_CHARACTER_SELSIZE),
	uwAnim_m(0),
	tAnim_m(0),
	bUpdate_m(true),
	tMissile_m(0),
	bMissile_m(false),
	bMissileEnd_m(false),
	bEnd_m(false),
	bDead_m(false),
	cpCharPath_m(0),
	uwNbCharPath_m(0)
{
} /* CCharacter::CCharacter */


/*
 *	CCharacter::CCharacter
 */
CCharacter::CCharacter(T_UWORD uwModel_p,ECharacterType eType_p,char* chpName_p,
		T_UWORD uwWorld_p,
		T_UWORD uwXZone_p,T_UWORD uwYZone_p,
		T_UWORD uwXBloc_p,T_UWORD uwYBloc_p,
		T_UWORD uwXCell_p,T_UWORD uwYCell_p):
	uwModel_m(uwModel_p),
	eType_m(eType_p),
	wLife_m(CUnivers::cpModel_m[uwModel_m].wLife_m),
	uwTireness_m(CUnivers::cpModel_m[uwModel_m].uwTireness_m),
	fTireness_m(T_FLOAT(uwTireness_m)),
	tTireUpdate_m(0),
	cpModelInst_m(0),
	uwSelSize_m(D_CHARACTER_SELSIZE),
	uwAnim_m(0),
	tAnim_m(0),
	bUpdate_m(true),
	tMissile_m(0),
	bMissile_m(false),
	bMissileEnd_m(false),
	bEnd_m(false),
	bDead_m(false),
	cpCharPath_m(0),
	uwNbCharPath_m(0)
{
	chpName_m=NEW char[strlen(chpName_p)+1];
	strcpy(chpName_m,chpName_p);
	for(T_UWORD uw=0;uw<strlen(chpName_m);uw++)
		if(chpName_m[uw]=='_')
			chpName_m[uw]=' ';

	cCharPos_m.Set(CUnivers::cpModel_m[uwModel_m].wAltitude_m*64+2,
		uwWorld_p,uwXZone_p,uwYZone_p,uwXBloc_p,uwYBloc_p,uwXCell_p,uwYCell_p);
	cHome_m.tX=cCharPos_m.cPosition_m.tX;
	cHome_m.tY=cCharPos_m.cPosition_m.tZ;
} /* CCharacter::CCharacter */


/*
 *	CCharacter::~CCharacter
 */
CCharacter::~CCharacter()
{
	if(uwNbCharPath_m!=0)
		DELETE cpCharPath_m;
	if(chpName_m!=0)
		DELETE []chpName_m;
	if(cpModelInst_m!=0)
		DELETE cpModelInst_m;
} /* CCharacter::~CCharacter */


/*
 *	CCharacter::Init
 */
void CCharacter::Init()
{
	cpModelInst_m=NEW CModelInst(uwModel_m);
	cCharPos_m.StartAltitude();
	fTireness_m=T_FLOAT(cpModelInst_m->cpModel_m->uwTireness_m);
	switch(cpModelInst_m->cpModel_m->eRace_m)
	{
	default:
	case CModel::E_MODEL_ANIMAL:
		tSpeed_m=3.0f;
		break;
	case CModel::E_MODEL_UERG:
		tSpeed_m=5.0f;
		break;
	case CModel::E_MODEL_NOMAREG:
		tSpeed_m=7.0f;
		break;
	case CModel::E_MODEL_HUMAN:
		tSpeed_m=30.0f;
		break;
	}
	if(strcmp(cpModelInst_m->cpModel_m->chpMesh_m,"STRACMITE")==0)
	{
		uwShadow_m=0;
		cpDead_m=CSound::cpStracmiteMort_m;
		cpAttack_m=CSound::cpStracmiteAttack_m;
		cpImpact_m=CSound::cpStracmiteImpact_m;
		for(T_UWORD uw=0;uw<4;uw++)
			cpOrder_m[uw]=cpImpact_m;
	}
	else if(strcmp(cpModelInst_m->cpModel_m->chpMesh_m,"UERG")==0)
	{
		uwShadow_m=1;
		cpDead_m=CSound::cpUergMort_m;
		cpAttack_m=CSound::cpUergAttack_m;
		cpImpact_m=CSound::cpUergImpact_m;
		for(T_UWORD uw=0;uw<4;uw++)
			cpOrder_m[uw]=CSound::cpUergOrdre_m[uw];
	}
	else if(strcmp(cpModelInst_m->cpModel_m->chpMesh_m,"RAAGAS")==0)
	{
		uwShadow_m=2;
		cpDead_m=CSound::cpRaagasMort_m;
		cpAttack_m=CSound::cpRaagasAttack_m;
		cpImpact_m=CSound::cpRaagasImpact_m;
		for(T_UWORD uw=0;uw<4;uw++)
			cpOrder_m[uw]=CSound::cpRaagasOrdre_m[uw];
	}
	else if(strcmp(cpModelInst_m->cpModel_m->chpMesh_m,"BARIVE")==0)
	{
		uwShadow_m=3;
		cpDead_m=CSound::cpUergMort_m;
		cpAttack_m=CSound::cpUergAttack_m;
		cpImpact_m=CSound::cpUergImpact_m;
		for(T_UWORD uw=0;uw<4;uw++)
			cpOrder_m[uw]=CSound::cpUergOrdre_m[uw];
	}
	else if(strcmp(cpModelInst_m->cpModel_m->chpMesh_m,"FOURRAAG")==0)
	{
		uwShadow_m=4;
		cpDead_m=CSound::cpFourmantaMort_m;
		cpAttack_m=CSound::cpFourmantaAttack_m;
		cpImpact_m=CSound::cpFourmantaImpact_m;
		for(T_UWORD uw=0;uw<4;uw++)
			cpOrder_m[uw]=CSound::cpFourmantaOrdre_m[uw];
	}
	else if(strcmp(cpModelInst_m->cpModel_m->chpMesh_m,"SAUREILLE")==0)
	{
		uwShadow_m=5;
		cpDead_m=CSound::cpSaureilleMort_m;
		cpImpact_m=CSound::cpSaureilleImpact_m;
		cpAttack_m=cpImpact_m;
		for(T_UWORD uw=0;uw<4;uw++)
			cpOrder_m[uw]=cpImpact_m;
	}
	else if(strcmp(cpModelInst_m->cpModel_m->chpMesh_m,"UERGP1")==0)
	{
		uwShadow_m=6;
		cpDead_m=CSound::cpUergMort_m;
		cpImpact_m=CSound::cpUergImpact_m;
		cpAttack_m=CSound::cpUergAttack_m;
		for(T_UWORD uw=0;uw<4;uw++)
			cpOrder_m[uw]=CSound::cpUergOrdre_m[uw];
	}
	else if(strcmp(cpModelInst_m->cpModel_m->chpMesh_m,"UERGP2")==0)
	{
		uwShadow_m=7;
		cpDead_m=CSound::cpUergMort_m;
		cpImpact_m=CSound::cpUergImpact_m;
		cpAttack_m=CSound::cpUergAttack_m;
		for(T_UWORD uw=0;uw<4;uw++)
			cpOrder_m[uw]=CSound::cpUergOrdre_m[uw];
	}
	else if(strcmp(cpModelInst_m->cpModel_m->chpMesh_m,"UERGP3")==0)
	{
		uwShadow_m=8;
		cpDead_m=CSound::cpUergMort_m;
		cpImpact_m=CSound::cpUergImpact_m;
		cpAttack_m=CSound::cpUergAttack_m;
		for(T_UWORD uw=0;uw<4;uw++)
			cpOrder_m[uw]=CSound::cpUergOrdre_m[uw];
	}
	else if(strcmp(cpModelInst_m->cpModel_m->chpMesh_m,"RAAGGARD")==0)
	{
		uwShadow_m=9;
		cpDead_m=CSound::cpRaagasMort_m;
		cpAttack_m=CSound::cpRaagasAttack_m;
		cpImpact_m=CSound::cpRaagasImpact_m;
		for(T_UWORD uw=0;uw<4;uw++)
			cpOrder_m[uw]=CSound::cpRaagasOrdre_m[uw];
	}
	else  
	{
		uwShadow_m=0;
		cpDead_m=0;
		cpAttack_m=0;
		cpImpact_m=0;
	}
} /* CCharacter::Init */


/*
 *	CCharacter::Shut
 */
void CCharacter::Shut()
{
	if(cpModelInst_m!=0)
	{
		DELETE cpModelInst_m;
		cpModelInst_m=0;
	}
} /* CCharacter::Shut */


/*
 *	CCharacter::operator=
 */
CCharacter& CCharacter::operator=(CCharacter& crCharacter_p)
{
	uwModel_m=crCharacter_p.uwModel_m;
	eType_m=crCharacter_p.eType_m;
	chpName_m=NEW char[strlen(crCharacter_p.chpName_m)+1];
	strcpy(chpName_m,crCharacter_p.chpName_m);
	wLife_m=crCharacter_p.wLife_m;
	uwTireness_m=crCharacter_p.uwTireness_m;

	cCharPos_m=crCharacter_p.cCharPos_m;
	cHome_m=crCharacter_p.cHome_m;

	cListCharPath_m=crCharacter_p.cListCharPath_m;
	uwNbCharPath_m=crCharacter_p.uwNbCharPath_m;
	if(uwNbCharPath_m!=0)
	{
		cpCharPath_m=NEW CCharPath[uwNbCharPath_m];
		memcpy(cpCharPath_m,crCharacter_p.cpCharPath_m,sizeof(CCharPath)*uwNbCharPath_m);
	}
	return *this;
} /* CCharacter::operator= */


/*
 *	CCharacter::Draw
 */
void CCharacter::Draw()
{
	CVector<T_3DVALUE> cVec=CPlayer::cpWorldView_m->cpCam_m->cTarget_m;

	cVec-=cCharPos_m.cPosition_m;
	T_3DVALUE tLen=cVec.tX*cVec.tX+cVec.tZ*cVec.tZ;
	if(tLen<704*704)
	{
		if(wLife_m<=0)
			cpModelInst_m->Draw(&cCharPos_m.cPosition_m,cCharPos_m.tAngle_m,uwShadow_m,true);
		else
			cpModelInst_m->Draw(&cCharPos_m.cPosition_m,cCharPos_m.tAngle_m,uwShadow_m,false);
	}
	else
	{
		if(wLife_m<=0)
			bDead_m=true;
	}

	if(bMissile_m)
	{
		cpModelInst_m->DrawMissile(&cMissilePos_m.cPosition_m);
		if(bMissileEnd_m)
			cpModelInst_m->DrawImpact(&cMissilePos_m.cPosition_m);
	}
} /* CCharacter::Draw */


/*
 *	CCharacter::Update
 */
T_BOOL CCharacter::Update()
{
	if(bMissile_m)
	{
		if(!bMissileEnd_m)
		{
			if(cMissilePos_m.Update(24.0f,CCharPos::E_CHARPOS_ALTITUDEFREE))
			{
				// Impact
				CSound::cpFireImpact_m->Play(CSound::cpCtrl_m);
				bMissileEnd_m=true;
				cpModelInst_m->cpPartObjSmoke_m->SetState(CParticleObj::E_PARTICLEOBJSTATE_OFF,CSystem::tTime_m);
				cpModelInst_m->cpPartObjImpact_m->SetState(CParticleObj::E_PARTICLEOBJSTATE_ON,CSystem::tTime_m);
				tMissile_m=CSystem::tTime_m+500;
				// Check si dans rayon d'autres character pour baisse de vie
				for(CCharacter* cp=CPlayer::cpCurWorld_m->cListCharacter_m.FindFirst();cp!=0;cp=CPlayer::cpCurWorld_m->cListCharacter_m.FindNext())
				{
					if(cp->wLife_m<=0)
						continue;
					CVector<T_3DVALUE> cVec=cp->cCharPos_m.cPosition_m-cMissilePos_m.cPosition_m;
					T_3DVALUE tLen=cVec.tX*cVec.tX+cVec.tY*cVec.tY+cVec.tZ*cVec.tZ;
					if(tLen<32.0f*32.0f)
					{
						cp->wLife_m-=10;
						if(cp->wLife_m<=0)
						{
							if(cp->cpDead_m!=0)
								cp->cpDead_m->Play(CSound::cpCtrl_m);
							cp->wLife_m=0;
						}
						else
						{
							if(cp->cpImpact_m!=0)
								cp->cpImpact_m->Play(CSound::cpCtrl_m);
						}
					}
				}

			}
		}
		else
		{
			if(!bEnd_m && tMissile_m<CSystem::tTime_m && cpModelInst_m->cpPartObjSmoke_m->GetNbActiveParticles()==0)
			{
				tMissile_m=CSystem::tTime_m+500;
				cpModelInst_m->cpPartObjImpact_m->SetState(CParticleObj::E_PARTICLEOBJSTATE_OFF,tMissile_m);
				bEnd_m=true;
			}
			else if(tMissile_m<CSystem::tTime_m && cpModelInst_m->cpPartObjImpact_m->GetNbActiveParticles()==0)
			{
				bMissile_m=false;
				bEnd_m=false;
			}
		}
	}

	if(wLife_m<=0)
	{
		cpModelInst_m->cpAnMgrObj_m->SetCurrentAnimation(CSystem::tTime_m,4);
		T_DURATION tAnimDur;
		cpModelInst_m->cpAnMgrObj_m->GetAnimDuration(uwAnim_m,&tAnimDur);
		tAnim_m=CSystem::tTime_m+tAnimDur;
		return cCharPos_m.Update(16.0f,CCharPos::E_CHARPOS_ALTITUDEFREE);
	}

	if(tTireUpdate_m==0)
		tTireUpdate_m=CSystem::tTime_m;

	if(fTireness_m<0)
		fTireness_m=0.0f;
	fTireness_m+=0.0005f*(CSystem::tTime_m-tTireUpdate_m);
	if(fTireness_m>T_FLOAT(cpModelInst_m->cpModel_m->uwTireness_m))
		fTireness_m=T_FLOAT(cpModelInst_m->cpModel_m->uwTireness_m);

	uwTireness_m=T_UWORD(fTireness_m);
	tTireUpdate_m=CSystem::tTime_m;

	T_BOOL bReturn=cCharPos_m.Update(tSpeed_m,CCharPos::E_CHARPOS_ROTATE);
	if(tAnim_m<CSystem::tTime_m || bUpdate_m!=bReturn)
	{
		if(bReturn)
		{
			if(rand()%6)
				uwAnim_m=0;
			else
			{
				T_UWORD uwAnim;
				do
				{
					uwAnim=2+rand()%2;
				}
				while(uwAnim_m==uwAnim);
				uwAnim_m=uwAnim;
			}
		}
		else
			uwAnim_m=1;

		cpModelInst_m->cpAnMgrObj_m->SetCurrentAnimation(CSystem::tTime_m,uwAnim_m);
		T_DURATION tAnimDur;
		cpModelInst_m->cpAnMgrObj_m->GetAnimDuration(uwAnim_m,&tAnimDur);
		tAnim_m=CSystem::tTime_m+tAnimDur;
		bUpdate_m=bReturn;

		CVector<T_3DVALUE> cPosition=CPlayer::cpWorldView_m->cpCam_m->cTarget_m;
		cPosition-=cCharPos_m.cPosition_m;;
		T_3DVALUE tLen=cPosition.tX*cPosition.tX+cPosition.tZ*cPosition.tZ;
		if(tLen<384*384)
		{
			if(strcmp(cpModelInst_m->cpModel_m->chpMesh_m,"BARIVE")==0)
				CSound::cpVolBarive_m->Play(CSound::cpCtrl_m);
			else if(strcmp(cpModelInst_m->cpModel_m->chpMesh_m,"SAUREILLE")==0)
				CSound::cpVolSaur_m->Play(CSound::cpCtrl_m);
			else if(strcmp(cpModelInst_m->cpModel_m->chpMesh_m,"FOURRAAG")==0)
				CSound::cpVolFour_m->Play(CSound::cpCtrl_m);
		}
	}
	return bReturn;
} /* CCharacter::Update */


/*
 *	CCharacter::SetSel
 */
void CCharacter::SetSel(T_UWORD uwColor_p)
{
	uwColor_m=uwColor_p;
	uwSelSize_m=0;
} /* CCharacter::SetSel */


/*
 *	CCharacter::DrawSel
 */
void CCharacter::DrawSel()
{
	T_3DVALUE tXMin=cpModelInst_m->cpModel_m->tXMin_m;
	T_3DVALUE tXMax=cpModelInst_m->cpModel_m->tXMax_m;
	T_3DVALUE tYMin=cpModelInst_m->cpModel_m->tYMin_m;
	T_3DVALUE tYMax=cpModelInst_m->cpModel_m->tYMax_m;

	CVector<T_3DVALUE> cCorner[4];
	cCorner[0].Set(tXMin,0,tYMax);
	cCorner[1].Set(tXMax,0,tYMax);
	cCorner[2].Set(tXMin,0,tYMin);
	cCorner[3].Set(tXMax,0,tYMin);

	CVector<T_3DVALUE> cCorner2[4];
	T_MATHANVALUE* tpAngle=&cCharPos_m.tAngle_m;
	T_3DVALUE tCos=cos(*tpAngle);
	T_3DVALUE tSin=sin(*tpAngle);
	CVector<T_3DVALUE>* cpPosition=&cCharPos_m.cPosition_m;

	cCorner2[0].Set(
		cpPosition->tX+cCorner[0].tX*tCos-cCorner[0].tZ*tSin,
		0,
		cpPosition->tZ+cCorner[0].tZ*tCos+cCorner[0].tX*tSin);
	cCorner2[1].Set(
		cpPosition->tX+cCorner[1].tX*tCos-cCorner[1].tZ*tSin,
		0,
		cpPosition->tZ+cCorner[1].tZ*tCos+cCorner[1].tX*tSin);
	cCorner2[2].Set(
		cpPosition->tX+cCorner[2].tX*tCos-cCorner[2].tZ*tSin,
		0,
		cpPosition->tZ+cCorner[2].tZ*tCos+cCorner[2].tX*tSin);
	cCorner2[3].Set(
		cpPosition->tX+cCorner[3].tX*tCos-cCorner[3].tZ*tSin,
		0,
		cpPosition->tZ+cCorner[3].tZ*tCos+cCorner[3].tX*tSin);

	cCorner_m[0].Set(
		Min(Min(cCorner2[0].tX,cCorner2[1].tX),Min(cCorner2[2].tX,cCorner2[3].tX)),
		cpPosition->tY,
		Max(Max(cCorner2[0].tZ,cCorner2[1].tZ),Max(cCorner2[2].tZ,cCorner2[3].tZ)));
	cCorner_m[1].Set(
		Max(Max(cCorner2[0].tX,cCorner2[1].tX),Max(cCorner2[2].tX,cCorner2[3].tX)),
		cpPosition->tY,
		Max(Max(cCorner2[0].tZ,cCorner2[1].tZ),Max(cCorner2[2].tZ,cCorner2[3].tZ)));
	cCorner_m[2].Set(
		Min(Min(cCorner2[0].tX,cCorner2[1].tX),Min(cCorner2[2].tX,cCorner2[3].tX)),
		cpPosition->tY,
		Min(Min(cCorner2[0].tZ,cCorner2[1].tZ),Min(cCorner2[2].tZ,cCorner2[3].tZ)));
	cCorner_m[3].Set(
		Max(Max(cCorner2[0].tX,cCorner2[1].tX),Max(cCorner2[2].tX,cCorner2[3].tX)),
		cpPosition->tY,
		Min(Min(cCorner2[0].tZ,cCorner2[1].tZ),Min(cCorner2[2].tZ,cCorner2[3].tZ)));


	if(uwSelSize_m==D_CHARACTER_SELSIZE)
		return;
	CPt<T_2DVALUE> cPjC[4];
	CSystem::cpCtx_m->ProjVectors(cCorner_m,cPjC,4);

	CRectangle<T_2DVALUE> cRect;
	if(cPjC[0].tX>=CScreen::cRenderPos_m.tX && 
		cPjC[0].tY>=0 && 
		cPjC[0].tX<CScreen::cRenderPos_m.tX+CScreen::cRenderSize_m.tX-D_CHARACTER_SELSIZE && 
		cPjC[0].tY<CScreen::cRenderSize_m.tY-D_CHARACTER_SELSIZE)
	{
		cRect.Set(cPjC[0].tX,cPjC[0].tY,cPjC[0].tX+D_CHARACTER_SELSIZE-uwSelSize_m,cPjC[0].tY);
		CSystem::cpPrim_m->Fill(&cRect,uwColor_m);
		cRect.Set(cPjC[0].tX,cPjC[0].tY,cPjC[0].tX,cPjC[0].tY+D_CHARACTER_SELSIZE-uwSelSize_m);
		CSystem::cpPrim_m->Fill(&cRect,uwColor_m);
	}
	if(cPjC[1].tX>=CScreen::cRenderPos_m.tX+D_CHARACTER_SELSIZE && 
		cPjC[1].tY>=0 && 
		cPjC[1].tX<CScreen::cRenderPos_m.tX+CScreen::cRenderSize_m.tX && 
		cPjC[1].tY<CScreen::cRenderSize_m.tY-D_CHARACTER_SELSIZE)
	{
		cRect.Set(cPjC[1].tX-D_CHARACTER_SELSIZE+uwSelSize_m,cPjC[1].tY,cPjC[1].tX,cPjC[1].tY);
		CSystem::cpPrim_m->Fill(&cRect,uwColor_m);
		cRect.Set(cPjC[1].tX,cPjC[1].tY,cPjC[1].tX,cPjC[1].tY+D_CHARACTER_SELSIZE-uwSelSize_m);
		CSystem::cpPrim_m->Fill(&cRect,uwColor_m);
	}
	if(cPjC[2].tX>=CScreen::cRenderPos_m.tX && 
		cPjC[2].tY>=D_CHARACTER_SELSIZE && 
		cPjC[2].tX<CScreen::cRenderPos_m.tX+CScreen::cRenderSize_m.tX-D_CHARACTER_SELSIZE && 
		cPjC[2].tY<CScreen::cRenderSize_m.tY)
	{
		cRect.Set(cPjC[2].tX,cPjC[2].tY,cPjC[2].tX+D_CHARACTER_SELSIZE-uwSelSize_m,cPjC[2].tY);
		CSystem::cpPrim_m->Fill(&cRect,uwColor_m);
		cRect.Set(cPjC[2].tX,cPjC[2].tY-D_CHARACTER_SELSIZE+uwSelSize_m,cPjC[2].tX,cPjC[2].tY);
		CSystem::cpPrim_m->Fill(&cRect,uwColor_m);
	}
	if(cPjC[3].tX>=CScreen::cRenderPos_m.tX+D_CHARACTER_SELSIZE && 
		cPjC[3].tY>=D_CHARACTER_SELSIZE && 
		cPjC[3].tX<CScreen::cRenderPos_m.tX+CScreen::cRenderSize_m.tX && 
		cPjC[3].tY<CScreen::cRenderSize_m.tY)
	{
		cRect.Set(cPjC[3].tX-D_CHARACTER_SELSIZE+uwSelSize_m,cPjC[3].tY,cPjC[3].tX,cPjC[3].tY);
		CSystem::cpPrim_m->Fill(&cRect,uwColor_m);
		cRect.Set(cPjC[3].tX,cPjC[3].tY-D_CHARACTER_SELSIZE+uwSelSize_m,cPjC[3].tX,cPjC[3].tY);
		CSystem::cpPrim_m->Fill(&cRect,uwColor_m);
	}
	uwSelSize_m++;
} /* CCharacter::DrawSel */





