// bclass.h: interface for the APoint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCLASS_H__A4F4DF7B_CC4F_454F_802B_315C1609E44C__INCLUDED_)
#define AFX_BCLASS_H__A4F4DF7B_CC4F_454F_802B_315C1609E44C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "ptdefine.h"
const double PI=3.1415926535;

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



void MoveObjRect(CDRect &rt,double mx,double my,int opno);
void HoldWH(CDRect &rt,double w,double h,int opno);

void PointOffset(DPOINT *in,POINT *out,int n,int dx,int dy);
void PointOffset(DPOINT *in,DPOINT *out,int n,int dx,int dy);
int  GetPctPieCirclePt(DPOINT *pt,CDRect &art,double pct,int flowover);
void BDrawButton(HDC hdc,CRect rt,char *text,LOGFONT *lf,int downup,int enable);
void PointActToScr(DPOINT *inpt,DPOINT *outpt,int ptsum,int dx,int dy,double zoom);
void PointActToScr(DPOINT *inpt,POINT *outpt,int ptsum,int dx,int dy,double zoom);
void DrawPoly(HDC hdc,CPoint *pt,int ptsum,DWORD lcolor,DWORD fcolor,int fill,int close,int w=1);
void DrawPoly(CDIB&mdc,CPoint *pt,int ptsum,DWORD lcolor,DWORD fcolor,int fill,int close);

void  GetptFromDRECT(DRECT&rt,DPOINT *pt);
DPOINT  GetPosition(DPOINT *pt,int npt,double min,double max,double value);
void BDrawDbx(HDC hdc,int num,POINT *pt,BYTE width,DWORD color,
			  DWORD colorb,BYTE type,BYTE lmode,BYTE endcap);
bool GetSinPoint(DPOINT *pt,DPOINT *spt,int np,int ptsum);
bool GetHSinPoint(DPOINT *pt,DPOINT *spt,int np,int ptsum);
double GetAngle(DPOINT p1,DPOINT p2);
double GetLength(DPOINT pt1,DPOINT pt2);
int  GetCirclePoint(DPOINT *pt,CDRect &art);
void BRotateObj(DPOINT  cpt,DPOINT &inpt,DPOINT &outpt,double angle);
void GetCircleDOT(DPOINT *pt,CRect rt,double zm);
int  GetDistance(CPoint p1, CPoint p2);
CDRect CreateNRt(int ptsum,DPOINT *pt);
HRGN CreateNRGN(int ptsum,DPOINT *pt,int type,int close,double zoom);
HRGN BCreateLineRGN(POINT ps, POINT pe,double width);
void NPolygonc(HDC hdc,POINT *point,int count,DWORD color1,DWORD color2);
void BDrawDIRSingle(CDIB&mdc,POINT ps,POINT pe,DWORD color,int width);
void BDrawDIRSingle(HDC hdc,POINT ps,POINT pe,DWORD color,int width);
void FillDbx(HDC hdc,POINT *pt,int ptsum,int color);
void DrawFlow(CDIB&mdc,POINT *pt,int ptsum,int start,int arrow,int w,int dis,DWORD color1,DWORD color2);
void DrawFlow(HDC hdc,POINT *pt,int ptsum,int start,int arrow,int size,int dis,DWORD color1,DWORD color2);
void ShowDigit(HDC hdc,CRect &rt,LOGFONT *lf,float val,char *pre,char *unit,char xs,DWORD color,BYTE style);
void ShowDigitPQ(HDC hdc,CRect &rt,LOGFONT *lf,float vp,float vq,char xs,DWORD color1,DWORD color2,BYTE style,BYTE direction);
void ShowAnalog(HDC hdc,CRect &rt,LOGFONT *lf,N_ANL *anl,int pm=0);

void ChangeMoveDot(DPOINT *pt,int ptsum,int k,int kxy);

bool SVGNameToCim(char *oldname,char *newname,int type,int &vl1,int &vl2,int &vl3);
bool SVGAnlNameToCim(char *oldname,char *newname,int type);
int  GetMsgType(char *msgname);
int  GetXsType(char *xsname);
int  SvgAnlTypeToXs(int type,int xstype);
CRect CreateNRt(int ptsum,POINT *pt);

#endif // !defined(AFX_BCLASS_H__A4F4DF7B_CC4F_454F_802B_315C1609E44C__INCLUDED_)
