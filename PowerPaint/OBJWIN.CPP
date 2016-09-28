// Objwin.cpp : implementation file
//

#include "stdafx.h"
#include "powerpaint.h"
#include "Objwin.h"
#include "textdlg.h"
#include "Scrtdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern char *ftr[];
BOOL GetImgFile(char *filename,char *filter,HWND hWndParent);

//显示打开DLL文件对话框
BOOL GetDllName(char *name,HWND hWndParent)
{
    char filter[32];
	char filename[128];
	int  len;
	strcpy(filter,"动态连接库(*.DLL)|*.DLL");
	CFileDialog  fodlg(false,NULL,NULL,OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,filter,CWnd::FromHandle(hWndParent));
	if(fodlg.DoModal()==IDOK){
	  strcpy(filename,fodlg.GetPathName());
	  len=strlen(filename);
	  if(len>63){
		MessageBox(0,"DLL文件名太长,超出定义!","提示",MB_OK);
		return false;
	  }else{
		strcpy(name,filename);
		return true;
	  };
	 }
	return false;
}

bool EditText(char *str,int n,HWND hWndParent)
{
	TextDlg dlg(str,n,CWnd::FromHandle(hWndParent));
	if (dlg.DoModal() != IDOK) return FALSE;
	return TRUE;

}

bool EditScrt(char *str,int n,HWND hWndParent)
{
	ScrtDlg dlg(str,n,CWnd::FromHandle(hWndParent));
	if (dlg.DoModal() != IDOK) return FALSE;
	return TRUE;

}

/////////////////////////////////////////////////////////////////////////////
// Objwin

Objwin::Objwin()
{
	font.CreateFont(16, 8,0,0,400,0,0,0,1,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH,"宋体" );
	font1.CreateFont(12,6,0,0,400,0,0,0,1,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH,"宋体" );
	pen.CreatePen(PS_SOLID,1,RGB(0x7f,0x7f,0x7f));
	brush.CreateSolidBrush(RGB(0xff,0xff,0xf0));
	brush1.CreateSolidBrush(RGB(0xff,0xff,0xff));
	cursor=0;
	dnbz=0;
	editzt=0;
	limg.Create(IDB_BITMAP1,16,0,RGB(255,0,255));
	oldrt=CRect(0,0,1,1);
}

Objwin::~Objwin()
{
   font.DeleteObject();
   font1.DeleteObject();
   pen.DeleteObject();
   brush.DeleteObject();
   brush1.DeleteObject();
}


BEGIN_MESSAGE_MAP(Objwin, CWnd)
	//{{AFX_MSG_MAP(Objwin)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_VSCROLL()
	ON_WM_SIZE()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Objwin message handlers
BOOL Objwin::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;
	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW),HBRUSH(COLOR_WINDOW+1), NULL);
	return TRUE;
}

int Objwin::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	ed.Create(WS_CHILD|WS_VISIBLE|ES_LEFT|ES_AUTOHSCROLL|ES_NOHIDESEL,CRect(10,10,100,30),this,100);
	ed.ShowWindow(SW_HIDE);
	ed.SetFont(&font,true);
	li.Create(WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST|WS_VSCROLL,CRect(0,0,1,1),this,101);
	li.ShowWindow(SW_HIDE);
	li.SetFont(&font,true);
	ReSet();	//所有项目清零
	return 0;
}

void Objwin::OnPaint() 
{
	CPaintDC dc(this); 
	ShowTitle(dc);
}





void Objwin::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CRect rt;
    int n,sy,ody;	
	sy=esum-maxy;
	ody=dy;
	ed.ShowWindow(SW_HIDE);
	li.ShowWindow(SW_HIDE);
    switch(nSBCode){
	case SB_LINEDOWN:  dy=dy<sy-1 ? dy+1:sy;	break;
	case SB_LINEUP:    dy=dy>0 ? dy-1:0;		break;
	case SB_PAGEUP:    dy=dy>=4   ? dy-4:0;		break; 	
	case SB_PAGEDOWN:  dy=dy<sy-4 ? dy+4:sy;	break;
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:	dy=nPos;			break;
	};
	n=ody-dy;
	SetScrollPos(SB_VERT,dy);
	if(n!=0){
		rt.left=1;rt.top=1;rt.bottom=maxy*24+1;rt.right=wx-1;
		ScrollWindow(0,n*24,&rt,&rt);
	};
	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

void Objwin::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	wx=cx;wy=cy;
	SetScrollBar();
}

void Objwin::ReSet()
{
	int i;
	char p[100];
	ed.ShowWindow(SW_HIDE);
	li.ShowWindow(SW_HIDE);
	for(i=0;i<MAXITEM;i++){
      edb[i].addr=NULL;
	  edb[i].type=0;
	  edb[i].strmax=1;
	  edb[i].canedit=0;
	  edb[i].index=-1;
	};
	for(i=0;i<MAXENM;i++){
	  sprintf(p,"第%d行",i);
	  strcpy(enm[i].name,p);
	  enm[i].img=i%5;
	};

	strcpy(title,"无标题");
   	esum=0;
	tsum=0; 
	nmw=80;
	dx=0;
	dy=0;
	maxy=1;
	tenable=0;

}

void Objwin::draw3dtitle(CDC&dc,CRect &rt, char *str,UINT style)
{
    CRect r;
	int dh;
	dc.Draw3dRect(rt,0x7f7f7f,0x7f7f7f);
	r=rt;
	dh=(r.bottom-r.top-16)/2;
	r.top+=dh;r.bottom-=dh;r.left+=22;r.right-=2;
	dc.DrawText(str,strlen(str),r,style);
}

void Objwin::ShowTitle(CDC &dc)
{
	int i,j,a;
	int cx,cy;
	CRect rt;
	cx=wx;
	cy=wy;
	dc.SetBkMode(TRANSPARENT);
	dc.SelectObject(&font);		
	dc.SetTextColor(0);
	rt.right=nmw+1;
	a=0;
	if(tenable==1){
	 dc.SelectObject(&font1);
	 dc.SetTextColor(0);
	 dc.FillSolidRect(CRect(0,0,wx,16),0xc0c0c0);
	 a=16;
	 dc.DrawText(title,strlen(title),CRect(2,2,wx-10,16),DT_LEFT);
	 rt=CRect(wx-15,2,wx-2,15);
	}
	dc.SelectObject(&font);
	dc.SetTextColor(0);
	for(i=0;i<maxy;i++){
      j=i+dy;
	  if(j>=esum) break;
	  rt.left=0;
      rt.top=a+i*24;rt.bottom=rt.top+24+1;
	  dc.FillSolidRect(rt,0xf0ffff);
	  if(enm[j].img>=0)	   limg.Draw(&dc,enm[j].img,CPoint(rt.left+4,rt.top+4),ILD_NORMAL);
	  draw3dtitle(dc,rt,enm[j].name,DT_LEFT);
	};
 	dc.SetBkColor(RGB(0xff,0xff,0xff));
	dc.SelectObject(&pen);
    for(i=dy;i<esum;i++){
      if((i-dy)>=maxy) break;
	   ShowItem(dc,i);
	}
}
int Objwin::Getmaxwidth()   //返回总宽度
{
    return 0 ;
}

int Objwin::Getmaxheigh(){	 //返回总高度
	return esum*24;
};


bool Objwin::Geteditrect(int y,CRect&rt) //返回X，Y所在的矩形
{
	int a;
    if(y>=esum) return false;
	if(tenable==1) a=16;else a=0;
    rt.left=nmw;rt.right=wx;
    rt.top=(y-dy)*24+a;
    rt.bottom=rt.top+24;
    return true;
}

void Objwin::ShowItem(CDC&dc,int y)      //显示X，Y项 
{
    CRect rt;
	int edbz,type,w;
	char temp[260];
	DWORD *dw;
	if(Geteditrect(y,rt)==0) return;
	type=edb[y].type;
	switch(type){
	case EDIT_COLOR:
	 if(edb[y].addr==NULL) break;
	 dw=(DWORD*)edb[y].addr;
	 rt.bottom+=1;
	 dc.Rectangle(rt);
	 rt.left+=3;rt.top+=4;
	 w=rt.right-rt.left;
	 w=w>32 ? 32:w;
	 rt.right=rt.left+w;
	 rt.bottom-=4;
	 dc.FillSolidRect(&rt,dw[0]);
	 dc.Draw3dRect(&rt,0,0);
 	 break;
	default:
	  Geteditstring(y,temp,edbz);
	  rt.right+=0;rt.bottom+=1;
	  dc.SelectObject(&brush);
	  if(edbz==0){
	    dc.SetTextColor(RGB(0x00,0x00,0x7f));
	    dc.SelectObject(&brush);
	  }else{
	   dc.SetTextColor(RGB(0x00,0x00,0x00));	
	   dc.SelectObject(&brush1);
		};
	  dc.Rectangle(rt);
	  rt.left+=2;rt.top+=4;rt.right-=3;rt.bottom-=3;
	  dc.DrawText(temp,strlen(temp),rt,DT_LEFT);
	return;
	}
}


void Objwin::Geteditstring(int y,char *str,int&caned)//返回x,y位置显示的字符串
{
    int    i,n;
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
	LOGFONT *lft;
	int   len;
	strcpy(str,"null");
	if(y>=esum) return ;
	i=edb[y].index;
	n=-1;
	if(edb[y].addr==NULL) return ;
	caned=edb[y].canedit; //能否编辑
    switch(edb[y].type){
	case EDIT_FLOAT:
		flt=(float*)edb[y].addr;
		n=(int)flt[0];
        sprintf(str,"%2.2f",flt[0]);
		break;
    case EDIT_STR:
		len=strlen(edb[y].addr);
		len=len>255 ? 255:len;
		strcpy(str,edb[y].addr);
		break;
	case EDIT_CHAR:
        ch=(char*)edb[y].addr;
		n=ch[0];
		sprintf(str,"%d",ch[0]);
		break;
	case EDIT_SHORT:
		sh=(short*)edb[y].addr;
		n=sh[0];
		sprintf(str,"%d",sh[0]);
		break;
	case EDIT_INT:
        in=(int*)edb[y].addr;
		n=in[0];
		sprintf(str,"%d",in[0]);
		break;
	case EDIT_BYTE:
		by=(BYTE*)edb[y].addr;
		n=by[0];
		sprintf(str,"%u",by[0]);
		break;
	case EDIT_WORD:
		wd=(WORD*)edb[y].addr;
		n=wd[0];
		sprintf(str,"%u",wd[0]);
		break;
	case EDIT_DWORD:
		dw=(DWORD*)edb[y].addr;
		n=(int)dw[0];
		sprintf(str,"%u",dw[0]);
		break;
	case EDIT_DOUBLE:
		dbl=(double*)edb[y].addr;
		n=(int)dbl[0];
		sprintf(str,"%4.2f",dbl[0]);
		break;
	case EDIT_DTIME:
	    ctm=(CTime*)edb[y].addr;
		sprintf(str,"%d-%2d-%2d %d:%d:%d",ctm->GetYear(),ctm->GetMonth(),
			ctm->GetDay(),ctm->GetHour(),ctm->GetMinute(),ctm->GetSecond());
		break;
	case EDIT_DATE:
	    ctm=(CTime*)edb[y].addr;
		sprintf(str,"%d-%2d-%2d",ctm->GetYear(),ctm->GetMonth(),
			ctm->GetDay());
		break;
	case EDIT_TIME:
	    ctm=(CTime*)edb[y].addr;
		sprintf(str,"%d:%d:%d",ctm->GetHour(),ctm->GetMinute(),ctm->GetSecond());
		break;
	case EDIT_BOOL:
	    BOL=(BOOL*)edb[y].addr;
		n=BOL[0];
		sprintf(str,"%d",BOL[0]);
		break;
	case EDIT_bool:
	    bol=(bool*)edb[y].addr;
		n=bol[0];
		sprintf(str,"%d",bol[0]);
		break;
	case EDIT_FILE: case EDIT_DLL:
		len=strlen(edb[y].addr);
		len=len>255 ? 255:len;
		strcpy(str,edb[y].addr);
		break;
	case EDIT_FONT:
		lft=(LOGFONT*)edb[y].addr;
		i=lft->lfHeight;
		i=i>0 ? i:-i;
		sprintf(str,"%s  %d",lft->lfFaceName,i);
		break;
	case EDIT_GIF:case EDIT_AVI:case EDIT_SWF:
		len=strlen(edb[y].addr);
		len=len>255 ? 255:len;
		strcpy(str,edb[y].addr);
		break;
		};

	if(i>=0&&i<lsum&&n>=0){
		 GetItemString(edb[y].index,n,str);
		}
}



void Objwin::SetScrollBar()  //设置滚动杆滚动范围
{
    int sy,omy;
	omy=maxy;
	maxy=wy/24;
	sy=esum-maxy;
	sy=sy<0 ? 0:sy;
	SetScrollRange(SB_VERT,0,sy);
}


int Objwin::IsFunctArea(CPoint point)  //判断是否是功能区
{
    CRect rt;
	rt=CRect(6,6,28,28);
	if(rt.PtInRect(point)) return 0;  //按下刷新键
	rt=CRect(30,6,52,28);
	if(rt.PtInRect(point)) return 1;  //按下恢复键
	rt=CRect(wx-20,4,wx-6,18);
	if(rt.PtInRect(point)) return 2;  //按下关闭件
	return -1;
}


void Objwin::editoperate(CPoint point)//编辑操作
{
    CRect rt;
	int x,y,i,j,w,agl,a;
	w=nmw;
	DWORD *dw;
	char filter[385];
	LOGFONT *lg;
	if(tenable==1) a=16;else a=0;
	rt.left=nmw;rt.top=1+a;rt.right=wx;rt.bottom=rt.top+maxy*24;
	if(!rt.PtInRect(point)) return;   //不在编辑区
	y=(point.y-a)/24+dy;
	if(y>=esum) return;
	w=nmw;
	if(Geteditrect(y,rt)==0) return;
	rt.top+=3;rt.left+=2;
	x=y;
	j=edb[y].index;
	//看是否是COLOR，FONT，FILE
	if(edb[x].type==EDIT_COLOR)
	{
	  dw=(DWORD*)edb[x].addr;
	  CColorDialog cdlg(dw[0],0,this);
	  if(cdlg.DoModal()==IDOK){
	  dw[0]=cdlg.GetColor();
	  ::SendMessage(GetParent()->m_hWnd,WM_COMMAND,DataChanged,0);
	  InvalidateRect(&rt);};
	  SetObjtCursorPos();
	  return;
	}
	if(edb[x].type==EDIT_FONT)
	{
	  lg=(LOGFONT*)edb[x].addr;
	  agl=lg->lfEscapement;
	  CFontDialog cdlg(lg);
	  if(cdlg.DoModal()==IDOK){
	  cdlg.GetCurrentFont(lg);
	  lg->lfEscapement=agl;
	  ::SendMessage(GetParent()->m_hWnd,WM_COMMAND,DataChanged,0);
	  InvalidateRect(&rt);}
	  SetObjtCursorPos();
	  return;
	}
	if(edb[x].type==EDIT_FILE)
	{
	  sprintf(filter,"%s%s|%s|%s|%s|%s|%s|%s|%s",ftr[0],ftr[1],ftr[2],ftr[3],ftr[4],ftr[5],
      ftr[6],ftr[7],ftr[8]);
	  if(GetImgFile(edb[x].addr,filter,m_hWnd)){
	  ::SendMessage(GetParent()->m_hWnd,WM_COMMAND,FileChange,0);
	  InvalidateRect(&rt);}
	  return;
	}
	if(edb[x].type==EDIT_GIF)
	{
	  strcpy(filter,ftr[7]);
	  if(GetImgFile(edb[x].addr,filter,m_hWnd)){
	  ::SendMessage(GetParent()->m_hWnd,WM_COMMAND,FileChange,0);
	  InvalidateRect(&rt);}
	  SetObjtCursorPos();
	  return;
	}
	if(edb[x].type==EDIT_AVI)
	{
	  strcpy(filter,"AVI文件(*.AVI)|*.avi");
	  CFileDialog  fodlg(true,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filter,this);
	  if(fodlg.DoModal()==IDOK){
	  strcpy(edb[x].addr,fodlg.GetPathName()); 
	  strupr(edb[x].addr);
	  ::SendMessage(GetParent()->m_hWnd,WM_COMMAND,FileChange,0);
	  InvalidateRect(&rt);
	  SetObjtCursorPos();
	  }
	  return;
	}
	if(edb[x].type==EDIT_DLL)
	{
	  if(GetDllName(edb[x].addr,m_hWnd)){
	   strupr(edb[x].addr);
	   ::SendMessage(GetParent()->m_hWnd,WM_COMMAND,FileChange,0);
	   InvalidateRect(&rt);
	   SetObjtCursorPos();
	  }
	  return;
	};
	if(edb[x].type==EDIT_SWF)
	{
	  strcpy(filter,"Flash:SWF文件(*.swf)|*.swf");
	  CFileDialog  fodlg(true,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filter,this);
	  if(fodlg.DoModal()==IDOK){
	   strcpy(edb[x].addr,fodlg.GetPathName()); 
	   strupr(edb[x].addr);
	   ::SendMessage(GetParent()->m_hWnd,WM_COMMAND,FileChange,0);
	   InvalidateRect(&rt);
	   SetObjtCursorPos();
	  }
	  return;
	};
	/*if(edb[x].type==EDIT_STR)
	{
	  if(!EditText(edb[x].addr,edb[x].strmax,m_hWnd)) return;
	  ::SendMessage(GetParent()->m_hWnd,WM_COMMAND,DataChanged,0);
	  InvalidateRect(&rt);
	  SetObjtCursorPos();
	  return;
	}*/
	//其他情况
	if((j<0||j>lsum)&&edb[x].canedit==1) {
		ed.SetDataLink(edb[x].type,edb[x].addr,edb[x].strmax,(WORD)x,2);
		if(rt.right>=wx) rt.right=wx-1;
		rt.bottom-=1;
		rt.right-=1;
		ed.MoveWindow(rt);
	    ed.ShowWindow(SW_SHOW);
		li.ShowWindow(SW_HIDE);
	  	ed.SetSel(0,-1);
	};
	if(j>=0&&j<lsum&&edb[x].canedit==1){
	    li.ResetContent();
		for(i=0;i<litem[j].itemsum;i++){
		 li.AddString(litem[j].name[i].name);
		};
		li.SetDataLink(edb[x].type,edb[x].addr,(WORD)x);
		rt.top-=4;
		rt.left-=1;
		rt.bottom=rt.top+100;
		if(rt.right>=wx) rt.right=wx;
		rt.right-=1;
		li.MoveWindow(rt);
		li.ShowWindow(SW_SHOW);
		ed.ShowWindow(SW_HIDE);
	};
}


void Objwin::OnEditCopy() //将编辑类容COPY到剪裁板
{
    ed.Copy( );	
} 

void Objwin::OnEditPaste() //将剪裁板的内容粘贴到编辑中
{
	ed.Paste( );
	
}

int Objwin::SetColLinNum(int y) //设置X，Y方向编辑的数字
{
	if(y>MAXENM) return 0;
	tsum=1;
	esum=y;
	return 1;
}

int Objwin::SetLineName(char *name, int img,int index,int w) //设置行名
{
	if(index>=esum||index<0) return 0;
    strcpy(enm[index].name,name);
	enm[index].img=img;
	nmw=w <40 ? 40:w;
	return 1;
}


int Objwin::AddEditItem(int y, void *addr,char type,BYTE strmax,char canedit,char index) //加入编辑项目名
{
	if(y>=esum||y<0) return 0;
	edb[y].addr=(char*)addr;
	edb[y].type=type;
	edb[y].canedit=canedit;
	edb[y].strmax=strmax;
	edb[y].index=index;
	return 1;
}

void Objwin::SetCaptionName(char *name) //设置标题名称
{
	strcpy(title,name);
	tenable=1;
}

void Objwin::HideEdit()
{
	ed.ShowWindow(SW_HIDE);
}

void Objwin::SetListSum(int sum)
{
	int i,j;
	if(sum>24) return;
	lsum=sum;
	for(i=0;i<sum;i++){
		litem[i].itemsum=0;
		for(j=0;j<24;j++){
	     litem[i].name[j].name[0]=0;
		};
	};
}

int Objwin::ADDSubListItem(int index, char *str)
{
	int n;
	if(index<0||index>=lsum) return 0;
	n=litem[index].itemsum;
	if(n>=24) return 0;
	if(strlen(str)>=31) return 0;
	strcpy(litem[index].name[n].name,str);
	n++;
	litem[index].itemsum=n;
	return 1;
}

void Objwin::GetItemString(int index, int item, char *str)
{
	int n;
	strcpy(str,"[NULL]");
	if(index>=lsum) return;
	n=litem[index].itemsum;
	if(item<0||item>=n) return;
	strcpy(str,litem[index].name[item].name);
}

void Objwin::DataChange()
{
	int i;
	CClientDC dc(this);
	dc.SetBkMode(TRANSPARENT);
	dc.SelectObject(&font);
	dc.SetBkColor(RGB(0xff,0xff,0xff));
	dc.SelectObject(&pen);
    for(i=dy;i<esum;i++){
      if((i-dy)>=maxy) break;
	  ShowItem(dc,i);
	}
}

BOOL Objwin::Createtun(DWORD dwStyle,CWnd* pParentWnd) 
{
	WNDCLASS wndcls;
	memset(&wndcls, 0,sizeof(WNDCLASS));   
    wndcls.lpfnWndProc = ::DefWindowProc;
	wndcls.hInstance = AfxGetInstanceHandle();
	wndcls.hCursor = NULL;
	wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
	wndcls.lpszClassName ="popupwin";
	AfxRegisterClass(&wndcls);
	return CreateEx (0, "popupwin","", dwStyle,1,1,100,300,pParentWnd->m_hWnd,NULL);
}

void Objwin::SetObjtCursorPos()
{
	CPoint pt=CPoint(wx/2,wy/2);
	ClientToScreen(&pt);
	SetCursorPos(pt.x,pt.y);
}


void Objwin::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CRect rt;
	int a;
	if(tenable==1) a=16;else a=0;
	rt=CRect(0,a,wx,wy);
	if(rt.PtInRect(point)){
		editoperate(point);
		return;
	};
	CWnd::OnLButtonDown(nFlags, point);
}


