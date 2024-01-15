#include "Player.h"
#include "NPChar.h"
#include "Sound.h"
#include "Interface.h"


CUnivers* CPlayer::cpUnivers_m;
CWorldView* CPlayer::cpWorldView_m;

CPChar* CPlayer::cppPChar_m[E_PLAYER_MAXPCHAR];
T_UWORD CPlayer::uwNbPChar_m;
T_UWORD CPlayer::uwCurPChar_m;
CPChar* CPlayer::cpCurPChar_m;
T_UWORD CPlayer::uwCurWorld_m;
CWorld* CPlayer::cpCurWorld_m;
CCharacter* CPlayer::cpCurCharacter_m;


/*
 *	CPlayer::CPlayer
 */
CPlayer::CPlayer(char* chpName_p)
{
	uwNbPChar_m=0;
	uwCurPChar_m=-1;
	cpCurPChar_m=0;
	uwCurWorld_m=0;
	cpCurCharacter_m=0;
	cpUnivers_m=NEW CUnivers(chpName_p);
	cpWorldView_m=NEW CWorldView(this);
	cpCurWorld_m=&cpUnivers_m->cpWorld_m[uwCurWorld_m];

	CNPChar::Get(uwCurWorld_m);
} /* CPlayer::CPlayer */


/*
 *	CPlayer::~CPlayer
 */
CPlayer::~CPlayer()
{
	CNPChar::Release();

	DELETE cpWorldView_m;
	DELETE cpUnivers_m;
} /* CPlayer::~CPlayer */


/*
 *	CPlayer::Get
 */
void CPlayer::Get(T_UWORD uwWorld_p)
{
	CNPChar::Release();
	CNPChar::Get(uwWorld_p);

	for(T_UWORD uw=0;uw<E_PLAYER_MAXPCHAR;uw++)
		cppPChar_m[uw]=0;

	CWorld* cpWorld=&CUnivers::cpWorld_m[uwWorld_p];
	for(CCharacter* cp=cpWorld->cListCharacter_m.FindFirst();cp!=0;cp=cpWorld->cListCharacter_m.FindNext())
	{
		if(cp->bDead_m)
			continue;
		if(cp->eType_m==CCharacter::E_CHARACTER_PC)
		{
			if(uwNbPChar_m==E_PLAYER_MAXPCHAR)
				return;
			cppPChar_m[uwNbPChar_m++]=NEW CPChar(cp);
		}
	}
	SetActive(uwNbPChar_m-1);
	DrawSel();
} /* CPlayer::Get */


/*
 *	CPlayer::Release
 */
void CPlayer::Release()
{
	for(T_UWORD uw=0;uw<uwNbPChar_m;uw++)
	{
		if(cppPChar_m[uw]!=0)
			DELETE cppPChar_m[uw];
	}
} /* CPlayer::Release */


/*
 *	CPlayer::SetActive
 */
void CPlayer::SetActive(T_UWORD uwPChar_p)
{
	if(uwPChar_p>=uwNbPChar_m)
		return;
	if(uwCurPChar_m!=uwPChar_p)
	{
		CSound::cpPannelSelection_m->Play(CSound::cpCtrl_m);
		if(cppPChar_m[uwPChar_p]->cpCharacter_m->cpAttack_m!=0)
			cppPChar_m[uwPChar_p]->cpCharacter_m->cpAttack_m->Play(CSound::cpCtrl_m);
		cppPChar_m[uwPChar_p]->cpCharacter_m->SetSel(CInterface::uwGreen_m);
	}

	uwCurPChar_m=uwPChar_p;
	cpCurPChar_m=cppPChar_m[uwCurPChar_m];
	cpCurCharacter_m=cpCurPChar_m->cpCharacter_m;
	uwCurWorld_m=cpCurCharacter_m->cCharPos_m.uwWorld_m;
	cpCurWorld_m=&CUnivers::cpWorld_m[uwCurWorld_m];
} /* CPlayer::SetActive */


/*
 *	CPlayer::Update
 */
void CPlayer::Update()
{
	CNPChar::Play();
	
	T_UWORD uw;
	for(uw=0;uw<uwNbPChar_m;uw++)
	{
		if(cppPChar_m[uw]->cpCharacter_m->wLife_m<=0)
		{
			CPChar* cpPChar=cppPChar_m[uw];
			uwNbPChar_m--;
			for(T_UWORD uwDel=uw;uwDel<uwNbPChar_m;uwDel++)
				cppPChar_m[uwDel]=cppPChar_m[uwDel+1];
			cppPChar_m[uwDel]=0;
			CNPChar::New(cpPChar->cpCharacter_m,CIA::E_IA_DEAD);
			DELETE cpPChar;

			if(uwNbPChar_m!=0)
			{
				if(uwCurPChar_m<uw)
					SetActive(uwCurPChar_m);
				else if(uwCurPChar_m>uw)
					SetActive(uwCurPChar_m-1);
				else
				{
					// Suppression de l'actif
					if(uwNbPChar_m>uw)
						SetActive(uw);	// prend le suivant si possible
					else
						SetActive(uw-1); // sinon le précédent
				}
			}
			else
				CSound::cpPannelDead_m->Play(CSound::cpCtrl_m);
			uw--;
		}
	}

	for(uw=0;uw<uwNbPChar_m;uw++)
		cppPChar_m[uw]->Update();


	if(uwNbPChar_m!=0)
		cpWorldView_m->Update(&cppPChar_m[uwCurPChar_m]->cpCharacter_m->cCharPos_m.cPosition_m);
	else
		cpWorldView_m->Update();
} /* CPlayer::Update */


/*
 *	CPlayer::Draw
 */
void CPlayer::Draw(T_BOOL bDebug_p)
{
	cpWorldView_m->Draw(bDebug_p);

	for(T_UWORD uw=0;uw<uwNbPChar_m;uw++)
		cppPChar_m[uw]->Draw();

	CNPChar::Draw();
} /* CPlayer::Draw */


/*
 *	CPlayer::DrawSel
 */
void CPlayer::DrawSel()
{
	for(T_UWORD uw=0;uw<uwNbPChar_m;uw++)
		cppPChar_m[uw]->DrawSel();

	CNPChar::DrawSel();
} /* CPlayer::DrawSel */



