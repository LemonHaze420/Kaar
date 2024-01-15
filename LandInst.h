#ifndef _INCLUDE_LANDINST_
#define _INCLUDE_LANDINST_
/**************************************************************************************
 * Description instance land object (objet de décor)
 **************************************************************************************/
#include "System.h"
#include "Ref.h"
#include "Land.h"
#include "DivHea\crpasmok.h"


class CZoneInst;


/*
 *	CLandInst
 */
class CLandInst:public CRef
{
public:
//	CCell* cpCell_m;
	CLand* cpLand_m;
	CLandPos cLandPos_m; 
	CMeshObj* cpMeshInst_m;


	CLandInst();	// Constructeur vide pour tableau
	Set(CLand* cpLand_p,CLandPos* cpLandPos_p);
	~CLandInst();

	void Draw(CZoneInst* cpZoneInst_p);

private:
	CParticleObj *cpPartObj_m;
	CParticleObjCallbackSmoke* cpParticleObjCallbackSmoke_m;

	// Virtual pure de CRef
	virtual void Init();
	virtual void Shut();
}; /* CLandInst */


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif


