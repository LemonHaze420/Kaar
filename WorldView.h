#ifndef _INCLUDE_WORLDVIEW_
#define _INCLUDE_WORLDVIEW_
/**************************************************************************************
 * 
 **************************************************************************************/
#include "System.h"
#include "Character.h"
#include "ZoneView.h"
#include "CellView.h"
#include "CamView.h"


class CSun	// TODO LIGHT
{
public:
	CLight* cpLight_m;

	CSun();
	~CSun();
};


class CPlayer;


/*
 *	CWorldView
 */
class CWorldView:public CCamView
{
public:
	static CZoneView* cpZoneView_m;

	CWorldView(CPlayer* cpPlayer_p);
	~CWorldView();

	static void Update(CVector<T_3DVALUE>* cpPosition_p=0);
	static void Draw(T_BOOL bDebug_p);

private:
	enum EWorldViewGridSize
	{
		E_WORLDVIEW_CELLSIZE=16,
		E_WORLDVIEW_CELLSIZE2=E_WORLDVIEW_CELLSIZE*E_WORLDVIEW_CELLSIZE
	};
	static CCellView* cpCellView_m;
	static CSun* cpSun_m;
	static CPlayer* cpPlayer_m;

	static void DrawDebug(T_UWORD uwBloc_p);
}; /* CWorldView */


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif

