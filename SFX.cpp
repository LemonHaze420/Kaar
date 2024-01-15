#include "SFX.h"


CBmFrameObj* CSFX::cpShadow_m;
CBmFrameObj* CSFX::cpParticule_m;
CBmFrameObj* CSFX::cpBlood_m;
T_BOOL CSFX::bShadow_m=true;
CParticleObj* CSFX::cpPartObjBlood_m;
CParticleObjCallbackSmoke* CSFX::cpParticleObjCallbackBlood_m;
T_DATE CSFX::tBloodDate_m;
T_BOOL CSFX::bBlood_m=false;


CSFX::CSFX()
{
	// Shadow
	CMaterial* cpMat;
	CSystem::cpFrame_m->CreateBmFrameObj(CSystem::cpFileCtx_m,CSystem::cp2d_m,"SHADOW",CBmap::F_CREATIONFLAGS_TEXTURABLE,&cpShadow_m);
	cpShadow_m->CreateMaterials(CSystem::cp3d_m);
	cpShadow_m->CreateTextures(CSystem::cp3d_m,0);

	T_CARD t,tNbMat;
	cpShadow_m->GetNbBmaps(&tNbMat);
	for(t=0;t<tNbMat;t++)
	{
		cpShadow_m->GetMaterialPtr(t,&cpMat);
		cpMat->SetBlending(CMaterial::E_BLMODE_NOSRCDESTINVSRC);
		cpMat->SetFlags(CMaterial::F_MATFLAGS_OPACITY);
	}

	// Particule
	CSystem::cpFrame_m->CreateBmFrameObj(CSystem::cpFileCtx_m,CSystem::cp2d_m,"SHOOT",CBmap::F_CREATIONFLAGS_TEXTURABLE,&cpParticule_m);
	cpParticule_m->CreateTextures(CSystem::cp3d_m,0);
	cpParticule_m->CreateMaterials(CSystem::cp3d_m);

	cpParticule_m->GetNbBmaps(&tNbMat);
	for(t=0;t<tNbMat;t++)
	{
		cpParticule_m->GetMaterialPtr(t,&cpMat);
		cpMat->SetBlending(CMaterial::E_BLMODE_ADDSRCANDDEST);
		cpMat->SetFlags(CMaterial::F_MATFLAGS_OPACITY);
	}
	// Blood
	CSystem::cpFrame_m->CreateBmFrameObj(CSystem::cpFileCtx_m,CSystem::cp2d_m,"BLOOD",CBmap::F_CREATIONFLAGS_TEXTURABLE,&cpBlood_m);
	cpBlood_m->CreateTextures(CSystem::cp3d_m,0);
	cpBlood_m->CreateMaterials(CSystem::cp3d_m);

	cpBlood_m->GetNbBmaps(&tNbMat);
	for(t=0;t<tNbMat;t++)
	{
		cpBlood_m->GetMaterialPtr(t,&cpMat);
		cpMat->SetBlending(/*E_BLMODE_ADDSRCANDDEST*/CMaterial::E_BLMODE_INVSRCANDDEST);
		cpMat->SetFlags(CMaterial::F_MATFLAGS_OPACITY);
	}
	CVector<T_3DVALUE> cPartSize;
	CVector<T_3DVALUE> cPartMove;
	cPartSize.Set(32.0,1.0,32.0);
	cPartMove.Set(0.0,0.0,0.0);

	cpParticleObjCallbackBlood_m=NEW CParticleObjCallbackSmoke(
		CSystem::cpMath_m,
		0,				// Numéro de l'anim dans l'objet
		3,				// Nombre d'anim pour tirage aléatoire -> anim de la particule 0 ou 1
		&cPartSize,		// Taille de la zone de génération
		&cPartMove,		// Vitesse et direction en T_3DVALUE/SEC des particules
		1000,			// Durée entre chaque génération de particule
		1.0f,			// Prob de génération de particule
		50);			// Nombre max de particule
	cpPartObjBlood_m=CSystem::cpPartMgr_m->CreateParticleObj(cpBlood_m,0,20,50); // (bmapframe,objet,taille particule, nombre max)
	cpPartObjBlood_m->SetCallbackObj(cpParticleObjCallbackBlood_m);
	cpPartObjBlood_m->SetState(CParticleObj::E_PARTICLEOBJSTATE_OFF,CSystem::tTime_m);

	tBloodDate_m=0;
}


CSFX::~CSFX()
{
	DELETE cpBlood_m;
	DELETE cpShadow_m;
	DELETE cpParticleObjCallbackBlood_m;
	DELETE cpPartObjBlood_m;
	DELETE cpParticule_m;
}


void CSFX::SetBlood(CVector<T_3DVALUE>* cpPosition_p)
{
	if(!bBlood_m)
		return;
	CVector<T_3DVALUE> cPosition=*cpPosition_p;
	cPosition.tY+=32;
	cpPartObjBlood_m->SetPos(&cPosition);
	tBloodDate_m=CSystem::tTime_m+500;
	cpPartObjBlood_m->SetState(CParticleObj::E_PARTICLEOBJSTATE_ON,CSystem::tTime_m);
}


void CSFX::UpdateBlood()
{
	if(!bBlood_m)
		return;
	cpPartObjBlood_m->PlayAndAddPrims(CSystem::cpCtx_m,CSystem::tTime_m);
	if(tBloodDate_m<CSystem::tTime_m)
		cpPartObjBlood_m->SetState(CParticleObj::E_PARTICLEOBJSTATE_OFF,CSystem::tTime_m);
}




