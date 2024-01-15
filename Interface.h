#ifndef _INCLUDE_INTERFACE_
#define _INCLUDE_INTERFACE_
/**************************************************************************************
 * 
 **************************************************************************************/
#include "System.h"
#include "IntChar.h"


/*
 *	CInterface
 */
class CInterface
{
public:
	enum EInterfaceElmt
	{
		E_INTERFACE_ALL=0x01
	};
	static CBmap* cpBmap_m;
	static CPt<T_2DVALUE>* cpSize_m;

	static T_UWORD uwLife_m;
	static T_UWORD uwTireness_m;
	static T_UWORD uwSelected_m;
	static T_UWORD uwPC_m;
	static T_UWORD uwNPC_m;

	static T_UWORD uwRed_m;
	static T_UWORD uwYellow_m;
	static T_UWORD uwGreen_m;
	static T_UWORD uwScroll_m;

	CIntChar* cpIntChar_m;

	CInterface(CPt<T_2DVALUE>* cpSize_p);
	~CInterface();

	void Update(T_FLAGS tElmt=E_INTERFACE_ALL);
	void Draw();
		
	void SetPos(CPt<T_2DVALUE>* cpPos_p);

	static void Bevel(CRectangle<T_2DVALUE>* cpRect_p,T_UWORD uwThickness_p,T_BOOL bUp_p,void* pScreen_p=0);

private:
	CPt<T_2DVALUE>* cpPos_m;
	CBmFrameObj* cpTexture_m;
	CBmFrameObj* cpLogo_m;
	CBmFrameObj* cpRadar_m;
	static T_UWORD uwDarkMsk_m;
	static T_UWORD uwLightMsk_m;
	T_UWORD uwCurPChar_m;
	T_UWORD uwNbPChar_m;

	static void HBevel(CRectangle<T_2DVALUE>* cpRect_p,T_UWORD uwThickness_p,T_BOOL bUp_p,void* pScreen_p=0);
	static void VBevel(CRectangle<T_2DVALUE>* cpRect_p,T_UWORD uwThickness_p,T_BOOL bUp_p,void* pScreen_p=0);

//	void CInterface::StateBar(CPt<T_2DVALUE>* cpPt_p,T_UWORD uwLife_p,T_UWORD uwTireness_p,void* pScreen_p=0);
	void DrawMap(CPt<T_2DVALUE>* cpPt_p,void* pScreen_p=0);

}; /* CInterface */


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif

