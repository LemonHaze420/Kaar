#include "Cell.h"


#define D_CELL_MINIMALALTITUDE -10000.0f


/*
 *	CCell::PointInSegment
 */
T_BOOL CCell::PointInSegment(CVector<T_3DVALUE>* cpP0_p,CVector<T_3DVALUE>* cpP1_p,CVector<T_3DVALUE>* cpM_p)
{
	if((cpM_p->tX>=cpP0_p->tX && cpM_p->tX<=cpP1_p->tX) ||
		(cpM_p->tX<=cpP0_p->tX && cpM_p->tX>=cpP1_p->tX))
	{
		if((cpM_p->tZ>=cpP0_p->tZ && cpM_p->tZ<=cpP1_p->tZ) ||
			(cpM_p->tZ<=cpP0_p->tZ && cpM_p->tZ>=cpP1_p->tZ))
			return true;
	}
	return false;
} /* CCell::PointInSegment */


/*
 *	CCell::AltitudeInSegment
 */
T_3DVALUE CCell::AltitudeInSegment(CVector<T_3DVALUE>* cpP0_p,CVector<T_3DVALUE>* cpP1_p,CVector<T_3DVALUE>* cpM_p)
{
	T_3DVALUE tXab=cpP1_p->tX-cpP0_p->tX;
	T_3DVALUE tZab=cpP1_p->tZ-cpP0_p->tZ;
	T_3DVALUE tYab=cpP1_p->tY-cpP0_p->tY;
	T_3DVALUE tYa=cpP0_p->tY;
	if(tXab==0.0f)
	{
		if(tZab==0.0f)
			return Max(cpP0_p->tY,cpP1_p->tY);
		else
		{
			T_3DVALUE tZam=cpM_p->tZ-cpP0_p->tZ;
			return tYa+tZam*tYab/tZab;
		}
	}
	T_3DVALUE tXam=cpM_p->tZ-cpP0_p->tZ;
	return tYa+tXam*tYab/tXab;
} /* CCell::AltitudeInSegment */


/*
 *	CCell::PointInFace
 */
T_BOOL CCell::PointInFace(CVector<T_3DVALUE>* cpP0_p,CVector<T_3DVALUE>* cpP1_p,CVector<T_3DVALUE>* cpP2_p,CVector<T_3DVALUE>* cpM_p)
{
	CVector<T_3DVALUE> cAB=(*cpP1_p)-(*cpP0_p);
	CVector<T_3DVALUE> cAM=(*cpM_p)-(*cpP0_p);
	CVector<T_3DVALUE> cBC=(*cpP2_p)-(*cpP1_p);
	CVector<T_3DVALUE> cBM=(*cpM_p)-(*cpP1_p);
	CVector<T_3DVALUE> cCA=(*cpP0_p)-(*cpP2_p);
	CVector<T_3DVALUE> cCM=(*cpM_p)-(*cpP2_p);


	T_3DVALUE tY_ABvAM=cAB.tZ*cAM.tX-cAB.tX*cAM.tZ;
	T_3DVALUE tY_BCvBM=cBC.tZ*cBM.tX-cBC.tX*cBM.tZ;
	T_3DVALUE tY_CAvCM=cCA.tZ*cCM.tX-cCA.tX*cCM.tZ;

	if(tY_ABvAM>=0.0f && tY_BCvBM>=0.0f && tY_CAvCM>=0.0f)
		return true;
	return false;
} /* CCell::PointInFace */


/*
 *	CCell::AltitudeInFace
 */
T_3DVALUE CCell::AltitudeInFace(CVector<T_3DVALUE>* cpP0_p,CVector<T_3DVALUE>* cpP1_p,CVector<T_3DVALUE>* cpP2_p,CVector<T_3DVALUE>* cpM_p)
{
	T_3DVALUE tXab=cpP1_p->tX-cpP0_p->tX;
	T_3DVALUE tZab=cpP1_p->tZ-cpP0_p->tZ;
	T_3DVALUE tXac=cpP2_p->tX-cpP0_p->tX;
	T_3DVALUE tZac=cpP2_p->tZ-cpP0_p->tZ;

	T_3DVALUE tD=tXac*tZab-tXab*tZac;
	if(tD==0.0f)
	{
		// La face est dans un plan vertical
		T_3DVALUE tY01=D_CELL_MINIMALALTITUDE;
		T_3DVALUE tY12=D_CELL_MINIMALALTITUDE;
		T_3DVALUE tY20=D_CELL_MINIMALALTITUDE;
		if(PointInSegment(cpP0_p,cpP1_p,cpM_p))
			tY01=AltitudeInSegment(cpP0_p,cpP1_p,cpM_p);
		if(PointInSegment(cpP1_p,cpP2_p,cpM_p))
			tY12=AltitudeInSegment(cpP1_p,cpP2_p,cpM_p);
		if(PointInSegment(cpP2_p,cpP0_p,cpM_p))
			tY20=AltitudeInSegment(cpP2_p,cpP0_p,cpM_p);

		return Max(Max(tY01,tY12),tY20);
	}
	// Sinon calcul de l'intersection avec le plan de la face
	T_3DVALUE tYab=cpP1_p->tY-cpP0_p->tY;
	T_3DVALUE tYac=cpP2_p->tY-cpP0_p->tY;
	T_3DVALUE tXma=cpP0_p->tX-cpM_p->tX;
	T_3DVALUE tZma=cpP0_p->tZ-cpM_p->tZ;
	T_3DVALUE tYa=cpP0_p->tY;

	T_3DVALUE tAlpha=(tXac*tZma-tXma*tZac)/tD;
	T_3DVALUE tBeta=(tXma*tZab-tXab*tZma)/tD;
	return tYa-tAlpha*tYab-tBeta*tYac;
} /* CCell::AltitudeInFace */


/*
 *	CCell::GetAltitude
 */
void CCell::GetAltitude(CMeshObj* cpMeshObj_p,T_3DVALUE tX_p,T_3DVALUE tY_p)
{
	CVector<T_3DVALUE> cM;
	cM.Set(tX_p,0.0f,-tY_p);
	T_3DVALUE tAltitude=D_CELL_MINIMALALTITUDE;
	T_BOOL bFound=false;

	// Accès aux données des meshes
	cpMeshObj_p->Evaluate();
	// Récupérer le premier éval mgr
	T_HANDLE tEvHa;
	CMeshObj::EEvMgrType eEvMgrType;
	CMeshEvalMgrObj *cpMeshEv;
	cpMeshObj_p->GetFirstEvalMgr((CDynamicSceneNodeEvalMgr **)&cpMeshEv,&eEvMgrType,&tEvHa);

	while(cpMeshEv!=NULL)
	{
		// Mesh evaluator ?
		if(eEvMgrType!=CMeshObj::E_EVMGRTYPE_MESH)
			continue;

		// Ok, ici mesh evaluator détecté.
		// Récupérer le nombre de face groups associé à notre évaluateur
		T_CARD tNbFg;
		cpMeshEv->GetNbFaceGroup(&tNbFg);

		// Parcourir chaque facegroup
		for(T_INDEX tFg=0;tFg<tNbFg;tFg++)
		{
			// Pour ce face group, récupérer les vecteurs évalué correspondant aux 
			// positions,normales,textures etc.
			CVector<T_3DVALUE>* cpVecPos;
			T_CARD tNbVecPos;
			cpMeshEv->GetEvaluatedVectors(tFg,CMeshEvalMgrObj::E_NODEPTRIND_POSITION,
				&cpVecPos,&tNbVecPos);
/*			CVector<T_3DVALUE>* cpVecNor;
			T_CARD tNbVecNor;
			cpMeshEv->GetEvaluatedVectors(tFg,CMeshEvalMgrObj::E_NODEPTRIND_NORMAL,
				&cpVecNor,&tNbVecNor);
			CVector<T_3DVALUE>* cpVecTex;
			T_CARD tNbVecTex;
			cpMeshEv->GetEvaluatedVectors(tFg,CMeshEvalMgrObj::E_NODEPTRIND_TEXTURE,
				&cpVecTex,&tNbVecTex);
*/
			// Récupérer le ptr sur le facegroup
			CFaceGroup *cpFg;
			cpMeshEv->GetFaceGroup(tFg,&cpFg);
			// Récupérer pour ce fg, les meshvertex
			T_CARD tNbVert;
			cpFg->GetNbVertex(&tNbVert);
			CVertex *cpVert;
			cpFg->GetVertexRef(&cpVert);
			// Récupérer le nombre de facesets.
			T_CARD tNbFs;
			cpFg->GetNbFaceSet(&tNbFs);

			// Parcourir chacun des facesets
			for(T_INDEX tFs=0;tFs<tNbFs;tFs++)
			{
				// Récupérer le ptr sur le faceset
				CFaceSet *cpFs;
				cpFg->GetFaceSet(tFs,&cpFs);

				// Pour ce faceset, regarde le type de pushtype
				CFaceSet::EPushingType ePushType;
				cpFs->GetPushType(&ePushType);
				if(ePushType!=CFaceSet::E_PUSHINGTYPE_TRIANGLE)
					continue;

				// Récupérer ptr sur tab d'index
				T_CARD tNbInd;
				cpFs->GetNbVertInd(&tNbInd);
				T_INDEX *tpInd;
				cpFs->GetVertIndRef(&tpInd);

				for(T_INDEX t=0;t<tNbInd/3;t++)
				{
					// Calcul altitude
					CVector<T_3DVALUE>* cpP0=&cpVecPos[cpVert[tpInd[t*3+0]].wXYZIndex];
					CVector<T_3DVALUE>* cpP1=&cpVecPos[cpVert[tpInd[t*3+1]].wXYZIndex];
					CVector<T_3DVALUE>* cpP2=&cpVecPos[cpVert[tpInd[t*3+2]].wXYZIndex];
					if(PointInFace(cpP0,cpP1,cpP2,&cM))
					{
						T_3DVALUE t=AltitudeInFace(cpP0,cpP1,cpP2,&cM);
						if(t>tAltitude)
							tAltitude=t;
						bFound=true;
					}
				}
			}
		}			
		cpMeshObj_p->GetNextEvalMgr((CDynamicSceneNodeEvalMgr **)&cpMeshEv,&eEvMgrType,&tEvHa);
	}
	if(!bFound)
	{
//		throw "CCell - Vertex altitude in bloc mesh not found";
		biAltitude_m=0;
		biType_m=E_CELL_TYPENONE;
		biEvent_m=0;
	}
	else
	{
		if(tAltitude>255.0f || tAltitude<-256.0f)
			throw "CCell - Vertex altitude in bloc mesh must be between -256 & 255";
		biAltitude_m=T_WORD(tAltitude)/4+2;
		biType_m=E_CELL_TYPEGROUND;
		biEvent_m=0;
	}
} /* CCell::GetAltitude */







		
