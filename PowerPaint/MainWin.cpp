// MainWin.cpp : implementation of the CMainWin class
//

#include "stdafx.h"
#include "PowerPaint.h"
#include "MainWin.h"
#include "gdata.h"
#include "comobj.h"
#include "prtmode.h"
#include "middll.h"
#include "bfcfgdlg.h"
#include "cfgzmdlg.h"
#include "GetNMDlg.h"
#include "GetIDDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
CImageList  othimg;
gdata	dbm;
comobj  cobj;

extern int testflag;
/////////////////////////////////////////////////////////////////////////////
// CMainWin

CMainWin::CMainWin()
{
	
}

CMainWin::~CMainWin()
{
	UnRegistFileOK(tmphwnd);
}


BEGIN_MESSAGE_MAP(CMainWin,CWnd )
	//{{AFX_MSG_MAP(CMainWin)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(IDC_PRINT, OnPrint)
	ON_COMMAND(IDC_TEST,  OnTest)
	ON_COMMAND(IDC_PUTOUT, OnPutout)
	ON_UPDATE_COMMAND_UI(IDC_PUTOUT, OnUpdatePutout)
	ON_COMMAND(IDC_TOHMIDIR, OnTohmidir)
	ON_COMMAND(IDC_BUSRALATE, OnBusralate)
	ON_COMMAND(IDC_ZMCTL, OnZmctl)
	ON_UPDATE_COMMAND_UI(IDC_TOSQRT, OnUpdateTosqrt)
	ON_COMMAND(IDC_GETNM, OnGetnm)
	ON_COMMAND(IDC_GETID, OnGetid)
	ON_COMMAND(IDC_OUTSVG, OnOutsvg)
	ON_COMMAND(IDC_LOADCIM, OnLoadcim)
	ON_COMMAND(IDC_SVGNAME, OnSvgname)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMainWin message handlers

BOOL CMainWin::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	//cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), NULL, NULL);

	return TRUE;
}

void CMainWin::OnPaint() 
{
	CPaintDC dc(this); 
	spl.OnPaint(dc);
}


int CMainWin::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd ::OnCreate(lpCreateStruct) == -1)
		return -1;
	//设置3d环境为平面//////////////////////////////////////////////////
	//Set3DEnv(0,1024,768,0);
	////////////////////////////////////////////////////////////////////

	othimg.Create(IDB_BITMAP4,32,0,RGB(255,0,255));
	
	tlw.Create("","",WS_CHILD|WS_VISIBLE,CRect(0,0,1,1),this,101);
	wkw.Create("","",WS_CHILD|WS_VISIBLE,CRect(0,0,1,1),this,100);
	

	spl.Create(this,&tlw,&wkw,NULL,0);
	spl.SetInitPosition(240);
	cobj.wwin=&wkw;
	cobj.tlsw=&tlw;
	//数据库操作
	dbm.dbfok=InitMemDbf();
	if(!dbm.dbfok){
		MessageBox("内存库平台未启动，有些牵涉到数据库的操作将被禁止！","错误",MB_ICONSTOP);
		return 0;
	}
	//读取数据库颜色
	cobj.ReadDefColor();
	//取得与数据库相关的界面文件目录
	GetHmiPath(cobj.path[1].path);
	//注册文件接收通知
	RegistFileOK(m_hWnd);
	tmphwnd=m_hWnd;
	return 0;
}

void CMainWin::OnSize(UINT nType, int cx, int cy) 
{
	CWnd ::OnSize(nType, cx, cy);
	if(cx>10&&cy>10) spl.OnSize(cx,cy);
}

void CMainWin::OnLButtonDown(UINT nFlags, CPoint point) 
{
	spl.OnLButtonDown(point);
	
	CWnd ::OnLButtonDown(nFlags, point);
}

void CMainWin::OnLButtonUp(UINT nFlags, CPoint point) 
{
	spl.OnLButtonUp(point);
	CWnd ::OnLButtonUp(nFlags, point);
}

void CMainWin::OnMouseMove(UINT nFlags, CPoint point) 
{
	spl.OnMouseMove(point);
		
	CWnd ::OnMouseMove(nFlags, point);
}

BOOL CMainWin::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	if (wkw.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;
	if (tlw.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;
	return CWnd ::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

//页面改变
void CMainWin::PageChange(int page)
{
	dbm.GoToPage(page);
	cobj.cvs->PageChange();
	wkw.SetTitlename();
}

void CMainWin::OnPrint() 
{
	BYTE pm;
	char p[100];
	double zm,pdx,pdy;
	int i,j,mok,mx,my;
	int yl,w,h,kw,kh,dx,dy,ht,mh;
	DEVMODE *dev,devmode;
	double bl;
	CPrintDialog pdlg(true);
	if(pdlg.DoModal()==IDOK){
		dev=pdlg.GetDevMode();
		devmode=dev[0];
	}else return;

	PMODE lppm;
	CPrtMode pmdlg(&lppm);
	mok=pmdlg.DoModal();
	if(mok==IDCANCEL) return;
	if(lppm.mode<1) pm=1;else pm=0;


	HDC hdc=pdlg.CreatePrinterDC();
	if(hdc==NULL){
		MessageBox("当前选择的打印机不存在\n请重新选择打印机后再式");	
		return;
	}
	kw=dbm.cpage->head.width;
	kh=dbm.cpage->head.height;
	yl=devmode.dmPrintQuality;
	
	if(devmode.dmOrientation==1){ //确定方向：1为正常方向
		w=devmode.dmPaperWidth-100;
		h=devmode.dmPaperLength-100;
	}else{
		h=devmode.dmPaperWidth-100;
		w=devmode.dmPaperLength-100;
	};
	

	//每页纸的象素大小
	w=(int)(w*yl/255);
	h=(int)(h*yl/255);
	zm=cobj.curzoom;
	cobj.curzoom=1;
	bl=kw/(double)kh;
	ht=(int)(w/bl);


	//单张纸的特殊处理方式
	if(lppm.px==0){
		if(ht<h){
			dx=0;
			dy=((h-ht)*kw/w)/2;
			h=ht;
		}else{	
			dy=0;
			dx=(int)(((w-h*bl)*kh/h)/2);
			w=(int)(h*bl);
		}
		//////////////// 打 印 到 纸 上 ///////////////////
		StartDoc(hdc,NULL);
		SetMapMode(hdc,MM_ISOTROPIC);
		SetWindowExtEx(hdc,kw,kh,NULL);
		SetViewportExtEx(hdc,w,h,NULL);
		StartPage(hdc);
		dbm.PrintShow(hdc,pm,dx,dy);
		EndPage(hdc);
		EndDoc(hdc);
		DeleteDC(hdc);
		///////////////////////////////////////////////////
	}
	//放大打印
	if(lppm.px>0){
		mx=lppm.px+1;  //x方向的纸张数
		mh=ht*mx;	   //需要的总高度
		my=mh/h;	   //计算纵向所需纸张数
		j=mh-my*h;
		if(j>0) my++;
		sprintf(p,"所需纸张数:%d张。\n还需打印吗? ",mx*my);
		mok=MessageBox(p,"打印最后确认",MB_YESNO);
		if(mok==IDNO) return;
		w=w*mx;
		pdx=(double)((double)kw/(double)mx);
		pdy=(double)((double)mh/(double)h);
		pdy=(double)((double)kh/pdy);

		
		for(i=0;i<my;i++){
			for(j=0;j<mx;j++){
				//////////////// 打 印 到 纸 上 ///////////////////
				dx=(int)(j*pdx);
				dy=(int)(i*pdy);
				StartDoc(hdc,NULL);
				SetMapMode(hdc,MM_ISOTROPIC);
				SetWindowExtEx(hdc,kw,kh,NULL);
				SetViewportExtEx(hdc,w,mh,NULL);
				StartPage(hdc);
				dbm.PrintShow(hdc,pm,-dx,-dy);
				EndPage(hdc);
				EndDoc(hdc);
				///////////////////////////////////////////////////
			}
		}
		DeleteDC(hdc);
	}
	cobj.curzoom=zm;
}

//测试窗口
void CMainWin::OnTest() 
{
	int w,h;
	testflag=1;
	w=GetSystemMetrics(SM_CXSCREEN);
	h=GetSystemMetrics(SM_CYSCREEN);
	tstw.Createtun(WS_POPUPWINDOW|WS_VISIBLE|WS_CAPTION,CRect(0,0,w,h),this);
	tstw.SetPage();
}

void CMainWin::OnUpdatePutout(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(dbm.filebz==1&&dbm.dbfok==true ? true:false);
}

//发布当前编辑文件
void CMainWin::OnPutout() 
{
	char fnm[256];
	if(MessageBox("确实要将本界面及其相关文件发布吗？","发布界面文件",MB_YESNO)!=IDYES) return;
	//将界面的关联文件拷贝到界面目录
	dbm.CopyToHmiDir();
	//先保存当前文件
	wkw.OnFileSave();
	//拷贝pw0界面文件
	strcpy(fnm,dbm.pwfname);
	MessageBox(fnm,"界面发布",MB_OK);
	dbm.CopyFileTo(fnm);
	//发送文件到服务器
	dbm.SendHmiToSvr();
	MessageBox("文件发布完毕!\n各节点已具有与本界面一样的界面！","界面发布",MB_OK);
}

void CMainWin::OnTohmidir() 
{
	char fnm[256];
	if(MessageBox("确实要将本界面及其相关文件收集到界面目录吗？","收集界面文件",MB_YESNO)!=IDYES) return;
	//将界面的关联文件拷贝到界面目录
	dbm.CopyToHmiDir();
	//先保存当前文件
	wkw.OnFileSave();
	//拷贝pw0界面文件
	strcpy(fnm,dbm.pwfname);
	dbm.CopyFileTo(fnm);
}


LRESULT CMainWin::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	char fnm[256];
	if(message==1310&&wParam==5){ //文件更新后，是否需要重新调入
		GetLastRecFile(fnm);
		wkw.RecFileOkOpen(fnm);
	}
	return CWnd ::WindowProc(message, wParam, lParam);
}
//编辑母线动态关联
void CMainWin::OnBusralate() 
{
	BFCfgDlg dlg;
	dlg.cpage=dbm.cpage;
	dlg.DoModal();
}
//多界面互控配置
void CMainWin::OnZmctl() 
{
	int i;
	N_APDINFO tmp;
	CCfgZmDlg dlg;
	//获取当页的控制信息
	i=dbm.GetIndexOfAppInfo((BYTE)dbm.curpage);
	if(i>=0) tmp=dbm.apdinfo[i];			//存在，则取出
	else memset(&tmp,0,sizeof(N_APDINFO));	//不存在则用临时摸板
	dlg.tmp=tmp;
	if(dlg.DoModal()!=IDOK) return;

	//保存编辑的结果
	tmp=dlg.tmp;
	tmp.pageno=(BYTE)dbm.curpage;
	if(tmp.enablein==0&&tmp.enableout==0) //同时取消时，删除原有的记录
	{
		if(i>=0) dbm.DelAAppendInfo((BYTE)dbm.curpage);
		dbm.editbz=1;
		return;
	}
	if(i>=0) dbm.apdinfo[i]=tmp;
	else dbm.AddAppendInfo(tmp);
	dbm.editbz=1;
}

void CMainWin::OnUpdateTosqrt(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(dbm.GetFirstSelObj()<0 ? false:true);
	
}

void CMainWin::OnGetnm() 
{
	GetNMDlg dlg;
	dlg.dbm=&dbm;
	dlg.DoModal();
}

void CMainWin::OnGetid() 
{
	GetIdDlg dlg;
	dlg.dbm=&dbm;
	dlg.DoModal();
}

//输出SVG格式
void CMainWin::OnOutsvg() 
{
	char filter[256],path[256],title[64];
	char fnm[256];
	char *lp;
	strcpy(path,cobj.path[1].path);
	strcpy(title,"保存为SVG图形格式文件");
	strcpy(filter,"SVG格式文件(*.svg)|*.svg");
	CFileDialog  fodlg(false,NULL,NULL,OFN_CREATEPROMPT|OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filter,this);
	fodlg.m_ofn.lpstrTitle=title;
	fodlg.m_ofn.lpstrInitialDir=path;
	if(fodlg.DoModal()==IDOK)
	{
	  strcpy(fnm,fodlg.GetPathName());
	  lp=strchr(fnm,'.');
	  if(lp!=NULL) *lp=0;
	  strcat(fnm,".svg");
	  dbm.SaveFileSvg(fnm);
	};
}

//调入CIM模型
void CMainWin::OnLoadcim() 
{
	char filter[512],fnm[512],title[64];
	strcpy(title,"打开CIM XML文件");
	strcpy(filter,"CIM XML文件(*.xml)|*.xml|");
	CFileDialog  fodlg(true,NULL,NULL,
		OFN_FILEMUSTEXIST|OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filter,this);
	fodlg.m_ofn.lpstrTitle=title;
	if(fodlg.DoModal()==IDOK){
	  strcpy(fnm,fodlg.GetPathName());
	  ReadPowerCimFile(fnm);
	};
}

void CMainWin::OnSvgname() 
{
	if(!IsCimOpen())
	{
		MessageBox("CIM模型未打开，不能进行名字更换!","错误",MB_OK|MB_ICONSTOP);
		return;
	}
	dbm.ExchangeCimName();
	MessageBox("从CIM更新设备名字完成！\n之后，采用[自动从设备名升级ID]即可完成SVG图形免维护工作.","提示",MB_OK);
}
