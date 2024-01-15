#ifndef _INCLUDE_KAAR_
#define _INCLUDE_KAAR_
/**************************************************************************************
 * 
 **************************************************************************************/
#include "System.h"
#include "DrvMgr.h"
#include "Screen.h"
#include "Game.h"
#include "Sound.h"
#include "SFX.h"


/*
 *	CKaar
 */
class CKaar:public CApp
{
public:
	static CScreen* cpScreen_m;
	static CGame* cpGame_m;

	CKaar();
	~CKaar();

	virtual T_RESULT Run(ERetType *epError_p);
private:
	CDrvMgr* cpDrvMgr_m;
	CWindow* cpWin_m;
	CSound* cpSound_m;
	CSFX* cpSFX_m;
};


#endif // _INCLUDE_KAAR_


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif




