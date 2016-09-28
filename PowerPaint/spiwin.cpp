// spiwin.cpp : implementation file
//

#include "stdafx.h"
#include "PowerPaint.h"
#include "spiwin.h"
#include "gdata.h"
#include "comobj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern gdata dbm;
extern comobj cobj;
extern char *ftr[];
BOOL GetImgFile(char *filename,char *filter,HWND hWndParent);
/////////////////////////////////////////////////////////////////////////////
// spiwin

spiwin::spiwin()
{
	dy=0;
	maxy=1;
	pgsum=0;
	curpg=0;
	selpic=0;
	mdc.Create(1,1);
	menu.LoadMenu(IDR_SPICMG);
}

spiwin::~spiwin()
{
	menu.DestroyMenu();
}


BEGIN_MESSAGE_MAP(spiwin, CWnd)
	//{{AFX_MSG_MAP(spiwin)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_COMMAND(IDC_ADDSPIC, OnAddspic)
	ON_COMMAND(IDC_OPENSPIC, OnOpenspic)
	ON_COMMAND(IDC_SAVESPIC, OnSavespic)
	ON_WM_VSCROLL()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(IDC_DELSPIC, OnDelspic)
	ON_COMMAND(IDC_DELNOUSE, OnDelnouse)
	ON_COMMAND(IDC_COPYTODESK, OnCopytodesk)
	ON_COMMAND(IDC_DEFPTN, OnDefptn)
	ON_COMMAND(IDC_DEFACT, OnDefact)
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// spiwin message handlers

BOOL spiwin::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), NULL, NULL);
	return TRUE;
}

void spiwin::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	wx=cx;
	wy=cy;
	if(wx>1&&wy>1) mdc.SizeChange(wx-20,wy);
	yscroll.MoveWindow(CRect(wx-21,0,wx,wy));
	computpage();
	SetYScroll();
}

void spiwin::OnPaint() 
{
	CPaintDC dc(this);
	ShowImg();
	mdc.BitBlt(dc.m_hDC,CRect(0,0,wx-20,wy));
	computpage();
	SetYScroll();
}

int spiwin::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	yscroll.Create(WS_CHILD|WS_VISIBLE|SBS_VERT,CRect(0,0,1,1),this,100);
	
	return 0;
}

//在画板上显示图片
void spiwin::ShowImg()
{
	char p[100];
	BITMAPINFO *bi;
	int j,k;
	CRect rt,rt1;
	DWORD color;
	mdc.FillBG(0xffffff);

	for(j=0;j<maxy+1;j++){
		k=dy+j;
		if(k>=cobj.spicsum) break;
		rt.left=dx;
		rt.top=j*100+5;
		rt.right=rt.left+90;
		rt.bottom=rt.top+90;
		rt1=rt;
		rt1.left+=3;rt1.top+=3;
		rt1.right-=3;rt1.bottom-=3;
		ShowAimg(k,rt1);
		rt1=rt;
		if(k==selpic)
		{
			GLRect(mdc.m_hDC,rt.left,rt.top,rt.right,rt.bottom,1,0);
			rt.left--;
			rt.top--;
			rt.right++;
			rt.bottom++;
			GLRect(mdc.m_hDC,rt.left,rt.top,rt.right,rt.bottom,1,0);
		}
		else GLRect(mdc.m_hDC,rt.left,rt.top,rt.right,rt.bottom,1,0xc0c0c0);
		bi=(BITMAPINFO*)cobj.spic[k].img.bnf;
		sprintf(p,"%dX%dX%d",cobj.spic[k].img.nWidth,cobj.spic[k].img.nHeight,bi->bmiHeader.biBitCount);
		rt1.top=rt1.bottom-16;
		rt1.bottom-=2;
		color=cobj.spic[k].inuse>0 ? 0xff0000:0;
		GLDDrawText(mdc.m_hDC,&rt1,&lf,p,0,0,DT_CENTER);
	};
}

//显示一幅图片
void spiwin::ShowAimg(int index, CRect &rt)
{
	int w,h,w1,h1,dw,dh;
	int x,y;
	w=cobj.spic[index].img.nWidth;
	h=cobj.spic[index].img.nHeight;
	w1=rt.right-rt.left;
	h1=rt.bottom-rt.top;
	if(w<w1&&h<h1){
	  x=rt.left+(w1-w)/2;
	  y=rt.top+(h1-h)/2;
	  cobj.spic[index].img.Show(mdc.m_hDC,x,y);
	  return;
	};
	dw=w1;
	dh=h1;
	if(w>h) dh=h*w1/w;
	if(w<h) dw=w*h1/h;
	x=rt.left+(w1-dw)/2;
	y=rt.top+(h1-dh)/2;
	StretchBlt(mdc.m_hDC,x,y,dw,dh,cobj.spic[index].img.m_hDC,0,0,w,h,SRCCOPY);
}

//计算页面数
void spiwin::computpage()
{
	int sum=cobj.spicsum;
	dx=(wx-90-21)/2;
	if(dx<0) dx=0;
	maxy=wy/100;
}

//设置滚动杆
void spiwin::SetYScroll()
{
	int sp=cobj.spicsum-1;
	sp=sp<0 ? 0:sp;
	if(sp>0){
		yscroll.EnableScrollBar(ESB_ENABLE_BOTH);
		yscroll.SetScrollRange(0,sp);
		yscroll.SetScrollPos(dy);
	}else{
		yscroll.EnableScrollBar(ESB_DISABLE_BOTH);
	};
}

void spiwin::OnAddspic() 
{
	char filter[385];
	char filename[256];
	sprintf(filter,"%s%s|%s|%s|%s|%s|%s|%s|%s",ftr[0],ftr[1],ftr[2],ftr[3],ftr[4],ftr[5],
    ftr[6],ftr[7],ftr[8]);
	if(GetImgFile(filename,filter,m_hWnd)){
		AddImg(filename);
	};
}

//添加一幅小图到
void spiwin::AddImg(char *filename)
{
	if(cobj.spicsum>=MAXSPIC){
	  MessageBox("缓冲区已满,不能添加图标!");
	  return;
	};
	if(cobj.spic[cobj.spicsum].img.ReadImage(filename))
	{
	 cobj.spic[cobj.spicsum].id=cobj.GetANoUsePICID();
	 cobj.spic[cobj.spicsum].inuse=0;
	 cobj.spic[cobj.spicsum].tranmode=0;
	 cobj.spic[cobj.spicsum].trancolor=0x10101;
	 cobj.spicsum++;
	 computpage();
	 SetYScroll();
	 Invalidate();
	}
}

void spiwin::OnOpenspic() 
{
	char filter[256];
	char fnm[256];
	strcpy(filter,"图形组文件(*.GGP)|*.ggp");
	CFileDialog  fodlg(true,NULL,NULL,
		OFN_FILEMUSTEXIST|OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filter,this);
	if(fodlg.DoModal()==IDOK){
	  strcpy(fnm,fodlg.GetPathName());
	  LoadGGP(fnm);
	};
}

//打开一个图形组文件
void spiwin::LoadGGP(char *filename)
{
	int i,k,n;
	DWORD *dw;
	uncmpres upr;
	FILE *fp;
	N_PHEAD ph;
	N_PDATA pd;
	char *btmp;
	char *dib;
	fp=fopen(filename,"r+b");
	if(fp==NULL){
	  MessageBox("文件不存在");
	  return;
	};
	fread(&ph,sizeof(N_PHEAD),1,fp);
	if(ph.flag!=0xf9876761||ph.version>0x100){
	  MessageBox("不识别的文件格式或高版本的文件!");
	  return;
	};
	n=0;
	for(i=0;i<ph.picsum;i++){
	  k=i+cobj.spicsum;
	  fread(&pd,sizeof(N_PDATA),1,fp);
	  if(pd.start!=0x10891111) break;
	  btmp=new char[pd.psize+100];
	  dib=new char[pd.size+100];
	  fread(btmp,pd.psize,1,fp);
	  dw=(DWORD*)btmp;
	  upr.initdata();
	  upr.DDeCode(btmp+4,dib,pd.psize,dw[0]); //解压
	  cobj.spic[k].img.Create(dib);
	  if(pd.tranflag==1&&pd.bits<=8) cobj.spic[k].img.CreateRGN(pd.tranindex); 
	  cobj.spic[k].id=cobj.GetANoUsePICID();
	  cobj.spic[k].tranmode=pd.tranmode;
	  cobj.spic[k].trancolor=pd.trancolor;
	  cobj.spic[k].inuse=0;
	  cobj.spic[k].id=k;
	  delete btmp;	
	  delete dib;
	  n++;
	};
	fclose(fp);
	cobj.spicsum+=n;
	computpage();
	SetYScroll();
	Invalidate();
}

void spiwin::OnSavespic() 
{
	char filter[256];
	char fnm[256];
	char *lp;
	if(cobj.spicsum<=0){
		MessageBox("小图区没有图形");	
		return;
	};
	strcpy(filter,"图形组文件(*.GGP)|*.ggp");
	CFileDialog  fodlg(false,NULL,NULL,
		OFN_CREATEPROMPT|OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filter,this);
	if(fodlg.DoModal()==IDOK){
	  strcpy(fnm,fodlg.GetPathName());
	  lp=strchr(fnm,'.');
	  if(lp!=NULL) *lp=0;
	  strcat(fnm,".ggp");
	  SaveGGP(fnm);
	};
}

//保存图形组
void spiwin::SaveGGP(char *filename)
{
	int i;
	BITMAPINFO *bi;
	FILE *fp;
	N_PHEAD ph;
	N_PDATA pd;
	int hsize,size,ks,sz;
	char *btmp,*src;
	cmpress cps;
	fp=fopen(filename,"w+b");
	if(fp==NULL) return;
	SetCursor(LoadCursor(NULL,IDC_WAIT));
	ph.flag=0xf9876761;
	ph.version=0x100;
	ph.picsum=cobj.spicsum;
	fwrite(&ph,sizeof(N_PHEAD),1,fp);
	pd.start=0x10891111;
	pd.press=1;
	for(i=0;i<cobj.spicsum;i++){
		bi=(BITMAPINFO*)cobj.spic[i].img.bnf;
		pd.bits=(BYTE)bi->bmiHeader.biBitCount;
		hsize=colornums(pd.bits)*sizeof(RGBQUAD)+sizeof(BITMAPINFOHEADER);
		pd.sPerline=cobj.spic[i].img.sPerline;
		pd.tranflag=cobj.spic[i].img.tranflag;
		pd.tranindex=cobj.spic[i].img.colorindex;
		pd.nWidth=cobj.spic[i].img.nWidth;
		pd.nHeight=cobj.spic[i].img.nHeight;
		pd.tranmode=cobj.spic[i].tranmode;
		pd.trancolor=cobj.spic[i].trancolor;
		size=pd.sPerline*pd.nHeight;
		pd.size=size+hsize;
		src=new char[pd.size+1000];
		memcpy(src,cobj.spic[i].img.bnf,hsize);
		memcpy(src+hsize,cobj.spic[i].img.dib,size);
		ks=pd.size;
	    btmp=new char[ks+10000];
		cps.initdata();
	    sz=cps.EEnCode(src,btmp,ks,ks+100);
		pd.psize=sz;
		fwrite(&pd,sizeof(N_PDATA),1,fp);
		fwrite(btmp,1,sz,fp);
		delete btmp;
		delete src;
		};
	 fclose(fp);
	 SetCursor(LoadCursor(NULL, IDC_ARROW));
}

int spiwin::colornums(int bits) //返回颜色数
{
	switch(bits)
    {
        case 1: return 2;
        case 4: return 16;
        case 8: return 256;
        default: return 0;
    }
}

void spiwin::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int sy,vy;
	vy=dy;
	switch(nSBCode){
	case SB_LINEDOWN:
	case SB_PAGEDOWN:
		dy=dy<cobj.spicsum-1 ? dy+1:dy;	
		break;
	case SB_LINEUP:
	case SB_PAGEUP:
		dy=dy>0 ? dy-1:0;
		break;
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
		dy=nPos;
		break;  
	};
	sy=dy-vy;
	if(sy!=0){
		yscroll.SetScrollPos(dy);
		CClientDC dc(this);
	    ShowImg();
		mdc.BitBlt(dc.m_hDC,CRect(0,0,wx-20,wy));
	};
	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

void spiwin::OnLButtonDown(UINT nFlags, CPoint point) 
{
	int k;
	k=dy+point.y/100;
	if(k>=cobj.spicsum) return;
	selpic=k;
	CClientDC dc(this);
	ShowImg();
	mdc.BitBlt(dc.m_hDC,CRect(0,0,wx-20,wy));
	SetFocus();
	CWnd::OnLButtonDown(nFlags, point);
}

void spiwin::OnDelspic() 
{
	int i,id,k;
	if(cobj.spicsum<=0||selpic<0||selpic>=cobj.spicsum) return;
	id=cobj.spic[selpic].id;
	if(dbm.SpicInUse(id)){
	 MessageBox("当前图标正在使用,不能删除!");
	 return;
	};
	//删除选择的图形
	cobj.spic[selpic].img.FreeMem();
	for(i=selpic;i<cobj.spicsum-1;i++){
	  cobj.spic[i]=cobj.spic[i+1];
	};
	cobj.spicsum--;
	k=cobj.spicsum;
	if(k>0){
	  cobj.spic[k].img.bnf=NULL;	
	  cobj.spic[k].img.dib=NULL;
	  cobj.spic[k].img.hbitmap=NULL;
	  cobj.spic[k].img.hrgn=NULL;
	  cobj.spic[k].img.m_hDC=0;
	};
	CClientDC dc(this);
	ShowImg();
	mdc.BitBlt(dc.m_hDC,CRect(0,0,-20,100));
}

void spiwin::OnDelnouse() 
{
	int i;
	for(i=0;i<cobj.spicsum;i++){
		if(cobj.spic[i].inuse<=0){
		  if(DeleteAPIC(i)) i--;;
		};
	};
	computpage();
	SetYScroll();
	CClientDC dc(this);
	ShowImg();
	mdc.BitBlt(dc.m_hDC,CRect(0,0,wx-20,wy));
}

//清除一个给定记录的图标
bool spiwin::DeleteAPIC(int recno)
{
	int i,k;
	if(recno>=cobj.spicsum) return false;
	cobj.spic[recno].img.FreeMem();
	for(i=recno;i<cobj.spicsum-1;i++){
	  cobj.spic[i]=cobj.spic[i+1];
	};
	cobj.spicsum--;
	k=cobj.spicsum;
	if(k>0){
	  cobj.spic[k].img.bnf=NULL;	
	  cobj.spic[k].img.dib=NULL;
	  cobj.spic[k].img.hbitmap=NULL;
	  cobj.spic[k].img.hrgn=NULL;
	  cobj.spic[k].img.m_hDC;
	};
	return true;
}

void spiwin::OnCopytodesk() 
{
	if(cobj.spicsum<=0||selpic>=cobj.spicsum)
	{
		MessageBox("没有选择图形!");
		return;
	}
	cobj.patternID=cobj.spic[selpic].id;
	cobj.cvs->Addspic();
	cobj.tlsw->ReFreshWin();
}

void spiwin::OnDefptn() 
{
	if(cobj.spicsum<=0||selpic>=cobj.spicsum)
	{
		MessageBox("没有选择图形!");
		return;
	}
	cobj.patternID=cobj.spic[selpic].id;
}


void spiwin::OnDefact() 
{
	int i,id;
	N_ACTOBJ *act;
	i=dbm.GetFirstSelObj();
	if(i<0){
	 MessageBox("没有选中对象");
	 return;
	}
	if(dbm.clayer->obj[i].attr.type!=80){
	 MessageBox("选中的对象不是活动对象类型！");
	 return;
	}
	id=cobj.spic[selpic].id;
	act=(N_ACTOBJ*)dbm.clayer->obj[i].buf;
	act->gid=id;
	cobj.cvs->DrawShow();
	cobj.tlsw->ReFreshWin();
}

void spiwin::ReOpen()
{
	computpage();
	SetYScroll();
	CClientDC dc(this);
	ShowImg();
	mdc.BitBlt(dc.m_hDC,CRect(0,0,wx-20,wy));
}

void spiwin::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CPoint pt;
	CMenu *mm;
	pt=point;
	ClientToScreen(&pt);
	mm=menu.GetSubMenu(0);
	mm->TrackPopupMenu(TPM_LEFTALIGN,pt.x,pt.y,this);
	CWnd::OnRButtonDown(nFlags, point);
}

BOOL spiwin::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	int sy,vy,y;
	CClientDC dc(this);
	vy=dy;
	y=zDelta>0 ? 1:2;
	switch(y){
	case 2:
		dy=dy<cobj.spicsum-1 ? dy+1:dy;	
		break;
	case 1:
		dy=dy>0 ? dy-1:0;
		break;
	};
	sy=dy-vy;
	if(sy!=0){
		yscroll.SetScrollPos(dy);
		ShowImg();
		mdc.BitBlt(dc.m_hDC,CRect(0,0,wx-20,wy));
	};
	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}
