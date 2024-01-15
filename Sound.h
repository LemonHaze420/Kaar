#ifndef _INCLUDE_SOUND_
#define _INCLUDE_SOUND_
/**************************************************************************************
 * 
 **************************************************************************************/
#include "System.h"


/*
 *	CSound
 */
class CSound
{
public:
	static CSndBuf* cpPannelRoll_m;
	static CSndBuf* cpPannelLock_m;
	static CSndBuf* cpNewGame_m;
	static CSndBuf* cpPannelSelection_m;
	static CSndBuf* cpFireImpact_m;
	static CSndBuf* cpFireLaunch_m;
	static CSndBuf* cpChuteImpact_m;
	static CSndBuf* cpJuicy_m;
	static CSndBuf* cpVolBarive_m;
	static CSndBuf* cpVolSaur_m;
	static CSndBuf* cpVolFour_m;
	static CSndBuf* cpPannelDead_m;

	static CSndBuf* cpStracmiteAttack_m;
	static CSndBuf* cpStracmiteImpact_m;
	static CSndBuf* cpStracmiteMort_m;

	static CSndBuf* cpUergImpact_m;
	static CSndBuf* cpUergAttack_m;
	static CSndBuf* cpUergMort_m;
	static CSndBuf* cpUergOrdre_m[4];

	static CSndBuf* cpRaagasImpact_m;
	static CSndBuf* cpRaagasAttack_m;
	static CSndBuf* cpRaagasMort_m;
	static CSndBuf* cpRaagasOrdre_m[4];

	static CSndBuf* cpFourmantaImpact_m;
	static CSndBuf* cpFourmantaAttack_m;
	static CSndBuf* cpFourmantaMort_m;
	static CSndBuf* cpFourmantaOrdre_m[4];

	static CSndBuf* cpSaureilleImpact_m;
	static CSndBuf* cpSaureilleMort_m;
	static CSndCtrl* cpCtrl_m;


	CSound();
	~CSound();


}; /* CSound */


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif

