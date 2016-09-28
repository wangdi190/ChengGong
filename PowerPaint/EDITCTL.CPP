// editctl.cpp : implementation file
//

#include "stdafx.h"
#include "editctl.h"
#include "jhsyslibl.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// editctl

editctl::editctl()
{
	type=0;            //0=float 1=str 2=char 3=short 2=int 
	addr=NULL;         //数据交换缓冲区地址
	strmax=1;          //字符串长度
}

editctl::~editctl()
{
}


BEGIN_MESSAGE_MAP(editctl, CEdit)
	//{{AFX_MSG_MAP(editctl)
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// editctl message handlers

void editctl::GetEditString()  //返回字符串
{
	float  *flt;
	char   *ch;
	short  *sh;
	int    *in;
	BYTE   *by;
	WORD   *wd;
	DWORD  *dw;
	double *dbl;
	CTime  *ctm;
	BOOL   *BOL;
	bool   *bol;

	int   len;
	if(addr==NULL){
		strcpy(buf,"null");
		return;
	};
	switch(type){    
	case EDIT_FLOAT:
		flt=(float*)addr;
		GetDoubleStr((double)flt[0],buf,xs);
		break;
    case EDIT_STR:
		len=strlen(addr);
		len=len>255 ? 255:len;
		strcpy(buf,addr);
		break;
	case EDIT_CHAR:
        ch=(char*)addr;
		sprintf(buf,"%d",ch[0]);
		break;
	case EDIT_SHORT:
		sh=(short*)addr;
		sprintf(buf,"%d",sh[0]);
		break;
	case EDIT_INT:
        in=(int*)addr;
		sprintf(buf,"%d",in[0]);
		break;
	case EDIT_BYTE:
		by=(BYTE*)addr;
		sprintf(buf,"%u",by[0]);
		break;
	case EDIT_WORD:
		wd=(WORD*)addr;
		sprintf(buf,"%u",wd[0]);
		break;
	case EDIT_DWORD:
		dw=(DWORD*)addr;
		sprintf(buf,"%u",dw[0]);
		break;
	case EDIT_DOUBLE:
		dbl=(double*)addr;
		GetDoubleStr(dbl[0],buf,xs);
		break;
	case EDIT_DTIME:
	    ctm=(CTime*)addr;
		sprintf(buf,"%d-%d-%2d %d:%d:%d",ctm->GetYear(),ctm->GetMonth(),
			ctm->GetDay(),ctm->GetHour(),ctm->GetMinute(),ctm->GetSecond());
		break;
	case EDIT_DATE:
	    ctm=(CTime*)addr;
		sprintf(buf,"%d-%2d-%2d",ctm->GetYear(),ctm->GetMonth(),
			ctm->GetDay());
		break;
	case EDIT_TIME:
	    ctm=(CTime*)addr;
		sprintf(buf,"%d:%d:%d",ctm->GetHour(),ctm->GetMinute(),ctm->GetSecond());
		break;
	case EDIT_BOOL:
	    BOL=(BOOL*)addr;
		sprintf(buf,"%d",BOL[0]);
		break;
	case EDIT_bool:
	    bol=(bool*)addr;
		sprintf(buf,"%d",bol[0]);
		break;
    default:
		strcpy(buf,"no data");
		};
}

void editctl::SetDataLink(char dtype, char *bf, BYTE maxl,WORD recno,BYTE xsd)  //设置数据交换
{
    type=dtype;            //数据类型
	xs=xsd;
	addr=bf;               //数据交换缓冲区地址
	strmax=maxl;           //字符串长度
	GetEditString();       //转化为字符串
	rec=recno;
	SetWindowText(buf);    //送入编辑框
}

void editctl::OnChange()   //数据变化后及时送回数据库
{
	float  *flt,f1;
	char   *ch,c1;
	short  *sh,s1;
	int    *in,i1;
	BYTE   *by,b1;
	WORD   *wd,w1;
	DWORD  *dw,d1;
	double *dbl,l1;
	CTime  *ctm,t1;
	BOOL   *BOL,BO;
	bool   *bol,bo;
	int   len;
	int year,mon,day,hour,min,sec,bz;
	if(addr==NULL) return;
	bz=0;
	len=GetWindowText(buf,256);
		
	switch(type){    
	case EDIT_FLOAT:
		flt=(float*)addr;
		f1=(float)atof(buf);
        if(flt[0]!=f1){ flt[0]=f1;bz=1;};
		break;
    case EDIT_STR:
        len=len>strmax ? strmax:len;
		if(strcmp(addr,buf)!=0) bz=1;
		strncpy(addr,buf,len);
		addr[len]=0;
		break;
	case EDIT_CHAR:
        ch=(char*)addr;
		c1=(char)atoi(buf);
		if(ch[0]!=c1) bz=1;
		ch[0]=c1;
		break;
	case EDIT_SHORT:
		sh=(short*)addr;
		s1=(short)atoi(buf);
		if(s1!=sh[0]) bz=1;
		sh[0]=s1;
		break;
	case EDIT_INT:
        in=(int*)addr;
		i1=atoi(buf);
		if(i1!=in[0]) bz=1;
		in[0]=i1;
		break;
	case EDIT_BYTE:
        by=(BYTE*)addr;
		b1=(BYTE)atoi(buf);
		if(b1!=by[0]) bz=1;
		by[0]=b1;
		break;
	case EDIT_WORD:
        wd=(WORD*)addr;
		w1=(WORD)atoi(buf);
		if(w1!=wd[0]) bz=1;
		wd[0]=w1;
		break;
	case EDIT_DWORD:
        dw=(DWORD*)addr;
		d1=(DWORD)atoi(buf);
		if(d1!=dw[0]) bz=1;
		dw[0]=d1;
		break;
	case EDIT_DOUBLE:
        dbl=(double*)addr;
		l1=(double)atof(buf);
		if(l1!=dbl[0]) bz=1;
		dbl[0]=l1;
		break;
	case EDIT_DTIME:
		ctm=(CTime*)addr;
		i1=sscanf(buf,"%d-%d-%d %d:%d:%d",&year,&mon,&day,&hour,&min,&sec);
		if(i1==6&&IsNorTime(year,mon,day,hour,min,sec)){
			t1=CTime(year,mon,day,hour,min,sec);
		    if(t1!=ctm[0]) bz=1;
		    ctm[0]=t1;
		};
		break;
	case EDIT_DATE:
		ctm=(CTime*)addr;
		i1=sscanf(buf,"%d-%d-%d",&year,&mon,&day);
		if(i1>=3&&IsNorTime(year,mon,day,8,0,0)){
			t1=CTime(year,mon,day,8,0,0);
		    if(t1!=ctm[0]) bz=1;
		    ctm[0]=t1;
		};
		break;
	case EDIT_TIME:
		ctm=(CTime*)addr;
		i1=sscanf(buf,"%d:%d:%d",&hour,&min,&sec);
		if(i1>=3&&IsNorTime(1999,12,31,hour,min,sec)){
			t1=CTime(1999,12,31,hour,min,sec);
		    if(t1!=ctm[0]) bz=1;
		    ctm[0]=t1;
		};
		break;
	case EDIT_BOOL:
		BOL=(BOOL*)addr;
		BO=atoi(buf)==0 ? 0:1;
		if(BO!=BOL[0]) bz=1;
		BOL[0]=BO;
		break;
	case EDIT_bool:
		bol=(bool*)addr;
		bo=atoi(buf)==0 ? 0:1;
		if(bo!=bol[0]) bz=1;
		bol[0]=bo;
		break;
    default:
		break;
		};
	if(bz==1){
		GetParent()->GetParent()->SendMessage(WM_COMMAND,DataChanged,rec);
	}
}



int editctl::IsNorTime(int year, int mon, int day, int hour, int min, int sec)
{
	if(year<1970||year>2038) return 0;
	if(mon<1||mon>12)   return 0;
	if(day<1||day>31)   return 0;
	if(hour<0||hour>23) return 0;
	if(min<0||min>59)   return 0;
	if(sec<0||sec>59)   return 0;
	return 1;
}


LRESULT editctl::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if(message==WM_KEYDOWN){
		if(wParam==VK_DOWN||wParam==VK_UP){
		 GetParent()->SendMessage(message,wParam,lParam);
		};
	};
	if(message==WM_CHAR){
		if(wParam==0xd){
		 GetParent()->SendMessage(message,wParam,lParam);
		};
	};
	return CEdit::WindowProc(message, wParam, lParam);
}