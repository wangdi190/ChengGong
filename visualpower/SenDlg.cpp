// SenDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPower.h"
#include "SenDlg.h"
#include "comobj.h"
#include "middll.h"
#include "bclass.h"
#include "DObj.h"
#include "gdata.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char *typestr[]={"灵敏度类型:\n发电机和负荷对线路的灵敏度。",
"灵敏度类型:\n发电机、电容器和变压器对节点电压的灵敏度。"};

extern comobj  cobj;
/////////////////////////////////////////////////////////////////////////////
// SenDlg dialog

SenDlg::SenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SenDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SenDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	type=0;
	hpr=0;
	selpt.x=0;
	selpt.y=0;
}
SenDlg::~SenDlg()
{
	KillTimer(100);
}

void SenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SenDlg)
	DDX_Control(pDX, IDC_SENTYPE, m_type);
	DDX_Control(pDX, IDC_PROGRESS1, m_prg);
	DDX_Control(pDX, IDC_DEV, m_dev);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SenDlg, CDialog)
	//{{AFX_MSG_MAP(SenDlg)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SenDlg message handlers

BOOL SenDlg::OnInitDialog() 
{
	char p[100];
	CDialog::OnInitDialog();
	
	//获取选择的设备ID号
	if(type>=0&&type<2) m_type.SetWindowText(typestr[type]);
	switch(type)
	{
	case 0: //线路
		ComputeBra();
			break;
	case 1:
		ComputeBus();
		break;
	}
	if(id==-1){
		MessageBox(str,"灵敏度选择错误",MB_ICONSTOP);
		CDialog::OnCancel();
		return false;
	}
	if(type==0&&id>=0)
	{
		nodefrom=ReadLineNodeFrom(); //读取线路起始节点
		id=NT_GetDevID(id,2);
		if(nodefrom==-1){
			sprintf(p,"该%s线路在数据库中不存在！\n请验证数据库中的该条记录。",type==0 ? "交流":"直流");
			MessageBox(p,"错误",MB_ICONSTOP);
			CDialog::OnCancel();
			return false;
		}
	}
	//演示示时用，正式版本将这两行去掉
	//CDialog::OnOK();
	//return true;
	
	
	
	StartRun();
	return TRUE; 
}

void SenDlg::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent==100)	CheckCompute();
	CDialog::OnTimer(nIDEvent);
}

void SenDlg::OnCancel() 
{
	KillTimer(100);
	CDialog::OnCancel();
}

//计算相交母线
void SenDlg::ComputeBra()
{
	int i,j,n,rtn;
	CRect rt;
	POINT pt1[20],ptt;
	HRGN hrgn1,hrgn2;
	CDPoint apt;
	id=-1;
	name[0]=0;
	hrgn1=SCreateLineRGN(pt,ptsum);
	hrgn2=NULL;
	for(i=0;i<fwsum;i++){
		n=r_fw[i].ptsum;
		n=n>20 ? 20:n;
		for(j=0;j<n;j++){
			pt1[j].x=(int)((double)(r_fw[i].flw->pt[j].x*dbm->curzoom));
			pt1[j].y=(int)((double)(r_fw[i].flw->pt[j].y*dbm->curzoom));
		}
		if(hrgn2!=NULL) DeleteObject(hrgn2);
		hrgn2=SCreateLineRGN(pt1,n);
		rtn=CombineRgn(hrgn2,hrgn1,hrgn2,RGN_AND);
		if(rtn!=NULLREGION){
			id=r_fw[i].flw->did;
			strcpy(name,r_fw[i].flw->dev_name);
			linetype=r_fw[i].flw->type;
			GetRgnBox(hrgn2,&rt);
			ptt=rt.CenterPoint();
			apt.x=(double)ptt.x;
			apt.y=(double)ptt.y;
			apt.ScrPtToAct(dbm->curzoom);
			selpt.x=apt.x;
			selpt.y=apt.y;
			break;
		}
	}
	if(hrgn1!=NULL) DeleteObject(hrgn1);	
	if(hrgn2!=NULL) DeleteObject(hrgn2);
	if(id!=-1) sprintf(str,"选择的线路:线路id=%d  线路名=%s",id,name);
	else strcpy(str,"没有选择到线路,请重新选择！");
	m_dev.SetWindowText(str);
}

//计算相交母线（节点）
void SenDlg::ComputeBus()
{
	int id1;
	HRGN hrgn1,hrgn2;
	CDRect art;
	CRect crt;
	int i,rtn;
	id=-1;
	id1=-1;
	name[0]=0;
	hrgn1=SCreateLineRGN(pt,ptsum);
	hrgn2=NULL;
	for(i=0;i<bssum;i++){
		art=CreateDrawNRt(4,r_bs[i].bus->pt,dbm->curzoom);
		art.GetRECT(crt);
		if(hrgn2!=NULL) DeleteObject(hrgn2);
		hrgn2=CreateRectRgn(crt.left,crt.top,crt.right,crt.bottom);
		rtn=CombineRgn(hrgn2,hrgn1,hrgn2,RGN_AND);
		if(rtn!=NULLREGION){
			id1=r_bs[i].bus->did;
			id=NT_GetDevID(id1,1);
			strcpy(name,r_bs[i].bus->dev_name);
			selpt=r_bs[i].bs->ort.CenterPoint();
			break;
		}
	}
	if(hrgn1!=NULL) DeleteObject(hrgn1);	
	if(hrgn2!=NULL) DeleteObject(hrgn2);
	if(id!=-1) sprintf(str,"选择的母线:母线id=%d  母线名=%s",id,name);
	else if(id1>=0) strcpy(str,"库中没有选择到的母线,请重新选择!");
	else strcpy(str,"没有选择到母线,请重新选择!");
	m_dev.SetWindowText(str);
}


//读取线路起始节点
int SenDlg::ReadLineNodeFrom()
{
	int nf,nt;
	LinData  acdata;//交流
	DLinData dcdata;//直流
	switch(linetype){
	case 0: //交流
		memset(&acdata,0,sizeof(LinData));
		acdata.lid=id;
		NT_GetDevBusID(id,2,nf,nt);
		return nf;
	case 1: //直流
		memset(&dcdata,0,sizeof(DLinData));
		dcdata.lid=id;
		NT_GetDevBusID(id,2,nf,nt);
		return nf;
	}
	return -1;
}


//开始计算
void SenDlg::StartRun()
{
	PROCESS_INFORMATION li;
	STARTUPINFO  st;
	//先设置目录(设置为启动目录)
	SetCurrentDirectory(cobj.startpath);
	//检测ACSOPF02.EXE是否存在
	if(!cobj.IsFileExist("ACSOPF02.exe"))
	{
		MessageBox("acsopf02.exe及其相关文件不存在，不能进行灵敏度计算！","错误",MB_ICONSTOP);	
		CDialog::OnCancel();
		return;
	}
	//以下是准备计算的相关工作
	//生成DAT文件
	NT_CreateDAT("tmp.dat");
	//生成宏文件
	CreateMacFile("tmp.mac");
	//2.执行计算
	memset(&li,0,sizeof(PROCESS_INFORMATION));
	memset(&st,0,sizeof(STARTUPINFO));
	st.cb=sizeof(STARTUPINFO);
	st.wShowWindow=SW_HIDE;
	st.dwFlags=STARTF_USESHOWWINDOW;
	CreateProcess(NULL,"CMD.EXE /c ACSOPF02.exe<tmp.mac",NULL,NULL,FALSE,0,NULL,NULL,&st,&li);
	hpr=(HANDLE)li.hProcess;
	nt=0;
	m_prg.SetRange(0,100);
	SetTimer(100,150,NULL);
}


extern char *lsenstr[];
extern char *nsenstr[];
//生成宏文件
void SenDlg::CreateMacFile(char *filename)
{
	FILE *fp;
	fp=fopen(filename,"w+t");
	if(fp==NULL) return;
	switch(type)
	{
	case 0: //线路
		fprintf(fp,"%s",lsenstr[0]);
		fprintf(fp,"%d\n",nodefrom);
		fprintf(fp,"%d\n",id);
		fprintf(fp,"%s",lsenstr[3]);
		break;
	case 1: //节点
		fprintf(fp,"%s",nsenstr[0]);
		fprintf(fp,"%d\n",id);
		fprintf(fp,"%s",nsenstr[2]);
		break;
	}
	fclose(fp);
}


//察看进程是否在运行
bool SenDlg::IsProcessActive()
{
	DWORD ex;
	if(hpr==0) return false;
	int b=GetExitCodeProcess(hpr,&ex);
	if(b==0) return false;
	if(b==1&&ex==0) return false;
	return true;
}
//检查计算进程是否在进行
void SenDlg::CheckCompute()
{
	nt+=12;
	if(nt>60) nt=60;
	m_prg.SetPos(nt);
	if(IsProcessActive()) return; //表示还在运行
	KillTimer(100);
	//进行数据转换
	//1.出理收敛报告
	if(NT_FileConvertInput("CONVERGE.OUT")!=0)//不收敛
	{ 
		MessageBox("计算结果不收敛！\n请检查相关电网数据库和实时数据是否正确。","错误",MB_ICONSTOP);	
		SaveDataFile();
		CDialog::OnCancel();
		return;
	}
	m_prg.SetPos(80);
	if(!cobj.IsFileExist("tmp.out"))
	{
		MessageBox("没有产生输出结果文件！不能得到灵敏度结果。\n请检查数据库是否正确。","错误",MB_ICONSTOP);	
		CDialog::OnCancel();
		return;
	}
	if(NT_FileOutInput("tmp.out",type)!=0)
	{
		MessageBox("计算结果转换出错！\n请检查数据库是否正确。","错误",MB_ICONSTOP);	
		CDialog::OnCancel();
		return;
	}
	m_prg.SetPos(100);
	CDialog::OnOK();
}

//当计算结果不收敛时保存data文件
void SenDlg::SaveDataFile()
{
	char desnm[512];
	CTime tm=CTime::GetCurrentTime();
	sprintf(desnm,"%s\\sen_%d年%d月%d日%d点%d分%d秒.dat",cobj.senfilepath,tm.GetYear(),tm.GetMonth(),tm.GetDay(),
		tm.GetHour(),tm.GetMinute(),tm.GetSecond());
	CopyFile("tmp.dat",desnm,false);
}


