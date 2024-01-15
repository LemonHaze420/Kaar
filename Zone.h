#ifndef _INCLUDE_ZONE_
#define _INCLUDE_ZONE_
/**************************************************************************************
 * Zone = 2 pointeur sur groups + tableau de pointeur sur bloc + list de set d'objet de décor
 **************************************************************************************/
#include "System.h"
#include "Ref.h"
#include "Group.h"
#include "Bloc.h"
#include "List.h"
#include "Set.h"


/*
 *	CZone
 */
class CZone:public CRef
{
public:
	enum EZoneSize
	{
		E_ZONE_SIZE=4,
		E_ZONE_SIZE2=E_ZONE_SIZE*E_ZONE_SIZE
	};
	CGroup* cpGroupA_m;
	CGroup* cpGroupB_m;

	CBloc* cppBloc_m[E_ZONE_SIZE2];
	CBlocPos cpBlocPos_m[E_ZONE_SIZE2];

	CList<CSet> cListSet_m;
	CSet* cpSet_m;
	T_UWORD uwNbSet_m;

	CZone();
	~CZone();

	CZone& operator=(CZone& crZone_p);		

private:
	// Virtual pure de CRef
	virtual void Init();
	virtual void Shut();
}; /* CZone */


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif


