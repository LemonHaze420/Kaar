#include "CharPos.h"
#include "Univers.h"
#include "WorldPos.h"


/*
 *	CCharPos
 */
CCharPos::CCharPos()
{
	uwWorld_m=0;
	uwXZone_m=0;
	uwYZone_m=0;
	uwXBloc_m=0;
	uwYBloc_m=0;
	uwXCell_m=0;
	uwYCell_m=0;
	cpWorld_m=0;
	cpZoneInst_m=0;
	cpBlocInst_m=0;
	cpBlocItem_m=0;
	cPosition_m.Set(0.0f,0.0f,0.0f);
	tAngle_m=D_PI;
	tToAngle_m=D_PI;
	tAltitude_m=0;
} /* CCharPos */


/*
 *	CCharPos::Set
 */
void CCharPos::Set(T_3DVALUE tAltitude_p,T_UWORD uwWorld_p,T_UWORD uwXZone_p,T_UWORD uwYZone_p,T_UWORD uwXBloc_p,T_UWORD uwYBloc_p,T_UWORD uwXCell_p,T_UWORD uwYCell_p)
{
	tAltitude_m=tAltitude_p;
	uwWorld_m=uwWorld_p;
	uwXZone_m=uwXZone_p;
	uwYZone_m=uwYZone_p;
	uwXBloc_m=uwXBloc_p;
	uwYBloc_m=uwYBloc_p;
	uwXCell_m=uwXCell_p;
	uwYCell_m=uwYCell_p;

	cToGo_m.tX=cPosition_m.tX=CWorld::GetXPosition(uwXZone_p,uwXBloc_p,uwXCell_p);
	cToGo_m.tZ=cPosition_m.tZ=CWorld::GetYPosition(uwYZone_p,uwYBloc_p,uwYCell_p);
	cToGo_m.tY=cPosition_m.tY=0.0f;
} /* CCharPos::Set */


/*
 *	CCharPos::StartAltitude
 */
void CCharPos::StartAltitude()
{
	CWorldPos cWorldPos(uwWorld_m,cToGo_m.tX,cToGo_m.tZ);
	cToGo_m.tY=cWorldPos.GetAltitude()+tAltitude_m;
} /* CCharPos::StartAltitude */


/*
 *	CCharPos::Update
 */
T_BOOL CCharPos::Update(T_3DVALUE tSpeed_p,ECharPosFlag eFlag_p)
{
	T_DATE tDifTime=CSystem::tTime_m-tPrevTime_m;
	tPrevTime_m=CSystem::tTime_m;
	T_FLOAT tTimeFactor=1.0f;//tDifTime/40.0f;

	CVector<T_3DVALUE> cMove;
	cMove.Set(cToGo_m.tX-cPosition_m.tX,cToGo_m.tY-cPosition_m.tY,cToGo_m.tZ-cPosition_m.tZ);

	T_3DVALUE tLen=T_3DVALUE(sqrt(double(cMove.tX*cMove.tX+cMove.tY*cMove.tY+cMove.tZ*cMove.tZ)));
	T_3DVALUE t2DLen=T_3DVALUE(sqrt(double(cMove.tX*cMove.tX+cMove.tZ*cMove.tZ)));
	T_BOOL bStop=false;
	if(((eFlag_p&E_CHARPOS_ALTITUDEFREE) && tLen<=(tSpeed_p/2.0f)) ||
		(!(eFlag_p&E_CHARPOS_ALTITUDEFREE) && t2DLen<=(tSpeed_p/2.0f)))
	{
		bStop=true;
		cMove.Set(0.0f,0.0f,0.0f);
		T_MATHANVALUE tDelta=tToAngle_m-tAngle_m;
		while(tDelta<-D_PI)
			tDelta+=D_PI*2.0f;

		while(tDelta>D_PI)
			tDelta-=D_PI*2.0f;

		tAngle_m+=4.0f*tDelta/(tSpeed_p*tTimeFactor);
	}
	else
	{
		if(eFlag_p&E_CHARPOS_ROTATE)
		{
			CVector<T_3DVALUE> cVec;
			cVec.Set(cMove.tX/t2DLen,0.0f,cMove.tZ/t2DLen);

			tToAngle_m=acos(double(cVec.tZ));
			if(cVec.tX>0)
				tToAngle_m=D_PI*2.0f-tToAngle_m;

			T_MATHANVALUE tDelta=tToAngle_m-tAngle_m;
			while(tDelta<-D_PI)
				tDelta+=D_PI*2.0f;

			while(tDelta>D_PI)
				tDelta-=D_PI*2.0f;

			tAngle_m+=2.0f*tDelta*tTimeFactor/tSpeed_p;
		}
		cMove.Set(tSpeed_p*cMove.tX*tTimeFactor/tLen,tSpeed_p*cMove.tY*tTimeFactor/tLen,tSpeed_p*cMove.tZ*tTimeFactor/tLen);
	}

	cPosition_m.tX+=cMove.tX;
	cPosition_m.tZ+=cMove.tZ;
	if(eFlag_p&E_CHARPOS_ALTITUDEFREE)
		tAltitude_m+=cMove.tY;
//		cPosition_m.tY+=cMove.tY;

	cpWorld_m=&CUnivers::cpWorld_m[uwWorld_m];
	T_3DVALUE tAltitude;
	if(cpWorld_m->InRange(cPosition_m.tX,cPosition_m.tZ))
	{
		uwXZone_m=cpWorld_m->GetXZone(cPosition_m.tX);
		uwYZone_m=cpWorld_m->GetYZone(cPosition_m.tZ);
		cpZoneInst_m=cpWorld_m->GetZoneInst(uwXZone_m,uwYZone_m);

		uwXBloc_m=cpZoneInst_m->GetXBloc(cPosition_m.tX);
		uwYBloc_m=cpZoneInst_m->GetYBloc(cPosition_m.tZ);
		cpBlocInst_m=cpZoneInst_m->GetBlocInst(uwXBloc_m,uwYBloc_m);

		uwXCell_m=cpBlocInst_m->GetXCell(cPosition_m.tX);
		uwYCell_m=cpBlocInst_m->GetYCell(cPosition_m.tZ);
		cpCell_m=cpBlocInst_m->GetCell(uwXCell_m,uwYCell_m);

		tAltitude=T_3DVALUE(cpZoneInst_m->wAltitude_m+cpBlocInst_m->cBlocPos_m.biAltitude_m*64+cpCell_m->biAltitude_m*4);
		cPosition_m.tY+=((tAltitude_m+tAltitude)-cPosition_m.tY)/4.0f;
		if((eFlag_p&E_CHARPOS_ALTITUDEFREE) && cPosition_m.tY<tAltitude)
			cPosition_m.tY=tAltitude;

		// TODO EN VISU ?
		cpBlocItem_m=0;
	}
	else
	{
		uwXZone_m=0;
		uwYZone_m=0;
		cpZoneInst_m=0;
		uwXBloc_m=0;
		uwYBloc_m=0;
		cpBlocInst_m=0;
		uwXCell_m=0;
		uwYCell_m=0;
		cpCell_m=0;
		cpBlocItem_m=0;
		cPosition_m.tY=tAltitude_m;
	}

	return bStop;
} /* CCharPos::Update */


