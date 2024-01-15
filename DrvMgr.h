#ifndef _INCLUDE_DRVMGR_
#define _INCLUDE_DRVMGR_
/**************************************************************************************
 * 
 **************************************************************************************/
#include "System.h"


/*
 *	CDrvMgr
 */
class CDrvMgr:public CBase
{
public:
	CDrvInst* cpMathDrvInst_m;
	CDrvInst* cpInputDrvInst_m;
	CDrvInst* cpGfxDrvInst_m;
	CDrvInst* cpSceneDrvInst_m;
	CDrvInst* cpMeshDrvInst_m;
	CDrvInst* cpEvMeshInst_m;
	CDrvInst* cpEvMbInst_m;
	CDrvInst* cpAnMgrInst_m;
	CDrvInst* cpFrameDrvInst_m;
	CDrvInst* cpBmFntDrvInst_m;
	CDrvInst* cpPartDrvInst_m;
	CDrvInst* cpTimerDrvInst_m;
	CDrvInst* cpSndDrvInst_m;

	CDrvMgr();
	~CDrvMgr();
}; /* CDrvMgr */


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif


