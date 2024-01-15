#include "Land.h"
#include "Group.h"


/*
 *	CLand::CLand
 */
CLand::CLand():
	cpGroup_m(0),
	uwIndex_m(0),
	chpMeshName_m(0),
	cpMeshObj_m(0),
	ePartType_m(E_LANDINST_NONE),
	cpParticule_m(0)
{
} /* CLand::CLand */


/* 
 *	CLand::CLand
 */
CLand::CLand(const char* chpMeshName_p,T_UWORD uwIndex_p,ELandPartType ePartType_p):
	cpGroup_m(0),
	uwIndex_m(uwIndex_p),
	cpMeshObj_m(0),
	ePartType_m(ePartType_p),
	cpParticule_m(0)
{
	chpMeshName_m=NEW char[strlen(chpMeshName_p)+1];
	strcpy(chpMeshName_m,chpMeshName_p);
} /* CLand::CLand */


/* 
 *	CLand::~CLand
 */
CLand::~CLand()
{
	if(cpParticule_m!=0)
		DELETE cpParticule_m;
	if(chpMeshName_m!=0)
		DELETE []chpMeshName_m;
	if(cpMeshObj_m!=0)
		DELETE cpMeshObj_m;
} /* CLand::~CLand */


/*
 *	CLand::operator=
 */
CLand& CLand::operator=(CLand& crLand_p)
{
	chpMeshName_m=NEW char[strlen(crLand_p.chpMeshName_m)+1];
	strcpy(chpMeshName_m,crLand_p.chpMeshName_m);
	cpGroup_m=crLand_p.cpGroup_m;
	uwIndex_m=crLand_p.uwIndex_m;
	ePartType_m=crLand_p.ePartType_m;
	return *this;
} /* CLand::operator= */


/*
 *	CLand::Init
 */
void CLand::Init()
{
	// Chargement mesh
	CSystem::cpMesh_m->LoadMeshObj(
		CSystem::cpFileCtx_m,
		CSystem::cpCtx_m,
		CSystem::cp3d_m,
		CSystem::cpMath_m,
		cpGroup_m->cpTexture_m,
		uwIndex_m,
		CSystem::cpScene_m,
		CSystem::cpEvMesh_m,
		CSystem::cpEvMb_m,
		CSystem::cpAnMgr_m,
		chpMeshName_m,
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

	cpMeshObj_m->Evaluate();

	// chargement particule
	if(ePartType_m==CLand::E_LANDINST_FUMES || ePartType_m==CLand::E_LANDINST_SMALLFUMES)
	{
		CSystem::cpFrame_m->CreateBmFrameObj(CSystem::cpFileCtx_m,CSystem::cp2d_m,"FUMES",CBmap::F_CREATIONFLAGS_TEXTURABLE,&cpParticule_m);
		cpParticule_m->CreateTextures(CSystem::cp3d_m,0);
		cpParticule_m->CreateMaterials(CSystem::cp3d_m);
		CMaterial *cpMat;

		T_CARD tNbMat;
		cpParticule_m->GetNbBmaps(&tNbMat);
		for(T_CARD t=0;t<tNbMat;t++)
		{
			cpParticule_m->GetMaterialPtr(t,&cpMat);
			cpMat->SetBlending(CMaterial::E_BLMODE_ADDSRCANDDEST);
			cpMat->SetFlags(CMaterial::F_MATFLAGS_OPACITY);
		}
	}
} /* CLand::Init */


/*
 *	CLand::Shut
 */
void CLand::Shut()
{
	if(cpParticule_m!=0)
	{
		DELETE cpParticule_m;
		cpParticule_m=0;
	}
	if(cpMeshObj_m!=0)
	{
		DELETE cpMeshObj_m;
		cpMeshObj_m=0;
	}
} /* CLand::Shut */

