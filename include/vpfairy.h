// vpfairy.h: interface for the vpfairy class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VPFAIRY_H__8FC58859_F713_42A9_92E3_AE717E8A1CAB__INCLUDED_)
#define AFX_VPFAIRY_H__8FC58859_F713_42A9_92E3_AE717E8A1CAB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*vpf(可视化程序精灵)界面控制类 VC++专用
  第一版:2002.5由陈金海设计
*/
#define  PWIDOK     1500
#define  PWIDCANCEL 1501
#include "vpfdata.h"

class vpfairy : public Vpfdata
{
public:
	void SetText(int id,char *str);
	void SetLineEnable(int id, BYTE enable);
	void SetEgrpEnable(int recno,BYTE enable);
	void SetPicDepth(BYTE depth,int id);
	void SetPieData(int pieid,NPIEDAT *pd);
	HWND GetSelfCtl(int selftid);
	void EnablePush(int pushid,bool enable);
	vpfairy();
	virtual ~vpfairy();
	CWnd * GetComCtl(int ctlid);
	bool SetRateValue(int recno, R_RAT &v);
	bool SetRateValue(char *id, R_RAT &v);
	bool SetStatusValue(int recno, R_STA &v);
	bool SetStatusValue(char *id,R_STA &v);
	bool SetAnalogValue(int recno,R_ANL &v);
	bool SetAnalogValue(char *id,R_ANL &v);
	bool GetObjNameRecNo(int type,WORD index,char *name,int &recno);
	int  GetObjectSum(int type);
	int  CreateDlg(CDialog &thisdlg,DWORD wstyle,CWnd* pParentWnd);
	bool SetDlgPage(CWnd *cwnd, char *filename, int pageno);
	int  SetModalDilaog(CDialog &dlg,CWnd *pwnd=NULL);
	bool SetWinPage(CWnd *cwnd,char *filename,int pageno);
	LRESULT vpfWndProc(UINT message, WPARAM wParam, LPARAM lParam);
protected:
	bool SetNewWndProc(vpfairy *lpvpf);
private:
	void RunPushCmd(N_PUSH *ph);
	BOOL OnSetCursor(UINT nHitTest, UINT message);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnTimer(UINT nIDEvent);
	void OnPaint();
	bool proccanuse;
	HCURSOR tcur[3];		//光标
	int  dlgbz;				//对话框标志
	CDialog *vdlg;			//所属对话框
};

#endif // !defined(AFX_VPFAIRY_H__8FC58859_F713_42A9_92E3_AE717E8A1CAB__INCLUDED_)
