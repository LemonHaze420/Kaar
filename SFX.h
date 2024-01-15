#ifndef _INCLUDE_SFX_
#define _INCLUDE_SFX_
/**************************************************************************************
 * 
 **************************************************************************************/
#include "System.h"
#include "DivHea\crpasmok.h"


class CSFX
{
public:
	static CBmFrameObj* cpShadow_m;
	static CBmFrameObj *cpParticule_m;
	static CBmFrameObj *cpBlood_m;
	static T_BOOL bShadow_m;
	static T_BOOL bBlood_m;

	CSFX();
	~CSFX();

	static void SetBlood(CVector<T_3DVALUE>* cpPosition_p);
	static void UpdateBlood();
private:
	static CParticleObj* cpPartObjBlood_m;
	static CParticleObjCallbackSmoke* cpParticleObjCallbackBlood_m;
	static T_DATE tBloodDate_m;
};


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif

