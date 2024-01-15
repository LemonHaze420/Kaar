#ifndef _INCLUDE_REF_
#define _INCLUDE_REF_


/*
 *	CRef
 */
class CRef
{
public:
	CRef()
	{
		lRef_m=0;
	}

	void AddRef()
	{
		if(lRef_m==0)
			Init();

		lRef_m++;
	}
	void Release()
	{
		lRef_m--;

		if(lRef_m==0)
			Shut();
	}

private:
	T_LONG lRef_m;

	virtual void Init()=0;
	virtual void Shut()=0;
}; /* CRef */


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif


