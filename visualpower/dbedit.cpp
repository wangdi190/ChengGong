// dbedit.cpp : implementation file
//

#include "stdafx.h"
#include "dbedit.h"
#include "jhsyslibl.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// dbedit

dbedit::dbedit()
{
	curfld=0;
	dnbz=0;
	dx=0;dy=0;
	cursor=0;				//当前光标
	field_size=0;			//记录域字节大小
	field_count=0;			//域总数
	dfield=new dFIELD[128];	//最大128个域
	fwd=new WORD[128];			//记录域坐标
	data=NULL;       
	img=NULL;  

	font.CreateFont(14, 7,0,0,400,0,0,0,1,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH,"宋体" );
	fcolor=GetSysColor(COLOR_3DFACE);
	hcur=LoadCursor(NULL,IDC_SIZEWE);
	pen.CreatePen(PS_SOLID,1,RGB(0x7f,0x7f,0x7f));
	cursor=0;
}

dbedit::~dbedit()
{
	if(dfield!=NULL) delete dfield;
	if(fwd!=NULL)    delete fwd;
	font.DeleteObject();
	DeleteObject(hcur);
	pen.DeleteObject();
}


BEGIN_MESSAGE_MAP(dbedit, CWnd)
	//{{AFX_MSG_MAP(dbedit)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// dbedit message handlers

BOOL dbedit::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), NULL, NULL);
	return TRUE;
}

int dbedit::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}

LRESULT dbedit::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	return CWnd::WindowProc(message, wParam, lParam);
}


void dbedit::SetInitPara(char *buff, int rsize, int recmax,int recused) //设置基本参数
{
	reset();
	data=buff;
	field_size=rsize; 
	maxr=recmax;
	recu=recused;
	record_count=recused;
	SetScroll();
}
//所有项目复位
void dbedit::reset()
{
	img=NULL;  
	field_size=0;    //记录域字节大小
	field_count=0;   //域总数
	record_count=0;  //记录数
	data=NULL;       //数据库指针
	cursor=0;

	dx=0;
	dy=0;
	dnbz=0;
	curfld=0;
}


void dbedit::OnPaint() 
{
	CPaintDC dc(this);
	ShowFrame(dc);
}

//显示框架
void dbedit::ShowFrame(CDC &dc)
{
	int i,j,h;
	DWORD color;
	dc.SelectObject(&font);
	if(maxr<=0)
	{
		dc.FillSolidRect(CRect(0,0,wx,wy),0xffffff);
		return;
	}
	dc.FillSolidRect(CRect(0,0,wx,wy),0xffffff);
	dc.FillSolidRect(CRect(0,0,60,23),fcolor);
	for(i=0;i<field_count;i++)	DrawItemTitle(dc,i);
	for(i=dy;i<record_count;i++)
	{
		if((i-dy)>maxyl) break;
		DrawLeftTitle(dc,i);
	}
	for(i=dy;i<record_count;i++)
	{
		if((i-dy)>maxyl) break;
		color=GetColor(i);
		for(j=dx;j<field_count;j++)	 ShowItem(dc,j,i,color);
	}
	dc.Draw3dRect(CRect(0,0,60,23),0xffffff,0x7f7f7f);
	h=record_count-dy+1;
	if(h<maxyl)
	{
		h=22+h*22;
		dc.FillSolidRect(CRect(0,h,60,wy),0xffffff);
	}
	if(record_count>0) DrawLine(dc.m_hDC,0,23,60,23,0x7f7f7f);
}

void dbedit::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	wx=cx;
	wy=cy;
	maxyl=(wy-23)/22+2;
	SetScroll();
}

int dbedit::AddItemType(char *name,BYTE type,BYTE strmax,BYTE edit,char image,char lindex,BYTE xs,int twidth)
{
	int len,m;
	if(field_count>=128) return 0;
	len=strlen(name);
	len=len>63 ? 63:len;   //最大63字符限制
	dfield[field_count].edit=edit;
	dfield[field_count].image=image;
	dfield[field_count].strmax=strmax;
	dfield[field_count].type=type;
	dfield[field_count].xs=xs;
	strncpy(dfield[field_count].fieldname,name,len);
	dfield[field_count].fieldname[len]=0;
	m=image>=0 ? 26:0;
	dfield[field_count].width=twidth*9+m; //计算宽度
	dfield[field_count].index=lindex;
	field_count++;
	ComputWidth();     //计算一次宽度
	SetScroll();
	return field_count;//返回当前的域个数
}
void dbedit::SetImageList(CImageList *imglist) //设置图形
{
	img=imglist;
}

void dbedit::ComputWidth()  //计算域的宽度
{
	int i;
	int w=0;
	for(i=0;i<field_count;i++)
	{
	   fwd[i]=w;
	   w+=dfield[i].width;
	   fwd[i+1]=w;
	 };
}

//画子项的标题
void dbedit::DrawItemTitle(CDC &dc, int j)
{
	char nm[128];
	CRect rt,rt1;
	int w,x0,x1,ino,w0;
	rt.top=0;
	rt.bottom=23;
	w=dfield[j].width;
	x0=fwd[dx];
	x1=fwd[j];
	rt.left=60+x1-x0;
	rt.right=rt.left+w;
	if(rt.left>wx) return;

	ino=dfield[j].image;
	if(ino>=0) w0=16;else w0=0;
	dc.FillSolidRect(rt,fcolor);
	dc.SetBkColor(fcolor);
	dc.SetTextColor(0);
	strcpy(nm,dfield[j].fieldname);
	rt1=rt;
	rt.left+=w0;
	if(ino>=0) img->Draw(&dc,ino,CPoint(rt1.left+2,rt.top+4),ILD_NORMAL);
	dc.DrawText(dfield[j].fieldname,rt,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	dc.Draw3dRect(rt1,0xffffff,0x7f7f7f);
}

//返回数据项的矩形位置
CRect dbedit::GetItenRect(int x, int y)
{
	int j,x0,x1,w;
	CRect rt;
	if(x<dx||y<dy) return CRect(0,0,0,0);
	w=dfield[x].width;
	x0=fwd[dx];
	x1=fwd[x];
	j=y-dy;
	rt.top=23+j*22;
	rt.bottom=rt.top+23;
	rt.left=60+x1-x0;
	rt.right=rt.left+w+1;
	return rt;
}

void dbedit::GetFieldString(int y, int field, char *str) //返回串
{
	int    len,recno,n;
	char   mon[12],day[12],hor[12],min[12],sec[12];
	char   *lp;
	int    offseta,offsetb;
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
	strcpy(str,"[error]");
	recno=y;
	sprintf(str,"%d %d",field,y);
	if(recno>=record_count||field>=field_count) return;
	//计算偏移量
	offseta=recno*field_size;
	offsetb=GetFieldOffset(field);
	lp=data+offseta+offsetb;
	n=-1;
	switch(dfield[field].type)
	{
	case EDIT_FLOAT:
		flt=(float*)lp;
		n=(int)flt[0];
		GetDoubleStr((double)flt[0],str,dfield[field].xs);
		break;
    case EDIT_STR:
		len=strlen(lp);
		len=len>255 ? 255:len;
		strcpy(str,lp);
		break;
	case EDIT_CHAR:
        ch=(char*)lp;
		n=ch[0];
		sprintf(str,"%d",ch[0]);
		break;
	case EDIT_SHORT:
		sh=(short*)lp;
		n=sh[0];
		sprintf(str,"%d",sh[0]);
		break;
	case EDIT_INT:
        in=(int*)lp;
		n=in[0];
		sprintf(str,"%d",in[0]);
		break;
	case EDIT_BYTE:
		by=(BYTE*)lp;
		n=by[0];
		sprintf(str,"%u",by[0]);
		break;
	case EDIT_WORD:
		wd=(WORD*)lp;
		n=wd[0];
		sprintf(str,"%u",wd[0]);
		break;
	case EDIT_DWORD:
		dw=(DWORD*)lp;
		n=(int)dw[0];
		sprintf(str,"%u",dw[0]);
		break;
	case EDIT_DOUBLE:
		dbl=(double*)lp;
		n=(int)dbl[0];
		sprintf(str,"%f",dbl[0]);
		//GetDoubleStr(dbl[0],str,dfield[field].xs);
		break;
	case EDIT_DTIME:
	    ctm=(CTime*)lp;
		IntTostring(hor,ctm->GetHour(),2);
		IntTostring(min,ctm->GetMinute(),2);
		IntTostring(sec,ctm->GetSecond(),2);
		IntTostring(mon,ctm->GetMonth(),2);
		IntTostring(day,ctm->GetDay(),2);
		sprintf(str,"%d-%s-%s %s:%s:%s",ctm->GetYear(),mon,
			day,hor,min,sec);
		break;
	case EDIT_DATE:
	    ctm=(CTime*)lp;
		IntTostring(mon,ctm->GetMonth(),2);
		IntTostring(day,ctm->GetDay(),2);
		sprintf(str,"%2d-%s-%s",ctm->GetYear(),mon,day);
		break;
	case EDIT_TIME:
	    ctm=(CTime*)lp;
		IntTostring(hor,ctm->GetHour(),2);
		IntTostring(min,ctm->GetMinute(),2);
		IntTostring(sec,ctm->GetSecond(),2);
		sprintf(str,"%s:%s:%s",hor,min,sec);
		break;
	case EDIT_BOOL:
	    BOL=(BOOL*)lp;
		n=BOL[0];
		sprintf(str,"%d",BOL[0]);
		break;
	case EDIT_bool:
	    bol=(bool*)lp;
		n=bol[0];
		sprintf(str,"%d",bol[0]);
		break;
		};
}

//返回行颜色
DWORD  dbedit::GetColor(int y)
{
	char *lp;
	DWORD *color;
	int    offseta;
	offseta=(y+1)*field_size;
	lp=data+offseta-4;
	color=(DWORD*)lp;
	return *color;
}

int dbedit::GetFieldOffset(int field) //返回域偏移量
{
	int i,offset=0;
	for(i=0;i<field;i++) offset+=dfield[i].strmax;
	return offset;
}

void dbedit::IntTostring(char *str, int val, int w)
{
	int i,n,len;
	char p[100];
	char rtn[256];
	sprintf(p,"%d",val);
	len=strlen(p);
	if(len<w){
	 n=w-len;
	 strcpy(rtn,"");
	 for(i=0;i<n;i++) strcat(rtn,"0");
	 strcat(rtn,p);
	}else{
	 strcpy(rtn,p);	
	};
	strcpy(str,rtn);
}
//显示数据项
void dbedit::ShowItem(CDC &dc, int x, int y,DWORD color)
{
	char temp[260];
	CRect rt,rt1;
	rt=GetItenRect(x,y);
	GetFieldString(y,x,temp);
	dc.SetBkColor(0xffffff);
	dc.SetTextColor(color);
	rt1=rt;
	rt.top+=3;
	rt.right-=3;
	dc.SelectObject(&font);
	dc.DrawText(temp,rt,DT_RIGHT|DT_VCENTER);
	dc.Draw3dRect(rt1,0xc0c0c0,0xc0c0c0);
}


//返回当前的光标
void dbedit::GetCursor(CPoint point)
{
	int i,w0,w1;
	CRect rt;
	rt.top=0;
	rt.bottom=22;
	w0=fwd[dx];
	for(i=dx;i<field_count;i++)
	{
		w1=fwd[i]-w0+dfield[i].width;
		rt.left=57+w1;
		rt.right=63+w1;
		if(rt.PtInRect(point)){
			cursor=1;
			curfld=i;
			return;
		}
	}
	cursor=0;
	return;
}

BOOL dbedit::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if(nHitTest == HTCLIENT)
	 {
		if(cursor==1)
		{
		   SetCursor(hcur);
		   return false;
		};
      }
	
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

void dbedit::OnMouseMove(UINT nFlags, CPoint point) 
{
	
	if(dnbz==0) GetCursor(point);
	if(cursor==1&&dnbz==1)
	{
		drawxorline(oldx);
		drawxorline(point.x);
	}
	CWnd::OnMouseMove(nFlags, point);
}

void dbedit::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CClientDC dc(this);
	dnbz=1;
	SetCapture();
	switch(cursor){
	case 0:
		break;
	case 1:
		oldx=-1;
		oldp1=point;
		drawxorline(point.x);
		break;
	}
	CWnd::OnLButtonDown(nFlags, point);
}

void dbedit::OnLButtonUp(UINT nFlags, CPoint point) 
{
	int w,w1;
	ReleaseCapture();
	if(cursor==1){
		drawxorline(oldx);
		w=point.x-oldp1.x;
		w1=dfield[curfld].width;
		w1=w1+w;
		if(w1<20) w1=20;
		dfield[curfld].width=w1;
		ComputWidth();
		Invalidate();
	}
	cursor=0;
	dnbz=0;
	CWnd::OnLButtonUp(nFlags, point);
}

void dbedit::drawxorline(int x)  //移动竖条时画线
{
	CClientDC dc(this);
	dc.SetROP2(R2_XORPEN);
	dc.SelectObject(&pen);
	dc.MoveTo(x,0);
	dc.LineTo(x,wy);
	oldx=x;
}

void dbedit::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CRect rt;
    int n,sy,ody;	
	sy=record_count-maxyl/2;
	ody=dy;
	switch(nSBCode)
	{
	case SB_LINEDOWN: 
		 dy=dy<sy-1 ? dy+1:sy;
		 break;
	case SB_LINEUP:
		 dy=dy>0 ? dy-1:0;
		 break;
	case SB_PAGEDOWN:
		 dy=dy<sy-maxyl ? dy+maxyl:sy;
		 break;
	case SB_PAGEUP:
		 dy=dy>maxyl ? dy-maxyl:0;
		 break;
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:
		dy=nPos;break;
	};
	n=ody-dy;
	SetScrollPos(SB_VERT,dy);
	if(n!=0)	ScrollWindow(0,n*22,CRect(0,23,wx,wy),CRect(0,23,wx,wy));
	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

void dbedit::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CRect rt;
    int n,sx,odx,h;	
	sx=field_count-1;
	odx=dx;
	switch(nSBCode)
	{
	case SB_LINERIGHT: 
		 dx=dx<sx-1 ? dx+1:sx;break;
	case SB_LINELEFT:
		 dx=dx>0 ? dx-1:0;break;
    case SB_PAGEDOWN:
		 dx=dx<sx-3 ? dx+3:sx;
		 break;
	case SB_PAGEUP:
		 dx=dx>3 ?  dx-3:0;
		 break;
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:
		dx=nPos;break;
	};
	n=fwd[odx]-fwd[dx];
	SetScrollPos(SB_HORZ,dx);
	if(n!=0)
	{
		h=record_count-dy;
		h=h*22+22;
		h=h>wy ? wy:h;
		ScrollWindow(n,0,CRect(60,0,wx,h),CRect(60,0,wx,h));
	};	
	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}
//设置滚动杆
void dbedit::SetScroll()
{
	int sx,sy;
	sx=field_count-1;
	sy=record_count-(maxyl/2);
	SetScrollRange(SB_HORZ,0,sx);
	SetScrollRange(SB_VERT,0,sy);
	SetScrollPos(SB_HORZ,dx);
	SetScrollPos(SB_HORZ,dy);
}
//显示左边方框
void dbedit::DrawLeftTitle(CDC&dc,int y)
{
	int j,y1;
	char p[100];
	CRect rt;
	y1=24;
	j=y-dy;
	rt.left=0;
	rt.right=60;
	rt.top=y1+j*22;
	rt.bottom=46+j*22;
	dc.FillSolidRect(rt,fcolor);
	dc.Draw3dRect(rt,0xffffff,0x7f7f7f);
	dc.SetBkColor(fcolor);
	dc.SetTextColor(0);
	sprintf(p,"%d",y);
	dc.DrawText(p,rt,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	
}

//已使用的记录数发生变化
void dbedit::UsedChanged(int recused)
{
	record_count=recused;
	SetScroll();
	Invalidate();
}


//返回编辑位置
bool dbedit::GetEditPos(CPoint point, int &xd, int &yd)
{
	int i,x,x1,x2,y,maxx;
	if(field_count<=0)   return false;
	y=(point.y-22)/22;
	y+=dy;
	if(y>=record_count) return false;
	maxx=fwd[field_count-1]-fwd[dx]+60+dfield[field_count-1].width;;
	if(point.x<60||point.x>maxx) return false;
	x=-1;
	for(i=dx;i<field_count;i++)
	{
		x1=fwd[i]-fwd[dx]+60;
		x2=x1+dfield[i].width;
		if(point.x>x1&&point.x<x2){
			x=i;
			break;
		}
	}
	if(x<0) return false;
	xd=x;
	yd=y;
	return true;
}



//画一条直线
void dbedit::DrawLine(HDC hdc, int x1, int y1, int x2, int y2, DWORD color)
{
	HPEN oldpen,pen1;
	pen1=CreatePen(PS_SOLID,1,color);
	oldpen=(HPEN)SelectObject(hdc,pen1);
	MoveToEx(hdc,x1,y1,NULL);
	LineTo(hdc,x2,y2);
	SelectObject(hdc,oldpen);
	DeleteObject(pen1);
}

