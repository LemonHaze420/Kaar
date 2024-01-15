#include "Cursor.h"
#include "Cursor.yh"
#include "Screen.h"
#include "Sound.h"
#include "Player.h"


CCursor::ECursorState CCursor::eAnim_m;


/*
 *	CCursor::CCursor
 */
CCursor::CCursor():
	tAnim_m(E_GFXANIMS_CURSOR_CURSOR_PAUSE),
	eSnd_m(E_CURSOR_NOSOUND),
	tFrame_m(0)
{
	eAnim_m=E_CURSOR_STATEANIM;
	// Charger cursor
	CSystem::cpFrame_m->CreateBmFrameObj(CSystem::cpFileCtx_m,CSystem::cp2d_m,"CURSOR",0,&cpCursor_m);

	CRectangle<T_MOUSEPTVALUE> cRect;
	cRect.Set(
		min(CScreen::cRenderPos_m.tX,CScreen::cInterfacePos_m.tX),0,
		min(CScreen::cRenderPos_m.tX,CScreen::cInterfacePos_m.tX)+CScreen::cRenderSize_m.tX+CScreen::cInterfaceSize_m.tX,CScreen::cRenderSize_m.tY);
	CSystem::cpMouse_m->SetClippingRegion(&cRect);
} /* CCursor::CCursor */


/*
 *	CCursor::~CCursor
 */
CCursor::~CCursor()
{
	DELETE cpCursor_m;
} /* CCursor::~CCursor */


/*
 *	CCursor::WaitNoClick
 */
void CCursor::WaitNoClick()
{
	eAnim_m=E_CURSOR_STATEWAITNOCLICK;
} /* CCursor::WaitNoClick */


/*
 *	CCursor::Update
 */
void CCursor::Update()
{
	CSystem::cpMouse_m->Refresh();
	CSystem::cpMouse_m->Read((CPt<T_MOUSEPTVALUE>*)(&cPosition_m),&tButton_m);

	CRectangle<T_2DVALUE> cMapRect;
	cMapRect.Set(CScreen::cInterfacePos_m.tX+26,CScreen::cInterfaceSize_m.tY-81,CScreen::cInterfacePos_m.tX+26+78,CScreen::cInterfaceSize_m.tY-81+76);
	CRectangle<T_2DVALUE> cInterfaceRect;
	cInterfaceRect.Set(CScreen::cInterfacePos_m.tX,0,CScreen::cInterfacePos_m.tX+CScreen::cInterfaceSize_m.tX,CScreen::cInterfaceSize_m.tY);
	CRectangle<T_2DVALUE> cRenderRect;
	cRenderRect.Set(CScreen::cRenderPos_m.tX,0,CScreen::cRenderPos_m.tX+CScreen::cRenderSize_m.tX,CScreen::cRenderSize_m.tY);
//	CRectangle<T_2DVALUE> cLogoRect;
//	cLogoRect.Set(CScreen::cInterfacePos_m.tX+91,CScreen::cInterfaceSize_m.tY-40,CScreen::cInterfacePos_m.tX+CScreen::cInterfaceSize_m.tX,CScreen::cInterfaceSize_m.tY);

	switch(eAnim_m)
	{
	case E_CURSOR_STATEANIM:
		if(CScreen::CheckPtInRect(&cPosition_m,&cRenderRect))	// Ecran de rendu
		{
			if(tButton_m&CMouse::F_BUTS_BUTTON1)	// possession perso
			{
				StartAnim(E_GFXANIMS_CURSOR_CURSOR_CLICK);
				CPt<T_2DVALUE> cPt=cPosition_m-CScreen::cRenderPos_m;
				CSystem::cpMessager_m->Send(CMessager::E_MESSAGER_RENDERCLICK1,(void*)(&cPt));
			}
			else if(tButton_m&CMouse::F_BUTS_BUTTON2) 	// Gestion attack & déplacement
			{
				StartSound(E_CURSOR_SOUNDORDER);
				StartAnim(E_GFXANIMS_CURSOR_CURSOR_CLICK);
				CPt<T_2DVALUE> cPt=cPosition_m-CScreen::cRenderPos_m;
				CSystem::cpMessager_m->Send(CMessager::E_MESSAGER_RENDERCLICK2,(void*)(&cPt));
			}
			else
			{
				StartSound(E_CURSOR_NOSOUND);
				StartAnim(E_GFXANIMS_CURSOR_CURSOR_PAUSE);
			}
		}
		else	// Interface
		{
			if(CScreen::CheckPtInRect(&cPosition_m,&cMapRect))	// Map
			{
				if(tButton_m&CMouse::F_BUTS_BUTTON2)
				{
					StartSound(E_CURSOR_SOUNDORDER);
					StartAnim(E_GFXANIMS_CURSOR_CURSOR_CLICK);
					CPt<T_2DVALUE> cPt=cPosition_m-CScreen::cInterfacePos_m;
					CSystem::cpMessager_m->Send(CMessager::E_MESSAGER_INTERFACECLICK1,(void*)(&cPt));
				}
				else
				{
					StartSound(E_CURSOR_NOSOUND);
					StartAnim(E_GFXANIMS_CURSOR_CURSOR_PAUSE);
				}
			}
			else	// Onglet
			{
				StartSound(E_CURSOR_NOSOUND);
				if(CScreen::cRenderPos_m.tX<CScreen::cInterfacePos_m.tX)
					StartAnim(E_GFXANIMS_CURSOR_CURSOR_FLECHEG);
				else
					StartAnim(E_GFXANIMS_CURSOR_CURSOR_FLECHED);

				if(tButton_m&CMouse::F_BUTS_BUTTON1)
				{
					CPt<T_2DVALUE> cPt=cPosition_m-CScreen::cInterfacePos_m;
					CSystem::cpMessager_m->Send(CMessager::E_MESSAGER_INTERFACECLICK1,(void*)(&cPt));
				}
			}
		}
		break;
	case E_CURSOR_STATEWAITNOCLICK:
		StartSound(E_CURSOR_NOSOUND);
		if(!(tButton_m&CMouse::F_BUTS_BUTTON1) && !(tButton_m&CMouse::F_BUTS_BUTTON2))
			eAnim_m=E_CURSOR_STATEANIM;
		break;
	}
} /* CCursor::Update */


/*
 *	CCursor::StartAnim
 */
void CCursor::StartAnim(T_INDEX tAnim_p)
{
	if(tAnim_m==tAnim_p)
		return;
	tAnim_m=tAnim_p;
	tFrame_m=0;
	eAnim_m=E_CURSOR_STATEANIM;
} /* CCursor::StartAnim */


/*
 *	CCursor::StartSound
 */
void CCursor::StartSound(ECursorSound eSnd_p)
{
	if(eSnd_m==eSnd_p)
		return;
	eSnd_m=eSnd_p;

	CSndBuf* cpSnd;
	switch(eSnd_m)
	{
	case E_CURSOR_NOSOUND:
		cpSnd=0;
		break;
	case E_CURSOR_SOUNDCLICK:
		cpSnd=0;
		break;
	case E_CURSOR_SOUNDORDER:
		if(CPlayer::cpCurPChar_m!=0)
		{
			T_UWORD uwRand;
			do
			{
				uwRand=rand()%4;
			}
			while(uwRand==uwRand_m);
			uwRand_m=uwRand;

			cpSnd=CPlayer::cpCurCharacter_m->cpOrder_m[uwRand_m];
		}
		else
			cpSnd=0;

		break;
	}
	
	if(cpSnd!=0)
		cpSnd->Play(CSound::cpCtrl_m);
} /* CCursor::StartSound */


/*
 *	CCursor::UpdateFrame
 */
void CCursor::UpdateFrame()
{
	T_INDEX tNbFrame;
	cpCursor_m->GetAnimNbFrames(E_GFXOBJS_CURSOR_CURSOR,tAnim_m,&tNbFrame);
	tFrame_m++;
	if(tFrame_m>=tNbFrame)
		tFrame_m=0;
} /* CCursor::UpdateFrame */


/*
 *	CCursor::Draw
 */
void CCursor::Draw()
{
	CSystem::cpPrim_m->SetSrcBlitMode(CBmap::F_SRCBLIT_COLORKEY);
	cpCursor_m->Display(CSystem::cpPrim_m,E_GFXOBJS_CURSOR_CURSOR,tAnim_m,tFrame_m,(CPt<T_MOUSEPTVALUE>*)(&cPosition_m));
	UpdateFrame();
} /* CCursor::Draw */


