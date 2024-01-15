#include "System.h"


// High level
CFileCtx* CSystem::cpFileCtx_m;
CMessager* CSystem::cpMessager_m;

// Mid Level
CInput* CSystem::cpInput_m;
CMath* CSystem::cpMath_m;
CGfx* CSystem::cpGfx_m;
C2d* CSystem::cp2d_m;
C3d* CSystem::cp3d_m;
CScene* CSystem::cpScene_m;
CMesh* CSystem::cpMesh_m;
CMeshEvalMgr* CSystem::cpEvMesh_m;
CMogBoxEvalMgr* CSystem::cpEvMb_m;
CAnimationMgr* CSystem::cpAnMgr_m;
CBmFrame* CSystem::cpFrame_m;
CBmFnt* CSystem::cpBmFnt_m;
CParticleMgr* CSystem::cpPartMgr_m;
CTimer* CSystem::cpTimer_m;
CSnd* CSystem::cpSnd_m;


// Low level
CKbd* CSystem::cpKbd_m;
CMouse* CSystem::cpMouse_m;
CBmap* CSystem::cpPrim_m;
CViewport* CSystem::cpVp_m;
CRenderCtx* CSystem::cpCtx_m;
CBmFntObj* CSystem::cpFontObj_m;
CTimerObj* CSystem::cpTimerObj_m;
T_DATE CSystem::tTime_m;
C2dSnd* CSystem::cp2dSnd_m;
