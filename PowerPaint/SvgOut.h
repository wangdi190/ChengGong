// SvgOut.h: interface for the SvgOut class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SVGOUT_H__B0BE8DB5_68A0_4DBD_BC8E_EC609819E73C__INCLUDED_)
#define AFX_SVGOUT_H__B0BE8DB5_68A0_4DBD_BC8E_EC609819E73C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "gdata.h"


class SvgOut  
{
public:
	void DefineEleGrp();
	void DrawOnSvgFile();
	void WriteSvgHead();
	void CloseFile();
	bool OpenWFile(char *filename);
	SvgOut();
	virtual ~SvgOut();
	FILE *fp; //当前处理的文件
	N_PAGEPWF  *cpage; //当前页面
	N_ELEGRP *egp;	   //组合图元
	int  egpsum;	   //当前的组合图元数
private:
	void EgpTran(BASE0 *bs,int id,int index,int sum);
	void DrawEleGrp(BASE0&bs,int gp=1);
	int  ANSIToUtf8(char  *ostr,BYTE *nstr,int maxbuf);
	void GStyleOut(int fill,DWORD fcolor,DWORD lcolor,float lwidth,int gp);
	void DrawObj(BASE0&bs);
	void ChangeFontFaceName(char *oldname,char *newname);
	void ShowEleBus(BASE0 &bs);
	void ShowDigit(char *text,float val,char *pre,char *unit,char xs);
	void ShowDigitPQ(char *text,float vp,float vq,char xs);
	void DrawCoordinate(CRect drt,N_COORDINATE &co);
	void GetColorStr(char *str,DWORD color);

	void ShowTime(BASE0&bs);
	void ShowDate(BASE0&bs);
	void ShowPie(BASE0 &bs);
	void ShowCoordnate(BASE0 &bs);
	void ShowTable(BASE0 &bs);
	void ShowPctPie(BASE0 &bs);
	void ShowBar(BASE0 &bs);
	void ShowAnalog(BASE0 &bs);
	void ShowEleGrp(BASE0 &bs);
	void ShowConline(BASE0 &bs);
	void ShowBus(BASE0 &bs);
	void ShowFlow(BASE0 &bs);
	void ShowEgpMb(BASE0 &bs,int gp=0);
	void ShowEsite(BASE0 &bs,int gp=0);
	void ShowText(BASE0 &bs,int gp=0);
	void ShowGlass(BASE0 &bs,int gp=0);
	void ShowArrow(BASE0 &bs,int gp=0);
	void ShowArc(BASE0 &bs,int gp=0);
	void ShowSin(BASE0 &bs,int gp=0);
	void ShowHSin(BASE0 &bs,int gp=0);
	void ShowCircle(BASE0 &bs,int gp=0);
	void ShowRect(BASE0 &bs,int gp=0);
	void ShowDbx(BASE0 &bs,int gp=0);
};

#endif // !defined(AFX_SVGOUT_H__B0BE8DB5_68A0_4DBD_BC8E_EC609819E73C__INCLUDED_)
