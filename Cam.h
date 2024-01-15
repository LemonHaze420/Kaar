#ifndef _INCLUDE_CAM_
#define _INCLUDE_CAM_
/**************************************************************************************
 * 
 **************************************************************************************/
#include "System.h"


/*
 *	CCam
 */
class CCam	// TODO KERNEL CAMERA
{
public:
	CCamera* cpCamera_m;
	CMatrix* cpMatrix_m;
	CVector<T_3DVALUE> cTarget_m;
	CVector<T_3DVALUE> cPosition_m;
	CVector<T_MATHANVALUE> cRot_m;
	CVector<T_3DVALUE> cDelta_m;
	// TODO LIGHT

	CCam();
	~CCam();

	void SetTarget(CVector<T_3DVALUE>* cpPosition_p);
	void SetRot(T_FLOAT fX_p,T_FLOAT fY_p);
	void SetPos(T_FLOAT fH_p);

	void Update();

	T_3DVALUE GetXPos();
	T_3DVALUE GetYPos();
	T_3DVALUE GetAltitude();


//	void Get3dPos(T_UWORD uwWorld_p,CPt<T_2DVALUE>* cp2dPosition_p,CVector<T_3DVALUE>* cp3dPosition_p);

private:
	void GetDeltaFromTarget();
}; /* CCam */


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif


