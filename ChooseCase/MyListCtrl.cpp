// MyListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "ChooseCase.h"
#include "MyListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl

CMyListCtrl::CMyListCtrl()
{
}

CMyListCtrl::~CMyListCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CMyListCtrl)
	ON_WM_MEASUREITEM_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl message handlers


void CMyListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)  
{  
	// TODO: Add your code to draw the specified item  
	ASSERT(lpDrawItemStruct->CtlType == ODT_LISTVIEW);  
	CDC dc;   
	dc.Attach(lpDrawItemStruct->hDC);  
	ASSERT(NULL != dc.GetSafeHdc());  
	// Save these value to restore them when done drawing.  
	COLORREF crOldTextColor = dc.GetTextColor();  
	COLORREF crOldBkColor = dc.GetBkColor();  
	
	// If this item is selected, set the background color   
	// and the text color to appropriate values. Also, erase  
	// rect by filling it with the background color.  
/*	if ((lpDrawItemStruct->itemAction | ODA_SELECT) &&  
		(lpDrawItemStruct->itemState & ODS_SELECTED))  
	{  
		dc.SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));  
		dc.SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));  
		dc.FillSolidRect(&lpDrawItemStruct->rcItem,   
			::GetSysColor(COLOR_HIGHLIGHT));  
	}  
	else  
	{  
		if(lpDrawItemStruct->itemID%2)
			dc.FillSolidRect(&lpDrawItemStruct->rcItem, RGB(219,239, 250));
		else
			dc.FillSolidRect(&lpDrawItemStruct->rcItem, RGB(255,128,255));
	}  */
	
	// If this item has the focus, draw a red frame around the  
	// item's rect.  
	if ((lpDrawItemStruct->itemAction | ODA_FOCUS) &&  
		(lpDrawItemStruct->itemState & ODS_FOCUS))  
	{  
		CBrush br(RGB(0, 0, 128));  
		dc.FrameRect(&lpDrawItemStruct->rcItem, &br);  
	}  
	
	// Draw the text.  
	CString strText(_T(""));  
	CRect rcItem;  
	
	for(int i=0; i<GetHeaderCtrl()->GetItemCount(); i++)  
	{  
		strText = GetItemText(lpDrawItemStruct->itemID, i);  
		GetSubItemRect(lpDrawItemStruct->itemID, i, LVIR_LABEL, rcItem);  
		rcItem.left += 5;  
		dc.DrawText(  
			strText,  
			strText.GetLength(),  
			&rcItem,  
			DT_LEFT|DT_SINGLELINE|DT_VCENTER);  
	}  
	
	// Reset the background color and the text color back to their  
	// original values.  
	dc.SetTextColor(crOldTextColor);  
	dc.SetBkColor(crOldBkColor);  
	
	dc.Detach();  
}  

void CMyListCtrl::SetItemHeight(UINT nHeight)
{
	m_nItemHeight = nHeight;
	
	CRect rcWin;
	GetWindowRect(&rcWin);
	WINDOWPOS wp;
	wp.hwnd = m_hWnd;
	wp.cx = rcWin.Width();
	wp.cy = rcWin.Height();
	wp.flags = SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER;
	
	SendMessage(WM_WINDOWPOSCHANGED, 0, (LPARAM)&wp);
}

void CMyListCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	lpMeasureItemStruct->itemHeight = m_nItemHeight;
}
