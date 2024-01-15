#include "IAVolant.h"
#include "Univers.h"
#include "WorldPos.h"
#include "NPChar.h"
#include "Player.h"
#include "Sound.h"



CIAVolant::CIAVolant(CCharacter* cpCharacter_p):
	cpCharacter_m(cpCharacter_p),
	uwPath_m(0),
	uwStep_m(0),
	tDate_m(0)
{
}

CIA::EIAState CIAVolant::UpdateGarde()
{
	if(cpCharacter_m->wLife_m<=cpCharacter_m->cpModelInst_m->cpModel_m->wLife_m/2 || 
		cpCharacter_m->uwTireness_m<=10)
	{
		cpCharacter_m->cCharPos_m.cToGo_m.Set(
			cpCharacter_m->cHome_m.tX,
			0.0f,
			cpCharacter_m->cHome_m.tY);
		CWorldPos cWorldPos(CNPChar::uwWorld_m,cpCharacter_m->cCharPos_m.cToGo_m.tX,cpCharacter_m->cCharPos_m.cToGo_m.tZ);
		cpCharacter_m->cCharPos_m.cToGo_m.tY=cWorldPos.GetAltitude()+cpCharacter_m->cCharPos_m.tAltitude_m;
		return E_IA_GOHOME;
	}
	if((cpAttackCharacter_m=GetAttackCharacter(1024))!=0)
		return E_IA_SEARCH;

	if(cpCharacter_m->Update())
	{
		T_ULONG ulXSize=CPlayer::cpCurWorld_m->uwXSize_m*1024;
		T_ULONG ulYSize=CPlayer::cpCurWorld_m->uwYSize_m*1024;
		static T_3DVALUE tAngle;
		static T_3DVALUE tDiameter=0.01f;
		tDiameter+=0.01f;
		CVector<T_3DVALUE> cVec;
		cVec.tX=(ulXSize+ulXSize*cos(tAngle)*tDiameter)/2;
		cVec.tZ=(ulYSize+ulYSize*sin(tAngle)*cos(tAngle/3)*tDiameter)/-2;
		tAngle+=0.02f;
		if(tDiameter>=1.0f)
			tDiameter=0.01f;

		cpCharacter_m->cCharPos_m.cToGo_m=cVec;
		CWorldPos cWorldPos(CNPChar::uwWorld_m,cpCharacter_m->cCharPos_m.cToGo_m.tX,cpCharacter_m->cCharPos_m.cToGo_m.tZ);
		cpCharacter_m->cCharPos_m.cToGo_m.tY=cWorldPos.GetAltitude()+cpCharacter_m->cCharPos_m.tAltitude_m;
	}
	return E_IA_GARDE;
}


CIA::EIAState CIAVolant::UpdateGoHome()
{
	if(!cpCharacter_m->Update())
	{
		tDate_m=CSystem::tTime_m+30000;
		return E_IA_GOHOME;
	}
	if(tDate_m>CSystem::tTime_m)
		return E_IA_GOHOME;
	else
		return E_IA_GARDE;
}

CIA::EIAState CIAVolant::UpdateDead()
{
	cpCharacter_m->Update();
	return E_IA_DEAD;
}

CIA::EIAState CIAVolant::UpdateSearch()
{
	cpCharacter_m->cCharPos_m.cToGo_m=cpAttackCharacter_m->cCharPos_m.cPosition_m;
	CWorldPos cWorldPos(CNPChar::uwWorld_m,cpCharacter_m->cCharPos_m.cToGo_m.tX,cpCharacter_m->cCharPos_m.cToGo_m.tZ);
	cpCharacter_m->cCharPos_m.cToGo_m.tY=cWorldPos.GetAltitude()+cpCharacter_m->cCharPos_m.tAltitude_m;

	if(cpCharacter_m->wLife_m<=cpCharacter_m->cpModelInst_m->cpModel_m->wLife_m/2 || 
		cpCharacter_m->uwTireness_m<=10)
	{
		cpCharacter_m->cCharPos_m.cToGo_m.Set(
			cpCharacter_m->cHome_m.tX,
			0.0f,
			cpCharacter_m->cHome_m.tY);
		CWorldPos cWorldPos(CNPChar::uwWorld_m,cpCharacter_m->cCharPos_m.cToGo_m.tX,cpCharacter_m->cCharPos_m.cToGo_m.tZ);
		cpCharacter_m->cCharPos_m.cToGo_m.tY=cWorldPos.GetAltitude()+cpCharacter_m->cCharPos_m.tAltitude_m;
		return E_IA_GOHOME;
	}
	cpCharacter_m->Update();
	if((cpAttackCharacter_m=GetAttackCharacter(128))!=0)
		return E_IA_ATTACK;
	return E_IA_SEARCH;
}


CIA::EIAState CIAVolant::UpdateAttack()
{
	if(cpCharacter_m->wLife_m<=cpCharacter_m->cpModelInst_m->cpModel_m->wLife_m/2 || 
		cpCharacter_m->uwTireness_m<=10)
	{
		cpCharacter_m->cCharPos_m.cToGo_m.Set(
			cpCharacter_m->cHome_m.tX,
			0.0f,
			cpCharacter_m->cHome_m.tY);
		CWorldPos cWorldPos(CNPChar::uwWorld_m,cpCharacter_m->cCharPos_m.cToGo_m.tX,cpCharacter_m->cCharPos_m.cToGo_m.tZ);
		cpCharacter_m->cCharPos_m.cToGo_m.tY=cWorldPos.GetAltitude()+cpCharacter_m->cCharPos_m.tAltitude_m;
		return E_IA_GOHOME;
	}
	if(!cpCharacter_m->bMissile_m)
	{
		// Déclenchement de l'attack
		cpCharacter_m->fTireness_m-=10.0f;
		if(cpCharacter_m->fTireness_m<=0.0f)
			cpCharacter_m->fTireness_m=0.0f;
		else
		{
			CSound::cpFireLaunch_m->Play(CSound::cpCtrl_m);

			cpCharacter_m->cMissilePos_m.cToGo_m=cpAttackCharacter_m->cCharPos_m.cPosition_m;
			cpCharacter_m->cMissilePos_m.cPosition_m=cpCharacter_m->cCharPos_m.cPosition_m;
			cpCharacter_m->bMissile_m=true;
			cpCharacter_m->bMissileEnd_m=false;
			cpCharacter_m->cpModelInst_m->cpPartObjSmoke_m->SetState(CParticleObj::E_PARTICLEOBJSTATE_ON,CSystem::tTime_m);
			cpCharacter_m->cMissilePos_m.cToGo_m.tY+=8;
			cpCharacter_m->cMissilePos_m.cPosition_m.tY+=cpCharacter_m->cpModelInst_m->cpModel_m->tRadius_m/2.0f;
			cpCharacter_m->cMissilePos_m.tAltitude_m=0;
		}

		// Orientation
		CVector<T_3DVALUE> cVec=cpAttackCharacter_m->cCharPos_m.cPosition_m-cpCharacter_m->cCharPos_m.cPosition_m;
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

	cpCharacter_m->Update();
	return E_IA_GARDE;
}


CCharacter* CIAVolant::GetAttackCharacter(T_3DVALUE tDist_p)
{
	for(CCharacter* cp=CPlayer::cpCurWorld_m->cListCharacter_m.FindFirst();cp!=0;cp=CPlayer::cpCurWorld_m->cListCharacter_m.FindNext())
	{
		if(cp->wLife_m<=0)
			continue;
		if(cp==cpCharacter_m)
			continue;
		if(CUnivers::cpModel_m[cp->uwModel_m].eRace_m==
			CUnivers::cpModel_m[cpCharacter_m->uwModel_m].eRace_m)
			continue;
		if(cp->eType_m==CCharacter::E_CHARACTER_NPC)
			continue;
		CVector<T_3DVALUE> cVec=cp->cCharPos_m.cPosition_m-cpCharacter_m->cCharPos_m.cPosition_m;
		T_3DVALUE tLen=cVec.tX*cVec.tX+cVec.tY*cVec.tY+cVec.tZ*cVec.tZ;
		if(tLen>tDist_p*tDist_p || cVec.tY>16.0f)
			continue;
		return cp;
	}
	return 0;
}


