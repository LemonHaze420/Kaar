#ifndef _INCLUDE_CHARACTER_
#define _INCLUDE_CHARACTER_
/**************************************************************************************
 *
 **************************************************************************************/
#include "System.h"
#include "Ref.h"
#include "ModelInst.h"
#include "CharPos.h"
#include "List.h"


class CCharPath
{
public:
	T_UWORD uwPath_m;
	
	CCharPath() {}
	CCharPath(T_UWORD uwPath_p):
		uwPath_m(uwPath_p)
	{
	}
};


/*
 *	CCharacter
 */
class CCharacter:public CRef
{
public:
	enum ECharacterType
	{
		E_CHARACTER_PC=0x01,	// Playable Character
		E_CHARACTER_AC=0x02,	// Associate Character
		E_CHARACTER_DC=0x04,	// Domptable Character
		E_CHARACTER_NPC=0x08	// Non Playable Character
	};
	T_UWORD uwModel_m;
	ECharacterType eType_m;

	char* chpName_m;
	T_WORD wLife_m;
	T_UWORD uwTireness_m;
	T_FLOAT fTireness_m;
	T_DATE tTireUpdate_m;

	CCharPos cCharPos_m;
	CPt<T_3DVALUE> cHome_m;
	CList<CCharPath> cListCharPath_m;
	T_UWORD uwNbCharPath_m;
	CCharPath* cpCharPath_m;

	CModelInst* cpModelInst_m;

	CCharPos cMissilePos_m;
	T_DATE tMissile_m;
	T_BOOL bMissile_m;
	T_BOOL bMissileEnd_m;
	T_BOOL bEnd_m;

//	CCharacter* cpAttackedBy_m;
	T_BOOL bDead_m;
	T_3DVALUE tSpeed_m;

	T_UWORD uwAnim_m;
	T_DATE tAnim_m;


	CSndBuf* cpAttack_m;
	CSndBuf* cpImpact_m;
	CSndBuf* cpDead_m;
	CSndBuf* cpOrder_m[4];

	CVector<T_3DVALUE> cCorner_m[4];

	
	CCharacter();
	CCharacter(T_UWORD uwModel_p,ECharacterType eType_p,char* chpName_p,
					T_UWORD uwWorld_p,
					T_UWORD uwXZone,T_UWORD uwYZone,
					T_UWORD uwXBloc,T_UWORD uwYBloc,
					T_UWORD uwXCell,T_UWORD uwYCell);

	~CCharacter();
	CCharacter& operator=(CCharacter& crCharacter_p);

	void Draw();
	T_BOOL Update();
	void SetSel(T_UWORD uwColor_p);
	void DrawSel();

private:
	T_UWORD uwSelSize_m;
	T_BOOL bUpdate_m;
	T_UWORD uwColor_m;
	T_UWORD uwShadow_m;

	T_3DVALUE Max(T_3DVALUE tA_p,T_3DVALUE tB_p) {return (tA_p>tB_p)?tA_p:tB_p;}
	T_3DVALUE Min(T_3DVALUE tA_p,T_3DVALUE tB_p) {return (tA_p<tB_p)?tA_p:tB_p;}

	// Virtual pure de CRef
	virtual void Init();
	virtual void Shut();
}; /* CCharacter */


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif

