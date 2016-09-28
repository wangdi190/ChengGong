#if !defined(AFX_DBEDIT_H__33841F2A_D123_43EA_9A9C_FCE90FE96C5E__INCLUDED_)
#define AFX_DBEDIT_H__33841F2A_D123_43EA_9A9C_FCE90FE96C5E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dbedit.h : header file
//
#include "lib.h"
#define  CHANGELINE1 3100
#define  INSERTREC1  3302
#define  DELETEREC1  3303
/////////////////////////////////////////////////////////////////////////////
// dbedit window

class dbedit : public CWnd
{
// Construction
public:
	dbedit();
	int  field_size;		//记录域字节大小
	int  field_count;		//域总数
	dFIELD  *dfield;		//最大128个域
	WORD    *fwd;			//记录域坐标
	int  record_count;		//记录数
	char *data;				//数据库指针
	CImageList  *img;		//图形指针
	DWORD fcolor;			//表面颜色
	int wx,wy;				//窗口的高宽
	int dx,dy;				//x,y方向偏移量
	int maxyl;				//Y方向的最大显示行数
	CFont font;
	int cursor,curfld;
	HCURSOR hcur;
	CPen  pen;
	int dnbz;
	int oldx;
	CPoint oldp1;

	int  maxr,recu;			//最大记录数和已使用记录数
// Attributes
public:
	void SetImageList(CImageList *imglist);
	int  AddItemType(char *name,BYTE type,BYTE strmax,BYTE width,char image,char lindex,BYTE xs,int twidth);
	void SetInitPara(char *buff, int rsize,int recmax,int recused=0);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(dbedit)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	void UsedChanged(int recused);
	void SetScroll();
	void reset();
	virtual ~dbedit();

	// Generated message map functions
protected:
	//{{AFX_MSG(dbedit)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void DrawLine(HDC hdc,int x1,int y1,int x2,int y2,DWORD color);
	bool GetEditPos(CPoint point,int &x,int &y);
	void DrawLeftTitle(CDC&dc,int y);
	void drawxorline(int x); //移动竖条时画线
	void GetCursor(CPoint point);
	void ShowItem(CDC&dc,int x,int y,DWORD color);
	void IntTostring(char *str, int val, int w);
	int  GetFieldOffset(int field); //返回域偏移量
	void GetFieldString(int y, int field, char *str);
	CRect GetItenRect(int x,int y);
	void DrawItemTitle(CDC &dc, int j);
	void ShowFrame(CDC&dc);
	void ComputWidth();
	DWORD  GetColor(int y);
	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBEDIT_H__33841F2A_D123_43EA_9A9C_FCE90FE96C5E__INCLUDED_)
