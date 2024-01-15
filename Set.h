#ifndef _INCLUDE_SET_
#define _INCLUDE_SET_
/**************************************************************************************
 * Set = ensemble d'objets décors (Land) et de ses positions associées
 **************************************************************************************/
#include "System.h"
#include "Land.h"
#include "List.h"


/*
 *	CLandPtr
 */
class CLandPtr
{
public:
	CLand* cpLand_m;

	CLandPtr():cpLand_m(0) {}
	CLandPtr(CLand* cpLand_p):cpLand_m(cpLand_p) {}
}; /* CLandPtr */


/*
 *	CSet
 */
class CSet
{
public:
	CList<CLandPtr> cListLandPtr_m;
	CList<CLandPos> cListLandPos_m;
	T_UWORD uwNbLand_m;
	CLandPtr* cpLandPtr_m;
	CLandPos* cpLandPos_m;

	CSet();
	~CSet();

	CSet& operator=(CSet& crSet_p);		
}; /* CSet */


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif


