#ifndef _INCLUDE_SYSTEM_
#define _INCLUDE_SYSTEM_
/**************************************************************************************
 * 
 **************************************************************************************/
#include <CrsWin.h>
#include "IntHea\MathDrv.h"
#include "IntHea\GfxDrv.h"
#include "IntHea\FrameDrv.h"
#include "IntHea\InputDrv.h"
#include "IntHea\SndDrv.h"
#include "IntHea\TimerDrv.h"
#include "IntHea\ScriptDrv.h"
#include "IntHea\MeshDrv.h"
#include "IntHea\EvMeDrv.h"
#include "IntHea\EvMbDrv.h"
#include "IntHea\BmFntDrv.h"
#include "IntHea\PrtclDrv.h"
#include "IntHea\SndDrv.h"
#include "IntHea\SConvDrv.h"

#include "Messager.h"


/*
 *	CSystem
 */
class CSystem
{
public:
	// High level
	static CFileCtx* cpFileCtx_m;
	static CMessager* cpMessager_m;

	// Mid Level
	static CMath* cpMath_m;
	static CInput* cpInput_m;
	static CGfx* cpGfx_m;
	static C2d* cp2d_m;
	static C3d* cp3d_m;
	static CScene* cpScene_m;
	static CMesh* cpMesh_m;
	static CMeshEvalMgr* cpEvMesh_m;
	static CMogBoxEvalMgr* cpEvMb_m;
	static CAnimationMgr* cpAnMgr_m;
	static CBmFrame* cpFrame_m;
	static CBmFnt* cpBmFnt_m;
	static CParticleMgr* cpPartMgr_m;
	static CTimer* cpTimer_m;
	static CSnd* cpSnd_m;

	// Low level
	static CKbd* cpKbd_m;
	static CMouse* cpMouse_m;
	static CBmap* cpPrim_m;
	static CViewport* cpVp_m;
	static CRenderCtx* cpCtx_m;
	static CBmFntObj* cpFontObj_m;
	static CTimerObj* cpTimerObj_m;
	static T_DATE tTime_m;
	static C2dSnd* cp2dSnd_m;
};


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif




