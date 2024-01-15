#include "World.h"


/*
 *	CWorld::CWorld
 */
CWorld::CWorld():
	uwXSize_m(0),
	uwYSize_m(0),
	cpZoneInst_m(0),
	ulNbCharacter_m(0)
{
} /* CWorld::CWorld */


/*
 *	CWorld::CWorld
 */
CWorld::CWorld(T_UWORD uwXSize_p,T_UWORD uwYSize_p):
	uwXSize_m(uwXSize_p),
	uwYSize_m(uwYSize_p),
	cpZoneInst_m(NEW CZoneInst[uwXSize_p*uwYSize_p])
{
} /* CWorld::CWorld */


/*
 *	CWorld::~CWorld
 */
CWorld::~CWorld()
{
	if(cpZoneInst_m!=0)
		DELETE []cpZoneInst_m;
	cListCharacter_m.Delete();
} /* CWorld::~CWorld */


/*
 *	CWorld::operator=
 */
CWorld& CWorld::operator=(CWorld& crWorld_p)
{
	uwXSize_m=crWorld_p.uwXSize_m;
	uwYSize_m=crWorld_p.uwYSize_m;
	cpZoneInst_m=NEW CZoneInst[uwXSize_m*uwYSize_m];
	for(T_UWORD uw=0;uw<uwXSize_m*uwYSize_m;uw++)
		cpZoneInst_m[uw]=crWorld_p.cpZoneInst_m[uw];

	// Les lists ont aussi le = de redéfinie
	cListCharacter_m=crWorld_p.cListCharacter_m;
	ulNbCharacter_m=crWorld_p.ulNbCharacter_m;

	return *this;
} /* CWorld::operator= */



/*
 *	CWorld::GetZoneInst
 *
CZoneInst* CWorld::GetZoneInst(T_FLOAT fX,T_FLOAT fY)
{
	// En dehors du monde ?
	if(fX<0.0f || -fY<0.0f)
		return 0;

	// Index et coordonnée de la zone dans le monde
	T_WORD wXZone=T_WORD(fX/T_FLOAT(CZone::E_ZONE_SIZE*256));
	T_WORD wYZone=T_WORD(-fY/T_FLOAT(CZone::E_ZONE_SIZE*256));
	// En dehors du monde ?
	if(wXZone>=uwXSize_m || wYZone>=uwYSize_m)
		return 0;

	T_UWORD uwIndexZone=wXZone+uwXSize_m*wYZone;
	return &cpZoneInst_m[uwIndexZone];
} /* CWorld::GetZoneInst */


