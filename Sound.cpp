#include "Sound.h"


CSndBuf* CSound::cpPannelRoll_m;
CSndBuf* CSound::cpPannelLock_m;
CSndBuf* CSound::cpNewGame_m;
CSndBuf* CSound::cpPannelSelection_m;
CSndBuf* CSound::cpStracmiteAttack_m;
CSndBuf* CSound::cpStracmiteImpact_m;
CSndBuf* CSound::cpStracmiteMort_m;
CSndBuf* CSound::cpFireImpact_m;
CSndBuf* CSound::cpFireLaunch_m;
CSndBuf* CSound::cpChuteImpact_m;
CSndBuf* CSound::cpJuicy_m;
CSndBuf* CSound::cpVolBarive_m;
CSndBuf* CSound::cpVolSaur_m;
CSndBuf* CSound::cpVolFour_m;
CSndBuf* CSound::cpPannelDead_m;

CSndBuf* CSound::cpUergImpact_m;
CSndBuf* CSound::cpUergAttack_m;
CSndBuf* CSound::cpUergMort_m;
CSndBuf* CSound::cpUergOrdre_m[4];

CSndBuf* CSound::cpRaagasImpact_m;
CSndBuf* CSound::cpRaagasAttack_m;
CSndBuf* CSound::cpRaagasMort_m;
CSndBuf* CSound::cpRaagasOrdre_m[4];

CSndBuf* CSound::cpFourmantaImpact_m;
CSndBuf* CSound::cpFourmantaAttack_m;
CSndBuf* CSound::cpFourmantaMort_m;
CSndBuf* CSound::cpFourmantaOrdre_m[4];

CSndBuf* CSound::cpSaureilleImpact_m;
CSndBuf* CSound::cpSaureilleMort_m;

CSndCtrl* CSound::cpCtrl_m;



/*
 *	CSound::CSound
 */
CSound::CSound()
{
	CSystem::cp2dSnd_m->SelectBestDevice(
		C2dSnd::F_SN2DSND_8CHANNELS|
		C2dSnd::F_SN2DSND_16BITS|
		C2dSnd::F_SN2DSND_STEREO|
		C2dSnd::F_SN2DSND_VOLUMECTRL|
		C2dSnd::F_SN2DSND_PANCTRL);

	CSystem::cp2dSnd_m->SetVolume(0.0f);

	CSystem::cp2dSnd_m->CreateSndCtrl(&cpCtrl_m);
	cpCtrl_m->SetPitch(0.0f);

	CStdStr cName;
	cName="Divers\\PannelRoll.Wav";
	CSystem::cp2dSnd_m->LoadSndBuf(CSystem::cpFileCtx_m,cName,&cpPannelRoll_m);
	cName="Divers\\PannelLock.Wav";
	CSystem::cp2dSnd_m->LoadSndBuf(CSystem::cpFileCtx_m,cName,&cpPannelLock_m);
	cName="Divers\\NewGame.Wav";
	CSystem::cp2dSnd_m->LoadSndBuf(CSystem::cpFileCtx_m,cName,&cpNewGame_m);
	cName="Divers\\PannelSelection.Wav";
	CSystem::cp2dSnd_m->LoadSndBuf(CSystem::cpFileCtx_m,cName,&cpPannelSelection_m);
	cName="Divers\\FireImpact.Wav";
	CSystem::cp2dSnd_m->LoadSndBuf(CSystem::cpFileCtx_m,cName,&cpFireImpact_m);
	cName="Divers\\FireLaunch.Wav";
	CSystem::cp2dSnd_m->LoadSndBuf(CSystem::cpFileCtx_m,cName,&cpFireLaunch_m);
	cName="Divers\\ChuteImpact.Wav";
	CSystem::cp2dSnd_m->LoadSndBuf(CSystem::cpFileCtx_m,cName,&cpChuteImpact_m);
	cName="Divers\\Juicy.Wav";
	CSystem::cp2dSnd_m->LoadSndBuf(CSystem::cpFileCtx_m,cName,&cpJuicy_m);
	cName="Divers\\VolBarive.Wav";
	CSystem::cp2dSnd_m->LoadSndBuf(CSystem::cpFileCtx_m,cName,&cpVolBarive_m);
	cName="Divers\\VolSaur.Wav";
	CSystem::cp2dSnd_m->LoadSndBuf(CSystem::cpFileCtx_m,cName,&cpVolSaur_m);
	cName="Divers\\VolFour.Wav";
	CSystem::cp2dSnd_m->LoadSndBuf(CSystem::cpFileCtx_m,cName,&cpVolFour_m);
	cName="Divers\\PannelDead.Wav";
	CSystem::cp2dSnd_m->LoadSndBuf(CSystem::cpFileCtx_m,cName,&cpPannelDead_m);

	cName="Stracmite\\Attack.Wav";
	CSystem::cp2dSnd_m->LoadSndBuf(CSystem::cpFileCtx_m,cName,&cpStracmiteAttack_m);
	cName="Stracmite\\Mort.Wav";
	CSystem::cp2dSnd_m->LoadSndBuf(CSystem::cpFileCtx_m,cName,&cpStracmiteMort_m);
	cName="Stracmite\\Impact.Wav";
	CSystem::cp2dSnd_m->LoadSndBuf(CSystem::cpFileCtx_m,cName,&cpStracmiteImpact_m);

	cName="Uerg\\Attack.Wav";
	CSystem::cp2dSnd_m->LoadSndBuf(CSystem::cpFileCtx_m,cName,&cpUergAttack_m);
	cName="Uerg\\Mort.Wav";
	CSystem::cp2dSnd_m->LoadSndBuf(CSystem::cpFileCtx_m,cName,&cpUergMort_m);
	cName="Uerg\\Impact.Wav";
	CSystem::cp2dSnd_m->LoadSndBuf(CSystem::cpFileCtx_m,cName,&cpUergImpact_m);
	cName="Uerg\\Ordre1.Wav";
	CSystem::cp2dSnd_m->LoadSndBuf(CSystem::cpFileCtx_m,cName,&cpUergOrdre_m[0]);
	cName="Uerg\\Ordre2.Wav";
	CSystem::cp2dSnd_m->LoadSndBuf(CSystem::cpFileCtx_m,cName,&cpUergOrdre_m[1]);
	cName="Uerg\\Ordre3.Wav";
	CSystem::cp2dSnd_m->LoadSndBuf(CSystem::cpFileCtx_m,cName,&cpUergOrdre_m[2]);
	cName="Uerg\\Ordre4.Wav";
	CSystem::cp2dSnd_m->LoadSndBuf(CSystem::cpFileCtx_m,cName,&cpUergOrdre_m[3]);

	cName="Raagas\\Attack.Wav";
	CSystem::cp2dSnd_m->LoadSndBuf(CSystem::cpFileCtx_m,cName,&cpRaagasAttack_m);
	cName="Raagas\\Mort.Wav";
	CSystem::cp2dSnd_m->LoadSndBuf(CSystem::cpFileCtx_m,cName,&cpRaagasMort_m);
	cName="Raagas\\Impact.Wav";
	CSystem::cp2dSnd_m->LoadSndBuf(CSystem::cpFileCtx_m,cName,&cpRaagasImpact_m);
	cName="Raagas\\Ordre1.Wav";
	CSystem::cp2dSnd_m->LoadSndBuf(CSystem::cpFileCtx_m,cName,&cpRaagasOrdre_m[0]);
	cName="Raagas\\Ordre2.Wav";
	CSystem::cp2dSnd_m->LoadSndBuf(CSystem::cpFileCtx_m,cName,&cpRaagasOrdre_m[1]);
	cName="Raagas\\Ordre3.Wav";
	CSystem::cp2dSnd_m->LoadSndBuf(CSystem::cpFileCtx_m,cName,&cpRaagasOrdre_m[2]);
	cName="Raagas\\Ordre4.Wav";
	CSystem::cp2dSnd_m->LoadSndBuf(CSystem::cpFileCtx_m,cName,&cpRaagasOrdre_m[3]);

	cName="Fourmanta\\Attack.Wav";
	CSystem::cp2dSnd_m->LoadSndBuf(CSystem::cpFileCtx_m,cName,&cpFourmantaAttack_m);
	cName="Fourmanta\\Mort.Wav";
	CSystem::cp2dSnd_m->LoadSndBuf(CSystem::cpFileCtx_m,cName,&cpFourmantaMort_m);
	cName="Fourmanta\\Impact.Wav";
	CSystem::cp2dSnd_m->LoadSndBuf(CSystem::cpFileCtx_m,cName,&cpFourmantaImpact_m);
	cName="Fourmanta\\Ordre1.Wav";
	CSystem::cp2dSnd_m->LoadSndBuf(CSystem::cpFileCtx_m,cName,&cpFourmantaOrdre_m[0]);
	cName="Fourmanta\\Ordre2.Wav";
	CSystem::cp2dSnd_m->LoadSndBuf(CSystem::cpFileCtx_m,cName,&cpFourmantaOrdre_m[1]);
	cName="Fourmanta\\Ordre3.Wav";
	CSystem::cp2dSnd_m->LoadSndBuf(CSystem::cpFileCtx_m,cName,&cpFourmantaOrdre_m[2]);
	cName="Fourmanta\\Ordre4.Wav";
	CSystem::cp2dSnd_m->LoadSndBuf(CSystem::cpFileCtx_m,cName,&cpFourmantaOrdre_m[3]);

	cName="Saureille\\Impact.Wav";
	CSystem::cp2dSnd_m->LoadSndBuf(CSystem::cpFileCtx_m,cName,&cpSaureilleImpact_m);
	cName="Saureille\\Mort.Wav";
	CSystem::cp2dSnd_m->LoadSndBuf(CSystem::cpFileCtx_m,cName,&cpSaureilleMort_m);
} /* CSound::CSound */


/*
 *	CSound::~CSound
 */
CSound::~CSound()
{
	DELETE cpPannelRoll_m;
	DELETE cpPannelLock_m;
	DELETE cpNewGame_m;
	DELETE cpPannelSelection_m;
	DELETE cpFireImpact_m;
	DELETE cpFireLaunch_m;
	DELETE cpChuteImpact_m;
	DELETE cpJuicy_m;
	DELETE cpVolBarive_m;
	DELETE cpVolSaur_m;
	DELETE cpVolFour_m;
	DELETE cpPannelDead_m;

	DELETE cpStracmiteAttack_m;
	DELETE cpStracmiteMort_m;
	DELETE cpStracmiteImpact_m;

	DELETE cpUergAttack_m;
	DELETE cpUergMort_m;
	DELETE cpUergImpact_m;
	DELETE cpUergOrdre_m[0];
	DELETE cpUergOrdre_m[1];
	DELETE cpUergOrdre_m[2];
	DELETE cpUergOrdre_m[3];

	DELETE cpRaagasAttack_m;
	DELETE cpRaagasMort_m;
	DELETE cpRaagasImpact_m;
	DELETE cpRaagasOrdre_m[0];
	DELETE cpRaagasOrdre_m[1];
	DELETE cpRaagasOrdre_m[2];
	DELETE cpRaagasOrdre_m[3];

	DELETE cpFourmantaAttack_m;
	DELETE cpFourmantaMort_m;
	DELETE cpFourmantaImpact_m;
	DELETE cpFourmantaOrdre_m[0];
	DELETE cpFourmantaOrdre_m[1];
	DELETE cpFourmantaOrdre_m[2];
	DELETE cpFourmantaOrdre_m[3];

	DELETE cpSaureilleImpact_m;
	DELETE cpSaureilleMort_m;

	DELETE cpCtrl_m;
} /* CSound::~CSound */

