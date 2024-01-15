#include "ZoneInst.h"


/*
 *	CZoneInst::CZoneInst
 */
CZoneInst::CZoneInst():
	cpZone_m(0),
	uwX_m(0),
	uwY_m(0),
	wAltitude_m(0),
	eZoneGeo_m(E_ZONEINST_GEOHUMAIN),
	cpLandInst_m(0),
	uwNbLandInst_m(0)
{
} /* CZoneInst::CZoneInst */


/*
 *	CZoneInst::~CZoneInst
 */
CZoneInst::~CZoneInst()
{
	if(cpLandInst_m!=0)
		DELETE []cpLandInst_m;
} /* CZoneInst::~CZoneInst */


/*
 *	CZoneInst::operator=
 */
CZoneInst& CZoneInst::operator=(CZoneInst& crZoneInst_p)
{
	cpZone_m=crZoneInst_p.cpZone_m;
	uwX_m=crZoneInst_p.uwX_m;
	uwY_m=crZoneInst_p.uwY_m;
	wAltitude_m=crZoneInst_p.wAltitude_m;
	eZoneGeo_m=crZoneInst_p.eZoneGeo_m;
	memcpy(cpBlocInst_m,crZoneInst_p.cpBlocInst_m,CZone::E_ZONE_SIZE2*sizeof(CBlocInst));
	uwNbLandInst_m=crZoneInst_p.uwNbLandInst_m;
	if(uwNbLandInst_m!=0)
	{
		cpLandInst_m=NEW CLandInst[uwNbLandInst_m];
		for(T_UWORD uw=0;uw<uwNbLandInst_m;uw++)
			cpLandInst_m[uw]=crZoneInst_p.cpLandInst_m[uw];
	}
	return *this;
} /* CZoneInst::operator= */


/* 
 *	CZoneInst::Set
 */
void CZoneInst::Set(CZone* cpZone_p,T_UWORD uwX_p,T_UWORD uwY_p,T_WORD wAltitude_p,EZoneInstGeo eZoneGeo_p)
{
	if(cpZone_m!=0)
		throw "CZoneInst - Set instance sur ZoneInst déjà initialisé";

	cpZone_m=cpZone_p;
	uwX_m=uwX_p;
	uwY_m=uwY_p;
	wAltitude_m=wAltitude_p;
	eZoneGeo_m=eZoneGeo_p;
	uwNbLandInst_m=0;	// Pas de landset
	cpLandInst_m=0;

	for(T_UWORD uw=0;uw<CZone::E_ZONE_SIZE2;uw++)
		cpBlocInst_m[uw].Set(cpZone_m->cppBloc_m[uw],&cpZone_m->cpBlocPos_m[uw]);
} /* CZoneInst::Set */


/* 
 *	CZoneInst::Set
 */
void CZoneInst::Set(CZone* cpZone_p,T_UWORD uwSet_p,T_UWORD uwX_p,T_UWORD uwY_p,T_WORD wAltitude_p,EZoneInstGeo eZoneGeo_p)
{
	if(cpZone_m!=0)
		throw "CZoneInst - Set instance sur ZoneInst déjà initialisé";

	cpZone_m=cpZone_p;
	uwX_m=uwX_p;
	uwY_m=uwY_p;
	wAltitude_m=wAltitude_p;
	eZoneGeo_m=eZoneGeo_p;

	uwNbLandInst_m=cpZone_m->cpSet_m[uwSet_p].uwNbLand_m;
	cpLandInst_m=NEW CLandInst[uwNbLandInst_m];

	T_UWORD uw;
	CSet* cpSet=&cpZone_m->cpSet_m[uwSet_p];
	for(uw=0;uw<uwNbLandInst_m;uw++)
		cpLandInst_m[uw].Set(cpSet->cpLandPtr_m[uw].cpLand_m,&cpSet->cpLandPos_m[uw]);

	for(uw=0;uw<CZone::E_ZONE_SIZE2;uw++)
		cpBlocInst_m[uw].Set(cpZone_m->cppBloc_m[uw],&cpZone_m->cpBlocPos_m[uw]);
} /* CZoneInst::Set */


/*
 *	CZoneInst::GetBlocInst
 *
CBlocInst* CZoneInst::GetBlocInst(T_FLOAT fX_p,T_FLOAT fY_p)
{
	// Coordonnée du bloc dans la zone
	T_UWORD uwXBloc=T_UWORD(fX_p/256.0f)%CZone::E_ZONE_SIZE;
	T_UWORD uwYBloc=T_UWORD(-fY_p/256.0f)%CZone::E_ZONE_SIZE;
	T_UWORD uwIndexBloc=uwXBloc+uwYBloc*CZone::E_ZONE_SIZE;
	return &cpBlocInst_m[uwIndexBloc];
} /* CZoneInst::GetBlocInst */


/*
 *	CZoneInst::Init
 */
void CZoneInst::Init() 
{
	// Load les textures
	cpZone_m->AddRef();

	// Crée les instances // TODO
	T_UWORD uw;
	// Charge les blocs et crée les instances
	for(uw=0;uw<CZone::E_ZONE_SIZE2;uw++)
		cpBlocInst_m[uw].AddRef();

	// Charge les land object et crée les instances
	for(uw=0;uw<uwNbLandInst_m;uw++)
		cpLandInst_m[uw].AddRef();
} /* CZoneInst::Init */


/*
 *	CZoneInst::Shut
 */
void CZoneInst::Shut() 
{
	// Release les instances // TODO
	T_UWORD uw;
	// Release les land (mesh+instances)
	for(uw=0;uw<uwNbLandInst_m;uw++)
		cpLandInst_m[uw].Release();

	// Release les blocs (mesh+instances)
	for(uw=0;uw<CZone::E_ZONE_SIZE2;uw++)
		cpBlocInst_m[uw].Release();

	// Release les textures
	cpZone_m->Release();
} /* CZoneInst::Shut */



