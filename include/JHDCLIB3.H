#if !defined(AFX_JHDCLIB3_H__INCLUDED_)
#define AFX_JHDCLIB3_H__INCLUDED_

#ifdef JHDCLIB3_EXPORTS
#define JHDCLIB3_API __declspec(dllexport)
#else
#define JHDCLIB3_API __declspec(dllimport)
#endif


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

typedef struct _RGB24{
	BYTE b,g,r;
}RGB24;

typedef struct _PDOT{
  WORD x;
  WORD y;
  char bz; //0表示左上点，1表示右下点
}PDOT;

class JHDCLIB3_API CImgList;
//------------------------------------------------------------------
class JHDCLIB3_API CMemDC  
{
friend CImgList;
public:
	CMemDC();
	CMemDC(int width,int height);
	virtual ~CMemDC();
	void Create(int width,int height);
	HDC m_hDC;              //HDC
	BITMAPINFO bi;			//图形信息
//----------外部公用函数-------------------------------
public:							
	void CutNoUse();
	void ChangeWH(int width,int height);		//改变大小
	void FillBG(DWORD color);					//底色填充
	void BitBlt(HDC hdc,RECT rt,DWORD dwRop);	//把位图传输到HDC
	void FillSolidRect(RECT rt,DWORD color);	//填充矩形
	void DrawBrushDot(int x,int y,int k,RGB24 rgb);
	void PenBrush(int x,int y,int ra,DWORD color);
	void AddBrushDot(int x,int y,int k);
	void AddPenBrush(int x,int y,int ra);
	int  width();								//返回宽度
	int  height();								//返回高度
	int  GetPline();							//返回每行字节数
	DWORD GetBgColor();							//返回背景色
	BYTE *Dib();								//图形数据
	void ReadImageFile(char *filename);			//读入图形文件	
	void TranImage(DWORD color,DWORD Tolerance);//透明处理
	void FloodFill(POINT pt);					//雪塴式填充
	void Filter1();								//过滤器1：平滑处理
//-----------------------------------------------------
	bool	GetPixel(int x,int y,RGB24&color);  //返回象素色
	void	SetPixel(int x,int y,RGB24 color);	//设置象素点
	
	void    *dib;								//图形地址
	HBITMAP hbitmap;							//位图句柄
	int     sPerline;							//每行字节数
	int     nWidth,nHeight;						//宽度、高度
	DWORD   bgcolor;							//用FillBG填充过的背景色
};

//--------------C I m g L i s t------------------------
//可以直接读入外部位图，并分离显示
class JHDCLIB3_API CImgList:public CMemDC
{
public:
	CImgList();
	~CImgList();
	void DrawItem(HDC hdc,int x,int y,int n);
	void ReadImg(char *fname,int w,int h,DWORD color);
	int xn,yn,maxn;
	int xw,yw;
};

//--------------C D I B--------------------------------
class JHDCLIB3_API CDIB
{
public:
	CDIB();
	~CDIB();
//----------外部公用函数-------------------------------
void Create(int width,int height);
void FillBG(DWORD color);
void SetPenAttrib(int pw,DWORD color);
void SetBkColor(DWORD color);
void SubBright(int x,int y,BYTE *brush);
void DrawBrushDot(int x,int y,int k,RGB24 rgb);
void PenBrush(int x,int y,int ra,DWORD color);
void AddBrushDot(int x,int y,int k);
void AddPenBrush(int x,int y,int ra);
void BitBlt(HDC hdc,RECT rt);
void BitBltRect(HDC hdc,RECT rts,RECT rtd);
void FillSolidRect(RECT rt,DWORD color);
int  CreateOutLine(PDOT *pt,BYTE *sdata,int sw,int sh,DWORD color);
void ShadowRect(RECT rt,int style);
void DrawDot(int x,int y);
void CopyDIB(CDIB&sdib);  //拷贝DIB的图象到本CDIB（两个CDIB必须一样的宽和高）
void TranDIB(CDIB&sdib,DWORD trancolor);     //透明DIB的图象到本CDIB（两个CDIB必须一样的宽和高）
void SizeChange(int newWidth,int newHeight); //改变DIB的宽和高
//------绘图操作绘图操作----------------------------------------------------------------------------------
void CopyImg(CMemDC&mdc,RECT drt);				     //拷贝图形到矩形区
void TranImg(CMemDC&mdc,RECT drt,DWORD color=1);     //透明
void TranImgShadow(CMemDC&mdc,RECT drt,int shadow=0);//透明+阴影
void FillImg(CMemDC&mdc);							 //用mdc来填充
void CopyImgPercent(CMemDC&mdc,RECT drt,BYTE depth); //按百分比传输(半透明)
void DrawArrow(POINT p1,POINT p2,DWORD color,int width,int shadow);
void CTextOut(char *str,RECT drt,LOGFONT *lf,DWORD color,int style,
			  int shadow,DWORD align=DT_LEFT) ;
void CLine(POINT pt1,POINT pt2,DWORD color,int width,int flow,int shadow);
void CRectc(RECT rt,DWORD color1,DWORD color2,WORD style,int shadow);
void CDrawButton(RECT rt,char *text,int shadow,int enable);
void CDrawDownButton(RECT rt,char *text,int shadow);
void CDrawFormDemo(RECT rt,char *name,int tranbg,int shadow);
void CDrawHRule(RECT rt,float *value,DWORD color,int shadow);
void CDrawVRule(RECT rt,float *value,DWORD color,int shadow);
void CDrawOutLine(POINT *point,int count,BYTE width,DWORD color,int shadow);
void CDrawDbx(POINT *point,int count,BYTE width,DWORD color,int flow,int shadow);
void CDrawFLow(POINT *point,int count,BYTE width,DWORD color1,DWORD color2
			   ,int shadow,int start=0,int f=0,int style=0);
void CEllipsec(RECT rt,DWORD color1,DWORD color2,WORD style,int shadow);
void CCircle(int x1,int y1,int x2,int y2,int width,DWORD color,int shadow);
void CPolygonc(POINT *point,int count,DWORD color1,DWORD color2,WORD style,int shadow);
void DrawBmp(HBITMAP hbmp,int xrc=0, int yrc=0,int xto=0,int yto=0,int w=0, int h=0,int rop=SRCCOPY);
void CDrawRect(RECT drt,int Penw,DWORD Pcolor,int shadow=0);                  //用特定颜色画一个空矩形
void CDraw3DRect(RECT drt,DWORD color1,DWORD color2,int shadow=0);            //画3D矩形
void CDrawGlass(RECT rt,DWORD bcolor,DWORD fcolor,BYTE oline,BYTE dp); //画玻璃层
void CDrawHSin(RECT drt,BYTE width,DWORD color,int xy,int pe,int mode,int shadow);
void CDrawSin(RECT drt,BYTE width,DWORD color,int xy,int pe,int shadow);
void CDrawBall(RECT rt,DWORD color,int shadow);
void CDrawArc(RECT drt,DWORD color,WORD s,WORD e,BYTE w,BYTE shadow);
//---------------------------------------------------------------------------------------------------------
public:
	void CDrawBar(RECT drt,void *data,int shadow);
	void StrechImg(CMemDC &mdc,RECT rt,int shadow);
	RGB24 *GetDibAddr(int x,int y);
	void  ShadowPattern(BYTE *sdata,RECT rt,int sw,int sh);
	void  SmoothPattern(BYTE *sdata,RECT rt,int sw,int sh,DWORD color,int ss);
	void  DrawOutLine(BYTE *sdata,RECT rt,int sw,int sh,DWORD color);
	//--------------------基本参数------------------------------------------------
	int		nWidth,nHeight;				//宽度、高度
	HDC		m_hDC;						//本内存DC
	void	*dib;						//图形数据地址	
	int		dibsize;					//DIB字节数
	int		sPerline;					//每行字节数
	int		Abs(int iV);				//取绝对值
	DWORD	PenColor;					//笔颜色
	DWORD	BkColor;					//背景色
	int		pWidth;						//笔宽度
	HBITMAP hbitmap;					//与本DC相关的位图
	BITMAPINFO bi;						//BMP信息
};
/////////////////////////////////////////////////////////////////////
//处理图形DC的类ImageDC
class JHDCLIB3_API ImageDC  
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


class JHDCLIB3_API CGIFAnm  
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
///////////////////////////////////////////////////////////////////
//打开所有图形的类CMImage

class JHDCLIB3_API CMImage : public ImageDC  
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


class JHDCLIB3_API JpegFile 
{
public:
	char *m_dib;         //设备无关位图
	BYTE *rgbbuf;		 //RGB图象
	int  width,height;	 //图象高宽
	int  bytes_per_line;  //每行字节数
public:
	void FreeMem();
	void read(char * fileName);

	static BOOL RGBToJpegFile(char * fileName,				// path
							BYTE *dataBuf,					// RGB buffer
							UINT width,						// pixels
							UINT height,					// rows
							BOOL color,						// TRUE = RGB
															// FALSE = Grayscale
							int quality);					// 0 - 100

	
	static BOOL GetJPGDimensions(char * fileName,			// path
								UINT *width,				// pixels
								UINT *height);


	static BYTE * MakeDwordAlignedBuf(BYTE *dataBuf,			// input buf
									 UINT widthPix,				// input pixels
									 UINT height,				// lines
									 UINT *uiOutWidthBytes);	// new width bytes


	
	static BYTE *RGBFromDWORDAligned(BYTE *inBuf,				// input buf
									UINT widthPix,				// input size
									UINT widthBytes,			// input size
									UINT height);
	static BOOL VertFlipBuf(BYTE * inbuf,						// input buf
					   UINT widthBytes,							// input width bytes
					   UINT height);							// height

	
	static BOOL MakeGrayScale(BYTE *buf,						// input buf 
						UINT widthPix,							// width in pixels
						UINT height);							// height

	
	static BOOL BGRFromRGB(BYTE *buf,							// input buf
					UINT widthPix,								// width in pixels
					UINT height);								// lines

	////////////////////////////////////////////////////////////////
	// these do nothing
	JpegFile();		// creates an empty object
	~JpegFile();	// destroys nothing
private:
	void RGBToDIB();
};

//-----以下函数是特殊处理的绘图函数----------------------------------------------------------------
//可以在任何HDC上绘制

void  JHDCLIB3_API GLLine(HDC hdc,int x1,int y1,int x2,int y2,DWORD color,int width=1);
void  JHDCLIB3_API GLLineXor(HDC hdc,int x1,int y1,int x2,int y2,DWORD color=0xffffff,int w=1);
void  JHDCLIB3_API GLCircleXor(HDC hdc,int x1,int y1,int x2,int y2);
void  JHDCLIB3_API GLRectXor(HDC hdc,int x1,int y1,int x2,int y2);
void  JHDCLIB3_API GLEllipse(HDC hdc,int x1,int y1,int x2,int y2,DWORD color);
void  JHDCLIB3_API GL3DRect(HDC hdc,RECT rt,DWORD color);
void  JHDCLIB3_API GLRectc(HDC hdc,RECT rt,DWORD color1,DWORD color2,WORD style);
void  JHDCLIB3_API Predraw(HDC hdc,int w,int h,DWORD color1,DWORD color2,WORD style);
void  JHDCLIB3_API GLPolygonc(HDC hdc,POINT *point,int count,DWORD color1,DWORD color2,WORD style);
void  JHDCLIB3_API GLEllipsec(HDC hdc,RECT rt,DWORD color1,DWORD color2,WORD style);
void  JHDCLIB3_API GL3DEllipsec(HDC hdc,RECT rt,DWORD color,int shad,int outline);
void  JHDCLIB3_API GL3DXEllipsec(HDC hdc,RECT rt,DWORD color,int shad,int outline);
SIZE  JHDCLIB3_API GLDGetTextSize(HDC hdc,LOGFONT *font,char *text);
void  JHDCLIB3_API GLDrawLine(HDC hdc,int x1,int y1,int x2,int y2,BYTE width,DWORD color);
void  JHDCLIB3_API GLDrawDbx(HDC hdc,int num,POINT *pt,BYTE width,DWORD color);
void  JHDCLIB3_API GLDrawOutLine(HDC hdc,int num,POINT *pt,BYTE width,DWORD color);
void  JHDCLIB3_API GLCircle(HDC hdc,int x1,int y1,int x2,int y2,int width,DWORD color);
void  JHDCLIB3_API GLRect(HDC hdc,int x1,int y1,int x2,int y2,int width,DWORD color);
void  JHDCLIB3_API GLDDraw3DRect(HDC hdc,RECT rt,DWORD color1=0,DWORD color2=0xffffff,int width=1);
void  JHDCLIB3_API GLDDrawText(HDC hdc,RECT *rt,LOGFONT *lf,char *text,DWORD color,int style,DWORD align=DT_LEFT);
void  JHDCLIB3_API GLFillRect(HDC hdc,RECT rt,DWORD color);
void  JHDCLIB3_API GLDrawButton(HDC hdc,RECT rt,char *text,int enable=0);
void  JHDCLIB3_API GLDrawDownButton(HDC hdc,RECT rt,char *text);
void  JHDCLIB3_API GLDrawZb(HDC hdc,RECT rt);
void  JHDCLIB3_API GLDrawTrend(HDC hdc,float *val,RECT rt,void *param);
void  JHDCLIB3_API GLDrawCure(HDC hdc,RECT drt,void *param);
void  JHDCLIB3_API GLDrawFormDemo(HDC hdc,RECT rt,char *name,int tranbg);
void  JHDCLIB3_API GLDrawBar(HDC hdc,RECT rt,void *data);
void  JHDCLIB3_API GLDrawHRule(HDC hdc,RECT rt,float *value,DWORD color);
void  JHDCLIB3_API GLDrawVRule(HDC hdc,RECT rt,float *value,DWORD color);
RECT  JHDCLIB3_API GLDrawCtrlOutline(HDC hdc,RECT rt,BYTE style=0);
void  JHDCLIB3_API GLDrawScroll(HDC hdc,RECT rt,int style);
void  JHDCLIB3_API GLDrawScrollA(HDC hdc,RECT rt,int style);
void  JHDCLIB3_API GLDrawDBXA(HDC hdc,POINT *pt,int ptsum,BYTE width,
				DWORD c1,DWORD c2,DWORD c3,int mode);
void  JHDCLIB3_API GLDrawHSin(HDC hdc,RECT rt,BYTE width,DWORD color,int xy,int pe,int mode);
void  JHDCLIB3_API GLDrawSin(HDC hdc,RECT rt,BYTE width,DWORD color,int xy,int pe);
void  JHDCLIB3_API DrawDIRSingle(HDC hdc,POINT ps,POINT pe,DWORD color,BYTE width); 
void  JHDCLIB3_API DrawDbxFlowA(HDC hdc,POINT *pt,int count,DWORD color1,DWORD color2,
								BYTE width,int start,int f,int sytle);
int   JHDCLIB3_API DrawFlowA(HDC hdc,POINT ps,POINT pe,DWORD color1,DWORD color2,
			  BYTE width,int start,int&first);
int   JHDCLIB3_API DrawFlowB(HDC hdc,POINT ps,POINT pe,DWORD color1,DWORD color2,
			  BYTE width,int start,int&first);
void  JHDCLIB3_API DrawBall(HDC hdc,RECT rt,DWORD color);
void  JHDCLIB3_API GLDrawArc(HDC hdc,RECT drt,DWORD color,WORD start,WORD end,BYTE w);
void  JHDCLIB3_API GLDraw2Pie(HDC hdc,RECT drt,DWORD c1,DWORD c2,DWORD c3,float percent);
//--------用于压缩类：算法同ARJ,不失真，入口为内存地址-------------------------------------------------------

class JHDCLIB3_API cmpress{
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
class JHDCLIB3_API uncmpres{
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

class JHDCLIB3_API piedraw  
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

/**********************************************
图象处理软件子程序2000.11.12 CJH
***********************************************/
//24位图形底片处理
void JHDCLIB3_API img24_reverse(BYTE  *dib,int w,int h); 
//24位图形灰度处理
void JHDCLIB3_API img24_gray(BYTE  *dib,int w,int h); 
//24位图形镜像处理
void JHDCLIB3_API img24_glass(BYTE  *dib,int w,int h);   
//24位图形倒置处理
void JHDCLIB3_API img24_updown(BYTE  *dib,int w,int h);  
//24位图形平滑处理
void JHDCLIB3_API img24_smooth(BYTE  *dib,int w,int h);  
//24位图形减色处理
void JHDCLIB3_API img24_rcolor(BYTE  *dib,int w,int h,
				  BYTE MaxColor);  
//24位图加亮边缘
void JHDCLIB3_API img24_bd_bright(BYTE  *dib,int w,int h);
//24位图加黑边缘
void JHDCLIB3_API img24_bd_black(BYTE *dib,int w,int h); 
//24位图加黑边框
void JHDCLIB3_API img24_bd_hard(BYTE  *dib,int w,int h);  
//24位图加水线
void JHDCLIB3_API img24_bd_wl(BYTE  *dib,int w,int h);	 
//24位图形缩小
void JHDCLIB3_API img24_stratch(BYTE *dib1,	BYTE *dib2,int w1,
							int h1,int w2,int h2);



//数据转化和特殊处理
void  JHDCLIB3_API GetDoubleStr(double value,char *str,int xs);
void  JHDCLIB3_API GetNoDataStr(char *str,int xs);
void  JHDCLIB3_API GetDtStr(int s,char *str);
HRGN  JHDCLIB3_API CreatePolyRgn(int ptsum,POINT *pt);
HRGN  JHDCLIB3_API CrealeLineRGN(POINT ps, POINT pe);
RECT  JHDCLIB3_API CreateRt(int ptsum,POINT *pt);
void  JHDCLIB3_API SetSelRtCan(RECT &rt);
int   JHDCLIB3_API ReducePoint(POINT *pt,int n);
POINT JHDCLIB3_API  GetPosition(POINT *pt,int npt,double min,double max,double value);
#endif




