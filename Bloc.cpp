#include "Bloc.h"
#include "Group.h"
// debug shadow
#include "Univers.h"


/*
 *	CBloc::CBloc
 */
CBloc::CBloc():
	cpGroup_m(0),
	uwIndex_m(0),
	chpMeshName_m(0),
	cpMeshObj_m(0)
{
} /* CBloc::CBloc */


/*
 *	CBloc::CBloc
 */
CBloc::CBloc(const char* chpMeshName_p,T_UWORD uwIndex_p):
	cpGroup_m(0),
	uwIndex_m(uwIndex_p),
	cpMeshObj_m(0)
{
	chpMeshName_m=NEW char[strlen(chpMeshName_p)+1];
	strcpy(chpMeshName_m,chpMeshName_p);
} /* CBloc::CBloc */


/*
 *	CBloc::~CBloc
 */
CBloc::~CBloc()
{
	if(chpMeshName_m!=0)
		DELETE []chpMeshName_m;
	if(cpMeshObj_m!=0)
		DELETE cpMeshObj_m;
} /* CBloc::~CBloc */


/*
 *	CBloc::operator=
 */
CBloc& CBloc::operator=(CBloc& crBloc_p)
{
	chpMeshName_m=NEW char[strlen(crBloc_p.chpMeshName_m)+1];
	strcpy(chpMeshName_m,crBloc_p.chpMeshName_m);
	cpGroup_m=crBloc_p.cpGroup_m;
	uwIndex_m=crBloc_p.uwIndex_m;
//	memcpy(cpGrid_m,crBloc_p.cpGrid_m,sizeof(CCell)*CBloc::E_BLOC_GRIDSIZE2);
	cpMeshObj_m=0;
	return *this;
} /* CBloc::operator= */


/*
 *	CBloc::Init
 */
void CBloc::Init() 
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
	
	CVector<T_FLOAT> cVec;
	cVec.Set(1,1,1);
	cpRepTrans->SetScale(&cVec);

	cVec.Zero();
	cpRepTrans->SetTrans(&cVec);
	cVec.Set(D_PI/2,D_PI/2,3*D_PI/2);
	cpRepTrans->SetRot(&cVec);

	cpMeshObj_m->Evaluate();
} /* CBloc::Init */


/*
 *	CBloc::Shut
 */
void CBloc::Shut() 
{
	if(cpMeshObj_m!=0)
	{
		DELETE cpMeshObj_m;
		cpMeshObj_m=0;
	}
} /* CBloc::Shut */







