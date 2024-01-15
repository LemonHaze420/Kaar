#include "IAAnimal.h"
#include "Univers.h"
#include "WorldPos.h"
#include "NPChar.h"
#include "Player.h"
#include "Sound.h"



CIAAnimal::CIAAnimal(CCharacter* cpCharacter_p):
	cpCharacter_m(cpCharacter_p),
	uwPath_m(0),
	uwStep_m(0),
	tDate_m(0)
{
}

CIA::EIAState CIAAnimal::UpdateGarde()
{
	if((cpAttackCharacter_m=GetAttackCharacter(96))!=0)
	{
		if(cpCharacter_m->cpAttack_m!=0)
			cpCharacter_m->cpAttack_m->Play(CSound::cpCtrl_m);
		cpCharacter_m->tSpeed_m*=3;

		return E_IA_ATTACK;
	}
	if(cpCharacter_m->wLife_m<=cpCharacter_m->cpModelInst_m->cpModel_m->wLife_m/3)
	{
		cpCharacter_m->cCharPos_m.cToGo_m.Set(
			cpCharacter_m->cHome_m.tX,
			0.0f,
			cpCharacter_m->cHome_m.tY);
		CWorldPos cWorldPos(CNPChar::uwWorld_m,cpCharacter_m->cCharPos_m.cToGo_m.tX,cpCharacter_m->cCharPos_m.cToGo_m.tZ);
		cpCharacter_m->cCharPos_m.cToGo_m.tY=cWorldPos.GetAltitude()+cpCharacter_m->cCharPos_m.tAltitude_m;
		return E_IA_GOHOME;
	}

	if(cpCharacter_m->Update())
	{
		if(CUnivers::uwNbPath_m==0 || cpCharacter_m->uwNbCharPath_m==0)
			return E_IA_GARDE;

		if(tDate_m>CSystem::tTime_m)
			return E_IA_GARDE;

		T_UWORD uwPath=cpCharacter_m->cpCharPath_m[uwPath_m].uwPath_m;
		CPath* cpPath=&CUnivers::cpPath_m[uwPath];
		CPathPos* cpPathPos=&cpPath->cpPathPos_m[uwStep_m];

		if(*cpPathPos==cPathPos_m)
			tDate_m=CSystem::tTime_m+2000;
		else
		{
			cPathPos_m=*cpPathPos;
			cpCharacter_m->cCharPos_m.cToGo_m.Set(
				cpCharacter_m->cHome_m.tX+T_3DVALUE(cPathPos_m.wDX_m*16),
				0.0f,
				cpCharacter_m->cHome_m.tY+T_3DVALUE(cPathPos_m.wDY_m*16));

			CWorldPos cWorldPos(CNPChar::uwWorld_m,cpCharacter_m->cCharPos_m.cToGo_m.tX,cpCharacter_m->cCharPos_m.cToGo_m.tZ);
			cpCharacter_m->cCharPos_m.cToGo_m.tY=cWorldPos.GetAltitude()+cpCharacter_m->cCharPos_m.tAltitude_m;
		}

		uwStep_m++;
		if(uwStep_m>=cpPath->uwNbPathPos_m)
		{
			uwStep_m=0;
			uwPath_m++;
			if(uwPath_m>=cpCharacter_m->uwNbCharPath_m)
				uwPath_m=0;
		}
	}
	return E_IA_GARDE;
}


CIA::EIAState CIAAnimal::UpdateGoHome()
{
	if((cpAttackCharacter_m=GetAttackCharacter(48))!=0)
	{
		cpCharacter_m->tSpeed_m*=3;
		if(cpCharacter_m->cpAttack_m!=0)
			cpCharacter_m->cpAttack_m->Play(CSound::cpCtrl_m);

		return E_IA_ATTACK;
	}

	if(!cpCharacter_m->Update())
	{
		tDate_m=CSystem::tTime_m+1000;
		return E_IA_GOHOME;
	}
	if(tDate_m>CSystem::tTime_m)
		return E_IA_GOHOME;
	else
	{
		cpCharacter_m->cCharPos_m.cToGo_m.Set(
			cpCharacter_m->cHome_m.tX+(rand()%64)-32,
			0.0f,
			cpCharacter_m->cHome_m.tY+(rand()%64)-32);

		CWorldPos cWorldPos(CNPChar::uwWorld_m,cpCharacter_m->cCharPos_m.cToGo_m.tX,cpCharacter_m->cCharPos_m.cToGo_m.tZ);
		cpCharacter_m->cCharPos_m.cToGo_m.tY=cWorldPos.GetAltitude()+cpCharacter_m->cCharPos_m.tAltitude_m;
	}
	return E_IA_GOHOME;
}

CIA::EIAState CIAAnimal::UpdateDead()
{
	cpCharacter_m->Update();
	return E_IA_DEAD;
}

CIA::EIAState CIAAnimal::UpdateSearch()
{
	return E_IA_GARDE;
}


CIA::EIAState CIAAnimal::UpdateAttack()
{
	if(cpAttackCharacter_m->wLife_m<=0)
	{
		cpCharacter_m->tSpeed_m/=3;
		return E_IA_GARDE;
	}
	cpCharacter_m->cCharPos_m.cToGo_m=cpAttackCharacter_m->cCharPos_m.cPosition_m;
	CWorldPos cWorldPos(CNPChar::uwWorld_m,cpCharacter_m->cCharPos_m.cToGo_m.tX,cpCharacter_m->cCharPos_m.cToGo_m.tZ);
	cpCharacter_m->cCharPos_m.cToGo_m.tY=cWorldPos.GetAltitude()+cpCharacter_m->cCharPos_m.tAltitude_m;

	if(cpCharacter_m->Update())
	{
		cpAttackCharacter_m->wLife_m-=2;
		if(cpAttackCharacter_m->wLife_m<=0)
		{
			if(cpAttackCharacter_m->cpDead_m!=0)
				cpAttackCharacter_m->cpDead_m->Play(CSound::cpCtrl_m);

			cpAttackCharacter_m->wLife_m=0;
		}
		else if(cpAttackCharacter_m->cpImpact_m!=0)
		{
			if(tDate_m<CSystem::tTime_m)
			{
				tDate_m=CSystem::tTime_m+2000;
				cpAttackCharacter_m->cpImpact_m->Play(CSound::cpCtrl_m);
			}
		}

		cpCharacter_m->tSpeed_m/=3;
		return E_IA_GOHOME;
	}
	return E_IA_ATTACK;
}



CCharacter* CIAAnimal::GetAttackCharacter(T_3DVALUE tDist_p)
{
	for(CCharacter* cp=CPlayer::cpCurWorld_m->cListCharacter_m.FindFirst();cp!=0;cp=CPlayer::cpCurWorld_m->cListCharacter_m.FindNext())
	{
		if(cp->wLife_m<=0)
			continue;
		if(cp->uwModel_m==cpCharacter_m->uwModel_m)
			continue;
		CVector<T_3DVALUE> cVec=cp->cCharPos_m.cPosition_m-cpCharacter_m->cCharPos_m.cPosition_m;
		T_3DVALUE tLen=cVec.tX*cVec.tX+cVec.tY*cVec.tY+cVec.tZ*cVec.tZ;
		if(tLen>tDist_p*tDist_p || cVec.tY>16.0f)
			continue;
		return cp;
	}
	return 0;
}
