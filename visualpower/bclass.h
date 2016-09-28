// bclass.h: interface for the APoint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCLASS_H__A4F4DF7B_CC4F_454F_802B_315C1609E44C__INCLUDED_)
#define AFX_BCLASS_H__A4F4DF7B_CC4F_454F_802B_315C1609E44C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "pwptdef.h"

/////////////////////////////////////////////////////////////
//2006.7.3
void ShowMPt1(HDC hdc,DPOINT cpt,double r,double angle,int axw,int pw,DWORD color);
void ShowMPt2(HDC hdc,DPOINT cpt,double r,double angle,int axw,int pw,DWORD color);
void ShowMPt3(HDC hdc,DPOINT cpt,double r,double angle,int axw,int pw,DWORD color);
void ShowMPt4(HDC hdc,DPOINT cpt,double r,double angle,int axw,int pw,DWORD color);
void ShowMPt5(HDC hdc,DPOINT cpt,double r,double angle,int axw,int pw,DWORD color);

void ShowMPt1(CDIB&mdc,DPOINT cpt,double r,double angle,double axw,double pw,DWORD color);
void ShowMPt2(CDIB&mdc,DPOINT cpt,double r,double angle,double axw,double pw,DWORD color);
void ShowMPt3(CDIB&mdc,DPOINT cpt,double r,double angle,double axw,double pw,DWORD color);
void ShowMPt4(CDIB&mdc,DPOINT cpt,double r,double angle,double axw,double pw,DWORD color);
void ShowMPt5(CDIB&mdc,DPOINT cpt,double r,double angle,double axw,double pw,DWORD color);

void ShowKd1(HDC hdc,POINT pt1,POINT pt2,DWORD color);

void ShowKd1(CDIB&mdc,DPOINT pt1,DPOINT pt2,DWORD color);

//2006.4.20新加/改的功能
int GetLineLength(DPOINT *pt,int n);
HRGN BCreateLineRGN1(POINT ps, POINT pe,double width);
void StartRatate(HDC hdc,double angle,float cx,float cy);
void SetIncline(HDC hdc,double angle);
void PointActToScr(DPOINT *inpt,DPOINT *outpt,int ptsum,double curzoom);
void PointActToScr(DPOINT *inpt,POINT *outpt,int ptsum,double curzoom);
//HRGN Get3dBarRGN(CDRect rt,int h1);
//HRGN Get3dTaperRGN(CDRect rt,int h1);
//HRGN Get3dTaperuRGN(CDRect rt,int h1);
CRect CreateCRt(int ptsum,POINT *pt);  
HRGN SCreateLineRGN(POINT *pt,int ptsum);
DPOINT  GetPosition(DPOINT *pt,int npt,double min,double max,double value);

CDRect CreateNRt(int ptsum,DPOINT *pt);
float GetSingleVal(READDEV&data,int xsmode);
void DrawPoly(HDC hdc,CPoint *pt,int ptsum,DWORD lcolor,DWORD fcolor,int fill,int close,int w=1);
void DrawPoly(CDIB&mdc,CPoint *pt,int ptsum,DWORD lcolor,DWORD fcolor,int fill,int close);


void PtOffset(DPOINT *in,POINT *out,int n,int dx,int dy);
void PtOffset(POINT *pt,int n,int dx,int dy);
//////////////////////////////////////////////////////////////
void BDrawButton(HDC hdc,CRect rt,char *text,LOGFONT *lf,int downup,int enable);
double GetPercent(double curval,double maxv);
DWORD GetPctPieColor(DWORD color,double pct);
int  GetPctPieCirclePt(DPOINT *pt,CDRect &art,double pct,int flowover);
void GetHalfCircle(int &s,DPOINT *inpt,DPOINT *outpt);
///////////////////////////////////////////////////////////////////////////////
HRGN DY_GetActObjRgn(HRGN oldhrgn,RACTOBJ  *r_at,int atsum,int dx,int dy,double curzoom);
HRGN DY_GetScrtxtRgn(HRGN oldhrgn,RSCRTXT  *r_sc,int scsum,CRect srt,int dx,int dy,double curzoom);
HRGN DY_GetYBRgn(HRGN oldhrgn,RMETER   *r_yb,int ybsum,CRect srt,int dx,int dy,double curzoom);
HRGN DY_GetGifAmlRgn(HRGN oldhrgn,RAML  *r_am,int  amsum,CRect srt,int dx,int dy,double curzoom);
HRGN DY_GetGenRgn(CDIB &mdc,HRGN oldhrgn,RREV  *r_rv,int rvsum,CRect srt,int dx,int dy,int gendyn,double curzoom);
void ComputFlowJs(RFLOW *r_fw,int fwsum,int showtype);
void ComputGenJs(RREV  *r_rv,int rvsum);
void ComputGifAmlJs(RAML *r_am,int amsum);

void DRectTo4Dpt(DRECT *rt,DPOINT *pt);
int GetLineSeg(double *slen,double &ys,double dis,int n);
////////////////////////////////////////////////////////////////////////////////////////////////////
void ComputeN1Zoom(N1BAR *r_n1, int n1sum,double &zm,int wy);
////////////////////////////////////////////////////////////////////////////////////////////////////
void His_RegistFlow(RFLOW *flw,int flwsum);
void His_RegistBus(RBUS *bs,int bsum);
void His_RegistDev(RSTA *st,int stsum);
bool IsThisId(DWORD *ida,int maxn,DWORD idb);


void ShowDmDraw(HDC hdc,POINT *pt,int segsum,int *sdot);
void DrawDmLine(CDIB&mdc,POINT *pt,int segsum,int *sdot);

void ClrStrEnter(char *str);
void GetSflRunParam(SUBW_PARAM&pad,RSELFCTL&pas);
void RunFunctModule(char *mstring);

void GetSoeStr(char *str,NSOES *soe,int   soesum,int order,char *name);
void GetFlashDot(DPOINT *dpt,DPOINT cpt,double zoom);
void ComputeSelBra(int &id,int &linetype,RFLOW *r_fw,int fwsum,POINT *pt,int ptsum,double czm);

int GetLstSource(char *str,int *ofset,int maxl);
CRect CreateNRt(int ptsum,POINT *pt);

#endif // !defined(AFX_BCLASS_H__A4F4DF7B_CC4F_454F_802B_315C1609E44C__INCLUDED_)
