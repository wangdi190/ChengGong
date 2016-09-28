// GetIdDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PowerPaint.h"
#include "GetIdDlg.h"
#include "middll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GetIdDlg dialog


GetIdDlg::GetIdDlg(CWnd* pParent /*=NULL*/)
	: CDialog(GetIdDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(GetIdDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void GetIdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GetIdDlg)
	DDX_Control(pDX, IDC_PROGRESS1, m_prg);
	DDX_Control(pDX, IDC_PNAME, m_pname);
	DDX_Control(pDX, IDC_NUM, m_num);
	DDX_Control(pDX, IDC_LNAME, m_lname);
	DDX_Control(pDX, IDC_DNAME, m_dname);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GetIdDlg, CDialog)
	//{{AFX_MSG_MAP(GetIdDlg)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GetIdDlg message handlers

BOOL GetIdDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetTimer(100,200,NULL);
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void GetIdDlg::RunGet()
{
	int i,j,k,m,djlh;
	SELECTDEV sd;
	BYTE type,subtype,vl;
	char dev_name[25];
	char p[100];
	BASE0 *obj;
	strcpy(sd.dbname,"visualpw");
	sd.type=2;

	for(i=0;i<dbm->pagesum;i++)
	{
		m_pname.SetWindowText(dbm->page[i].head.Name);
		for(j=0;j<dbm->page[i].laysum;j++)
		{
			sprintf(p,"%d层",j);
			m_lname.SetWindowText(p);
			obj=dbm->page[i].layer[j].obj;
			m=dbm->page[i].layer[j].objnum;
			m_prg.SetRange(0,m);
			for(k=0;k<m;k++)
			{
				m_prg.SetPos(k);
				sprintf(p,"%d/%d",k,m);
				m_num.SetWindowText(p);
				switch(obj[k].attr.type)
				{
				case 64:
					if(!obj[k].GetAnlDevType(dev_name,type)) continue;
					if(GetAnlMemID(dev_name,type,djlh))
					{
						obj[k].SetAnlIdType(djlh,type);	
					}
					break;
				default:
					if(!obj[k].GetDevType(type,subtype,vl,dev_name,djlh)) continue;
					if(type!=2) continue;
					//调用数据源设置程序		
					strcpy(sd.name,dev_name);
					sd.did=-1;
					sd.dtype=subtype;
	
					if(GetIDByName(sd))
					{
						obj[k].SetDevSource(sd.name,sd.did);	
						sprintf(p,"更新设备:名字=%s  id=%d ",sd.name,sd.did);
						m_dname.SetWindowText(p);
					}
					break;
				}
				Sleep(50);
			}
		}
	}
	dbm->editbz=0;
	CDialog::OnCancel();
	
}


void GetIdDlg::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent==100)
	{
		KillTimer(100);
		RunGet();
	}
	
	CDialog::OnTimer(nIDEvent);
}

//返回模拟量的ID和类型
bool GetIdDlg::GetAnlMemID(char *name,BYTE &type,int &id)
{
	bool rtn=false;
	SELECTDEV sd;
	sd.type=2;
	strcpy(sd.dbname,"visualpw");
	strcpy(sd.name,name);
	sd.did=-1;
	id=-1;
	switch(type)
	{
	case 0:
		sd.dtype=1;
		if(GetIDByName(sd))
		{
			id=sd.did;
			rtn=true;
		}
		break;
	case 1:
		sd.dtype=34;
		if(GetIDByName(sd))
		{
			id=sd.did;
			type=1;
			rtn=true;

		}else
		{
			sd.dtype=35;
			if(GetIDByName(sd))
			{
				id=sd.did;
				type=2;
				rtn=true;
			}
		}
		break;
	case 2:
		sd.dtype=35;
		if(GetIDByName(sd))
		{
			id=sd.did;
			type=2;
			rtn=true;

		}else
		{
			sd.dtype=34;
			if(GetIDByName(sd))
			{
				id=sd.did;
				type=1;
				rtn=true;
			}
		}
		break;
	case 3:
		sd.dtype=33;
		if(GetIDByName(sd))
		{
			id=sd.did;
			rtn=true;
		}
		break;
	case 4:
		sd.dtype=3;
		if(GetIDByName(sd))
		{
			id=sd.did;
			rtn=true;
		}
		break;
	case 5:
		sd.dtype=7;
		if(GetIDByName(sd))
		{
			id=sd.did;
			type=5;
			rtn=true;

		}else
		{
			sd.dtype=8;
			if(GetIDByName(sd))
			{
				id=sd.did;
				type=6;
				rtn=true;
			}
		}
		break;
	case 6:
		sd.dtype=8;
		if(GetIDByName(sd))
		{
			id=sd.did;
			type=6;
			rtn=true;

		}else
		{
			sd.dtype=7;
			if(GetIDByName(sd))
			{
				id=sd.did;
				type=5;
				rtn=true;
			}
		}
		break;
	case 7:
		sd.dtype=4;
		if(GetIDByName(sd))
		{
			id=sd.did;
			type=7;
			rtn=true;

		}else
		{
			sd.dtype=5;
			if(GetIDByName(sd))
			{
				id=sd.did;
				type=8;
				rtn=true;
			}
		}
		break;
	case 8:
		sd.dtype=5;
		if(GetIDByName(sd))
		{
			id=sd.did;
			type=8;
			rtn=true;
		}else
		{
			sd.dtype=4;
			if(GetIDByName(sd))
			{
				id=sd.did;
				type=7;
				rtn=true;
			}
		}
		break;
	default:
		rtn=false;
	}
	return rtn;		
}