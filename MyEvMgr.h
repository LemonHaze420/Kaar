#ifndef _INCLUDE_MYEVMGR_
#define _INCLUDE_MYEVMGR_
/**************************************************************************************
 * 
 **************************************************************************************/
#include "System.h"


class CMyEvMgr:public CWinEventMgr
{
public: 		
	T_BOOL boFocus_m;

	virtual void CharInput(T_CHAR tChar_p)
	{
		//cpKbd_m->PlayKbdCharEvent(tChar_p);
	}
	virtual void FocusLost()
	{
		if(CSystem::cp3d_m!=0)
			CSystem::cp3d_m->LooseFocus();
		if(CSystem::cp2d_m!=0)
			CSystem::cp2d_m->LooseFocus();
		boFocus_m=false;
	}
	virtual void FocusGained()
	{
		if(CSystem::cp2d_m!=0)
			CSystem::cp2d_m->GainFocus();
		if(CSystem::cp3d_m!=0)
			CSystem::cp3d_m->GainFocus();
		boFocus_m=true;
	}
};


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif


