// FirstDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WelcomePage.h"
#include "FirstDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFirstDlg dialog


CFirstDlg::CFirstDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFirstDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFirstDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFirstDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFirstDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFirstDlg, CDialog)
	//{{AFX_MSG_MAP(CFirstDlg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFirstDlg message handlers

void CFirstDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CRect rect;
	this->GetClientRect(rect);
	
	m_capbitmap.LoadBitmap(IDB_BACK_BMP);
	
	CDC m_memdc;
	m_memdc.CreateCompatibleDC(&dc);
	CBitmap   *pOldBit=m_memdc.SelectObject(&m_capbitmap);   	
	
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &m_memdc, 0,0,SRCCOPY);
	m_memdc.SelectObject(pOldBit);
	m_memdc.DeleteDC();
	// Do not call CDialog::OnPaint() for painting messages
}
