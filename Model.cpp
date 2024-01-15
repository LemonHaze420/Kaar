#include "Model.h"


/*
 *	CModel::CModel
 */
CModel::CModel():
	eRace_m(EModelRace(0)),
	chpIcon_m(0),
	chpMesh_m(0),
	chpTexture_m(0),
	chpMovie_m(0),
	chpIA_m(0),
	wAltitude_m(0),
	wLife_m(0),
	uwTireness_m(0),
	cpTexture_m(0),
	cpMeshObj_m(0)
{
} /* CModel::CModel */


/*
 *	CModel::CModel
 */
CModel::CModel(EModelRace eRace_p,
		char* chpIcon_p,
		char* chpMesh_p,
		char* chpTexture_p,
		char* chpMovie_p,
		char* chpIA_p,
		T_WORD wAltitude_p,
		T_WORD wLife_p,
		T_UWORD uwTireness_p):
	eRace_m(eRace_p),
	chpIcon_m(NEW char[strlen(chpIcon_p)+1]),
	chpMesh_m(NEW char[strlen(chpMesh_p)+1]),
	chpTexture_m(NEW char[strlen(chpTexture_p)+1]),
	chpMovie_m(NEW char[strlen(chpMovie_p)+1]),
	chpIA_m(NEW char[strlen(chpIA_p)+1]),
	wAltitude_m(wAltitude_p),
	wLife_m(wLife_p),
	uwTireness_m(uwTireness_p),
	cpTexture_m(0),
	cpMeshObj_m(0)
{
	strcpy(chpIcon_m,chpIcon_p);
	strcpy(chpMesh_m,chpMesh_p);
	strcpy(chpTexture_m,chpTexture_p);
	strcpy(chpMovie_m,chpMovie_p);
	strcpy(chpIA_m,chpIA_p);
} /* CModel::CModel */


/*
 *	CModel::~CModel
 */
CModel::~CModel()
{
	if(chpIcon_m!=0)
		DELETE []chpIcon_m;
	if(chpMesh_m!=0)
		DELETE []chpMesh_m;
	if(chpTexture_m!=0)
		DELETE []chpTexture_m;
	if(chpMovie_m!=0)
		DELETE []chpMovie_m;
	if(chpIA_m!=0)
		DELETE []chpIA_m;

	if(cpTexture_m!=0)
	{
		cpTexture_m->ReleaseTextures();
		cpTexture_m->ReleaseMaterials();
		DELETE cpTexture_m;
	}
	if(cpMeshObj_m!=0)
		DELETE cpMeshObj_m;
} /* CModel::~CModel */


/*
 *	CModel::operator=
 */
CModel& CModel::operator=(CModel& crModel_p)
{
	eRace_m=crModel_p.eRace_m;

	chpIcon_m=NEW char[strlen(crModel_p.chpIcon_m)+1];
	chpMesh_m=NEW char[strlen(crModel_p.chpMesh_m)+1];
	chpTexture_m=NEW char[strlen(crModel_p.chpTexture_m)+1];
	chpMovie_m=NEW char[strlen(crModel_p.chpMovie_m)+1];
	chpIA_m=NEW char[strlen(crModel_p.chpIA_m)+1];
	strcpy(chpIcon_m,crModel_p.chpIcon_m);
	strcpy(chpMesh_m,crModel_p.chpMesh_m);
	strcpy(chpTexture_m,crModel_p.chpTexture_m);
	strcpy(chpMovie_m,crModel_p.chpMovie_m);
	strcpy(chpIA_m,crModel_p.chpIA_m);

	wLife_m=crModel_p.wLife_m;
	uwTireness_m=crModel_p.uwTireness_m;
	wAltitude_m=crModel_p.wAltitude_m;
	return *this;
} /* CModel::operator= */


/*
 *	CModel::Init
 */
void CModel::Init()
{
	// Charger icon
	CSystem::cpFrame_m->CreateBmFrameObj(CSystem::cpFileCtx_m,CSystem::cp2d_m,chpIcon_m,0,&cpIcon_m);
	// Charger photo
	CSystem::cpFrame_m->CreateBmFrameObj(CSystem::cpFileCtx_m,CSystem::cp2d_m,chpMovie_m,0,&cpMovie_m);

	// Chargement texture
	CSystem::cpFrame_m->CreateBmFrameObj(CSystem::cpFileCtx_m,CSystem::cp2d_m,chpTexture_m,CBmap::F_CREATIONFLAGS_TEXTURABLE,&cpTexture_m);
	cpTexture_m->CreateMaterials(CSystem::cp3d_m);
	cpTexture_m->CreateTextures(CSystem::cp3d_m,0);
	T_CARD tNbMat;
	cpTexture_m->GetNbBmaps(&tNbMat);
	for(T_CARD t=0;t<tNbMat;t++)
	{
		CMaterial* cpMat;
		cpTexture_m->GetMaterialPtr(t,&cpMat);

		T_INDEX tGroupNum;
		cpTexture_m->GetBmapGroupNum(t,&tGroupNum);
		if(tGroupNum==1)
			cpMat->SetBlending(CMaterial::E_BLMODE_INVSRCANDDEST);

		cpMat->SetFlags(CMaterial::F_MATFLAGS_OPACITY);
	}

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
		chpMesh_m,
		&cpMeshObj_m);
	
	// Init default & Radius 
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
	cVec.Set(D_PI/2,D_PI/2,3*D_PI/2);
	cpRepTrans->SetRot(&cVec);

	GetRadius();

} /* CModel::Init */


/*
 *	CModel::Shut
 */
void CModel::Shut()
{
	if(cpTexture_m!=0)
	{
		cpTexture_m->ReleaseTextures();
		cpTexture_m->ReleaseMaterials();
		DELETE cpTexture_m;
		cpTexture_m=0;
	}
	if(cpMeshObj_m!=0)
	{
		DELETE cpMeshObj_m;
		cpMeshObj_m=0;
	}
	if(cpIcon_m!=0)
	{
		DELETE cpIcon_m;
		cpIcon_m=0;
	}
	if(cpMovie_m!=0)
	{
		DELETE cpMovie_m;
		cpMovie_m=0;
	}
} /* CModel::Shut */


/*
 *	CModel::GetRadius
 */
void CModel::GetRadius()
{
	// Accès aux données des meshes
	cpMeshObj_m->Evaluate();
	// Récupérer le premier éval mgr
	T_HANDLE tEvHa;
	CMeshObj::EEvMgrType eEvMgrType;
	CMeshEvalMgrObj *cpMeshEv;
	cpMeshObj_m->GetFirstEvalMgr((CDynamicSceneNodeEvalMgr **)&cpMeshEv,&eEvMgrType,&tEvHa);


	tRadius_m=0;
	tXMax_m=0;
	tYMax_m=0;
	tXMin_m=0;
	tYMin_m=0;
	while(cpMeshEv!=NULL)
	{
		// Mesh evaluator ?
		if(eEvMgrType!=CMeshObj::E_EVMGRTYPE_MESH)
			continue;

		// Ok, ici mesh evaluator détecté.
		// Récupérer le nombre de face groups associé à notre évaluateur
		T_CARD tNbFg;
		cpMeshEv->GetNbFaceGroup(&tNbFg);

		// Parcourir chaque facegroup
		for(T_INDEX tFg=0;tFg<tNbFg;tFg++)
		{
			// Pour ce face group, récupérer les vecteurs évalué correspondant aux 
			// positions,normales,textures etc.
			CVector<T_3DVALUE>* cpVecPos;
			T_CARD tNbVecPos;
			cpMeshEv->GetEvaluatedVectors(tFg,CMeshEvalMgrObj::E_NODEPTRIND_POSITION,
				&cpVecPos,&tNbVecPos);
			for(T_INDEX t=0;t<tNbVecPos;t++)
			{
				CVector<T_3DVALUE>* cpVec=&cpVecPos[t];
				T_3DVALUE tLen=T_3DVALUE(sqrt(double(cpVec->tX*cpVec->tX+/*cpVec->tY*cpVec->tY+*/cpVec->tZ*cpVec->tZ)));
				if(tLen>tRadius_m)
					tRadius_m=tLen;

				if(cpVec->tX>tXMax_m)
					tXMax_m=cpVec->tX;
				if(cpVec->tZ>tYMax_m)
					tYMax_m=cpVec->tZ;
				if(cpVec->tX<tXMin_m)
					tXMin_m=cpVec->tX;
				if(cpVec->tZ<tYMin_m)
					tYMin_m=cpVec->tZ;
			}
		}			
		cpMeshObj_m->GetNextEvalMgr((CDynamicSceneNodeEvalMgr **)&cpMeshEv,&eEvMgrType,&tEvHa);
	}
} /* CModel::GetRadius */
