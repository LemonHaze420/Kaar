#include "IntChar.h"
#include "Interface.h"
#include "Player.h"
#include "Screen.h"


/*
 *	CIntChar::CIntChar
 */
CIntChar::CIntChar():
	uwMovieAnim_m(0)
{
	// Charger Jauge
	CSystem::cpFrame_m->CreateBmFrameObj(CSystem::cpFileCtx_m,CSystem::cp2d_m,"JAUGE",0,&cpJauge_m);
} /* CIntChar::CIntChar */


/*
 *	CIntChar::~CIntChar
 */
CIntChar::~CIntChar()
{
	DELETE cpJauge_m;
} /* CIntChar::~CIntChar */


/*
 *	CIntChar::UpdateP
 */
void CIntChar::UpdateP()
{
	if(CPlayer::uwNbPChar_m!=0)
	{
		CBmFrameObj* cpIcon=CPlayer::cpCurCharacter_m->cpModelInst_m->cpModel_m->cpIcon_m;

		T_INDEX tFrame;
		cpIcon->GetFrameNum(0,0,tStartDate_m,CSystem::tTime_m,&tFrame);

		CPt<T_2DVALUE> cPt;
		cPt.Set(CScreen::cInterfacePos_m.tX+6+CPlayer::uwCurPChar_m*20,6+CInterface::uwScroll_m);
		CSystem::cpPrim_m->SetSrcBlitMode(CBmap::F_SRCBLIT_COLORKEY);
		cpIcon->Display(CSystem::cpPrim_m,0,0,tFrame,&cPt);

		CRectangle<T_2DVALUE> cRect;
		// vie perso
		if(CPlayer::cpCurCharacter_m->wLife_m>0)
		{
			T_WORD wMaxLife=CPlayer::cpCurCharacter_m->cpModelInst_m->cpModel_m->wLife_m;
			T_WORD wLife=96*CPlayer::cpCurCharacter_m->wLife_m/wMaxLife;
			cRect.Set(CScreen::cInterfacePos_m.tX+107,CInterface::uwScroll_m+27+96-wLife,CScreen::cInterfacePos_m.tX+112,CInterface::uwScroll_m+123);
			CSystem::cpPrim_m->SetSrcBlitMode(0);
			CSystem::cpPrim_m->Fill(&cRect,CInterface::uwLife_m);
		}
		CSystem::cpPrim_m->SetSrcBlitMode(CBmap::F_SRCBLIT_COLORKEY);
		cPt.Set(CScreen::cInterfacePos_m.tX+107,CInterface::uwScroll_m+26);
		cpJauge_m->Display(CSystem::cpPrim_m,0,0,0,&cPt);
		// fatigue perso
		if(CPlayer::cpCurCharacter_m->uwTireness_m!=0)
		{
			T_UWORD uwMaxTireness=CPlayer::cpCurCharacter_m->cpModelInst_m->cpModel_m->uwTireness_m;
			T_UWORD uwTireness=96*CPlayer::cpCurCharacter_m->uwTireness_m/uwMaxTireness;
			cRect.Set(CScreen::cInterfacePos_m.tX+115,CInterface::uwScroll_m+27+96-uwTireness,CScreen::cInterfacePos_m.tX+120,CInterface::uwScroll_m+123);
			CSystem::cpPrim_m->SetSrcBlitMode(0);
			CSystem::cpPrim_m->Fill(&cRect,CInterface::uwTireness_m);
		}
		CSystem::cpPrim_m->SetSrcBlitMode(CBmap::F_SRCBLIT_COLORKEY);
		cPt.Set(CScreen::cInterfacePos_m.tX+115,CInterface::uwScroll_m+26);
		cpJauge_m->Display(CSystem::cpPrim_m,0,0,1,&cPt);
	}
} /* CIntChar::UpdateP */


/*
 *	CIntChar::Update
 */
void CIntChar::Update(T_FLAGS tElmt_p)
{
	if(tElmt_p==E_INTCHAR_ALL)
	{
		uwMovieAnim_m=0;
		tStartDate_m=CSystem::tTime_m;
		tMovieStartDate_m=tStartDate_m;

		CRectangle<T_2DVALUE> cRect;
		// cadre perso 
		cRect.Set(4,24,123,140);
		CInterface::Bevel(&cRect,1,false);
		cRect.Set(6,26,105,125);
		CInterface::Bevel(&cRect,1,true);
		// cadre nom perso 
		cRect.Set(6,127,121,138);
		CInterface::Bevel(&cRect,1,true);

		// Name
		CPt<T_2DVALUE> cPt;
		cPt.Set(9,129);
		CInterface::cpBmap_m->SetSrcBlitMode(CBmap::F_SRCBLIT_COLORKEY);
		CSystem::cpFontObj_m->Display(CInterface::cpBmap_m,&cPt,CPlayer::cpCurCharacter_m->chpName_m);

		// onglet perso
		for(T_UWORD uw=0;uw<CPlayer::uwNbPChar_m;uw++)
		{
			cRect.Set(4+uw*20,4,4+uw*20+19,(uw==CPlayer::uwCurPChar_m)?4+20:4+19);
			if(CPlayer::uwNbPChar_m!=0)
				CInterface::Bevel(&cRect,1,(uw==CPlayer::uwCurPChar_m)?false:true);
			else
				CInterface::Bevel(&cRect,1,true);
		}

		for(uw=0;uw<CPlayer::uwNbPChar_m;uw++)
		{
			if(uw==CPlayer::uwCurPChar_m)
				continue;
			cPt.Set(6+uw*20,6);
			CBmFrameObj* cpIcon=CPlayer::cppPChar_m[uw]->cpCharacter_m->cpModelInst_m->cpModel_m->cpIcon_m;
			CInterface::cpBmap_m->SetSrcBlitMode(CBmap::F_SRCBLIT_COLORKEY);
			cpIcon->Display(CInterface::cpBmap_m,0,0,0,&cPt);
		}
	}
/*	if(tElmt_p&E_INTCHAR_LIFE)
	{
		// vie perso
		T_WORD wMaxLife=CPlayer::cpCurCharacter_m->cpModelInst_m->cpModel_m->wLife_m;
		T_WORD wLife=96*CPlayer::cpCurCharacter_m->wLife_m/wMaxLife;

		CRectangle<T_2DVALUE> cRect;
		cRect.Set(107,27+96-wLife,112,123);
		CInterface::cpBmap_m->SetSrcBlitMode(0);
		CInterface::cpBmap_m->Fill(&cRect,CInterface::uwLife_m);
		CInterface::cpBmap_m->SetSrcBlitMode(CBmap::F_SRCBLIT_COLORKEY);
		CPt<T_2DVALUE> cPt;
		cPt.Set(107,26);
		cpJauge_m->Display(CInterface::cpBmap_m,0,0,0,&cPt);
	}
	if(tElmt_p&E_INTCHAR_TIRENESS)
	{
		// fatigue perso
		T_UWORD uwMaxTireness=CPlayer::cpCurCharacter_m->cpModelInst_m->cpModel_m->uwTireness_m;
		T_UWORD uwTireness=96*CPlayer::cpCurCharacter_m->uwTireness_m/uwMaxTireness;

		CRectangle<T_2DVALUE> cRect;
		cRect.Set(115,27+96-uwTireness,120,123);
		CInterface::cpBmap_m->SetSrcBlitMode(0);
		CInterface::cpBmap_m->Fill(&cRect,CInterface::uwTireness_m);
		CInterface::cpBmap_m->SetSrcBlitMode(CBmap::F_SRCBLIT_COLORKEY);
		CPt<T_2DVALUE> cPt;
		cPt.Set(115,26);
		cpJauge_m->Display(CInterface::cpBmap_m,0,0,1,&cPt);
	}
*/	if(tElmt_p&E_INTCHAR_MOVIE)
	{
		CBmFrameObj* cpMovie=CPlayer::cpCurCharacter_m->cpModelInst_m->cpModel_m->cpMovie_m;
		T_DURATION tDuration;
		cpMovie->GetAnimDuration(0,uwMovieAnim_m,&tDuration);
		if(CSystem::tTime_m>tMovieStartDate_m+tDuration)
		{
			tMovieStartDate_m=CSystem::tTime_m;

			if(rand()%3)
				uwMovieAnim_m=0;
			else
			{
				T_UWORD uwMovieAnim;
				do
				{
					uwMovieAnim=rand()%4;
				}
				while(uwMovieAnim_m==uwMovieAnim);
				uwMovieAnim_m=uwMovieAnim;
			}
		}
		T_INDEX tFrame;
		cpMovie->GetFrameNum(0,uwMovieAnim_m,tMovieStartDate_m,CSystem::tTime_m,&tFrame);
		CPt<T_2DVALUE> cPt;
		cPt.Set(7,27);
		CInterface::cpBmap_m->SetSrcBlitMode(0);
		cpMovie->Display(CInterface::cpBmap_m,0,uwMovieAnim_m,tFrame,&cPt);
	}
} /* CIntChar::Update */

