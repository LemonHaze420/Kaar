#include "Kaar.h"
#include "MyEvMgr.h"
#include "Messager.h"
#include "Player.h"
#include "Sound.h"


#define D_KAARX 1024
#define D_KAARY 768

/*
#define D_KAARX 512
#define D_KAARY 384
#define D_KAARX 800
#define D_KAARY 600



*/

CScreen* CKaar::cpScreen_m;
CGame* CKaar::cpGame_m;

/**************************************************************************************
 * Virtual pure
 **************************************************************************************/
CRootApp* gAppEntryPoint(T_LONG *lpMaxMen,CStdStr *cpErrorText)
{
	return NEW CKaar;
} 
/**************************************************************************************
 * End virtual
 **************************************************************************************/


/*
 *	CKaar
 */
CKaar::CKaar():
	CApp("Kaar")
{
	SetFatalize(E_FATALIZEMODE_FATALIZEALLERRORS);
	CSystem::cpFileCtx_m=cpFiCtx;
	GetWin(&cpWin_m);
	try
	{
		cpDrvMgr_m=NEW CDrvMgr();
	}
	catch(char* chpMessage)
	{
		MessageBox(NULL,chpMessage,"Error Manager tempo",MB_OK);
		exit(1);
	}
	CSystem::cpFileCtx_m->SetPath("Datas");
	CSystem::cpTimerObj_m->Start();
	try
	{
		cpScreen_m=NEW CScreen(D_KAARX,D_KAARY,CScreen::E_SCREEN_TYPELEFT);
	}
	catch(char* chpMessage)
	{
		DELETE cpDrvMgr_m;
		MessageBox(NULL,chpMessage,"Error Manager tempo",MB_OK);
		exit(1);
	}
	try
	{
		cpGame_m=NEW CGame;
	}
	catch(char* chpMessage)
	{
		DELETE cpScreen_m;
		DELETE cpDrvMgr_m;
		MessageBox(NULL,chpMessage,"Error Manager tempo",MB_OK);
		exit(1);
	}
	cpSFX_m=NEW CSFX;
	cpSound_m=NEW CSound;
} /* CKaar */


/*
 *	~CKaar
 */
CKaar::~CKaar()
{
	static T_BOOL bDebug=false;

	if(bDebug)
		return;
	bDebug=true;

	DELETE cpSound_m;
	DELETE cpSFX_m;
	CSystem::cpTimerObj_m->Stop();
	DELETE cpGame_m;
	DELETE cpScreen_m;
	DELETE cpDrvMgr_m;
} /* ~CKaar */


/*
 *	Run
 */
T_RESULT CKaar::Run(ERetType *epError_p)
{
	CMyEvMgr cMyEvMgr;
	cpWin_m->SetWinEventMgr(&cMyEvMgr);

	float fX=0.0f;
	float fY=0.0f;
	float fH=0.0f;

	for(;;)
	{
		cpWin_m->ManageEvents();
		if(!cMyEvMgr.boFocus_m)
			continue;

		CSystem::cpKbd_m->Refresh();
		CSystem::cpTimerObj_m->Read(&CSystem::tTime_m);

		CKbd::EKeyState eKey;
		CSystem::cpKbd_m->GetKeyState(CKbd::E_KEYS_ESC,&eKey);
		if(eKey==CKbd::E_KEYSTATE_PRESSED)
			break;

		CSystem::cpKbd_m->GetKeyState(CKbd::E_KEYS_TAB,&eKey);
		if(eKey==CKbd::E_KEYSTATE_PRESSED)
		{
			static T_BOOL bInterface=true;
			if(bInterface)
				cpScreen_m->Update(D_KAARX,D_KAARY,CScreen::E_SCREEN_TYPERIGHT);
			else
				cpScreen_m->Update(D_KAARX,D_KAARY,CScreen::E_SCREEN_TYPELEFT);
			bInterface^=1;
		}

		static T_BOOL bFirst=true;
		CSystem::cpKbd_m->GetKeyState(CKbd::E_KEYS_ENTER,&eKey);
		if(eKey==CKbd::E_KEYSTATE_PRESSED)
		{
			CSound::cpNewGame_m->Play(CSound::cpCtrl_m);
			if(bFirst)
			{
				CScreen::Print("Starting demo, Loading world...");
				cpScreen_m->Flip();
				cpGame_m->Start();
				bFirst=false;
			}
			else
			{
				CScreen::Print("Restarting demo, Loading world...");
				cpScreen_m->Flip();
				cpGame_m->ReStart();
			}
		}

		CSystem::cpKbd_m->GetKeyState(CKbd::E_KEYS_1,&eKey);
		if(eKey==CKbd::E_KEYSTATE_PRESSED)
			CPlayer::SetActive(0);
		CSystem::cpKbd_m->GetKeyState(CKbd::E_KEYS_2,&eKey);
		if(eKey==CKbd::E_KEYSTATE_PRESSED)
			CPlayer::SetActive(1);
		CSystem::cpKbd_m->GetKeyState(CKbd::E_KEYS_3,&eKey);
		if(eKey==CKbd::E_KEYSTATE_PRESSED)
			CPlayer::SetActive(2);
		CSystem::cpKbd_m->GetKeyState(CKbd::E_KEYS_4,&eKey);
		if(eKey==CKbd::E_KEYSTATE_PRESSED)
			CPlayer::SetActive(3);
		CSystem::cpKbd_m->GetKeyState(CKbd::E_KEYS_5,&eKey);
		if(eKey==CKbd::E_KEYSTATE_PRESSED)
			CPlayer::SetActive(4);
		CSystem::cpKbd_m->GetKeyState(CKbd::E_KEYS_6,&eKey);
		if(eKey==CKbd::E_KEYSTATE_PRESSED)
			CPlayer::SetActive(5);

		cpGame_m->Update();

		CSystem::cpKbd_m->GetKeyState(CKbd::E_KEYS_FB,&eKey);
		if(eKey==CKbd::E_KEYSTATE_PRESSED)
			cpGame_m->Draw(true);
		else
			cpGame_m->Draw();

		CSystem::cpKbd_m->GetKeyState(CKbd::E_KEYS_FC,&eKey);
		if(eKey==CKbd::E_KEYSTATE_PRESSED)
			cpScreen_m->Flip(true);
		else
			cpScreen_m->Flip();

		CSystem::cpKbd_m->GetKeyState(CKbd::E_KEYS_F1,&eKey);
		if(eKey==CKbd::E_KEYSTATE_PRESSED)
		{
			CSFX::bShadow_m^=1;
			if(CSFX::bShadow_m)
				CScreen::Print("Shadow on");
			else
				CScreen::Print("Shadow off");
		}

		CSystem::cpKbd_m->GetKeyState(CKbd::E_KEYS_F2,&eKey);
		if(eKey==CKbd::E_KEYSTATE_PRESSED)
		{
			CSystem::cp2dSnd_m->SetVolume(0.0f);
			CScreen::Print("Volume 0");
		}

		CSystem::cpKbd_m->GetKeyState(CKbd::E_KEYS_F3,&eKey);
		if(eKey==CKbd::E_KEYSTATE_PRESSED)
		{
			CSystem::cp2dSnd_m->SetVolume(0.85f);
			CScreen::Print("Volume 50%");
		}

		CSystem::cpKbd_m->GetKeyState(CKbd::E_KEYS_F4,&eKey);
		if(eKey==CKbd::E_KEYSTATE_PRESSED)
		{
			CSystem::cp2dSnd_m->SetVolume(1.0f);
			CScreen::Print("Volume 100%");
		}

		CSystem::cpKbd_m->GetKeyState(CKbd::E_KEYS_F5,&eKey);
		if(eKey==CKbd::E_KEYSTATE_PRESSED)
		{
			CSFX::bBlood_m^=1;
			if(CSFX::bBlood_m)
				CScreen::Print("Blood on");
			else
				CScreen::Print("Blood off");
		}
	}
	return E_SUCCEED;
} /* Run */


/*			fX=0.0f;
			fY=0.0f;
			fH=0.0f;
		cpGame_m->cpCharacter_m->cCam_m.SetRot(fX,fY);
		cpGame_m->cpCharacter_m->cCam_m.SetPos(fH);
*/

























