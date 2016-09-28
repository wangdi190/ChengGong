#if !defined(AFX_WORKWIN_H__8AA427DC_119C_434C_BF81_CF5B8E7F67D5__INCLUDED_)
#define AFX_WORKWIN_H__8AA427DC_119C_434C_BF81_CF5B8E7F67D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// workwin.h : header file
//
typedef struct MANYWIN{
	CWnd *wnd;    //窗口
	int  height;  //高度
	int  width;	  //宽度
	int  show;    //是否显示
}MANYWIN;

#include "canvas.h"
#include "pagectl.h"
/////////////////////////////////////////////////////////////////////////////
// workwin window

class workwin : public CWnd
{
// Construction
public:
	workwin();

	canvas cvs;			//画布
	//CToolBar tb1,tb2;	//工具条
	pagectl  ptl;		//页面控制
	//MANYWIN  win[4];	//四个窗口统一管理
	int wx,wy;
// Attributes
public:
	void OnFileSave();
// Operations
public:
	void SetTitlename();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(workwin)
	public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	void RecFileOkOpen(char *filename);
	void Relayer();
	virtual ~workwin();

	// Generated message map functions
protected:
	//{{AFX_MSG(workwin)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnFileOpen();
	afx_msg void OnFileNew();
	afx_msg void OnNormal();
	afx_msg void OnMovepic();
	afx_msg void OnPartzoom();
	afx_msg void OnZoomio();
	afx_msg void OnLineAdddot();
	afx_msg void OnLineSubdot();
	afx_msg void OnCutline();
	afx_msg void OnBindline();
	afx_msg void OnClearimg();
	afx_msg void OnCutimg();
	afx_msg void OnTranimg();
	afx_msg void OnPaintimg();
	afx_msg void OnBrightimg();
	afx_msg void OnSetregon();
	afx_msg void OnCutregon();
	afx_msg void OnLine();
	afx_msg void OnRect();
	afx_msg void OnCircle();
	afx_msg void OnHsin();
	afx_msg void OnSin();
	afx_msg void OnCoord();
	afx_msg void OnArc();
	afx_msg void OnArrow();
	afx_msg void OnGlass();
	afx_msg void OnCbar();
	afx_msg void OnText();
	afx_msg void OnEsite();
	afx_msg void OnEgpmb();
	afx_msg void OnTable();
	afx_msg void OnImage();
	afx_msg void OnPath();
	afx_msg void OnAnalog();
	afx_msg void OnBar();
	afx_msg void OnPie();
	afx_msg void OnDate();
	afx_msg void OnTime();
	afx_msg void OnGifanl();
	afx_msg void OnScrtext();
	afx_msg void OnPush();
	afx_msg void OnSelfctl();
	afx_msg void OnConline();
	afx_msg void OnFlow();
	afx_msg void OnBus();
	afx_msg void OnActobj();
	afx_msg void OnFlash();
	afx_msg void OnEditCut();
	afx_msg void OnGototop();
	afx_msg void OnGotobuttom();
	afx_msg void OnEditUndo();
	afx_msg void OnStraight();
	afx_msg void OnImgstratch();
	afx_msg void OnFilterGray();
	afx_msg void OnFilterRev();
	afx_msg void OnFilterSmoth();
	afx_msg void OnFilterWl();
	afx_msg void OnTranMir();
	afx_msg void OnTranUd();
	afx_msg void OnBdBlack();
	afx_msg void OnBdBlk();
	afx_msg void OnBdBright();
	afx_msg void OnCopytoclib();
	afx_msg void OnPasteclib();
	afx_msg void OnCutnouse();
	afx_msg void OnSetpage();
	afx_msg void OnDrawattr();
	afx_msg void OnVlcolor();
	afx_msg void OnFillptn();
	afx_msg void OnFillcolor();
	afx_msg void OnShowguide();
	afx_msg void OnGuide();
	afx_msg void OnEgptosgl();
	afx_msg void OnResetsite();
	afx_msg void OnShowsite();
	afx_msg void OnNocondev();
	afx_msg void OnNocdev();
	afx_msg void OnFileSaveAs();
	afx_msg void OnAddpage();
	afx_msg void OnAddlayer();
	afx_msg void OnDelcurpage();
	afx_msg void OnDelcurlayer();
	afx_msg void OnPctpie();
	afx_msg void OnTosqrt();
	afx_msg void OnMeter1();
	afx_msg void OnMeter2();
	afx_msg void OnMeter3();
	afx_msg void OnMeter4();
	afx_msg void OnUpdateMeter1(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMeter2(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMeter3(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMeter4(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAnalog(CCmdUI* pCmdUI);
	afx_msg void OnUpdateActobj(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePctpie(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBar(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConline(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFlow(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBus(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePie(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDate(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTime(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGifanl(CCmdUI* pCmdUI);
	afx_msg void OnUpdateScrtext(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePush(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSelfctl(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFlash(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCoord(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTable(CCmdUI* pCmdUI);
	afx_msg void OnUpdateText(CCmdUI* pCmdUI);
	afx_msg void OnUpdateImage(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEsite(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEgpmb(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateArrow(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCircle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateArc(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHsin(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSin(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGlass(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePath(CCmdUI* pCmdUI);
	afx_msg void OnReservoir();
	afx_msg void OnUpdateReservoir(CCmdUI* pCmdUI);
	afx_msg void OnPolyzone();
	afx_msg void OnUpdatePolyzone(CCmdUI* pCmdUI);
	afx_msg void OnDrawrt();
	afx_msg void OnUpdateDrawrt(CCmdUI* pCmdUI);
	afx_msg void OnModifont();
	afx_msg void OnUpdateModifont(CCmdUI* pCmdUI);
	afx_msg void OnDbxtozone();
	afx_msg void OnUpdateDbxtozone(CCmdUI* pCmdUI);
	afx_msg void OnInsvg();
	afx_msg void OnMultext();
	afx_msg void OnUpdateMultext(CCmdUI* pCmdUI);
	afx_msg void OnSyspie();
	afx_msg void OnInsvgBat();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void RefreshCanvas();
	void ProcImg(int method, BYTE param=0);
	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORKWIN_H__8AA427DC_119C_434C_BF81_CF5B8E7F67D5__INCLUDED_)
