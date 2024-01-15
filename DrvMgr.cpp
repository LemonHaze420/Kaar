#include "DrvMgr.h"
#include "System.h"



/*
 *	CDrvMgr::CDrvMgr
 */
CDrvMgr::CDrvMgr()
{
	#ifdef _DEBUG
//		CSystem::cpFileCtx_m->SetPath("Drivers");
		CSystem::cpFileCtx_m->SetPath("DebugDrivers");
	#else
		CSystem::cpFileCtx_m->SetPath("Drivers");
	#endif	

	cpInputDrvInst_m=NEW CDrvInst(CSystem::cpFileCtx_m,
				"InputDrv",
				CDrvDesc::E_CAT_INPUT,
				CVersion(1,0));
	
	cpGfxDrvInst_m=NEW CDrvInst(CSystem::cpFileCtx_m,
				"GfxDrv",
				CDrvDesc::E_CAT_GFX,
				CVersion(1,0));

	cpFrameDrvInst_m=NEW CDrvInst(CSystem::cpFileCtx_m,
				"FrameDrv",
				CDrvDesc::E_CAT_FRAME,
				CVersion(1,0));

	cpMathDrvInst_m=NEW CDrvInst(CSystem::cpFileCtx_m,
				"MathDrv",
				CDrvDesc::E_CAT_MATH,
				CVersion(1,0));

	cpSceneDrvInst_m=NEW CDrvInst(CSystem::cpFileCtx_m,
				"SceneDrv",
				CDrvDesc::E_CAT_SCENE,
				CVersion(1,0));

	cpMeshDrvInst_m=NEW CDrvInst(CSystem::cpFileCtx_m,
				"MeshDrv",
				CDrvDesc::E_CAT_MESH,
				CVersion(1,0));
	
	cpEvMeshInst_m=NEW CDrvInst(CSystem::cpFileCtx_m,
				"EvMeDrv",
				CDrvDesc::E_CAT_MESHEVALMGR,
				CVersion(1,0));

	cpEvMbInst_m=NEW CDrvInst(CSystem::cpFileCtx_m,
				"EvMbDrv",
				CDrvDesc::E_CAT_MOGBOXEVALMGR,
				CVersion(1,0));

	cpAnMgrInst_m=NEW CDrvInst(CSystem::cpFileCtx_m,
				"AnMgDrv",
				CDrvDesc::E_CAT_ANIMMGR,
				CVersion(1,0));

	cpBmFntDrvInst_m=NEW CDrvInst(CSystem::cpFileCtx_m,
				"BmFntDrv",
				CDrvDesc::E_CAT_BMFONT,
				CVersion(1,0));

	cpPartDrvInst_m=NEW CDrvInst(CSystem::cpFileCtx_m,
				"PrtclDrv",
				CDrvDesc::E_CAT_PARTICLE,
				CVersion(1,0));

	cpTimerDrvInst_m=NEW CDrvInst(CSystem::cpFileCtx_m,
					"TimerDrv",
					CDrvDesc::E_CAT_TIMER,
					CVersion(1,0));

	cpSndDrvInst_m=NEW CDrvInst(CSystem::cpFileCtx_m,
					"SndDrv",
					CDrvDesc::E_CAT_SND,
					CVersion(1,0));

	CSystem::cpFileCtx_m->SetPath("..");

	cpInputDrvInst_m->CreateInterface((T_VOID **)&CSystem::cpInput_m);
	CSystem::cpInput_m->CreateKbdObj(&CSystem::cpKbd_m);
	CSystem::cpInput_m->CreateMouseObj(&CSystem::cpMouse_m);
	cpGfxDrvInst_m->CreateInterface((T_VOID **)&CSystem::cpGfx_m);
	cpFrameDrvInst_m->CreateInterface((T_VOID **)&CSystem::cpFrame_m);
	cpMathDrvInst_m->CreateInterface((T_VOID **)&CSystem::cpMath_m);
	cpSceneDrvInst_m->CreateInterface((T_VOID **)&CSystem::cpScene_m);
	cpMeshDrvInst_m->CreateInterface((T_VOID **)&CSystem::cpMesh_m);
	cpEvMeshInst_m->CreateInterface((T_VOID **)&CSystem::cpEvMesh_m);
	cpEvMbInst_m->CreateInterface((T_VOID **)&CSystem::cpEvMb_m);
	cpAnMgrInst_m->CreateInterface((T_VOID **)&CSystem::cpAnMgr_m);
	cpBmFntDrvInst_m->CreateInterface((T_VOID **)&CSystem::cpBmFnt_m);
	cpPartDrvInst_m->CreateInterface((T_VOID **)&CSystem::cpPartMgr_m);
	cpTimerDrvInst_m->CreateInterface((T_VOID **)&CSystem::cpTimer_m);
	CSystem::cpTimer_m->CreateTimerObj(&CSystem::cpTimerObj_m);
	cpSndDrvInst_m->CreateInterface((T_VOID **)&CSystem::cpSnd_m);
	CSystem::cpSnd_m->Create2dObj(&CSystem::cp2dSnd_m);
} /* CDrvMgr */


/*
 *	~CDrvMgr
 */
CDrvMgr::~CDrvMgr()
{
	DELETE CSystem::cp2dSnd_m;
	DELETE CSystem::cpSnd_m;
	DELETE cpSndDrvInst_m;
	DELETE CSystem::cpBmFnt_m;
	DELETE cpBmFntDrvInst_m;
	DELETE CSystem::cpFrame_m;
	DELETE cpFrameDrvInst_m;
	DELETE CSystem::cpKbd_m;
	DELETE CSystem::cpMouse_m;
	DELETE CSystem::cpInput_m;
	DELETE cpInputDrvInst_m;
	DELETE CSystem::cpGfx_m;
	DELETE cpGfxDrvInst_m;
	DELETE CSystem::cpMath_m;
	DELETE cpMathDrvInst_m;
	DELETE CSystem::cpScene_m;
	DELETE cpSceneDrvInst_m;
	DELETE CSystem::cpMesh_m;
	DELETE cpMeshDrvInst_m;
	DELETE CSystem::cpEvMesh_m;
	DELETE cpEvMeshInst_m;
	DELETE CSystem::cpEvMb_m;
	DELETE cpEvMbInst_m;
	DELETE CSystem::cpAnMgr_m;
	DELETE cpAnMgrInst_m;
	DELETE CSystem::cpPartMgr_m;
	DELETE cpPartDrvInst_m;
	DELETE CSystem::cpTimerObj_m;
	DELETE CSystem::cpTimer_m;
	DELETE cpTimerDrvInst_m;
} /* ~CDrvMgr */
