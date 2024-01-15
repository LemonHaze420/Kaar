#ifndef _INCLUDE_ZONEITEM_
#define _INCLUDE_ZONEITEM_
/**************************************************************************************
 * 
 **************************************************************************************/
#include "ZoneInst.h"


/*
 *	CZoneItem
 */
class CZoneItem
{
public:
	CZoneInst* cpZoneInst_m;

	void Set();
	void Draw();
}; /* CZoneItem */


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif


