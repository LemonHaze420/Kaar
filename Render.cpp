#include "Render.h"


/*
 *	CRender::CRender
 */
CRender::CRender(CPt<T_2DVALUE>* cpSize_p):
	cSize_m(*cpSize_p)
{
	CSystem::cp2d_m->Create3dObj(&CSystem::cp3d_m);

	CSystem::cp3d_m->SelectBestDevice(CSystem::cpPrim_m,
			C3d::F_DEVFLAGS_ZBUF16BITS|
			C3d::F_DEVFLAGS_TEXT8BITSPAL|
			C3d::F_DEVFLAGS_PERSPCORRECT|
			C3d::F_DEVFLAGS_TRANSFORM);

	// Créer un viewport
	CSystem::cp3d_m->CreateViewport(
		CViewport::F_VPFLAGS_CLEAR|CViewport::F_VPFLAGS_CLEARZBUF,
		&CSystem::cpVp_m);

	CColor cTmpColor;
	cTmpColor.Set((T_UBYTE)0x50,(T_UBYTE)0x60,(T_UBYTE)0x80);
	CSystem::cpVp_m->SetBackColor(&cTmpColor);

	// Créer un contexte de rendu
	CSystem::cp3d_m->CreateRenderCtx(CSystem::cpMath_m,&CSystem::cpCtx_m);
	CSystem::cpCtx_m->SetViewportRef(CSystem::cpVp_m);

	CColor cAmbient;
	cAmbient.White();
	CSystem::cpCtx_m->SetSceneAmbientLight(&cAmbient);
	CSystem::cpCtx_m->SetGroupLightMode(CRenderCtx::F_LIGHTMODE_USESCENEAMBIENT);
//	CSystem::cpCtx_m->SetGroupLightMode(CRenderCtx::F_LIGHTMODE_VERTEXLIGHT|
//		CRenderCtx::F_LIGHTMODE_USESCENEAMBIENT);
/*
		CRenderCtx::F_LIGHTMODE_GROUPLIGHT+
		CRenderCtx::F_LIGHTMODE_GROUPLIGHTVEC+
		CRenderCtx::F_LIGHTMODE_VERTEXLIGHT+
		CRenderCtx::F_LIGHTMODE_VERTEXLIGHTVEC+
		CRenderCtx::F_LIGHTMODE_USESCENEAMBIENT/*+
		CRenderCtx::F_LIGHTMODE_USEGROUPAMBIENT+
		CRenderCtx::F_LIGHTMODE_USEMATERIALAMBIENT+
		CRenderCtx::F_LIGHTMODE_USEVERTEXAMBIENT

	cpCtx_m->SetFogFlags(CRenderCtx::F_FOGFLAGS_SCENE);
	cpCtx_m->SetSceneFogColor(&cTmpColor);

	cpCtx_m->SetSceneFogMode(CRenderCtx::E_SCFOGMODE_LINEAR);
	cpCtx_m->SetGroupFogMode(CRenderCtx::E_GRFOGMODE_GROUP);
*/
} /* CRender::CRender */


/*
 *	CRender::~CRender
 */
CRender::~CRender()
{
	DELETE CSystem::cpCtx_m;
	DELETE CSystem::cpVp_m;

	CSystem::cp3d_m->UnselectDevice();
	DELETE CSystem::cp3d_m;
} /* CRender::~CRender */


/*
 *	CRender::SetPos
 */
void CRender::SetPos(CPt<T_2DVALUE>* cpPos_p)
{
	// Mise à jour zone de rendu 
	CRectangle<T_2DVALUE> cRect;
	cRect.Set(
		cpPos_p->tX,
		cpPos_p->tY,
		cpPos_p->tX+cSize_m.tX-1,
		cpPos_p->tY+cSize_m.tY-1);
	CSystem::cpVp_m->SetRenderZone(&cRect);
} /* CRender::SetPos */