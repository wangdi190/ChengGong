#if !defined(AFX_JHSYSLIB_H__INCLUDED_)
#define AFX_JHSYSLIB_H__INCLUDED_


#ifdef JHSYSLIB_EXPORTS
#define JHSYSLIB_API __declspec(dllexport)
#else
#define JHSYSLIB_API __declspec(dllimport)
#endif

//-------------------------------------------------------------------------
//  图形处理DLL:2000.11
//  作者:陈金海
//  修改记录:
//	1999.10   第一版 jhdclib.dll jhdclib2.h
//  2000.11   由原来的JHDCLIB升级到JHDCLIB2
//  2000.12   增加饼图类class piechart  原来不包含"format.h"
//  2001.3.1  升级到jhdclib3 不兼容旧版本，旧版本极其界面工具可以继续使用
//			  重点修改阴影部分程序，对CDIB CMemDC类进行修改
//  2005.10   全面改版，增加一些特殊绘图，等高线等类，增加CIPoint CIRect类，
//			  去除原来的图形边缘处理
//-------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////

#define  mpi  3.1415926535897932
#define  MAXCONTOUR    400
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
//////////////////////////////////////////////////////////
typedef struct _PIEDAT{ //饼图数据结构
	char name[12];       //数据名称
	float value;		 //值
}PIEDAT;
typedef struct OBJ_PIEPAM{  //饼图结构数据
	WORD   ID;			 //ID号
	BYTE   style;		 //0=一般 1=分离 2=立体 3=分离立体
	BYTE   outline;		 //包围线 0=无 1=有
	BYTE   shad;		 //过渡色 0=否 1=是
	BYTE   sum;			 //饼数
	DWORD  fcolor;		 //字符色
	WORD   angle;		 //起始角度0-360度
	DWORD  color[8];     //8个颜色
	PIEDAT pd[8];		 //8个数据 
	char   reserved[12]; //保留字节
}OBJ_PIEPAM;
/////////////////////////////////////////////////////////////////////////////
//-----以下函数是特殊处理的绘图函数----------------------------------------------------------------
//可以在任何HDC上绘制

void  JHSYSLIB_API GLLine(HDC hdc,int x1,int y1,int x2,int y2,DWORD color,int width=1);
void  JHSYSLIB_API GLLineXor(HDC hdc,int x1,int y1,int x2,int y2,DWORD color=0xffffff,int w=1);
void  JHSYSLIB_API GLCircleXor(HDC hdc,int x1,int y1,int x2,int y2);
void  JHSYSLIB_API GLRectXor(HDC hdc,int x1,int y1,int x2,int y2);
void  JHSYSLIB_API GLEllipse(HDC hdc,int x1,int y1,int x2,int y2,DWORD color);
void  JHSYSLIB_API GL3DRect(HDC hdc,RECT rt,DWORD color);
void  JHSYSLIB_API GLRectc(HDC hdc,RECT rt,DWORD color1,DWORD color2,WORD style);
void  JHSYSLIB_API GLPolygonc(HDC hdc,POINT *point,int count,DWORD color1,DWORD color2,WORD style);
void  JHSYSLIB_API GLEllipsec(HDC hdc,RECT rt,DWORD color1,DWORD color2,WORD style);
void  JHSYSLIB_API GL3DEllipsec(HDC hdc,RECT rt,DWORD color,int shad,int outline);
void  JHSYSLIB_API GL3DXEllipsec(HDC hdc,RECT rt,DWORD color,int shad,int outline);
SIZE  JHSYSLIB_API GLDGetTextSize(HDC hdc,LOGFONT *font,char *text);
void  JHSYSLIB_API GLDrawLine(HDC hdc,int x1,int y1,int x2,int y2,BYTE width,DWORD color);
void  JHSYSLIB_API GLDrawDbx(HDC hdc,int num,POINT *pt,BYTE width,DWORD color);
void  JHSYSLIB_API GLDrawOutLine(HDC hdc,int num,POINT *pt,BYTE width,DWORD color);
void  JHSYSLIB_API GLCircle(HDC hdc,int x1,int y1,int x2,int y2,int width,DWORD color);
void  JHSYSLIB_API GLRect(HDC hdc,int x1,int y1,int x2,int y2,int width,DWORD color);
void  JHSYSLIB_API GLDDraw3DRect(HDC hdc,RECT rt,DWORD color1=0,DWORD color2=0xffffff,int width=1);
void  JHSYSLIB_API GLDDrawText(HDC hdc,RECT *rt,LOGFONT *lf,char *text,DWORD color,int style,DWORD align=DT_LEFT);
void  JHSYSLIB_API GLFillRect(HDC hdc,RECT rt,DWORD color);
void  JHSYSLIB_API GLDrawButton(HDC hdc,RECT rt,char *text,int enable=0);
void  JHSYSLIB_API GLDrawDownButton(HDC hdc,RECT rt,char *text);
void  JHSYSLIB_API GLDrawTrend(HDC hdc,float *val,RECT rt,void *param);
void  JHSYSLIB_API GLDrawCure(HDC hdc,RECT drt,void *param);
void  JHSYSLIB_API GLDrawFormDemo(HDC hdc,RECT rt,char *name,int tranbg);
void  JHSYSLIB_API GLDrawBar(HDC hdc,RECT rt,void *data);
RECT  JHSYSLIB_API GLDrawCtrlOutline(HDC hdc,RECT rt,BYTE style=0);
void  JHSYSLIB_API GLDrawScroll(HDC hdc,RECT rt,int style);
void  JHSYSLIB_API GLDrawScrollA(HDC hdc,RECT rt,int style);
void  JHSYSLIB_API GLDrawHSin(HDC hdc,RECT rt,BYTE width,DWORD color,int xy,int pe,int mode);
void  JHSYSLIB_API GLDrawSin(HDC hdc,RECT rt,BYTE width,DWORD color,int xy,int pe);
void  JHSYSLIB_API DrawDIRSingle(HDC hdc,POINT ps,POINT pe,DWORD color,BYTE width); 
void  JHSYSLIB_API DrawBall(HDC hdc,RECT rt,DWORD color);
void  JHSYSLIB_API GLDrawArc(HDC hdc,RECT drt,DWORD color,WORD start,WORD end,BYTE w);
void  JHSYSLIB_API GLDraw2Pie(HDC hdc,RECT drt,DWORD c1,DWORD c2,DWORD c3,float percent);
/////////////////////////////////////////////////////////////////////////////////////////////
//特殊计算
void  JHSYSLIB_API CptLookDown(DPOINT *tp,int tpsum,int wx,int wy);
void  JHSYSLIB_API CptLookDown(POINT *tp,int tpsum,int wx,int wy);
//数据转化和特殊处理
void  JHSYSLIB_API GetDoubleStr(double value,char *str,int xs);
void  JHSYSLIB_API GetDtStr(int s,char *str);
HRGN  JHSYSLIB_API CreatePolyRgn(int ptsum,POINT *pt);
HRGN  JHSYSLIB_API CrealeLineRGN(POINT ps, POINT pe,double w);
RECT  JHSYSLIB_API CreateRt(int ptsum,POINT *pt);
////////////////24位真彩结构定义/////////////////////////////////////////////
typedef struct _RGB24{
	BYTE b,g,r;
}RGB24;
/////////////////////////////////////////////////////////////////////////////
class JHSYSLIB_API CIPoint:public tagPOINT
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
class JHSYSLIB_API CDPoint:public DPOINT
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
class JHSYSLIB_API CIRect:public tagRECT 
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
class JHSYSLIB_API CDRect:public DRECT  
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
class JHSYSLIB_API ImageDC  
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


class JHSYSLIB_API CGIFAnm  
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
class JHSYSLIB_API JpegFile 
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

class JHSYSLIB_API CMImage : public ImageDC  
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
///////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------
class JHSYSLIB_API CMemDC  
{
public:
	CMemDC();
	virtual ~CMemDC();
	void Create(int width,int height);

//----------外部公用函数-------------------------------
public:							
	void CutNoUse();
	void SizeChange(int width,int height);		//改变大小
	void FillBG(DWORD color);					//底色填充
	void BitBlt(HDC hdc,RECT rt,DWORD dwRop);	//把位图传输到HDC
	void FillSolidRect(RECT rt,DWORD color);	//填充矩形
	void TranImage(DWORD color,DWORD Tolerance);//透明处理
	void ReadImageFile(char *filename);			//读入图形文件	
	void FloodFill(POINT pt);					//雪塴式填充
	bool GetPixel(int x,int y,RGB24&color);  //返回象素色
	void SetPixel(int x,int y,RGB24 color);	//设置象素点
	void DrawBrushDot(int x,int y,int k,RGB24 rgb);
	void PenBrush(int x,int y,int ra,DWORD color);
	void AddBrushDot(int x,int y,int k);
	void AddPenBrush(int x,int y,int ra);
	HDC m_hDC;              //HDC
	BITMAPINFO bi;			//图形信息
	void    *dib;								//图形地址
	HBITMAP hbitmap;							//位图句柄
	int     sPerline;							//每行字节数
	int     nWidth,nHeight;						//宽度、高度
	
};
////////////////////////////////////////////////////////////////////////////////////
//--------------C D I B--------------------------------
class JHSYSLIB_API CDIB
{
public:
	CDIB();
	~CDIB();
	//----------外部公用函数-------------------------------
	void Create(int width,int height);
	void SizeChange(int newWidth,int newHeight); //改变DIB的宽和高
	void FillBG(DWORD color);
	void BitBlt(HDC hdc,RECT rt);
	void BitBltRect(HDC hdc,RECT rts,RECT rtd);
	void FillSolidRect(RECT rt,DWORD color);
	void ShadowRect(RECT rt,int style);
	void CopyDIB(CDIB&sdib);  //拷贝DIB的图象到本CDIB（两个CDIB必须一样的宽和高）
	void TranDIB(CDIB&sdib,DWORD trancolor);     //透明DIB的图象到本CDIB（两个CDIB必须一样的宽和高）
	//------绘图操作绘图操作----------------------------------------------------------------------------------
	void CopyImg(CMemDC&mdc,RECT drt);				     //拷贝图形到矩形区
	void TranImg(CMemDC&mdc,RECT drt,DWORD color=1);     //透明
	void TranImgShadow(CMemDC&mdc,RECT drt,int shadow=0);//透明+阴影
	void FillImg(CMemDC&mdc);							 //用mdc来填充
	void CopyImgPercent(CMemDC&mdc,RECT drt,BYTE depth); //按百分比传输(半透明)
	void DrawArrow(POINT p1,POINT p2,DWORD color,int width);
	void CTextOut(char *str,RECT drt,LOGFONT *lf,DWORD color,int style,DWORD align=DT_LEFT) ;
	void CLine(POINT pt1,POINT pt2,DWORD color,int width);
	void CDLine(DPOINT p1,DPOINT p2,DWORD color);
	void CRectc(RECT rt,DWORD color1,DWORD color2,WORD style);
	void CDrawOutLine(POINT *point,int count,DWORD color);
	void CDrawOutDLine(DPOINT *point,int count,DWORD color);
	void CDrawDbx(POINT *point,int count,BYTE width,DWORD color);
	void CDrawDbx(DPOINT *point,int count,BYTE width,DWORD color);
	void CDrawFLow(POINT *point,int count,BYTE width,DWORD color,int start=0,int style=0);
	void CEllipsec(RECT rt,DWORD color);
	void CEllipsec(DRECT rt,DWORD color);
	void CCircle(RECT rt,int width,DWORD color);
	void CCircle(DRECT rt,int width,DWORD color);
	void CPolygonc(POINT *point,int count,DWORD color);
	void DrawBmp(HBITMAP hbmp,int xrc=0, int yrc=0,int xto=0,int yto=0,int w=0, int h=0,int rop=SRCCOPY);
	void CDrawRect(RECT drt,int Penw,DWORD Pcolor);                  //用特定颜色画一个空矩形
	void CDraw3DRect(RECT drt,DWORD color1,DWORD color2);            //画3D矩形
	void CDrawGlass(RECT rt,DWORD bcolor,DWORD fcolor,BYTE oline,BYTE dp);		  //画玻璃层
	void CDrawHSin(RECT rt,BYTE width,DWORD color,int xy,int pe,int mode);
	void CDrawSin(RECT rt,BYTE width,DWORD color,int xy,int pe,int startdeg);
	void CDrawArc(RECT rt,DWORD color,WORD s,WORD e,BYTE width);
	void CSetLineStyle(int LStyle);
	void CopyLookDownDIB(int sx,int sy,int dx,int dy,CDIB&mdc,int wx,int wy,RGB24 color);
	void LDCircle(DRECT rt,DWORD color,DWORD bcolor,int fill,int dx,int dy,int wx,int wy);
	//---------------------------------------------------------------------------------------------------------
public:
	void CDrawBar(RECT drt,void *data);
	void StrechImg(CMemDC &mdc,RECT rt,int shadow);
	RGB24 *GetDibAddr(int x,int y);
	void  ShadowPattern(BYTE *sdata,RECT rt,int sw,int sh);
	void  SmoothPattern(BYTE *sdata,RECT rt,int sw,int sh,DWORD color,int ss);
	//--------------------基本参数------------------------------------------------
	int		nWidth,nHeight;				//宽度、高度
	HDC		m_hDC;						//本内存DC
	void	*dib;						//图形数据地址	
	int		dibsize;							//DIB字节数
	int		sPerline;					//每行字节数
	HBITMAP hbitmap;					//与本DC相关的位图
	BITMAPINFO bi;						//BMP信息
private:
	void    SubBright(int x,int y,BYTE *brush);
	void    SetRGB24(DWORD color);
	bool    PTIsInDC(POINT pt);
	double	tlx,tly;
	RGB24	tlrgb;
	int		linestyle;			//0=实线 1=点线 2=点划线
	int     lstym,lstya,lstyb;	//画各种线性所需要的参数
	void	QDrawDot();
	void    DrawSTyleDot();
	void	QLine(POINT p1,POINT p2,DWORD color); //画基本线（宽度=1）
	void	QDrawLineX(double xs,double y,double xe,int yoff);
	void	QDrawLineY(double ys,double x,double ye,int xoff);
};

/////////////////////////////////////////////////////////////////////////////////////////////
//--------用于压缩类：算法同ARJ,不失真，入口为内存地址-------------------------------------------------------

class JHSYSLIB_API cmpress{
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
class JHSYSLIB_API uncmpres{
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
//////////////////////////////////////////////////////////////
//饼图绘制类 2000.12.29 由陈金海添加
//////////////////////////////////////////////////////////////
class JHSYSLIB_API piedraw  
{
public:
	void SetThisParam(OBJ_PIEPAM*piepam);
	void Show(HDC hdc,RECT rt);
	void OnDraw(HDC hdc);
	piedraw();
	virtual ~piedraw();
	int w,h;
	double   bf[8];
	double   vsum;
	OBJ_PIEPAM   pp;		//参数
	POINT   point[380],pt3d[380];
private:
	void ShowText(HDC hdc,POINT pt,int c,char *text);
	void computpoint();
	void ShowValue(HDC hdc,int ax,int ay,int c,int index,int div=1);
	void computdata();
	void DrawPie4(HDC hdc);
	void DrawPie3(HDC hdc);
	void DrawPie2(HDC hdc);
	void DrawPie1(HDC hdc);
	void ComputXY();
	void CreateDemoData();
	void SizeChange(int wd,int hg);
	void GetMColor(DWORD color1, DWORD &c1, DWORD &c2);
	LOGFONT lf2;
	//坐标系统
	int  x,y,r;//圆心,半经
	int  x0,x1,x2,x3;
	int  y0,y1,y2,y3,y4;
	//原点偏移
	POINT org;
};
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
	/*
	  vhow=0  全部有效 
		  =1  高于无效
		  =2  低于无效
	  emptyfill=127
			   =255
			   =0
    */
}CTR_COLOR;

typedef struct SHOWCFG{
	WORD ver;					//版本=0x1000;
	char first;					//第一次标志 0=第一次 1=否
	char showdgx;				//是否显示等高线0=不显 1=显示
	char gendyn;				//动态显示发电机 
	char showrev;				//发电机储备 1=有功 2=无功 3=变压器
	char flowover;				//过流推出
	char ctrtype;				//等高线类型0=母线电压 1=母线电压低 2=母线电压高 3=输电线状态 
								//4=节点电价
	char tranbg;				//等高线透明背景
	BYTE smooth;				//等高线平滑度1-30;
	BYTE oneline;				//等高线是否单线 0=过渡色 1=单线
	CTR_COLOR cr[20];			//当前系统运行的等高线颜色目前6种 其他留作备用 
	char lookdown;				//俯视标志 0=平面 1=俯视
	char cpu;					//CPU性能0=低CPU 1=高CPU
	char flowdyn;				//潮流动态显示
	char lmd;					//灵敏度显示
	float flowzoom;				//潮流箭头放大倍数
	float senzoom;				//灵敏度放大倍数
	float pqzoom;				//有功无功放大倍数
	float tpzoom;				//变压器功率放大倍数
	float tptzoom;				//变压器温度放大系数
	char reserved[116];			//保留备用
}SHOWCFG;

class JHSYSLIB_API CContour  
{
public:
	void Draw(BYTE *pb,int w,int h,double zoom,int dx,int dy);
	CContour();
	virtual ~CContour();
	/////////////////////////////
	int    wx,wy;
	BYTE   *cb;
	BYTE   enable;	//是否有效0=无效 1=有效
	int    type;    //等高线形状类型 0=矩形 1=线段
	RECT   rt;		//矩形
	CIPoint cpt;	//中心点位置
	DPOINT *point;	//线段点
	WORD   ptsum;	//点数
	double v_pu;	//当前值
	BYTE   val;		//当前值 已转换成0-255之间的值
	int    dis;		//距离(画园的最小距离)
private:
	void DrawLineDgx(POINT ps,POINT pe,int length);
	void DrawFirstLine(POINT ps, POINT pe,int depth);
	void FillRect(RECT &rect,int depth);
	void DrawRectDgx(RECT rect,int length);
};

class JHSYSLIB_API CSysContour  
{
public:
	bool SetContourEnable(int i);
	void MemSetPb();
	void ComputeMinDis();
	void SmoothDgx();
	void DrawDGX(CDIB&mdc,CIRect rt,int dx,int dy);
	void DrawDgxinMem(double zomm,int dx,int dy);
	bool SetVal(int i,double val);
	void ScrSizeChange(int width,int height);
	void SetNPOINTPos(DPOINT *np,int ptsum,int i);
	void SetRectPos(RECT rt,int i);
	void CreatePalette();
	void SetCfg(SHOWCFG  *cfg);
	CSysContour();
	virtual ~CSysContour();
	SHOWCFG  *p_cfg;	//显示配置地址
	COLORPAL cmap[256]; //256色调色板
	int  w,h;			//屏幕的高和宽
	BYTE *pb;			//等高线缓冲区
	CContour contr[MAXCONTOUR];//等高线基本元素
	int  csum;			//等高线个数
	double curzoom;		//当前的屏幕放大系数
private:
	void ShowDgxOneLine(CDIB &mdc, RECT rt);
	void ShowDgx3(CDIB&mdc,RECT rt);
	void ShowDgx012(CDIB&mdc,RECT rt);
	void ComputAVal(int i);
};
/**********************************************
图象处理软件子程序2000.11.12 CJH
***********************************************/
//24位图形底片处理
void JHSYSLIB_API img24_reverse(BYTE  *dib,int w,int h); 
//24位图形灰度处理
void JHSYSLIB_API img24_gray(BYTE  *dib,int w,int h); 
//24位图形镜像处理
void JHSYSLIB_API img24_glass(BYTE  *dib,int w,int h);   
//24位图形倒置处理
void JHSYSLIB_API img24_updown(BYTE  *dib,int w,int h);  
//24位图形平滑处理
void JHSYSLIB_API img24_smooth(BYTE  *dib,int w,int h);  
//24位图形减色处理
void JHSYSLIB_API img24_rcolor(BYTE  *dib,int w,int h,
				  BYTE MaxColor);  
//24位图加亮边缘
void JHSYSLIB_API img24_bd_bright(BYTE  *dib,int w,int h);
//24位图加黑边缘
void JHSYSLIB_API img24_bd_black(BYTE *dib,int w,int h); 
//24位图加黑边框
void JHSYSLIB_API img24_bd_hard(BYTE  *dib,int w,int h);  
//24位图加水线
void JHSYSLIB_API img24_bd_wl(BYTE  *dib,int w,int h);	 
//24位图形缩小
void JHSYSLIB_API img24_stratch(BYTE *dib1,	BYTE *dib2,int w1,int h1,int w2,int h2);
//////////////////////////////////////////////////////////////////////////////////////
//特殊处理子程序
HRGN JHSYSLIB_API BCreateLine1RGN(POINT ps, POINT pe,double width);
int  JHSYSLIB_API GetTowPtDistance(POINT p1,POINT p2);
///////////////////////////////////////////////////////////////////////////////////////
#endif