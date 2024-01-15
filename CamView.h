#ifndef _INCLUDE_CAMVIEW_
#define _INCLUDE_CAMVIEW_
/**************************************************************************************
 * 
 **************************************************************************************/
#include "System.h"
#include "Cam.h"
//#include "WorldPos.h"


/*
 *	CCamView
 */
class CCamView
{
public:
	enum ECamViewAltitude
	{
		E_CAMVIEW_ALTITUDE=150
	};

	static CCam* cpCam_m;
	static CVector<T_3DVALUE> cPosition_m;
	static CVector<T_3DVALUE> cToGo_m;

	CCamView();
	~CCamView();

	static T_BOOL UpdateGoTo(T_UWORD uwWorld_p,CVector<T_3DVALUE>* cpToGo_p=0);
	static void UpdateTarget(CVector<T_3DVALUE>* cpPosition_p);

private:
	static T_DATE tPrevTime_m;

}; /* CCamView */


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif


