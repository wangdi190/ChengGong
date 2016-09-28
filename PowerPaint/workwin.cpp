// workwin.cpp : implementation file
//

#include "stdafx.h"
#include "PowerPaint.h"
#include "workwin.h"
#include "gdata.h"
#include "comobj.h"
#include "guiddlg.h"
#include "cfgcrdlg.h"
#include "patrdlg.h"
#include "CheckSvgType.h"
#include "ImportDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern gdata dbm;
extern comobj cobj;
int  whw[]={30,15*27,30,19*27,30,-1,-1,-1};

char *ftr[]={"图形文件(支持15种格式)|*.bmp;*.jpg;*.tga;*.pcd;*.pcx;",
   "*.tif;*.gif;*.RLE;*.jpg;*.VDA;*.ICB;*.VST;*.pbm;*.pgm;*.ppm",
   "Windows and OS/2 BMP文件(*.BMP,*.RLE)|*.bmp;*.rle",
   "JPEG文件(*.JPG;*.JPE)|*.jpg;*.jpe",
   "Targa文件(*.TGA;*.VDA;*.ICB;*.VST)|*.tga;*.vda;*.icb;*.vst",
   "Photo CD文件(*.PCD)|*.pcd",
   "Tiff TIF文件(*.TIF)|*.tif",
   "GIF89a文件(*.GIF)|*.gif",
   "Portable Bit Map(*.PBM;*.PGM;*.PPM)|*.pbm;*.pgm;*.ppm"};
/////////////////////////////////////////////////////////////////////////////
// workwin
workwin::workwin()
{
	/*int i;
	for(i=0;i<4;i++){
		win[i].show=1;
		win[i].height=whw[i*2]; 
		win[i].width=whw[i*2+1];
	}
	win[0].wnd=(CWnd*)&tb1;
	win[1].wnd=(CWnd*)&tb2;
	win[2].wnd=(CWnd*)&ptl;
	win[3].wnd=(CWnd*)&cvs;*/

}

workwin::~workwin()
{

}

BEGIN_MESSAGE_MAP(workwin, CWnd)
	//{{AFX_MSG_MAP(workwin)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_NORMAL, OnNormal)
	ON_COMMAND(ID_MOVEPIC, OnMovepic)
	ON_COMMAND(ID_PARTZOOM, OnPartzoom)
	ON_COMMAND(ID_ZOOMIO, OnZoomio)
	ON_COMMAND(ID_LINE_ADDDOT, OnLineAdddot)
	ON_COMMAND(ID_LINE_SUBDOT, OnLineSubdot)
	ON_COMMAND(ID_CUTLINE, OnCutline)
	ON_COMMAND(ID_BINDLINE, OnBindline)
	ON_COMMAND(ID_CLEARIMG, OnClearimg)
	ON_COMMAND(ID_CUTIMG, OnCutimg)
	ON_COMMAND(ID_TRANIMG, OnTranimg)
	ON_COMMAND(ID_PAINTIMG, OnPaintimg)
	ON_COMMAND(ID_BRIGHTIMG, OnBrightimg)
	ON_COMMAND(ID_SETREGON, OnSetregon)
	ON_COMMAND(ID_CUTREGON, OnCutregon)
	ON_COMMAND(ID_LINE, OnLine)
	ON_COMMAND(ID_RECT, OnRect)
	ON_COMMAND(ID_CIRCLE, OnCircle)
	ON_COMMAND(ID_HSIN, OnHsin)
	ON_COMMAND(ID_SIN, OnSin)
	ON_COMMAND(ID_COORD, OnCoord)
	ON_COMMAND(ID_ARC, OnArc)
	ON_COMMAND(ID_ARROW, OnArrow)
	ON_COMMAND(ID_GLASS, OnGlass)
	ON_COMMAND(ID_CBAR, OnCbar)
	ON_COMMAND(ID_TEXT, OnText)
	ON_COMMAND(ID_ESITE, OnEsite)
	ON_COMMAND(ID_EGPMB, OnEgpmb)
	ON_COMMAND(ID_TABLE, OnTable)
	ON_COMMAND(ID_IMAGE, OnImage)
	ON_COMMAND(ID_PATH, OnPath)
	ON_COMMAND(ID_ANALOG, OnAnalog)
	ON_COMMAND(ID_BAR, OnBar)
	ON_COMMAND(ID_PIE, OnPie)
	ON_COMMAND(ID_DATE, OnDate)
	ON_COMMAND(ID_TIME, OnTime)
	ON_COMMAND(ID_GIFANL, OnGifanl)
	ON_COMMAND(ID_SCRTEXT, OnScrtext)
	ON_COMMAND(ID_PUSH, OnPush)
	ON_COMMAND(ID_SELFCTL, OnSelfctl)
	ON_COMMAND(ID_CONLINE, OnConline)
	ON_COMMAND(ID_FLOW, OnFlow)
	ON_COMMAND(ID_BUS, OnBus)
	ON_COMMAND(ID_ACTOBJ, OnActobj)
	ON_COMMAND(ID_FLASH, OnFlash)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_GOTOTOP, OnGototop)
	ON_COMMAND(ID_GOTOBUTTOM, OnGotobuttom)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_COMMAND(IDC_STRAIGHT, OnStraight)
	ON_COMMAND(ID_IMGSTRATCH, OnImgstratch)
	ON_COMMAND(ID_FILTER_GRAY, OnFilterGray)
	ON_COMMAND(ID_FILTER_REV, OnFilterRev)
	ON_COMMAND(ID_FILTER_SMOTH, OnFilterSmoth)
	ON_COMMAND(ID_FILTER_WL, OnFilterWl)
	ON_COMMAND(ID_TRAN_MIR, OnTranMir)
	ON_COMMAND(ID_TRAN_UD, OnTranUd)
	ON_COMMAND(ID_BD_BLACK, OnBdBlack)
	ON_COMMAND(ID_BD_BLK, OnBdBlk)
	ON_COMMAND(ID_BD_BRIGHT, OnBdBright)
	ON_COMMAND(IDC_COPYTOCLIB, OnCopytoclib)
	ON_COMMAND(IDC_PASTECLIB, OnPasteclib)
	ON_COMMAND(IDC_CUTNOUSE, OnCutnouse)
	ON_COMMAND(IDC_SETPAGE, OnSetpage)
	ON_COMMAND(IDC_DRAWATTR, OnDrawattr)
	ON_COMMAND(ID_VLCOLOR, OnVlcolor)
	ON_COMMAND(IDC_FILLPTN, OnFillptn)
	ON_COMMAND(IDC_FILLCOLOR, OnFillcolor)
	ON_COMMAND(IDC_SHOWGUIDE, OnShowguide)
	ON_COMMAND(IDC_GUIDE, OnGuide)
	ON_COMMAND(IDC_EGPTOSGL, OnEgptosgl)
	ON_COMMAND(IDC_RESETSITE, OnResetsite)
	ON_COMMAND(IDC_SHOWSITE, OnShowsite)
	ON_COMMAND(IDC_NOCONDEV, OnNocondev)
	ON_COMMAND(IDC_NOCDEV, OnNocdev)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(IDC_ADDPAGE, OnAddpage)
	ON_COMMAND(IDC_ADDLAYER, OnAddlayer)
	ON_COMMAND(IDC_DELCURPAGE, OnDelcurpage)
	ON_COMMAND(IDC_DELCURLAYER, OnDelcurlayer)
	ON_COMMAND(ID_PCTPIE, OnPctpie)
	ON_COMMAND(IDC_TOSQRT, OnTosqrt)
	ON_COMMAND(ID_METER1, OnMeter1)
	ON_COMMAND(ID_METER2, OnMeter2)
	ON_COMMAND(ID_METER3, OnMeter3)
	ON_COMMAND(ID_METER4, OnMeter4)
	ON_UPDATE_COMMAND_UI(ID_METER1, OnUpdateMeter1)
	ON_UPDATE_COMMAND_UI(ID_METER2, OnUpdateMeter2)
	ON_UPDATE_COMMAND_UI(ID_METER3, OnUpdateMeter3)
	ON_UPDATE_COMMAND_UI(ID_METER4, OnUpdateMeter4)
	ON_UPDATE_COMMAND_UI(ID_ANALOG, OnUpdateAnalog)
	ON_UPDATE_COMMAND_UI(ID_ACTOBJ, OnUpdateActobj)
	ON_UPDATE_COMMAND_UI(ID_PCTPIE, OnUpdatePctpie)
	ON_UPDATE_COMMAND_UI(ID_BAR, OnUpdateBar)
	ON_UPDATE_COMMAND_UI(ID_CONLINE, OnUpdateConline)
	ON_UPDATE_COMMAND_UI(ID_FLOW, OnUpdateFlow)
	ON_UPDATE_COMMAND_UI(ID_BUS, OnUpdateBus)
	ON_UPDATE_COMMAND_UI(ID_PIE, OnUpdatePie)
	ON_UPDATE_COMMAND_UI(ID_DATE, OnUpdateDate)
	ON_UPDATE_COMMAND_UI(ID_TIME, OnUpdateTime)
	ON_UPDATE_COMMAND_UI(ID_GIFANL, OnUpdateGifanl)
	ON_UPDATE_COMMAND_UI(ID_SCRTEXT, OnUpdateScrtext)
	ON_UPDATE_COMMAND_UI(ID_PUSH, OnUpdatePush)
	ON_UPDATE_COMMAND_UI(ID_SELFCTL, OnUpdateSelfctl)
	ON_UPDATE_COMMAND_UI(ID_FLASH, OnUpdateFlash)
	ON_UPDATE_COMMAND_UI(ID_COORD, OnUpdateCoord)
	ON_UPDATE_COMMAND_UI(ID_TABLE, OnUpdateTable)
	ON_UPDATE_COMMAND_UI(ID_TEXT, OnUpdateText)
	ON_UPDATE_COMMAND_UI(ID_IMAGE, OnUpdateImage)
	ON_UPDATE_COMMAND_UI(ID_ESITE, OnUpdateEsite)
	ON_UPDATE_COMMAND_UI(ID_EGPMB, OnUpdateEgpmb)
	ON_UPDATE_COMMAND_UI(ID_LINE, OnUpdateLine)
	ON_UPDATE_COMMAND_UI(ID_ARROW, OnUpdateArrow)
	ON_UPDATE_COMMAND_UI(ID_RECT, OnUpdateRect)
	ON_UPDATE_COMMAND_UI(ID_CIRCLE, OnUpdateCircle)
	ON_UPDATE_COMMAND_UI(ID_ARC, OnUpdateArc)
	ON_UPDATE_COMMAND_UI(ID_HSIN, OnUpdateHsin)
	ON_UPDATE_COMMAND_UI(ID_SIN, OnUpdateSin)
	ON_UPDATE_COMMAND_UI(ID_GLASS, OnUpdateGlass)
	ON_UPDATE_COMMAND_UI(ID_PATH, OnUpdatePath)
	ON_COMMAND(ID_RESERVOIR, OnReservoir)
	ON_UPDATE_COMMAND_UI(ID_RESERVOIR, OnUpdateReservoir)
	ON_COMMAND(ID_POLYZONE, OnPolyzone)
	ON_UPDATE_COMMAND_UI(ID_POLYZONE, OnUpdatePolyzone)
	ON_COMMAND(IDC_DRAWRT, OnDrawrt)
	ON_UPDATE_COMMAND_UI(IDC_DRAWRT, OnUpdateDrawrt)
	ON_COMMAND(IDC_MODIFONT, OnModifont)
	ON_UPDATE_COMMAND_UI(IDC_MODIFONT, OnUpdateModifont)
	ON_COMMAND(IDC_DBXTOZONE, OnDbxtozone)
	ON_UPDATE_COMMAND_UI(IDC_DBXTOZONE, OnUpdateDbxtozone)
	ON_COMMAND(IDC_INSVG, OnInsvg)
	ON_COMMAND(IDC_MULTEXT, OnMultext)
	ON_UPDATE_COMMAND_UI(IDC_MULTEXT, OnUpdateMultext)
	ON_COMMAND(ID_SYSPIE, OnSyspie)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(IDC_INSVG_BAT, OnInsvgBat)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// workwin message handlers

BOOL workwin::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), /*HBRUSH(COLOR_WINDOW+1)*/NULL, NULL);
	return TRUE;
}

int workwin::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	/*tb1.CreateEx(this,TBSTYLE_FLAT|TBSTYLE_TOOLTIPS|TBSTYLE_LIST,WS_CHILD|WS_VISIBLE|CBRS_TOP|CBRS_TOOLTIPS);
	tb1.LoadToolBar(IDR_BASGRP);
	tb2.CreateEx(this,TBSTYLE_FLAT|TBSTYLE_TOOLTIPS|TBSTYLE_LIST,WS_CHILD|WS_VISIBLE|CBRS_TOP|CBRS_TOOLTIPS);
	tb2.LoadToolBar(IDR_ACTGRP);*/
	cvs.Create("","",WS_CHILD|WS_VISIBLE,CRect(0,0,1,1),this,100);
	ptl.Create("","",WS_CHILD|WS_VISIBLE,CRect(0,0,1,1),this,101);
	
	cobj.cvs=&cvs;
	cobj.pgcw=&ptl;
	return 0;
}

void workwin::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	wx=cx;
	wy=cy;
	Relayer(); //重新排列
}

void workwin::OnPaint() 
{
	CPaintDC dc(this); 
	dc.Draw3dRect(CRect(0,0,wx,wy),0,0xffffff);
}

void workwin::Relayer()
{
	ptl.MoveWindow(0,0,wx,24);
	cvs.MoveWindow(0,24,wx,wy);
	/*int w,h,w1;
	h=0;
	w=0;
	w1=win[0].width+win[1].width;
	if(win[0].show==1)
	{
		if(win[1].show==1&&w1<=wx) win[0].wnd->MoveWindow(CRect(w,h,w+win[0].width,h+win[0].height));
		else win[0].wnd->MoveWindow(CRect(w,h,wx,h+win[0].height));
		w+=win[0].width;
	} else  win[0].wnd->MoveWindow(CRect(0,0,0,0));

	if(win[1].show==1)
	{
		if(w1<=wx) win[1].wnd->MoveWindow(CRect(w,h,wx,h+win[1].height));
		else {
			h+=win[0].height;
			win[1].wnd->MoveWindow(CRect(0,h,wx,h+win[1].height));
		}
	}else win[1].wnd->MoveWindow(CRect(0,0,0,0));

	if(win[0].show==1||win[1].show==1) h+=win[0].height;
	
	if(win[2].show==1)
	{
		win[2].wnd->MoveWindow(CRect(0,h,wx,h+win[2].height));
		h+=win[2].height;
	}
	win[3].wnd->MoveWindow(CRect(0,h,wx,wy));*/

}

BOOL workwin::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	if (ptl.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;
	if (cvs.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;
	return CWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void workwin::SetTitlename()
{
	char p[512];
	sprintf(p,"电力可视化绘图包VisualPaint 2.1[%s]-[%s]",dbm.pwfname,
		dbm.page[dbm.curpage].head.Name);
	AfxGetMainWnd()->SetWindowText(p);
	cobj.cursor=0;
}

//打开文件
void workwin::OnFileOpen() 
{
	char filter[512],fnm[512],path[256],title[64];
	bool rtn;
	if(dbm.editbz==1){
	   if(MessageBox("编辑数据发生变化, 是否需要保存?\n按[否]将丢失数据.",
		    "提示",MB_YESNO)==IDYES){
		    OnFileSave();				
		}
	}
	strcpy(title,"打开可视化界面文件");
	strcpy(filter,"VisualPaint界面文件(*.pw0)|*.pw0|");
	CFileDialog  fodlg(true,NULL,NULL,
		OFN_FILEMUSTEXIST|OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filter,this);
	rtn=false; 
	strcpy(path,cobj.path[1].path);
	fodlg.m_ofn.lpstrInitialDir=path;
	fodlg.m_ofn.lpstrTitle=title;
	if(fodlg.DoModal()==IDOK){
	  dbm.curpage=0;
	  strcpy(fnm,fodlg.GetPathName());
	  rtn=dbm.OpenPwFile(fnm);
	  if(!rtn){
	   MessageBox("版本不同！\n请用格式转换工具转换。\n打开文件失败");
	   return;
	  };
	};
	if(!rtn) return;
	dbm.dx=0;
	dbm.dy=0;
	dbm.GoToPage(0);
	dbm.ParamChange();
	SetTitlename();
	cobj.spiw->ReOpen();
	cvs.DrawShow();
	ptl.dx=0;
	ptl.DrawShow();
	cvs.ShowObjsum();
	cobj.egpw->ReOpenGrp();
	cobj.nwin->ZoomChange();
	cvs.PageChange();
}

void workwin::OnFileSave() 
{
	char filter[256],path[256],title[64];
	char fnm[256],fname[256];
	char *lp;
	if(dbm.filebz==1){
		dbm.SaveFile(dbm.pwfname);
		return;
	};
	strcpy(path,cobj.path[1].path);
	strcpy(title,"保存可视化文件");
	strcpy(filter,"VisualPaint界面文件(*.pw0)|*.pw0");
	CFileDialog  fodlg(false,NULL,NULL,
		OFN_CREATEPROMPT|OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filter,this);
	fodlg.m_ofn.lpstrTitle=title;
	fodlg.m_ofn.lpstrInitialDir=path;

	strcpy(fname,dbm.cpage->head.Name);
	fodlg.m_ofn.lpstrFile=fname;
	if(fodlg.DoModal()==IDOK){
	  strcpy(fnm,fodlg.GetPathName());
	  lp=strrchr(fnm,'.');
	  if(lp!=NULL) *lp=0;
	  strcat(fnm,".pw0");
	  dbm.SaveFile(fnm);
	  SetTitlename();
	 };
}



void workwin::OnFileNew() 
{
	if(dbm.drawbz==1){
	if(MessageBox("编辑数据发生变化, 是否需要保存?\n按[否]将丢失数据.",
		"提示",MB_YESNO)==IDYES){
		OnFileSave();				
		}
	}
	dbm.FreeMem();
	cobj.FreeMem();
	cobj.InitParam();
	dbm.InitParam();
	dbm.GoToPage(0);
	OnSize(SIZE_RESTORED,wx,wy);
	cvs.PageChange();
	cvs.ShowObjsum();
	SetTitlename();
}



void workwin::OnNormal() 
{
	cvs.DrawChange(0);
}

void workwin::OnMovepic() 
{
	cobj.cursor=102;
}

void workwin::OnPartzoom() 
{
	cobj.cursor=103;
}

void workwin::OnZoomio() 
{
	cobj.cursor=104;
}


LRESULT workwin::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	CMainWin *mwin;
	if(message==1007){
		switch(wParam){
		case 100:
			mwin=(CMainWin*)GetParent();
			mwin->PageChange((int)lParam);
			cobj.layw->DrawLayerPic();
			cobj.layw->Invalidate();
			return true;
		case 101:
			mwin=(CMainWin*)GetParent();
			cvs.LayerChange();
			return true;
		}
	}
	return CWnd::WindowProc(message, wParam, lParam);
}

void workwin::OnLineAdddot() 
{
	if(cobj.cursor==106) cobj.cursor=0;	
	else cobj.cursor=106;	
}

void workwin::OnLineSubdot() 
{
	if(cobj.cursor==107) cobj.cursor=0;
	else cobj.cursor=107;
}

void workwin::OnCutline() 
{
	if(cobj.cursor==108) cobj.cursor=0;
	else cobj.cursor=108;
}

void workwin::OnBindline() 
{
	dbm.BindLine();
	cvs.DrawShow();
}

void workwin::OnClearimg() 
{
	cvs.DrawChange(201);
}

void workwin::OnCutimg() 
{
	cvs.DrawChange(202);
}

void workwin::OnTranimg() 
{
	cvs.DrawChange(203);
}

void workwin::OnPaintimg() 
{
	cvs.DrawChange(205);
}

void workwin::OnBrightimg() 
{
	cvs.DrawChange(206);
}

void workwin::OnSetregon() 
{
	cvs.DrawChange(63);
}

void workwin::OnCutregon() 
{
	dbm.CutImgRgn();
	cvs.DrawShow();
}
//////////////////////////////////////////////////////////////////////////////////////////////
void workwin::OnLine()		{cvs.DrawChange(1);}
void workwin::OnRect()		{cvs.DrawChange(4);}
void workwin::OnCircle()	{cvs.DrawChange(5);}
void workwin::OnHsin()		{cvs.DrawChange(6);}
void workwin::OnSin()		{cvs.DrawChange(7);}
void workwin::OnArc()		{cvs.DrawChange(8);}
void workwin::OnArrow()		{cvs.DrawChange(9);}
void workwin::OnGlass()		{cvs.DrawChange(10);}
void workwin::OnCbar()		{cvs.DrawChange(11);}
void workwin::OnText()		{cvs.DrawChange(12);}
void workwin::OnEsite()		{cvs.DrawChange(13);}
void workwin::OnEgpmb()		{cvs.DrawChange(14);}
void workwin::OnCoord()		{cvs.DrawChange(15);}
void workwin::OnTable()		{cvs.DrawChange(16);}
void workwin::OnImage()		{cvs.DrawChange(17);}
void workwin::OnPath()		{cvs.DrawChange(18);}

void workwin::OnAnalog()	{cvs.DrawChange(64);}
void workwin::OnReservoir() {cvs.DrawChange(65);}
void workwin::OnSyspie()	{cvs.DrawChange(67);}
void workwin::OnBar()		{cvs.DrawChange(68);}
void workwin::OnPie()		{cvs.DrawChange(69);}

void workwin::OnDate()		{cvs.DrawChange(70);}
void workwin::OnTime()		{cvs.DrawChange(71);}
void workwin::OnGifanl()	{cvs.DrawChange(72);}
void workwin::OnScrtext()	{cvs.DrawChange(73);}
void workwin::OnPush()		{cvs.DrawChange(74);}
void workwin::OnSelfctl()	{cvs.DrawChange(75);}
void workwin::OnConline()	{cvs.DrawChange(76);}
void workwin::OnFlow()		{cvs.DrawChange(77);}
void workwin::OnBus()		{cvs.DrawChange(78);}
void workwin::OnActobj()	{cvs.DrawChange(79);}
void workwin::OnFlash()		{cvs.DrawChange(80);}
void workwin::OnPctpie()	{cvs.DrawChange(81);}
void workwin::OnMeter1()	{cvs.DrawChange(32);}
void workwin::OnMeter2()    {cvs.DrawChange(33);}
void workwin::OnMeter3()	{cvs.DrawChange(34);}
void workwin::OnMeter4()	{cvs.DrawChange(35);}
void workwin::OnPolyzone()  {cvs.DrawChange(82);}
void workwin::OnMultext()   {cvs.DrawChange(83);}	

void workwin::OnEditCut() 
{
	//dbm.CopyToCpyBuf();
	cobj.unp.AddAUndoOp(2);
	dbm.DelSelObj();
	cvs.ShowObjsum();
	cvs.DrawShow();
}

void workwin::OnGototop() 
{
	dbm.SelObjToTOP();
	cvs.drawbg=1;
	cvs.DrawShow();
}

void workwin::OnGotobuttom() 
{
	dbm.SelObjToButtom();
	cvs.drawbg=1;
	cvs.DrawShow();
}

void workwin::OnEditUndo() 
{
	cobj.unp.UnDOAStep();
	cvs.DrawShow();
	cvs.ShowObjsum();
	cobj.cursor=0;
}



void workwin::OnStraight() 
{
	dbm.StraightObj();
	cvs.DrawShow();
}

void workwin::OnImgstratch() 
{
	CMemDC dc1;
	N_IMG *img;
	int j,k,w,h,id;
	j=dbm.GetFirstSelObj();
	if(j<0) return;
	if(dbm.clayer->obj[j].attr.type!=15) return;
	img=(N_IMG*)dbm.clayer->obj[j].buf;
	id=img->imgID;
	k=cobj.GetMPICRecno(id);
	if(k<0) return;
	w=(int)dbm.clayer->obj[j].ort.Width();
	h=(int)dbm.clayer->obj[j].ort.Height();
	dc1.Create(w,h);
	img24_stratch((BYTE*)cobj.mpic[k].dc.dib,(BYTE*)dc1.dib,
						cobj.mpic[k].dc.nWidth,cobj.mpic[k].dc.nHeight,w,h);
	cobj.mpic[k].dc.SizeChange(w,h);
	dc1.BitBlt(cobj.mpic[k].dc.m_hDC,CRect(0,0,w,h),SRCCOPY);
	cvs.Invalidate();
}

//按不同的要求处理图像
void workwin::ProcImg(int method, BYTE param)
{
	BYTE *buf;
	int w,h;
	SetCursor(LoadCursor(NULL, IDC_WAIT));
	if(!dbm.GetProcImgBuf(&buf,w,h)) return;
	switch(method){
	 case ID_FILTER_REV:	img24_reverse(buf,w,h);break;
	 case ID_FILTER_GRAY:	img24_gray(buf,w,h);   break;
	 case ID_FILTER_SMOTH:	img24_smooth(buf,w,h); break;
	 case ID_TRAN_MIR:		img24_glass(buf,w,h);  break;
	 case ID_TRAN_UD:		img24_updown(buf,w,h); break;
	 case ID_BD_BRIGHT:		img24_bd_bright(buf,w,h); break;
	 case ID_BD_BLACK:	    img24_bd_black(buf,w,h);break;
	 case ID_BD_BLK:	    img24_bd_hard(buf,w,h);break;
	 case ID_FILTER_WL:		img24_bd_wl(buf,w,h);  break;
	 case ID_FILTER_REDUCE: img24_rcolor(buf,w,h,param);break;
	};
	Invalidate();
	SetCursor(LoadCursor(NULL, IDC_ARROW));
}

void workwin::OnFilterGray() 
{
	ProcImg(ID_FILTER_GRAY);
	
}



void workwin::OnFilterRev() 
{
	ProcImg(ID_FILTER_REV);
}

void workwin::OnFilterSmoth() 
{
	ProcImg(ID_FILTER_SMOTH);
}

void workwin::OnFilterWl() 
{
	ProcImg(ID_FILTER_WL);
}

void workwin::OnTranMir() 
{
	ProcImg(ID_TRAN_MIR);
}

void workwin::OnTranUd() 
{
	ProcImg(ID_TRAN_UD);
}

void workwin::OnBdBlack() 
{
	ProcImg(ID_BD_BLACK);
}

void workwin::OnBdBlk() 
{
	ProcImg(ID_BD_BLK);
}

void workwin::OnBdBright() 
{
	ProcImg(ID_BD_BRIGHT);
}

void workwin::OnCopytoclib() 
{
	BITMAPINFOHEADER bi;
	CDIB mdc;
	HGLOBAL hg;
	int w,h,size;
	double oldz;
	char *buf,*lp;
	if(!OpenClipboard())
	{
		MessageBox("剪贴板被独占!");
		return;
	};
	EmptyClipboard();
	w=dbm.page[dbm.curpage].head.width;
	h=dbm.page[dbm.curpage].head.height;
	//保存放大倍数
	oldz=cobj.curzoom;
	cobj.curzoom=1;
	mdc.Create(w,h);
	dbm.ShowBkgd(mdc,CRect(0,0,w,h));
	dbm.Showobject(mdc,0,0,CRect(0,0,w,h),0);
	bi.biSize=sizeof(BITMAPINFOHEADER);
    bi.biWidth=w;
    bi.biHeight=h; 
    bi.biPlanes=1;
    bi.biBitCount=24;
	bi.biCompression=BI_RGB; 
    bi.biXPelsPerMeter=0; 
    bi.biYPelsPerMeter=0; 
    bi.biClrUsed=0; 
    bi.biClrImportant=0; 
	bi.biSizeImage=h*mdc.sPerline; 
    size=sizeof(BITMAPINFOHEADER)+mdc.dibsize+100;
	hg=GlobalAlloc(GMEM_MOVEABLE,size);
	if(hg==NULL) return;
	buf=(char*)GlobalLock(hg);
	memcpy(buf,&bi,sizeof(BITMAPINFOHEADER));
	lp=buf+sizeof(BITMAPINFOHEADER);
	memcpy(lp,mdc.dib,mdc.dibsize);
	GlobalUnlock(hg);
  	SetClipboardData(CF_DIB,hg);
	CloseClipboard();
	GlobalFree(hg);
	//恢复放大倍数
	cobj.curzoom=oldz;
}

void workwin::OnPasteclib() 
{
	HBITMAP hbmp;
	if(!OpenClipboard()) return;
	hbmp=(HBITMAP)GetClipboardData(CF_BITMAP);
	if(hbmp==NULL)
	{
		CloseClipboard();
		MessageBox("位图粘贴出错！");
		return;
    }
	dbm.AddPasteImg(hbmp);
	CloseClipboard();
	DeleteObject(hbmp);
	cvs.Invalidate();
	cvs.ShowObjsum();
}

void workwin::OnCutnouse() 
{
	dbm.CutMpicNoUse();
	cvs.DrawShow();
}

void workwin::OnSetpage() 
{
	int w,h,j;
	j=dbm.curpage;
	w=dbm.page[j].head.width;
	h=dbm.page[j].head.height;
	PatrDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		if(w!=dbm.page[j].head.width||h!=dbm.page[j].head.height) dbm.ParamChange();
		SetTitlename();
		OnSize(SIZE_RESTORED,wx,wy);
		cvs.DrawShow();
		ptl.Invalidate();
		dbm.editbz=1;
		//GetParent()->SendMessage(1200);
	}
}

void workwin::OnDrawattr() 
{
	cobj.edobj=1;
	cobj.cursor=0;
	if(!cobj.tlsw->IsEditActive()) cobj.tlsw->EnableEditTool();
	cobj.objw->EditSysParam();
}

void workwin::OnVlcolor() 
{
	CCfgCRDlg dlg;
	dlg.DoModal();
}

//重新显示在BTM上,并显示在画布上
void workwin::RefreshCanvas()
{
	cvs.drawbg=1;
	cvs.DrawShow();
	cobj.nwin->Objchange();
	GetParent()->SendMessage(1200);
}

void workwin::OnFillptn() 
{
	dbm.SetImgToBg(cobj.patternID);	
	RefreshCanvas();
}

void workwin::OnFillcolor() 
{
	DWORD color;
	color=dbm.page[dbm.curpage].head.BgColor;
	CColorDialog cdlg(color,0,this);
	if(cdlg.DoModal()==IDOK){
	  color=cdlg.GetColor();
	  dbm.SetColorToBg(color);
	  RefreshCanvas();
	}
}

void workwin::OnShowguide() 
{
	cobj.gshow=cobj.gshow==0 ? 1:0;
	cvs.DrawShow();
	cobj.nwin->Objchange();
}

void workwin::OnGuide() 
{
	guiddlg dlg;
	if(dlg.DoModal()==IDOK){
		cvs.DrawShow();
		cobj.nwin->Objchange();
	};
}

void workwin::OnEgptosgl() 
{
	dbm.SingleEGrp();
	cvs.DrawShow();
}

void workwin::OnResetsite() 
{
	dbm.ReComputeSitePos();
	cvs.DrawShow();
}

void workwin::OnShowsite() 
{
	cobj.showsite=cobj.showsite==0 ? 1:0;
	cvs.DrawShow();
}

void workwin::OnNocondev() 
{
	cobj.nocondev=cobj.nocondev==0 ? 1:0;
	cvs.DrawShow();
}

void workwin::OnNocdev() 
{
	cobj.nocdev=cobj.nocdev==0 ? 1:0;
	cvs.DrawShow();
}

void workwin::OnFileSaveAs() 
{
	char filter[256],path[256],title[64];
	char fnm[256];
	char *lp;
	strcpy(path,cobj.path[1].path);
	strcpy(title,"另存可视化文件");
	strcpy(filter,"VisualPaint界面文件(*.pw0)|*.pw0");
	CFileDialog  fodlg(false,NULL,NULL,
		OFN_CREATEPROMPT|OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filter,this);
	fodlg.m_ofn.lpstrInitialDir=path;
	fodlg.m_ofn.lpstrTitle=title;
	if(fodlg.DoModal()==IDOK){
	  strcpy(fnm,fodlg.GetPathName());
	  lp=strchr(fnm,'.');
	  if(lp!=NULL) *lp=0;
	  strcat(fnm,".pw0");
	  dbm.SaveFile(fnm);
	  SetTitlename();
	 };
}


void workwin::OnAddpage() 
{
	if(dbm.AddNewPage())
	{
		dbm.editbz=0;
		dbm.drawbz=1;
		ptl.dx=dbm.curpage>5 ? ptl.dx=dbm.curpage-3:0;
		cvs.DrawShow();
		cobj.nwin->PageChange();
		cobj.nwin->Invalidate();
		cobj.layw->Invalidate();
		ptl.Invalidate();
		if(cobj.tlsw->IsEditActive()) cobj.objw->EmptyEdit();
	};
}

void workwin::OnAddlayer() 
{
	if(dbm.AddNewLayer()){
		dbm.editbz=0;
		dbm.drawbz=1;
		cvs.DrawShow();
		ptl.Invalidate();
		if(cobj.tlsw->IsEditActive()) cobj.objw->EmptyEdit();
		cobj.layw->Invalidate();
	}
}

void workwin::OnDelcurpage() 
{
	if(dbm.DelCurPage()){
		dbm.editbz=0;
		dbm.drawbz=1;
		cobj.nwin->Invalidate();
		cvs.DrawShow();
		ptl.Invalidate();
		if(cobj.tlsw->IsEditActive()) cobj.objw->EmptyEdit();
	};
}

void workwin::OnDelcurlayer() 
{
	if(dbm.DelCurLayer()){
		dbm.editbz=0;
		dbm.drawbz=1;
		cvs.DrawShow();
		cobj.nwin->Invalidate();
		ptl.Invalidate();
		if(cobj.tlsw->IsEditActive()) cobj.objw->EmptyEdit();
		cobj.layw->Invalidate();
	}
}


//接收到文件，察看是否需要重新打开
void workwin::RecFileOkOpen(char *filename)
{
	int oldpage;
	bool rtn;
	if(strcmp(filename,dbm.pwfname)!=0) return; //当前编辑的不是和更新的文件一样
	oldpage=dbm.curpage;
	rtn=dbm.OpenPwFile(filename);
	if(!rtn)  return;
	oldpage=oldpage>=dbm.pagesum ? 0:oldpage;
	dbm.GoToPage(oldpage);
	dbm.ParamChange();
	SetTitlename();
	cobj.spiw->ReOpen();
	ptl.dx=0;
	ptl.DrawShow();
	cvs.ShowObjsum();
	cobj.egpw->ReOpenGrp();
	cobj.nwin->ZoomChange();
	cvs.PageChange();
}

//将一个图形的宽高置为相等
void workwin::OnTosqrt() 
{
	dbm.SqrtObj();
	cvs.DrawShow();
}







void workwin::OnUpdateMeter1(CCmdUI* pCmdUI)	{pCmdUI->SetCheck(cobj.cursor==32 ? 1:0);}
void workwin::OnUpdateMeter2(CCmdUI* pCmdUI)	{pCmdUI->SetCheck(cobj.cursor==33 ? 1:0);}
void workwin::OnUpdateMeter3(CCmdUI* pCmdUI)	{pCmdUI->SetCheck(cobj.cursor==34 ? 1:0);}
void workwin::OnUpdateMeter4(CCmdUI* pCmdUI)	{pCmdUI->SetCheck(cobj.cursor==35 ? 1:0);}
void workwin::OnUpdateAnalog(CCmdUI* pCmdUI)	{pCmdUI->SetCheck(cobj.cursor==64 ? 1:0);}
void workwin::OnUpdateActobj(CCmdUI* pCmdUI)	{pCmdUI->SetCheck(cobj.cursor==79 ? 1:0);}
void workwin::OnUpdatePctpie(CCmdUI* pCmdUI)	{pCmdUI->SetCheck(cobj.cursor==81 ? 1:0);}
void workwin::OnUpdateBar(CCmdUI* pCmdUI)		{pCmdUI->SetCheck(cobj.cursor==68 ? 1:0);}
void workwin::OnUpdateConline(CCmdUI* pCmdUI)	{pCmdUI->SetCheck(cobj.cursor==76 ? 1:0);}
void workwin::OnUpdateFlow(CCmdUI* pCmdUI)		{pCmdUI->SetCheck(cobj.cursor==77 ? 1:0);}
void workwin::OnUpdateBus(CCmdUI* pCmdUI)		{pCmdUI->SetCheck(cobj.cursor==78 ? 1:0);}
void workwin::OnUpdatePie(CCmdUI* pCmdUI)		{pCmdUI->SetCheck(cobj.cursor==69 ? 1:0);}
void workwin::OnUpdateDate(CCmdUI* pCmdUI)		{pCmdUI->SetCheck(cobj.cursor==70 ? 1:0);}
void workwin::OnUpdateTime(CCmdUI* pCmdUI)		{pCmdUI->SetCheck(cobj.cursor==71 ? 1:0);}
void workwin::OnUpdateGifanl(CCmdUI* pCmdUI)	{pCmdUI->SetCheck(cobj.cursor==72 ? 1:0);}
void workwin::OnUpdateScrtext(CCmdUI* pCmdUI)	{pCmdUI->SetCheck(cobj.cursor==73 ? 1:0);}
void workwin::OnUpdatePush(CCmdUI* pCmdUI)		{pCmdUI->SetCheck(cobj.cursor==74 ? 1:0);}
void workwin::OnUpdateSelfctl(CCmdUI* pCmdUI)	{pCmdUI->SetCheck(cobj.cursor==75 ? 1:0);}
void workwin::OnUpdateFlash(CCmdUI* pCmdUI)		{pCmdUI->SetCheck(cobj.cursor==80 ? 1:0);}
void workwin::OnUpdateCoord(CCmdUI* pCmdUI)		{pCmdUI->SetCheck(cobj.cursor==15 ? 1:0);}
void workwin::OnUpdateTable(CCmdUI* pCmdUI)		{pCmdUI->SetCheck(cobj.cursor==16 ? 1:0);}
void workwin::OnUpdateText(CCmdUI* pCmdUI)		{pCmdUI->SetCheck(cobj.cursor==12 ? 1:0);}
void workwin::OnUpdateImage(CCmdUI* pCmdUI)		{pCmdUI->SetCheck(cobj.cursor==17 ? 1:0);}
void workwin::OnUpdateEsite(CCmdUI* pCmdUI)		{pCmdUI->SetCheck(cobj.cursor==13 ? 1:0);}
void workwin::OnUpdateEgpmb(CCmdUI* pCmdUI)		{pCmdUI->SetCheck(cobj.cursor==14 ? 1:0);}
void workwin::OnUpdateLine(CCmdUI* pCmdUI)		{pCmdUI->SetCheck(cobj.cursor==1 ? 1:0); }
void workwin::OnUpdateArrow(CCmdUI* pCmdUI)		{pCmdUI->SetCheck(cobj.cursor==9 ? 1:0);}
void workwin::OnUpdateRect(CCmdUI* pCmdUI)		{pCmdUI->SetCheck(cobj.cursor==4 ? 1:0);}
void workwin::OnUpdateCircle(CCmdUI* pCmdUI)	{pCmdUI->SetCheck(cobj.cursor==5 ? 1:0);}
void workwin::OnUpdateArc(CCmdUI* pCmdUI)		{pCmdUI->SetCheck(cobj.cursor==8 ? 1:0);}
void workwin::OnUpdateHsin(CCmdUI* pCmdUI)		{pCmdUI->SetCheck(cobj.cursor==6 ? 1:0);}
void workwin::OnUpdateSin(CCmdUI* pCmdUI)		{pCmdUI->SetCheck(cobj.cursor==7 ? 1:0);}
void workwin::OnUpdateGlass(CCmdUI* pCmdUI)		{pCmdUI->SetCheck(cobj.cursor==10 ? 1:0);}
void workwin::OnUpdatePath(CCmdUI* pCmdUI)		{pCmdUI->SetCheck(cobj.cursor==18 ? 1:0);}
void workwin::OnUpdatePolyzone(CCmdUI* pCmdUI)  {pCmdUI->SetCheck(cobj.cursor==82 ? 1:0);}
void workwin::OnUpdateMultext(CCmdUI* pCmdUI)   {pCmdUI->SetCheck(cobj.cursor==83 ? 1:0);}

void workwin::OnUpdateReservoir(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(cobj.cursor==65 ? 1:0);
}

//启动矩形
void workwin::OnDrawrt() 
{
	cvs.DrawChange(260);
	
}

void workwin::OnUpdateDrawrt(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(cobj.cursor==260 ? 1:0);
	pCmdUI->Enable(dbm.cpage->head.showbyrt==0 ? 0:1);
}

//批量修改字体
void workwin::OnModifont() 
{
	LOGFONT lf;
	CFontDialog cdlg;
	if(cdlg.DoModal()==IDOK){
	  cdlg.GetCurrentFont(&lf);
	  dbm.ModiFont(lf);
	  cvs.DrawShow();
	}
	
}

void workwin::OnUpdateModifont(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(dbm.selbz>0 ? true:false);
}

void workwin::OnDbxtozone() 
{
	int j;
	N_DBX *dbx;
	j=dbm.GetFirstSelObj();
	if(j<0){
		MessageBox("没有选择");
		return;
	}
	if(dbm.clayer->obj[j].attr.type!=1)
	{
		MessageBox("选择的对象不是多边形！","错误",MB_OK|MB_ICONSTOP);
		return;
	}
	dbx=(N_DBX*)dbm.clayer->obj[j].buf;
	cvs.AddDZone(dbx->ptsum,dbx->pt);
}



void workwin::OnUpdateDbxtozone(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(dbm.selbz>0 ? true:false);
}

//输入SVG格式
void workwin::OnInsvg() 
{
	CCheckSvgType  svgt;
	int type;
	char filter[128],fnm[256],title[64];
	if(dbm.editbz==1){
	   if(MessageBox("编辑数据发生变化, 是否需要保存?\n按[否]将丢失数据.",
		    "提示",MB_YESNO)==IDYES){
		    OnFileSave();				
		}
	}
	strcpy(title,"打开SVG图形格式文件");
	strcpy(filter,"SVG格式文件(*.svg)|*.svg|");
	CFileDialog  fodlg(true,NULL,NULL,
		OFN_FILEMUSTEXIST|OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filter,this);
	fodlg.m_ofn.lpstrTitle=title;

	if(fodlg.DoModal()==IDOK){
	    strcpy(fnm,fodlg.GetPathName());
		type=svgt.GetSvgType(fnm);
		switch(type)
		{
		case 0:
			dbm.ImportSvgFile(fnm);
			break;
		default:
			MessageBox("不认识的SVG格式","错误",MB_OK|MB_ICONSTOP);
			return;
		}
		//cvs.PageChange();
		cvs.ShowObjsum();
		cobj.nwin->Objchange();
		SetTitlename();
		dbm.dx=0;
		dbm.dy=0;
		dbm.GoToPage(0);
		dbm.ParamChange();
		SetTitlename();
		cobj.spiw->ReOpen();
		//cvs.DrawShow();
		ptl.dx=0;
		ptl.DrawShow();
		cvs.ShowObjsum();
		cobj.egpw->ReOpenGrp();
		cobj.nwin->ZoomChange();
		cvs.PageChange();
	
	};
}

void workwin::OnInsvgBat() 
{
	CImportDlg impdlg;
	impdlg.DoModal();
}
