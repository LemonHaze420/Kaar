#ifndef _INCLUDE_SCREEN_
#define _INCLUDE_SCREEN_
/**************************************************************************************
 * 
 **************************************************************************************/
#include "System.h"
#include "Render.h"
#include "Interface.h"
#include "Cursor.h"


/*
 *	CScreen
 */
class CScreen
{
public:
	enum EScreenType
	{
		E_SCREEN_TYPELEFT=1,
		E_SCREEN_TYPERIGHT=2
	};
	static CPt<T_2DVALUE> cSize_m;

	static CPt<T_2DVALUE> cRenderSize_m;
	static CPt<T_2DVALUE> cRenderPos_m;
	static CPt<T_2DVALUE> cInterfaceSize_m;
	static CPt<T_2DVALUE> cInterfacePos_m;
	
	CScreen(T_UWORD uwXSize_p,T_UWORD uwYSize_p,EScreenType eType_p);
	~CScreen();

	void Update(T_UWORD uwXSize_p,T_UWORD uwYSize_p,EScreenType eType_p);

	static void BeginRendering();
	static void EndRendering();
	static bool CheckPtInRect(CPt<T_2DVALUE>* cpPt_p,CRectangle<T_2DVALUE>* cpRect_p);

	static void Flip(T_BOOL bDebug_p=false);
	static void Print(char* chpText_p);

private:
	EScreenType eType_m;
	CRender* cpRender_m;
	static CInterface* cpInterface_m;
	static CCursor* cpCursor_m;
	static T_UWORD uwBorder_m;
	static T_LONG lNbPrim_m;
	static	T_DATE tDateText_m;
	static char chpText_m[81];


	CBmFrameObj* cpFontFrame_m;

	void CreateFont();
}; /* CScreen */


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif

