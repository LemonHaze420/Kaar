#include "Interface.h"
#include "Player.h"
#include "WorldPos.h"
#include "Sound.h"


CPt<T_2DVALUE>* CInterface::cpSize_m;
CBmap* CInterface::cpBmap_m;

// Couleur interface
T_UWORD CInterface::uwRed_m;
T_UWORD CInterface::uwYellow_m;
T_UWORD CInterface::uwGreen_m;
T_UWORD CInterface::uwLife_m;
T_UWORD CInterface::uwTireness_m;
T_UWORD CInterface::uwSelected_m;
T_UWORD CInterface::uwPC_m;
T_UWORD CInterface::uwNPC_m;
// Mask
T_UWORD CInterface::uwDarkMsk_m;
T_UWORD CInterface::uwLightMsk_m;
// Position de scroll
T_UWORD CInterface::uwScroll_m;


#define RGB24TO16(r,g,b) ((unsigned short)( ((r<<8)&0xF800) + ((g<<3)&0x07E0) + ((b>>3)&0x001F) ))


/*
 *	CInterface::CInterface
 */
CInterface::CInterface(CPt<T_2DVALUE>* cpSize_p):
	uwNbPChar_m(-1),
	uwCurPChar_m(-1)
{
	cpSize_m=cpSize_p;
	uwScroll_m=cpSize_m->tY;

	// TODO 15 BITS
	// Init 16 bits
	uwDarkMsk_m=0xF7DE;
	uwLightMsk_m=0x7BEF;

	uwRed_m=0xF800;
	uwYellow_m=0xFFE0;
	uwGreen_m=0x7E0;

/*	uwLife_m=RGB24TO16(202,27,2);
	uwTireness_m=RGB24TO16(215,150,1);
*/
	uwLife_m=RGB24TO16(138,0,0);
	uwTireness_m=RGB24TO16(8,107,5);
	uwSelected_m=RGB24TO16(126,157,181);
	uwPC_m=RGB24TO16(247,178,46);
	uwNPC_m=RGB24TO16(201,146,221);


	// Charger fond
	CSystem::cpFrame_m->CreateBmFrameObj(CSystem::cpFileCtx_m,CSystem::cp2d_m,"TBR",0,&cpTexture_m);
	// Charger Logo
	CSystem::cpFrame_m->CreateBmFrameObj(CSystem::cpFileCtx_m,CSystem::cp2d_m,"LOGO",0,&cpLogo_m);
	// Charger Radar
	CSystem::cpFrame_m->CreateBmFrameObj(CSystem::cpFileCtx_m,CSystem::cp2d_m,"RADAR",0,&cpRadar_m);

	CSystem::cp2d_m->CreateBmap((CPt<T_2DVALUE>*)(cpSize_m),CBmap::F_CREATIONFLAGS_OFFSCREEN|CBmap::F_CREATIONFLAGS_16BITS,&cpBmap_m);

	Update();
	cpIntChar_m=NEW CIntChar;
} /* CInterface::CInterface */


/*
 *	CInterface::~CInterface
 */
CInterface::~CInterface()
{
	DELETE cpIntChar_m;
	DELETE cpLogo_m;
	DELETE cpRadar_m;
	DELETE cpBmap_m;
	DELETE cpTexture_m;
} /* CInterface::~CInterface */


/*
 *	CInterface::SetPos
 */
void CInterface::SetPos(CPt<T_2DVALUE>* cpPos_p)
{
	cpPos_m=cpPos_p;
} /* CInterface::SetPos */

/*
 *	CInterface::Update
 */
void CInterface::Update(T_FLAGS tElmt)
{
	if(tElmt&E_INTERFACE_ALL)
	{
		T_UWORD uwX;
		T_UWORD uwY;
		for(uwY=0;uwY<(cpSize_m->tY+63)/64;uwY++)
			for(uwX=0;uwX<(cpSize_m->tX+63)/64;uwX++)
			{
				CPt<T_2DVALUE> cPt(uwX*64,uwY*64);
				cpTexture_m->Display(cpBmap_m,0,0,(uwY+uwX)%4,&cPt);
			}

		void* pVoid;
		cpBmap_m->Lock(&pVoid);
		// cadre global
		CRectangle<T_2DVALUE> cRect;
		cRect.Set(0,0,127,cpSize_m->tY-1);
		Bevel(&cRect,2,true,pVoid);
/*		// onglet menu
		for(T_UWORD uw=0;uw<6;uw++)
		{
			cRect.Set(4+uw*20,143,4+uw*20+19,(uw==0)?143+20:143+19);
			Bevel(&cRect,1,(uw==0)?false:true,pVoid);
		}
*/		// cadre menu
		cRect.Set(4,163,123,295);
		Bevel(&cRect,1,false,pVoid);

		cpBmap_m->Unlock();
		CPt<T_2DVALUE> cPt;
		// Logo
		if(cpSize_m->tY>=600)
		{
			cPt.Set(2,296);
			cpBmap_m->SetSrcBlitMode(CBmap::F_SRCBLIT_COLORKEY);
			cpLogo_m->Display(cpBmap_m,0,0,0,&cPt);
		}
		if(cpSize_m->tY>=768)
		{
			cPt.Set(2,296+146);
			cpBmap_m->SetSrcBlitMode(CBmap::F_SRCBLIT_COLORKEY);
			cpLogo_m->Display(cpBmap_m,1,0,0,&cPt);
		}
		cPt.Set(7,173);
		cpBmap_m->SetSrcBlitMode(CBmap::F_SRCBLIT_COLORKEY);
		CSystem::cpFontObj_m->Display(cpBmap_m,&cPt,"KAAR DEMO\n\n(C) CHAMAN\n\n1998");
	}
} /* CInterface::Update */



/*
 *	CInterface::Draw
 */
void CInterface::Draw()
{
	if(CPlayer::uwNbPChar_m!=0)
	{
		if(uwNbPChar_m!=CPlayer::uwNbPChar_m || uwCurPChar_m!=CPlayer::uwCurPChar_m)
		{
			// Interface globale
			Update();
			// Personnage
			cpIntChar_m->Update();
		}
		else
			cpIntChar_m->Update(CIntChar::E_INTCHAR_MOVIE);

		// Map
		CPt<T_2DVALUE> cPt;
		cPt.Set(26,cpSize_m->tY-9-72);
		DrawMap(&cPt);
		cPt.Set(3,cpSize_m->tY-5-80);
		cpBmap_m->SetSrcBlitMode(CBmap::F_SRCBLIT_COLORKEY);
		cpRadar_m->Display(cpBmap_m,0,0,0,&cPt);
	}
	else
		Update();

	uwNbPChar_m=CPlayer::uwNbPChar_m;
	uwCurPChar_m=CPlayer::uwCurPChar_m;

	CPt<T_2DVALUE> cPt;
	cPt.Set(cpPos_m->tX,cpPos_m->tY);

	if(uwScroll_m==cpSize_m->tY)
		CSound::cpPannelRoll_m->Play(CSound::cpCtrl_m);
	if(uwScroll_m>0)
	{
		uwScroll_m-=16;
		if(uwScroll_m<=16)
			CSound::cpPannelLock_m->Play(CSound::cpCtrl_m);
	}

	cPt.tY+=uwScroll_m;
	CSystem::cpPrim_m->SetSrcBlitMode(0);
	CSystem::cpPrim_m->Blit(cpBmap_m,NULL,&cPt);
	
	if(uwScroll_m!=0)
	{
		CRectangle<T_2DVALUE> cRect;
		cRect.Set(cPt.tX,0,cPt.tX+127,cPt.tY-1);
		CSystem::cpPrim_m->Fill(&cRect,0);
	}

	if(CPlayer::uwNbPChar_m!=0)
		cpIntChar_m->UpdateP();
} /* CInterface::Draw */


/*
 *	CInterface::Bevel
 */
void CInterface::Bevel(CRectangle<T_2DVALUE>* cpRect_p,T_UWORD uwThickness_p,T_BOOL bUp_p,void* pScreen_p)
{
	HBevel(cpRect_p,uwThickness_p,bUp_p,pScreen_p);
	VBevel(cpRect_p,uwThickness_p,bUp_p,pScreen_p);
} /* CInterface::Bevel */


/*
 *	CInterface::HBevel
 */
void CInterface::HBevel(CRectangle<T_2DVALUE>* cpRect_p,T_UWORD uwThickness_p,T_BOOL bUp_p,void* pScreen_p)
{
	void* pVoid;
	if(pScreen_p==0)
		cpBmap_m->Lock(&pVoid);
	else
		pVoid=pScreen_p;

	T_UWORD uwWidth=cpRect_p->tX2-cpRect_p->tX1+1;

	T_UWORD uwLineLen=cpSize_m->tX;
	T_UWORD* uwpLightScreen=(T_UWORD*)(pVoid)+uwLineLen*cpRect_p->tY1+cpRect_p->tX1;
	T_UWORD* uwpDarkScreen=(T_UWORD*)(pVoid)+uwLineLen*cpRect_p->tY2+cpRect_p->tX2;

	T_UWORD uwBevel=1;
	if(bUp_p)
	{
		for(T_UWORD uwY=0;uwY<uwThickness_p;uwY++)
		{
			for(T_UWORD uwX=0;uwX<uwWidth-uwBevel;uwX++,uwpLightScreen++,uwpDarkScreen--)
			{
				*uwpLightScreen=(*uwpLightScreen&uwLightMsk_m)<<1;
				*uwpDarkScreen=(*uwpDarkScreen&uwDarkMsk_m)>>1;
			}
			uwpLightScreen+=uwBevel+uwLineLen-uwWidth+1;
			uwpDarkScreen-=uwBevel+uwLineLen-uwWidth+1;
			uwBevel+=2;
		}
	}
	else
	{
		for(T_UWORD uwY=0;uwY<uwThickness_p;uwY++)
		{
			for(T_UWORD uwX=0;uwX<uwWidth-uwBevel;uwX++,uwpLightScreen++,uwpDarkScreen--)
			{
				*uwpLightScreen=(*uwpLightScreen&uwDarkMsk_m)>>1;
				*uwpDarkScreen=(*uwpDarkScreen&uwLightMsk_m)<<1;
			}
			uwpLightScreen+=uwBevel+uwLineLen-uwWidth+1;
			uwpDarkScreen-=uwBevel+uwLineLen-uwWidth+1;
			uwBevel+=2;
		}
	}
	if(pScreen_p==0)
		cpBmap_m->Unlock();
} /* CInterface::HBevel */


/*
 *	CInterface::VBevel
 */
void CInterface::VBevel(CRectangle<T_2DVALUE>* cpRect_p,T_UWORD uwThickness_p,T_BOOL bUp_p,void* pScreen_p)
{
	void* pVoid;
	if(pScreen_p==0)
		cpBmap_m->Lock(&pVoid);
	else
		pVoid=pScreen_p;

	T_UWORD uwHeight=cpRect_p->tY2-cpRect_p->tY1+1;
	T_UWORD uwLineLen=cpSize_m->tX;

	T_UWORD uwBevel=1;
	if(bUp_p)
	{
		for(T_UWORD uwX=0;uwX<uwThickness_p;uwX++)
		{
			T_UWORD* uwpLightScreen=(T_UWORD*)(pVoid)+uwLineLen*(1+cpRect_p->tY1)+cpRect_p->tX1+uwX+uwX*uwLineLen;
			T_UWORD* uwpDarkScreen=(T_UWORD*)(pVoid)+uwLineLen*(1+cpRect_p->tY1)+cpRect_p->tX2-uwX+uwX*uwLineLen;
			for(T_UWORD uwY=0;uwY<uwHeight-uwBevel-1;uwY++,uwpLightScreen+=uwLineLen,uwpDarkScreen+=uwLineLen)
			{
				*uwpLightScreen=(*uwpLightScreen&uwLightMsk_m)<<1;
				*uwpDarkScreen=(*uwpDarkScreen&uwDarkMsk_m)>>1;
			}
			uwBevel+=2;
		}
	}
	else
	{
		for(T_UWORD uwX=0;uwX<uwThickness_p;uwX++)
		{
			T_UWORD* uwpLightScreen=(T_UWORD*)(pVoid)+uwLineLen*(1+cpRect_p->tY1)+cpRect_p->tX1+uwX+uwX*uwLineLen;
			T_UWORD* uwpDarkScreen=(T_UWORD*)(pVoid)+uwLineLen*(1+cpRect_p->tY1)+cpRect_p->tX2-uwX+uwX*uwLineLen;
			for(T_UWORD uwY=0;uwY<uwHeight-uwBevel-1;uwY++,uwpLightScreen+=uwLineLen,uwpDarkScreen+=uwLineLen)
			{
				*uwpLightScreen=(*uwpLightScreen&uwDarkMsk_m)>>1;
				*uwpDarkScreen=(*uwpDarkScreen&uwLightMsk_m)<<1;
			}
			uwBevel+=2;
		}
	}
	if(pScreen_p==0)
		cpBmap_m->Unlock();
} /* CInterface::VBevel */


/*
 *	CInterface::StateBar
 *
void CInterface::StateBar(CPt<T_2DVALUE>* cpPt_p,T_UWORD uwLife_p,T_UWORD uwTireness_p,void* pScreen_p)
{
	CRectangle<T_2DVALUE> cRect;

	cRect.Set(cpPt_p->tX,cpPt_p->tY+42-uwLife_p,cpPt_p->tX+3,cpPt_p->tY+42);
	cpBmap_m->Fill(&cRect,uwRed_m);

	cRect.Set(cpPt_p->tX+6,cpPt_p->tY+42-uwTireness_p,cpPt_p->tX+9,cpPt_p->tY+42);
	cpBmap_m->Fill(&cRect,uwYellow_m);
} /* CInterface::StateBar */

/*
 *	CInterface::DrawMap
 */
void CInterface::DrawMap(CPt<T_2DVALUE>* cpPt_p,void* pScreen_p)
{
	CCharacter* cpCharacter=CPlayer::cpCurCharacter_m;
	if(cpCharacter==0)
		return;
	CVector<T_3DVALUE>* cpPosition=&cpCharacter->cCharPos_m.cPosition_m;
	T_UWORD uwWorld=cpCharacter->cCharPos_m.uwWorld_m;

	void* pVoid;
	if(pScreen_p==0)
		cpBmap_m->Lock(&pVoid);
	else
		pVoid=pScreen_p;

	T_UWORD* uwpScreen=(T_UWORD*)(pVoid)+128*cpPt_p->tY+cpPt_p->tX;

	for(T_UWORD uwY=0;uwY<72;uwY++)
		for(T_UWORD uwX=0;uwX<76;uwX++)
		{
			CWorldPos cWorldPos(uwWorld,cpPosition->tX+(uwX-38)*16*2/*D_MAPZOOM*/,cpPosition->tZ-(uwY-36)*16*2);
			T_UWORD uwAltitude=(384+cWorldPos.GetAltitude()-cpPosition->tY+100)/(3*4);
			uwAltitude=
				((uwAltitude<<10)&0xF800)|
				((uwAltitude<<5)&0x07E0)|
				((uwAltitude>>1)&0x001F);
			uwpScreen[uwY*128+uwX]=uwAltitude;

		}

	CWorld* cpWorld=CPlayer::cpCurWorld_m;
	for(CCharacter* cp=cpWorld->cListCharacter_m.FindFirst();cp!=0;cp=cpWorld->cListCharacter_m.FindNext())
	{
		if(cp->bDead_m || cp->wLife_m<=0)
			continue;
		CVector<T_3DVALUE>* cpPosOther=&cp->cCharPos_m.cPosition_m;
		if(cpPosOther->tX>cpPosition->tX-(38*16*2) && cpPosOther->tX<cpPosition->tX+(38*16*2) &&
			cpPosOther->tZ<cpPosition->tZ+(36*16*2) && cpPosOther->tZ>cpPosition->tZ-(36*16*2))
		{
			T_UWORD uwX=(cpPosOther->tX-cpPosition->tX)/(16*2)+38;
			T_UWORD uwY=-(cpPosOther->tZ-cpPosition->tZ)/(16*2)+36;
			if(cp->eType_m==CCharacter::E_CHARACTER_NPC)
			{
				uwpScreen[(uwY-1)*128+uwX]=uwNPC_m;
				uwpScreen[(uwY+1)*128+uwX]=uwNPC_m;
				uwpScreen[uwY*128+uwX]=0;
				uwpScreen[uwY*128+uwX-1]=uwNPC_m;
				uwpScreen[uwY*128+uwX+1]=uwNPC_m;
			}
			else
			{
				uwpScreen[(uwY-1)*128+uwX]=uwPC_m;
				uwpScreen[(uwY+1)*128+uwX]=uwPC_m;
				uwpScreen[uwY*128+uwX]=0;
				uwpScreen[uwY*128+uwX-1]=uwPC_m;
				uwpScreen[uwY*128+uwX+1]=uwPC_m;
			}
		}
	}

	if(pScreen_p==0)
		cpBmap_m->Unlock();
} /* CInterface::DrawMap */





