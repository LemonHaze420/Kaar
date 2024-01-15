// -------------------------------------------------------------------------------
// -------------------------------------------------------------------------------
// -------------------------------------------------------------------------------
// -------------------------------------------------------------------------------
// -------------------------------------------------------------------------------
//
//		Purpose:
//			This file provide definition of a simple shadow caster
//
//		Writer:					
//			Eric Métens	<metens@club-internet.fr> (29/01/1998)
//
//		Modification list:
//
//			------------------------------------ (--/--/----)
//				---------------------------------------------------------------
//
//			------------------------------------ (--/--/----)
//				---------------------------------------------------------------
//
// -------------------------------------------------------------------------------
// -------------------------------------------------------------------------------
// -------------------------------------------------------------------------------
// -------------------------------------------------------------------------------
// -------------------------------------------------------------------------------

// Include du Kernel
#include "CRSWIN.H"

// Include local
#include "CRSPRSHA.H"

// Init ratio utilisation uv (Sqr(2))
const T_MATHVALUE		CSprShadow::tUVRatio_m=1.0f/1.414213562f;

// Constructeur
CSprShadow::CSprShadow(T_VOID):
	tpX_m(&CVector<T_3DVALUE>::tX),
	tpY_m(&CVector<T_3DVALUE>::tY),
	tpZ_m(&CVector<T_3DVALUE>::tZ)
{
T_INDEX t;

	// Init de tous nos vertex
	for (t=0;t<D_PRIVATECONST_MAXVERTNUM;t++)
	{
		cpVertex_m[t].cAmbientColor.White();
		cpVertex_m[t].wNXYZIndex=CVertex::D_PUBLICCONST_UNUSEDENTRY;
	}

	// Init de nos primitives
	for (t=0;t<D_PRIVATECONST_MAXPRIMNUM;t++)
	{
		cpPrim_m[t].tFlags=0;
	}

//	SetMemberPtrs(&CVector<T_3DVALUE>::tX,&CVector<T_3DVALUE>::tY,&CVector<T_3DVALUE>::tZ);

} // CSprShadow::CSprShadow

// Préparation au calcul des shadow (appel lors de chaque boucle).
T_VOID CSprShadow::Prepare(T_VOID)
{
	// Raz

	tNbPrim_m=0;	// Nbre de prim
	tNbTexVec_m=0;	// Nombre de vec tex
	tNbPosVec_m=0;	// Nombre de vec pos
	tNbVertex_m=0;	// Nombre de vertex
	
} // CSprShadow::Prepare

// Ajout des primitive de l'ensemble des shadows
T_VOID CSprShadow::AddPrims(CRenderCtx *cpCtx_p)
{

	cpCtx_p->AddPrims(
			cpVertex_m,tNbVertex_m,
			cpPosVec_m,tNbPosVec_m,
			NULL,0,
			cpTexVec_m,tNbTexVec_m,
			cpPrim_m,tNbPrim_m);

} // CSprShadow::AddPrims

// Calcul d'une shadow
T_VOID CSprShadow::ComputeShadow(
	CMath *cpMath_p,									// Objet math à utiliser
	CBmFrameObj *cpFrameObj_p,							// Ptr sur framefile
	T_INDEX tObjNum_p,									// Numéro d'objet
	T_INDEX tAnimNum_p,									// Numéro d'animation
	T_INDEX tFrameNum_p,								// Numéro de frame
	const CPt<T_3DVALUE> *cpShadPos_p,					// Position de la shadow
	T_3DVALUE tShadSize_p,								// Taille de la shadow
	CMeshObj *cpMeshToMap_p,							// Mesh à mapper
	const CVector<T_3DVALUE> *cpShiftPos_p,				// Valeur ajoutée à chaque coord
	T_MATHANVALUE tAnZ_p)								// Angle de rotation shad
{
CMeshEvalMgrObj *cpMeshEv;							// Evaluateur de mesh
T_HANDLE tEvHa;										// Handle sur évaluateurs 
CMeshObj::EEvMgrType eEvMgrType;					// Type d'évaluateur
CVector<T_3DVALUE> *cpMeshPosVec,*cpMeshTexVec;		// Vecteurs pos et tex du mesh
T_CARD tNbMeshPosVec,tNbMeshTexVec;					// Nombre de vecteurs pos et tex du mesh
CFaceGroup *cpFg;									// Ptr sur FaceGroup courant
CVertex *cpMeshVertex;								// Ptr sur les vertex du mesh
T_CARD tNbMeshVert;									// Nombre de vertex du mesh
T_CARD tNbFs;										// Nombre de FaceSet du FaceGroup de notre mesh
T_INDEX *tpMeshInd;									// Tab d'index pour FaceSet de notre mesh
T_CARD tNbMeshInd;									// Nombre d'index pour FaceSet de notre mesh
CFaceSet *cpFs;										// Ptr sur FaceSet courant
T_INDEX tCurFs;										// Index pour boucle des FaceSet
T_INDEX tCurMeshPrim;								// Index pour boucle des "prim" des FaceSet du mesh 
CFaceSet::EPushingType ePushType;					// Push type du faceset courant
CTrianglePrim *cpCurPrim;							// Ptr courant sur primitives
CVector<T_3DVALUE> *cpCurPosVec,*cpCurTexVec;		// Ptr courant sur vec pos et tex
CVertex *cpCurVertex;								// Ptr courant sur vertex
T_CARD tCurNbPrim;									// Nombre courant de prim
T_CARD tCurNbPosVec,tCurNbTexVec;					// Nombre courant de vec pos et tex
T_CARD tCurNbVertex;								// Nombre courant de vertex
CVector<T_3DVALUE> cpPrimPosVec[CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS]; // Vecteurs pos de la prim a clipper
CVector<T_3DVALUE> cpPrimTexVec[CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS]; // Vecteurs tex de la prim a clipper
T_CARD tNbClippedVec;								// Nombre de vecteurs clippés
T_INDEX tClippedPrim;								// Index pour primitive clippée courante
T_INDEX tClippedInd;								// Index pour index prim clippée
CMaterial *cpMat;									// Material associé
T_INDEX tSubMatIndex;								// Numéro de sub-mat
CVector<T_3DVALUE> cTmpVec;							// Temp pour calculs divers
T_MATHVALUE tSin,tCos;								// Sin  et cos de notre angle
CRectangle<T_3DVALUE> cShadRect;					// Zone de la shadow
T_3DVALUE tHalfShadSize=tShadSize_p*0.5f;			// Demi-taille de la shadow
T_3DVALUE tInvShadSize=1/tShadSize_p;				// Inverse de la taille de la shadow

	// Calcul de la zone de la shadow
	cShadRect.Set(
		cpShadPos_p->tX-tHalfShadSize,
		cpShadPos_p->tY-tHalfShadSize,
		cpShadPos_p->tX+tHalfShadSize,
		cpShadPos_p->tY+tHalfShadSize);

	// Calcul sin et cos de notre angle
	cpMath_p->Sin(tAnZ_p,&tSin);
	cpMath_p->Cos(tAnZ_p,&tCos);
	tSin*=tUVRatio_m;
	tCos*=tUVRatio_m;

	// Récup material et submat
	cpFrameObj_p->GetFrameInfo(tObjNum_p,tAnimNum_p,tFrameNum_p,&tSubMatIndex,&cpMat);

	// Calculer les différents ptrs à utiliser en fonction de l'état courant

	// Primtives
	cpCurPrim=cpPrim_m+tNbPrim_m;

	// Vecteurs pos et tex
	cpCurPosVec=cpPosVec_m+tNbPosVec_m;
	cpCurTexVec=cpTexVec_m+tNbTexVec_m;

	// Vertex
	cpCurVertex=cpVertex_m+tNbVertex_m;

	// Utilisation de "nombres courant" correspondant aux nouveaux ptrs.

	// Primitives
	tCurNbPrim=0;

	// Nombre de vecteur pos et tex
	tCurNbPosVec=0;
	tCurNbTexVec=0;

	// Nombre de vertex
	tCurNbVertex=0;

	// Récupérer dans le mesh chargé, les informations sur les meshvertexs etc.

	// Récupérer le premier éval mgr
	cpMeshToMap_p->GetFirstEvalMgr((CDynamicSceneNodeEvalMgr **)&cpMeshEv,&eEvMgrType,&tEvHa);

	// Evaluateur valide? 
	if (cpMeshEv!=NULL)
	{
		for (;;)
		{
			// Mesh evaluator ?
			if (eEvMgrType==CMeshObj::E_EVMGRTYPE_MESH)
			{
				cpMeshEv->GetEvaluatedVectors(0,CMeshEvalMgrObj::E_NODEPTRIND_POSITION,
					&cpMeshPosVec,&tNbMeshPosVec);

				cpMeshEv->GetEvaluatedVectors(0,CMeshEvalMgrObj::E_NODEPTRIND_TEXTURE,
					&cpMeshTexVec,&tNbMeshTexVec);

				// Récupérer le ptr sur le premier facegroup (a priori 1 seul fg présent)
				cpMeshEv->GetFaceGroup(0,&cpFg);

				// Récupérer pour ce fg, les meshvertex
				cpFg->GetNbVertex(&tNbMeshVert);
				cpFg->GetVertexRef(&cpMeshVertex);
		
				// Récupérer le ptr sur le faceset
				cpFg->GetNbFaceSet(&tNbFs);

				for (tCurFs=0;tCurFs<tNbFs;tCurFs++)
				{
					cpFg->GetFaceSet(tCurFs,&cpFs);

					// Pour ce faceset, regarde le type de pushtype
					cpFs->GetPushType(&ePushType);

					// Récupérer le nbre d'index
					cpFs->GetNbVertInd(&tNbMeshInd);

					// Récupérer ptr sur tab d'index
					cpFs->GetVertIndRef(&tpMeshInd);

					// Checker les primitives concernées par la shadow.
					for (tCurMeshPrim=0;tCurMeshPrim<tNbMeshInd/CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS;tCurMeshPrim++)
					{
						// Pour clipper, il nous faut récupérer les coordonnées des 3 vecteurs
						// de notre primitive.

						// Vecteurs position
						cpPrimPosVec[0]=cpMeshPosVec[cpMeshVertex[tpMeshInd[0+tCurMeshPrim*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS]].wXYZIndex]+*cpShiftPos_p;
						cpPrimPosVec[1]=cpMeshPosVec[cpMeshVertex[tpMeshInd[1+tCurMeshPrim*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS]].wXYZIndex]+*cpShiftPos_p;
						cpPrimPosVec[2]=cpMeshPosVec[cpMeshVertex[tpMeshInd[2+tCurMeshPrim*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS]].wXYZIndex]+*cpShiftPos_p;

						// Vecteurs tex (par calcul)
						cpPrimTexVec[0].tX=cpPrimPosVec[0].*tpX_m-cShadRect.tX1;
						cpPrimTexVec[0].tX*=tInvShadSize;
						cpPrimTexVec[0].tY=cpPrimPosVec[0].*tpY_m-cShadRect.tY1;
						cpPrimTexVec[0].tY*=tInvShadSize;

						cpPrimTexVec[1].tX=cpPrimPosVec[1].*tpX_m-cShadRect.tX1;
						cpPrimTexVec[1].tX*=tInvShadSize;
						cpPrimTexVec[1].tY=cpPrimPosVec[1].*tpY_m-cShadRect.tY1;
						cpPrimTexVec[1].tY*=tInvShadSize;

						cpPrimTexVec[2].tX=cpPrimPosVec[2].*tpX_m-cShadRect.tX1;
						cpPrimTexVec[2].tX*=tInvShadSize;
						cpPrimTexVec[2].tY=cpPrimPosVec[2].*tpY_m-cShadRect.tY1;
						cpPrimTexVec[2].tY*=tInvShadSize;

						// Le centre correspond à 0.5 0.5
						// Effectuer une rotation des coords de tex
						cTmpVec.tX=cpPrimTexVec[0].tX-0.5f;
						cTmpVec.tY=cpPrimTexVec[0].tY-0.5f;
						cpPrimTexVec[0].tX=(cTmpVec.tX*tCos+cTmpVec.tY*tSin)+0.5f;
						cpPrimTexVec[0].tY=(-cTmpVec.tX*tSin+cTmpVec.tY*tCos)+0.5f;
						
						cTmpVec.tX=cpPrimTexVec[1].tX-0.5f;
						cTmpVec.tY=cpPrimTexVec[1].tY-0.5f;
						cpPrimTexVec[1].tX=(cTmpVec.tX*tCos+cTmpVec.tY*tSin)+0.5f;
						cpPrimTexVec[1].tY=(-cTmpVec.tX*tSin+cTmpVec.tY*tCos)+0.5f;

						cTmpVec.tX=cpPrimTexVec[2].tX-0.5f;
						cTmpVec.tY=cpPrimTexVec[2].tY-0.5f;
						cpPrimTexVec[2].tX=(cTmpVec.tX*tCos+cTmpVec.tY*tSin)+0.5f;
						cpPrimTexVec[2].tY=(-cTmpVec.tX*tSin+cTmpVec.tY*tCos)+0.5f;

						// Clipping (ajout des vecteurs pos et tex) (D_PRIVATECONST_MAXVECNUM/2 car double buffer)
//						tNbClippedVec=D_PRIVATECONST_MAXVECNUM-tCurNbPosVec-tNbPosVec_m;
						tNbClippedVec=D_PRIVATECONST_MAXVECNUM/2-tCurNbPosVec-tNbPosVec_m;
						ClipTriangleWithRect(
							cpPrimPosVec,
							cpPrimTexVec,
							&cShadRect,
							cpCurPosVec+tCurNbPosVec,
							cpCurTexVec+tCurNbTexVec,
							&tNbClippedVec);

						// Checker si on dispose de la place pour les vertex 
						if (tCurNbVertex+tNbVertex_m+tNbClippedVec>D_PRIVATECONST_MAXVERTNUM)
						{
							D_ERROR(E_ERROR_SPRSHADOW_OVERFLOW,"No more room for vertex");
						}

						// Ajout des vertex correspondants aux index après clipping.
						for (tClippedInd=0;tClippedInd<tNbClippedVec;tClippedInd++)
						{
							cpCurVertex[tCurNbVertex+tClippedInd].wXYZIndex=tClippedInd+tCurNbPosVec+tNbPosVec_m;
							cpCurVertex[tCurNbVertex+tClippedInd].wTextIndex[0]=cpCurVertex[tCurNbVertex+tClippedInd].wXYZIndex;
						}

						// Checker si on dipose de la place pour les primitives
						if (tCurNbPrim+tNbPrim_m+tNbClippedVec/CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS>D_PRIVATECONST_MAXPRIMNUM)
						{
							D_ERROR(E_ERROR_SPRSHADOW_OVERFLOW,"No more room for primitive");
						}

						// Ajout des primitives clippées
						for (tClippedPrim=0;tClippedPrim<tNbClippedVec/CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS;tClippedPrim++)
						{
							// Ajout de la prim
							cpCurPrim[tCurNbPrim].cpMat=cpMat;
							cpCurPrim[tCurNbPrim].tSubMatIndex=tSubMatIndex;

							// !!!!!!!!!!!!!! On considère qu'un triangle contient 3 points !!!!!!!!!!!!!!!!!!
							cpCurPrim[tCurNbPrim].wVertexIndex[0]=
								tClippedPrim*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS+tCurNbVertex+tNbVertex_m+0;
							cpCurPrim[tCurNbPrim].wVertexIndex[1]=
								tClippedPrim*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS+tCurNbVertex+tNbVertex_m+1;
							cpCurPrim[tCurNbPrim].wVertexIndex[2]=
								tClippedPrim*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS+tCurNbVertex+tNbVertex_m+2;
							// !!!!!!!!!!!!!! On considère qu'un triangle contient 3 points !!!!!!!!!!!!!!!!!!

							tCurNbPrim++;
						}

						// Mise à jour des nombres courants
						tCurNbVertex+=tNbClippedVec;
						tCurNbPosVec+=tNbClippedVec;
						tCurNbTexVec+=tNbClippedVec;
					}
				}

				// Mise à jour des nombre de vertex etc. de notre classe

				// Primitives
				tNbPrim_m+=tCurNbPrim;

				// Nombre de vecteur pos et tex
				tNbPosVec_m+=tCurNbPosVec;
				tNbTexVec_m+=tCurNbTexVec;

				// Nombre de vertex
				tNbVertex_m+=tCurNbVertex;

				return;

			}
			cpMeshToMap_p->GetNextEvalMgr((CDynamicSceneNodeEvalMgr **)&cpMeshEv,&eEvMgrType,&tEvHa);

			if (cpMeshEv==NULL)
				break;
		}

	}

} // CSprShadow::ComputeShadow

// Effectue le clipping d'un triangle en fonction d'une zone rectangulaire
T_VOID CSprShadow::ClipTriangleWithRect(
	CVector<T_3DVALUE> *cpPosSrcTri_p,				// Triangle source (pos)
	CVector<T_3DVALUE> *cpTexSrcTri_p,				// Triangle source (tex)
	const CRectangle<T_3DVALUE> *cpClipRect_p,		// Zone de clip
	CVector<T_3DVALUE> *cpPosDestVec_p,				// Vec pos dest
	CVector<T_3DVALUE> *cpTexDestVec_p,				// Vec tex dest
	T_CARD *tpMaxDestVec_p							// Nbre max de vec dest (et retour nbre de vec)
	)
{
T_INDEX tMaxDestVec;
T_INDEX tDoubleBufDestVec;
CVector<T_3DVALUE> cTmpPosVec[2];
CVector<T_3DVALUE> cTmpTexVec[2];
T_3DVALUE tTmpVal;
T_INDEX tOut,tOut1,tOut2;
T_INDEX tIn,tIn1,tIn2;
T_BOOL boCut;
T_INDEX tCurTri;
T_CARD tNbSrcVec,tNbDestVec;
CVector<T_3DVALUE> *cpPosSrcVec,*cpPosDestVec;
CVector<T_3DVALUE> *cpTexSrcVec,*cpTexDestVec;
CVector<T_3DVALUE> *cpPosPt0,*cpPosPt1,*cpPosPt2;

	// Stocker le nombre max d'index et vecs
	tMaxDestVec=*tpMaxDestVec_p;
	tDoubleBufDestVec=D_PRIVATECONST_MAXVECNUM/2;

	// Commencer avec la source triangle passé en params 0 et dest à cpDest....+tDoubleBufDestVec....

	cpPosSrcVec=cpPosSrcTri_p;
	cpTexSrcVec=cpTexSrcTri_p;
	tNbSrcVec=CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS;

	cpPosDestVec=cpPosDestVec_p+tDoubleBufDestVec;
	cpTexDestVec=cpTexDestVec_p+tDoubleBufDestVec;
	tNbDestVec=0;

	// Test général de clipping
	if (
		cpPosSrcTri_p[0].*tpX_m>=cpClipRect_p->tX1 && cpPosSrcTri_p[0].*tpX_m<=cpClipRect_p->tX2 &&
		cpPosSrcTri_p[0].*tpY_m>=cpClipRect_p->tY1 && cpPosSrcTri_p[0].*tpY_m<=cpClipRect_p->tY2 &&
		cpPosSrcTri_p[1].*tpX_m>=cpClipRect_p->tX1 && cpPosSrcTri_p[1].*tpX_m<=cpClipRect_p->tX2 &&
		cpPosSrcTri_p[1].*tpY_m>=cpClipRect_p->tY1 && cpPosSrcTri_p[1].*tpY_m<=cpClipRect_p->tY2 &&
		cpPosSrcTri_p[2].*tpX_m>=cpClipRect_p->tX1 && cpPosSrcTri_p[2].*tpX_m<=cpClipRect_p->tX2 &&
		cpPosSrcTri_p[2].*tpY_m>=cpClipRect_p->tY1 && cpPosSrcTri_p[2].*tpY_m<=cpClipRect_p->tY2)
	{
		// Clipping non nécésaire...

		cpPosDestVec_p[0]=cpPosSrcTri_p[0];
		cpPosDestVec_p[1]=cpPosSrcTri_p[1];
		cpPosDestVec_p[2]=cpPosSrcTri_p[2];

		cpTexDestVec_p[0]=cpTexSrcTri_p[0];
		cpTexDestVec_p[1]=cpTexSrcTri_p[1];
		cpTexDestVec_p[2]=cpTexSrcTri_p[2];

		*tpMaxDestVec_p=3;

		return;
	}

	// Parcourir les triangles sortant en x-

	for (tCurTri=0;tCurTri<tNbSrcVec/CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS;tCurTri++)
	{
		// Pas de découpe
		boCut=D_FALSE;

		// Récup des ptrs sur les vecteurs
		cpPosPt0=&cpPosSrcVec[tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS+0];
		cpPosPt1=&cpPosSrcVec[tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS+1];
		cpPosPt2=&cpPosSrcVec[tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS+2];

		// Si les 3 points sortent, on continue
		if (cpPosPt0->*tpX_m<cpClipRect_p->tX1 && cpPosPt1->*tpX_m<cpClipRect_p->tX1 && cpPosPt2->*tpX_m<cpClipRect_p->tX1)
		{
			continue;
		}
	
		// Triangle non clippé?
		if (cpPosPt0->*tpX_m>=cpClipRect_p->tX1 && cpPosPt1->*tpX_m>=cpClipRect_p->tX1 && cpPosPt2->*tpX_m>=cpClipRect_p->tX1)
		{
			// Checker si on a la place (1 triangle)
			if (tNbDestVec+CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS>=tMaxDestVec)
			{
				D_ERROR(E_ERROR_SPRSHADOW_OVERFLOW,"No more room for vector");
			}

			// Ajout des vecteurs
			D_ADDVECDESTFROMINDEX(tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS+0);
			D_ADDVECDESTFROMINDEX(tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS+1);
			D_ADDVECDESTFROMINDEX(tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS+2);
			continue;
		}
	
		// 1 point sortant: 0
		if (cpPosPt0->*tpX_m<cpClipRect_p->tX1 && cpPosPt1->*tpX_m>=cpClipRect_p->tX1 && cpPosPt2->*tpX_m>=cpClipRect_p->tX1)
		{
			// Garder les pts dans le sens horlogique.
			tOut=0;	// Point sortant
			tIn1=1;	// Point intérieur 1 
			tIn2=2; // Point intérieur 2
			// On doit découper....
			boCut=D_TRUE;
		}
		else
		// 1 point sortant: 1
		if (cpPosPt1->*tpX_m<cpClipRect_p->tX1 && cpPosPt2->*tpX_m>=cpClipRect_p->tX1 && cpPosPt0->*tpX_m>=cpClipRect_p->tX1)
		{
			// Garder les pts dans le sens horlogique.
			tOut=1;	// Point sortant
			tIn1=2;	// Point intérieur 1 
			tIn2=0; // Point intérieur 2
			// On doit découper....
			boCut=D_TRUE;
		}
		else
		// 1 point sortant: 2
		if (cpPosPt2->*tpX_m<cpClipRect_p->tX1 && cpPosPt0->*tpX_m>=cpClipRect_p->tX1 && cpPosPt1->*tpX_m>=cpClipRect_p->tX1)
		{
			// Garder les pts dans le sens horlogique.
			tOut=2;	// Point sortant
			tIn1=0;	// Point intérieur 1 
			tIn2=1; // Point intérieur 2
			// On doit découper....
			boCut=D_TRUE;
		}

		// Découpe.
		if (boCut)
		{
			// Checker si on a la place (2 triangles)
			if (tNbDestVec+CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS*2>=tMaxDestVec)
			{
				D_ERROR(E_ERROR_SPRSHADOW_OVERFLOW,"No more room for vector");
			}

			// Mise à jour out,in1,in2
			tOut+=tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS;
			tIn1+=tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS;
			tIn2+=tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS;

			// Découper segment out-in1
			D_CUTSEG(cpClipRect_p->tX1,tOut,tIn1,cTmpPosVec[0],cTmpTexVec[0],*tpX_m,*tpY_m)
			// Découper segment out-in2
			D_CUTSEG(cpClipRect_p->tX1,tOut,tIn2,cTmpPosVec[1],cTmpTexVec[1],*tpX_m,*tpY_m)

			// Ajout triangle 1
			D_ADDVECDEST(cTmpPosVec[0],cTmpTexVec[0]);
			D_ADDVECDESTFROMINDEX(tIn1);
			D_ADDVECDESTFROMINDEX(tIn2);

			// Ajout triangle 2
			D_ADDVECDESTFROMINDEX(tIn2);
			D_ADDVECDEST(cTmpPosVec[1],cTmpTexVec[1]);
			D_ADDVECDEST(cTmpPosVec[0],cTmpTexVec[0]);
		}
		else
		{
			// 2 points sortant: 0 1
			if (cpPosPt0->*tpX_m<cpClipRect_p->tX1 && cpPosPt1->*tpX_m<cpClipRect_p->tX1 && cpPosPt2->*tpX_m>=cpClipRect_p->tX1)
			{
				// Garder les pts dans le sens horlogique.
				tOut1=0;	// Point sortant 1
				tOut2=1;	// Point sortant 2
				tIn=2;		// Point intérieur 
				// On doit découper....
				boCut=D_TRUE;
			}
			else
			// 2 points sortant: 1 2
			if (cpPosPt1->*tpX_m<cpClipRect_p->tX1 && cpPosPt2->*tpX_m<cpClipRect_p->tX1 && cpPosPt0->*tpX_m>=cpClipRect_p->tX1)
			{
				// Garder les pts dans le sens horlogique.
				tOut1=1;	// Point sortant 1
				tOut2=2;	// Point sortant 2
				tIn=0;		// Point intérieur 
				// On doit découper....
				boCut=D_TRUE;
			}
			else
			// 2 points sortant: 2 0
			if (cpPosPt2->*tpX_m<cpClipRect_p->tX1 && cpPosPt0->*tpX_m<cpClipRect_p->tX1 && cpPosPt1->*tpX_m>=cpClipRect_p->tX1)
			{
				// Garder les pts dans le sens horlogique.
				tOut1=2;	// Point sortant 1
				tOut2=0;	// Point sortant 2
				tIn=1;		// Point intérieur 
				// On doit découper....
				boCut=D_TRUE;
			}

			// Découpe.
			if (boCut)
			{
				// Checker si on a la place (1 triangle)
				if (tNbDestVec+CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS>=tMaxDestVec)
				{
					D_ERROR(E_ERROR_SPRSHADOW_OVERFLOW,"No more room for vector");
				}

				// Mise à jour out1,out2,in
				tOut1+=tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS;
				tOut2+=tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS;
				tIn+=tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS;
				
				// Découper segment out1-in
				D_CUTSEG(cpClipRect_p->tX1,tOut1,tIn,cTmpPosVec[0],cTmpTexVec[0],*tpX_m,*tpY_m)
				// Découper segment out2-in
				D_CUTSEG(cpClipRect_p->tX1,tOut2,tIn,cTmpPosVec[1],cTmpTexVec[1],*tpX_m,*tpY_m)

				// Ajout triangle.
				D_ADDVECDEST(cTmpPosVec[0],cTmpTexVec[0]);
				D_ADDVECDEST(cTmpPosVec[1],cTmpTexVec[1]);
				D_ADDVECDESTFROMINDEX(tIn);
			}
		}


	}			

	// Source: cpDestVec..+tDoubleBufDestVec 
	// Dest  : cpDestVec..

	cpPosSrcVec=cpPosDestVec_p+tDoubleBufDestVec;
	cpTexSrcVec=cpTexDestVec_p+tDoubleBufDestVec;
	tNbSrcVec=tNbDestVec;

	cpPosDestVec=cpPosDestVec_p;
	cpTexDestVec=cpTexDestVec_p;
	tNbDestVec=0;

	// Parcourir les triangles sortant en x+

	for (tCurTri=0;tCurTri<tNbSrcVec/CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS;tCurTri++)
	{

		
		// Pas de découpe
		boCut=D_FALSE;

		// Récup des ptrs sur les vecteurs
		cpPosPt0=&cpPosSrcVec[tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS+0];
		cpPosPt1=&cpPosSrcVec[tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS+1];
		cpPosPt2=&cpPosSrcVec[tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS+2];

		// Si les 3 points sortent, on continue
		if (cpPosPt0->*tpX_m>cpClipRect_p->tX2 && cpPosPt1->*tpX_m>cpClipRect_p->tX2 && cpPosPt2->*tpX_m>cpClipRect_p->tX2)
		{
			continue;
		}
	
		// Triangle non clippé?
		if (cpPosPt0->*tpX_m<=cpClipRect_p->tX2 && cpPosPt1->*tpX_m<=cpClipRect_p->tX2 && cpPosPt2->*tpX_m<=cpClipRect_p->tX2)
		{
			// Checker si on a la place (1 triangle)
			if (tNbDestVec+CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS>=tMaxDestVec)
			{
				D_ERROR(E_ERROR_SPRSHADOW_OVERFLOW,"No more room for vector");
			}

			// Ajout des vecteurs
			D_ADDVECDESTFROMINDEX(tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS+0);
			D_ADDVECDESTFROMINDEX(tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS+1);
			D_ADDVECDESTFROMINDEX(tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS+2);
			continue;
		}

		
		// 1 point sortant: 0
		if (cpPosPt0->*tpX_m>cpClipRect_p->tX2 && cpPosPt1->*tpX_m<=cpClipRect_p->tX2 && cpPosPt2->*tpX_m<=cpClipRect_p->tX2)
		{
			// Garder les pts dans le sens horlogique.
			tOut=0;	// Point sortant
			tIn1=1;	// Point intérieur 1 
			tIn2=2; // Point intérieur 2
			// On doit découper....
			boCut=D_TRUE;
		}
		else
		// 1 point sortant: 1
		if (cpPosPt1->*tpX_m>cpClipRect_p->tX2 && cpPosPt2->*tpX_m<=cpClipRect_p->tX2 && cpPosPt0->*tpX_m<=cpClipRect_p->tX2)
		{
			// Garder les pts dans le sens horlogique.
			tOut=1;	// Point sortant
			tIn1=2;	// Point intérieur 1 
			tIn2=0; // Point intérieur 2
			// On doit découper....
			boCut=D_TRUE;
		}
		else
		// 1 point sortant: 2
		if (cpPosPt2->*tpX_m>cpClipRect_p->tX2 && cpPosPt0->*tpX_m<=cpClipRect_p->tX2 && cpPosPt1->*tpX_m<=cpClipRect_p->tX2)
		{
			// Garder les pts dans le sens horlogique.
			tOut=2;	// Point sortant
			tIn1=0;	// Point intérieur 1 
			tIn2=1; // Point intérieur 2
			// On doit découper....
			boCut=D_TRUE;
		}

		// Découpe.
		if (boCut)
		{
			// Checker si on a la place (2 triangles)
			if (tNbDestVec+CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS*2>=tMaxDestVec)
			{
				D_ERROR(E_ERROR_SPRSHADOW_OVERFLOW,"No more room for vector");
			}

			// Mise à jour out,in1,in2
			tOut+=tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS;
			tIn1+=tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS;
			tIn2+=tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS;

			// Découper segment out-in1
			D_CUTSEG(cpClipRect_p->tX2,tOut,tIn1,cTmpPosVec[0],cTmpTexVec[0],*tpX_m,*tpY_m)
			// Découper segment out-in2
			D_CUTSEG(cpClipRect_p->tX2,tOut,tIn2,cTmpPosVec[1],cTmpTexVec[1],*tpX_m,*tpY_m)

			// Ajout triangle 1
			D_ADDVECDEST(cTmpPosVec[0],cTmpTexVec[0]);
			D_ADDVECDESTFROMINDEX(tIn1);
			D_ADDVECDESTFROMINDEX(tIn2);

			// Ajout triangle 2
			D_ADDVECDESTFROMINDEX(tIn2);
			D_ADDVECDEST(cTmpPosVec[1],cTmpTexVec[1]);
			D_ADDVECDEST(cTmpPosVec[0],cTmpTexVec[0]);
		}
		else
		{
			// 2 points sortant: 0 1
			if (cpPosPt0->*tpX_m>cpClipRect_p->tX2 && cpPosPt1->*tpX_m>cpClipRect_p->tX2 && cpPosPt2->*tpX_m<=cpClipRect_p->tX2)
			{
				// Garder les pts dans le sens horlogique.
				tOut1=0;	// Point sortant 1
				tOut2=1;	// Point sortant 2
				tIn=2;		// Point intérieur 
				// On doit découper....
				boCut=D_TRUE;
			}
			else
			// 2 points sortant: 1 2
			if (cpPosPt1->*tpX_m>cpClipRect_p->tX2 && cpPosPt2->*tpX_m>cpClipRect_p->tX2 && cpPosPt0->*tpX_m<=cpClipRect_p->tX2)
			{
				// Garder les pts dans le sens horlogique.
				tOut1=1;	// Point sortant 1
				tOut2=2;	// Point sortant 2
				tIn=0;		// Point intérieur 
				// On doit découper....
				boCut=D_TRUE;
			}
			else
			// 2 points sortant: 2 0
			if (cpPosPt2->*tpX_m>cpClipRect_p->tX2 && cpPosPt0->*tpX_m>cpClipRect_p->tX2 && cpPosPt1->*tpX_m<=cpClipRect_p->tX2)
			{
				// Garder les pts dans le sens horlogique.
				tOut1=2;	// Point sortant 1
				tOut2=0;	// Point sortant 2
				tIn=1;		// Point intérieur 
				// On doit découper....
				boCut=D_TRUE;
			}

			// Découpe.
			if (boCut)
			{
				// Checker si on a la place (1 triangle)
				if (tNbDestVec+CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS>=tMaxDestVec)
				{
					D_ERROR(E_ERROR_SPRSHADOW_OVERFLOW,"No more room for vector");
				}

				// Mise à jour out1,out2,in
				tOut1+=tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS;
				tOut2+=tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS;
				tIn+=tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS;
				
				// Découper segment out1-in
				D_CUTSEG(cpClipRect_p->tX2,tOut1,tIn,cTmpPosVec[0],cTmpTexVec[0],*tpX_m,*tpY_m)
				// Découper segment out2-in
				D_CUTSEG(cpClipRect_p->tX2,tOut2,tIn,cTmpPosVec[1],cTmpTexVec[1],*tpX_m,*tpY_m)

				// Ajout triangle.
				D_ADDVECDEST(cTmpPosVec[0],cTmpTexVec[0]);
				D_ADDVECDEST(cTmpPosVec[1],cTmpTexVec[1]);
				D_ADDVECDESTFROMINDEX(tIn);
			}
		}
	}			

	//eric

	// Source: cpDestVec..
	// Dest  : cpDestVec.. +tDoubleBufDestVec 

	cpPosSrcVec=cpPosDestVec_p;
	cpTexSrcVec=cpTexDestVec_p;
	tNbSrcVec=tNbDestVec;

	cpPosDestVec=cpPosDestVec_p+tDoubleBufDestVec;
	cpTexDestVec=cpTexDestVec_p+tDoubleBufDestVec;
	tNbDestVec=0;

	// Parcourir les triangles sortant en y-

	for (tCurTri=0;tCurTri<tNbSrcVec/CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS;tCurTri++)
	{
		// Pas de découpe
		boCut=D_FALSE;

		// Récup des ptrs sur les vecteurs
		cpPosPt0=&cpPosSrcVec[tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS+0];
		cpPosPt1=&cpPosSrcVec[tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS+1];
		cpPosPt2=&cpPosSrcVec[tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS+2];

		// Si les 3 points sortent, on continue
		if (cpPosPt0->*tpY_m<cpClipRect_p->tY1 && cpPosPt1->*tpY_m<cpClipRect_p->tY1 && cpPosPt2->*tpY_m<cpClipRect_p->tY1)
		{
			continue;
		}
	
		// Triangle non clippé?
		if (cpPosPt0->*tpY_m>=cpClipRect_p->tY1 && cpPosPt1->*tpY_m>=cpClipRect_p->tY1 && cpPosPt2->*tpY_m>=cpClipRect_p->tY1)
		{
			// Checker si on a la place (1 triangle)
			if (tNbDestVec+CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS>=tMaxDestVec)
			{
				D_ERROR(E_ERROR_SPRSHADOW_OVERFLOW,"No more room for vector");
			}

			// Ajout des vecteurs
			D_ADDVECDESTFROMINDEX(tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS+0);
			D_ADDVECDESTFROMINDEX(tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS+1);
			D_ADDVECDESTFROMINDEX(tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS+2);
			continue;
		}
	
		// 1 point sortant: 0
		if (cpPosPt0->*tpY_m<cpClipRect_p->tY1 && cpPosPt1->*tpY_m>=cpClipRect_p->tY1 && cpPosPt2->*tpY_m>=cpClipRect_p->tY1)
		{
			// Garder les pts dans le sens horlogique.
			tOut=0;	// Point sortant
			tIn1=1;	// Point intérieur 1 
			tIn2=2; // Point intérieur 2
			// On doit découper....
			boCut=D_TRUE;
		}
		else
		// 1 point sortant: 1
		if (cpPosPt1->*tpY_m<cpClipRect_p->tY1 && cpPosPt2->*tpY_m>=cpClipRect_p->tY1 && cpPosPt0->*tpY_m>=cpClipRect_p->tY1)
		{
			// Garder les pts dans le sens horlogique.
			tOut=1;	// Point sortant
			tIn1=2;	// Point intérieur 1 
			tIn2=0; // Point intérieur 2
			// On doit découper....
			boCut=D_TRUE;
		}
		else
		// 1 point sortant: 2
		if (cpPosPt2->*tpY_m<cpClipRect_p->tY1 && cpPosPt0->*tpY_m>=cpClipRect_p->tY1 && cpPosPt1->*tpY_m>=cpClipRect_p->tY1)
		{
			// Garder les pts dans le sens horlogique.
			tOut=2;	// Point sortant
			tIn1=0;	// Point intérieur 1 
			tIn2=1; // Point intérieur 2
			// On doit découper....
			boCut=D_TRUE;
		}

		// Découpe.
		if (boCut)
		{
			// Checker si on a la place (2 triangles)
			if (tNbDestVec+CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS*2>=tMaxDestVec)
			{
				D_ERROR(E_ERROR_SPRSHADOW_OVERFLOW,"No more room for vector");
			}

			// Mise à jour out,in1,in2
			tOut+=tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS;
			tIn1+=tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS;
			tIn2+=tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS;

			// Découper segment out-in1
			D_CUTSEG(cpClipRect_p->tY1,tOut,tIn1,cTmpPosVec[0],cTmpTexVec[0],*tpY_m,*tpX_m)
			// Découper segment out-in2
			D_CUTSEG(cpClipRect_p->tY1,tOut,tIn2,cTmpPosVec[1],cTmpTexVec[1],*tpY_m,*tpX_m)

			// Ajout triangle 1
			D_ADDVECDEST(cTmpPosVec[0],cTmpTexVec[0]);
			D_ADDVECDESTFROMINDEX(tIn1);
			D_ADDVECDESTFROMINDEX(tIn2);

			// Ajout triangle 2
			D_ADDVECDESTFROMINDEX(tIn2);
			D_ADDVECDEST(cTmpPosVec[1],cTmpTexVec[1]);
			D_ADDVECDEST(cTmpPosVec[0],cTmpTexVec[0]);
		}
		else
		{
			// 2 points sortant: 0 1
			if (cpPosPt0->*tpY_m<cpClipRect_p->tY1 && cpPosPt1->*tpY_m<cpClipRect_p->tY1 && cpPosPt2->*tpY_m>=cpClipRect_p->tY1)
			{
				// Garder les pts dans le sens horlogique.
				tOut1=0;	// Point sortant 1
				tOut2=1;	// Point sortant 2
				tIn=2;		// Point intérieur 
				// On doit découper....
				boCut=D_TRUE;
			}
			else
			// 2 points sortant: 1 2
			if (cpPosPt1->*tpY_m<cpClipRect_p->tY1 && cpPosPt2->*tpY_m<cpClipRect_p->tY1 && cpPosPt0->*tpY_m>=cpClipRect_p->tY1)
			{
				// Garder les pts dans le sens horlogique.
				tOut1=1;	// Point sortant 1
				tOut2=2;	// Point sortant 2
				tIn=0;		// Point intérieur 
				// On doit découper....
				boCut=D_TRUE;
			}
			else
			// 2 points sortant: 2 0
			if (cpPosPt2->*tpY_m<cpClipRect_p->tY1 && cpPosPt0->*tpY_m<cpClipRect_p->tY1 && cpPosPt1->*tpY_m>=cpClipRect_p->tY1)
			{
				// Garder les pts dans le sens horlogique.
				tOut1=2;	// Point sortant 1
				tOut2=0;	// Point sortant 2
				tIn=1;		// Point intérieur 
				// On doit découper....
				boCut=D_TRUE;
			}

			// Découpe.
			if (boCut)
			{
				// Checker si on a la place (1 triangle)
				if (tNbDestVec+CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS>=tMaxDestVec)
				{
					D_ERROR(E_ERROR_SPRSHADOW_OVERFLOW,"No more room for vector");
				}

				// Mise à jour out1,out2,in
				tOut1+=tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS;
				tOut2+=tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS;
				tIn+=tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS;
				
				// Découper segment out1-in
				D_CUTSEG(cpClipRect_p->tY1,tOut1,tIn,cTmpPosVec[0],cTmpTexVec[0],*tpY_m,*tpX_m)
				// Découper segment out2-in
				D_CUTSEG(cpClipRect_p->tY1,tOut2,tIn,cTmpPosVec[1],cTmpTexVec[1],*tpY_m,*tpX_m)

				// Ajout triangle.
				D_ADDVECDEST(cTmpPosVec[0],cTmpTexVec[0]);
				D_ADDVECDEST(cTmpPosVec[1],cTmpTexVec[1]);
				D_ADDVECDESTFROMINDEX(tIn);
			}
		}


	}			

	// Source: cpDestVec..+tDoubleBufDestVec 
	// Dest  : cpDestVec

	cpPosSrcVec=cpPosDestVec_p+tDoubleBufDestVec;
	cpTexSrcVec=cpTexDestVec_p+tDoubleBufDestVec;
	tNbSrcVec=tNbDestVec;

	cpPosDestVec=cpPosDestVec_p;
	cpTexDestVec=cpTexDestVec_p;
	tNbDestVec=0;

	// Parcourir les triangles sortant en x+

	for (tCurTri=0;tCurTri<tNbSrcVec/CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS;tCurTri++)
	{

		
		// Pas de découpe
		boCut=D_FALSE;

		// Récup des ptrs sur les vecteurs
		cpPosPt0=&cpPosSrcVec[tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS+0];
		cpPosPt1=&cpPosSrcVec[tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS+1];
		cpPosPt2=&cpPosSrcVec[tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS+2];

		// Si les 3 points sortent, on continue
		if (cpPosPt0->*tpY_m>cpClipRect_p->tY2 && cpPosPt1->*tpY_m>cpClipRect_p->tY2 && cpPosPt2->*tpY_m>cpClipRect_p->tY2)
		{
			continue;
		}
	
		// Triangle non clippé?
		if (cpPosPt0->*tpY_m<=cpClipRect_p->tY2 && cpPosPt1->*tpY_m<=cpClipRect_p->tY2 && cpPosPt2->*tpY_m<=cpClipRect_p->tY2)
		{
			// Checker si on a la place (1 triangle)
			if (tNbDestVec+CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS>=tMaxDestVec)
			{
				D_ERROR(E_ERROR_SPRSHADOW_OVERFLOW,"No more room for vector");
			}

			// Ajout des vecteurs
			D_ADDVECDESTFROMINDEX(tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS+0);
			D_ADDVECDESTFROMINDEX(tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS+1);
			D_ADDVECDESTFROMINDEX(tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS+2);
			continue;
		}

		
		// 1 point sortant: 0
		if (cpPosPt0->*tpY_m>cpClipRect_p->tY2 && cpPosPt1->*tpY_m<=cpClipRect_p->tY2 && cpPosPt2->*tpY_m<=cpClipRect_p->tY2)
		{
			// Garder les pts dans le sens horlogique.
			tOut=0;	// Point sortant
			tIn1=1;	// Point intérieur 1 
			tIn2=2; // Point intérieur 2
			// On doit découper....
			boCut=D_TRUE;
		}
		else
		// 1 point sortant: 1
		if (cpPosPt1->*tpY_m>cpClipRect_p->tY2 && cpPosPt2->*tpY_m<=cpClipRect_p->tY2 && cpPosPt0->*tpY_m<=cpClipRect_p->tY2)
		{
			// Garder les pts dans le sens horlogique.
			tOut=1;	// Point sortant
			tIn1=2;	// Point intérieur 1 
			tIn2=0; // Point intérieur 2
			// On doit découper....
			boCut=D_TRUE;
		}
		else
		// 1 point sortant: 2
		if (cpPosPt2->*tpY_m>cpClipRect_p->tY2 && cpPosPt0->*tpY_m<=cpClipRect_p->tY2 && cpPosPt1->*tpY_m<=cpClipRect_p->tY2)
		{
			// Garder les pts dans le sens horlogique.
			tOut=2;	// Point sortant
			tIn1=0;	// Point intérieur 1 
			tIn2=1; // Point intérieur 2
			// On doit découper....
			boCut=D_TRUE;
		}

		// Découpe.
		if (boCut)
		{
			// Checker si on a la place (2 triangles)
			if (tNbDestVec+CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS*2>=tMaxDestVec)
			{
				D_ERROR(E_ERROR_SPRSHADOW_OVERFLOW,"No more room for vector");
			}

			// Mise à jour out,in1,in2
			tOut+=tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS;
			tIn1+=tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS;
			tIn2+=tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS;

			// Découper segment out-in1
			D_CUTSEG(cpClipRect_p->tY2,tOut,tIn1,cTmpPosVec[0],cTmpTexVec[0],*tpY_m,*tpX_m)
			// Découper segment out-in2
			D_CUTSEG(cpClipRect_p->tY2,tOut,tIn2,cTmpPosVec[1],cTmpTexVec[1],*tpY_m,*tpX_m)

			// Ajout triangle 1
			D_ADDVECDEST(cTmpPosVec[0],cTmpTexVec[0]);
			D_ADDVECDESTFROMINDEX(tIn1);
			D_ADDVECDESTFROMINDEX(tIn2);

			// Ajout triangle 2
			D_ADDVECDESTFROMINDEX(tIn2);
			D_ADDVECDEST(cTmpPosVec[1],cTmpTexVec[1]);
			D_ADDVECDEST(cTmpPosVec[0],cTmpTexVec[0]);
		}
		else
		{
			// 2 points sortant: 0 1
			if (cpPosPt0->*tpY_m>cpClipRect_p->tY2 && cpPosPt1->*tpY_m>cpClipRect_p->tY2 && cpPosPt2->*tpY_m<=cpClipRect_p->tY2)
			{
				// Garder les pts dans le sens horlogique.
				tOut1=0;	// Point sortant 1
				tOut2=1;	// Point sortant 2
				tIn=2;		// Point intérieur 
				// On doit découper....
				boCut=D_TRUE;
			}
			else
			// 2 points sortant: 1 2
			if (cpPosPt1->*tpY_m>cpClipRect_p->tY2 && cpPosPt2->*tpY_m>cpClipRect_p->tY2 && cpPosPt0->*tpY_m<=cpClipRect_p->tY2)
			{
				// Garder les pts dans le sens horlogique.
				tOut1=1;	// Point sortant 1
				tOut2=2;	// Point sortant 2
				tIn=0;		// Point intérieur 
				// On doit découper....
				boCut=D_TRUE;
			}
			else
			// 2 points sortant: 2 0
			if (cpPosPt2->*tpY_m>cpClipRect_p->tY2 && cpPosPt0->*tpY_m>cpClipRect_p->tY2 && cpPosPt1->*tpY_m<=cpClipRect_p->tY2)
			{
				// Garder les pts dans le sens horlogique.
				tOut1=2;	// Point sortant 1
				tOut2=0;	// Point sortant 2
				tIn=1;		// Point intérieur 
				// On doit découper....
				boCut=D_TRUE;
			}

			// Découpe.
			if (boCut)
			{
				// Checker si on a la place (1 triangle)
				if (tNbDestVec+CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS>=tMaxDestVec)
				{
					D_ERROR(E_ERROR_SPRSHADOW_OVERFLOW,"No more room for vector");
				}

				// Mise à jour out1,out2,in
				tOut1+=tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS;
				tOut2+=tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS;
				tIn+=tCurTri*CTrianglePrim::D_PUBLICCONST_NBTRIANGLEPTS;
				
				// Découper segment out1-in
				D_CUTSEG(cpClipRect_p->tY2,tOut1,tIn,cTmpPosVec[0],cTmpTexVec[0],*tpY_m,*tpX_m)
				// Découper segment out2-in
				D_CUTSEG(cpClipRect_p->tY2,tOut2,tIn,cTmpPosVec[1],cTmpTexVec[1],*tpY_m,*tpX_m)

				// Ajout triangle.
				D_ADDVECDEST(cTmpPosVec[0],cTmpTexVec[0]);
				D_ADDVECDEST(cTmpPosVec[1],cTmpTexVec[1]);
				D_ADDVECDESTFROMINDEX(tIn);
			}
		}
	}			

	// Nombre de vecteurs destination
	*tpMaxDestVec_p=tNbDestVec;

} // CSprShadow::ClipTriangleWithRect


