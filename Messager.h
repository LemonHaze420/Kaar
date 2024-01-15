#ifndef _INCLUDE_MESSAGER_
#define _INCLUDE_MESSAGER_
/**************************************************************************************
 * 
 **************************************************************************************/


/*
 *	CMessager
 */
class CMessager
{
public:
	enum EMessagerMsg
	{
		E_MESSAGER_NEWCHARACTER,
		E_MESSAGER_DELCHARACTER,
		E_MESSAGER_RENDERCLICK1,
		E_MESSAGER_RENDERCLICK2,
		E_MESSAGER_INTERFACECLICK1,
		E_MESSAGER_INTERFACECLICK2
	};

	static void Send(EMessagerMsg eMsg_p,void* cpParam_p=0);
}; /* CMessager */


#endif


// Compiler specific & compatible optimisation
#if _MSC_VER>1000
#pragma once
#endif

