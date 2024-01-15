#include "Group.h"


/*
 *	CGroup::CGroup
 */
CGroup::CGroup():
	chpTextureName_m(0),
	cpBloc_m(0),
	uwNbBloc_m(0),
	cpLand_m(0),
	uwNbLand_m(0),
	cpTexture_m(0)
{
} /* CGroup::CGroup */


/*
 *	CGroup::CGroup
 */
CGroup::CGroup(const char* chpTextureName_p):
	cpBloc_m(0),
	uwNbBloc_m(0),
	cpLand_m(0),
	uwNbLand_m(0),
	cpTexture_m(0)
{
	chpTextureName_m=NEW char[strlen(chpTextureName_p)+1];
	strcpy(chpTextureName_m,chpTextureName_p);
} /* CGroup::CGroup */


/*
 *	CGroup::~CGroup
 */
CGroup::~CGroup()
{
	if(chpTextureName_m!=0)
		DELETE []chpTextureName_m;
	if(cpBloc_m!=0)
		DELETE []cpBloc_m;
	if(cpLand_m!=0)
		DELETE []cpLand_m;
	if(cpTexture_m!=0)
	{
		cpTexture_m->ReleaseTextures();
		cpTexture_m->ReleaseMaterials();
		DELETE cpTexture_m;
	}
} /* CGroup::~CGroup */


/*
 *	CGroup::operator=
 */
CGroup& CGroup::operator=(CGroup& crGroup_p)
{
	chpTextureName_m=NEW char[strlen(crGroup_p.chpTextureName_m)+1];
	strcpy(chpTextureName_m,crGroup_p.chpTextureName_m);
	uwNbBloc_m=crGroup_p.uwNbBloc_m;
	if(uwNbBloc_m!=0)
	{
		cpBloc_m=NEW CBloc[uwNbBloc_m];
		for(T_UWORD uw=0;uw<uwNbBloc_m;uw++)
		{
			cpBloc_m[uw]=crGroup_p.cpBloc_m[uw];
			cpBloc_m[uw].cpGroup_m=this;
		}
	}
	else
		cpBloc_m=0;
		
	uwNbLand_m=crGroup_p.uwNbLand_m;
	if(uwNbLand_m!=0)
	{
		cpLand_m=NEW CLand[uwNbLand_m];
		for(T_UWORD uw=0;uw<uwNbLand_m;uw++)
		{
			cpLand_m[uw]=crGroup_p.cpLand_m[uw];
			cpLand_m[uw].cpGroup_m=this;
		}
	}
	else
		cpLand_m=0;

	cpTexture_m=0;
	return *this;
} /* CGroup::operator= */


/*
 *	CGroup::Init
 */
void CGroup::Init() 
{
	CSystem::cpFrame_m->CreateBmFrameObj(CSystem::cpFileCtx_m,CSystem::cp2d_m,chpTextureName_m,CBmap::F_CREATIONFLAGS_TEXTURABLE,&cpTexture_m);
	cpTexture_m->CreateMaterials(CSystem::cp3d_m);
	cpTexture_m->CreateTextures(CSystem::cp3d_m,0);

	T_CARD tNbMat;
	cpTexture_m->GetNbBmaps(&tNbMat);
	for(T_CARD t=0;t<tNbMat;t++)
	{
		CMaterial* cpMat;
		cpTexture_m->GetMaterialPtr(t,&cpMat);
		cpMat->SetFlags(CMaterial::F_MATFLAGS_OPACITY);
	}

// Realease bitmap et garde texture
//	cpTexture_m->ReleaseBmaps();

} /* CGroup::Init */


/*
 *	CGroup::Shut
 */
void CGroup::Shut() 
{
	if(cpTexture_m!=0)
	{
		cpTexture_m->ReleaseTextures();
		cpTexture_m->ReleaseMaterials();
		DELETE cpTexture_m;
		cpTexture_m=0;
	}
} /* CGroup::Shut */


/*
 *	CGroup::SetCtx
 */
void CGroup::SetCtx(CRenderCtx* cpCtx_p)
{
	T_UWORD uw;
	for(uw=0;uw<uwNbBloc_m;uw++)
	{
		if(cpBloc_m[uw].cpMeshObj_m!=0)
			cpBloc_m[uw].cpMeshObj_m->SetRenderCtx(cpCtx_p);
	}
	for(uw=0;uw<uwNbLand_m;uw++)
	{
		if(cpLand_m[uw].cpMeshObj_m!=0)
			cpLand_m[uw].cpMeshObj_m->SetRenderCtx(cpCtx_p);
	}
} /* CGroup::SetCtx */


