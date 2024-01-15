#include "ZoneView.h"


/*
 *	CZoneView::CZoneView
 */
CZoneView::CZoneView():
	cpZoneItem_m(cpZoneItem0_m)
{
	for(T_UWORD uw=0;uw<E_ZONEVIEW_SIZE;uw++)
	{
		cpZoneItem0_m[uw].cpZoneInst_m=0;
		cpZoneItem1_m[uw].cpZoneInst_m=0;
	}
} /* CZoneView::~CZoneView */


/*
 *	CZoneView::~CZoneView
 */
CZoneView::~CZoneView()
{
	FlipRelease();
} /* CZoneView::~CZoneView */


/*
 *	CZoneView::Update
 */
void CZoneView::Update(CWorld* cpWorld_p,T_FLOAT fXC_p,T_FLOAT fYC_p)
{
	FlipRelease();

	for(T_FLOAT fY=-512.0f;fY<=512.0f;fY+=256.0f)
		for(T_FLOAT fX=-512.0f;fX<=512.0f;fX+=256.0f)
			Set(cpWorld_p,fXC_p+fX,fYC_p+fY+128);
/*
	Set(cpWorld_p,fXC_p-256,fYC_p-256);
	Set(cpWorld_p,fXC_p,fYC_p-256);
	Set(cpWorld_p,fXC_p+256,fYC_p-256);

	Set(cpWorld_p,fXC_p-256,fYC_p);
	Set(cpWorld_p,fXC_p,fYC_p);
	Set(cpWorld_p,fXC_p+256,fYC_p);

	Set(cpWorld_p,fXC_p-256,fYC_p+256);
	Set(cpWorld_p,fXC_p,fYC_p+256);
	Set(cpWorld_p,fXC_p+256,fYC_p+256);
*/
	cBlocView_m.Update(cpWorld_p,fXC_p,fYC_p);
} /* CZoneView::Update */


/*
 *	CZoneView::Draw
 */
void CZoneView::Draw()
{
	for(T_UWORD uw=0;uw<E_ZONEVIEW_SIZE;uw++)
	{
		if(cpZoneItem_m[uw].cpZoneInst_m==0)
			break;
		cpZoneItem_m[uw].Draw();
	}
	cBlocView_m.Draw();
} /* CZoneView::Draw */


/*
 *	CZoneView::FlipRelease
 */
void CZoneView::FlipRelease()
{
	if(cpZoneItem_m==cpZoneItem0_m)
		cpZoneItem_m=cpZoneItem1_m;
	else
		cpZoneItem_m=cpZoneItem0_m;

	for(T_UWORD uw=0;uw<E_ZONEVIEW_SIZE;uw++)
	{
		if(cpZoneItem_m[uw].cpZoneInst_m==0)
			break;
		cpZoneItem_m[uw].cpZoneInst_m->Release();
		cpZoneItem_m[uw].cpZoneInst_m=0;
	}
} /* CZoneView::FlipRelease */


/*
 *	CZoneView::Set
 */
void CZoneView::Set(CWorld* cpWorld_p,T_FLOAT fX_p,T_FLOAT fY_p)
{
	CZoneInst* cpZoneInst=cpWorld_p->GetZoneInst(fX_p,fY_p);
	if(cpZoneInst==0)
		return;

	T_UWORD uw;
	// Check si ZoneItem existe déja dans le slot
	for(uw=0;uw<E_ZONEVIEW_SIZE;uw++)
	{
		if(cpZoneItem_m[uw].cpZoneInst_m==cpZoneInst)
			break;
	}
	// S'il n'existe pas en slot
	if(uw==E_ZONEVIEW_SIZE)
	{
		// Trouve premier slot de libre
		for(uw=0;uw<E_ZONEVIEW_SIZE;uw++)
		{
			if(cpZoneItem_m[uw].cpZoneInst_m==0)
				break;
		}
		if(uw==E_ZONEVIEW_SIZE)
			throw "CZoneView - Aucun slot de ZoneItem libre";

		cpZoneItem_m[uw].cpZoneInst_m=cpZoneInst;
	}
	cpZoneInst->AddRef();
} /* CZoneView::Set */


