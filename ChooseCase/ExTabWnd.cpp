// ExTabWnd.cpp : implementation file
//

#include "stdafx.h"
//#include "CVisModeMGDll.h"
#include "ChooseCase.h"
#include "ExTabWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExTabWnd

CExTabWnd::CExTabWnd()
{
	m_cursel = 0;
	m_view.RemoveAll();
	m_ptab.RemoveAll();
	m_viewID.RemoveAll();
}

CExTabWnd::~CExTabWnd()
{
	int count = m_ptab.GetSize();
	for(int i=0; i<count; i++)
	{
		CButtonST* ptemp =NULL;
		ptemp = (CButtonST*)m_ptab.GetAt(i);
		if(ptemp!=NULL)
			delete ptemp;
	}
	m_ptab.RemoveAll();

/*	count = m_view.GetSize();
	for(i=0; i<count; i++)
	{
		CDialog* ptemp =NULL;
		ptemp = (CDialog*)m_view.GetAt(i);
		if(ptemp!=NULL)
		{
			//ptemp->CloseWindow();
			delete ptemp;
		}
	}*/
	m_view.RemoveAll();
	m_viewID.RemoveAll();
}


BEGIN_MESSAGE_MAP(CExTabWnd, CWnd)
	//{{AFX_MSG_MAP(CExTabWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CExTabWnd message handlers

int CExTabWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	szcaption.Format("%s", lpCreateStruct->lpszName);
	CRect rect;
	this->GetClientRect(&rect);

	m_caprect = rect;
	m_childrect = rect;

	//m_caprect.bottom = 35;
	//m_childrect.top = m_caprect.bottom-3;

	//创建按钮
//	m_ptab = new CButtonST[3];
	int count = m_ptab.GetSize();

	/*for(int i=0; i<count; i++)
	{
		CButtonST* pbutton = (CButtonST*)m_ptab.GetAt(i);

		pbutton->Create(_T(pbutton->m_name), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
			CRect(m_caprect.left+2+i*150+1,m_caprect.top+2,m_caprect.left+2+(i+1)*150+5,m_caprect.bottom), this, i+1000);

		pbutton->ShowWindow(SW_SHOW);
//		pbutton->SetFlat(FALSE);
		pbutton->SetIcon(IDI_ICON1, IDI_ICON1);
		pbutton->SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, CAPTION_CLCOLOR);
		pbutton->SetColor(CButtonST::BTNST_COLOR_BK_OUT, CAPTION_CLCOLOR);
//		pbutton->OffsetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(200, 128, 0));
//		pbutton->SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(200, 101, 51));
		pbutton->m_devtype = i+1;
	}*/

	//创建属性页
	CRect viewrc;
	viewrc = m_childrect;
	/*viewrc.top+=10;
	viewrc.left+=10;
	viewrc.bottom-=10;
	viewrc.right-=10;*/

	count = m_view.GetSize();
	RECT rc ={viewrc.left,viewrc.top,viewrc.right,viewrc.bottom};
	for(int i=0; i<count; i++)
	{
		CDialog* pwnd = (CDialog*)m_view.GetAt(i);
		if(pwnd==NULL||pwnd->GetSafeHwnd()!=NULL)
			continue;

//		pwnd->Create(NULL,   NULL,   AFX_WS_DEFAULT_VIEW, 
//			viewrc, this, 2000+i);
//		pwnd->OnInitialUpdate();
		pwnd->Create(m_viewID.GetAt(i), this);

		pwnd->MoveWindow(viewrc, TRUE);
		if(i==0)
			pwnd->ShowWindow(SW_SHOW);
		else
			pwnd->ShowWindow(SW_HIDE);
	}
	m_cursel = 0;
	showtabview(m_cursel+1);
	return 0;
}

void CExTabWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	dc.FillSolidRect(&m_caprect,CAPTION_BKCOLOR);
	dc.FillSolidRect(&m_childrect, CAPTION_CLCOLOR);

	dc.SetBkMode(TRANSPARENT);
	dc.TextOut(m_caprect.right-200, m_caprect.Height()/4, szcaption);
	// Do not call CWnd::OnPaint() for painting messages
}

LRESULT CExTabWnd::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(message==ID_TABCHANGE)
	{
		if(lParam!=NULL)
			showtabview(lParam);
	}
	return CWnd::WindowProc(message, wParam, lParam);
}

void CExTabWnd::showtabview(LPARAM lParam)
{
	int type = (int)lParam-1;
	if(type<0||type>3)
		return;

	m_cursel = type;
//	CString sztring;
//	sztring.Format("%d", type);
//	::AfxMessageBox(sztring);
	int count = m_view.GetSize();
	for(int i=0; i<count; i++)
	{
		CDialog* pwnd = (CDialog*)m_view.GetAt(i);
		if(pwnd==NULL||pwnd->GetSafeHwnd()==NULL)
			continue;

		if(m_cursel==i)
		{
			pwnd->ShowWindow(SW_SHOW);
		}
		else
		{
			pwnd->ShowWindow(SW_HIDE);
		}
	}

	/*count = m_ptab.GetSize();
	CRect rect;
	for(i=0; i<count; i++)
	{
		CButtonST* pbutton = (CButtonST*)m_ptab.GetAt(i);
		if(pbutton==NULL||pbutton->GetSafeHwnd()==NULL)
			continue;

		if(m_cursel==i)
			rect = CRect(m_caprect.left+2+i*150+1,m_caprect.top+2,m_caprect.left+2+(i+1)*150,m_caprect.bottom);
		else
			rect = CRect(m_caprect.left+2+i*150+1,m_caprect.top+2,m_caprect.left+2+(i+1)*150,m_caprect.bottom-4);
		pbutton->MoveWindow(&rect, TRUE);
	}*/

//	this->UpdateWindow();


/*	switch(type)
	{
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	default:
		break;
	}*/
}

void CExTabWnd::AddView(CDialog* pview, UINT viewID, LPCSTR szname)
{
//	CDialog* pnewview = new CDialog;
	m_view.Add(pview);
	m_viewID.Add(viewID);

	//按钮
	CButtonST* pnew = new CButtonST;
	m_ptab.Add(pnew);

	pnew->m_name.Format("%s", szname);
	pnew->m_devtype = m_ptab.GetSize();
}
