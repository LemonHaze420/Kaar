#include "Univers.h"
#include "Character.h"


CGroup* CUnivers::cpGroup_m;
T_UWORD CUnivers::uwNbGroup_m;
CZone* CUnivers::cpZone_m;
T_UWORD CUnivers::uwNbZone_m;
CWorld* CUnivers::cpWorld_m;
T_UWORD CUnivers::uwNbWorld_m;
CModel* CUnivers::cpModel_m;
T_UWORD CUnivers::uwNbModel_m;
CPath* CUnivers::cpPath_m;
T_UWORD CUnivers::uwNbPath_m;

const char CUnivers::chpDelimit_m[]=" ,*=:\t\n\r";


/*
 *	CUnivers::CUnivers
 */
CUnivers::CUnivers(char *chpName_p)
{
	cpGroup_m=0;
	cpZone_m=0;
	cpWorld_m=0;
	cpModel_m=0;
	cpPath_m=0;
	// Load script
	CStdStr cName(chpName_p);
	T_LONG lSize;
	CSystem::cpFileCtx_m->FileSize(cName,&lSize);
	char* chpScript=NEW char[lSize+1];
	CSystem::cpFileCtx_m->FileLoadAt(cName,(void*)chpScript);
	chpScript[lSize]='\x0';
	_strupr(chpScript);

	// Parse script
	if(strcmp(strtok(chpScript,chpDelimit_m),"UNIVERS")!=0)
		throw "Script: Univers definition - Missing Univers keyword";
	if(strcmp(strtok(NULL,chpDelimit_m),"{")!=0)
		throw "Script: Univers definition - Missing {";

	
	char* chpToken;
	if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"}")==0)
		throw "Script: Univers definition - Missing Group description";
	T_UWORD uwIndex=atoi(chpToken);
	chpToken=strtok(NULL,chpDelimit_m);

	if(strcmp(chpToken,"GROUP")!=0)
		throw "Script: Univers definition - Missing Group description";
	uwNbGroup_m=0;
	do
	{
		GetGroup(uwIndex);

		if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"}")==0)
			throw "Script: Univers definition - Missing Zone description";
		uwIndex=atoi(chpToken);
		chpToken=strtok(NULL,chpDelimit_m);
	}
	while(strcmp(chpToken,"GROUP")==0);
	cpGroup_m=cListGroup_m.ConvertToArray();
	cListGroup_m.Delete();


	if(strcmp(chpToken,"ZONE")!=0)
		throw "Script: Univers definition - Missing Zone description";
	uwNbZone_m=0;
	do
	{
		GetZone(uwIndex);

		if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"}")==0)
			throw "Script: Univers definition - Missing Model description";
		uwIndex=atoi(chpToken);
		chpToken=strtok(NULL,chpDelimit_m);
	}
	while(chpToken && strcmp(chpToken,"ZONE")==0);
	cpZone_m=cListZone_m.ConvertToArray();
	cListZone_m.Delete();


	if(strcmp(chpToken,"MODEL")!=0)
		throw "Script: Univers definition - Missing Model description";
	uwNbModel_m=0;
	do
	{
		GetModel(uwIndex);

		if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"}")==0)
			throw "Script: Univers definition - Missing Path description";
		uwIndex=atoi(chpToken);
		chpToken=strtok(NULL,chpDelimit_m);
	}
	while(chpToken && strcmp(chpToken,"MODEL")==0);
	cpModel_m=cListModel_m.ConvertToArray();
	cListModel_m.Delete();


	if(strcmp(chpToken,"PATH")!=0)
		throw "Script: Univers definition - Missing Path description";
	uwNbPath_m=0;
	do
	{
		GetPath(uwIndex);

		if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"}")==0)
			throw "Script: Univers definition - Missing World description";
		uwIndex=atoi(chpToken);
		chpToken=strtok(NULL,chpDelimit_m);
	}
	while(chpToken && strcmp(chpToken,"PATH")==0);
	cpPath_m=cListPath_m.ConvertToArray();
	cListPath_m.Delete();


	if(!chpToken || strcmp(chpToken,"WORLD")!=0)
		throw "Script: Univers definition - Missing World description";
	uwNbWorld_m=0;
	do
	{
		GetWorld(uwIndex);

		if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"}")==0)
			break;
		uwIndex=atoi(chpToken);
		chpToken=strtok(NULL,chpDelimit_m);
	}
	while(chpToken && strcmp(chpToken,"WORLD")==0);
	cpWorld_m=cListWorld_m.ConvertToArray();
	cListWorld_m.Delete();

	if(!chpToken || strcmp(chpToken,"}")!=0)
		throw "Script: Univers definition - Missing }";

	DELETE []chpScript;

	InitCell();
} /* CUnivers::CUnivers */


/*
 *	CUnivers::~CUnivers
 */
CUnivers::~CUnivers()
{
	DELETE []cpGroup_m;
	DELETE []cpZone_m;
	DELETE []cpModel_m;
	DELETE []cpPath_m;
	DELETE []cpWorld_m;
} /* CUnivers::~CUnivers */


/*
 *	CUnivers::GetGroup
 */
void CUnivers::GetGroup(T_UWORD uwIndex_p)
{
	if(uwIndex_p!=uwNbGroup_m++)
		throw "Script: Group definition - Bad Group index number";

	char* chpToken;
	if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"{")==0)
		throw "Script: Group definition - Missing texture resource filename";

	if(strcmp(strtok(NULL,chpDelimit_m),"{")!=0)
		throw "Script: Group definition - Missing {";

	CGroup* cpGroup=cListGroup_m.Insert(CGroup(chpToken),CList<CGroup>::E_LIST_INSERTQUEUE);

	cpGroup->uwNbBloc_m=0;
	cpGroup->uwNbLand_m=0;
	while((chpToken=strtok(NULL,chpDelimit_m)) && strcmp(chpToken,"}")!=0)
	{
		T_UWORD uwIndex=atoi(chpToken);
		chpToken=strtok(NULL,chpDelimit_m);
		if(strcmp(chpToken,"BLOC")==0)
			GetBloc(cpGroup,uwIndex);
		else if(strcmp(chpToken,"LAND")==0)
			GetLand(cpGroup,uwIndex);
		else
			throw "Script: Group definition - Missing Bloc or Land definition";
	}
	if(chpToken==NULL)
		throw "Script: Group definition - Missing }";

	cpGroup->cpBloc_m=cpGroup->cListBloc_m.ConvertToArray();
	cpGroup->cListBloc_m.Delete();
	cpGroup->cpLand_m=cpGroup->cListLand_m.ConvertToArray();
	cpGroup->cListLand_m.Delete();
} /* CUnivers::GetGroup */


/*
 *	CUnivers::GetBloc
 */
void CUnivers::GetBloc(CGroup* cpGroup_p,T_UWORD uwIndex_p)
{
	if(uwIndex_p!=cpGroup_p->uwNbBloc_m++)
		throw "Script: Bloc definition - Bad Bloc index number";

	char *chpToken;
	if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"}")==0)
		throw "Script: Bloc definition - Missing mesh filename";

	cpGroup_p->cListBloc_m.Insert(CBloc(chpToken,uwIndex_p),CList<CBloc>::E_LIST_INSERTQUEUE);
} /* CUnivers::GetBloc */


/*
 *	CUnivers::GetLand
 */
void CUnivers::GetLand(CGroup* cpGroup_p,T_UWORD uwIndex_p)
{
	if(uwIndex_p!=cpGroup_p->uwNbLand_m++)
		throw "Script: Land definition - Bad Land index number";

	char *chpToken;
	if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"}")==0)
		throw "Script: Land definition - Missing mesh filename";

	if(strcmp(chpToken,"ODRC_002")==0)
		cpGroup_p->cListLand_m.Insert(CLand(chpToken,cpGroup_p->uwNbBloc_m+uwIndex_p,CLand::E_LANDINST_FUMES),CList<CLand>::E_LIST_INSERTQUEUE);
	else if(strcmp(chpToken,"ODRC_005")==0 || strcmp(chpToken,"ODRC_006")==0 || strcmp(chpToken,"ODRC_009")==0)
		cpGroup_p->cListLand_m.Insert(CLand(chpToken,cpGroup_p->uwNbBloc_m+uwIndex_p,CLand::E_LANDINST_SMALLFUMES),CList<CLand>::E_LIST_INSERTQUEUE);
	else
		cpGroup_p->cListLand_m.Insert(CLand(chpToken,cpGroup_p->uwNbBloc_m+uwIndex_p),CList<CLand>::E_LIST_INSERTQUEUE);
} /* CUnivers::GetLand */


/*
 *	CUnivers::GetZone
 */
void CUnivers::GetZone(T_UWORD uwIndex_p)
{
	if(uwIndex_p!=uwNbZone_m++)
		throw "Script: Zone definition - Bad Zone index number";
	if(strcmp(strtok(NULL,chpDelimit_m),"{")!=0)
		throw "Script: Zone definition - Missing {";

	CZone* cpZone=cListZone_m.Insert(CZone(),CList<CZone>::E_LIST_INSERTQUEUE);

	// Récupération de la valeur symbole clé de group
	char *chpToken;
	if(strcmp(strtok(NULL,chpDelimit_m),"¤")!=0)
		throw "Script: Zone definition - Missing ¤ keyword";
	if(strcmp(chpToken=strtok(NULL,chpDelimit_m),"GROUP")!=0)
		throw "Script: Zone definition - Missing Group keyword";

	cpZone->cpGroupA_m=&cpGroup_m[atoi(strtok(NULL,chpDelimit_m))];

	if(strcmp(strtok(NULL,chpDelimit_m),"§")!=0)
		throw "Script: Zone definition - Missing § keyword";
	if(strcmp(chpToken=strtok(NULL,chpDelimit_m),"GROUP")!=0)
	{
		if(strcmp(chpToken,"NOGROUP")!=0)
			throw "Script: Zone definition - Missing Group/NoGroup keyword";
		cpZone->cpGroupB_m=0;
	}
	else
		cpZone->cpGroupB_m=&cpGroup_m[atoi(strtok(NULL,chpDelimit_m))];

	// Création de la définition bloc de la zone
	T_UWORD uw=0;
	for(T_UWORD uwY=0;uwY<CZone::E_ZONE_SIZE;uwY++)
		for(T_UWORD uwX=0;uwX<CZone::E_ZONE_SIZE;uwX++,uw++)
		{
			if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"}")==0)
				throw "Script: Zone definition - Missing Bloc index number";
			CGroup* cpGroup=(chpToken[0]=='¤'?cpZone->cpGroupA_m:cpZone->cpGroupB_m);
			if(cpGroup==0)
				throw "Script: Zone definition - Group § not defined";
			chpToken++;
			T_UWORD uwIndex=atoi(chpToken);
			if(uwIndex>=cpGroup->uwNbBloc_m)
				throw "Script: Zone definition - Bad Bloc index";

			if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"}")==0)
				throw "Script: Zone definition - Missing Bloc altitude";

			cpZone->cpBlocPos_m[uw].Set(uwX,uwY,atoi(chpToken));
			cpZone->cppBloc_m[uw]=&cpGroup->cpBloc_m[uwIndex];
		}

	if(!(chpToken=strtok(NULL,chpDelimit_m)))
		throw "Script: Zone definition - Missing }";

	cpZone->uwNbSet_m=0;
	// Si pas de } création des sets de land
	while(strcmp(chpToken,"}")!=0)
	{
		if(strlen(chpToken)!=1 || chpToken[0]<'A' || chpToken[0]>'Z')
			throw "Script: Zone definition - Missing/bad Set index (A-Z)";

		GetSet(cpZone,chpToken[0]-'A');

		if(!(chpToken=strtok(NULL,chpDelimit_m)))
			throw "Script: Zone definition - Missing }";
	}
	cpZone->cpSet_m=cpZone->cListSet_m.ConvertToArray();
	cpZone->cListSet_m.Delete();
} /* CUnivers::GetZone */


/*
 *	CUnivers::GetSet
 */
void CUnivers::GetSet(CZone* cpZone_p,T_UWORD uwIndex_p)
{
	if(uwIndex_p!=cpZone_p->uwNbSet_m++)
		throw "Script: Set definition - Bad Set index letter";

	if(strcmp(strtok(NULL,chpDelimit_m),"SET")!=0)
		throw "Script: Set definition - Missing Set keyword";

	if(strcmp(strtok(NULL,chpDelimit_m),"{")!=0)
		throw "Script: Set definition - Missing {";

	CSet* cpSet=cpZone_p->cListSet_m.Insert(CSet(),CList<CSet>::E_LIST_INSERTQUEUE);

	// Création de la définition land du set
	cpSet->uwNbLand_m=0;
	char *chpToken;
	while(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"}")!=0)
	{
		CGroup* cpGroup=(chpToken[0]=='¤'?cpZone_p->cpGroupA_m:cpZone_p->cpGroupB_m);
		if(cpGroup==0)
			throw "Script: Zone definition - Group § not defined";
		chpToken++;
		T_UWORD uwIndex=atoi(chpToken);
		if(uwIndex>=cpGroup->uwNbLand_m)
			throw "Script: Set definition - Bad Land index";

		if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"}")==0)
			throw "Script: Set definition - Missing Land X parameter";
		T_UWORD uwX=atoi(chpToken);
		if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"}")==0)
			throw "Script: Set definition - Missing Land Y parameter";
		T_UWORD uwY=atoi(chpToken);
		if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"}")==0)
			throw "Script: Set definition - Missing Land altitude";
		
		cpSet->cListLandPtr_m.Insert(CLandPtr(&cpGroup->cpLand_m[uwIndex]),CList<CLandPtr>::E_LIST_INSERTQUEUE);
		cpSet->cListLandPos_m.Insert(CLandPos(uwX,uwY,atoi(chpToken)),CList<CLandPos>::E_LIST_INSERTQUEUE);
		cpSet->uwNbLand_m++;
	}
	cpSet->cpLandPtr_m=cpSet->cListLandPtr_m.ConvertToArray();
	cpSet->cpLandPos_m=cpSet->cListLandPos_m.ConvertToArray();
	cpSet->cListLandPtr_m.Delete();
	cpSet->cListLandPos_m.Delete();
} /* CUnivers::GetSet */


/*
 * CUnivers::GetWorld
 */
void CUnivers::GetWorld(T_UWORD uwIndex_p)
{
	if(uwIndex_p!=uwNbWorld_m++)
		throw "Script: World definition - Bad World index number";

	char *chpToken;
	if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"{")==0)
		throw "Script: World definition - Missing X size";
	T_UWORD uwXSize=atoi(chpToken);
	if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"{")==0)
		throw "Script: World definition - Missing Y size";
	T_UWORD uwYSize=atoi(chpToken);
	
	CWorld* cpWorld=cListWorld_m.Insert(CWorld(uwXSize,uwYSize),CList<CWorld>::E_LIST_INSERTQUEUE);

	if(strcmp(strtok(NULL,chpDelimit_m),"{")!=0)
		throw "Script: World definition - Missing {";

	T_UWORD uw=0;
	for(T_UWORD uwY=0;uwY<uwYSize;uwY++)
		for(T_UWORD uwX=0;uwX<uwXSize;uwX++,uw++)
		{
			if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"}")==0)
				throw "Script: World definition - Missing Set & Zone index letter & number";

			// création des instances de bloc & de land en fonction du set s'il existe
			if(strlen(chpToken)==1 || (chpToken[0]>='0' && chpToken[0]<='9'))
			{
				T_UWORD uwIndex=atoi(chpToken);
				if(uwIndex>=uwNbZone_m)
					throw "Script: World definition - Bad Zone index";
				if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"}")==0 || strcmp(chpToken,"CHARACTER")==0)
					throw "Script: World definition - Missing Zone altitude";
				T_WORD wAltitude=atoi(chpToken)*64;
				cpWorld->cpZoneInst_m[uw].Set(&cpZone_m[uwIndex],uwX,uwY,wAltitude,CZoneInst::E_ZONEINST_GEOHUMAIN);
			}
			else
			{
				T_UWORD uwSet=chpToken[0]-'A';
				chpToken++;
				T_UWORD uwIndex=atoi(chpToken);
				if(uwIndex>=uwNbZone_m)
					throw "Script: World definition - Bad Zone index";
				if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"}")==0 || strcmp(chpToken,"CHARACTER")==0)
					throw "Script: World definition - Missing Zone altitude";
				T_WORD wAltitude=atoi(chpToken)*64;

				if(uwSet>=cpZone_m[uwIndex].uwNbSet_m)
					throw "Script: World definition - Unexisting Set in Zone Instance";

				cpWorld->cpZoneInst_m[uw].Set(&cpZone_m[uwIndex],uwSet,uwX,uwY,wAltitude,CZoneInst::E_ZONEINST_GEOHUMAIN);
			}
		}

	cpWorld->ulNbCharacter_m=0;
	while(strcmp(chpToken=strtok(NULL,chpDelimit_m),"CHARACTER")==0)
		GetCharacter(cpWorld,uwIndex_p);

	if(strcmp(chpToken,"}")!=0)
		throw "Script: World definition - Missing }";
} /* CUnivers::GetWorld */


/*
 * CUnivers::GetPath
 */
void CUnivers::GetPath(T_UWORD uwIndex_p)
{
	if(uwIndex_p!=uwNbPath_m++)
		throw "Script: Path definition - Bad Path index number";
	if(strcmp(strtok(NULL,chpDelimit_m),"{")!=0)
		throw "Script: Path definition - Missing {";

	CPath* cpPath=cListPath_m.Insert(CPath(),CList<CPath>::E_LIST_INSERTQUEUE);

	cpPath->uwNbPathPos_m=0;
	char *chpToken;
	while((chpToken=strtok(NULL,chpDelimit_m)) && strcmp(chpToken,"}")!=0)
	{
		T_WORD wDX=atoi(chpToken);
		if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"}")==0)
			throw "Script: Path definition - Missing Path DY";
		T_WORD wDY=atoi(chpToken);
		cpPath->cListPathPos_m.Insert(CPathPos(wDX,wDY),CList<CPathPos>::E_LIST_INSERTQUEUE);
		cpPath->uwNbPathPos_m++;
	}
	cpPath->cpPathPos_m=cpPath->cListPathPos_m.ConvertToArray();
	cpPath->cListPathPos_m.Delete();

	if(strcmp(chpToken,"}")!=0)
		throw "Script: Path definition - Missing }";
} /* CUnivers::GetPath */


/*
 * CUnivers::GetModel
 */
void CUnivers::GetModel(T_UWORD uwIndex_p)
{
	if(uwIndex_p!=uwNbModel_m++)
		throw "Script: Model definition - Bad Model index number";
	if(strcmp(strtok(NULL,chpDelimit_m),"{")!=0)
		throw "Script: Model definition - Missing {";

	char *chpToken;
	if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"RACE")!=0)
		throw "Script: Model definition - Missing Model Race keyword";
	if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"ICON")==0)
		throw "Script: Model definition - Missing Model Race (Human/Uerg/Nomareg/Animal)";
	CModel::EModelRace eRace;
	if(strcmp(chpToken,"HUMAN")==0)
		eRace=CModel::E_MODEL_HUMAN;
	else if(strcmp(chpToken,"UERG")==0)
		eRace=CModel::E_MODEL_UERG;
	else if(strcmp(chpToken,"NOMAREG")==0)
		eRace=CModel::E_MODEL_NOMAREG;
	else if(strcmp(chpToken,"ANIMAL")==0)
		eRace=CModel::E_MODEL_ANIMAL;
	else
		throw "Script: Model definition - Bad Model Race (Human/Uerg/Nomareg/Animal)";

	if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"ICON")!=0)
		throw "Script: Model definition - Missing Model Icon keyword";
	char* chpIcon;
	if(!(chpIcon=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"MESH")==0)
		throw "Script: Model definition - Missing Model Icon";

	if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"MESH")!=0)
		throw "Script: Model definition - Missing Model Mesh keyword";
	char* chpMesh;
	if(!(chpMesh=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"TEXTURE")==0)
		throw "Script: Model definition - Missing Model Mesh";

	if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"TEXTURE")!=0)
		throw "Script: Model definition - Missing Model Texture keyword";
	char* chpTexture;
	if(!(chpTexture=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"MOVIE")==0)
		throw "Script: Model definition - Missing Model Texture";

	if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"MOVIE")!=0)
		throw "Script: Model definition - Missing Model Movie keyword";
	char* chpMovie;
	if(!(chpMovie=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"IA")==0)
		throw "Script: Model definition - Missing Model Movie";

	if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"IA")!=0)
		throw "Script: Model definition - Missing Model IA keyword";
	char* chpIA;
	if(!(chpIA=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"ALTITUDE")==0)
		throw "Script: Model definition - Missing Model IA";

	if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"ALTITUDE")!=0)
		throw "Script: Model definition - Missing Model Altitude keyword";
	if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"LIFE")==0)
		throw "Script: Model definition - Missing Model Altitude";
	T_WORD wAltitude=atoi(chpToken);

	if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"LIFE")!=0)
		throw "Script: Model definition - Missing Model Life keyword";
	if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"TIRENESS")==0)
		throw "Script: Model definition - Missing Model Life";
	T_WORD wLife=atoi(chpToken);

	if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"TIRENESS")!=0)
		throw "Script: Model definition - Missing Model Tireness keyword";
	if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"}")==0)
		throw "Script: Model definition - Missing Model Tireness";
	T_UWORD uwTireness=atoi(chpToken);
	
	CModel* cpModel=cListModel_m.Insert(
		CModel(eRace,chpIcon,chpMesh,chpTexture,chpMovie,chpIA,wAltitude,wLife,uwTireness),
		CList<CModel>::E_LIST_INSERTQUEUE);

	if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"}")!=0)
		throw "Script: Model definition - Missing }";
} /* CUnivers::GetModel */


/*
 * CUnivers::GetCharacter
 */
void CUnivers::GetCharacter(CWorld* cpWorld_p,T_UWORD uwIndex_p)
{
	cpWorld_p->ulNbCharacter_m++;
	if(strcmp(strtok(NULL,chpDelimit_m),"{")!=0)
		throw "Script: Character definition - Missing {";

	char* chpToken;
	if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"MODEL")!=0)
		throw "Script: Character definition - Missing Character Model keyword";
	if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"TYPE")==0)
		throw "Script: Character definition - Missing Character Model";
	T_UWORD uwModel=atoi(chpToken);
	if(uwModel>=uwNbModel_m)
		throw "Script: Character definition - Bad Character Model";

	if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"TYPE")!=0)
		throw "Script: Character definition - Missing Character Type keyword";
	if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"NAME")==0)
		throw "Script: Character definition - Missing Character Type";
	CCharacter::ECharacterType eType;
	if(strcmp(chpToken,"NPC")==0)
		eType=CCharacter::E_CHARACTER_NPC;
	else if(strcmp(chpToken,"PC")==0)
		eType=CCharacter::E_CHARACTER_PC;
	else if(strcmp(chpToken,"AC")==0)
		eType=CCharacter::E_CHARACTER_AC;
	else if(strcmp(chpToken,"DC")==0)
		eType=CCharacter::E_CHARACTER_DC;
	else 
		throw "Script: Character definition - Bad Character Type";

	char* chpName;
	if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"NAME")!=0)
		throw "Script: Character definition - Missing Character Name keyword";
	if(!(chpName=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"HOME")==0)
		throw "Script: Character definition - Missing Character Name";

	if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"HOME")!=0)
		throw "Script: Character definition - Missing Character Home keyword";
	if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"}")==0)
		throw "Script: Character definition - Missing Character Home parameter XZone";
	T_UWORD uwXZone=atoi(chpToken);
	if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"}")==0)
		throw "Script: Character definition - Missing Character Home parameter YZone";
	T_UWORD uwYZone=atoi(chpToken);
	if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"}")==0)
		throw "Script: Character definition - Missing Character Home parameter XBloc";
	T_UWORD uwXBloc=atoi(chpToken);
	if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"}")==0)
		throw "Script: Character definition - Missing Character Home parameter YBloc";
	T_UWORD uwYBloc=atoi(chpToken);
	if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"}")==0)
		throw "Script: Character definition - Missing Character Home parameter XCell";
	T_UWORD uwXCell=atoi(chpToken);
	if(!(chpToken=strtok(NULL,chpDelimit_m)) || strcmp(chpToken,"}")==0)
		throw "Script: Character definition - Missing Character Home parameter YCell";
	T_UWORD uwYCell=atoi(chpToken);
	CCharacter* cpCharacter=cpWorld_p->cListCharacter_m.Insert(
		CCharacter(uwModel,eType,chpName,uwIndex_p,uwXZone,uwYZone,uwXBloc,uwYBloc,uwXCell,uwYCell),
		CList<CCharacter>::E_LIST_INSERTQUEUE);

	cpCharacter->uwNbCharPath_m=0;
	if((chpToken=strtok(NULL,chpDelimit_m)) && strcmp(chpToken,"PATH")==0)
	{
		while((chpToken=strtok(NULL,chpDelimit_m)) && strcmp(chpToken,"}")!=0)
		{
			T_UWORD uwPath=atoi(chpToken);
			if(uwPath>=uwNbPath_m)
				throw "Script: Character definition - Bad Character Path index";

			cpCharacter->cListCharPath_m.Insert(CCharPath(uwPath),CList<CCharPath>::E_LIST_INSERTQUEUE);
			cpCharacter->uwNbCharPath_m++;
		}
		cpCharacter->cpCharPath_m=cpCharacter->cListCharPath_m.ConvertToArray();
		cpCharacter->cListCharPath_m.Delete();
	}

	if(!chpToken || strcmp(chpToken,"}")!=0)
		throw "Script: Character definition - Missing }";
} /* CUnivers::GetCharacter */


/*
 *	CUnivers::InitCell
 */
void CUnivers::InitCell()
{
	// Load Texture & bloc
	for(T_UWORD uw=0;uw<uwNbGroup_m;uw++)
	{
		cpGroup_m[uw].AddRef();
		for(T_UWORD uwBloc=0;uwBloc<cpGroup_m[uw].uwNbBloc_m;uwBloc++)
			cpGroup_m[uw].cpBloc_m[uwBloc].AddRef();
	}

	// Création des cellule
	for(uw=0;uw<cpWorld_m->uwXSize_m*cpWorld_m->uwYSize_m;uw++)
	{
		CZoneInst* cpZoneInst=&cpWorld_m->cpZoneInst_m[uw];
		for(T_UWORD uwBloc=0;uwBloc<CZone::E_ZONE_SIZE2;uwBloc++)
			cpZoneInst->cpBlocInst_m[uwBloc].InitCell();
	}

	// Release texture & bloc
	for(uw=0;uw<uwNbGroup_m;uw++)
	{
		for(T_UWORD uwBloc=0;uwBloc<cpGroup_m[uw].uwNbBloc_m;uwBloc++)
			cpGroup_m[uw].cpBloc_m[uwBloc].Release();
		cpGroup_m[uw].Release();
	}
} /* CUnivers::InitCell */


