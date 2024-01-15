#include "LandInst.h"
#include "Zone.h"
#include "Player.h"


#define D_LANDINST_DELTAALTITUDE 2


/*
 *	CLandInst::CLandInst
 */
CLandInst::CLandInst():
	cpLand_m(0),
	cpMeshInst_m(0),
	cpPartObj_m(0),
	cpParticleObjCallbackSmoke_m(0)
{
} /* CLandInst::CLandInst */


/*
 *	CLandInst::Set
 */
CLandInst::Set(CLand* cpLand_p,CLandPos* cpLandPos_p)
{
	cpLand_m=cpLand_p;
	cLandPos_m=*cpLandPos_p;
	cLandPos_m.biAltitude_m+=D_LANDINST_DELTAALTITUDE;
} /* CLandInst::Set */


/*
 *	CLandInst::~CLandInst
 */
CLandInst::~CLandInst()
{
	if(cpParticleObjCallbackSmoke_m!=0)
		DELETE cpParticleObjCallbackSmoke_m;
	if(cpPartObj_m!=0)
		DELETE cpPartObj_m;
	if(cpMeshInst_m!=0)
		DELETE cpMeshInst_m;
} /* CLandInst::~CLandInst */


/*
 *	CLandInst::Init
 */
void CLandInst::Init() 
{
	cpLand_m->AddRef();
	cpLand_m->cpMeshObj_m->CreateInstance(0,&cpMeshInst_m);

	// TODO PARTICULE
	if(cpLand_m->ePartType_m==CLand::E_LANDINST_FUMES)
	{
		CVector<T_3DVALUE> cPartSize;
		CVector<T_3DVALUE> cPartMove;

		cPartSize.Set(10.0f,10.0f,10.0f);
		cPartMove.Set(15.0f,100.0f,5.0f);

		cpParticleObjCallbackSmoke_m=NEW CParticleObjCallbackSmoke(
			CSystem::cpMath_m,
			0,				// Numéro de l'anim dans l'objet
			4,				// Nombre d'anim pour tirage aléatoire -> anim de la particule 0 ou 1
			&cPartSize,		// Taille de la zone de génération
			&cPartMove,		// Vitesse et direction en T_3DVALUE/SEC des particules
			30,			// Durée entre chaque génération de particule
			0.15f,			// Prob de génération de particule
			25);			// Nombre max de particule

		cpPartObj_m=CSystem::cpPartMgr_m->CreateParticleObj(cpLand_m->cpParticule_m,0,28,25); // (bmapframe,objet,taille particule, nombre max)
		cpPartObj_m->SetCallbackObj(cpParticleObjCallbackSmoke_m);

		cpPartObj_m->SetState(CParticleObj::E_PARTICLEOBJSTATE_ON,0);
	}
	else if(cpLand_m->ePartType_m==CLand::E_LANDINST_SMALLFUMES)
	{
		CVector<T_3DVALUE> cPartSize;
		CVector<T_3DVALUE> cPartMove;

		cPartSize.Set(5.0f,5.0f,5.0f);
		cPartMove.Set(7.0f,50.0f,2.5f);

		cpParticleObjCallbackSmoke_m=NEW CParticleObjCallbackSmoke(
			CSystem::cpMath_m,
			0,				// Numéro de l'anim dans l'objet
			4,				// Nombre d'anim pour tirage aléatoire -> anim de la particule 0 ou 1
			&cPartSize,		// Taille de la zone de génération
			&cPartMove,		// Vitesse et direction en T_3DVALUE/SEC des particules
			30,			// Durée entre chaque génération de particule
			0.15f,			// Prob de génération de particule
			25);			// Nombre max de particule

		cpPartObj_m=CSystem::cpPartMgr_m->CreateParticleObj(cpLand_m->cpParticule_m,0,14,25); // (bmapframe,objet,taille particule, nombre max)
		cpPartObj_m->SetCallbackObj(cpParticleObjCallbackSmoke_m);

		cpPartObj_m->SetState(CParticleObj::E_PARTICLEOBJSTATE_ON,0);
	}
	cpMeshInst_m->InvalidateRepCache();
	cpMeshInst_m->Evaluate();
} /* CLandInst::Init */


/*
 *	CLandInst::Shut
 */
void CLandInst::Shut() 
{
	if(cpMeshInst_m!=0)
	{
		DELETE cpMeshInst_m;
		cpMeshInst_m=0;
	}
	if(cpPartObj_m!=0)
	{
		DELETE cpPartObj_m;
		cpPartObj_m=0;
	}
	if(cpParticleObjCallbackSmoke_m!=0)
	{
		DELETE cpParticleObjCallbackSmoke_m;
		cpParticleObjCallbackSmoke_m=0;
	}
	cpLand_m->Release();
} /* CLandInst::Shut */


/*
 *	CLandInst::Draw
 */
void CLandInst::Draw(CZoneInst* cpZoneInst_p) 
{
	CVector<T_FLOAT> cVec;
	cVec.Set(
		T_FLOAT(cpZoneInst_p->uwX_m*CZone::E_ZONE_SIZE*256+cLandPos_m.biX_m*64),
		T_FLOAT(cLandPos_m.biAltitude_m*4),
		T_FLOAT(-cpZoneInst_p->uwY_m*CZone::E_ZONE_SIZE*256-cLandPos_m.biY_m*64));

	CVector<T_3DVALUE> cPosition=CPlayer::cpWorldView_m->cpCam_m->cTarget_m;

	cPosition-=cVec;
	T_3DVALUE tLen=cPosition.tX*cPosition.tX+cPosition.tZ*cPosition.tZ;
	if(tLen<704*704)
	{
		C3dTransformation *cpRepTrans;
		cpMeshInst_m->GetRepTransRef(&cpRepTrans);
		cpRepTrans->SetTrans(&cVec);

		if(cpLand_m->ePartType_m!=CLand::E_LANDINST_NONE)
		{
			cVec.tX+=48.0f;
			cVec.tZ-=64.0f;
			cpPartObj_m->SetPos(&cVec);
			cpPartObj_m->PlayAndAddPrims(CSystem::cpCtx_m,CSystem::tTime_m);
		}

		cVec.Set(D_PI/2,D_PI/2,3*D_PI/2);
		cpRepTrans->SetRot(&cVec);

		cpMeshInst_m->InvalidateRepCache();
		cpMeshInst_m->Evaluate();
	}
} /* CLandInst::Draw */

