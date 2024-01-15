// -------------------------------------------------------------------------------
// -------------------------------------------------------------------------------
// -------------------------------------------------------------------------------
// -------------------------------------------------------------------------------
// -------------------------------------------------------------------------------
//
//		Purpose:
//			This file provide declaration of a simple shadow caster class
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

#ifndef _INCLUDE_CRSPRSHA_
#define _INCLUDE_CRSPRSHA_

// Interfaces
#include "INTHEA\MESHDRV.H"

// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
// Définition du groupe d'erreur associé à la classe CSprShadow
// Ce numéro de groupe DOIT ETRE DEFINI PAR L'APPLI MAITRE,
// il figure ici à titre d'exemple.
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
enum ECustomErrorGroup
{
	E_ERRORGROUP_SPRSHADOW = E_ERRORGROUP_USER,
};
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------

// Codes d'erreur
#include "CREHSPSH.H"

// Ajout d'un vec / à index
#define D_ADDVECDESTFROMINDEX(ind)\
	{\
		cpPosDestVec[tNbDestVec]=cpPosSrcVec[ind];\
		cpTexDestVec[tNbDestVec]=cpTexSrcVec[ind];\
		tNbDestVec++;\
	}

// Ajout d'un vec
#define D_ADDVECDEST(vecpos,vectex)\
	{\
		cpPosDestVec[tNbDestVec]=vecpos;\
		cpTexDestVec[tNbDestVec]=vectex;\
		tNbDestVec++;\
	}

// Découpe d'un segment 
#define D_CUTSEG(clipx,s1,s2,posvec,texvec,px,py)\
	{\
		tTmpVal=(clipx-cpPosSrcVec[s1].px)/(cpPosSrcVec[s2].px-cpPosSrcVec[s1].px);\
		posvec.px=clipx;\
		posvec.py=\
			cpPosSrcVec[s1].py+\
			(cpPosSrcVec[s2].py-cpPosSrcVec[s1].py)*tTmpVal;\
		posvec.*tpZ_m=\
			cpPosSrcVec[s1].*tpZ_m+\
			(cpPosSrcVec[s2].*tpZ_m-cpPosSrcVec[s1].*tpZ_m)*tTmpVal;\
		texvec.tZ=0;\
		texvec.tX=\
			cpTexSrcVec[s1].tX+\
			(cpTexSrcVec[s2].tX-cpTexSrcVec[s1].tX)*tTmpVal;\
		texvec.tY=\
			cpTexSrcVec[s1].tY+\
			(cpTexSrcVec[s2].tY-cpTexSrcVec[s1].tY)*tTmpVal;\
	}

// Gestionnaire de shadow 
class CSprShadow
{

	public:

		// Constructeur
											CSprShadow(T_VOID);


		// Préparation au calcul des shadow (appel lors de chaque boucle).
		T_VOID								Prepare(T_VOID);

		// Ajout des primitive de l'ensemble des shadows
		T_VOID								AddPrims(CRenderCtx *cpCtx_p);

		// Calcul d'une shadow
		T_VOID								ComputeShadow(
												CMath *cpMath_p,									// Objet math à utiliser
												CBmFrameObj *cpFrameObj_p,							// Ptr sur framefile
												T_INDEX tObjNum_p,									// Numéro d'objet
												T_INDEX tAnimNum_p,									// Numéro d'animation
												T_INDEX tFrameNum_p,								// Numéro de frame
												const CPt<T_3DVALUE> *cpShadPos_p,					// Position de la shadow
												T_3DVALUE tShadSize_p,								// Taille de la shadow
												CMeshObj *cpMeshToMap_p,							// Mesh à mapper
												const CVector<T_3DVALUE> *cpShiftPos_p,				// Valeur ajoutée à chaque coord
												T_MATHANVALUE tAnZ_p);								// Angle de rotation shad

		// Mise à jour des ptrs sur membres
		inline T_VOID						SetMemberPtrs(
												T_3DVALUE CVector<T_3DVALUE>::*tpX_p,
												T_3DVALUE CVector<T_3DVALUE>::*tpY_p,
												T_3DVALUE CVector<T_3DVALUE>::*tpZ_p)
		{
			tpX_m=tpX_p;
			tpY_m=tpY_p;
			tpZ_m=tpZ_p;
		}
												
	private:

		// Constantes privées
		enum DPrivateConst
		{
			// Nombre de primitives max
			D_PRIVATECONST_MAXPRIMNUM =		1600,
			
			// Nombre de vertex max
			D_PRIVATECONST_MAXVERTNUM =		3200,

			// Nombre de vecteur (pos et texture) max
			D_PRIVATECONST_MAXVECNUM =		3200,

		};

		// Ratio pour utilisation uvs
		const static T_MATHVALUE			tUVRatio_m;

		// Primitives
		CTrianglePrim						cpPrim_m[D_PRIVATECONST_MAXPRIMNUM];

		// Nombre courant de primitives 
		T_CARD								tNbPrim_m;

		// Vecteurs position et texture
		CVector<T_3DVALUE>					cpPosVec_m[D_PRIVATECONST_MAXVECNUM];
		CVector<T_3DVALUE>					cpTexVec_m[D_PRIVATECONST_MAXVECNUM];

		// Nombre courant de vecteurs position et texture
		T_CARD								tNbPosVec_m;
		T_CARD								tNbTexVec_m;

		// Vertex
		CVertex								cpVertex_m[D_PRIVATECONST_MAXVERTNUM];

		// Nombre courant de vertex
		T_CARD								tNbVertex_m;

		// Ptr sur membres
		T_3DVALUE							CVector<T_3DVALUE>::*tpX_m;
		T_3DVALUE							CVector<T_3DVALUE>::*tpY_m;
		T_3DVALUE							CVector<T_3DVALUE>::*tpZ_m;

		// Effectue le clipping d'un triangle en fonction d'une zone rectangulaire
		T_VOID								ClipTriangleWithRect(
													CVector<T_3DVALUE> *cpPosSrcTri_p,				// Triangle source (pos)
													CVector<T_3DVALUE> *cpTexSrcTri_p,				// Triangle source (tex)
													const CRectangle<T_3DVALUE> *cpClipRect_p,		// Zone de clip
													CVector<T_3DVALUE> *cpPosDestVec_p,				// Vec pos dest
													CVector<T_3DVALUE> *cpTexDestVec_p,				// Vec tex dest
													T_CARD *tpMaxDestVec_p							// Nbre max de vec dest (et retour nbre de vec)
												);




};

#endif // _INCLUDE_CRSPRSHA_
