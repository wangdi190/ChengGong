#if!defined(__SPLITASS_H)
#define __SPLITASS_H
//切分窗口伴侣
//CJH 1999年11月设计

class SplitAss{
public:
	SplitAss();
	~SplitAss();
	void Create(CWnd *cwnd,CWnd *cwnd1,CWnd *cwnd2,char *text=NULL,int style=0);
	void SetInitPosition(int pos);
	void OnMouseMove(CPoint point);
	void OnLButtonDown(CPoint point);
	void OnLButtonUp(CPoint point);
	void OnSize(int cx,int cy);
	void OnPaint(CDC&dc);
	CWnd *pwin;       //所对应的主窗口
	CWnd *wnd1,*wnd2; //子窗口
private:
	void drawxorline(CPoint point);
	void ComputRect();//计算两个矩形位置
	CRect rw1,rw2;    //两个窗口的矩形
	int  style;       //0=上下切分 1=左右切分
	char titlebz;     //标题标志
	char title[45];   //标题字符
	int  position;    //当前切分位置
	int  wx,wy;		  //父窗口的大小
	CPoint opos;
	CPen pen;
	CFont font;
	int  dnbz;		  //压下鼠标标志
	int  cursor;      //当前鼠标
	int  closebz;     //关闭标志
	HCURSOR hcurx,hcury;
};

#endif