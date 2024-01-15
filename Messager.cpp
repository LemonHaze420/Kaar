#include "Messager.h"
#include "Player.h"
#include "Screen.h"


/*
 *	CMessager::Send
 */
void CMessager::Send(EMessagerMsg eMsg_p,void* cpParam_p)
{
	if(eMsg_p==E_MESSAGER_RENDERCLICK1)
	{
		CPChar* cpPChar=CPlayer::cpCurPChar_m;

		if(cpPChar!=0 && cpPChar->cpCharacter_m->wLife_m>0)
		{
			cpPChar->GetInTo((CPt<T_2DVALUE>*)(cpParam_p));
/*			CSndBuf* cpSnd=cpPChar->cpCharacter_m->cpOrder_m[rand()%4];
			if(cpSnd!=0)
				cpSnd->Play(CSound::cpCtrl_m);
*/		}
	}
	else if(eMsg_p==E_MESSAGER_RENDERCLICK2)
	{
		CPChar* cpPChar=CPlayer::cpCurPChar_m;

		if(cpPChar!=0 && cpPChar->cpCharacter_m->wLife_m>0)
		{
			cpPChar->MoveTo((CPt<T_2DVALUE>*)(cpParam_p));
/*			CSndBuf* cpSnd=cpPChar->cpCharacter_m->cpOrder_m[rand()%4];
			if(cpSnd!=0)
				cpSnd->Play(CSound::cpCtrl_m);
*/		}
	}

	else if(eMsg_p==E_MESSAGER_INTERFACECLICK1)
	{
		// onglet perso
		for(T_UWORD uw=0;uw<CPlayer::uwNbPChar_m;uw++)
		{
			CRectangle<T_2DVALUE> cRect;
			cRect.Set(4+uw*20,4,4+uw*20+19,(uw==0)?4+20:4+19);

			if(CScreen::CheckPtInRect((CPt<T_2DVALUE>*)(cpParam_p),&cRect))
			{
				CPlayer::SetActive(uw);
				return;
			}
		}
		// map
		if(CPlayer::cpCurPChar_m!=0)
		{
			CRectangle<T_2DVALUE> cRect;
			cRect.Set(26,CScreen::cInterfaceSize_m.tY-81,26+76,CScreen::cInterfaceSize_m.tY-9);

			CPt<T_2DVALUE> cPt=*((CPt<T_2DVALUE>*)(cpParam_p));
			if(CScreen::CheckPtInRect(&cPt,&cRect))
			{
/*				CSndBuf* cpSnd=CPlayer::cpCurCharacter_m->cpOrder_m[rand()%4];
				if(cpSnd!=0)
					cpSnd->Play(CSound::cpCtrl_m);
*/				T_ULONG ulX=cPt.tX-27.0f-38.0f;
				T_ULONG ulY=cPt.tY-CScreen::cInterfaceSize_m.tY+9.0f+36.0f;

				CPlayer::cpCurPChar_m->MoveTo(ulX*2/*D_MAPZOOM*/,ulY*2);
			}
		}
	}
} /* CMessager::Send */



