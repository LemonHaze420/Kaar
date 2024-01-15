#ifndef _INCLUDE_BLOC_
#define _INCLUDE_BLOC_
/**************************************************************************************
 * Description bloc 3D
 **************************************************************************************/
#include "System.h"
#include "Ref.h"


class CGroup;


/*
 *	CBlocPos
 */
class CBlocPos
{
public:
	T_UWORD biX_m:2;	// 0 à 3 car 4*4 blocs par zone
	T_UWORD biY_m:2;
	T_WORD biAltitude_m:4;	// Altitude entre -512& +511 codée /64 (-8...+7)

	CBlocPos():
		biX_m(0),
		biY_m(0),
		biAltitude_m(0)
	{
	}

	void Set(T_UWORD uwX_p,T_UWORD uwY_p,T_WORD wAltitude_p)
	{
		biX_m=uwX_p;
		biY_m=uwY_p;
		biAltitude_m=wAltitude_p;
	}
}; /* CBlocPos */


/*
 *	CBloc
 */
class CBloc:public CRef
{
public:
	char* chpMeshName_m;
	CGroup* cpGroup_m;
	T_UWORD uwIndex_m;		// Index objet dans group de texture

	CMeshObj* cpMeshObj_m;

	CBloc();	// Constructeur vide pour tableau
	CBloc(const char* chpMeshName_p,T_UWORD uwIndex_p);	// Constructeur pour liste
	~CBloc();

	CBloc& operator=(CBloc& crBloc_p);	// Redéfinition = pour conversion liste en tableau

private:
	// Virtual pure de CRef
	virtual void Init();
	virtual void Shut();
}; /* CBloc */


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif


