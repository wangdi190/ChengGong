
#include "stdafx.h"

#include "dbapi.h"
#include "mstruct.h"
#include "visualdb.h"
#include "userapi.h"

extern char *devtbl[];

bool dbok=false;

//通过ID号返回设备名称

bool GetDevNameByID(SELECTDEV&dev)
{
	visualpw_PT *pt;
	visualpw_Switch *swt;
	visualpw_GND *gnd;
	visualpw_CVT *cvt;
	visualpw_Gen *gen;
	visualpw_Line *line;
	visualpw_DCLine *dcl;
	visualpw_Bus  *bus;
	visualpw_Load *load;
	visualpw_Tfm1 *tfm1;
	visualpw_Tfm2 *tfm2;
	visualpw_Shunt *sht;
	visualpw_Sreact *srt;
	visualpw_SVC  *svc;

	
	DWORD idi;
	MEMTABLE *mtb;
	int t,ti,i,j,num;


	if(!dbok) //如果数据库未打开，则执行
	{
		dbok=LSI_InitNTDbi();
	}
	if(!dbok) return false; //还是打不开

	ti=dev.dtype>=33 ? dev.dtype-22:dev.dtype;
	if(ti>13||ti<0)	return false;
	
	num=0;
	t=ti;
	
	if(!LSI_GetTableID(dev.dbname,devtbl[t],idi)) return false;
	j=LOWORD(idi);
	mtb=(MEMTABLE *)LSI_GetTableAdd(j);
	if(mtb==NULL) return false;
	num=mtb->userec;

	switch(t)
	{
	case 0: //PT
		pt=(visualpw_PT *)mtb->data;
		for(i=0;i<num;i++){
			if(pt[i].NU==(DWORD)dev.did)
			{
			  strcpy(dev.name,pt[i].Name);
			  return true;
			}
		}
		break;
	case 1: //发电机 
		gen=(visualpw_Gen *)mtb->data;
		for(i=0;i<num;i++){
			if((DWORD)dev.did==gen[i].NU)
			{
			   strcpy(dev.name,gen[i].Name);
			   return true;
			}
		}
		break;
	case 2:	//开关，刀闸
		swt=(visualpw_Switch *)mtb->data;
		for(i=0;i<num;i++){
			if(swt[i].NU==(DWORD)dev.did)
			{
			  strcpy(dev.name,swt[i].Name);
			  return true;
			}
		}
		break;
	case 3: //负荷
		load=(visualpw_Load *)mtb->data;
		for(i=0;i<num;i++){
			if(load[i].NU==(DWORD)dev.did)
			{
			  strcpy(dev.name,load[i].Name);
			  return true;
			}
		}
		break;
	case 4:  //电容
		sht=(visualpw_Shunt *)mtb->data;
		for(i=0;i<num;i++){
			if(sht[i].NU==(DWORD)dev.did)
			{
			  strcpy(dev.name,sht[i].Name);
			  return true;
			}
		}
		break;
	case 5:  //电抗
		srt=(visualpw_Sreact *)mtb->data;
		for(i=0;i<num;i++){
			if(srt[i].NU==(DWORD)dev.did)
			{
			  strcpy(dev.name,srt[i].Name);
			  return true;
			}
		}
		break;
	case 6:  //接地
		gnd=(visualpw_GND *)mtb->data;
		for(i=0;i<num;i++){
			if(gnd[i].NU==(DWORD)dev.did)
			{
			  strcpy(dev.name,gnd[i].Name);
			  return true;
			}
		}
		break;

	case 7: //2绕变
		tfm1=(visualpw_Tfm1 *)mtb->data;
		for(i=0;i<num;i++){
			if(tfm1[i].NU==(DWORD)dev.did)
			{
			  strcpy(dev.name,tfm1[i].Name);
			  return true;
			}
		}
		break;
	case 8: //三绕变
		tfm2=(visualpw_Tfm2 *)mtb->data;
		for(i=0;i<num;i++){
			if(tfm2[i].NU==(DWORD)dev.did)
			{
			  strcpy(dev.name,tfm2[i].Name);
			  return true;
			}
		}
		break;
	case 9: //SVC
		svc=(visualpw_SVC *)mtb->data;
		for(i=0;i<num;i++){
			if(svc[i].NU==(DWORD)dev.did)
			{
			  strcpy(dev.name,svc[i].Name);
			  return true;
			}
		}
		break;
	case 10://逆变器
		cvt=(visualpw_CVT *)mtb->data;
		for(i=0;i<num;i++){
			if(cvt[i].NU==(DWORD)dev.did)
			{
			  strcpy(dev.name,cvt[i].Name);
			  return true;
			}
		}
		break;
	case 11: //母线
		bus=(visualpw_Bus *)mtb->data;
		for(i=0;i<num;i++){
			if(bus[i].NU==(DWORD)dev.did)
			{
			  strcpy(dev.name,bus[i].Name);
			  return true;
			}
		}
		break;
	case 12: //交流输电线
		line=(visualpw_Line *)mtb->data;
		for(i=0;i<num;i++){
			if(line[i].NU==(DWORD)dev.did)
			{
			  strcpy(dev.name,line[i].Name);
			  return true;
			}
		}
		break;
	case 13: //直流输电线
		dcl=(visualpw_DCLine *)mtb->data;
		for(i=0;i<num;i++){
			if(dcl[i].NU==(DWORD)dev.did)
			{
			  strcpy(dev.name,dcl[i].Name);
			  return true;
			}
		}
		break;
	default:
		return false;
	}
	return false;
}


int s=0;
//通过设备名称号返回ID

bool GetDevIDByName(SELECTDEV&dev)
{
	visualpw_PT *pt;
	visualpw_Switch *swt;
	visualpw_GND *gnd;
	visualpw_CVT *cvt;
	visualpw_Gen *gen;
	visualpw_Line *line;
	visualpw_DCLine *dcl;
	visualpw_Bus  *bus;
	visualpw_Load *load;
	visualpw_Tfm1 *tfm1;
	visualpw_Tfm2 *tfm2;
	visualpw_Shunt *sht;
	visualpw_Sreact *srt;
	visualpw_SVC  *svc;

	
	DWORD idi;
	MEMTABLE *mtb;
	int t,ti,i,j,num;


	if(!dbok) //如果数据库未打开，则执行
	{
		dbok=LSI_InitNTDbi();
	}
	if(!dbok) return false; //还是打不开

	ti=dev.dtype>=33 ? dev.dtype-22:dev.dtype;
	if(ti>13||ti<0)	return false;
	
	num=0;
	t=ti;
	if(t>13||t<0) return false;
	
	if(!LSI_GetTableID(dev.dbname,devtbl[t],idi)) return false;
	j=LOWORD(idi);
	mtb=(MEMTABLE *)LSI_GetTableAdd(j);
	if(mtb==NULL) return false;
	num=mtb->userec;

	

	switch(t)
	{
	case 0: //PT
		pt=(visualpw_PT *)mtb->data;
		for(i=0;i<num;i++)
		{
			if(strcmp(pt[i].Name,dev.name)==0)
			{
			  dev.did=pt[i].NU;
			  return true;
			}
		}
		break;
	case 1: //发电机 
		gen=(visualpw_Gen *)mtb->data;
		for(i=0;i<num;i++)
		{
			if(strcmp(gen[i].Name,dev.name)==0)
			{
			   dev.did=gen[i].NU;
			   return true;
			}
		}
		break;
	case 2:	//开关，刀闸
		swt=(visualpw_Switch *)mtb->data;
		for(i=0;i<num;i++)
		{
			if(strcmp(swt[i].Name,dev.name)==0)
			{
			  dev.did=swt[i].NU;
			  return true;
			}
		}
		break;
	case 3: //负荷
		load=(visualpw_Load *)mtb->data;
		for(i=0;i<num;i++)
		{
			if(strcmp(load[i].Name,dev.name)==0)
			{
			  dev.did=load[i].NU;
			  return true;
			}
		}
		break;
	case 4:  //电容
		sht=(visualpw_Shunt *)mtb->data;
		for(i=0;i<num;i++)
		{
			if(strcmp(sht[i].Name,dev.name)==0)
			{
			  dev.did=sht[i].NU;
			  return true;
			}
		}
		break;
	case 5:  //电抗
		srt=(visualpw_Sreact *)mtb->data;
		for(i=0;i<num;i++)
		{
			if(strcmp(srt[i].Name,dev.name)==0)
			{
			  dev.did=srt[i].NU;
			  return true;
			}
		}
		break;
	case 6:  //接地
		gnd=(visualpw_GND *)mtb->data;
		for(i=0;i<num;i++)
		{
			if(strcmp(gnd[i].Name,dev.name)==0)
			{
			  dev.did=gnd[i].NU;
			  return true;
			}
		}
		break;
	case 7: //2绕变
		tfm1=(visualpw_Tfm1 *)mtb->data;
		for(i=0;i<num;i++)
		{
			if(strcmp(tfm1[i].Name,dev.name)==0)
			{
			  dev.did=tfm1[i].NU;
			  return true;
			}
		}
		break;
	case 8: //三绕变
		tfm2=(visualpw_Tfm2 *)mtb->data;
		for(i=0;i<num;i++)
		{
			if(strcmp(tfm2[i].Name,dev.name)==0)
			{
			  dev.did=tfm2[i].NU;
			  return true;
			}
		}
		break;
	case 9: //SVC
		svc=(visualpw_SVC *)mtb->data;
		for(i=0;i<num;i++)
		{
			if(strcmp(svc[i].Name,dev.name)==0)
			{
			  dev.did=svc[i].NU;
			  return true;
			}
		}
		break;
	case 10://逆变器
		cvt=(visualpw_CVT *)mtb->data;
		for(i=0;i<num;i++)
		{
			if(strcmp(cvt[i].Name,dev.name)==0)
			{
			  dev.did=cvt[i].NU;
			  return true;
			}
		}
		break;
	case 11: //母线
		bus=(visualpw_Bus *)mtb->data;
		s++;
		for(i=0;i<num;i++)
		{
			if(strcmp(bus[i].Name,dev.name)==0)
			{
			  dev.did=bus[i].NU;
			  return true;
			}
		}
		break;
	case 12: //交流输电线
		line=(visualpw_Line *)mtb->data;
		for(i=0;i<num;i++)
		{
			if(strcmp(line[i].Name,dev.name)==0)
			{
			  dev.did=line[i].NU;
			  return true;
			}
		}
		break;
	case 13: //直流输电线
		dcl=(visualpw_DCLine *)mtb->data;
		for(i=0;i<num;i++)
		{
			if(strcmp(dcl[i].Name,dev.name)==0)
			{
			  dev.did=dcl[i].NU;
			  return true;
			}
		}
		break;
	default:
		return false;
	}
	return false;
}
