#if !defined(AFX_JHSYSLIBL_H__INCLUDED_)
#define AFX_JHSYSLIBL_H__INCLUDED_



//-------------------------------------------------------------------------
//jhsyslib的静态库版本,对应库为jhsyslibL.lib
//-------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////
#define  dpi  6.28318530
#define  mpi  3.14159265
#define  hpi  1.57079632
#define  MAXCONTOUR    1200

////////////////////////////////////////////////////////////////////////
typedef struct COLORPAL{ //颜色表
	DWORD color;         //颜色
	BYTE r,g,b;			 //颜色分量
}COLORPAL;
typedef struct CTR_COLOR{		//等高线颜色定义
	float value[5];				//对应的5个值
	DWORD color[5];				//对应的五个颜色
	char  unit[12];				//单位pu,h.mw
	char  vhow;					//取值约定
	BYTE  emptyfill;			//空白填充
}CTR_COLOR;
//////////////// 定义双精度浮点点坐标和矩形坐标//////////////////////////////
typedef struct _DPOINT{		 //点
	double x;				 //X坐标
	double y;				 //Y坐标
}DPOINT;

typedef struct _DRECT{		//矩形
	double left;			//左上角X坐标
	double top;				//左上角y坐标
	double right;			//右下角X坐标
	double bottom;			//右下角Y坐标
}DRECT;
/////////////////////////////////////////////////////////////////////////////
//-----以下函数是特殊处理的绘图函数----------------------------------------------------------------
//可以在任何HDC上绘制
void    GLLineXor(HDC hdc,int x1,int y1,int x2,int y2,DWORD color=0xffffff,int w=1);
void	GLCircle(HDC hdc,RECT rt,int width,DWORD color);
int     GetDirPoint(DPOINT ps,DPOINT pe,DPOINT *pt,int width);
int		GetWLine4Point(DPOINT ps,DPOINT pe,DPOINT *pt,int width);
void    GLLine(HDC hdc,int x1,int y1,int x2,int y2,DWORD color,int width=1);
void    GLEllipse(HDC hdc,int x1,int y1,int x2,int y2,DWORD color);
void    GL3DRect(HDC hdc,RECT rt,DWORD color);
void    GLRectc(HDC hdc,RECT rt,DWORD color1,DWORD color2,WORD style);
void    GLPolygonc(HDC hdc,POINT *point,int count,DWORD color1,DWORD color2,WORD style);
void    GLEllipsec(HDC hdc,RECT rt,DWORD color1,DWORD color2,WORD style);
SIZE    GLDGetTextSize(HDC hdc,LOGFONT *font,char *text);
void    GLDrawLine(HDC hdc,int x1,int y1,int x2,int y2,BYTE width,DWORD color);
void    GLDrawDbx(HDC hdc,int num,POINT *pt,BYTE width,DWORD color);
void    GLDrawOutLine(HDC hdc,int num,POINT *pt,BYTE width,DWORD color);
void    GLRect(HDC hdc,int x1,int y1,int x2,int y2,int width,DWORD color);
void    GLDDraw3DRect(HDC hdc,RECT rt,DWORD color1=0,DWORD color2=0xffffff,int width=1);
void    GLDDrawText(HDC hdc,RECT *rt,LOGFONT *lf,char *text,DWORD color,int style,DWORD align=DT_LEFT);
void	GLDrawArc(HDC hdc,RECT drt,DWORD color,double start,double end,BYTE w);
void	GLDrawArcBand(HDC hdc,DPOINT cpt,double r1,double r2,double as,double ae,DWORD color);

////////////////24位真彩结构定义//////////////////////////////////////////////////
typedef struct _RGB24{
	BYTE b,g,r;
}RGB24;
/////////////////////////////////////////////////////////////////////////////
class   CIPoint:public tagPOINT
{
public:
	CIPoint();
	CIPoint(int initX, int initY);
	CIPoint(POINT initPt);
	void Offset(int xOffset,int yOffset);
	void Offset(POINT point);
	void Offset(SIZE size);
	void operator = (CIPoint point);
	void operator -=(CIPoint point);
	void operator +=(CIPoint point);
	CIPoint operator - (CIPoint point);
	CIPoint operator + (CIPoint point);
	bool operator == (CIPoint point);
};
//////////////////////////////////////////////////////////////////////////////
class   CDPoint:public DPOINT
{
public:
	CDPoint();
	CDPoint(double initX, double initY);
	CDPoint(DPOINT initPt);
	void Offset(double xOffset,double yOffset);
	void Offset(DPOINT point);
	void ActPtToScr(double zoomm);
	void ScrPtToAct(double zoom);
	void GetPOINT(POINT&pt);
	void SetPOINT(POINT pt);
	void operator = (CDPoint point);
	void operator -=(CDPoint point);
	void operator +=(CDPoint point);
	CDPoint operator - (CDPoint point);
	CDPoint operator + (CDPoint point);
	bool operator == (CDPoint point);
};
//////////////////////////////////////////////////////////////////////////////
class   CIRect:public tagRECT 
{
public:
	CIRect();
	public:
	POINT CenterPoint();
	void SetRectEmpty();
	void NormalizeRect();
	bool PtInRect(POINT point);
	bool IsRectEmpty();
	int  Height();
	int  Width();
	void SetRect(int x1, int y1, int x2, int y2);
	void SetRect(POINT topLeft, POINT bottomRight);
	void Offset(int dx,int dy);
	CIRect(int Left,int Top,int Right,int Bottom);
	void operator =(CIRect &rt);
	void operator &=(CIRect &rt);
	void operator |=(CIRect &rt);
};
///////////////////////////////////////////////////////////////////////////
class   CDRect:public DRECT  
{
public:
	CDRect();
	virtual ~CDRect();
	public:
	DPOINT CenterPoint();
	void SetRectEmpty();
	void ActRtToScr(double zoom);
	void ScrRtToAct(double zoom);
	void GetDRECT(DRECT &rt);
	void GetRECT(RECT&rt);
	void NormalizeRect();
	BOOL PtInRect(CDPoint point);
	BOOL PtInRect(POINT point);
	BOOL IsRectEmpty( );
	double Height();
	double Width();
	void Offset(double dx,double dy);
	void Offset(int dx,int dy);
	CDRect(double ILeft,double ITop,double IRight,double IBottom);
	void operator =(CDRect &rt);
	void operator &=(CDRect &rt);
	void operator |=(CDRect &rt);
	void SetCRect(RECT &rt);
	void SetDRECT(DRECT &rt);
};

/////////////////////////////////////////////////////////////////////
//处理图形DC的类ImageDC
class   ImageDC  
{
public:
	void CreateRGN(BYTE index);
	void Show(HDC hdc,int x,int y,int w=0,int h=0);
	void FreeMem();
	void Create(char *sdib);
	ImageDC();
	virtual ~ImageDC();
	HDC m_hDC;              //HDC
	BITMAPINFO *bi;			//图形信息
	char    *bnf;			//BITMAPINFO缓冲区
	void    *dib;			//图形地址
	HBITMAP hbitmap;		//位图句柄
	int     sPerline;		//每行字节数
	int     nWidth,nHeight;	//宽度、高度
	HRGN    hrgn;	        //图形部分的区域
	BYTE    tranflag;		//透明标志
	BYTE    colorindex;	    //透明索引
private:
	int colornums(int bits);
};
//////////////////////////////////////////////////////////////
//处理动画GIFAnm
struct IMGFRM{
	int    x,y;        //绘图的X,Y位置
	int    w,h;		   //宽高
	BYTE   disposal;
	BYTE   tranflag;   //透明标志
	BYTE   tranIndex;  //透明颜色
	WORD   delay;	   //延迟时间
	int    count;	   //计数器
	ImageDC *imgdc;    //图片
};


class   CGIFAnm  
{
public:
	bool CanShow();
	void FreeMem();
	void Show(HDC hdc,int x,int y,int w=0,int h=0);
	void ShowSel(HDC hdc,int n, int x, int y, int w=0, int h=0);
	void ReadGifFile(char *filename);
	CGIFAnm();
	virtual ~CGIFAnm();
	IMGFRM frm[60];      //60帧画面
	int frmsum;          //当前画面数
	int last;			 //上一幅
	int curfrm;			 //当前帧
	WORD  width,height;  //动画占用的宽度高宽
	HDC m_hDC;              //HDC
	BITMAPINFO bi;			//图形信息
	void    *dib;			//图形地址
	HBITMAP hbitmap;		//位图句柄
	int     sPerline;		//每行字节数
private:
	void CreateDDB_buf();
};
//////////////////////////////////////////////////////////////////////////////////////////
class   JpegFile 
{
public:
	char *m_dib;         //设备无关位图
	BYTE *rgbbuf;		 //RGB图象
	int  width,height;	 //图象高宽
	int  bytes_per_line;  //每行字节数
public:
	void FreeMem();
	void read(char * fileName);

	static BOOL RGBToJpegFile(char * fileName,BYTE *dataBuf,UINT width,						
							UINT height,BOOL color,int quality);					
	static BOOL GetJPGDimensions(char * fileName,UINT *width,UINT *height);
	static BYTE * MakeDwordAlignedBuf(BYTE *dataBuf,UINT widthPix,UINT height,
									 UINT *uiOutWidthBytes);
	static BYTE *RGBFromDWORDAligned(BYTE *inBuf,UINT widthPix,UINT widthBytes,UINT height);
	static BOOL VertFlipBuf(BYTE * inbuf,UINT widthBytes,UINT height);							// height
	static BOOL MakeGrayScale(BYTE *buf,UINT widthPix,UINT height);	
	static BOOL BGRFromRGB(BYTE *buf,UINT widthPix,UINT height);								// lines
	JpegFile();
	~JpegFile();
private:
	void RGBToDIB();
};


///////////////////////////////////////////////////////////////////
//打开所有图形的类CMImage

class   CMImage : public ImageDC  
{
public:
	bool ReadImage(char *filename);
	CMImage();
	virtual ~CMImage();

private:
	void LoadMor(char *filename);
	void LoadPcx(char *filename);
	void LoadGif(char *filename);
	void LoadJpeg(char *filename);
	int GetTypeOfImg(char *filename);
};
///////////////////////////////////////////////////////////////////////
//基本内存DC类
class CBMemDC  
{
public:
	CBMemDC();
	virtual ~CBMemDC();
	void Create(int width,int height);
	void SizeChange(int width,int height);
public:
	//------绘图操作绘图操作----------------------------------------------------------------------------------
	void CTextOut(char *str,RECT drt,LOGFONT *lf,DWORD color,int style,DWORD align=DT_LEFT) ;
	void CLine(POINT pt1,POINT pt2,DWORD color);
	void CDLine(DPOINT p1,DPOINT p2,DWORD color);
	void CRectc(RECT rt,DWORD color1,DWORD color2,WORD style);
	void CDrawOutLine(POINT *point,int count,DWORD color);
	void CDrawDbx(POINT *point,int count,DWORD color);
	void CDrawDbx(DPOINT *point,int count,DWORD color);
	void CEllipsec(RECT rt,DWORD color);
	void CEllipsec(DRECT rt,DWORD color);
	void CCircle(RECT rt,DWORD color);
	void CCircle(DRECT rt,DWORD color);
	void CDrawHSin(RECT rt,DWORD color,int xy,int pe,int mode);
	void CDrawSin(RECT rt,DWORD color,int xy,int pe,int startdeg);
	void CDrawArc(RECT rt,DWORD color,double s,double e);
	void GLDrawArcBand(DPOINT cpt,double r1,double r2,double as,double ae,DWORD color);
	void CDrawArrow(DPOINT ps,DPOINT pe,DWORD color,int width);
	void CPolygonc(POINT *point,int count,DWORD color);
	void DrawBmp(HBITMAP hbmp,int xrc=0, int yrc=0,int xto=0,int yto=0,int w=0, int h=0,int rop=SRCCOPY);
	void CDrawRect(RECT drt,int Penw,DWORD Pcolor);                  //用特定颜色画一个空矩形
	void CDraw3DRect(RECT drt,DWORD color1,DWORD color2);            //画3D矩形
	void CDraw3dRectP(POINT *pt,DWORD color);						 //通过4点画3D矩形
	void CDraw3dRectP(POINT *pt,DWORD c1,DWORD c2);					 //通过4点画3D矩形
	void CDrawGlass(RECT rt,DWORD bcolor,DWORD fcolor,BYTE oline,BYTE dp);		  //画玻璃层
	void CDrawPolyGlass(POINT *pt,int ptsum,DWORD bcolor,DWORD fcolor,BYTE oline,BYTE dp);
	void CDrawDotm(DPOINT *point,int count,DWORD color);
	void CDrawOutDLine(DPOINT *point,int count,DWORD color);
	void CDrawPoly(DPOINT *pt,int ptsum,DWORD lcolor,DWORD fcolor,int fill,int close);
	void CDrawDbxW(POINT *point,int count,DWORD color,int width);
	void StrechImg(CBMemDC &mdc,RECT rt,int shadow);
	void  SmoothPattern(BYTE *sdata,RECT rt,int sw,int sh,DWORD color,int ss);
	RGB24 *GetDibAddr(int x,int y);
	void CSetLineStyle(int LStyle);
	int  CGetLineStyle();
	//--------基本平面绘图操作--------------------------------------------------------
	void FillBG(DWORD color);
	void FillSolidRect(RECT rt,DWORD color);
	void BitBltRect(HDC hdc,RECT rts,RECT rtd);
	void BitBlt(HDC hdc,RECT rt,DWORD dwRop=SRCCOPY);
	void TranImage(DWORD color,DWORD Tolerance);
	void CutNoUse();
	bool GetPixel(int x,int y,RGB24&color);
	void SetPixel(int x,int y,RGB24 color);
	void FloodFill(POINT pt);
	void PenBrush(int x,int y,int ra,DWORD color);
	void AddBrushDot(int x,int y,int k);
	void AddPenBrush(int x,int y,int ra);
	void ShadowRect(RECT rt,int style);
	void CopyImg(CBMemDC&mdc,RECT drt);
	void TranImg(CBMemDC&mdc,RECT drt,DWORD color);
	void TranImgShadow(CBMemDC&mdc,RECT drt,int shadow=0);		//透明+阴影
	void FillImg(CBMemDC&mdc);									//用mdc来填充
	void CopyImgPercent(CBMemDC&mdc,RECT drt,BYTE depth);		//按百分比传输(半透明)
	void LightDot(int x,int y,int mode,int repeat);
	//---------------------------------------------------------------------------------
	void SetRGB24(DWORD color);
	void DrawSTyleDot();
	void QDrawDot();
	void QLine(POINT p1,POINT p2,DWORD color); //画基本线（宽度=1）
	void FillPoly(POINT *pt,int ptsum,DWORD color);
	void DrawDot();
	bool PTIsInDC(POINT pt);
	void DpToIp(DPOINT &in,POINT &out);
	void FillDbx(DPOINT *pt,int ptsum,DWORD lcolor,DWORD fcolor,int border=1);
	//---------------------------------------------------------------------------------
	HDC m_hDC;              //HDC
	BITMAPINFO bi;			//图形信息
	void    *dib;								//图形地址
	HBITMAP hbitmap;							//位图句柄
	int		dibsize;					//DIB字节数
	int     sPerline;							//每行字节数
	int     nWidth,nHeight;						//宽度、高度
	//---------------------------------------------------------------------------------
	double	tlx,tly;
	RGB24	tlrgb;
	int		linestyle;			//0=实线 1=点线 2=点划线
	int     lstym,lstya,lstyb;	//画各种线性所需要的参数
private:
	void CCirclei(DRECT rt);
	void CEllipseci(DRECT rt);
	void QDrawLineX(double xs,double y,double xe,int yoff);
	void QDrawLineY(double ys,double x,double ye,int xoff);
	void ShadowPattern(BYTE *sdata,RECT rt,int sw,int sh);
	void SubBright(int x,int y,BYTE *brush);
	void AddBright(int x,int y,BYTE *brush);
	void DrawBrushDot(int x,int y,int k,RGB24 rgb);
};

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
class   CMemDC : public CBMemDC 
{
public:
	CMemDC();
	virtual ~CMemDC();
public:							
	void ReadImageFile(char *filename);			//读入图形文件	
};
///////////////////////////////3D绘图处理类/////////////////////////////////////////////////////
//--------------C D I B-------------------------------------
class   CDIB : public CBMemDC
{
public:
	CDIB();
	~CDIB();
	//----------外部公用函数--------------------------------
	void CopyDIB(CDIB&sdib);  //拷贝DIB的图象到本CDIB（两个CDIB必须一样的宽和高）
	void TranDIB(CDIB&sdib,DWORD trancolor);     //透明DIB的图象到本CDIB（两个CDIB必须一样的宽和高）
	//-----------一下函数用于旋转和俯视3D显示---------------
	bool D3MPie(CDRect &rt,DWORD *color,double *value,DPOINT  *textcpt,int num,DWORD linecolor,bool line,int dx,int dy,double high=0);
	void D3GenPie(DRECT rt,double rp,DWORD color,int dx,int dy,double high=0);
	void D3DrawRectBarj(DPOINT *pt,double h1,double h2,DWORD color,int dx,int dy,int drwup=0);
	void D3DrawRectBar(DPOINT *pt,double h1,double h2,DWORD color,int dx,int dy,int drwup=0);
	void D3DrawRectBar(DPOINT *pt,double h1,double h2,DWORD color,DWORD topcolor,int sta,int dx,int dy,int drwup=0);
	void D3DrawTaperj(DRECT rt,double h1,DWORD color,int dx,int dy);
	void D3DrawTaper(DRECT rt,double h1,DWORD color,int dx,int dy);
	void D3DrawTaperu(DRECT rt,double h1,DWORD color,int dx,int dy);
	void D3DrawTaperuj(DRECT rt,double h1,DWORD color,int dx,int dy);
	void D3DrawBar2j(DRECT rt,double h1,double h2,DWORD color,int dx,int dy,int drwup=0);
	void D3DrawBar2(DRECT rt,double h1,double h2,DWORD color,int dx,int dy,int drwup=0);
	void D3DrawFlow(DPOINT *pt,int ptsum,int start,int arrow,int size,int dis,DWORD color1,DWORD color2,int dx,int dy,double high=0);
	void D3FlowLowf(DPOINT *pt,int ptsum,float *Vlf,int  flen,DWORD color,int dx,int dy,double high=0);
	void D3Draw2Pie(CDRect &rt,DWORD c1,DWORD c2,DWORD c3,double pw,int dx,int dy,double high=0);
	void D3Draw2Pie1(CDRect &rt,DWORD c1,DWORD c2,DWORD c3,double pw,int dx,int dy,double high=0);
	void D3DrawPoly(DPOINT *pt,int ptsum,DWORD lcolor,DWORD fcolor,int fill,int close,int dx,int dy,double high=0);
	void D3DrawArrow(DPOINT p1,DPOINT p2,DWORD color,int width,int dx,int dy,double high=0);
	void D3Ellipsec(DRECT rt,DWORD lcolor,DWORD fcolor,int dx,int dy,double high=0);
	void D3Circle(DRECT rt,DWORD color,int dx,int dy,double high=0);
	void D3DrawHSin(DRECT rt,DWORD color,int xy,int pe,int dx,int dy,int mode=0,double high=0);
	void D3DrawSin(DRECT rt,DWORD color,int xy,int pe,int dx,int dy,int startdeg=0,double high=0);
	void D3DrawArc(DRECT rt,DWORD color,short s,short e,int dx,int dy,double high=0);
	void D3ShowImg(CBMemDC &mdc,RECT rt,int dx,int dy,double high=0);
	//---------------------------------------------------------------------------------------------------------
	HRGN Get3dTaperRGN(CDRect rt,int h1);
	HRGN Get3dTaperuRGN(CDRect rt,int h1);
	HRGN Get3dBarRGN(CDRect rt,int h1);
	HRGN Get3dRectBarRGN(CDRect rt,int h1);
	double GetDeep(double x,double y);
	//---------------------------------------------------------------------------------------------------------
	void RotateDPOINT(double &x,double &y);
	void RotateDPOINT(DPOINT *pt,int ptsum);
	void LookDownAPt(double &x,double &y,double h);
	void LookDownMPt(DPOINT *pt,int ptsum,double h);
	void Set3DEnv(int angle,double w,double h,int ld);
	void DPtToScrPt(double &x,double &y,int dx,int dy,double h=0);
	void DPtToScrPt(DPOINT *in,DPOINT *out,int ptsum,int dx,int dy,double h=0);
	void DPtToScrPt(DPOINT *in,POINT *out,int ptsum,int dx,int dy,double h=0);
	void DPtToActPt(DPOINT *in,DPOINT *out,int ptsum,int dx,int dy,double h=0);
private:
	//-----------3D环境参数-----------------------------
	double d3zw,d3zh;		//当前的图形宽、高
	double d3x,d3y;			//中心点
	int	   d3angle;			//旋转角度0-360;
	int    d3lookdown;		//俯视 0=正常 1=俯视
	double d3vx,d3vy,d3vz;	//视点坐标
	double d3yoff;			//Y方向的偏移
};

/////////////////////////////////////////////////////////////////////////////////////////////
//--------用于压缩类：算法同ARJ,不失真，入口为内存地址-------------------------------------------------------

class   cmpress{
  public:
	cmpress();
	~cmpress();
	int EEnCode(char *in,char *out,int sizein,int sizeout);
	void initdata();
  private:
	int PutChar(int c);
	int GetChar();
    BYTE  *inbuf,*outbuf; //输入、输出缓冲区
    int   insize,outsize; //输入、输出缓冲区大小（字节）
    int   injs,outjs;     //输入、输出计数器
    DWORD textsize,codesize,printcount;
    BYTE  text_buf[4155];
	short match_position, match_length,lson[4097],rson[4353], dad[4097];
	unsigned short freq[628];
	short prnt[941];
	short son[627];
	unsigned short getbuf;
	BYTE getlen;
	unsigned short putbuf;
	BYTE putlen;
	unsigned short code,len;
	void InitTree(void);
	void InsertNode(int r);
	void DeleteNode(int p);
	void Putcode(short l, unsigned short c);
	void StartHuff();
	void reconst();
	void update(short c);
	void EncodeChar(unsigned short c);
	void EncodePosition(unsigned short c);
	void EncodeEnd();
	void Encode(void);
};

//---------解压缩：与压缩相反-----------------------------------------------------------------------
class   uncmpres{
  public:
	uncmpres();
	~uncmpres();
	int DDeCode(char *in,char *out,int sizein,int sizeout);
	void initdata();
  private:
	int PutChar(int c);
	int GetChar();
	BYTE  *inbuf,*outbuf; //输入、输出缓冲区
	int   insize,outsize; //输入、输出缓冲区大小（字节）
	int   injs,outjs;     //输入、输出计数器
	DWORD textsize , codesize, printcount;
	BYTE  text_buf[4155];
	short match_position, match_length,lson[4097],rson[4353], dad[4097];
	unsigned  short freq[628];
	short prnt[941];
	short son[627];
	unsigned short getbuf;
	BYTE getlen;
	unsigned short putbuf;
	BYTE putlen;
	unsigned short code,len;
	void DeleteNode(int p);
	int  GetBit(void);
	int  GetByte(void);
	void Putcode(int l, unsigned c);
	void StartHuff();
	void reconst();
	void update(int c);
	int  DecodeChar();
	int  DecodePosition();
	void Decode(void);
};


class   CContour  
{
public:
	void Draw(CDIB&mdc,BYTE *pb,int w,int h,double zoom,int dx,int dy);
	void DrawLineDgx(CDIB&mdc,int dx,int dy,double zoom,DWORD color);
	CContour();
	virtual ~CContour();
	/////////////////////////////
	int    wx,wy;
	BYTE   *cb;
	BYTE   enable;	//是否有效0=无效 1=有效
	int    type;    //等高线形状类型 0=矩形 1=线段
	RECT   rt;		//矩形
	CIPoint cpt;	//中心点位置
	CIPoint vpt;	//设备中心位置，经过变换后的位置
	DPOINT *point;	//线段点
	WORD   ptsum;	//点数
	double v_pu;	//当前值
	BYTE   val;		//当前值 已转换成0-255之间的值
	int    dis;		//距离(画园的最小距离)
	int    isout;	//是否界外
private:
	void DrawLineDgx(POINT ps,POINT pe,int length);
	void DrawFirstLine(POINT ps, POINT pe,int depth);
	void FillRect(RECT &rect,int depth);
	void DrawRectDgx(CDIB&mdc,DRECT *rt,int length,int dx,int dy,int a);
};

class   CSysContour  
{ 
public:
	bool SetContourEnable(int i);
	void MemSetPb();
	void ComputeMinDis(CDIB&mdc,int dx,int dy);
	void SmoothDgx();
	void DrawDGX(CDIB&mdc);
	void DrawDGXGrid(CDIB &mdc,int pw,int ph,int gw,int dx,int dy);
	void DrawDgxinMem(CDIB&mdc,double zomm,int dx,int dy);
	bool SetVal(int i,double val);
	void ScrSizeChange(int width,int height);
	void SetNPOINTPos(DPOINT *np,int ptsum,int i);
	void SetRectPos(RECT rt,int i);
	void CreatePalette();
	void SetCfg(BYTE smt,BYTE oline,char tbg,char type,CTR_COLOR * cr);
	CSysContour();
	virtual ~CSysContour();
	BYTE smooth;		//等高线平滑度1-30;
	char ctrtype;		//等高线类型0=母线电压 1=母线电压低 2=母线电压高 3=输电线状态 
						//4=节点电价
	CTR_COLOR *ctrcr;	//当前系统运行的等高线颜色目前6种 其他留作备用
	BYTE oneline;		//等高线是否单线 0=过渡色 1=单线
	char tranbg;		//等高线透明背景

	COLORPAL cmap[256]; //256色调色板
	int  w,h;			//屏幕的高和宽
	BYTE *pb;			//等高线缓冲区
	CContour contr[MAXCONTOUR];//等高线基本元素
	int  csum;			//等高线个数
	double curzoom;		//当前的屏幕放大系数
	int rdx,rdy;
private:
	int GetHigh(DPOINT &pt);
	void ShowDgxOneLine(CDIB &mdc);
	void ShowDgx3(CDIB &mdc);
	void ShowDgx012(CDIB&mdc);
	void ComputAVal(int i);
	void ShowDgx4(CDIB &mdc);
};
/**********************************************
图象处理软件子程序2000.11.12 CJH
***********************************************/
//24位图形底片处理
void   img24_reverse(BYTE  *dib,int w,int h); 
//24位图形灰度处理
void   img24_gray(BYTE  *dib,int w,int h); 
//24位图形镜像处理
void   img24_glass(BYTE  *dib,int w,int h);   
//24位图形倒置处理
void   img24_updown(BYTE  *dib,int w,int h);  
//24位图形平滑处理
void   img24_smooth(BYTE  *dib,int w,int h);  
//24位图形减色处理
void   img24_rcolor(BYTE  *dib,int w,int h,
				  BYTE MaxColor);  
//24位图加亮边缘
void   img24_bd_bright(BYTE  *dib,int w,int h);
//24位图加黑边缘
void   img24_bd_black(BYTE *dib,int w,int h); 
//24位图加黑边框
void   img24_bd_hard(BYTE  *dib,int w,int h);  
//24位图加水线
void   img24_bd_wl(BYTE  *dib,int w,int h);	 
//24位图形缩小
void   img24_stratch(BYTE *dib1,	BYTE *dib2,int w1,int h1,int w2,int h2);
//////////////////////////////////////////////////////////////////////////////////////
//特殊处理子程序
HRGN   BCreateLineRGN(POINT ps, POINT pe,double width);
HRGN   CrealeLineRGN(POINT ps, POINT pe,double w);
HRGN   CreatePolyRgn(int ptsum,POINT *pt);
int    GetLength(POINT pt1,POINT pt2); 
double GetLength(DPOINT pt1,DPOINT pt2);

/////////////////////////////////////////////////////////////////////////////////////////////
//特殊计算
void	NPolygonc(HDC hdc,POINT *point,int count,DWORD color1,DWORD color2);
void	Draw3dRect(HDC hdc,POINT *pt,DWORD c1,DWORD c2);
void	Draw3dRectP(HDC hdc,POINT *pt,DWORD color);
CDRect  CreateDrawNRt(int ptsum,DPOINT *pt,double zoom);
CDRect  CreateDrawNRt(int ptsum,DPOINT *pt);
int		GetSinPoint(CDRect rt,DPOINT *opt,int np,int dr,int startdeg);
int		GetHSinPoint(CDRect rt,DPOINT *opt,int np,int dr);
int		GetCircleAllPt(DPOINT *pt,DRECT &rt);
void	GetLeftRight(DPOINT *pt,int n,int &r,int &l,double a=0);
void	GetLeftRight(DPOINT *pt,int n,int &r,int &l,DPOINT cp);
double	GetAngle(DPOINT p1,DPOINT p2);
double  GetAngle(POINT p1,POINT p2);
void	OrderPos(int *pos, int n);
DPOINT  *GetCirclePoint(int &n,DRECT &art);
int		Abs(int iV);				//取绝对值
double	Abs(double iV);				//取绝对值
DWORD	GetCColor(DWORD color,int mode);
POINT   GetRPt(DPOINT cpt,double angle,double r);
DPOINT  GetRDPt(DPOINT cpt,double angle,double r);
//数据转化和特殊处理
void    GetDoubleStr(double value,char *str,int xs);
void    GetDtStr(int s,char *str);
///////////////////////////////////////////////////////////////////////////////////////
#endif