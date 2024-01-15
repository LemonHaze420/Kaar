#include "Zone.h"


/*
 *	CZone::CZone
 */
CZone::CZone():
	cpGroupA_m(0),
	cpGroupB_m(0),
	cpSet_m(0),
	uwNbSet_m(0)
{
	// Constructeur vide pour tableau
} /* CZone::CZone */


/*
 *	CZone::~CZone
 */
CZone::~CZone()
{
	if(uwNbSet_m!=0)
		DELETE []cpSet_m;
} /* CZone::~CZone */


/*
 *	CZone::operator=
 */
CZone& CZone::operator=(CZone& crZone_p)
{
	cpGroupA_m=crZone_p.cpGroupA_m;
	cpGroupB_m=crZone_p.cpGroupB_m;
	memcpy(cppBloc_m,crZone_p.cppBloc_m,E_ZONE_SIZE2*sizeof(CBloc*));
	memcpy(cpBlocPos_m,crZone_p.cpBlocPos_m,E_ZONE_SIZE2*sizeof(CBlocPos));
	
	uwNbSet_m=crZone_p.uwNbSet_m;
	if(uwNbSet_m!=0)
	{
		cpSet_m=NEW CSet[uwNbSet_m];
		for(T_UWORD uw=0;uw<uwNbSet_m;uw++)
			cpSet_m[uw]=crZone_p.cpSet_m[uw];
	}

	return *this;
} /* CZone::operator= */


/*
 *	CZone::Init
 */
void CZone::Init() 
{
	// Load les textures
	cpGroupA_m->AddRef();
	if(cpGroupB_m!=0)
		cpGroupB_m->AddRef();
} /* CZone::Init */


/*
 *	CZone::Shut
 */
void CZone::Shut() 
{
	// Release textures
	cpGroupA_m->Release();
	if(cpGroupB_m!=0)
		cpGroupB_m->Release();
} /* CZone::Shut */

