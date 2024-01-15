#ifndef _INCLUDE_CURSOR_
#define _INCLUDE_CURSOR_
/**************************************************************************************
 * 
 **************************************************************************************/
#include "System.h"
#include "Character.h"


/*
 *	CCursor
 */
class CCursor
{
public:
	CPt<T_2DVALUE> cPosition_m;
	T_FLAGS tButton_m;

	CCursor();
	~CCursor();
	
	void Update();
	void Draw();
	static void WaitNoClick();

private:
	enum ECursorState
	{
		E_CURSOR_STATEANIM,
		E_CURSOR_STATEWAITNOCLICK
	};
	enum ECursorSound
	{
		E_CURSOR_NOSOUND,
		E_CURSOR_SOUNDCLICK,
		E_CURSOR_SOUNDORDER
	};
	CBmFrameObj* cpCursor_m;
	T_INDEX tAnim_m;
	T_INDEX tFrame_m;
	ECursorSound eSnd_m;
	T_UWORD uwRand_m;

	static ECursorState eAnim_m;

	void StartAnim(T_INDEX tAnim_p);
	void StartSound(ECursorSound eSnd_p);
	void UpdateFrame();

}; /* CCursor */


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif

