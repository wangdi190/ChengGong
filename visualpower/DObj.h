// DObj.h: interface for the DObj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOBJ_H__8FD77ECC_72D9_4985_9763_F299D2B74D5E__INCLUDED_)
#define AFX_DOBJ_H__8FD77ECC_72D9_4985_9763_F299D2B74D5E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PWPTDEF.H"
#include "gdata.h"

class DObj  
{
public:
	DObj();
	virtual ~DObj();
	//数据定义
	gdata *dbm;
	int showdyn;				//是否动态显示
	N_BASATTR  attr;			//图形基本属性
	CDRect     ort;				//所占的矩形区域
	void       *buf;			//变化后的数据
//基本函数部分
public:
	void Print(HDC hdc,int pm,int dx,int dy);
	bool ObjIsCutRgn(HRGN hrgn);
	bool ObjIsInRect(CRect &rt);
	bool PtIsInObj(POINT &pta);
	bool GetType(BYTE &type, BYTE &subtype,char *ds_name,int &jlh);
	void InitSelfCtl();
	void SetSObjZM(double zm);
	bool SetAnlVal(READDEV &ran);
	void SetMeterVal(float val);
	void SetMeterMaxMin(MTRRANGE &mtr);
	bool SetDevAnl(READDEV &ran,int k=0);
	DPOINT *GetObjectPt(int &ptsum);
	void CreateSelRect();
	void AddObject(N_BASATTR &atr, void *obuf);
	void FreeMem();
	//显示分类函数
	void Show(HDC hdc,int dx,int dy);
	//显示对象函数
	void ShowSysPie(HDC hdc, int dx, int dy);
	void ShowMTText(HDC hdc, int dx, int dy,int pm);
	void ShowZone(HDC hdc,int dx, int dy,int pm);
	void ShowReservoir(HDC hdc,int dx, int dy,int pm);
	void ShowMeter4(HDC hdc, int dx, int dy);
	void ShowMeter3(HDC hdc, int dx, int dy);
	void ShowMeter2(HDC hdc, int dx, int dy);
	void ShowMeter1(HDC hdc,int dx, int dy);
	void ShowFlow(HDC hdc,int dx, int dy);
	void ShowEleGrp(HDC hdc, int dx, int dy);
	void ShowYb(HDC hdc, int dx, int dy);
	void ShowPctPie(HDC hdc, int dx, int dy);
	void ShowConLine(HDC hdc,int dx, int dy);
	void ShowBus(HDC hdc, int dx, int dy);
	void ShowFlowLine(HDC hdc,int dx, int dy);
	void ShowPush(HDC hdc, int dx, int dy);
	void ShowScrText(HDC hdc, int dx, int dy,int pm);
	void ShowGifAnl(HDC hdc, int dx, int dy);
	void ShowTime(HDC hdc, int dx, int dy,int pm);
	void ShowDate(HDC hdc, int dx, int dy,int pm);
	void ShowPie(HDC hdc, int dx, int dy);
	void ShowBar(HDC hdc, int dx, int dy);
	void ShowAnl(HDC hdc, int dx, int dy,int pm);
	void ShowImg(HDC hdc, int dx, int dy);
	void ShowTable(HDC hdc, int dx, int dy,int pm);
	void ShowCoordnate(HDC hdc, int dx, int dy,int pm);
	void ShowText(HDC hdc, int dx, int dy);
	void ShowArrow(HDC hdc, int dx, int dy);
	void ShowArc(HDC hdc, int dx, int dy);
	void ShowSin(HDC hdc, int dx, int dy);
	void ShowHSin(HDC hdc, int dx, int dy);
	void ShowCircle(HDC hdc,int dx, int dy);
	void ShowRect(HDC hdc,int dx, int dy);
	void ShowDbx(HDC hdc,int dx, int dy);
	//打印用
	void ShowRectP(HDC hdc,int dx, int dy,int pm);
	void ShowArrowP(HDC hdc, int dx, int dy,int pm);
	void ShowConLineP(HDC hdc,int dx, int dy,int pm);
	void ShowFlowLineP(HDC hdc,int dx, int dy,int pm);
	void ShowTextP(HDC hdc, int dx, int dy,int pm);
	void ShowArcP(HDC hdc, int dx, int dy,int pm);
	void ShowDbxP(HDC hdc,int dx, int dy,int pm);
	void ShowSinP(HDC hdc, int dx, int dy,int pm);
	void ShowHSinP(HDC hdc, int dx, int dy,int pm);
	void ShowBusP(HDC hdc, int dx, int dy,int pm);
	void ShowPctPieP(HDC hdc, int dx, int dy,int pm);
	void ShowEleGrpP(HDC hdc, int dx, int dy,int pm);
	void ShowCircleP(HDC hdc,int dx, int dy,int pm);
    //其它辅助函
	int  GetLineNum(char *str);
	void DrawFlow(HDC hdc,POINT *pt,int ptsum,int start,int arrow,int size,
					int dis,DWORD color1,DWORD color2,int dx,int dy);
	void PreBusEGPExP(HDC hdc,int num,int index,int dx,int dy,int pm);
	void PreBusEGPEx(HDC hdc,int num,int index,int dx,int dy);
	void SetColor(DWORD color,int bgmode=0);
	void MoveObject2(CDRect prt, double xl, double yl);
	void PreShowEGPExP(HDC hdc,int num,int index,int dx,int dy,int pm);
	void PreShowEGPEx(HDC hdc,int num,int index,int dx,int dy);
	void PreShowEGPYB(HDC hdc,int num,int dx,int dy);
	int  GetAWordW(char *str,int *pos,int f,int len);
	int  GetALine(int start,char *str,int *pos,int w,int max);
	void RtToDrawDpt(CRect &rt,DPOINT *pt,DPOINT *opt,int dr);
	void ShowTextEx(HDC hdc,LOGFONT *lf,char *str,float x,float y,int w,int h,double angle,DWORD color,DWORD nfmt);
	void SDrawText(HDC hdc,DPOINT *pt,char *text,LOGFONT *ft,int dx,int dy,DWORD color,int nfmt=DT_LEFT);
	CRect CreateDrawRect(int ptsum,DPOINT *pt,int dx,int dy);
	void DrawPieP(HDC hdc,CRect &rt,DWORD c1,DWORD c2,DWORD c3,double pw,int pm);
	void DrawPie(HDC hdc,CDRect &rt,DWORD c1,DWORD c2,DWORD c3,double pw,int dx,int dy);
	void OffsetRt(DRECT &rt,int wh, int direct, int qh);
	void DrtToDPt(DRECT &rt,DPOINT *pt,int dr);
	void MDrawText(HDC hdc,DPOINT *pt,char *text,LOGFONT *ft,int dx,int dy,DWORD color,DWORD nfmt);
	void ShowDigitPQ(HDC hdc,DRECT &rt,LOGFONT *lf,float vp,float vq,char xs,DWORD color1,DWORD color2,
			BYTE direction,int dx,int dy);
	void ShowDigit(HDC hdc,DRECT &rt,LOGFONT *lf,float val,char *pre,char *unit,char xs,
					 DWORD color,BYTE direction,int dx,int dy);
	void ShowAnalog(HDC hdc,DRECT &rt,N_ANL *anl,int dx,int dy,int pm);
	void DrawArrowP(HDC hdc,DPOINT *pts,DWORD color,int dx, int dy);
	void DrawArrow(HDC hdc,DPOINT *pts,DWORD color,int dx, int dy);
	void ShowTextXT(HDC hdc,LOGFONT *ft,char *str,DPOINT *pt,DWORD color,int dx,int dy);

	void ShowE(HDC hdc,int dx, int dy);
	void ShowEP(HDC hdc,int dx, int dy,int pm);
	void GetSubTxt(char *obuf,char *Outbuf,int *offset,int maxlst,int index);
	void DrawMPie(HDC hdc,CDRect &rt,DWORD *cr,double *vp,int num,LOGFONT &lf,DWORD fcolor,int dx,int dy);
//平滑显示专用
public:
	void ShowAct(CDIB&mdc,int dx,int dy);
	void ShowS(CDIB&mdc,int dx,int dy,int high);
	//平滑显示
	void ShowSysPie(CDIB&mdc, int dx, int dy);
	void ShowZone(CDIB&mdc,int dx, int dy);
	void ShowReservoir(CDIB&mdc,int dx, int dy);
	void ShowMeter1(CDIB&mdc,int dx, int dy);
	void ShowImg(CDIB&mdc, int dx, int dy);
	void ShowScrText(CDIB &mdc, int dx, int dy);
	void ShowFlow(CDIB&mdc, int dx, int dy);
	void ShowYb(CDIB&mdc, int dx, int dy);
	void ShowEleGrp(CDIB&mdc, int dx, int dy,int high,int active=0);
	void ShowPctPie(CDIB&mdc,int dx,int dy);
	void ShowBus(CDIB&mdc, int dx, int dy,int high);
	void ShowConLine(CDIB&mdc, int dx, int dy);
	void ShowFlowLine(CDIB&mdc, int dx, int dy,int high);
	void ShowTime(CDIB&mdc, int dx, int dy);
	void ShowDate(CDIB&mdc, int dx, int dy);
	void ShowPie(CDIB&mdc, int dx, int dy);
	void ShowBar(CDIB&mdc, int dx, int dy);
	void ShowTable(CDIB&mdc, int dx, int dy);
	void ShowCoordnate(CDIB&mdc, int dx, int dy);
	void ShowGlass(CDIB&mdc,int dx,int dy);
	void ShowArrow(CDIB&mdc, int dx, int dy,int high);
	void ShowArc(CDIB&mdc, int dx, int dy,int high);
	void ShowSin(CDIB&mdc, int dx, int dy,int high);
	void ShowHSin(CDIB&mdc, int dx, int dy,int high);
	void ShowCircle(CDIB&mdc, int dx, int dy,int high);
	void ShowRect(CDIB&mdc, int dx, int dy,int high);
	void ShowDbx(CDIB&mdc, int dx, int dy,int high,int bgmode);
private:
	//void DrawPie(CDIB&mdc,CDRect &rt,DWORD c1,DWORD c2,DWORD c3,double pw,int dx,int dy);
	void ShowGenPie(CDIB&mdc,CDRect art,float maxv,float curv,int deg,DWORD color,int dx,int dy);
	void PreBusEGPEx(CDIB&mdc,int num,int index,int dx,int dy,int high);
	void ShowES(CDIB&mdc,int dx, int dy,int high);
	void PreShowEGPYB(CDIB&mdc,int num,int dx,int dy);
	void PreShowEGPExDy(CDIB&mdc,int num,int index,int dx,int dy,int high);
	void PreShowEGPEx(CDIB&mdc,int num,int index,int dx,int dy,int high);
	void DrawPie(CDIB&mdc,CDRect &rt,DWORD c1,DWORD c2,DWORD c3,double pw,int dx,int dy);
};

#endif // !defined(AFX_DOBJ_H__8FD77ECC_72D9_4985_9763_F299D2B74D5E__INCLUDED_)
