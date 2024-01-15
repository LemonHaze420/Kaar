#include "Set.h"


/*
 *	CSet::CSet
 */
CSet::CSet():
	uwNbLand_m(0),
	cpLandPtr_m(0),
	cpLandPos_m(0)
{
} /* CSet::CSet */


/*
 *	CSet::~CSet
 */
CSet::~CSet()
{
	if(cpLandPtr_m!=0)
		DELETE []cpLandPtr_m;
	if(cpLandPos_m!=0)
		DELETE []cpLandPos_m;
} /* CSet::~CSet */


/*
 *	CSet::operator=
 */
CSet& CSet::operator=(CSet& crSet_p)
{
	uwNbLand_m=crSet_p.uwNbLand_m;
	cpLandPtr_m=NEW CLandPtr[uwNbLand_m];
	cpLandPos_m=NEW CLandPos[uwNbLand_m];
	memcpy(cpLandPtr_m,crSet_p.cpLandPtr_m,uwNbLand_m*sizeof(CLandPtr));
	memcpy(cpLandPos_m,crSet_p.cpLandPos_m,uwNbLand_m*sizeof(CLandPos));

	return *this;
} /* CSet::operator= */
