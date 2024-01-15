#include "ZoneItem.h"


/*
 *	CZoneItem::Draw
 */
void CZoneItem::Draw()
{
	for(T_UWORD uwLand=0;uwLand<cpZoneInst_m->uwNbLandInst_m;uwLand++)
		cpZoneInst_m->cpLandInst_m[uwLand].Draw(cpZoneInst_m);
} /* CZoneItem::Draw */


