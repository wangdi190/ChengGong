// imgopen.cpp : implementation file
//

#include "stdafx.h"
#include "PowerPaint.h"
#include "imgopen.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNAMIC(imgopen, CFileDialog)

imgopen::imgopen(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
	m_ofn.hInstance = AfxGetInstanceHandle();
    m_ofn.lpTemplateName = MAKEINTRESOURCE(IDD_IMGDLG);
    //m_ofn.lpfnHook = OFNHookProc;   
	m_showpreview=0;
    img.FreeMem();
}

imgopen::~imgopen()
{
	img.FreeMem();
}

BEGIN_MESSAGE_MAP(imgopen, CFileDialog)
	//{{AFX_MSG_MAP(imgopen)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		ON_COMMAND(IDC_SHOWPREVIEW,OnSHowpreview)
		ON_COMMAND(IDC_DEPTH,OnDepth)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void imgopen::OnSHowpreview()
{
	CWnd *wnd;
	OFSTRUCT o;
	char filename[256],str[255];
	m_showpreview = IsDlgButtonChecked(IDC_SHOWPREVIEW);
    if (!m_showpreview)
    {                    
		img.FreeMem();
        wnd =GetDlgItem(IDC_PREVIEWBTN);
        if(wnd!=NULL) wnd->InvalidateRect(NULL,TRUE);    
        SetDlgItemText(IDC_WIDTH,"");
        SetDlgItemText(IDC_HEIGHT,"");
        SetDlgItemText(IDC_FSIZE,"");
    }else{
		GetParent()->SendMessage(CDM_GETFILEPATH ,1024,(LPARAM)filename);                
		if(strlen(filename)>4) img.ReadImage(filename);
	};
	if(img.m_hDC!=NULL){
		wnd = GetDlgItem(IDC_PREVIEWBTN);
		if(wnd!=NULL) wnd->InvalidateRect(NULL,TRUE);
        w=img.nWidth;
		h=img.nHeight;
        
        wsprintf(str,"宽度: %d 象素",w);
        SetDlgItemText(IDC_WIDTH,str);
        wsprintf(str,"高度: %d 象素",h);
        SetDlgItemText(IDC_HEIGHT,str);
        		
        HFILE f = OpenFile(filename,&o,OF_READ);
        wsprintf(str,"文件: %ld Kb",GetFileSize((HANDLE)f,NULL)/1024);
        SetDlgItemText(IDC_FSIZE,str);
        _lclose(f);
	};

}

void imgopen::OnDepth()
{
	CWnd *wnd;
	if(img.m_hDC==NULL) return;
	wnd = GetDlgItem(IDC_PREVIEWBTN);
	if(wnd!=NULL) wnd->InvalidateRect(NULL,TRUE);
}

LRESULT imgopen::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	LPNMHDR pnmh;
	pnmh = (LPNMHDR) lParam;
	switch(message)
	{
	case WM_DRAWITEM:
		OnDraw(lParam);
		break;
	case WM_NOTIFY:
		OnNotify(pnmh);
		break;
		
	}
	return CFileDialog::WindowProc(message, wParam, lParam);
}

void imgopen::OnDraw(LPARAM lParam)
{
	RECT rt;
	int s;
	LPDRAWITEMSTRUCT lpdis;
	char filename[1024];
	int height,height2,width,width2;
	filename[0]=0;
	if (img.m_hDC!=NULL)
    {
        w=img.nWidth;
		h=img.nHeight;
		lpdis = (LPDRAWITEMSTRUCT)lParam;
		rt=lpdis->rcItem;
        CPoint size(w,h);
		if(w==0||h==0) return;
        if (w> h)
        {
			height = lpdis->rcItem.bottom - lpdis->rcItem.top;
			float ratio = (float)h/(float)w;                 
			lpdis->rcItem.bottom  = (long) (lpdis->rcItem.top + (lpdis->rcItem.right-lpdis->rcItem.left)*ratio);
            height2 = (height - (lpdis->rcItem.bottom - lpdis->rcItem.top))/2;
            lpdis->rcItem.top += height2;
            lpdis->rcItem.bottom += height2;
         }
         else
         {
            width = lpdis->rcItem.right - lpdis->rcItem.left;
            float ratio = (float)w/(float)h;                 
            lpdis->rcItem.right  = (long) (lpdis->rcItem.left + (lpdis->rcItem.bottom-lpdis->rcItem.top)*ratio);
            width2 = (width - (lpdis->rcItem.right - lpdis->rcItem.left))/2;
            lpdis->rcItem.left += width2;
            lpdis->rcItem.right += width2;
          }    
		s=IsDlgButtonChecked(IDC_DEPTH);
        if(s==0) StretchBlt(lpdis->hDC,lpdis->rcItem.left,lpdis->rcItem.top,lpdis->rcItem.right-lpdis->rcItem.left,lpdis->rcItem.bottom-lpdis->rcItem.top,img.m_hDC,0,0,w,h,SRCCOPY);
		else img.Show(lpdis->hDC,rt.left,rt.top,rt.right-rt.left,rt.bottom-rt.top);
   }
}

void imgopen::OnNotify(LPNMHDR pnmh)
{
	CWnd *wnd;
	OFSTRUCT o;
	char filename[256],str[255];
	filename[0]=0;
	switch(pnmh->code)
	{
	case CDN_INITDONE:
		CheckDlgButton(IDC_SHOWPREVIEW,m_showpreview);
        break;
	case CDN_SELCHANGE:
		if (!IsDlgButtonChecked(IDC_SHOWPREVIEW)) return;
        GetParent()->SendMessage(CDM_GETFILEPATH ,1024,(LPARAM)filename);                
        img.ReadImage(filename);
		if(img.m_hDC==NULL||img.nHeight==0||img.nWidth==0) return;
        wnd = GetDlgItem(IDC_PREVIEWBTN);
        if(wnd!=NULL) wnd->InvalidateRect(NULL,TRUE);
        if (img.m_hDC)
        {
            w=img.nWidth;
		    h=img.nHeight;
        
            wsprintf(str,"宽度: %d 象素",w);
            SetDlgItemText(IDC_WIDTH,str);
            wsprintf(str,"高度: %d 象素",h);
            SetDlgItemText(IDC_HEIGHT,str);
            
			HFILE f = OpenFile(filename,&o,OF_READ);
            wsprintf(str,"文件: %ld Kb",GetFileSize((HANDLE)f,NULL)/1024);
            SetDlgItemText(IDC_FSIZE,str);
            _lclose(f);
         }
         else
         {
            SetDlgItemText(IDC_WIDTH,"");
            SetDlgItemText(IDC_HEIGHT,"");
            SetDlgItemText(IDC_FSIZE,"");
          }
		 break;
    }
}

BOOL GetImgFile(char *filename,char *filter,HWND hWndParent)
{
	 imgopen  fodlg(true,NULL,NULL,OFN_ENABLEHOOK|OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT|OFN_EXPLORER|OFN_ENABLETEMPLATE,
		 filter,CWnd::FromHandle(hWndParent));
	 if(fodlg.DoModal()==IDOK)
	 {
		strcpy(filename,fodlg.GetPathName()); 
		return true;
	 };
	 return false;
};
