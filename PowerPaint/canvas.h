#if !defined(AFX_CANVAS_H__E7F9278F_8172_470A_BE70_BB57A9795186__INCLUDED_)
#define AFX_CANVAS_H__E7F9278F_8172_470A_BE70_BB57A9795186__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// canvas.h : header file
//
#include "jhsyslibl.h"
#include "ptdefine.h"

/////////////////////////////////////////////////////////////////////////////
// canvas window

class canvas : public CWnd
{
// Construction
public:
	canvas();
	CDIB mtp;				//临时绘图用
	CDIB mat;				//动态绘图
//	NaviDlg nwin;			//导航器
	int    tptsum;			//tpt的点数
	CPoint tpt[1000];		//最大400点
	int  drawbg;			//是否需要画背景
	int  wx,wy;				//屏幕的宽高
	int  xmax,ymax;			//最大可移动象素
// Attributes
public:
	bool GetAAttr(int type,N_BASATTR&atr);
	void AddDZone(int ptsum,DPOINT *pt1);
	bool AddDLine(int ptsum,DPOINT *pt1);
	bool AddCLine(int ptsum,DPOINT *pt1);
	void EditAttr();
	void Addegpr(BYTE no);
	void AddegpYb();
	void LayerChange();
	void Addspic();
	void DrawChange(int funct);
	void ShowObjsum();
	void PageChange();
	void ComputZCenter();
// Operations
public:
	void DrawShow();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(canvas)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~canvas();

	// Generated message map functions
protected:
	//{{AFX_MSG(canvas)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnZoomnml();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnNormal();
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnAlignDown();
	afx_msg void OnAlignDstx();
	afx_msg void OnAlignDsty();
	afx_msg void OnAlignHg();
	afx_msg void OnAlignLeft();
	afx_msg void OnAlignRight();
	afx_msg void OnAlignUp();
	afx_msg void OnAlignWd();
	afx_msg void OnEditAttr();
	afx_msg void OnConnectDev();
	afx_msg void OnEditDev();
	afx_msg void OnEditSft();
	afx_msg void OnAboutSft();
	afx_msg void OnDbsource();
	afx_msg void OnUp();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnGototop();
	afx_msg void OnGotobuttom();
	afx_msg void OnCurnml();
	afx_msg void OnSelelebus();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnAddlinedot();
	afx_msg void OnSublinedot();
	afx_msg void OnZmin();
	afx_msg void OnZmout();
	afx_msg void OnAvccfg();
	afx_msg void OnDbxtoline();
	afx_msg void OnDbxtocl();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ChkMousemove(CPoint point);
	void DrawingLine(HDC hdc,int dx,int dy);
	void MoveDrawLine(CPoint pt);
	void ChangeShowRT();
	void SelMeterDbs(BASE0 &bs);
	void PasteObj(CPoint point);
	CMenu *RMenuSet();
	void AddRegon();
	void ShowB(HDC hdc,CRect rt);
	void ShowA();
	void ZoomInOut();
	void MoveObject(int mx, int my);
	void MouseMove(CPoint point);
	void MovePic(CPoint point);
	bool CreateNPOINT4dot(DPOINT *pt,int mode=0);
	void AddMtText();
	void AddSysPie();
	void AddZone();
	void AddReservoir();
	void AddPctPie();
	void AddFlash();
	void AddActObj();
	void AddBus();
	void AddFlow();
	void AddConLine();
	void AddSelfCtl();
	void AddPush();
	void AddScrText();
	void AddGifAnl();
	void AddTime();
	void AddDate();
	void AddPie();
	void AddBar();
	void AddAnalog();
	void AddPath();
	void AddImage();
	void AddMeter1();
	void AddMeter2();
	void AddMeter3();
	void AddMeter4();
	void AddTable();
	void AddCoordinate();
	void AddEgpmb();
	void AddEsite();
	void AddText();
	void AddGlass();
	void AddArrow();
	void AddArc();
	void AddSin();
	void AddHSin();
	void AddCircle();
	void AddRect();
	void AddDbx(int type);
	void PartZoom(CRect rt);
	void MouseLBUp(CPoint point);
	void BrightImg(CPoint point);
	void BrushImage(CPoint point);
	void TranImage(CPoint point);
	void CutImage(CPoint point);
	void ClearImg(CPoint point);
	void AddPoint(CPoint point);
	
	void DrawXorRect(CRect rt);
	void MouseLBDown(CPoint point);
	void SetZoominfo();
	void ZoomChange();
	void Show(HDC hdc,CRect rt);
	void ComputMaxXY();
	void SizeChange(int cx, int cy);
	CPoint pt1,pt2,oldpt,mpt,rpt1,rpt2;
	CRect  oldrt;
	double  vx,vy;			//放大中心点
	CMenu pmenu;			//右键菜单
	CMenu pmenu1;			//右键菜单1
	CMenu pmenu2;			//右键菜单2
	CMenu pmenu3;			//右键菜单3
	CMenu pmenu4;			//右键菜单4
	CMenu pmenu5;			//右键菜单5
	CMenu pmenu6;			//右键菜单5
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CANVAS_H__E7F9278F_8172_470A_BE70_BB57A9795186__INCLUDED_)
