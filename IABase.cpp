#include "IABase.h"
#include "Univers.h"
#include "WorldPos.h"
#include "NPChar.h"
#include "Player.h"
#include "Sound.h"



CIABase::CIABase(CCharacter* cpCharacter_p):
	cpCharacter_m(cpCharacter_p),
	uwPath_m(0),
	uwStep_m(0),
	tDate_m(0)
{
}

CIA::EIAState CIABase::UpdateGarde()
{
	if(cpCharacter_m->wLife_m<=cpCharacter_m->cpModelInst_m->cpModel_m->wLife_m/2)
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


CIA::EIAState CIABase::UpdateGoHome()
{
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
			cpCharacter_m->cHome_m.tX+(rand()%128)-64,
			0.0f,
			cpCharacter_m->cHome_m.tY+(rand()%128)-64);

		CWorldPos cWorldPos(CNPChar::uwWorld_m,cpCharacter_m->cCharPos_m.cToGo_m.tX,cpCharacter_m->cCharPos_m.cToGo_m.tZ);
		cpCharacter_m->cCharPos_m.cToGo_m.tY=cWorldPos.GetAltitude()+cpCharacter_m->cCharPos_m.tAltitude_m;
	}
	return E_IA_GOHOME;
}

CIA::EIAState CIABase::UpdateDead()
{
	cpCharacter_m->Update();
	return E_IA_DEAD;
}

CIA::EIAState CIABase::UpdateSearch()
{
	return E_IA_GARDE;
}


CIA::EIAState CIABase::UpdateAttack()
{
	return E_IA_GARDE;
}



