#ifndef _INCLUDE_LIST_
#define _INCLUDE_LIST_
/**************************************************************************************
 *	Redéfinition de l'opérateur = OBLIGATOIRE pour toute utilisation du template
 **************************************************************************************/

 
/*
 *	CList
 */
template<class T>class CList
{
public:
	enum EListInsert
	{
		E_LIST_INSERTHEAD,
		E_LIST_INSERTQUEUE
	};
	class CItem
	{
	public:
		T* cp_m;
		CItem* cpNext_m;

		CItem(T* cp_p):
			cpNext_m(0),
			cp_m(cp_p)
		{
		}
		~CItem()
		{
			DELETE cp_m;
		}
	};
	CItem* cpHead_m;
	CItem* cpQueue_m;
	CItem* cpFind_m;
	T_ULONG ulNbItem_m;

	CList():
		cpHead_m(0),
		cpQueue_m(0),
		cpFind_m(0),
		ulNbItem_m(0)
	{
	}
	~CList()
	{
		Delete();
	}

	void Delete()
	{
		while(cpHead_m!=0)
		{
			CItem* cpItemList=cpHead_m;
			cpHead_m=cpHead_m->cpNext_m;
			DELETE cpItemList;
		}
		cpQueue_m=0;
		ulNbItem_m=0;
	}

	void Delete(T* cp_p)
	{
		CItem* cpItemList=cpHead_m;
		CItem* cpPrev=0;
		while(cpItemList!=0)
		{
			if(cpItemList->cp_m==cp_p)
			{
				if(cpPrev==0)
					cpHead_m=cpItemList->cpNext_m;
				else
					cpPrev->cpNext_m=cpItemList->cpNext_m;
				
				DELETE cpItemList;
				ulNbItem_m--;
				return;
			}
			cpPrev=cpItemList;
			cpItemList=cpItemList->cpNext_m;
		}
	}


	T* Insert(T& cr_p,EListInsert eHead_p=E_LIST_INSERTHEAD)
	{
		T* cp=NEW T;
		*cp=cr_p;

		// Si liste vide
		if(cpHead_m==0)
		{
			cpQueue_m=cpHead_m=NEW CItem(cp);
		}
		// Sinon tête de liste
		else if(eHead_p==E_LIST_INSERTHEAD)
		{
			CItem* cpItemList=cpHead_m;

			cpHead_m=NEW CItem(cp);
			cpHead_m->cpNext_m=cpItemList;
		}
		// Sinon queue de liste
		else
		{
			cpQueue_m=cpQueue_m->cpNext_m=NEW CItem(cp);
		}
		ulNbItem_m++;
		return cp;
	}

	T* ConvertToArray()
	{
		if(ulNbItem_m==0)
			return 0;
		// Converti liste en tableau
		T* cpArray=NEW T[ulNbItem_m];
		CItem* cpItemList=cpHead_m;

		for(T_ULONG ul=0;ul<ulNbItem_m;ul++)
		{
			// = transforme un élmnt de liste en élmnt de tableau
			cpArray[ul]=*cpItemList->cp_m;

			CItem* cpItem=cpItemList;
			cpItemList=cpItemList->cpNext_m;
		}
		return cpArray;
	}

	T* FindFirst()
	{
		cpFind_m=cpHead_m;
		if(cpFind_m==0)
			return 0;
		return cpFind_m->cp_m;
	}
	T* FindNext()
	{
		if(cpFind_m==0)
			return 0;
		cpFind_m=cpFind_m->cpNext_m;
		if(cpFind_m==0)
			return 0;
		return cpFind_m->cp_m;
	}

	CList& operator=(CList& crList_p)
	{
		for(T* cp=crList_p.FindFirst();cp!=0;cp=crList_p.FindNext())
			this->Insert(*cp,E_LIST_INSERTQUEUE);
		return *this;
	}

}; /* CList */


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif


