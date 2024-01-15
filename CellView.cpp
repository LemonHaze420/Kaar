#include "CellView.h"


T_ULONG CCellView::ulRef_m=0;
CMeshObj* CCellView::cpMeshObj_m=0;
CBmFrameObj* CCellView::cpTexture_m=0;


/*
 *	CCellView::CCellView
 */
CCellView::CCellView()
{
	if(ulRef_m==0)
	{
		// Chargement texture
		CSystem::cpFrame_m->CreateBmFrameObj(CSystem::cpFileCtx_m,CSystem::cp2d_m,"prtcl",CBmap::F_CREATIONFLAGS_TEXTURABLE,&cpTexture_m);
		cpTexture_m->CreateMaterials(CSystem::cp3d_m);
		cpTexture_m->CreateTextures(CSystem::cp3d_m,0);

		// Chargement mesh
		CSystem::cpMesh_m->LoadMeshObj(
			CSystem::cpFileCtx_m,
			CSystem::cpCtx_m,
			CSystem::cp3d_m,
			CSystem::cpMath_m,
			cpTexture_m,
			0,
			CSystem::cpScene_m,
			CSystem::cpEvMesh_m,
			CSystem::cpEvMb_m,
			CSystem::cpAnMgr_m,
			"Case",
			&cpMeshObj_m);

		// Init default
		CAnimationMgrObj *cpAnMgrObj;
		cpMeshObj_m->GetAnimMgrObjRef(&cpAnMgrObj);
		cpAnMgrObj->SetCurrentAnimation(0,0);

		C3dTransformation *cpRepTrans;
		cpMeshObj_m->GetRepTransRef(&cpRepTrans);
		
		CVector<T_3DVALUE> cVec;
		cVec.Set(1,1,1);
		cpRepTrans->SetScale(&cVec);

		cVec.Zero();
		cpRepTrans->SetTrans(&cVec);
		cpRepTrans->SetRot(&cVec);
	}

	cpMeshObj_m->CreateInstance(0,&cpMeshInst_m);
	ulRef_m++;
} /* CCellView::CCellView */


/*
 *	CCellView::~CCellView
 */
CCellView::~CCellView()
{
	ulRef_m--;

	DELETE cpMeshInst_m;

	if(ulRef_m==0)
	{
		DELETE cpMeshObj_m;
		cpTexture_m->ReleaseTextures();
		cpTexture_m->ReleaseMaterials();
		DELETE cpTexture_m;
	}
} /* CCellView::~CCellView */


/*
 *	CCellView::Draw
 */
void CCellView::Draw(T_3DVALUE tX_p,T_3DVALUE tZ_p,T_3DVALUE tY_p)
{
	C3dTransformation *cpRepTrans;
	cpMeshInst_m->GetRepTransRef(&cpRepTrans);

	CVector<T_FLOAT> cVec;
	cVec.Set(D_PI/2,D_PI/2,3*D_PI/2);
	cpRepTrans->SetRot(&cVec);
	
	cVec.Set(tX_p,tZ_p+2,tY_p);
	cpRepTrans->SetTrans(&cVec);

	cpMeshInst_m->InvalidateRepCache();
	cpMeshInst_m->Evaluate();
} /* CCellView::Draw */


