// MainWin.h : interface of the CMainWin class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINWIN_H__CC47DF28_A08B_4868_B310_1282B2C52214__INCLUDED_)
#define AFX_MAINWIN_H__CC47DF28_A08B_4868_B310_1282B2C52214__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "scadawin.h"
#include "msalmwin.h"
#include "menuwin.h"
#include "webbrowser2.h"
#include "pagectl.h"
#include "childfrm.h"
#include "NavWin.h"
#include "chrgwin.h"


//多窗口控制结构
typedef struct PAGEWIN
{
	HWND hwnd;		//窗口
	int  type;		//窗口类型  0=swin 1=web页面 2=google页面
	CChildFrm *cwin;//窗口地址
	CRect rt;		//标题显示位置
}PAGEWIN;


/////////////////////////////////////////////////////////////////////////////
// CMainWin window

class CMainWin : public CWnd
{
// Construction
public:
	CMainWin();
	CChrgWin cwin;		  //色谱窗口
	CNavWin  nwin;		  //导航器窗口
	pagectl  ptl;		  //页面控制
	MenuWin  mnwin;	      //控制菜单窗口
	MsAlmWin alwin;		  //告警窗口
	int     showmnwin;    //是否显示索引菜单窗口
	PAGEWIN  *page;       //页面地址
	int      pagesum;     //页面个数
	int      curpage;	  //当前页面
	int		 rw,lw;
	//HWND   AvchWnd;			//AVC的窗口
	HWND     hHisWnd;
//	CRect  avcrt;			//avc窗口的位置
//  Attributes
public:

// Operations
public:
	
	int  GetCurpageType();
	///////////////////////////////////////
	void NewEmptywindow();
	int  GetVWIndex(void *pswin);
	int  PSoeSum();
	int  PSoebz();
	int  PCurang();
	int  PN1bz();
	int  PFtype();
	int  PCurrtn();
	int  PCtrtype();
	int  PHisplay();
	int  PDbzt();
	BOOL PHdbok();
	int  PRev();
	int  PDevn(int sel);
	int  PSenflag();
	int  PSen();
	int  PDmflow();
	int  PDgx();
	int  PCurhmi();
	int  PLowf();
	int  PType();
	int  PCursor();
	///////////////////////////////////////
	void DelCurChild();
	void OPenGoogleEarth(char *wwwstr,char *name);
	void OPenWeb(char *wwwstr,char *name);
	void GoToPage(int j);
	void GetPageName(int j,char *txt);
	void ToolBarDgxSel();
	void MoveChildWin();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainWin)
	public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainWin();
	// Generated message map functions
protected:
	//{{AFX_MSG(CMainWin)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFileOpen();
	afx_msg void OnFilePrint();
	afx_msg void OnMovepic();
	afx_msg void OnPartzoom();
	afx_msg void OnZoomio();
	afx_msg void OnZoomnml();
	afx_msg void OnNavigation();
	afx_msg void OnSavetobmp();
	afx_msg void OnSavetojpg();
	afx_msg void OnZoomall();
	afx_msg void OnNormal();
	afx_msg void OnLasthmi();
	afx_msg void OnShowdgx();
	afx_msg void OnSectflw();
	afx_msg void OnDmflow();
	afx_msg void OnCfgattr();
	afx_msg void OnSenopr();
	afx_msg void OnBussen();
	afx_msg void OnLinesen();
	afx_msg void OnGenrev();
	afx_msg void OnGenrevq();
	afx_msg void OnShowcrmap();
	afx_msg void OnBasflow();
	afx_msg void OnShowsys();
	afx_msg void OnStarthis();
	afx_msg void OnEndhis();
	afx_msg void OnPlay();
	afx_msg void OnFastfw();
	afx_msg void OnGototop();
	afx_msg void OnPause();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCtllayer();
	afx_msg void OnFastrev();
	afx_msg void OnRelogin();
	afx_msg void OnTranrev();
	afx_msg void OnSectdf();
	afx_msg void OnMainpage();
	afx_msg void OnShowstf();
	afx_msg void OnRotate();
	afx_msg void OnNormalns();
	afx_msg void OnFullscr();
	afx_msg void OnNofullscr();
	afx_msg void OnLowf();
	afx_msg void OnByqwd();
	afx_msg void OnNexthmi();
	afx_msg void OnNbus();
	afx_msg void OnNflow();
	afx_msg void OnN1all();
	afx_msg void OnNbusf();
	afx_msg void OnNflowf();
	afx_msg void OnN1allf();
	afx_msg void OnSpdown();
	afx_msg void OnSpup();
	afx_msg void OnDefinesect();
	afx_msg void OnPredmjs();
	afx_msg void OnUpdatePredmjs(CCmdUI* pCmdUI);
	afx_msg void OnShadow();
	afx_msg void OnCfgalm();
	afx_msg void OnOpenmenuwin();
	afx_msg void OnDestroy();
	afx_msg void OnNewwindow();
	afx_msg void OnOpensoe();
	afx_msg void OnClosesoe();
	afx_msg void OnGetnewsoe();
	afx_msg void OnPlaysoe();
	afx_msg void OnPausesoe();
	afx_msg void OnSoegototop();
	afx_msg void OnDldljs();
	afx_msg void OnManualdl();
	afx_msg void OnMselline();
	afx_msg void OnDlwf();
	afx_msg void OnBtnreturn();
	afx_msg void OnN1list();
	afx_msg void OnCfgtrans();
	afx_msg void OnZonebar();
	afx_msg void OnSyspiebar();
	afx_msg void OnSvAuto();
	afx_msg void OnUpdateSvAuto(CCmdUI* pCmdUI);
	afx_msg void OnSvwin();
	afx_msg void OnUpdateSvwin(CCmdUI* pCmdUI);
	afx_msg void OnToolHistory();
	afx_msg void OnUpdateToolHistory(CCmdUI* pCmdUI);
	afx_msg void OnChange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int  GetTypeSum(int type);
	void HideChildWin();
	void ShowPageHead(CDC&dc);
	void AddAWindow(HWND hwnd, CChildFrm *cw,int type);
	void Draw(CDC&dc);
	int  wx,wy;
	HWND tmphwnd;
	DWORD fcolor;
	BOOL m_bAutoShow;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINWIN_H__CC47DF28_A08B_4868_B310_1282B2C52214__INCLUDED_)
