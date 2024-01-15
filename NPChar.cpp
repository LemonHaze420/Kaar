#include "NPChar.h"
#include "Univers.h"
#include "WorldPos.h"
#include "Sound.h"
#include "SFX.h"
#include "IAAnimal.h"
#include "IAGarde.h"
#include "IABase.h"
#include "IAVolant.h"


	
CList<CNPChar> CNPChar::cListNPChar_m;
T_UWORD CNPChar::uwWorld_m;
CWorld* CNPChar::cpWorld_m;


/*
 *	CNPChar::CNPChar
 */
CNPChar::CNPChar(CCharacter* cpCharacter_p,CIA::EIAState eState_p):
	cpCharacter_m(cpCharacter_p),
	eState_m(eState_p),
	bFall_m(false),
	bFalled_m(false)
{
	CreateIA();
	cpCharacter_m->AddRef();
} /* CNPChar::CNPChar */


/*
 *	CNPChar::~CNPChar
 */
CNPChar::~CNPChar()
{
	DELETE cpIA_m;
	cpCharacter_m->Release();
} /* CNPChar::~CNPChar */


/*
 *	CNPChar::CreateIA
 */
void CNPChar::CreateIA()
{
	if(strcmp(CUnivers::cpModel_m[cpCharacter_m->uwModel_m].chpIA_m,"NONE")==0)
		cpIA_m=NEW CIABase(cpCharacter_m);
	else if(strcmp(CUnivers::cpModel_m[cpCharacter_m->uwModel_m].chpIA_m,"VOLANT")==0)
		cpIA_m=NEW CIAVolant(cpCharacter_m);
	else if(strcmp(CUnivers::cpModel_m[cpCharacter_m->uwModel_m].chpIA_m,"GARDE")==0)
		cpIA_m=NEW CIAGarde(cpCharacter_m);
	else if(strcmp(CUnivers::cpModel_m[cpCharacter_m->uwModel_m].chpIA_m,"ANIMAL")==0)
		cpIA_m=NEW CIAAnimal(cpCharacter_m);
} /* CNPChar::CreateIA */


/*
 *	CNPChar::operator=
 */
CNPChar& CNPChar::operator=(CNPChar& crNPChar_p)
{
	cpCharacter_m=crNPChar_p.cpCharacter_m;
	cpCharacter_m->AddRef();
	CreateIA();
	eState_m=crNPChar_p.eState_m;
	bFall_m=crNPChar_p.bFall_m;
	bFalled_m=crNPChar_p.bFalled_m;
	return *this;
} /* CNPChar::operator= */


/*
 *	CNPChar::New
 */
void CNPChar::New(CCharacter* cpCharacter_p,CIA::EIAState eState_p)
{
	cListNPChar_m.Insert(CNPChar(cpCharacter_p,eState_p));
	cpCharacter_p->eType_m=CCharacter::E_CHARACTER_NPC;
} /* CNPChar::New */


/*
 *	CNPChar::Get
 */
void CNPChar::Get(T_UWORD uwWorld_p)
{
	uwWorld_m=uwWorld_p;
	cpWorld_m=&CUnivers::cpWorld_m[uwWorld_m];


	for(CCharacter* cp=cpWorld_m->cListCharacter_m.FindFirst();cp!=0;cp=cpWorld_m->cListCharacter_m.FindNext())
	{
		if(cp->bDead_m)
			continue;
		if(cp->eType_m==CCharacter::E_CHARACTER_NPC)
			New(cp,CIA::E_IA_GARDE);
	}
} /* CNPChar::Get */


/*
 *	CNPChar::Release
 */
void CNPChar::Release()
{
	cListNPChar_m.Delete();
} /* CNPChar::Release */


/*
 *	CNPChar::Play
 */
void CNPChar::Play()
{
	CNPChar* cp;
	for(cp=cListNPChar_m.FindFirst();cp!=0;cp=cListNPChar_m.FindNext())
	{
		if(cp->cpCharacter_m->bDead_m)
		{
			cListNPChar_m.Delete(cp);
			break;
		}
	}
	for(cp=cListNPChar_m.FindFirst();cp!=0;cp=cListNPChar_m.FindNext())
		cp->Update();
} /* CNPChar::Play */


/*
 *	CNPChar::Draw
 */
void CNPChar::Draw()
{
	for(CNPChar* cp=cListNPChar_m.FindFirst();cp!=0;cp=cListNPChar_m.FindNext())
		cp->cpCharacter_m->Draw();
} /* CNPChar::Draw */


/*
 *	CNPChar::DrawSel
 */
void CNPChar::DrawSel()
{
	for(CNPChar* cp=cListNPChar_m.FindFirst();cp!=0;cp=cListNPChar_m.FindNext())
		cp->cpCharacter_m->DrawSel();
} /* CNPChar::DrawSel */


/*
 *	CNPChar::Update
 */
void CNPChar::Update()
{
	if(cpCharacter_m->wLife_m<=0)
	{
		eState_m=CIA::E_IA_DEAD;
		if(!bFall_m)
		{
			bFall_m=true;
			CVector<T_3DVALUE>* cpToGo=&cpCharacter_m->cCharPos_m.cToGo_m;
			T_3DVALUE tRadius=cpCharacter_m->cpModelInst_m->cpModel_m->tRadius_m;
			cpToGo->Set(
				cpCharacter_m->cCharPos_m.cPosition_m.tX+(rand()%T_UWORD(tRadius))-tRadius*0.5f,
				0.0f,
				cpCharacter_m->cCharPos_m.cPosition_m.tZ+(rand()%T_UWORD(tRadius))-tRadius*0.5f);
/*				cpCharacter_m->cCharPos_m.cPosition_m.tX,
				0.0f,
				cpCharacter_m->cCharPos_m.cPosition_m.tZ);
*/			CWorldPos cWorldPos(uwWorld_m,cpToGo->tX,cpToGo->tZ);
			cpToGo->tY=cWorldPos.GetAltitude()+4;
		}
		if(!bFalled_m)
		{

			CWorldPos cWorldPos(uwWorld_m,cpCharacter_m->cCharPos_m.cPosition_m.tX,cpCharacter_m->cCharPos_m.cPosition_m.tZ);
			T_3DVALUE tY=cWorldPos.GetAltitude();
			if(cpCharacter_m->cCharPos_m.cPosition_m.tY<=tY)
			{
				CSFX::SetBlood(&cpCharacter_m->cCharPos_m.cPosition_m);
				bFalled_m=true;
				CSound::cpChuteImpact_m->Play(CSound::cpCtrl_m);
				CSound::cpJuicy_m->Play(CSound::cpCtrl_m);
			}
		}
	}

	switch(eState_m)
	{
	case CIA::E_IA_GARDE:
		eState_m=cpIA_m->UpdateGarde();
		break;
	case CIA::E_IA_GOHOME:
		eState_m=cpIA_m->UpdateGoHome();
		break;
	case CIA::E_IA_ATTACK:
		eState_m=cpIA_m->UpdateAttack();
		break;
	case CIA::E_IA_DEAD:
		eState_m=cpIA_m->UpdateDead();
		break;
	case CIA::E_IA_SEARCH:
		eState_m=cpIA_m->UpdateSearch();
		break;
	}
} /*  CNPChar::Update */



