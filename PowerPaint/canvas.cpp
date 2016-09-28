// canvas.cpp : implementation file
//

#include "stdafx.h"
#include "PowerPaint.h"
#include "canvas.h"
#include "comobj.h"
#include "gdata.h"
#include "math.h"
#include "middll.h"
#include "seledlg.h"
#include "CfgMeter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern gdata dbm;
extern comobj cobj;
extern char *ftr[];
BOOL GetImgFile(char *filename,char *filter,HWND hWndParent);
BOOL GetDllName(char *name,HWND hWndParent);
bool EditText(char *str,int n,HWND hWndParent);
bool EditScrt(char *str,int n,HWND hWndParent);

/////////////////////////////////////////////////////////////////////////////
// canvas

canvas::canvas()
{
	pmenu.LoadMenu(IDR_RMENU);
	pmenu1.LoadMenu(IDR_RMENU1);
	pmenu2.LoadMenu(IDR_RMENU2);
	pmenu3.LoadMenu(IDR_RMENU3);
	pmenu4.LoadMenu(IDR_RMENU4);
	pmenu5.LoadMenu(IDR_RMENU5);
	pmenu6.LoadMenu(IDR_RMENU6);
	mtp.Create(1,1);
	mat.Create(1,1);
}

canvas::~canvas()
{
	pmenu.DestroyMenu();
	pmenu1.DestroyMenu();
	pmenu2.DestroyMenu();
	pmenu3.DestroyMenu();
	pmenu4.DestroyMenu();
	pmenu5.DestroyMenu();
	pmenu6.DestroyMenu();
	//nwin.closebz=1;
}


BEGIN_MESSAGE_MAP(canvas, CWnd)
	//{{AFX_MSG_MAP(canvas)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_SETCURSOR()
	ON_COMMAND(ID_ZOOMNML, OnZoomnml)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_NORMAL, OnNormal)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_ALIGN_DOWN, OnAlignDown)
	ON_COMMAND(ID_ALIGN_DSTX, OnAlignDstx)
	ON_COMMAND(ID_ALIGN_DSTY, OnAlignDsty)
	ON_COMMAND(ID_ALIGN_HG, OnAlignHg)
	ON_COMMAND(ID_ALIGN_LEFT, OnAlignLeft)
	ON_COMMAND(ID_ALIGN_RIGHT, OnAlignRight)
	ON_COMMAND(ID_ALIGN_UP, OnAlignUp)
	ON_COMMAND(ID_ALIGN_WD, OnAlignWd)
	ON_COMMAND(ID_EDIT_ATTR, OnEditAttr)
	ON_COMMAND(ID_CONNECT_DEV, OnConnectDev)
	ON_COMMAND(ID_EDIT_DEV, OnEditDev)
	ON_COMMAND(ID_EDIT_SFT, OnEditSft)
	ON_COMMAND(ID_ABOUT_SFT, OnAboutSft)
	ON_COMMAND(ID_DBSOURCE, OnDbsource)
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_GOTOTOP, OnGototop)
	ON_COMMAND(ID_GOTOBUTTOM, OnGotobuttom)
	ON_COMMAND(ID_CURNML, OnCurnml)
	ON_COMMAND(IDC_SELELEBUS, OnSelelebus)
	ON_WM_KEYDOWN()
	ON_COMMAND(IDC_ADDLINEDOT, OnAddlinedot)
	ON_COMMAND(IDC_SUBLINEDOT, OnSublinedot)
	ON_COMMAND(IDC_ZMIN, OnZmin)
	ON_COMMAND(IDC_ZMOUT, OnZmout)
	ON_COMMAND(IDC_AVCCFG, OnAvccfg)
	ON_COMMAND(IDC_DBXTOLINE, OnDbxtoline)
	ON_COMMAND(IDC_DBXTOCL, OnDbxtocl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// canvas message handlers

BOOL canvas::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW),NULL, NULL);
	return TRUE;
}

void canvas::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	wx=cx;
	wy=cy;
	mtp.SizeChange(cx+20,cy+20);
	mat.SizeChange(cx+20,cy+20);
	SizeChange(cx,cy);
	cobj.nwin->WinSizeChange(cx,cy);
}

void canvas::OnPaint() 
{
	CRect *rt,rt1;
	RGNDATA *lp;
	char buff[65024];
	int i,n,m;
	CRgn rgn;
	rgn.CreateRectRgn(0,0,10,10);
	int r=GetUpdateRgn( &rgn);
	CPaintDC dc(this);
	if(r!=NULLREGION||r!=ERROR){
		n=rgn.GetRegionData((LPRGNDATA)buff,1024);
		if(n!=ERROR||n!=NULLREGION){
			lp=(RGNDATA*)buff;
			m=lp->rdh.nCount;
			rt=(CRect*)lp->Buffer;
			for(i=0;i<m;i++){
				rt1=rt[i];
				Show(dc,rt1);
			}
		}
	 }
}


void canvas::Show(HDC hdc,CRect rt)
{
	int w,h;
	CRect rt1=rt;
	rt1.OffsetRect(-dbm.dx,-dbm.dy);
	w=rt.Width();
	h=rt.Height();
	CRect rt2=CRect(0,0,w,h);
	dbm.ShowBkgd(mtp,rt1);
	if(cobj.gshow==1) dbm.ShowWaterLine(mtp.m_hDC,dbm.dx,dbm.dy,rt);
	dbm.Showobject(mtp,-rt.left+dbm.dx,-rt.top+dbm.dy,rt1,0);
	if(dbm.selbz>0&&dbm.movebz==0) dbm.ShowSelectDot(mtp,-rt.left+dbm.dx,-rt.top+dbm.dy);
	if(dbm.selrgn==1) dbm.ShowRgn(mtp.m_hDC,0,dbm.dx-rt.left,dbm.dy-rt.top);
	DrawingLine(mtp.m_hDC,dbm.dx-rt.left,dbm.dy-rt.top);
	mtp.BitBltRect(hdc,rt2,rt);
}

//窗口大小发生变化
void canvas::SizeChange(int cx, int cy)
{
	ComputMaxXY();
	dbm.dx=xmax/2;
	dbm.dy=ymax/2;
	dbm.dx=dbm.dx<0 ? 0:dbm.dx;
	dbm.dy=dbm.dy<0 ? 0:dbm.dy;
	ComputZCenter();
}

//计算x,y方向可以移动的数
void canvas::ComputMaxXY()
{
	xmax=(int)(wx-dbm.cpage->zw-100);
	ymax=(int)(wy-dbm.cpage->zh-100);
}

//计算镜头中心点
void canvas::ComputZCenter()
{
	if(xmax<=0){
	  vx=(double)((-dbm.dx+wx/2)/cobj.curzoom);
	}else{
	  vx=(double)(dbm.cpage->head.width/(double)2);
	}
	if(ymax<=0){
	  vy=(double)((-dbm.dy+wy/2)/cobj.curzoom);
	}else{
	  vy=(double)(dbm.cpage->head.height/(double)2);	
	}
}

void canvas::DrawShow()
{
	CClientDC dc(this);
	Show(dc,CRect(0,0,wx+1,wy+1));
}

//页面改变
void canvas::PageChange()
{
	ComputMaxXY();
	dbm.dx=0;
	dbm.dy=0;
	dbm.nextstart=0;
	OnSize(SIZE_RESTORED, wx,wy);
	drawbg=1;
	ShowObjsum();
	DrawShow();
	cobj.nwin->PageChange();
}

//状态条中显示对象个数
void canvas::ShowObjsum()
{
	char p[40];
	//显示鼠标位置
	sprintf(p,"总:%d个对象 %d层 ",dbm.GetObjSum(),dbm.cpage->laysum);
	CStatusBar *pStatus=(CStatusBar *)AfxGetMainWnd()->GetDescendantWindow(AFX_IDW_STATUS_BAR); 
	pStatus->SetPaneText(4,p);
	cobj.nwin->Objchange();//重新显示导航图
}


void canvas::DrawChange(int funct)
{
	if(funct==cobj.cursor){
	  cobj.cursor=0;
	  return;
	};
	if(cobj.cursor!=63) dbm.selbz=0;
	cobj.cursor=funct;
	dbm.selop=0;
	tptsum=0;
	dbm.selrgn=0;
	dbm.firstsel=-1;
	DrawShow();
}

BOOL canvas::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if(nHitTest == HTCLIENT)
	 {
		if(cobj.cursor>0&&cobj.cursor<64)
		{
		   SetCursor(cobj.hcur[0]);
		   return TRUE;
		};
		switch(cobj.cursor)
		{
		case 100:  SetCursor(cobj.hcur[2]);  return TRUE;
		case 101:  SetCursor(cobj.hcur[1]);  return TRUE;
		case 102:  SetCursor(cobj.hcur[10]); return TRUE;
		case 103:  SetCursor(cobj.hcur[11]); return TRUE;
		case 104:  SetCursor(cobj.hcur[12]); return TRUE;
		case 106:  SetCursor(cobj.hcur[14]); return TRUE; //加点
		case 107:  SetCursor(cobj.hcur[15]); return TRUE; //减点
		case 108:  SetCursor(cobj.hcur[16]); return TRUE; //剪断线

		case 200:  SetCursor(cobj.hcur[3]);  return TRUE;
		case 201:  SetCursor(cobj.hcur[4]);  return TRUE;
		case 202:  SetCursor(cobj.hcur[5]);  return TRUE;
		case 203:  SetCursor(cobj.hcur[6]);  return TRUE;
		case 205:  SetCursor(cobj.hcur[8]);  return TRUE;
		case 206:  SetCursor(cobj.hcur[9]);  return TRUE;
		case 260:  SetCursor(cobj.hcur[0]);	 return TRUE;
		};
	   }
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

void canvas::OnZoomnml() 
{
	double oldz;
	if(cobj.test==1) return;
	oldz=cobj.curzoom;
	dbm.ZoomPage(0);
	if(oldz!=cobj.curzoom) ZoomChange();
	ComputZCenter();
}
//镜头发生变化
void canvas::ZoomChange()
{
	double x,y,width,height;
	width=dbm.cpage->zw;
	height=dbm.cpage->zh;
	ComputMaxXY();
	x=(double)(vx*cobj.curzoom);
	y=(double)(vy*cobj.curzoom);
	dbm.dx=(int)(wx/2-x);
	dbm.dy=(int)(wy/2-y);
	if(xmax>=0) dbm.dx=(int)((wx-width)/2);
	if(ymax>=0) dbm.dy=(int)((wy-height)/2);
	if(xmax<0&&dbm.dx>0) dbm.dx=0;
	if(ymax<0&&dbm.dy>0) dbm.dy=0;
	if(cobj.curzoom==1){
		dbm.dx=(int)((wx-width)/2);
		dbm.dy=(int)((wy-height)/2);
	}
	drawbg=1;
	DrawShow();
	SetZoominfo();
	cobj.nwin->ZoomChange(); 
	//编辑的对象选择区同时放缩
	if(dbm.selbz>0) dbm.CreateMoveRgn();
}

//显示状态放缩信息
void canvas::SetZoominfo()
{
	char p[40];
	//显示鼠标位置
	sprintf(p,"放缩比例:%2.3f％",cobj.curzoom*100);
	CStatusBar *pStatus=(CStatusBar *)AfxGetMainWnd()->GetDescendantWindow(AFX_IDW_STATUS_BAR); 
	pStatus->SetPaneText(2,p);
}

void canvas::OnLButtonDown(UINT nFlags, CPoint point) 
{
	MouseLBDown(point);
	SetFocus();
 	CWnd::OnLButtonDown(nFlags, point);
}

//鼠标左键按下
void canvas::MouseLBDown(CPoint point)
{
	dbm.dnbz=1;
	rpt1=point;
	rpt1.Offset(-dbm.dx,-dbm.dy);
	rpt2=rpt1;

	pt1=point;
	pt2=point;
	oldpt=point;
	oldrt=CRect(0,0,0,0);
	SetCapture();
	switch(cobj.cursor){
	case 0:  case 4:  case 5:  case 6:  case 7:  case 8:
	case 10: case 11: case 12: case 13: case 14: case 15:
	case 16: case 17: case 33: case 34: case 35: case 64: 
	case 67: case 68: case 69: case 70: case 71: case 72: 
	case 73: case 74: case 75: case 78: case 79: case 80:
	case 81: case 103: case 260: case 83:
		DrawXorRect(CRect(rpt1,rpt2)); 
		break;
	case 1:  case 18: case 63: case 76: 
	case  77: case 65: case 82:
		AddPoint(point);
		break;
	case 9: case 32:
		if(tptsum==0) AddPoint(point);
		break;
	case 201:dbm.oldpt1=point;
			 ClearImg(point);	break;
	case 202:CutImage(point);	break;
	case 203:TranImage(point);	break;
	case 205:BrushImage(point);	break;
	case 206:BrightImg(point);  break;
	}
}


void canvas::OnLButtonUp(UINT nFlags, CPoint point) 
{
	ReleaseCapture();
	MouseLBUp(point);
	dbm.dnbz=0;
	cobj.tlsw->ReFreshWin();
	CWnd::OnLButtonUp(nFlags, point);
}


//鼠标左键放开
void canvas::MouseLBUp(CPoint point)
{
	short k;
	int update,oldbz;
	CRect rt;
	CPoint tpoint;
	if(dbm.dnbz==0) return;
	pt2=point;
	rt=CRect(pt1,pt2);
	rt.NormalizeRect();
	tpoint=point;
	tpoint.Offset(-dbm.dx,-dbm.dy);
	rt.OffsetRect(-dbm.dx,-dbm.dy);
	k=GetKeyState(VK_LSHIFT);
	k=(k>>8)&1;
	update=0;
	oldbz=dbm.selbz;
	switch(cobj.cursor)
	{
	case 0:	//选择一个对象或一个区域中的对象
		if(k==0) dbm.ClearSelect();
		if(rt.Width()<5&&rt.Height()<5)
		{
			dbm.SelAObject(tpoint,k);//选择单个对象	
			if(dbm.selbz==1&&cobj.tlsw->IsEditActive()) OnEditAttr();
		}
		else {
			
			dbm.SelManyObject(rt);		//选择多个对象
		}
		if(dbm.selbz>0)
		{
			drawbg=1;
			dbm.CreateMoveRgn();
			dbm.mselrt=dbm.selrt;
		}
		update=1;
		break;
	case 100: 
		if(rt.Width()<2&&rt.Height()<2){
		  if(k==0) dbm.ClearSelect();
		  dbm.SelAObject(tpoint,k);
		  if(dbm.selbz==1&&cobj.tlsw->IsEditActive()) OnEditAttr();
	  	  dbm.CreateMoveRgn();
		  drawbg=1;
		  update=1;
		}else{ //移动结束
		  	//移动相关线条
			dbm.MoveConLine((rpt2.x-rpt1.x)/cobj.curzoom,(rpt2.y-rpt1.y)/cobj.curzoom);
			dbm.mselrt=dbm.selrt;
		}
	case 101:
		cobj.unp.AddAUndoOp(1);
		dbm.ClearSelect2();
		dbm.EndMoveObject();
		cobj.nwin->Objchange();
		update=1;
		drawbg=1;
		break;
	case 106:
		if(dbm.AddLineDot(point)){
		 update=1;
		 cobj.cursor=0;
		}
		break;
	case 107:
		if(dbm.SubLineDot(point)) update=1;
		break;
	case 108:
		if(dbm.CutLine(point)){
			cobj.cursor=0;
			update=1;
		}
		break;
	case 103:
		PartZoom(rt);
		drawbg=1;
		update=1;
		break;
	case 4:  AddRect();			break;
	case 5:  AddCircle();		break;
	case 6:  AddHSin();			break;
	case 7:  AddSin();			break;
	case 8:  AddArc();			break;
	case 10: AddGlass();		break;
	case 12: AddText();			break;
	case 13: AddEsite();		break;
	case 14: AddEgpmb();		break;
	case 15: AddCoordinate();	break;
	case 16: AddTable();		break;
	case 17: AddImage();		break;
	case 33: AddMeter2();		break;
	case 34: AddMeter3();		break;
	case 35: AddMeter4();		break;
	case 64: AddAnalog();		break;
	case 67: AddSysPie();		break;
	case 68: AddBar();			break;
	case 69: AddPie();			break;
	case 70: AddDate();			break;
	case 71: AddTime();			break;
	case 72: AddGifAnl();		break;
	case 73: AddScrText();	    break;
	case 74: AddPush();			break;
	case 75: AddSelfCtl();		break;
	case 78: AddBus();			break;
	case 79: AddActObj();		break;
	case 80: AddFlash();		break;
	case 81: AddPctPie();		break;
	case 260: ChangeShowRT();	break;
	case 83: AddMtText();		break;
	}
	k=cobj.cursor;
	if(update==1)  DrawShow();
	if(cobj.edobj==1&&dbm.selbz!=1)
	{
		cobj.objw->EmptyEdit();
		cobj.edobj=0;
	}
}

void canvas::OnMouseMove(UINT nFlags, CPoint point) 
{
	int ks;
	char p[100];
	ChkMousemove(point);
	//显示鼠标位置
	dbm.mpoint=point;
	CStatusBar *pStatus=(CStatusBar *)AfxGetMainWnd()->GetDescendantWindow(AFX_IDW_STATUS_BAR); 
	sprintf(p,"%d,%d",(int)((point.x-dbm.dx)/cobj.curzoom),	(int)((point.y-dbm.dy)/cobj.curzoom));
	pStatus->SetPaneText(1,p);
	ks=GetKeyState(VK_LCONTROL);
	if(ks<0||cobj.cursor==102) MovePic(point);
	else MouseMove(point);
	CWnd::OnMouseMove(nFlags, point);
}


//鼠标移动
void canvas::MouseMove(CPoint point)
{
	int cur;
	CPoint pt,ptt;
	CRect rt;
	cur=cobj.cursor;
	if(dbm.dnbz==1)
	{
		pt2=point;
		rpt2=point;
		rpt2.Offset(-dbm.dx,-dbm.dy);
		switch(cur)
		{
		case 0:  case 4:  case 5:   case 6:  case 7:  case 8:
		case 10: case 11: case 12:	case 13: case 14: case 15:
		case 16: case 17: case 64:  case 67: case 35: case 80: case 103:
		case 68: case 69: case 70:  case 71: case 72: case 73:
		case 74: case 75: case 78:	case 79: case 33: case 34: 
		case 81: case 260: case 83:
			rt=CRect(rpt1,rpt2);
			rt.NormalizeRect();
	  		DrawXorRect(rt);
			break;
		case 100: case 101: //选择的对象移动
			MoveObject(rpt2.x-rpt1.x,rpt2.y-rpt1.y);
			break;
		case 104: //拖动放大
			ZoomInOut();		
			break;
		case 201:  ClearImg(point);  break;
		case 205:  BrushImage(point);break;
		case 206:  BrightImg(point); break;
 	 	}
	}
	if(dbm.dnbz==0&&(cur==0||cur==100||cur==101)) cobj.cursor=dbm.GetCursor(point);
	if(dbm.dnbz==0&&tptsum>0)
	{
		switch(cobj.cursor)
		{
		case 1:case 2:case 9:case 16:case 18:case 76:case 77:case 63:case 32:case 65:case 82:
			MoveDrawLine(point);
			break;
		}
	}
}


void canvas::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CMenu *mm;
	switch(cobj.cursor){  //特殊绘图
	case 1:  AddPoint(point);  AddDbx(0);   return;
	case 9:  AddPoint(point);  AddArrow();	return;
	case 18: AddPoint(point);  AddPath();	return;
	case 32: AddPoint(point);   AddMeter1();return;
	case 76: AddPoint(point);  AddConLine();return;
	case 77: AddPoint(point);  AddFlow();	return;
	case 63: AddPoint(point);  AddRegon();	return;
	case 65: AddPoint(point);  AddReservoir();	return;
	case 82: AddPoint(point);  AddZone();	return;
	};
	pt2=point;
	ClientToScreen(&point);
	mm=RMenuSet();
	if(mm!=NULL) mm->TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);
	ReleaseCapture();
	
	CWnd::OnRButtonDown(nFlags, point);
}

CMenu *canvas::RMenuSet()
{
	CMenu *mm=NULL;
	int j,type;
	bool bl;
	bl=dbm.cpage->head.type==2 ? false:true;
	if(dbm.selbz==1){
	j=dbm.GetFirstSelObj();
	type=dbm.clayer->obj[j].attr.type;
	switch(type){
	case 1: case 2:  case 3:  case 4:  case 5:  case 6:  case 7: case 8: 
	case 9:	case 10: case 11: case 12: case 13: case 14: case 15:case 16:
	case 17:case 71: case 72:  case 75: case 81:case 32: case 33: case 34:
	case 35:  case 84: case 68:
		mm=pmenu1.GetSubMenu(0);
		if(type==1) mm->EnableMenuItem(IDC_DBXTOLINE,0);
		else mm->EnableMenuItem(IDC_DBXTOLINE,1);
		if(type==1) mm->EnableMenuItem(IDC_DBXTOCL,0);
		else mm->EnableMenuItem(IDC_DBXTOCL,1);
		break;
	case 76: case 74:
		mm=pmenu2.GetSubMenu(0);
		break;
	case 64: case 67: case 69: case 70: case 73:  case 80: case 82:case 65: case 83:
		mm=pmenu3.GetSubMenu(0);
		break;
	case 66: case 77: case 78: 
		mm=pmenu.GetSubMenu(0);
		break;
	case 79:
		mm=pmenu6.GetSubMenu(0);
		break;
	}
	}
	if(dbm.selbz==2) mm=pmenu4.GetSubMenu(0);
	if(mm==NULL) mm=pmenu5.GetSubMenu(0);
	return mm;
}
//添加一个区域显示
void canvas::AddRegon()
{
	int i;
	for(i=0;i<tptsum;i++){
	  //tpt[i].Offset(-dbm.dx,-dbm.dy);
	  dbm.tpt[i]=tpt[i];
	};
	dbm.tptsum=tptsum;
	ReleaseCapture();
	tptsum=0;
	Invalidate();
	cobj.cursor=0;
	
	dbm.selrgn=1;
}


//拖动放缩
void canvas::ZoomInOut()
{
	double oldz;
	int x,y;
	oldz=cobj.curzoom;
	x=pt2.x-pt1.x;
	y=pt2.y-pt1.y;
	pt1=pt2;
	if(x<0&&y<0) dbm.ZoomPage(1);
	if(x>0&&y>0) dbm.ZoomPage(2);
	if(oldz!=cobj.curzoom) ZoomChange();
}

//移动选中的对象
void canvas::MoveObject(int mx, int my)
{
	CRect rt;
	CDRect rt1,rt2;
	double lx,ly;
	if(drawbg==1){
		drawbg=0;		
		ShowA();
	}
	lx=(double)(mx/cobj.curzoom);
	ly=(double)(my/cobj.curzoom);
	dbm.movebz=1;
	rt1=dbm.selrt;
	rt1.NormalizeRect();
	if(dbm.selbz==1) dbm.MoveObject1(lx,ly);
	if(dbm.selbz==2) dbm.MoveObject2(lx,ly);
	rt2=dbm.selrt;
	rt2.NormalizeRect();
	rt1|=rt2;
	rt1.ActRtToScr(cobj.curzoom);
	rt1.Offset(dbm.dx,dbm.dy);
	rt1.left-=30;
	rt1.top-=30;
	rt1.right+=30;
	rt1.bottom+=30;
	rt1.GetRECT(rt);

	CClientDC dc(this);
	rt&=CRect(0,0,wx,wy);
	ShowB(dc,rt);
}


void canvas::MoveDrawLine(CPoint pt) //移动时画线
{
	int ks,qx,qy;
	CPoint tp;
	CClientDC dc(this);
	if(tptsum<1) return;
	ks=GetKeyState(VK_LSHIFT);
	tp=pt;
	tp.Offset(-dbm.dx,-dbm.dy);
	if(ks<0)
	{
		qx=tp.x-tpt[tptsum-1].x;
		qy=tp.y-tpt[tptsum-1].y;
		qx=qx<0 ? -qx:qx;
		qy=qy<0 ? -qy:qy;
		if(qx>=qy)
		{
			tp.y=tpt[tptsum-1].y;
		}else{
			tp.x=tpt[tptsum-1].x;
		}
	}
	mpt=tp;
	GLLineXor(dc.m_hDC,tpt[tptsum-1].x+dbm.dx,tpt[tptsum-1].y+dbm.dy,oldpt.x+dbm.dx,oldpt.y+dbm.dy);
	GLLineXor(dc.m_hDC,tpt[tptsum-1].x+dbm.dx,tpt[tptsum-1].y+dbm.dy,mpt.x+dbm.dx,mpt.y+dbm.dy);
	oldpt=tp;
}


//画线
void canvas::DrawingLine(HDC hdc,int dx,int dy)
{
	CPoint jpt[401];
	int i;
	HPEN oldpen,pen;
	if(tptsum<2) return;
	pen=CreatePen(PS_DOT,1,0xffffff);
	oldpen=(HPEN)SelectObject(hdc,pen);
	SetROP2(hdc,R2_XORPEN);
	MoveToEx(hdc,tpt[0].x+dx,tpt[0].y+dy,NULL);
	for(i=1;i<tptsum;i++) LineTo(hdc,tpt[i].x+dx,tpt[i].y+dy);
	SelectObject(hdc,oldpen);
	DeleteObject(pen);
	SetROP2(hdc,R2_COPYPEN);
}

void canvas::DrawXorRect(CRect rt)
{
	CRect rt1;
	CClientDC dc(this);
	rt1=rt;
	rt1.OffsetRect(dbm.dx,dbm.dy);
	dc.DrawDragRect(&rt1,CSize(1,1),&oldrt,CSize(1,1));
	oldrt=rt1;
}

//加入一个点
void canvas::AddPoint(CPoint point)
{
	int ks,qx,qy;
	CPoint tp;
	
	//点数太多
	if(tptsum>=1000) return;

	if(tptsum==0)
	{
		tpt[0]=point;
		tpt[0].Offset(-dbm.dx,-dbm.dy);
	    tptsum++;
		oldpt=tpt[0];
		return;
	}

	ks=GetKeyState(VK_LSHIFT);
	tp=point;
	tp.Offset(-dbm.dx,-dbm.dy);

	if(ks<0)
	{
		qx=tp.x-tpt[tptsum-1].x;
		qy=tp.y-tpt[tptsum-1].y;
		qx=qx<0 ? -qx:qx;
		qy=qy<0 ? -qy:qy;
		if(qx>=qy)
		{
			tp.y=tpt[tptsum-1].y;
		}else{
			tp.x=tpt[tptsum-1].x;
		}
	}
	//计算两点间的距离,如果太小则退出
	if(tptsum>0)
	{
		int dis=GetDistance(tp,tpt[tptsum-1]);
		if(dis<3) return;
	};
	pt1=tp;
	oldpt=tp;;
	tpt[tptsum]=tp;
	tptsum++;
}

//擦图操作
void canvas::ClearImg(CPoint point)
{
	CRect rt;
	CPoint oldp;
	oldp=dbm.oldpt1;
	dbm.ClearImgBg(point);
	rt=CRect(oldp,point);
	rt.NormalizeRect();
	rt.left=rt.left-dbm.pwidth;
	rt.top=rt.top-dbm.pwidth;
	rt.right=rt.right+dbm.pwidth;
	rt.bottom=rt.bottom+dbm.pwidth;
	CClientDC dc(this);
	Show(dc,rt);
}

//剪去一块图形
void canvas::CutImage(CPoint point)
{
	CRect rt=dbm.CutImage(point);
	Invalidate();
	/*CClientDC dc(this);
	//if(!rt.IsRectEmpty()){
		Show(dc,rt);
	//};*/
}

//透明颜色
void canvas::TranImage(CPoint point)
{
	CRect rt=dbm.TranImage(point);
	CClientDC dc(this);
	if(!rt.IsRectEmpty()){
		Show(dc,rt);
	};
}

//刷图形
void canvas::BrushImage(CPoint point)
{
	CRect rt=dbm.BrushImage(point,cobj.outcolor);
	if(!rt.IsRectEmpty()){
		CClientDC dc(this);
		Show(dc,rt);
	};
}

//加亮图形
void canvas::BrightImg(CPoint point)
{
	CRect rt=dbm.AddBrightImg(point);
	if(!rt.IsRectEmpty()){
		CClientDC dc(this);
		Show(dc,rt);
	};
}

//局部放大
void canvas::PartZoom(CRect rt)
{
	double xl,yl,a,k;
	int w,h;
	CRect rt1;
	CPoint pt;
	rt1=rt;
	rt1.NormalizeRect();
	pt=rt1.CenterPoint();
	w=rt1.Width();
	h=rt1.Height();
	if(w==0||h==0) return;
	vx=(int)(pt.x/cobj.curzoom);
	vy=(int)(pt.y/cobj.curzoom);
	xl=(double)(wx/(double)w);
	yl=(double)(wy/(double)h);
	a=xl<yl ? xl:yl;
	k=cobj.curzoom;
	k=(double)(k*a);
	switch(dbm.cpage->head.type){
	case 0: k=k>4	? 4:k;	break;
	case 1: k=k>10	? 10:k;	break;
	case 2: k=k>100 ? 100:k;break;
	default:return;
	}
	if(k<0.1) return;
	cobj.curzoom=k;
	dbm.cpage->zw=(int)(dbm.cpage->head.width*cobj.curzoom);
	dbm.cpage->zh=(int)(dbm.cpage->head.height*cobj.curzoom);
	ZoomChange();
}

bool canvas::GetAAttr(int type,N_BASATTR&atr)
{
	atr.type=(BYTE)type;
	atr.size=0;
	atr.ID=dbm.GetNewID();//唯一ID
	switch(type)
	{
	 case 1:  atr.size=sizeof(N_DBX);	break;
	 case 2:  atr.size=sizeof(N_RECT);	break;
	 case 3:  atr.size=sizeof(N_CIRCLE);break;
	 case 4:  atr.size=sizeof(N_HSIN);	break;
	 case 5:  atr.size=sizeof(N_SIN);	break;
	 case 6:  atr.size=sizeof(N_ARC);	break;
	 case 7:  atr.size=sizeof(N_ARROW);	break;
	 case 8:  atr.size=sizeof(N_GLASS);	break;
	 case 10: atr.size=sizeof(N_TEXT);	break;
	 case 11: atr.size=sizeof(N_ESITE);	break;
	 case 12: atr.size=sizeof(N_EGPMB); break;
	 case 13: atr.size=sizeof(N_COORDINATE); break;
	 case 14: atr.size=sizeof(N_TABLE); break;
	 case 15: atr.size=sizeof(N_IMG);   break;
	 case 17: atr.size=sizeof(N_SPIC);	break;
	 case 32: atr.size=sizeof(N_METER1);break;
	 case 33: atr.size=sizeof(N_METER2);break;
	 case 34: atr.size=sizeof(N_METER3);break;
	 case 35: atr.size=sizeof(N_METER4);break;
	 case 64: atr.size=sizeof(N_ANL);	break;
	 case 66: atr.size=sizeof(N_ELEGRPA);break;
	 case 67: atr.size=sizeof(N_ELEGRPYB);break;
	 case 68: atr.size=sizeof(N_SYSPIE); break;
	 case 69: atr.size=sizeof(N_BAR);	break;
	 case 70: atr.size=sizeof(N_PIE);	break;
	 case 71: atr.size=sizeof(N_DATE);	break;
	 case 72: atr.size=sizeof(N_TIME);	break;
	 case 73: atr.size=sizeof(N_GIFAML);break;
	 case 74: atr.size=sizeof(N_SRLTEXT);break;
	 case 75: atr.size=sizeof(N_PUSH);	 break;
	 case 76: atr.size=sizeof(N_SELFCTL);break;
	 case 79: atr.size=sizeof(N_BUS);	 break;
	 case 80: atr.size=sizeof(N_ACTOBJ); break;
	 case 81: atr.size=sizeof(N_FLASH);  break;
	 case 82: atr.size=sizeof(N_PCTPIE); break;
	 case 83: atr.size=sizeof(N_ZONE);   break;
	 case 84: atr.size=sizeof(N_MTTEXT); break;
	 };
	return true;
}
//加入一个多边形
void canvas::AddDbx(int type)
{
	int i,size;
	N_BASATTR  atr;
	char       *buf;
	DPOINT     *pt;
	CDPoint     apt; 
	N_DBX      *dbx;
	if(tptsum<=1) return;
	GetAAttr(1,atr);
	size=sizeof(N_DBX)+tptsum*sizeof(DPOINT);
	atr.size=size;
	buf=new char[size];
	dbx=(N_DBX*)buf;
	dbx->bcolor1=cobj.bcolor1;
	dbx->bcolor2=cobj.bcolor2;
	dbx->fillmode=cobj.fillmode;
	dbx->ltype=0;
	dbx->lmode=0;
	dbx->bgmode=0;
	dbx->autozoom=0;
	dbx->fill=cobj.fill;
	dbx->close=cobj.close;
	dbx->lcolor=cobj.outcolor;
	dbx->width=cobj.linewd/cobj.curzoom;
	dbx->ptsum=tptsum;
	pt=dbx->pt;
	for(i=0;i<tptsum;i++){
		apt.SetPOINT(tpt[i]);
		apt.ScrPtToAct(cobj.curzoom);
		pt[i].x=apt.x;
		pt[i].y=apt.y;
	};
	dbm.AddAObject(atr,buf,1);
	tptsum=0;
	DrawShow();
	delete buf;
	
	ShowObjsum();
}

//加入一个矩形
void canvas::AddRect()
{
	N_BASATTR  atr;
	N_RECT   nrt;
	GetAAttr(2,atr);
	nrt.bcolor1=cobj.bcolor1;
	nrt.bcolor2=cobj.bcolor2;
	nrt.fillmode=cobj.fillmode;
	nrt.fill=cobj.fill;
	nrt.type=0;
	nrt.autozoom=0;
	nrt.lcolor=cobj.outcolor;
	nrt.width=cobj.linewd/cobj.curzoom;
	if(CreateNPOINT4dot(nrt.pt)) dbm.AddAObject(atr,&nrt,1);
	DrawShow();
	ShowObjsum();
}

//加入一个园
void canvas::AddCircle()
{
	N_BASATTR  atr;
	N_CIRCLE   ncr;
	GetAAttr(3,atr);
	ncr.bcolor1=cobj.bcolor1;
	ncr.bcolor2=cobj.bcolor2;
	ncr.fillmode=cobj.fillmode;
	ncr.fill=cobj.fill;
	ncr.type=0;
	ncr.autozoom=0;
	ncr.lcolor=cobj.outcolor;
	ncr.width=cobj.linewd/cobj.curzoom;
	if(CreateNPOINT4dot(ncr.pt)) dbm.AddAObject(atr,&ncr,1);
	DrawShow();
	ShowObjsum();
}

//加入一个半波矩形
void canvas::AddHSin()
{
	N_BASATTR  atr;
	N_HSIN	   hsn;
	GetAAttr(4,atr);
	hsn.color=cobj.outcolor;
	hsn.bcolor=cobj.bcolor1;
	hsn.pirodic=2;
	hsn.ltype=0;
	hsn.lmode=0;
	hsn.endcap=0;
	hsn.autozoom=0;
	hsn.width=cobj.linewd/cobj.curzoom;
	if(CreateNPOINT4dot(hsn.pt)) dbm.AddAObject(atr,&hsn,1);
	DrawShow();
	ShowObjsum();
}

//加入一个正弦波
void canvas::AddSin()
{
	N_BASATTR  atr;
	N_SIN	   sn;
	GetAAttr(5,atr);
	sn.color=cobj.outcolor;
	sn.pirodic=1;
	sn.ltype=0;
	sn.startdeg=0;
	if(CreateNPOINT4dot(sn.pt)) dbm.AddAObject(atr,&sn,1);
	DrawShow();
	ShowObjsum();
}
//加入一个正弦波
void canvas::AddArc()
{
	N_BASATTR  atr;
	N_ARC	   arc;
	GetAAttr(6,atr);
	arc.color=cobj.outcolor;
	arc.start=0;
	arc.end=90;
	arc.autozoom=0;
	arc.width=cobj.linewd/cobj.curzoom;
	if(CreateNPOINT4dot(arc.pt)) dbm.AddAObject(atr,&arc,1);
	DrawShow();
	ShowObjsum();
}

//加入一个方向箭头
void canvas::AddArrow()
{
	int i;
	N_BASATTR  atr;
	CDPoint   apt; 
	N_ARROW  arw;
	if(tptsum<2) return;
	GetAAttr(7,atr);
	arw.color=cobj.outcolor;
	arw.width=cobj.linewd/cobj.curzoom;
	arw.autozoom=0;
	for(i=0;i<2;i++){
	  apt.SetPOINT(tpt[i]);
	  //apt.Offset(-dbm.dx,-dbm.dy);
	  apt.ScrPtToAct(cobj.curzoom);
	  arw.pt[i].x=apt.x;
	  arw.pt[i].y=apt.y;
	}
	dbm.AddAObject(atr,&arw,1);
	tptsum=0;
	DrawShow();
	
	ShowObjsum();
}

//加入一个玻璃层
void canvas::AddGlass()
{
	N_BASATTR  atr;
	N_GLASS	   gl;
	GetAAttr(8,atr);
	gl.color=cobj.bcolor1;
	gl.ocolor=cobj.outcolor;
	gl.outline=1;
	gl.depth=100;
	if(CreateNPOINT4dot(gl.pt)) dbm.AddAObject(atr,&gl,1);
	DrawShow();
	ShowObjsum();
	cobj.cursor=0;
}

//添加一个立体棒
void canvas::AddText()
{
	CSize size;
	N_BASATTR  atr;
	N_TEXT	   tx;
	GetAAttr(10,atr);
	tx.color=cobj.tcolor;
	tx.autofill=0;
	tx.style=cobj.tmode;
	tx.font=cobj.font;
	strcpy(tx.text,"新文本");
	tx.zm=1;
	if(CreateNPOINT4dot(tx.pt)){;
	 ReleaseCapture();
	 CClientDC dc(this);
	 if(EditText(tx.text,44,m_hWnd)){
	  size=GLDGetTextSize(dc.m_hDC,&tx.font,tx.text);
	  dbm.AddAObject(atr,&tx,1);
	 };
	}
	DrawShow();
	ShowObjsum();
	cobj.cursor=0;
}

//添加一个多行状态
void canvas::AddMtText()
{
	CSize size;
	N_BASATTR  atr;
	N_MTTEXT   tx;
	GetAAttr(84,atr);
	tx.fcolor=cobj.tcolor;
	tx.lf=cobj.font;
	tx.did=-1;
	strcpy(tx.text,"AGCRUN===AGCSUBSPEND===AGCSTOP");
	tx.type=0;
	strcpy(tx.name,"");
	if(CreateNPOINT4dot(tx.pt))  dbm.AddAObject(atr,&tx,1);
	DrawShow();
	ShowObjsum();
	cobj.cursor=0;
}

//添加一个端子
void canvas::AddEsite()
{
	N_BASATTR  atr;
	N_ESITE	   es;
	GetAAttr(11,atr);
	es.color=cobj.outcolor;
	es.solder=0;
	if(CreateNPOINT4dot(es.pt,1)) dbm.AddAObject(atr,&es,1);
	DrawShow();
	ShowObjsum();
}

void canvas::AddEgpmb()
{
	N_BASATTR  atr;
	N_EGPMB	   em;
	GetAAttr(12,atr);
	em.color=cobj.outcolor;
	em.mode=1;
	if(CreateNPOINT4dot(em.pt)) dbm.AddAObject(atr,&em,1);
	DrawShow();
	ShowObjsum();
	cobj.cursor=0;
}

void canvas::AddCoordinate()
{
	N_BASATTR  atr;
	N_COORDINATE   co;
	GetAAttr(13,atr);
	co.colorc=0xc0c0c0;
	co.colorw=0x7f7f7f;
	co.colort=0xc0c0c0;
	co.wxdraw=1;
	co.wydraw=1;
	co.xdot=5;
	co.ydot=4;
	co.xmax=100;
	co.xmin=0;
	co.ymax=100;
	co.ymin=0;
	co.xvshow=1;
	co.yvshow=1;
	co.width1=1/cobj.curzoom;
	co.width2=1/cobj.curzoom;
	co.fontx=cobj.font;
	co.fonty=cobj.font;
	co.zm=1;
	if(CreateNPOINT4dot(co.pt)) dbm.AddAObject(atr,&co,1);
	DrawShow();
	ShowObjsum();
}

void canvas::AddTable()
{
	N_BASATTR  atr;
	N_TABLE    ta;
	GetAAttr(14,atr);
	ta.color=0xc0c0c0;
	ta.dbline=1;
	ta.width=1/cobj.curzoom;
	ta.line=5;
	if(CreateNPOINT4dot(ta.pt)) dbm.AddAObject(atr,&ta,1);
	DrawShow();
	ShowObjsum();
}

void canvas::AddImage()
{
	char filter[385];
	char filename[256];
	int id;
	N_BASATTR  atr;
	N_IMG    img;
	GetAAttr(15,atr);
	img.depth=0;
	img.imgID=0;
	img.shadow=0;
	img.zoom=0;
	if(CreateNPOINT4dot(img.pt)){
	 sprintf(filter,"%s%s|%s|%s|%s|%s|%s|%s|%s",ftr[0],ftr[1],ftr[2],ftr[3],ftr[4],ftr[5],
     ftr[6],ftr[7],ftr[8]);
	 if(GetImgFile(filename,filter,m_hWnd)){
		id=cobj.GetANoUseMPICID();
		cobj.AddMpic(filename,id);
		img.imgID=(WORD)id;
		dbm.AddAObject(atr,&img,1);
	 }
	}
	DrawShow();
	ShowObjsum();
	cobj.cursor=0;
}

void canvas::AddMeter1()
{
	int i;
	N_BASATTR  atr;
	CDPoint   apt; 
	N_METER1  mtr;
	GetAAttr(32,atr);
	for(i=0;i<2;i++){
	  apt.SetPOINT(tpt[i]);
	  apt.ScrPtToAct(cobj.curzoom);
	  mtr.pt[i].x=apt.x;
	  mtr.pt[i].y=apt.y;
	}
	mtr.font=cobj.font;
	mtr.showarc=1;
	mtr.alarm=0;
	mtr.Vmin=0;
	mtr.Vmax=100;
	mtr.pstyle=0;		
	mtr.pcr=0xff;			
	mtr.scr=0xff00;			
	mtr.alarm=2;			
	mtr.val[0]=60;		
	mtr.val[1]=80;		
	mtr.val[2]=80;			
	mtr.val[3]=100;		
	mtr.cr[0]=0xff00;
	mtr.cr[1]=0xff;	
	mtr.angle=134;
	mtr.scale=10;			//刻度数
	mtr.slen=10;
	mtr.scales=5;			//每格的小刻度数
	mtr.shownum=1;
	mtr.numdot=0;			//小数点
	mtr.zm=1;
	mtr.stype=0;
	mtr.lstype=0;
	mtr.axw=4;				//轴的宽度
	mtr.pw=3;				//箭头宽度
	dbm.AddAObject(atr,&mtr,1);
	tptsum=0;
	DrawShow();
	ShowObjsum();
	
	cobj.cursor=0;

}

//加入一个刻度仪表
void canvas::AddMeter2()
{
	N_BASATTR  atr;
	CDPoint   apt; 
	N_METER2  mtr;
	GetAAttr(33,atr);
	mtr.alarm=0;
	mtr.Vmin=0;
	mtr.Vmax=100;
	mtr.pcr=0xff;			
	mtr.scr=0xff00;			
	mtr.alarm=2;			
	mtr.val[0]=60;		
	mtr.val[1]=80;		
	mtr.val[2]=80;			
	mtr.val[3]=100;		
	mtr.cr[0]=0xff00;
	mtr.cr[1]=0xff;	
	mtr.scale=5;			//刻度数
	mtr.scales=2;			//每格的小刻度数
	mtr.shownum=1;
	mtr.numdot=0;			//小数点
	mtr.showbl=1;
	if(CreateNPOINT4dot(mtr.pt)) dbm.AddAObject(atr,&mtr,1);
	DrawShow();
	ShowObjsum();
	cobj.cursor=0;
}

//加入一个刻度仪表
void canvas::AddMeter3()
{
	N_BASATTR  atr;
	CDPoint   apt; 
	N_METER3  mtr;
	GetAAttr(34,atr);
	mtr.alarm=0;
	mtr.Vmin=0;
	mtr.Vmax=100;
	mtr.pcr=0xff;			
	mtr.scr=0xff00;			
	mtr.alarm=2;			
	mtr.val[0]=60;		
	mtr.val[1]=80;		
	mtr.val[2]=80;			
	mtr.val[3]=100;		
	mtr.cr[0]=0xff00;
	mtr.cr[1]=0xff;	
	mtr.scale=5;			//刻度数
	mtr.scales=2;			//每格的小刻度数
	mtr.shownum=1;
	mtr.numdot=0;			//小数点
	mtr.showbl=1;
	if(CreateNPOINT4dot(mtr.pt)) dbm.AddAObject(atr,&mtr,1);
	DrawShow();
	ShowObjsum();
	cobj.cursor=0;
}


//加入一个数码表
void canvas::AddMeter4()
{
	N_BASATTR  atr;
	CDPoint   apt; 
	N_METER4  mtr;
	GetAAttr(35,atr);
	mtr.num=6;
	mtr.numdot=2;			//小数点
	mtr.ncr[0]=0xff00;
	mtr.ncr[1]=0xff;
	mtr.bcr=0xff00;
	if(CreateNPOINT4dot(mtr.pt)) dbm.AddAObject(atr,&mtr,1);
	DrawShow();
	ShowObjsum();
	cobj.cursor=0;
}

//加入一个多边形
void canvas::AddPath()
{
	int i,size;
	N_BASATTR  atr;
	char     *buf;
	DPOINT   *pt;
	CDPoint   apt; 
	N_PATH   *pth;
	if(tptsum<=1) return;
	GetAAttr(16,atr);
	size=sizeof(N_PATH)+tptsum*sizeof(DPOINT);
	atr.size=size;
	buf=new char[size];
	pth=(N_PATH*)buf;
	pth->start=0;
	pth->end=100;
	pth->ID=100;
	pth->color=0xc0c0c0;
	pth->ptsum=tptsum;
	pt=pth->pt;
	for(i=0;i<tptsum;i++){
		apt.SetPOINT(tpt[i]);
		apt.ScrPtToAct(cobj.curzoom);
		pt[i].x=apt.x;
		pt[i].y=apt.y;
	};
	dbm.AddAObject(atr,buf,1);
	tptsum=0;
	DrawShow();
	delete buf;
	
	ShowObjsum();
	cobj.cursor=0;
}

//添加模拟量
void canvas::AddAnalog()
{
	int i;
	N_BASATTR  atr;
	N_ANL    anl;
	memset(&anl,0,sizeof(N_ANL));
	GetAAttr(64,atr);
	anl.acolor=cobj.acolor;
	anl.ncolor=cobj.ncolor;
	strcpy(anl.dev_name,"");
	anl.did=-1;
	anl.lf=cobj.font;
	strcpy(anl.lf.lfFaceName,"Arial");
	anl.direction=0;
	anl.style=0;
	anl.xsmode=0;
	anl.xs=2;
	for(i=0;i<5;i++){
		anl.rval[i].alarm=0;
		anl.rval[i].curval=(float)123.456789;
		anl.rval[i].enable=1;
	}
	anl.zm=1;
	anl.dtype=0;
	if(CreateNPOINT4dot(anl.pt)) dbm.AddAObject(atr,&anl,1);
	DrawShow();
	ShowObjsum();
	cobj.cursor=0;
}





//添加棒图
void canvas::AddBar()
{
	N_BASATTR   atr;
	N_BAR		bar;
	GetAAttr(69,atr);
	strcpy(bar.dsrc.name,"");
	bar.dsrc.did=-1;
	bar.dsrc.dtype=0;
	bar.dsrc.xsmode=0;
	bar.max=200;
	bar.min=0;
	bar.ncolor=0xc0c0c0;
	bar.acolor=0xff;
	bar.aval=100;
	bar.xy=1;
	bar.outline=0;
	if(CreateNPOINT4dot(bar.pt)) dbm.AddAObject(atr,&bar,1);
	DrawShow();
	ShowObjsum();
	cobj.cursor=0;
}

//添加饼图
void canvas::AddPie()
{

	int i;
	DWORD   cr[]={0xff00,0xff,0xff0000,0x234400,0x8888,0xc0,0xc000,0xc00000};
    float dmvl[]={323,31,89,78,41,45,23,100};
	N_PIE  pie;
	N_BASATTR  atr;
	memset(&pie,0,sizeof(N_PIE));
	GetAAttr(70,atr);
	for(i=0;i<3;i++){
		pie.color[i]=cr[i];
	};
	pie.ID=100;
	pie.fcolor=0xffffff;			 //字符色
	pie.name[0]=0;
	pie.did=-1;
	pie.type=0;
	pie.lf=cobj.font;;
	if(CreateNPOINT4dot(pie.pt)) dbm.AddAObject(atr,&pie,1);
	DrawShow();
	ShowObjsum();
	cobj.cursor=0;
}

//添加系统饼图
void canvas::AddSysPie()
{

	int i;
	DWORD   cr[]={0xff00,0xff,0xff0000,0x234400,0x8888,0xc0,0xc000,0xc00000};
    float dmvl[]={323,31,89,78,41,45,23,100};
	N_SYSPIE  pie;
	N_BASATTR  atr;
	memset(&pie,0,sizeof(N_SYSPIE));
	GetAAttr(68,atr);
	for(i=0;i<6;i++)
	{
		pie.color[i]=cr[i];
	};
	pie.ID=100;
	pie.fcolor=0xffffff;			 //字符色
	pie.type=0;
	pie.lf=cobj.font;;
	if(CreateNPOINT4dot(pie.pt)) dbm.AddAObject(atr,&pie,1);
	DrawShow();
	ShowObjsum();
	cobj.cursor=0;
}


//添加日期
void canvas::AddDate()
{
	N_DATE  date;
	N_BASATTR  atr;
	GetAAttr(71,atr);
	date.bcolor=0xffffff;
	date.fcolor=0;
	date.fmt=0;
	date.font=cobj.font;
	date.outcolor=0;
	date.style=0;
	date.tran=0;
	date.shadow=0;
	date.outline=0;
	date.tm=CTime::GetCurrentTime();
	date.zm=1;
	if(CreateNPOINT4dot(date.pt)) dbm.AddAObject(atr,&date,1);
	DrawShow();
	ShowObjsum();
	cobj.cursor=0;
}

//添加时间
void canvas::AddTime()
{
	N_TIME  tim;
	N_BASATTR  atr;
	GetAAttr(72,atr);
	tim.bcolor=0xffffff;
	tim.fcolor=0;
	tim.fmt=0;
	tim.font=cobj.font;
	tim.outcolor=0;
	tim.style=0;
	tim.tran=0;
	tim.shadow=0;
	tim.outline=0;
	tim.tm=CTime::GetCurrentTime();
	tim.zm=1;
	if(CreateNPOINT4dot(tim.pt)) dbm.AddAObject(atr,&tim,1);
	DrawShow();
	ShowObjsum();
	cobj.cursor=0;
}

//添加GIF动画
void canvas::AddGifAnl()
{
	int  num,len;
	char filter[385];
	char filename[256];
	N_BASATTR   atr;
	N_GIFAML gal;
	num=cobj.GetNoUseGal();
	if(num<0){
	  MessageBox("动画缓冲区已满，不能添加GIF动画!");
	  return;
	};
	GetAAttr(73,atr);
	strcpy(gal.fname,"");
	if(CreateNPOINT4dot(gal.pt)){
	 sprintf(filter,"GIF动画 GIF文件(*.GIF)|*.gif");
	 if(GetImgFile(filename,filter,m_hWnd)){
		len=strlen(filename);
		if(len>63){
			MessageBox("文件名（含路经）太长！目前只支持63字节","提示");
			return;
		};
		strcpy(gal.fname,filename);
		gal.dsrc.dtype=0;
		gal.dsrc.xsmode=0;
		strcpy(gal.dsrc.name,"");
		gal.dsrc.did=-1;
		dbm.AddAObject(atr,&gal,1);
	 };
	}
	DrawShow();
	ShowObjsum();
	cobj.cursor=0;
}

//添加滚动文本
void canvas::AddScrText()
{;
	N_BASATTR   atr;
	N_SRLTEXT src;
	GetAAttr(74,atr);
	strcpy(src.text,"滚动文本");
	src.align=0;
	src.fcolor=0xff0000;
	src.depth=23;
	src.direct=1;
	src.gcolor=0xff0000;
	src.glass=1;
	src.id=100;
	src.outline=0;
	src.shadow=0;
	src.lf=cobj.font;
	src.tcolor=cobj.tcolor;
	src.tstyle=0;
	src.zm=1;
	if(CreateNPOINT4dot(src.pt)){
	 ReleaseCapture();
	 if(EditScrt(src.text,254,m_hWnd)){
		dbm.AddAObject(atr,&src,1);
	 };
	}
 	DrawShow();
 	ShowObjsum();
	cobj.cursor=0;
}

void canvas::AddPush()
{
	N_BASATTR   atr;
	N_PUSH psh;
	GetAAttr(75,atr);
	psh.style=0;
	psh.cmdtype=0;
	psh.shadow=0;
	psh.cmdnum=2000;
	psh.color1=0;
	psh.color2=0xff;
	psh.selfid=-1;
	psh.lf=cobj.font;
	psh.spicid=0;
	psh.autlin=1;
	psh.fstyle=0;
	psh.edit=1;
	psh.down=0;
	psh.zm=1;
	psh.tosta=0;
	psh.id=dbm.GetNoUseID(75);
	strcpy(psh.title,"新按钮");
	strcpy(psh.command,"");
	if(CreateNPOINT4dot(psh.pt)) dbm.AddAObject(atr,&psh,1);
	DrawShow();
	ShowObjsum();
	cobj.cursor=0;
}
//添加一个自助控件
void canvas:: AddSelfCtl()
{
	N_BASATTR   atr;
	N_SELFCTL slt;
	GetAAttr(76,atr);
	slt.dllname[0]=0;
	slt.hinst=0;
	slt.hwnd=0;
	slt.DfClose=0;
	slt.DfDrawDemo=0;
	slt.DfGetVer=0;
	slt.DfInit=0;
	slt.DfAbout=0;
	slt.DfSetParam=0;
	slt.style=0;
	slt.abottom=0;
	slt.aleft=0;
	slt.aright=0;
	slt.atop=0;
	slt.mode=0;
	memset(slt.lkbuf,0,255);
	slt.id=dbm.GetNoUseID(76);
	slt.rc=0;
	if(CreateNPOINT4dot(slt.pt)){
	 ReleaseCapture();
	 if(GetDllName(slt.dllname,m_hWnd)){
       dbm.AddAObject(atr,&slt,1);
	 };
	}
	DrawShow();
	ShowObjsum();
	cobj.cursor=0;
}


//加入一个连接线
void canvas::AddConLine()
{
	int i,size;
	N_BASATTR  atr;
	char     *buf;
	DPOINT   *pt;
	CDPoint   apt; 
	N_CONLINE  *cnl;
	if(tptsum<=1) return;
	GetAAttr(78,atr);
	size=sizeof(N_CONLINE)+tptsum*sizeof(DPOINT);
	atr.size=size;
	buf=new char[size];
	cnl=(N_CONLINE*)buf;
	cnl->vl=3;
	cnl->solder1=0;
	cnl->solder2=0;
	cnl->shadow=0;
	cnl->autozoom=0;
	cnl->conobj=0;
	cnl->el=0;
	cnl->width=(double)(cobj.linewd/cobj.curzoom);
	cnl->ptsum=tptsum;
	pt=cnl->pt;
	for(i=0;i<tptsum;i++){
		apt.SetPOINT(tpt[i]);
		apt.ScrPtToAct(cobj.curzoom);
		pt[i].x=apt.x;
		pt[i].y=apt.y;
	};
	dbm.AddAObject(atr,buf,1);
	tptsum=0;
	DrawShow();
	delete buf;
	
	ShowObjsum();
}

//加入一个潮流线
void canvas::AddFlow()
{
	int i,size;
	N_BASATTR  atr;
	char     *buf;
	DPOINT   *pt;
	CDPoint   apt; 
	N_FLOW   *flw;
	if(tptsum<=1) return;
	GetAAttr(77,atr);
	size=sizeof(N_FLOW)+tptsum*sizeof(DPOINT);
	atr.size=size;
	buf=new char[size];
	flw=(N_FLOW*)buf;
	flw->rf.pjs=0;
	flw->rf.pjs=15;
	flw->color1=0xff;
	flw->color2=0xff0000;
	flw->ptsum=tptsum;
	flw->style=0;
	flw->yh=0;
	flw->type=0;
	flw->direct=0;
	flw->linewidth=0;
	for(i=0;i<2;i++){
		flw->site[i].id=-1;
		flw->vl=cobj.vl;
	}

	strcpy(flw->dev_name,"");
	flw->did=-1;
	pt=flw->pt;
	for(i=0;i<tptsum;i++){
		apt.SetPOINT(tpt[i]);
		apt.ScrPtToAct(cobj.curzoom);
		pt[i].x=apt.x;
		pt[i].y=apt.y;
	};
	dbm.AddAObject(atr,buf,1);
	tptsum=0;
	DrawShow();
	delete buf;
	
	ShowObjsum();
	cobj.cursor=0;
}

//加入一个水库
void canvas::AddReservoir()
{
	int i,size;
	N_BASATTR  atr;
	char     *buf;
	DPOINT   *pt;
	CDPoint   apt; 
	N_RESERVOIR   *rev;
	if(tptsum<=1) return;
	GetAAttr(65,atr);
	size=sizeof(N_RESERVOIR)+tptsum*sizeof(DPOINT);
	atr.size=size;
	buf=new char[size];
	rev=(N_RESERVOIR*)buf;
	rev->color=0;
	rev->ncolor=0x00ff00;
	rev->hcolor=0xffc0c0;
	rev->lcolor=0xc0ffff;
	rev->ptsum=tptsum;
	strcpy(rev->dev_name,"");
	rev->did=-1;
	pt=rev->pt;
	for(i=0;i<tptsum;i++){
		apt.SetPOINT(tpt[i]);
		apt.ScrPtToAct(cobj.curzoom);
		pt[i].x=apt.x;
		pt[i].y=apt.y;
	};
	dbm.AddAObject(atr,buf);
	tptsum=0;
	DrawShow();
	delete buf;
	
	ShowObjsum();
	cobj.cursor=0;
}

//加入一个区域
void canvas::AddZone()
{
	int i,size;
	N_BASATTR  atr;
	char     *buf;
	DPOINT   *pt;
	CDPoint   apt; 
	N_ZONE   *zon;
	if(tptsum<=1) return;
	GetAAttr(83,atr);
	size=sizeof(N_ZONE)+tptsum*sizeof(DPOINT);
	atr.size=size;
	buf=new char[size];
	zon=(N_ZONE*)buf;
	zon->lcolor=0xff;
	strcpy(zon->zone_name,"未知区域");
	zon->did=-1;
	pt=zon->pt;
	zon->lf=cobj.sysfont;
	zon->fcolor=0xff;
	for(i=0;i<tptsum;i++)
	{
		apt.SetPOINT(tpt[i]);
		apt.ScrPtToAct(cobj.curzoom);
		pt[i].x=apt.x;
		pt[i].y=apt.y;
	};
	zon->ptsum=tptsum;
	dbm.AddAObject(atr,buf);
	tptsum=0;
	DrawShow();
	delete buf;
	
	ShowObjsum();
	cobj.cursor=0;
	
}


//加入一个区域
void canvas::AddDZone(int ptsum,DPOINT *pt1)
{
	int i,size;
	N_BASATTR  atr;
	char     *buf;
	N_ZONE   *zon;
	DPOINT   *pt;
	if(ptsum<=3) return;
	GetAAttr(83,atr);
	size=sizeof(N_ZONE)+ptsum*sizeof(DPOINT);
	atr.size=size;
	buf=new char[size];
	zon=(N_ZONE*)buf;
	zon->lcolor=0xff;
	strcpy(zon->zone_name,"未知区域");
	zon->did=-1;
	pt=zon->pt;
	zon->lf=cobj.sysfont;
	zon->fcolor=0xff;
	for(i=0;i<ptsum;i++)
	{
		pt[i].x=pt1[i].x;
		pt[i].y=pt1[i].y;
	};
	zon->ptsum=ptsum;
	dbm.AddAObject(atr,buf);
	DrawShow();
	delete buf;
	ShowObjsum();	
}


//转换加入一个线路
bool canvas::AddDLine(int ptsum,DPOINT *pt1)
{
	int i,size;
	N_BASATTR  atr;
	char     *buf;
	N_FLOW   *flw;
	DPOINT   *pt;
	if(ptsum<2) return false;
	GetAAttr(77,atr);
	size=sizeof(N_FLOW)+ptsum*sizeof(DPOINT);
	atr.size=size;
	buf=new char[size];
	flw=(N_FLOW*)buf;
	flw->linewidth=0;
	flw->type=0;;
	flw->vl=4;
	strcpy(flw->dev_name,"未知");
	flw->did=-1;
	pt=flw->pt;
	for(i=0;i<ptsum;i++)
	{
		pt[i].x=pt1[i].x;
		pt[i].y=pt1[i].y;
	};
	flw->ptsum=ptsum;
	dbm.AddAObject(atr,buf);
	DrawShow();
	delete buf;
	ShowObjsum();	
	return true;
}

//转换加入一个线路
bool canvas::AddCLine(int ptsum,DPOINT *pt1)
{
	int i,size;
	N_BASATTR  atr;
	char     *buf;
	N_CONLINE   *cl;
	DPOINT   *pt;
	if(ptsum<2) return false;
	GetAAttr(78,atr);
	size=sizeof(N_CONLINE)+ptsum*sizeof(DPOINT);
	atr.size=size;
	buf=new char[size];
	cl=(N_CONLINE*)buf;
	cl->vl=4;
	pt=cl->pt;
	for(i=0;i<ptsum;i++)
	{
		pt[i].x=pt1[i].x;
		pt[i].y=pt1[i].y;
	};
	cl->ptsum=ptsum;
	dbm.AddAObject(atr,buf);
	DrawShow();
	delete buf;
	ShowObjsum();	
	return true;
}

//添加母线
void canvas::AddBus()
{
	N_BUS  bus;
	N_BASATTR  atr;
	GetAAttr(79,atr);
	bus.type=0;
	bus.yh=0;
	bus.vl=cobj.vl;
	bus.shadow=0;
	strcpy(bus.dev_name,"");
	bus.did=-1;
	if(CreateNPOINT4dot(bus.pt)) dbm.AddAObject(atr,&bus,1);
	DrawShow();
	ShowObjsum();
	cobj.cursor=0;
}

//添加实心图
void canvas::AddActObj()
{
	N_BASATTR   atr;
	N_ACTOBJ    act;
	GetAAttr(80,atr);
	act.gid=-1;
	act.pathid=100;
	act.runmode=0;
	strcpy(act.dsrc.name,"");
	act.dsrc.did=-1;
	act.dsrc.dtype=0;
	act.dsrc.xsmode=0;
	act.skip=1;
	act.speed=0;
	if(CreateNPOINT4dot(act.pt)) {dbm.AddAObject(atr,&act,1);}
	DrawShow();
	ShowObjsum();
	cobj.cursor=0;
}

//添加FLASH部件
void canvas::AddFlash()
{
	int len;
	char filter[256],filename[512];
	N_BASATTR   atr;
	N_FLASH     fsh;
	GetAAttr(81,atr);
	strcpy(fsh.fname,"");
	fsh.playmode=0;
	if(CreateNPOINT4dot(fsh.pt)){
	 sprintf(filter,"Flash:SWF文件(*.swf)|*.swf");
	 if(GetImgFile(filename,filter,m_hWnd)){
		len=strlen(filename);
		if(len>127){
			MessageBox("文件名（含路经）太长！目前只支持127字节","提示");
			return;
		};
		strcpy(fsh.fname,filename);
		dbm.AddAObject(atr,&fsh,1);
	 };
	}
	DrawShow();
	ShowObjsum();
	cobj.cursor=0;
}


//添加一个小图标到桌面
void canvas::Addspic()
{
	int i,w,h,x,y;
	N_BASATTR   atr;
	N_SPIC  spic;
	GetAAttr(17,atr);
	spic.picID=cobj.patternID;
	spic.zoom=0;
	i=cobj.GetPICRecno(spic.picID);
	if(i<0) return;
	w=cobj.spic[i].img.nWidth;
	h=cobj.spic[i].img.nHeight;
	x=wx/2;
	y=wy/2;
	pt1.x=x;
	pt1.y=y;
	pt2.x=x+w;
	pt2.y=y+h;
	CreateNPOINT4dot(spic.pt);
	dbm.AddAObject(atr,&spic,1);
	cobj.SpicAddSubUse(cobj.patternID,1);
	DrawShow();
	ShowObjsum();
};

//添加百分比饼图
void canvas::AddPctPie()
{
	N_PCTPIE  pie;
	N_BASATTR  atr;
	GetAAttr(82,atr);
	pie.type=0;
	strcpy(pie.dev_name,"");
	pie.fcolor=0;
	pie.color1=0xff0000;
	pie.color2=0xffffff;
	pie.did=-1;
	pie.lf=cobj.font;
	pie.curval=10;
	pie.maxv=100;
	pie.zm=1;
	if(CreateNPOINT4dot(pie.pt)) dbm.AddAObject(atr,&pie,1);
	DrawShow();
	ShowObjsum();
	cobj.cursor=0;
}

//改变显示控制矩形
void canvas::ChangeShowRT()
{
	CRect rt=CRect(pt1,pt2);
	rt.NormalizeRect();
	dbm.cpage->head.x1=(short)((rt.left-dbm.dx)/cobj.curzoom);
	dbm.cpage->head.y1=(short)((rt.top-dbm.dy)/cobj.curzoom);
	dbm.cpage->head.x2=(short)((rt.right-dbm.dx)/cobj.curzoom);
	dbm.cpage->head.y2=(short)((rt.bottom-dbm.dy)/cobj.curzoom);
	DrawShow();
	cobj.cursor=0;
}

//产生矩形的4点
bool canvas::CreateNPOINT4dot(DPOINT *pt,int mode)
{
	int a;
	CRect rt=CRect(rpt1,rpt2);
	rt.NormalizeRect();
	if(mode!=0){
	 a=rt.Width()>rt.Height() ? rt.Height():rt.Width();
	 rt.right=rt.left+a;
	 rt.bottom=rt.top+a;
	}
	pt[0].x=(double)((rt.left)/cobj.curzoom);
	pt[0].y=(double)((rt.top)/cobj.curzoom);
	pt[1].x=(double)((rt.right)/cobj.curzoom);
	pt[1].y=(double)((rt.top)/cobj.curzoom);
	pt[2].x=(double)((rt.right)/cobj.curzoom);
	pt[2].y=(double)((rt.bottom)/cobj.curzoom);
	pt[3].x=(double)((rt.left)/cobj.curzoom);
	pt[3].y=(double)((rt.bottom)/cobj.curzoom);
	if((rt.Width()*rt.Height())<25) return false;
	return true;
}

void canvas::MovePic(CPoint point)
{
	int x,y;
	int oldx,oldy,sx,sy;
	if(dbm.dnbz!=1||(xmax>0&&ymax>0)) return;
	oldx=dbm.dx;
	oldy=dbm.dy;
	if(xmax<100)
	{
		x=point.x-pt1.x;
		dbm.dx+=x;
		dbm.dx=dbm.dx>100 ? 100:dbm.dx;
		dbm.dx=dbm.dx<xmax ? xmax:dbm.dx;
	}
	if(ymax<100)
	{
		y=point.y-pt1.y;
		dbm.dy+=y;
		dbm.dy=dbm.dy>100 ? 100:dbm.dy;
		dbm.dy=dbm.dy<ymax ? ymax:dbm.dy;
	}
	sx=oldx-dbm.dx;
	sy=oldy-dbm.dy;
	if(sx!=0||sy!=0){
		ScrollWindow(-sx,-sy);
	}
	pt1=point;
	drawbg=1;
	ComputZCenter();
	cobj.nwin->MoveCvs();	
};

//层面发生改变
void canvas::LayerChange()
{
	ShowObjsum();
	DrawShow();
}

//显示到临时背景上，以便活动对象显示
void canvas::ShowA()
{
	CRect rt=CRect(0,0,wx,wy);
	rt.OffsetRect(-dbm.dx,-dbm.dy);
	dbm.ShowBkgd(mat,rt);
	if(cobj.gshow==1)  dbm.ShowWaterLine(mat.m_hDC,dbm.dx,dbm.dy,CRect(0,0,wx,wy));
	dbm.Showobject(mat,dbm.dx,dbm.dy,rt,1);
}

void canvas::ShowB(HDC hdc,CRect rt)
{
	int w,h;
	CRect rt1=rt;
	rt1.OffsetRect(-dbm.dx,-dbm.dy);
	w=rt1.Width();
	h=rt1.Height();
	CRect rt2=CRect(0,0,w,h);
	mat.BitBltRect(mtp.m_hDC,rt,rt2);
	dbm.Showobject(mtp,-rt.left+dbm.dx,-rt.top+dbm.dy,rt1,2);
	if(dbm.selbz>0&&dbm.movebz==0) dbm.ShowSelectDot(mtp,dbm.dx+rt.left,dbm.dx+rt.top);
	if(dbm.selrgn==1) dbm.ShowRgn(mtp.m_hDC,0,dbm.dx-rt.left,dbm.dy-rt.top);
	mtp.BitBltRect(hdc,rt2,rt);
}

void canvas::OnNormal() 
{
	cobj.cursor=0;
}

void canvas::OnEditCopy() 
{
	if(cobj.edobj==1) cobj.objw->OnEditCopy();
	dbm.CopyToCpyBuf(m_hWnd);
}

void canvas::OnEditPaste() 
{
	if(cobj.edobj==1) cobj.objw->OnEditPaste();
	PasteObj(pt2);
}

//粘贴对象
void canvas::PasteObj(CPoint point)
{
	CDPoint pt;
	pt.SetPOINT(point);
	pt.Offset(-dbm.dx,-dbm.dy);
	pt.ScrPtToAct(cobj.curzoom);
	//察看是否剪贴板里有
	dbm.GetEleFromClipboard(m_hWnd);
	////////////////////////////
	dbm.PasteObject(pt.x,pt.y);
	cobj.cursor=0;
	drawbg=1;
	ReleaseCapture();
	DrawShow();
	ShowObjsum();
}

void canvas::OnAlignDown() 
{
	dbm.AlignBottom();
	DrawShow();
}

void canvas::OnAlignDstx() 
{
	dbm.AlignDstX();
	DrawShow();
}

void canvas::OnAlignDsty() 
{
	dbm.AlignDstY();
	DrawShow();
}

void canvas::OnAlignHg() 
{
	dbm.AlignHeight();
	DrawShow();
}

void canvas::OnAlignLeft() 
{
	dbm.AlignLeft();
	DrawShow();
}

void canvas::OnAlignRight() 
{
	dbm.AlignRight();
	DrawShow();
}

void canvas::OnAlignUp() 
{
	dbm.AlignTop();
	DrawShow();
}

void canvas::OnAlignWd() 
{
	dbm.AlignWidth();
	DrawShow();
}

void canvas::OnEditAttr() 
{
	cobj.edobj=1;
	cobj.cursor=0;
	if(!cobj.tlsw->IsEditActive()) cobj.tlsw->EnableEditTool();
	cobj.objw->EditSelObject();
}

//关联设备
void canvas::OnConnectDev() 
{
	int j,djlh;
	SELECTDEV sd;
	BYTE type,subtype,vl;
	char dev_name[64];
	j=dbm.GetFirstSelObj();
	if(!dbm.clayer->obj[j].GetDevType(type,subtype,vl,dev_name,djlh))
	{
		MessageBox("返回非法的设备类型!","错误",MB_OK|MB_ICONSTOP);
		return;
	}
	if(type!=2){
		MessageBox("不是可编辑的设备类型!","错误",MB_OK|MB_ICONSTOP);
		return;
	}
	//调用数据源设置程序		
	strcpy(sd.dbname,"visualpw");
	strcpy(sd.name,dev_name);
	sd.did=djlh;
	sd.type=2;
	sd.dtype=subtype;
	if(Select_device(sd)){ //NT_SelDev(sd)){
		
		dbm.editbz=1;
		dbm.clayer->obj[j].SetDevSource(sd.name,sd.did);		
	}
}

void canvas::OnEditDev() 
{
	int j,djlh;
	BYTE type,subtype,vl;
	char dev_name[25];
	j=dbm.GetFirstSelObj();
	if(!dbm.clayer->obj[j].GetDevType(type,subtype,vl,dev_name,djlh))
	{
		MessageBox("返回非法的设备类型!","错误",MB_OK|MB_ICONSTOP);
		return;
	}
	if(type!=2){
		MessageBox("不是可编辑的设备类型!","错误",MB_OK|MB_ICONSTOP);
		return;
	}
	//调用数据源设置程序		
//	if(NT_EditDev(djlh,dev_name,1,subtype))	  dbm.clayer->obj[j].SetDevSource(dev_name,djlh);
}

void canvas::OnEditSft() 
{
	int j,type;
	N_SELFCTL *sft;
	N_SRLTEXT *ost;
	j=dbm.GetFirstSelObj();
	type=dbm.clayer->obj[j].attr.type;
	if(type==74){
		ost=(N_SRLTEXT*)dbm.clayer->obj[j].buf;
		EditScrt(ost->text,255,m_hWnd);
	};
	if(type==76){
		sft=(N_SELFCTL*)dbm.clayer->obj[j].buf;
		if(sft->hinst!=NULL&&sft->DfSetParam!=NULL){
		 sft->DfSetParam(sft->style,sft->lkbuf);
		};
	}
	Invalidate();
}

void canvas::OnAboutSft() 
{
	int j,type;
	N_SELFCTL *sft;
	j=dbm.GetFirstSelObj();
	type=dbm.clayer->obj[j].attr.type;
	if(type==76){
		sft=(N_SELFCTL*)dbm.clayer->obj[j].buf;
		if(sft->hinst!=NULL&&sft->DfAbout!=NULL){
		 sft->DfAbout();
		};
	}
	Invalidate();
}

void canvas::OnDbsource() 
{
	int j,type;
	SELRESERVOIR  sr;
	SELDATA_DEV   ad;
	SELSINGLE_DEV sd;
	SELECTPIE     pd;
	N_ANL  *anl;
	N_BAR  *bar;
	N_GIFAML *gml;
	N_ACTOBJ *act;
	N_PIE  *pie;
	N_PCTPIE *ppie;
	N_RESERVOIR *wr;
	N_ZONE   *zn;
	j=dbm.GetFirstSelObj();
	type=dbm.clayer->obj[j].attr.type;
	switch(type){
	case 64: //模拟量显示
		anl=(N_ANL*)dbm.clayer->obj[j].buf;
		strcpy(ad.mdbnm,"visualpw");
		strcpy(ad.name,anl->dev_name);
		ad.did=anl->did;
		ad.dtype=anl->dtype;
		ad.xsmode=anl->xsmode;
		//调用数据源设置程序		
		if(SelAnlSHow(ad)){
			strcpy(anl->dev_name,ad.name);
			anl->did=ad.did;
			anl->dtype=ad.dtype;
			anl->xsmode=ad.xsmode;
		}
		break;
	case 65://水库
		wr=(N_RESERVOIR *)dbm.clayer->obj[j].buf;
		strcpy(sr.name,wr->dev_name);
		sr.id=wr->did;
		if(SelReservoir(sr))
		{
			strcpy(wr->dev_name,sr.name);
			wr->did=sr.id;
		}
		break;
	case 67: //仪表
		SelMeterDbs(dbm.clayer->obj[j]);
		break;
	case 69:  //棒图
		bar=(N_BAR*)dbm.clayer->obj[j].buf;
		strcpy(sd.mdbnm,"visualpw");
		sd.dbs=bar->dsrc;
		//调用数据源设置程序		
		if(SelSingleAnl(sd)) bar->dsrc=sd.dbs;
		break;
	case 73: //动画
		gml=(N_GIFAML*)dbm.clayer->obj[j].buf;
		strcpy(sd.mdbnm,"visualpw");
		sd.dbs=gml->dsrc;
		//调用数据源设置程序		
		if(SelDevSta(sd))	gml->dsrc=sd.dbs;
		break;
	case 80: //活动对象
		act=(N_ACTOBJ*)dbm.clayer->obj[j].buf;
		strcpy(sd.mdbnm,"visualpw");
		sd.dbs=act->dsrc;
		//调用数据源设置程序		
		if(SelSingleAnl(sd))	act->dsrc=sd.dbs;
		break;
	case 70: //网损饼图
		pie=(N_PIE*)dbm.clayer->obj[j].buf;
		strcpy(ad.mdbnm,"visualpw");
		ad.did=pie->did;
		strcpy(ad.name,pie->name);
		//调用数据源设置程序		
		if(SelZone(ad)){
			pie->did=ad.did;
			strcpy(pie->name,ad.name);
			pie->did=ad.did;
		}
		break;
	case 82:   //百分饼图
		ppie=(N_PCTPIE*)dbm.clayer->obj[j].buf;
		strcpy(pd.dbname,"visualpw");
		pd.did=ppie->did;
		pd.dtype=ppie->type;
		strcpy(pd.name,ppie->dev_name);
		if(SelPie(pd)){
			ppie->did=pd.did;
			strcpy(ppie->dev_name,pd.name);
			ppie->type=pd.dtype;
		}
		break;
	case 83:
		zn=(N_ZONE*)dbm.clayer->obj[j].buf;
		strcpy(ad.mdbnm,"visualpw");
		ad.did=zn->did;
		strcpy(ad.name,zn->zone_name);
		//调用数据源设置程序		
		if(SelZone(ad))
		{
			zn->did=ad.did;
			strcpy(zn->zone_name,ad.name);
			zn->did=ad.did;
		}
		break;
	default:
		MessageBox("类型错，不能编辑!","错误",MB_OK|MB_ICONSTOP);
    }
	DrawShow();
}

//添加一个组合图元到桌面
void canvas::Addegpr(BYTE no)
{
	int i,j;
	double w,h,x,y;
	N_BASATTR   atr;
	N_ELEGRPA   elegrp;
	CPoint pt;
	CDRect rt;
	memset(&elegrp,0,sizeof(N_ELEGRPA));
	GetAAttr(66,atr);
	elegrp.egrpid=cobj.patternID;
	j=cobj.GetEGPRecNo(cobj.patternID);
	if(j<0) return;
	strcpy(elegrp.dev_name,"");
	elegrp.did=-1;
	elegrp.showno=no;
	elegrp.type=cobj.egp[j].type;
	elegrp.subtype=cobj.egp[j].subtype;
	elegrp.sitesum=cobj.egp[j].sitesum;
	elegrp.maxp=0;
	elegrp.minp=0;
	elegrp.p=0;
	elegrp.q=0;
	elegrp.genrev=1;
	elegrp.angle=0;
	for(i=0;i<3;i++){
		elegrp.site[i].id=-1;
		elegrp.site[i].vl=cobj.vl;
		elegrp.site[i].srt=cobj.egp[j].srt[i];
		elegrp.rval[i].zt=0;	 //当前状态
		elegrp.rval[i].enable=0; //当前值是否有效
		elegrp.rval[i].ele=1;	 //带电状态
	}	
	rt.SetDRECT(cobj.egp[j].rt1);
	w=rt.Width();
	h=rt.Height();
	x=(wx-w)/2;
	y=(wy-h)/2;
	rt.left=x-dbm.dx;   rt.top=y-dbm.dy;
	rt.right=rt.left+w; rt.bottom=rt.top+h;
	rt.ScrRtToAct(cobj.curzoom);
	rt.NormalizeRect();
	elegrp.pt[0].x=rt.left;elegrp.pt[0].y=rt.top;
	elegrp.pt[1].x=rt.right;elegrp.pt[1].y=rt.top;
	elegrp.pt[2].x=rt.right;elegrp.pt[2].y=rt.bottom;
	elegrp.pt[3].x=rt.left;elegrp.pt[3].y=rt.bottom;
	dbm.AddAObject(atr,&elegrp,1);
	DrawShow();
	ShowObjsum();
};

//添加一个组合仪表到桌面
void canvas::AddegpYb()
{
	int i,j,k,m;
	double w,h,x,y;
	N_BASATTR   atr;
	N_ELEGRPYB  yb;
	N_METER1    *yb1;
	N_METER2    *yb2;
	N_METER3    *yb3;
	N_METER4    *yb4;

	BASE0 *bs;
	CPoint pt;
	CDRect rt;
	memset(&yb,0,sizeof(N_ELEGRPYB));
	GetAAttr(67,atr);
	memset(&yb.dbs,0,sizeof(DBSRC)*6);

	yb.egrpid=(WORD)cobj.patternID;
	j=cobj.GetEGPRecNo(cobj.patternID);
	if(j<0) return;


	bs=cobj.egp[j].bs1;
	m=cobj.egp[j].bsum1;
	for(i=0;i<8;i++){
		yb.dbs[i].did=-1;
		strcpy(yb.dbs[i].name,"未关联");
		yb.pam[i].ptype=0;
	}
	i=0;
	for(k=0;k<m;k++)
	{
		switch(bs[k].attr.type)
		{
		case 32:
			yb1=(N_METER1*)bs[k].buf;
			yb.pam[i].vmin=yb1->Vmin;
			yb.pam[i].vmax=yb1->Vmax;
			memcpy(yb.pam[i].val,yb1->val,4*sizeof(float));
			memcpy(yb.pam[i].color,yb1->cr,sizeof(DWORD)*2);
			yb.pam[i].alarm=yb1->alarm;
			i++;
			break;
		case 33:
			yb2=(N_METER2*)bs[k].buf;
			yb.pam[i].vmin=yb2->Vmin;
			yb.pam[i].vmax=yb2->Vmax;
			memcpy(yb.pam[i].val,yb2->val,4*sizeof(float));
			memcpy(yb.pam[i].color,yb2->cr,sizeof(DWORD)*2);
			yb.pam[i].alarm=yb2->alarm;
			i++;
			break;
		case 34:
			yb3=(N_METER3*)bs[k].buf;
			yb.pam[i].vmin=yb3->Vmin;
			yb.pam[i].vmax=yb3->Vmax;
			memcpy(yb.pam[i].val,yb3->val,4*sizeof(float));
			memcpy(yb.pam[i].color,yb3->cr,sizeof(DWORD)*2);
			yb.pam[i].alarm=yb3->alarm;
			i++;
			break;
		case 35:
			yb4=(N_METER4*)bs[k].buf;
			memcpy(yb.pam[i].color,yb4->ncr,sizeof(DWORD)*2);
			i++;
			break;
		}
		if(i>=8) break;
	}

	yb.dbsum=cobj.egp[j].sitesum;
	rt.SetDRECT(cobj.egp[j].rt1);
	w=rt.Width();
	h=rt.Height();
	x=(wx-w)/2;
	y=(wy-h)/2;
	rt.left=x-dbm.dx;   rt.top=y-dbm.dy;
	rt.right=rt.left+w; rt.bottom=rt.top+h;
	rt.ScrRtToAct(cobj.curzoom);
	rt.NormalizeRect();
	yb.pt[0].x=rt.left;yb.pt[0].y=rt.top;
	yb.pt[1].x=rt.right;yb.pt[1].y=rt.top;
	yb.pt[2].x=rt.right;yb.pt[2].y=rt.bottom;
	yb.pt[3].x=rt.left;yb.pt[3].y=rt.bottom;
	dbm.AddAObject(atr,&yb,1);
	DrawShow();
	ShowObjsum();
};

//支持鼠标滑轮驱动
BOOL canvas::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	int x,y;
	int oldx,oldy,sx,sy;

	if(xmax>0&&ymax>0) return CWnd::OnMouseWheel(nFlags, zDelta, pt);;
	oldx=dbm.dx;
	oldy=dbm.dy;
	if((MK_RBUTTON&nFlags)!=0){
		x=zDelta>0 ? 20:-20;
		y=0;
	}else{
		y=zDelta>0 ? 20:-20;
		x=0;
	}

	x=(int)(x*cobj.curzoom);
	y=(int)(y*cobj.curzoom);
	if(xmax<0){
		dbm.dx+=x;
		dbm.dx=dbm.dx>0 ? 0:dbm.dx;
		dbm.dx=dbm.dx<xmax ? xmax:dbm.dx;
	}
	if(ymax<0){
		dbm.dy+=y;
		dbm.dy=dbm.dy>0 ? 0:dbm.dy;
		dbm.dy=dbm.dy<ymax ? ymax:dbm.dy;
	}
	sx=oldx-dbm.dx;
	sy=oldy-dbm.dy;
	if(sx!=0||sy!=0){
		ScrollWindow(-sx,-sy);
	}
	pt1=pt;
	drawbg=1;
	ComputZCenter();
	cobj.nwin->MoveCvs();
	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}


void canvas::OnGototop() 
{
	dbm.SelObjToTOP();
	drawbg=1;
	DrawShow();
}

void canvas::OnGotobuttom() 
{
	dbm.SelObjToButtom();
	drawbg=1;
	DrawShow();
}

void canvas::OnCurnml() 
{
	DrawChange(0);
}

//母线选择关联的组合图元
void canvas::OnSelelebus() 
{
	int j;
	WORD id;
	N_BUS *bus;
	j=dbm.GetFirstSelObj();
	if(j<0) return;
	SelEDlg dlg;
	if(dlg.DoModal()!=IDOK) return;
	id=dlg.selid;
	if(id<0) return;
	bus=(N_BUS*)dbm.clayer->obj[j].buf;
	bus->eid=(WORD)id;
	bus->type=3;
	dbm.editbz=1;
	DrawShow();
}


void canvas::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CPoint pt;
	if(nChar>36&&nChar<41)
	{
		GetCursorPos(&pt);
		switch(nChar)
		{
		case 37:
			pt.x--;
			break;
		case 38:
			pt.y--;
			break;
		case 39:
			pt.x++;
			break;
		case 40:
			pt.y++;
			break;
		}
		SetCursorPos(pt.x,pt.y);
	}
	if(nChar==46) GetParent()->SendMessage(WM_COMMAND,ID_EDIT_CUT);
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

//选择仪表的数据源
void canvas::SelMeterDbs(BASE0 &bs)
{
	N_ELEGRPYB *yb;
	CCfgMeter dlg;
	yb=(N_ELEGRPYB*)bs.buf;
	dlg.tmp=yb[0];
	if(dlg.DoModal()==IDOK)
	{
		yb[0]=dlg.tmp;
	}
}

void canvas::OnAddlinedot() 
{
	dbm.AddLineDot(dbm.mpoint);
	DrawShow();
}

void canvas::OnSublinedot() 
{
	dbm.SubLineDot(dbm.mpoint);
	DrawShow();
}

void canvas::OnZmin() 
{
	double oldz;
	CPoint pt;
	if(dbm.dnbz==1||tptsum!=0) return;
	oldz=cobj.curzoom;
	//首先计算中心点
	vx=(-dbm.dx+dbm.mpoint.x)/cobj.curzoom;
	vy=(-dbm.dy+dbm.mpoint.y)/cobj.curzoom;
	dbm.ZoomPage(1);
	if(oldz!=cobj.curzoom) ZoomChange();
	dbm.mpoint.x=wx/2;
	dbm.mpoint.y=wy/2;
	pt=dbm.mpoint;
	ClientToScreen(&pt);
	SetCursorPos(pt.x,pt.y);
}

void canvas::OnZmout() 
{
	double oldz;
	CPoint pt;
	if(dbm.dnbz==1||tptsum!=0) return;
	oldz=cobj.curzoom;
	//首先计算中心点
	vx=(-dbm.dx+dbm.mpoint.x)/cobj.curzoom;
	vy=(-dbm.dy+dbm.mpoint.y)/cobj.curzoom;
	dbm.ZoomPage(2);
	if(oldz!=cobj.curzoom) ZoomChange();
	dbm.mpoint.x=wx/2;
	dbm.mpoint.y=wy/2;
	pt=dbm.mpoint;
	ClientToScreen(&pt);
	SetCursorPos(pt.x,pt.y);
}


//判断是否应该自动移动屏幕
void canvas::ChkMousemove(CPoint point)
{
	int oldx,oldy,sx,sy;

	switch(cobj.cursor)
	{
		case 0:case 102:case 104:
		return;
	}
	if(tptsum==0&&dbm.dnbz==0) return;
	if(point.x>5&&point.y>5&&point.x<(wx-10)&&point.y<(wy-10)) return;
	oldx=dbm.dx;
	oldy=dbm.dy;
	
	if(xmax<0)
	{
		if(point.x<10) //在左边
		{
			dbm.dx+=30;
			dbm.dx=dbm.dx>0 ? 0:dbm.dx;
		}

		if(point.x>(wx-10)) //在右边
		{
			dbm.dx-=30;
			dbm.dx=dbm.dx<xmax ? xmax:dbm.dx;
		}
	}
	if(ymax<0)
	{
		if(point.y<10) //在上边
		{
			dbm.dy+=30;
			dbm.dy=dbm.dy>0 ? 0:dbm.dy;
		}

		if(point.y>(wy-10)) //在右边
		{
			dbm.dy-=30;
			dbm.dy=dbm.dy<ymax ? ymax:dbm.dy;
		}
	}
	sx=oldx-dbm.dx;
	sy=oldy-dbm.dy;
	if(sx!=0||sy!=0)
	{
		if(tptsum!=0) oldpt=tpt[tptsum-1];
		oldrt.SetRectEmpty();
		DrawShow();
		drawbg=1;
	}else return;
	ComputZCenter();
	cobj.nwin->MoveCvs();
}

void canvas::OnAvccfg() 
{
	N_ELEGRPA *egp;
	int j,subtype;
	if(dbm.selbz!=1) return;
	j=dbm.GetFirstSelObj();
	if(dbm.clayer->obj[j].attr.type!=66) return;
	egp=(N_ELEGRPA*)dbm.clayer->obj[j].buf;
	subtype=egp->subtype;
	if(subtype!=7&&subtype!=8&&subtype!=1) return;
	if(subtype==7||subtype==8) 	subtype-=6;
	if(subtype==1) subtype=3;
	OpenPropertyDlg(egp->did,subtype);
}


void canvas::OnDbxtoline() 
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
	if(AddDLine(dbx->ptsum,dbx->pt)) dbm.DelSelObj();
}

void canvas::OnDbxtocl() 
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
	if(AddCLine(dbx->ptsum,dbx->pt)) dbm.DelSelObj();
}
