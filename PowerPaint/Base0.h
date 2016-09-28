// BASE0.h: interface for the BASE0 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASE0_H__DB95CF91_EE55_4D97_8A17_B5F5383E9274__INCLUDED_)
#define AFX_BASE0_H__DB95CF91_EE55_4D97_8A17_B5F5383E9274__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "PTDEFINE.H"
#include "bclass.h"

class BASE0  
{
public:
	void SetAnlIdType(int id,int type);
	bool GetAnlDevType(char *name,BYTE &type);
	bool IsSame(BASE0 &base);
	CDRect GetObjRect();
	void SetColor(DWORD color);
	void SetFont(LOGFONT&font);
	void SetVLevel(BYTE vl);
	bool SetStaVal(R_STA &v);
	bool SetAnlVal(R_ANL &v);
	void ShowFlow(HDC hdc,int dx, int dy,int pm=0);
	void ShowActGrp(CDIB &mdc,int dx, int dy,int mode=0);
	void ShowBasGrp(CDIB &mdc,int dx, int dy);
	void Print(HDC hdc,int pm,int dx, int dy);
	void ReSetValue(N_BASATTR &atr, void *obuf);
	void SetDevName(char *dev_name,int type=-1,int subtype=-1);
	void SetDevSource(char *dev_name, int djlh);
	void SetDevName_VL(char *dev_name, int vl1=-1,int vl2=-1,int vl3=-1);
	void SetEmpty();
	void SetLineWidth(double bl);
	void StraightObj();
	void SqrtObj();
	bool IsRotateObj();
	bool IsDeviceObj();
	void Offset(double dx, double dy);
	bool GetDevType(BYTE &type, BYTE &subtype,BYTE &vl,char *dev_name,int &jlh);
	HRGN CreateRGN();
	bool RtInRect(CDRect rect);
	CDRect CreateOldRect();
	void EndMOveObject();
	void SetSObjZM(double zm);
	void MoveObject2(CDRect prt, double xl, double yl);
	void MoveObject1(double mx, double my,int opno);
	DPOINT *GetObjectPt(int&ptsum,int &fill,int &close,int mode=0);
	void SetSelected(int selindex=1);
	bool PtInObject(CPoint point);
	void ClearSel();
	void ShowE(HDC hdc,int dx, int dy,int pm=0);
	void Show(CDIB &mdc,int dx, int dy);
	void AddObject(N_BASATTR &atr, void *obuf,int mode=0);
	void FreeMem();
	BASE0();
	virtual ~BASE0();
	N_BASATTR  attr;			//图形基本属性
	BYTE       sel;				//选中标记
	CDRect     ort;				//所占的矩形区域
	void       *buf;			//对象数据
	void       *bakbuf;			//对象数据备份
	BYTE       questdot;		//问题点(创建连接关系时产生)

	//平滑显示
	void ShowSysPie(HDC hdc, int dx, int dy);
	void ShowZone(CDIB&mdc,int dx, int dy);
	void ShowReservoir(CDIB&mdc,int dx, int dy);
	void ShowMeter1(CDIB&mdc,int dx, int dy);
	void ShowAnl(CDIB&mdc, int dx, int dy);
	void ShowBus(CDIB&mdc, int dx, int dy);
	void ShowConLine(CDIB&mdc,int dx, int dy);
	void ShowFlow(CDIB&mdc,int dx, int dy);
	void ShowArc(CDIB&mdc, int dx, int dy);
	void ShowESite(CDIB&mdc, int dx, int dy);
	void ShowArrow(CDIB&mdc, int dx, int dy);
	void ShowSin(CDIB&mdc, int dx, int dy);
	void ShowHSin(CDIB&mdc, int dx, int dy);
	void ShowE(CDIB&mdc,int dx, int dy);
	void PreShowEGPEx(CDIB&mdc,int num,int index,int dx,int dy);
	void PreBusEGPEx(CDIB&mdc,int num,int index,int dx,int dy);
	void ShowEleGrp(CDIB&mdc, int dx, int dy);
	void ShowYb(CDIB&mdc, int dx, int dy);
	void ShowDbx(CDIB&mdc,int dx, int dy);
	void ShowCircle(CDIB&mdc,int dx, int dy);
	//////////////////////////////////////////////////////////////////////////
	void OffsetRt(CRect&rt,int wh,int direct,int qh);
	CRect CreateDrawRect(int ptsum,DPOINT *pt,int dx,int dy);
	void InitSelfCtl();
	void DrawBar(HDC hdc,CRect  drt,N_BAR &bar);
	void DrawTable(HDC hdc,CRect drt,N_TABLE &ta,int pm=0);
	void DrawCoordinate(HDC hdc,CRect drt,int mode,N_COORDINATE &co,int pm);
	void CreateSelRect();
	void PreShowEGPEx(HDC hdc,int num,int index,int dx,int dy,int pm=0);
	void PreBusEGPEx(HDC hdc,int num,int index,int dx,int dy,int pm=0);
	void PreShowEGPYB(HDC hdc,int num,int dx,int dy);
	void PreShowEGPYB(CDIB&mdc,int num,int dx,int dy);
	//图元显示
	void ShowZone(HDC hdc,int dx, int dy,int pm=0);
	void ShowReservoir(HDC hdc,int dx, int dy,int pm=0);
	void ShowFlash(HDC hdc, int dx, int dy,int pm=0);
	void ShowEleGrp(HDC hdc, int dx, int dy,int pm=0);
	void ShowYb(HDC hdc, int dx, int dy);
	void ShowActObj(HDC hdc,int dx, int dy);
	void ShowSpic(CDIB &mdc,int dx, int dy);
	void ShowSpic(HDC hdc,int dx, int dy);
	void ShowBus(HDC hdc, int dx, int dy,int pm=0);
	
	void ShowMTText(HDC hdc, int dx, int dy,int pm=0);
	void ShowConLine(HDC hdc,int dx, int dy,int pm=0);
	void ShowSlfCtl(HDC hdc, int dx, int dy);
	void ShowPush(CDIB&mdc, int dx, int dy);
	void ShowPush(HDC hdc, int dx, int dy);
	void ShowScrText(CDIB &mdc, int dx, int dy);
	void ShowScrText(HDC hdc, int dx, int dy,int pm=0);
	void ShowGifAnl(HDC hdc, int dx, int dy);
	void ShowTime(HDC hdc, int dx, int dy,int pm=0);
	void ShowDate(HDC hdc, int dx, int dy,int pm=0);
	void ShowPie(HDC hdc, int dx, int dy);
	void ShowBar(HDC hdc, int dx, int dy);
	void ShowAnl(HDC hdc, int dx, int dy,int pm=0);
	void ShowMeter1(HDC hdc,int dx, int dy);
	void ShowMeter2(HDC hdc, int dx, int dy);
	void ShowMeter3(HDC hdc, int dx, int dy);
	void ShowMeter4(HDC hdc, int dx, int dy);
	void ShowPath(HDC hdc,int dx, int dy,int pm=0);
	void ShowImg(CDIB&mdc, int dx, int dy);
	void ShowImg(HDC hdc, int dx, int dy);
	void ShowTable(HDC hdc, int dx, int dy,int pm=0);
	void ShowCoordnate(HDC hdc, int dx, int dy,int pm=0);
	void ShowEgpMb(HDC hdc, int dx, int dy,int pm=0);
	void ShowESite(HDC hdc, int dx, int dy,int pm=0);
	void ShowText(HDC hdc, int dx, int dy,int pm=0);
	void ShowGlass(CDIB&mdc,int dx, int dy);
	void ShowArrow(HDC hdc, int dx, int dy,int pm=0);
	void ShowArc(HDC hdc, int dx, int dy,int pm=0);
	void ShowSin(HDC hdc, int dx, int dy,int pm=0);
	void ShowHSin(HDC hdc, int dx, int dy,int pm=0);
	void ShowCircle(HDC hdc,int dx, int dy,int pm=0);
	void ShowRect(HDC hdc,int dx, int dy,int pm=0);
	void ShowDbx(HDC hdc,int dx, int dy,int pm=0);
	void ShowLine(HDC hdc, int dx, int dy);
	
	void DrawMPie(HDC hdc,CRect &rt,DWORD *cr,double *vp,int num,LOGFONT &lf,DWORD fcolor,int dx,int dy);
	void DrawPie(HDC hdc,CDRect &rt,DWORD c1,DWORD c2,DWORD c3,double pw,int dx,int dy);
	void DrawArrow(HDC hdc,DPOINT *pts,DWORD color);
private:
	void GetSubTxt(char *obuf,char *nbuf);
	void ChangeOtherDot(DPOINT *pt,int ptsum,int k);
};

#endif // !defined(AFX_BASE0_H__DB95CF91_EE55_4D97_8A17_B5F5383E9274__INCLUDED_)
