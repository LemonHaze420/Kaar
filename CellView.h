#ifndef _INCLUDE_CELLVIEW_
#define _INCLUDE_CELLVIEW_
/**************************************************************************************
 * Affichage Cellule de bloc (256 par bloc)
 **************************************************************************************/
#include "System.h"


class CCellView
{
public:
	static T_ULONG ulRef_m;
	static CBmFrameObj* cpTexture_m;
	static CMeshObj* cpMeshObj_m;
	CMeshObj* cpMeshInst_m;

	CCellView();
	~CCellView();

	void Draw(T_3DVALUE tX_p,T_3DVALUE tZ_p,T_3DVALUE tY_p);

};


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif


