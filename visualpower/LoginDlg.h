#if !defined(AFX_LOGINDLG_H__30D1738B_5EE1_4167_9EE5_F9E5A746E940__INCLUDED_)
#define AFX_LOGINDLG_H__30D1738B_5EE1_4167_9EE5_F9E5A746E940__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LoginDlg.h : header file
//
typedef struct USER1{ //用户
	char name[20];
}USER1;


typedef struct SAVUSR{  //联机用户暂存结构
 char name[20];			//当前用户名
 char password[20];		//当前用户密码
 char usum;				//需要列表的用户数<=8个
 USER1 ulst[8];			//最多8个用户
 char ecode;			//解码
 char ccode;			//校验码
}SAVUSR;
/////////////////////////////////////////////////////////////////////////////
// LoginDlg dialog

class LoginDlg : public CDialog
{
// Construction
public:
	LoginDlg(CWnd* pParent = NULL);   // standard constructor
	int tm;
// Dialog Data
	//{{AFX_DATA(LoginDlg)
	enum { IDD = IDD_LOGIN };
	CComboBox	m_nlst;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LoginDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(LoginDlg)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeUsername();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool Decode();
	void Encode();
	void AddToList(char *name);
	void Savesfg();
	void LoadSavCfg();
	int curg,curu;
	SAVUSR sur;
	int rdbz; //正确读取
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGINDLG_H__30D1738B_5EE1_4167_9EE5_F9E5A746E940__INCLUDED_)
