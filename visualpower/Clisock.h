#if !defined(AFX_CLISOCK_H__BD042B26_80D6_11D3_ACC1_444553540000__INCLUDED_)
#define AFX_CLISOCK_H__BD042B26_80D6_11D3_ACC1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// clisock.h : header file
//
#include <winsock2.h>
#define WSA_VERSION  0x101
#define WSA_ASYNC    WM_USER+1
#define MAXIN        64000 //数据包大小
#define RECDATA      1000  //当有数据来时主窗口收到的消息
#define SVRCLOSE     1101  //服务器关闭 

typedef struct _DATAHEAD{
  char  flag1;              //标志=0x78
  WORD  len;                //长度<MAXIN 数据块的字节数
  unsigned char compress:1; //压缩标志 0=未压缩 1=压缩
  unsigned char reserved:7; //未用，保留
  char  check;              //校验：异或和
}DATAHEAD;

typedef struct NETBUFFC{ //发送任务清单数据
  BYTE   level;			//紧急级别0,1,2,3
  DWORD  len;			//字节数
  char   *buf;			//缓冲区
}NETBUFFC;

/////////////////////////////////////////////////////////////////////////////
// clisock window

class clisock : public CWnd
{
// Construction
public:
	clisock();
	int nAdapter;       //网卡数
	in_addr ad[6];		//网卡地址
	char connect_svr;
	char netstatus;
	int curnet;			//当前连接的网卡号
// Attributes
public:
	char *GetRecBuf(DWORD &n);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(clisock)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	int  GetData(char *buf,int n);
	int  senddata(char *buf,int len);
	void slogout();
	int  ReInitNet(in_addr laddr);   //重新初始化网络
    virtual ~clisock();
	int Connect(in_addr laddr,WORD port);
	// Generated message map functions
protected:
	//{{AFX_MSG(clisock)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void rechead();
	BOOL Enumerate();
	void recdata();
	int  SendToNet(char *buf, int len);
	void SendBuffer();
	void DeleteNbuff(int j);
	bool AddToBuff(char *buf, int len,int level);
	int  onWSAEvent(UINT wParam,LONG lParam);
	NETBUFFC  nbuf[1024];		//发送缓存
	int       bsum;				//有效缓冲区数
	char sbuffer[MAXIN+10];		//发送数据区
	char rbuffer[MAXIN+10];     //接收数据区
	int  dlen; 					//报文总长度
    int  rlen;                  //已读到的字节数
	char hbuf[10];              //传输头接收缓冲区
	char recflag;               //已接收到头标志
	HWND r_hWnd;                //所服务的窗口句柄
    SOCKADDR_IN sd,svradd;
    SOCKET  sid;
    WSADATA wsadata;
    LPSTR IPAddrStr;
	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLISOCK_H__BD042B26_80D6_11D3_ACC1_444553540000__INCLUDED_)
