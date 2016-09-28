#if !defined(AFX_OBJWIN_H__2897F185_57B3_4D45_8BD7_337ED1C32907__INCLUDED_)
#define AFX_OBJWIN_H__2897F185_57B3_4D45_8BD7_337ED1C32907__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Objwin.h : header file
//
#include "editctl.h"
#include "litemctl.h"
#include "lib.h"
/////////////////////////////////////////////////////////////////////////////
// Objwin window
typedef struct _LISTITEM1{
  int itemsum;        //单项数量	最大24项
  LISTNAME name[24];  //字符串资料
}LISTITEM1;


class Objwin : public CWnd
{
// Construction
public:
	Objwin();
	editctl  ed;		   //编辑
	litemctl li;           //下拉式组合框
// Attributes
public:

// Operations
public:
	void SetObjtCursorPos();
	BOOL Createtun(DWORD dwStyle,CWnd* pParentWnd);
	void DataChange();
	int  ADDSubListItem(int index,char *str);
	void SetListSum(int sum);
	void HideEdit();
	void SetCaptionName(char *name);
	int  AddEditItem(int y,void *addr,char type=EDIT_STR,
		   BYTE strmax=25,char canedit=1,char index=-1);
	int  SetLineName(char *name,int img,int index,int w);
	int  SetColLinNum(int y);
	void SetScrollBar();
	void ReSet();
	void OnEditCopy();
	void OnEditPaste();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Objwin)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~Objwin();

	// Generated message map functions
protected:
	//{{AFX_MSG(Objwin)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void GetItemString(int index, int item, char *str);
	int  editzt;           //编辑状态
	int  dbindex;          //当前编辑的数据点索引
	void editoperate(CPoint point);
	int  IsFunctArea(CPoint point);
	int  cursor;
	void Geteditstring(int y,char *str,int&caned);
	void ShowItem(CDC&dc,int y);
	bool Geteditrect(int y,CRect&rt);
	int  Getmaxheigh();
	int  Getmaxwidth();
	int  nmw;
	int  index; //当前改变光标的列
	int  dnbz;  //光标改变后，压下左键标志
	CPoint dnpt;
	CRect dnrt;
	int  wx,wy; //当前窗口大小
	void draw3dtitle(CDC&dc,CRect&rt,char *str,UINT style);
	int  dy;    //Y方向偏移量,代表行偏移
	int  dx;    //X方向偏移量,代表列偏移
	void ShowTitle(CDC&dc);
	CFont font;
	CFont font1;
	CPen  pen;
	CBrush brush,brush1;
	DBEDIT edb[MAXITEM];
	ENAME  enm[MAXENM];
	char   title[256];     //标题名称
	char   tenable;        //是否有标题
    int    esum,tsum;      //定义当前编辑项
	int    maxy;		   //X方向最大列和Y方向最大行
	LISTITEM1 litem[24];    //可支持24组选项
	int  lsum;             //选项总数
	
	CImageList limg;	   //小图标
	CRect oldrt;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OBJWIN_H__2897F185_57B3_4D45_8BD7_337ED1C32907__INCLUDED_)
