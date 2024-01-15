#include "Screen.h"
#include "Game.h"


#define D_SCREEN_INTERFACEWIDTH 128


CPt<T_2DVALUE> CScreen::cSize_m;
CPt<T_2DVALUE> CScreen::cRenderSize_m;
CPt<T_2DVALUE> CScreen::cRenderPos_m;
CPt<T_2DVALUE> CScreen::cInterfaceSize_m;
CPt<T_2DVALUE> CScreen::cInterfacePos_m;
T_LONG CScreen::lNbPrim_m;
CInterface* CScreen::cpInterface_m;
CCursor* CScreen::cpCursor_m;
T_UWORD CScreen::uwBorder_m;
char CScreen::chpText_m[81];
T_DATE CScreen::tDateText_m=0;


/*
 *	CScreen::CScreen
 */
CScreen::CScreen(T_UWORD uwXSize_p,T_UWORD uwYSize_p,EScreenType eType_p):
	cpRender_m(0)
{
	cpInterface_m=0;
	cpCursor_m=0;
	uwBorder_m=0;
	cSize_m.Set(0,0);
	Update(uwXSize_p,uwYSize_p,eType_p);
} /* CScreen::CScreen */


/*
 *	CScreen::~CScreen
 */
CScreen::~CScreen()
{
	DELETE cpFontFrame_m;
	DELETE CSystem::cpFontObj_m;

	DELETE cpInterface_m;
	DELETE cpRender_m;
	DELETE cpCursor_m;

	DELETE CSystem::cpPrim_m;
	CSystem::cp2d_m->RestoreFullScreen();
	DELETE CSystem::cp2d_m;		
} /* CScreen::~CScreen */


/*
 *	CScreen::Update
 */
void CScreen::Update(T_UWORD uwXSize_p,T_UWORD uwYSize_p,EScreenType eType_p)
{
	T_BOOL bSize=false;
	// Taille change
	if(cSize_m.tX!=uwXSize_p || cSize_m.tY!=uwYSize_p)
	{
		cSize_m.Set(uwXSize_p,uwYSize_p);
		// Création screen
		if(CSystem::cp2d_m!=0)
		{
			DELETE CSystem::cpPrim_m;
			DELETE CSystem::cp2d_m;		
		}
		CSystem::cpGfx_m->Create2dObj(&CSystem::cp2d_m);

		T_WORD wNum;
		CSystem::cp2d_m->GetNbDevice(&wNum);
		if(wNum==1)
			CSystem::cp2d_m->SelectDevice(0,C2d::F_DEVFLAGS_3D+C2d::F_DEVFLAGS_3DHARD);	// NO3DFX
		else
			CSystem::cp2d_m->SelectDevice(1,C2d::F_DEVFLAGS_3D+C2d::F_DEVFLAGS_3DHARD);	// 3DFX

		CSystem::cp2d_m->SetFullScreen((CPt<T_2DVALUE>*)(&cSize_m),C2d::E_DEPTH_16BITS);

		CSystem::cp2d_m->CreateBmap((CPt<T_2DVALUE>*)(&cSize_m),
			CBmap::F_CREATIONFLAGS_16BITS|
			CBmap::F_CREATIONFLAGS_PRIMARY|
			CBmap::F_CREATIONFLAGS_3DRENDER|
			CBmap::F_CREATIONFLAGS_SWAP2|
			CBmap::F_CREATIONFLAGS_ZBUF16BITS
			,&CSystem::cpPrim_m);

		// Création Render, Interface & Cursor
		cRenderSize_m.Set(uwYSize_p,uwYSize_p);
		cInterfaceSize_m.Set(D_SCREEN_INTERFACEWIDTH,uwYSize_p);

		if(cpRender_m!=0)
			DELETE cpRender_m;
		cpRender_m=NEW CRender(&cRenderSize_m);

		if(CSystem::cpFontObj_m!=0)
			DELETE CSystem::cpFontObj_m;
		if(CSystem::cpFontObj_m==0)
			CreateFont();

		if(cpInterface_m!=0)
			DELETE cpInterface_m;
		cpInterface_m=NEW CInterface(&cInterfaceSize_m);

		bSize=true;
	}
	if(bSize || eType_m!=eType_p)
	{
		uwBorder_m=(uwXSize_p-uwYSize_p-D_SCREEN_INTERFACEWIDTH)/2;
		// Pos change
		eType_m=eType_p;
		switch(eType_m)
		{
		case E_SCREEN_TYPELEFT:
			cRenderPos_m.Set(uwBorder_m,0);
			cInterfacePos_m.Set(uwYSize_p+uwBorder_m,0);
			break;
		default:
		case E_SCREEN_TYPERIGHT:
			cRenderPos_m.Set(D_SCREEN_INTERFACEWIDTH+uwBorder_m,0);
			cInterfacePos_m.Set(uwBorder_m,0);
			break;
		}
		cpRender_m->SetPos(&cRenderPos_m);
		cpInterface_m->SetPos(&cInterfacePos_m);

		CRectangle<T_2DVALUE> cRect;
		cRect.Set(uwBorder_m,0,uwBorder_m+cRenderSize_m.tX+cInterfaceSize_m.tX-1,uwYSize_p-1);
		CSystem::cpPrim_m->SetClipRect(&cRect);
		CSystem::cpPrim_m->SetDstBlitMode(CBmap::F_DSTBLIT_USECLIPRECT);

		if(cpCursor_m!=0)
			DELETE cpCursor_m;
		cpCursor_m=NEW CCursor();
	}
} /* CScreen::Update */


/*
 *	CScreen::BeginRendering
 */
void CScreen::BeginRendering()
{
	CSystem::cpCtx_m->BeginRendering();
} /* CScreen::BeginRendering */


/*
 *	CScreen::EndRendering
 */
void CScreen::EndRendering()
{
	CSystem::cpCtx_m->Draw(&lNbPrim_m);

	static int Cpt;
	if((Cpt%125)==0)
	{
		T_SIZE tTotalSize;
		T_SIZE tFreeSize;
		CSystem::cp2d_m->GetCurDeviceMemInfo(&tTotalSize,&tFreeSize);
		char chpTxt[256];
		sprintf(chpTxt,"\nNb pages: %d/%d",(tTotalSize-tFreeSize)/65536,tTotalSize/65536);
		OutputDebugString(chpTxt);
		sprintf(chpTxt,"\nNb faces: %d\n",lNbPrim_m);
		OutputDebugString(chpTxt);

		CVector<T_3DVALUE>* cpPosition=&CPlayer::cpWorldView_m->cpCam_m->cTarget_m;
		sprintf(chpTxt,"Position: X:%d Y:%d Alt:%d\n",T_WORD(cpPosition->tX),T_WORD(-cpPosition->tZ),T_WORD(cpPosition->tY));
		OutputDebugString(chpTxt);
		if(CPlayer::uwNbPChar_m!=0 && CPlayer::cpCurWorld_m->InRange(cpPosition->tX,cpPosition->tZ))
		{
			CZoneInst* cpZoneInst=CPlayer::cpCurWorld_m->GetZoneInst(cpPosition->tX,cpPosition->tZ);
			T_UWORD uwXZone=CPlayer::cpCurWorld_m->GetXZone(cpPosition->tX);
			T_UWORD uwYZone=CPlayer::cpCurWorld_m->GetYZone(cpPosition->tZ);
			T_UWORD uwXBloc=cpZoneInst->GetXBloc(cpPosition->tX);
			T_UWORD uwYBloc=cpZoneInst->GetYBloc(cpPosition->tZ);
			char* chpBloc=cpZoneInst->cpBlocInst_m[cpZoneInst->GetBlocIndex(uwXBloc,uwYBloc)].cpBloc_m->chpMeshName_m;

			sprintf(chpTxt,"Zone: %d %d\nBloc: %d %d %s\n",uwXZone,uwYZone,uwXBloc,uwYBloc,chpBloc);
			OutputDebugString(chpTxt);
		}
	}
	Cpt++;

	CSystem::cpCtx_m->EndRendering();
} /* CScreen::EndRendering */


/*
 *	CScreen::Flip
 */
void CScreen::Flip(T_BOOL bDebug_p)
{
	if(tDateText_m>CSystem::tTime_m)
		CSystem::cpFontObj_m->Display(CSystem::cpPrim_m,&cRenderPos_m,chpText_m);

	// Gestion Interface
	cpInterface_m->Draw();

	// Gestion Cursor
	cpCursor_m->Update();
	cpCursor_m->Draw();

	// Efface si ya du bord
	if(uwBorder_m!=0)
	{
		CRectangle<T_2DVALUE> cRect;
		cRect.Set(0,0,uwBorder_m-1,cSize_m.tY-1);
		CSystem::cpPrim_m->Fill(&cRect,0);

		cRect.Set(cSize_m.tX-uwBorder_m,0,cSize_m.tX-1,cSize_m.tY-1);
		CSystem::cpPrim_m->Fill(&cRect,0);
	}
	// Info Debug
	if(bDebug_p)
	{
		T_SIZE tTotalSize;
		T_SIZE tFreeSize;
		CSystem::cp2d_m->GetCurDeviceMemInfo(&tTotalSize,&tFreeSize);
		char chpTxt[256];
		sprintf(chpTxt,"\nNb pages: %d/%d\n\nNb faces: %d",(tTotalSize-tFreeSize)/65536,tTotalSize/65536,lNbPrim_m);

		CPt<T_2DVALUE> cPt;
		cPt.Set(0,0);
		CSystem::cpPrim_m->SetSrcBlitMode(CBmap::F_SRCBLIT_COLORKEY);
		CSystem::cpFontObj_m->Display(CSystem::cpPrim_m,&cPt,chpTxt);

		
		sprintf(chpTxt,"\n\n",lNbPrim_m);
		OutputDebugString(chpTxt);
	}
	// Flip
	CSystem::cpPrim_m->Flip();
} /* CScreen::Flip */


/*
 *	CScreen::CreateFont
 */
void CScreen::CreateFont()
{
	// Créer fonte
	CSystem::cpFrame_m->CreateBmFrameObj(CSystem::cpFileCtx_m,CSystem::cp2d_m,"FONT",0,&cpFontFrame_m);
	CSystem::cpBmFnt_m->CreateBmFntObj(&CSystem::cpFontObj_m);

	CBmFntProp cProp;
	cProp.tToSet_m=CBmFntProp::F_TOSET_ALL;
	cProp.cpBmFrameObj_m=cpFontFrame_m;
	cProp.tBmFrameObjObjNum_m=0;
	cProp.tBmFrameObjAnimNum_m=0;
	cProp.bFirstChar_m=32;
	cProp.tSpacing_m=1;
	cProp.tDisFlags_m=CBmFntObj::F_DISFLAGS_UPPER|CBmFntObj::F_DISFLAGS_MANAGELINEFEED;
	cProp.tLineHeightChar_m=65;
	CSystem::cpFontObj_m->SetProp(&cProp);
} /* CScreen::CreateFont */


/*
 *	CScreen::CheckPtInRect
 */
bool CScreen::CheckPtInRect(CPt<T_2DVALUE>* cpPt_p,CRectangle<T_2DVALUE>* cpRect_p)
{
	if(cpPt_p->tX>=cpRect_p->tX1 && cpPt_p->tX<=cpRect_p->tX2 &&
		cpPt_p->tY>=cpRect_p->tY1 && cpPt_p->tY<=cpRect_p->tY2)
		return true;
	return false;
} /* CScreen::CheckPtInRect */


/*
 *	CScreen::Print
 */
void CScreen::Print(char* chpText_p)
{
	strncpy(chpText_m,chpText_p,80);
	chpText_m[80]=0;
	tDateText_m=CSystem::tTime_m+4000;
} /* CScreen::Print */
