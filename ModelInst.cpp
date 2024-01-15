#include "ModelInst.h"
#include "Univers.h"
#include "Player.h"
#include "SFX.h"


/*
 *	CModelInst::CModelInst
 */
CModelInst::CModelInst(T_UWORD uwModel_p):
	cpModel_m(&CUnivers::cpModel_m[uwModel_p])
{
	// Mesh
	cpModel_m->AddRef();
	cpModel_m->cpMeshObj_m->CreateInstance(0,&cpMeshInst_m);

	cpMeshInst_m->GetAnimMgrObjRef(&cpAnMgrObj_m);
	cpAnMgrObj_m->SetCurrentAnimation(0,0);
	cpAnMgrObj_m->SetCurrentEvaluationGlobalTime(0);

	C3dTransformation *cpRepTrans;
	cpMeshInst_m->GetRepTransRef(&cpRepTrans);
	CVector<T_3DVALUE> cVec;
	cVec.Set(1.0f,1.0f,1.0f);
	cpRepTrans->SetScale(&cVec);

	// Particule
	CVector<T_3DVALUE> cPartSize;
	CVector<T_3DVALUE> cPartMove;
	cPartSize.Set(1.0,1.0,1.0);
	cPartMove.Set(0.0,5.0,0.0);

	cpParticleObjCallbackSmoke_m=NEW CParticleObjCallbackSmoke(
		CSystem::cpMath_m,
		0,				// Numéro de l'anim dans l'objet
		1,				// Nombre d'anim pour tirage aléatoire -> anim de la particule 0 ou 1
		&cPartSize,		// Taille de la zone de génération
		&cPartMove,		// Vitesse et direction en T_3DVALUE/SEC des particules
		20,			// Durée entre chaque génération de particule
		1.0f,			// Prob de génération de particule
		10);			// Nombre max de particule
	cpPartObjSmoke_m=CSystem::cpPartMgr_m->CreateParticleObj(CSFX::cpParticule_m,1,16,10); // (bmapframe,objet,taille particule, nombre max)
	cpPartObjSmoke_m->SetCallbackObj(cpParticleObjCallbackSmoke_m);
	cpPartObjSmoke_m->SetState(CParticleObj::E_PARTICLEOBJSTATE_OFF,CSystem::tTime_m);

	cPartSize.Set(32.0,1.0,32.0);
	cPartMove.Set(0.0,50.0,0.0);
	cpParticleObjCallbackImpact_m=NEW CParticleObjCallbackSmoke(
		CSystem::cpMath_m,
		0,				// Numéro de l'anim dans l'objet
		1,				// Nombre d'anim pour tirage aléatoire -> anim de la particule 0 ou 1
		&cPartSize,		// Taille de la zone de génération
		&cPartMove,		// Vitesse et direction en T_3DVALUE/SEC des particules
		40,			// Durée entre chaque génération de particule
		1.0f,			// Prob de génération de particule
		10);			// Nombre max de particule

	cpPartObjImpact_m=CSystem::cpPartMgr_m->CreateParticleObj(CSFX::cpParticule_m,0,64,10); // (bmapframe,objet,taille particule, nombre max)
	cpPartObjImpact_m->SetCallbackObj(cpParticleObjCallbackImpact_m);
	cpPartObjImpact_m->SetState(CParticleObj::E_PARTICLEOBJSTATE_OFF,CSystem::tTime_m);

	// SHADOW
	cShad_m.SetMemberPtrs(
		&CVector<T_3DVALUE>::tX,
		&CVector<T_3DVALUE>::tZ,
		&CVector<T_3DVALUE>::tY);
} /* CModelInst::CModelInst */


/*
 *	CModelInst::~CModelInst
 */
CModelInst::~CModelInst()
{
	DELETE cpParticleObjCallbackSmoke_m;
	DELETE cpParticleObjCallbackImpact_m;
	DELETE cpPartObjSmoke_m;
	DELETE cpPartObjImpact_m;
	DELETE cpMeshInst_m;
	cpModel_m->Release();
} /* CModelInst::~CModelInst */


/* 
 *	CModelInst::GetMeshShadow
 */
CMeshObj* CModelInst::GetMeshShadow(T_3DVALUE tX_p,T_3DVALUE tY_p)
{
	CZoneInst* cpZoneInst=CPlayer::cpCurWorld_m->GetZoneInst(tX_p,tY_p);
	if(cpZoneInst==0)
		return 0;
	CBlocInst* cpBlocInst=cpZoneInst->GetBlocInst(tX_p,tY_p);
	if(cpBlocInst==0)
		return 0;
	return cpBlocInst->cpMeshInst_m;
} /* CModelInst::GetMeshShadow */


/*
 *	CModelInst::ComputeShadow
 */
void CModelInst::ComputeShadow(CVector<T_3DVALUE>* cpPosition_p,T_MATHANVALUE tAngle_p,T_UWORD uwShadow_p,T_BOOL bDead_p)
{
	CMeshObj* cppMeshShad[4];
	cppMeshShad[0]=GetMeshShadow(cpPosition_p->tX-128,cpPosition_p->tZ-128);
	cppMeshShad[1]=GetMeshShadow(cpPosition_p->tX+128,cpPosition_p->tZ-128);
	cppMeshShad[2]=GetMeshShadow(cpPosition_p->tX+128,cpPosition_p->tZ+128);
	cppMeshShad[3]=GetMeshShadow(cpPosition_p->tX-128,cpPosition_p->tZ+128);

	if(cppMeshShad[0]==cppMeshShad[1] || cppMeshShad[0]==cppMeshShad[2] || cppMeshShad[0]==cppMeshShad[3])
		cppMeshShad[0]=0;
	if(cppMeshShad[1]==cppMeshShad[2] || cppMeshShad[1]==cppMeshShad[3])
		cppMeshShad[1]=0;
	if(cppMeshShad[2]==cppMeshShad[3])
		cppMeshShad[2]=0;

	CVector<T_3DVALUE> cShPos;
	cShPos.Set(0.0,2.0,0.0);
	CPt<T_3DVALUE> cShadPos;
	cShadPos.Set(cpPosition_p->tX,cpPosition_p->tZ);
	T_UWORD uwAnim;
	if(bDead_p)
		uwAnim=1;
	else
		uwAnim=0;

	if(cppMeshShad[0]!=0)
		cShad_m.ComputeShadow(CSystem::cpMath_m,CSFX::cpShadow_m,uwShadow_p,uwAnim,0,&cShadPos,220.0f,cppMeshShad[0],&cShPos,tAngle_p);
	if(cppMeshShad[1]!=0)
		cShad_m.ComputeShadow(CSystem::cpMath_m,CSFX::cpShadow_m,uwShadow_p,uwAnim,0,&cShadPos,220.0f,cppMeshShad[1],&cShPos,tAngle_p);
	if(cppMeshShad[2]!=0)
		cShad_m.ComputeShadow(CSystem::cpMath_m,CSFX::cpShadow_m,uwShadow_p,uwAnim,0,&cShadPos,220.0f,cppMeshShad[2],&cShPos,tAngle_p);
	if(cppMeshShad[3]!=0)
		cShad_m.ComputeShadow(CSystem::cpMath_m,CSFX::cpShadow_m,uwShadow_p,uwAnim,0,&cShadPos,220.0f,cppMeshShad[3],&cShPos,tAngle_p);


	// Objet décor Land
	CZoneInst* cpZoneInst=CPlayer::cpCurWorld_m->GetZoneInst(cpPosition_p->tX,cpPosition_p->tZ);
	if(cpZoneInst==0)
		return;

	for(T_UWORD uwLand=0;uwLand<cpZoneInst->uwNbLandInst_m;uwLand++)
	{
		CLandInst* cpLandInst=&cpZoneInst->cpLandInst_m[uwLand];
		CVector<T_3DVALUE> cVec;
		cVec.Set(
			T_FLOAT(cpZoneInst->uwX_m*CZone::E_ZONE_SIZE*256+cpLandInst->cLandPos_m.biX_m*64),
			0.0f,
			T_FLOAT(-cpZoneInst->uwY_m*CZone::E_ZONE_SIZE*256-cpLandInst->cLandPos_m.biY_m*64));

		cVec-=*cpPosition_p;
		T_3DVALUE tLen=cVec.tX*cVec.tX+cVec.tZ*cVec.tZ;
		if(tLen<256*256 && cpLandInst->cpMeshInst_m!=0)
			cShad_m.ComputeShadow(CSystem::cpMath_m,CSFX::cpShadow_m,uwShadow_p,0,0,&cShadPos,220.0f,cpLandInst->cpMeshInst_m,&cShPos,tAngle_p);
	}
} /* CModelInst::ComputeShadow */


/* 
 *	CModelInst::Draw
 */
void CModelInst::Draw(CVector<T_3DVALUE>* cpPosition_p,T_MATHANVALUE tAngle_p,T_UWORD uwShadow_p,T_BOOL bDead_p)
{
	if(CSFX::bShadow_m)
	{
		cShad_m.Prepare();

	//	T_INDEX tFr;
	//	cpModel_m->cpShadow_m->GetFrameNum(0,0,0,CSystem::tTime_m,&tFr);
		
		ComputeShadow(cpPosition_p,tAngle_p,uwShadow_p,bDead_p);
		cShad_m.AddPrims(CSystem::cpCtx_m);
	}
	cpAnMgrObj_m->SetCurrentEvaluationGlobalTime(CSystem::tTime_m);

	C3dTransformation *cpRepTrans;
	cpMeshInst_m->GetRepTransRef(&cpRepTrans);

	CVector<T_MATHANVALUE> cVec;
	cVec.Set(D_PI/2+tAngle_p,D_PI/2,3*D_PI/2);
	cpRepTrans->SetRot(&cVec);

	cpRepTrans->SetTrans(cpPosition_p);

	cpMeshInst_m->InvalidateRepCache();
	cpMeshInst_m->Evaluate();
} /* CModelInst::Draw */


/* 
 *	CModelInst::DrawMissile
 */
void CModelInst::DrawMissile(CVector<T_3DVALUE>* cpPosition_p)
{
	cpPartObjSmoke_m->SetPos(cpPosition_p);
	cpPartObjSmoke_m->PlayAndAddPrims(CSystem::cpCtx_m,CSystem::tTime_m);
} /* CModelInst::DrawMissile */


/* 
 *	CModelInst::DrawImpact
 */
void CModelInst::DrawImpact(CVector<T_3DVALUE>* cpPosition_p)
{
	cpPartObjImpact_m->SetPos(cpPosition_p);
	cpPartObjImpact_m->PlayAndAddPrims(CSystem::cpCtx_m,CSystem::tTime_m);
} /* CModelInst::DrawImpact */
