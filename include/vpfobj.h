// Vpfobj.h: interface for the Vpfobj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_Vpfobj_H__INCLUDED_)
#define AFX_Vpfobj_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "vpfdef.h"

class Vpfdata;
//基本图元管理
class Vpfobj  
{
public:
	Vpfobj();
	virtual ~Vpfobj();
	N_BASATTR  attr;			//图形基本属性
	BYTE       enable;			//是否有效
	BYTE       sel;				//选择标记
	CRect      ort;				//所占的矩形区域
	void       *buf;			//对象数据(objflag=0)
	N_BASATTR  *bakatr;			//图形基本属性备份,选中时有效
	void       *bakbuf;			//对象数据(objflag=0)备份
	Vpfdata    *odbm;
public:
	bool SetStaVal(R_STA &v);
	bool SetRatVal(R_RAT&v);
	bool SetAnlVal(R_ANL&v);
	void Showdemo(CDIB &mdc,int dx, int dy);
	//打印专用
	void Print(HDC  hdc,BYTE pm,int dx,int dy);
	void PRT_Cure(HDC hdc,BYTE pm, int dx, int dy);
	void PRT_Push(HDC hdc,int dx, int dy);
	void PRT_Pie(HDC hdc,int dx, int dy);
	void PRT_Trend(HDC hdc,BYTE pm, int dx, int dy);
	void PRT_ESite(HDC hdc,BYTE pm, int dx, int dy);
	void PRT_ScrText(HDC hdc,BYTE pm, int dx, int dy);
	void PRT_Time(HDC hdc, BYTE pm,int dx, int dy);
	void PRT_Date(HDC hdc,BYTE pm, int dx, int dy);
	void PRT_ConLine(HDC hdc,BYTE pm, int dx, int dy);
	void PRT_Flow(HDC hdc,BYTE pm, int dx, int dy);
	void PRT_Bar(HDC hdc,BYTE pm, int dx, int dy);
	void PRT_CBar(HDC hdc,BYTE pm, int dx, int dy);
	void PRT_Line(HDC hdc,BYTE pm, int dx, int dy);
	void PRT_Dbx(HDC hdc, BYTE pm, int dx, int dy);
	void PRT_EGrp(HDC hdc,BYTE pm,int dx, int dy);
	void PRT_Sgrp(HDC hdc,BYTE pm,int dx, int dy);
	void PRT_HSin(HDC hdc,BYTE pm, int dx, int dy);
	void PRT_Sin(HDC hdc, BYTE pm,int dx, int dy);
	void PRT_Arrow(HDC hdc,BYTE pm, int dx, int dy);
	void PRT_Bus(HDC hdc,BYTE pm,int dx, int dy);
	void PRT_Text(HDC hdc,BYTE pm, int dx, int dy);
	void PRT_Anl(HDC hdc,BYTE pm,int dx, int dy);
	void PRT_Rate(HDC hdc,BYTE pm, int dx, int dy);
	void PRT_Arc(HDC hdc,BYTE pm, int dx, int dy);
	void PRT_EleGrp(HDC hdc,BYTE pm, int dx, int dy);
	void PreShowEGP(HDC hdc,BYTE pm,int num, CRect rt,int index,int dx,int dy);
public:
	void ShowBasGrp(CDIB &mdc,int dx, int dy);
	void ShowActGrp(CDIB &mdc,int dx, int dy);
	void ShowAllGrp(CDIB &mdc,int dx, int dy);
	void ShowAll(CDIB &mdc,int dx, int dy);
	void SetDadaSource(char *ds_name,WORD jlh);
	bool GetType(int &type,int &subtype,char *ds_name);
	bool GetDevSiteParam(int sitn, BYTE &vlev, BYTE &ele);
	bool PointInSite(CRect rt,int id,BYTE sstn,BYTE &dstn);
	void SetColor(DWORD color);
	void CreateSelRect();
	void SetEmpty();
	int  GetSize();
	int  CopyData(char *lpbuf);
	void Offset(int dx, int dy);
	void EndMOveObject();
	CRect CreateOldRect();
	void MoveObject2(CRect prt, double xl, double yl);
	void MoveObject1(int mx, int my, int mode);
	void SetSelected();
	bool ObjectInRect(CRect rect);
	bool RtInRect(CRect rect);
	bool PtInObject(CPoint point);
	void ClearSel();
	void Show(CDIB &mdc,int dx, int dy);
	void FreeMem();
	void AddObject(N_BASATTR&atr,void *obuf,Vpfdata *fdbm);
	void ShowFlow(HDC hdc, int dx, int dy);
	void FreeSftDll();
	void InitSelfCtl();
private:
	void ShowCure(CDIB &mdc, int dx, int dy);
	void ShowPshEGP(CDIB&mdc,int num, CRect rt,int index,int dx,int dy);
	void ShowEleGrp(CDIB &mdc,int dx, int dy);
	void PreShowEGPEx(CDIB&mdc,int num, CRect rt,int index,int dx,int dy);
	int  ComputPos(int wh, int type);
	void ShowBus(CDIB &mdc, int dx, int dy);
	void ShowConLine(CDIB &mdc, int dx, int dy);
	void ShowArc(CDIB &mdc, int dx, int dy);
	void ShowPush(CDIB &mdc, int dx, int dy);
	void ShowTime(CDIB &mdc, int dx, int dy);
	void ShowDate(CDIB &mdc, int dx, int dy);
	void ShowPie(CDIB &mdc, int dx, int dy);
	void ShowBar(CDIB &mdc, int dx, int dy);
	void ShowTrend(CDIB &mdc, int dx, int dy);
	void ShowRate(CDIB &mdc, int dx, int dy);
	void ShowAnl(CDIB &mdc, int dx, int dy);
	void ShowESite(CDIB&mdc,int dx, int dy);
	void ShowImg(CDIB&mdc,int dx, int dy);
	void ShowText(CDIB &mdc, int dx, int dy);
	void ShowCBar(CDIB &mdc, int dx, int dy);
	void ShowArrow(CDIB &mdc, int dx, int dy);
	void ShowGlass(CDIB &mdc, int dx, int dy);
	void ShowSin(CDIB &mdc, int dx, int dy);
	void ShowHSin(CDIB &mdc, int dx, int dy);
	void ShowSgrp(CDIB &mdc, int dx, int dy);
	void ShowEGrp(CDIB &mdc, int dx, int dy);
	void ShowDbx(CDIB &mdc, int dx, int dy);
	void MoveDbx(int mx, int my, int mode);
	void ShowSpic(CDIB &mdc,int dx, int dy);
	void ShowLine(CDIB &mdc, int dx, int dy);
	void ShowScrText(CDIB &mdc, int dx, int dy);
};


#endif // !defined(AFX_Vpfobj_H__570D7BAC_C074_42B8_8928_5D044A42692E__INCLUDED_)
