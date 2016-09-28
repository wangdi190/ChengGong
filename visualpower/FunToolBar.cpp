// FunToolBar.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPower.h"
#include "FunToolBar.h"
#include "ComObj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char* g_pFun[]={"基本潮流","母线等高线","母线等高线低","母线等高线高","输电线等高线","变压器等高线","负荷等高线",\
                      "断面潮流","灵敏度计算","发电机备用","无功出力及备用","变压器备用","变压器温度","N-1电压风险排序",\
					  "N-1潮流风险排序","N-1风险排序","预测N-1电压风险排序","预测N-1潮流风险排序","预测N-1风险排序",\
					  "N-1影响","分区信息","系统统计棒图","SOE回放","低频震荡监视"};//24个

extern comobj  cobj;		//公共对象
/////////////////////////////////////////////////////////////////////////////
// FunToolBar

FunToolBar::FunToolBar()
{
	CFont font;
	color=GetSysColor(COLOR_3DFACE);
	font.CreateFont(16,8,0,0,400,0,0,0,1,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,"宋体" );
	font.GetLogFont(&lf);
	font.DeleteObject();
	mdc.Create(1,1);
	curft=0;
}

FunToolBar::~FunToolBar()
{
}


BEGIN_MESSAGE_MAP(FunToolBar, CToolBar)
	//{{AFX_MSG_MAP(FunToolBar)
	ON_WM_SIZE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FunToolBar message handlers

void FunToolBar::OnSize(UINT nType, int cx, int cy) 
{
	CRect rt;
	CToolBar::OnSize(nType, cx, cy);
	GetItemRect(1,&rt); 
	rt1=rt;
	rt1.left+=4;
	//rt1.top+=1;
	rt1.right-=1;
	rt1.bottom-=1;
	rt2=rt1;
	rt2.OffsetRect(-rt1.left,-rt1.top);
	rw=rt.Width();
	rh=rt.Height();
	mdc.SizeChange(rw,rh);	
	
}

void FunToolBar::OnPaint() 
{
	
	CToolBar::OnPaint();
	CClientDC dc(this);
	Showft();
	mdc.BitBlt(dc.m_hDC,rt1);
}


void FunToolBar::Showft()
{
	char p[100];
	CRect rt;
	mdc.FillBG(0x7f7f7f);
	mdc.CDraw3DRect(rt2,0,0xffffff);
	rt=rt2;
	rt.left+=2;
	rt.right-=2;
	if(curft>=24||curft<0) strcpy(p,"未知功能");	
	else strcpy(p,g_pFun[curft]);
	GLDDrawText(mdc.m_hDC,&rt,&lf,p,0xff00,0,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
}

//设置新的功能号
void FunToolBar::ReDrawNewFt()
{
	curft=cobj.swin->m_CurFun;
	CClientDC dc(this);
	Showft();
	mdc.BitBlt(dc.m_hDC,rt1);
}