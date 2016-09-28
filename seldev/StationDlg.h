#if !defined(AFX_STATIONDLG_H__2D09C146_65DE_4CDB_A159_92FFC82A2D60__INCLUDED_)
#define AFX_STATIONDLG_H__2D09C146_65DE_4CDB_A159_92FFC82A2D60__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StationDlg.h : header file
//
#include "mstruct.h"
#include "visualdb.h"
/////////////////////////////////////////////////////////////////////////////
// StationDlg dialog

class StationDlg : public CDialog
{
// Construction
public:
	StationDlg(CWnd* pParent = NULL);   // standard constructor
	~StationDlg();
	char dbfile[256];
	visualpw_Zone *zone;//保存域
	int zsum;			//域总数
	visualpw_Station *sta;//站
	int snum;			//站总数
	int mode;
	bool dbok;
// Dialog Data
	//{{AFX_DATA(StationDlg)
	enum { IDD = IDD_DEVSTATION };
	CComboBox	m_szone;
	CListCtrl	m_lst;
	CComboBox	m_mode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(StationDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(StationDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeMode();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCreate();
	afx_msg void OnDelete();
	afx_msg void OnModi();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void AppendData(visualpw_Station &tmp);
	void ModiData(int j,visualpw_Station &tmp);
	bool IsExistID(int id);
	void SetStationList();
	void ReadStation();
	int GetZoneIndex(int id);
	void SetZoneList();
	void GetZone();
	void EnableItem(int id,bool enable);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATIONDLG_H__2D09C146_65DE_4CDB_A159_92FFC82A2D60__INCLUDED_)
