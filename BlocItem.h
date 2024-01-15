#ifndef _INCLUDE_BLOCITEM_
#define _INCLUDE_BLOCITEM_
/**************************************************************************************
 * 
 **************************************************************************************/
#include "System.h"
#include "ZoneInst.h"
#include "BlocInst.h"


/*
 *	CBlocItem
 */
class CBlocItem
{
public:
	CZoneInst* cpZoneInst_m;
	CBlocInst* cpBlocInst_m;

	CBlocItem();

	void Set(CZoneInst* cpZoneInst_p,CBlocInst* cpBlocInst_p);
	void Draw();

private:
	CMeshObj* cpMeshObj_m;
}; /* CBlocItem */


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif


