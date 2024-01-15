#include "BlocView.h"


/*
 *	CBlocView::CBlocView
 */
CBlocView::CBlocView():
	cpBlocItem_m(cpBlocItem0_m)
{
} /* CBlocView::CBlocView */


/*
 *	CBlocView::Update
 */
void CBlocView::Update(CWorld* cpWorld_p,T_FLOAT fXC_p,T_FLOAT fYC_p)
{
	if(cpBlocItem_m==cpBlocItem0_m)
		cpBlocItem_m=cpBlocItem1_m;
	else
		cpBlocItem_m=cpBlocItem0_m;

	T_UWORD uw=0;
	// 25 BlocItems

	for(T_FLOAT fY=-512.0f;fY<=512.0f;fY+=256.0f)
		for(T_FLOAT fX=-512.0f;fX<=512.0f;fX+=256.0f,uw++)
			Set(cpWorld_p,uw,fXC_p+fX,fYC_p+fY+128);

/*
	Set(cpWorld_p,0,fXC_p-256,fYC_p-256);
	Set(cpWorld_p,1,fXC_p,fYC_p-256);
	Set(cpWorld_p,2,fXC_p+256,fYC_p-256);

	Set(cpWorld_p,3,fXC_p-256,fYC_p);
	Set(cpWorld_p,4,fXC_p,fYC_p);
	Set(cpWorld_p,5,fXC_p+256,fYC_p);

	Set(cpWorld_p,6,fXC_p-256,fYC_p+256);
	Set(cpWorld_p,7,fXC_p,fYC_p+256);
	Set(cpWorld_p,8,fXC_p+256,fYC_p+256);
*/
} /* CBlocView::Update */


/*
 *	CBlocView::Draw
 */
void CBlocView::Draw()
{
	T_UWORD uw;
	for(uw=0;uw<E_BLOCVIEW_SIZE2;uw++)
		cpBlocItem_m[uw].Draw();
} /* CBlocView::Draw */


/*
 *	CBlocView::Set
 */
void CBlocView::Set(CWorld* cpWorld_p,T_UWORD uwIndex_p,T_FLOAT fX_p,T_FLOAT fY_p)
{
	CZoneInst* cpZoneInst=cpWorld_p->GetZoneInst(fX_p,fY_p);
	CBlocInst* cpBlocInst=(cpZoneInst!=0)?cpZoneInst->GetBlocInst(fX_p,fY_p):0;
	cpBlocItem_m[uwIndex_p].Set(cpZoneInst,cpBlocInst);
} /* CBlocView::Set */


