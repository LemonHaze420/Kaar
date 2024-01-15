#ifndef _INCLUDE_GROUP_
#define _INCLUDE_GROUP_
/**************************************************************************************
 * Description Group decor
 **************************************************************************************/
#include "System.h"
#include "List.h"
#include "Bloc.h"
#include "Land.h"



/*
 *	CGroup
 */
class CGroup:public CRef
{
public:
	char* chpTextureName_m;
	// Liste&tableau de Bloc
	CList<CBloc> cListBloc_m;
	CBloc* cpBloc_m;
	T_UWORD uwNbBloc_m;
	CList<CLand> cListLand_m;
	CLand* cpLand_m;
	T_UWORD uwNbLand_m;

	CBmFrameObj* cpTexture_m;


	CGroup();	// Constructeur vide pour tableau
	CGroup(const char* chpTextureName_p);	// Constructeur pour liste
	~CGroup();

	CGroup& operator=(CGroup& crGroup_p);	// Redéfinition = pour conversion liste en tableau

	void SetCtx(CRenderCtx* cpCtx_p);

private:
	// Virtual pure de CRef
	virtual void Init();
	virtual void Shut();
}; /* CGroup */


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif


