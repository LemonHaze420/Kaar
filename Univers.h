#ifndef _INCLUDE_UNIVERS_
#define _INCLUDE_UNIVERS_
/**************************************************************************************
 * 
 **************************************************************************************/
#include "System.h"
#include "Group.h"
#include "Zone.h"
#include "World.h"
#include "Model.h"
#include "Path.h"
#include "List.h"


/*
 *	CUnivers
 */
class CUnivers
{
public:
	enum EUniversNumberBlocView
	{
		E_UNIVERS_BLOCVIEWSIZE=3,
		E_UNIVERS_BLOCVIEWSIZE2=E_UNIVERS_BLOCVIEWSIZE*E_UNIVERS_BLOCVIEWSIZE
	};
	static CGroup* cpGroup_m;
	static T_UWORD uwNbGroup_m;
	static CZone* cpZone_m;
	static T_UWORD uwNbZone_m;
	static CWorld* cpWorld_m;
	static T_UWORD uwNbWorld_m;
	static CModel* cpModel_m;
	static T_UWORD uwNbModel_m;
	static CPath* cpPath_m;
	static T_UWORD uwNbPath_m;


	CUnivers() {}
	CUnivers(char* chpName_p);
	~CUnivers();

private:
	static const char chpDelimit_m[];
	CList<CGroup> cListGroup_m;
	CList<CZone> cListZone_m;
	CList<CWorld> cListWorld_m;
	CList<CModel> cListModel_m;
	CList<CPath> cListPath_m;

	void GetGroup(T_UWORD uwIndex_p);
	void GetBloc(CGroup* cpGroup_p,T_UWORD uwIndex_p);
	void GetLand(CGroup* cpGroup_p,T_UWORD uwIndex_p);
	void GetZone(T_UWORD uwIndex_p);
	void GetSet(CZone* cpZone_p,T_UWORD uwIndex_p);
	void GetModel(T_UWORD uwIndex_p);
	void GetPath(T_UWORD uwIndex_p);
	void GetWorld(T_UWORD uwIndex_p);
	void GetCharacter(CWorld* cpWorld_p,T_UWORD uwIndex_p);
	void InitCell();
}; /* CUnivers */


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif


