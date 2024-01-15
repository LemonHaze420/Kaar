#ifndef _INCLUDE_MODEL_
#define _INCLUDE_MODEL_
/**************************************************************************************
 *
 **************************************************************************************/
#include "System.h"
#include "Ref.h"


class CModel:public CRef
{
public:
	enum EModelRace
	{
		E_MODEL_HUMAN=0x00,
		E_MODEL_NOMAREG=0x01,
		E_MODEL_UERG=0x02,
		E_MODEL_ANIMAL=0x03
	};
	EModelRace eRace_m;
	char* chpIcon_m;
	char* chpMesh_m;
	char* chpTexture_m;
	char* chpMovie_m;
	char* chpIA_m;

	T_WORD wLife_m;
	T_UWORD uwTireness_m;
	T_WORD wAltitude_m;		// De 0 à 256 /64
	T_3DVALUE tRadius_m;
	T_3DVALUE tXMax_m;
	T_3DVALUE tYMax_m;
	T_3DVALUE tXMin_m;
	T_3DVALUE tYMin_m;

	CMeshObj* cpMeshObj_m;
	CBmFrameObj* cpTexture_m;
	CBmFrameObj* cpIcon_m;
	CBmFrameObj* cpMovie_m;


	CModel();
	CModel(EModelRace eRace_p,
		char* chpIcon_p,
		char* chpMesh_p,
		char* chpTexture_p,
		char* chpMovie_p,
		char* chpIA_p,
		T_WORD wAltitude_p,
		T_WORD wLife_p,
		T_UWORD uwTireness_p);
	~CModel();

	CModel& operator=(CModel& crModel_p);

private:
	// Virtual pure de CRef
	virtual void Init();
	virtual void Shut();
	void GetRadius();
};


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif

