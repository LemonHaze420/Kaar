#include "Game.h"
#include "Screen.h"
#include "SFX.h"


CPlayer* CGame::cpPlayer_m;


/*
 *	CGame::CGame
 */
CGame::CGame()
{
	cpPlayer_m=NEW CPlayer("univers.txt");
	CSystem::cpMessager_m=NEW CMessager;
} /* CGame::CGame */


/*
 *	CGame::~CGame
 */
CGame::~CGame()
{
	CPlayer::Release();

	DELETE cpPlayer_m;
	DELETE CSystem::cpMessager_m;
} /* CGame::~CGame */


/*
 *	CGame::Start
 */
void CGame::Start(T_UWORD uwWorld_p)
{
	CPlayer::Get(uwWorld_p);
} /* CGame::Start */


/*
 *	CGame::ReStart
 */
void CGame::ReStart(T_UWORD uwWorld_p)
{
	CPlayer::Release();
	DELETE cpPlayer_m;
	cpPlayer_m=NEW CPlayer("univers.txt");
	CPlayer::Get(uwWorld_p);
} /* CGame::ReStart */


/*
 *	CGame::Update
 */
void CGame::Update()
{
	CPlayer::Update();
} /* CGame::Update */


/*
 *	CGame::Draw
 */
void CGame::Draw(T_BOOL bDebug_p)
{
	CScreen::BeginRendering();

	CPlayer::Draw(bDebug_p);
	CSFX::UpdateBlood();
	CScreen::EndRendering();

	CPlayer::DrawSel();
} /* CGame::Draw */


