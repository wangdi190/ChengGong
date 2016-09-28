// CrossObj.cpp: implementation of the CCrossObj class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VisualPower.h"
#include "CrossObj.h"
#include "bclass.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCrossObj::CCrossObj()
{
	fwsum=0;		//个数
	segsum=0;		//截面点数
	r_fw=NULL;
	pt=NULL;
	dbm=NULL;
}

CCrossObj::~CCrossObj()
{

}

//返回交叉的线路
bool CCrossObj::GetCrossLine(DMSECT &dm)
{
	int i,j,n,s,rtn;
	POINT pt1[20];
	HRGN hrgn1,hrgn2;
	double Imax,I,Pmax,Pcur;
	if(segsum<=0) return false;
	//生成区域多段画线区域
	hrgn1=SCreateLineRGN(pt,dmdot[0]);
	n=dmdot[0];
	for(i=1;i<segsum;i++)
	{
		hrgn2=SCreateLineRGN(&pt[n],dmdot[i]);
		CombineRgn(hrgn1,hrgn1,hrgn2,RGN_OR);
		DeleteObject(hrgn2);
		n+=dmdot[i];
	}
	hrgn2=NULL;
	s=0;
	Imax=0;
	I=0;
	Pmax=0;
	Pcur=0;
	//第一步:将点转换为实际值
	if(r_fw==NULL||pt==NULL||dbm==NULL) return false;
	n=n>500 ? 500:n;
	for(i=0;i<n;i++)
	{
		dm.pt[i].x=pt[i].x/dbm->curzoom;
		dm.pt[i].y=pt[i].y/dbm->curzoom;
	}
	for(i=0;i<segsum;i++)
	{
		dm.dmsdot[i]=dmdot[i];
	}
	dm.segsum=segsum;
	//dm.ptsum=n;
	//第二步:计算交叉线
	for(i=0;i<fwsum;i++)
	{
		n=r_fw[i].ptsum;
		n=n>20 ? 20:n;
		for(j=0;j<n;j++)
		{
			pt1[j].x=(int)((double)(r_fw[i].flw->pt[j].x*dbm->curzoom));
			pt1[j].y=(int)((double)(r_fw[i].flw->pt[j].y*dbm->curzoom));
		}
		if(hrgn2!=NULL) DeleteObject(hrgn2);
		hrgn2=SCreateLineRGN(pt1,n);
		rtn=CombineRgn(hrgn2,hrgn1,hrgn2,RGN_AND);
		if(rtn!=NULLREGION){ //添加
			Imax+=r_fw[i].flw->vr.value[6];
			I+=r_fw[i].flw->vr.value[7];
			Pmax+=r_fw[i].flw->vr.value[4];
			Pcur+=r_fw[i].flw->vr.value[0];//r_fw[i].flw->ps;
			if(s<32){
			  dm.ls[s].type=r_fw[i].flw->type;
			  dm.ls[s].id=r_fw[i].flw->did;
			  dm.ls[s].jlh=r_fw[i].recno;
			}
			s++;
			if(s>=32) break;
		}
	}
	if(hrgn1!=NULL) DeleteObject(hrgn1);	
	if(hrgn2!=NULL) DeleteObject(hrgn2);
	strcpy(dm.name,"新断面");
	dm.lsum=s;
	dm.Imax=(float)Imax;
	dm.Icur=(float)I;
	dm.Pmax=(float)Pmax;
	dm.Pcur=(float)Pcur;
	return s>0 ? true:false;
}
