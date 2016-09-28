// FindIDTODevInfo.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "FindIDTODevInfo.h"
#include "MemdbClass.h"
#include "publicpw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CFindIDTODevInfoApp

BEGIN_MESSAGE_MAP(CFindIDTODevInfoApp, CWinApp)
	//{{AFX_MSG_MAP(CFindIDTODevInfoApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindIDTODevInfoApp construction

CFindIDTODevInfoApp::CFindIDTODevInfoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	m_pUnEquMeas=NULL;
	m_pRelation=NULL;
	m_UnEquMeas=0;
	m_Relations=0;	
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CFindIDTODevInfoApp object

CFindIDTODevInfoApp theApp;
CMemdbClass  m_memdb;		//内存库接口
char p[32];


char* WINAPI IDtoNuName(char* ID,int Type,DWORD &iNU)
{	
	iNU=0;
	memset(p,0,32);
	
	int num,i;
	switch(Type)
	{
	case 1://Gen发电机 
		{
			m_memdb.GetMemdata("visualpw", "Gen");
			num=m_memdb.m_datatnum;		   
			visualpw_Gen* pGen = NULL;
			for(i=0;i<num;i++)
			{
				pGen = ((visualpw_Gen*)m_memdb.m_memdata)+i;
				if(pGen==NULL)
					break;
				if(strcmp(pGen->ID,ID)==0 || strncmp(pGen->ID,ID,strlen(ID))==0)
				{
					strcpy(p,pGen->Name);
					iNU = pGen->NU;
					break;
				}
			}
		}
		break;
	case 2://开关，刀闸  
		{
			m_memdb.GetMemdata("visualpw", "Switch");
			num=m_memdb.m_datatnum;	
			
			visualpw_Switch* pSw = NULL;
			for(i=0;i<num;i++)
			{
				pSw = ((visualpw_Switch*)m_memdb.m_memdata)+i;
				if(pSw==NULL)
					break;
				if(strcmp(pSw->ID,ID)==0)
				{				   	
					strcpy(p,pSw->Name);
					iNU = pSw->NU;
					break;
				}
			}
		}
		break;
	case 3://负荷 
		{
			m_memdb.GetMemdata("visualpw", "Load");
			num=m_memdb.m_datatnum;		   
			visualpw_Load* pLoad = NULL;
			for(i=0;i<num;i++)
			{
				pLoad = ((visualpw_Load*)m_memdb.m_memdata)+i;
				if(pLoad==NULL)
					break;
				if(strcmp(pLoad->ID,ID)==0)
				{
					strcpy(p,pLoad->Name);
					iNU = pLoad->NU;
					break;
				}
			}
		}
		break;
	case 4://电容  
		{
			m_memdb.GetMemdata("visualpw", "Shunt");
			num=m_memdb.m_datatnum;		   
			visualpw_Shunt* pShunt = NULL;
			for(i=0;i<num;i++)
			{
				pShunt = ((visualpw_Shunt*)m_memdb.m_memdata)+i;
				if(pShunt==NULL)
					break;
				if(strcmp(pShunt->ID,ID)==0)
				{
					strcpy(p,pShunt->Name);
					iNU = pShunt->NU;
					break;
				}
			}
		}
		break;
	case 5://电抗 
		{
			m_memdb.GetMemdata("visualpw", "Sreact");
			num=m_memdb.m_datatnum;
			
			visualpw_Sreact* pSreact = NULL;
			for(i=0;i<num;i++)
			{
				pSreact = ((visualpw_Sreact*)m_memdb.m_memdata)+i;
				if(pSreact==NULL)
					break;
				if(strcmp(pSreact->ID,ID)==0)
				{
					strcpy(p,pSreact->Name);
					iNU = pSreact->NU;
					break;
				}
			}
		}
		break;
	case 7://2绕变 
		{
			m_memdb.GetMemdata("common", "SubObject");
			num=m_memdb.m_datatnum;
			common_SubObject* pSubObj=NULL;
			for(i=0;i<num;i++)
			{
				pSubObj = ((common_SubObject*)m_memdb.m_memdata)+i;
				if(pSubObj==NULL)
					continue;
				if(pSubObj->PType==4 && strcmp(pSubObj->ID,ID)==0 )
				{
					iNU = pSubObj->PNU;
					break;
				}
			}
			//取得名字
			m_memdb.GetMemdata("visualpw", "Tfm1");
			num=m_memdb.m_datatnum;	
			visualpw_Tfm1* pTfm1=NULL;
			for(i=0;i<num;i++)
			{
				pTfm1 = ((visualpw_Tfm1*)m_memdb.m_memdata)+i;
				if(pTfm1==NULL)
					break;
				if(pTfm1->NU==iNU)
				{
					strcpy(p,pTfm1->Name);
					break;
				}
			}
		}
		break;
	case 8://3绕变 
		{
			m_memdb.GetMemdata("common", "SubObject");
			num=m_memdb.m_datatnum;		   
			common_SubObject* pSubObj=NULL;
			for(i=0;i<num;i++)
			{
				pSubObj = ((common_SubObject*)m_memdb.m_memdata)+i;
				if(pSubObj==NULL)
					continue;
				if(pSubObj->PType==5 && strcmp(pSubObj->ID,ID)==0)
				{
					iNU = pSubObj->PNU;
					break;
				}
			}
			m_memdb.GetMemdata("visualpw", "Tfm2");
			num=m_memdb.m_datatnum;		   
			visualpw_Tfm2* pTfm2=NULL;
			for(i=0;i<num;i++)
			{
				pTfm2 = ((visualpw_Tfm2*)m_memdb.m_memdata)+i;
				if(pTfm2==NULL)
					break;
				if(pTfm2->NU==iNU)
				{
					strcpy(p,pTfm2->Name);
					break;
				}
			}
		}
		break;
	case 20://非设备量测   
		{
			m_memdb.GetMemdata("common", "UnEquMeas");
			num=m_memdb.m_datatnum;		   
			common_UnEquMeas* pUnEqu = NULL;
			for(i=0;i<num;i++)
			{
				pUnEqu = ((common_UnEquMeas*)m_memdb.m_memdata)+i;
				if(pUnEqu==NULL)
					break;
				if(strcmp(pUnEqu->ID,ID)==0)
				{
					strcpy(p,pUnEqu->Name);
					iNU = pUnEqu->NU;
					break;
				}
			}
		}
		break;
	case 32://母线   
		{
			m_memdb.GetMemdata("visualpw", "Bus");
			num=m_memdb.m_datatnum;		   
			visualpw_Bus* pBus = NULL;
			for(i=0;i<num;i++)
			{
				pBus = ((visualpw_Bus*)m_memdb.m_memdata)+i;
				if(pBus==NULL)
					break;
				if(strcmp(pBus->ID,ID)==0)
				{
					strcpy(p,pBus->Name);
					iNU = pBus->NU;
					break;
				}
			}
		}
		break;
	case 33://交流线  
		{
			m_memdb.GetMemdata("visualpw", "Line");
			num=m_memdb.m_datatnum;		   
			visualpw_Line* pLine = NULL;
			for(i=0;i<num;i++)
			{
				pLine = ((visualpw_Line*)m_memdb.m_memdata)+i;
				if(pLine==NULL)
					break;
				if(strcmp(pLine->ID,ID)==0)
				{
					strcpy(p,pLine->Name);
					iNU = pLine->NU;
					break;
				}
			}
		}
		break;
	}
	return p;
}

char* WINAPI NUtoName(DWORD NU,int Type,DWORD &iNU)
{	
	iNU=NU;
	memset(p,0,32);

	int num,i;
	visualpw_Gen* pGen;
	visualpw_Switch* pSw;
	visualpw_Load* pLoad;
	visualpw_Shunt* pShunt;
	visualpw_Tfm1* pTfm1;
	visualpw_Tfm2* pTfm2;
    visualpw_Bus* pBus;
    visualpw_Line* pLine;
	common_UnEquMeas* pUnEqu;
	visualpw_Station* pStation;
    
	switch(Type)
	{
		case 1://Gen发电机           
		   m_memdb.GetMemdata("visualpw", "Gen");
		   num=m_memdb.m_datatnum;		   
		   for(i=0;i<num;i++)
		   {
			   pGen = NULL;
			   pGen = ((visualpw_Gen*)m_memdb.m_memdata)+i;
			   if(pGen==NULL)
				   break;
			   if(pGen->NU==NU)
			   {
				   strcpy(p,pGen->Name);
				   iNU = pGen->NU;
				   break;
			   }
		   }
		break;
		case 2://开关，刀闸           
		   m_memdb.GetMemdata("visualpw", "Switch");
		   num=m_memdb.m_datatnum;	
		  
		   for(i=0;i<num;i++)
		   {
			   pSw = NULL;
			   pSw = ((visualpw_Switch*)m_memdb.m_memdata)+i;
			   if(pSw==NULL)
				   break;
			   if(pSw->NU==NU)
			   {				   	
				   strcpy(p,pSw->Name);
				   iNU = pSw->NU;
				   break;
			   }
		   }
		break;
		case 3://负荷          
		   m_memdb.GetMemdata("visualpw", "Load");
		   num=m_memdb.m_datatnum;		   
		   for(i=0;i<num;i++)
		   {
			   pLoad = NULL;
			   pLoad = ((visualpw_Load*)m_memdb.m_memdata)+i;
			   if(pLoad==NULL)
				   break;
			   if(pLoad->NU==NU)
			   {
				   strcpy(p,pLoad->Name);
				   iNU = pLoad->NU;
				   break;
			   }
		   }
		break;
		case 4://电容        
		   m_memdb.GetMemdata("visualpw", "Shunt");
		   num=m_memdb.m_datatnum;		   
		   for(i=0;i<num;i++)
		   {
			   pShunt = NULL;
			   pShunt = ((visualpw_Shunt*)m_memdb.m_memdata)+i;
			   if(pShunt==NULL)
				   break;
			   if(pShunt->NU==NU)
			   {
				   strcpy(p,pShunt->Name);
				   iNU = pShunt->NU;
				   break;
			   }
		   }
		break;
		case 5://电抗 
			{
				m_memdb.GetMemdata("visualpw", "Sreact");
				num=m_memdb.m_datatnum;		   
				visualpw_Sreact* pSreact = NULL;
				for(i=0;i<num;i++)
				{
					pSreact = ((visualpw_Sreact*)m_memdb.m_memdata)+i;
					if(pSreact==NULL)
						break;
					if(pSreact->NU==NU)
					{
						strcpy(p,pSreact->Name);
						iNU = pSreact->NU;
						break;
					}
				}
			}
		break;
		case 6:
			{
				m_memdb.GetMemdata("visualpw", "GND");
				num=m_memdb.m_datatnum;		   
				visualpw_GND* pGND = NULL;
				for(i=0;i<num;i++)
				{
					pGND = ((visualpw_GND*)m_memdb.m_memdata)+i;
					if(pGND==NULL)
						break;
					if(pGND->NU==NU)
					{
						strcpy(p,pGND->Name);
						iNU = pGND->NU;
						break;
					}
				}
			}break;
		case 7://2绕变 
			{
				/*m_memdb.GetMemdata("common", "SubObject");
				num=m_memdb.m_datatnum;		   
				common_SubObject* pSubObj;
				for(i=0;i<num;i++)
				{
					pSubObj = ((common_SubObject*)m_memdb.m_memdata)+i;
					if(pSubObj==NULL)
						continue;
					if(pSubObj->PType==4 && pSubObj->NU==NU)
					{
						iNU = pSubObj->PNU;
						break;
					}
				}*/
				//取得名字
				m_memdb.GetMemdata("visualpw", "Tfm1");
				num=m_memdb.m_datatnum;		   
				for(i=0;i<num;i++)
				{
					pTfm1 = ((visualpw_Tfm1*)m_memdb.m_memdata)+i;
					if(pTfm1==NULL)
						break;
					if(pTfm1->NU==NU)
					{
						iNU=NU;
						strcpy(p,pTfm1->Name);
						break;
					}
				}
			}
			break;
		case 8://3绕变 
			{
				/*m_memdb.GetMemdata("common", "SubObject");
				num=m_memdb.m_datatnum;		   
				common_SubObject* pSubObj;
				for(i=0;i<num;i++)
				{
					pSubObj = ((common_SubObject*)m_memdb.m_memdata)+i;
					if(pSubObj==NULL)
						continue;
					if(pSubObj->PType==5 && atoi(pSubObj->ID)==ID)
					{
						iNU = pSubObj->PNU;
						break;
					}
				}*/
				m_memdb.GetMemdata("visualpw", "Tfm2");
				num=m_memdb.m_datatnum;		   
				for(i=0;i<num;i++)
				{
					pTfm2 = ((visualpw_Tfm2*)m_memdb.m_memdata)+i;
					if(pTfm2==NULL)
						break;
					if(pTfm2->NU==NU)
					{
						iNU=NU;
						strcpy(p,pTfm2->Name);
						break;
					}
				}
			}
			break;
		case 20://非设备量测          
		   m_memdb.GetMemdata("common", "UnEquMeas");
		   num=m_memdb.m_datatnum;		   
		   for(i=0;i<num;i++)
		   {
			   pUnEqu = NULL;
			   pUnEqu = ((common_UnEquMeas*)m_memdb.m_memdata)+i;
			   if(pUnEqu==NULL)
				   break;
			   if(pUnEqu->NU==NU)
			   {
				   strcpy(p,pUnEqu->Name);
				   iNU = pUnEqu->NU;
				   break;
			   }
		   }
		break;
		case 32://母线       
		   m_memdb.GetMemdata("visualpw", "Bus");
		   num=m_memdb.m_datatnum;		   
		   for(i=0;i<num;i++)
		   {
			   pBus = NULL;
			   pBus = ((visualpw_Bus*)m_memdb.m_memdata)+i;
			   if(pBus==NULL)
				   break;
			   if(pBus->NU==NU)
			   {
				   strcpy(p,pBus->Name);
				   iNU = pBus->NU;
				   break;
			   }
		   }
		break;
		case 33://交流线          
		   m_memdb.GetMemdata("visualpw", "Line");
		   num=m_memdb.m_datatnum;		   
		   for(i=0;i<num;i++)
		   {
			   pLine = NULL;
			   pLine = ((visualpw_Line*)m_memdb.m_memdata)+i;
			   if(pLine==NULL)
				   break;
			   if(pLine->NU==NU)
			   {
				   strcpy(p,pLine->Name);
				   iNU = pLine->NU;
				   break;
			   }
		   }
		break;

		case 100://厂站          
			m_memdb.GetMemdata("visualpw", "Station");
			num=m_memdb.m_datatnum;		   
			for(i=0;i<num;i++)
			{
				pStation = NULL;
				pStation = ((visualpw_Station*)m_memdb.m_memdata)+i;
				if(pStation==NULL)
					break;
				if(pStation->NU==NU)
				{
					strcpy(p,pStation->Name);
					iNU = pStation->NU;
					break;
				}
			}
		break;
	}
	return p;
}

char* WINAPI ExchangeIDName(char* pid,int &type,DWORD &iNU,int &mtype,int &mpos)
{
	int style=0;
	void* pRecord=theApp.SearchByID(pid,style);
	if(pRecord==NULL)
		return NULL;


	if(style==1)
	{
		type=0;
		common_Relation* pRel=(common_Relation*)pRecord;
		mtype=pRel->MeasType;
		mpos=pRel->MeasPos;
		switch(pRel->DevType)
		{
		case EQUIP_TYPE_GEN:
			{
				type=1;
				//除机端电压、功率、功角数据外，其他数据在关系表
				if(mtype!=MEASURE_TYPE_V && mtype!=MEASURE_TYPE_P && mtype!=MEASURE_TYPE_Q && mtype!=MEASURE_TYPE_Ang)
				{
					type=19;
					iNU=pRel->NU;
				}
			}
			break;
		case EQUIP_TYPE_SWITCH:
			{
				type=2;
				if(mtype!=MEASURE_TYPE_YX)
				{
					type=19;
					iNU=pRel->NU;
				}
			}
			break;
		case EQUIP_TYPE_LOAD:
			{
				type=3;
				if(mtype!=MEASURE_TYPE_I && mtype!=MEASURE_TYPE_P && mtype!=MEASURE_TYPE_Q)
				{
					type=19;
					iNU=pRel->NU;
				}
			}
			break;
		case EQUIP_TYPE_SHUNT:
			{
				type=4;
				if(mtype!=MEASURE_TYPE_Q)
				{
					type=19;
					iNU=pRel->NU;
				}
			}
			break;
		case EQUIP_TYPE_REACT:
			{
				type=5;
				if(mtype!=MEASURE_TYPE_Q)
				{
					type=19;
					iNU=pRel->NU;
				}
			}
			break;
		case EQUIP_TYPE_BITRS:
			{
				type=7;
				if(mtype!=MEASURE_TYPE_I && mtype!=MEASURE_TYPE_P && mtype!=MEASURE_TYPE_Q && mtype!=MEASURE_TYPE_T && mtype!=MEASURE_TYPE_Pos)
				{
					type=19;
					iNU=pRel->NU;
				}
			}
			break;
		case EQUIP_TYPE_TRITRS:
			{
				type=8;
				if(mtype!=MEASURE_TYPE_I && mtype!=MEASURE_TYPE_P && mtype!=MEASURE_TYPE_Q && mtype!=MEASURE_TYPE_T && mtype!=MEASURE_TYPE_Pos)
				{
					type=19;
					iNU=pRel->NU;
				}
			}
			break;
		case EQUIP_TYPE_BUS:
			{
				type=32;
				if(mtype!=MEASURE_TYPE_V && mtype!=MEASURE_TYPE_Vab && mtype!=MEASURE_TYPE_Vbc && mtype!=MEASURE_TYPE_Vca && mtype!=MEASURE_TYPE_Ang)
				{
					type=19;
					iNU=pRel->NU;
				}
			}
			break;
		case EQUIP_TYPE_LINE:
			{
				type=33;
				if(mtype!=MEASURE_TYPE_I && mtype!=MEASURE_TYPE_P && mtype!=MEASURE_TYPE_Q)
				{
					type=19;
					iNU=pRel->NU;
				}
			}
			break;
		}
		if(type==19)//设备量测
		{
			memset(p,0,32);
			strcpy(p,pRel->MeasID);
			return p;
		}
		else
			return NUtoName(pRel->VNu,type,iNU);
	}
	else
	{
		memset(p,0,32);
		common_UnEquMeas* pUnEqu=(common_UnEquMeas*)pRecord;
		iNU=pUnEqu->NU;
		strcpy(p,pUnEqu->Name);
		mtype=pUnEqu->type;
		type=20;
		return p;
	}
	return NULL;
}

BOOL CFindIDTODevInfoApp::InitInstance() 
{
	//初始化内存库
	if(!LSI_InitNTDbi())
	{
		AfxMessageBox("数据库平台未启动");	
		return false;
	}
	if(!LSI_CheckUser("sa",""))
	{
		AfxMessageBox("数据库平台未启动");	
		return false;
	}

	IniSearch();
	
	return CWinApp::InitInstance();
}

bool CFindIDTODevInfoApp::IniSearch()
{
	MEMTABLE* pMem=NULL;
	m_pUnEquMeas=(common_UnEquMeas*)GetMemTable("common","UnEquMeas",&pMem);
	m_UnEquMeas=pMem->userec;
	for(int i=0;i<m_UnEquMeas;i++)
	{
		m_MeasSearch.AddMap(m_pUnEquMeas[i].NU,m_pUnEquMeas[i].ID,NULL,i);
	}

	m_pRelation=(common_Relation*)GetMemTable("common","Relation",&pMem);
	m_Relations=pMem->userec;
	for(i=0;i<m_Relations;i++)
	{
		m_RelSearch.AddMap(m_pRelation[i].NU,m_pRelation[i].MeasID,NULL,i);
	}
	return true;
}

void* CFindIDTODevInfoApp::SearchByID(char *pid, int &type)
{
	BINARYMAP* pReturn=(BINARYMAP*)m_RelSearch.Search(pid);
	if(pReturn!=NULL && pReturn->idx<m_Relations)
	{
		type=1;
		if(m_pRelation[pReturn->idx].NU==pReturn->NU)
		{
			return &m_pRelation[pReturn->idx];
		}
		else
		{
			for(int i=0;i<m_Relations;i++)
			{
				if(m_pRelation[i].NU==pReturn->NU)
				{
					pReturn->idx=i;
					return &m_pRelation[i];
				}
			}
		}
	}
	else
	{
		type=2;
		pReturn=(BINARYMAP*)m_MeasSearch.Search(pid);
		if(pReturn!=NULL && pReturn->idx<m_UnEquMeas)
		{
			if(m_pUnEquMeas[pReturn->idx].NU==pReturn->NU)
			{
				return &m_pUnEquMeas[pReturn->idx];
			}
			else
			{
				for(int i=0;i<m_Relations;i++)
				{
					if(m_pUnEquMeas[i].NU==pReturn->NU)
					{
						pReturn->idx=i;
						return &m_pUnEquMeas[i];
					}
				}
			}
		}
	}
	return NULL;
}
