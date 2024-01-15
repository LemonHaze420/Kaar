#ifndef _INCLUDE_LAND_
#define _INCLUDE_LAND_
/**************************************************************************************
 *	Définition d'un Land (objet décor) et de sa classe de positionnement
 **************************************************************************************/
#include "System.h"
#include "Ref.h"


class CGroup;


/*
 *	CLandPos
 */
class CLandPos
{
public:
	T_UWORD biX_m:4;	// 0 à 15 car snap sur les carrés de textures (16*16 par zone)
	T_UWORD biY_m:4;
	T_WORD biAltitude_m:8;	// Altitude entre -512& +511 codée /4

	CLandPos():
		biX_m(0),
		biY_m(0),
		biAltitude_m(0)
	{
	}

	CLandPos(T_UWORD uwX_p,T_UWORD uwY_p,T_WORD wAltitude_p)
	{
		biX_m=uwX_p;
		biY_m=uwY_p;
		biAltitude_m=wAltitude_p;
	}
}; /* CLandPos */


/*
 *	CLand
 */
class CLand:public CRef
{
public:
	enum ELandPartType
	{
		E_LANDINST_NONE=0,
		E_LANDINST_FUMES=1,
		E_LANDINST_SMALLFUMES=2
	};
	char* chpMeshName_m;
	CGroup* cpGroup_m;
	T_UWORD uwIndex_m;		// Index objet dans group de texture

	CMeshObj* cpMeshObj_m;
	ELandPartType ePartType_m;
	CBmFrameObj *cpParticule_m;


	CLand();	// Constructeur vide pour tableau
	CLand(const char* chpMeshName_p,T_UWORD uwIndex_p,ELandPartType ePartType_p=E_LANDINST_NONE);	// Constructeur pour liste
	~CLand();

	CLand& operator=(CLand& crLand_p);	// Redéfinition = pour conversion liste en tableau

private:
	// Virtual pure de CRef
	virtual void Init();
	virtual void Shut();
}; /* CLand */


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif


