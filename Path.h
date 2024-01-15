#ifndef _INCLUDE_PATH_
#define _INCLUDE_PATH_
/**************************************************************************************
 *
 **************************************************************************************/
#include "System.h"
#include "List.h"


class CPathPos
{
public:
	T_WORD wDX_m;
	T_WORD wDY_m;

	CPathPos() {}
	CPathPos(T_WORD wDX_p,T_WORD wDY_p):
		wDX_m(wDX_p),
		wDY_m(wDY_p)
	{
	}
	bool operator==(CPathPos& crPathPos_p)
	{
		if(wDX_m==crPathPos_p.wDX_m && wDY_m==crPathPos_p.wDY_m)
			return true;
		return false;
	}

};


class CPath
{
public:
	CList<CPathPos> cListPathPos_m;
	CPathPos* cpPathPos_m;
	T_UWORD uwNbPathPos_m;

	CPath():
		cpPathPos_m(0),
		uwNbPathPos_m(0)
	{}
	~CPath()
	{
		if(cpPathPos_m!=0)
			DELETE cpPathPos_m;
	}

	CPath& operator=(CPath& crPath_p)
	{
		cListPathPos_m=crPath_p.cListPathPos_m;
		uwNbPathPos_m=crPath_p.uwNbPathPos_m;
		if(uwNbPathPos_m!=0)
		{
			cpPathPos_m=NEW CPathPos[uwNbPathPos_m];
			memcpy(cpPathPos_m,crPath_p.cpPathPos_m,uwNbPathPos_m*sizeof(CPathPos));
		}
		return *this;
	}
};


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif

