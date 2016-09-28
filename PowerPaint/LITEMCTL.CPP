// litemctl.cpp : implementation file
//

#include "stdafx.h"
#include "litemctl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// litemctl

litemctl::litemctl()
{
	addr=NULL;
}

litemctl::~litemctl()
{
}


BEGIN_MESSAGE_MAP(litemctl, CComboBox)
	//{{AFX_MSG_MAP(litemctl)
	ON_CONTROL_REFLECT(CBN_SELCHANGE, OnSelchange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// litemctl message handlers

void litemctl::SetDataLink(BYTE type1, char *buff,WORD recno)
{
    int n;
	type=type1;
	addr=buff;
	rec=recno;
	n=GetEditValue();
	SetCurSel(n);
}

void litemctl::OnSelchange() 
{
	float  *flt;
	char   *ch;
	short  *sh;
	int    *in;
	BYTE   *by;
	WORD   *wd;
	DWORD  *dw;
	double *dbl;
	BOOL   *BOL;
	bool   *bol;
	int n;
	if(addr==NULL) return;
	n=GetCurSel();
	switch(type){    
	case EDIT_FLOAT:
		flt=(float*)addr;
        flt[0]=(float)n;
		break;
    case EDIT_STR:
		GetLBText(n,addr);
		break;
	case EDIT_CHAR:
        ch=(char*)addr;
		ch[0]=(char)n;
		break;
	case EDIT_SHORT:
		sh=(short*)addr;
		sh[0]=(short)n;
		break;
	case EDIT_INT:
        in=(int*)addr;
		in[0]=n;
		break;
	case EDIT_BYTE:
        by=(BYTE*)addr;
		by[0]=(BYTE)n;
		break;
	case EDIT_WORD:
        wd=(WORD*)addr;
		wd[0]=(WORD)n;
		break;
	case EDIT_DWORD:
        dw=(DWORD*)addr;
		dw[0]=(DWORD)n;
		break;
	case EDIT_DOUBLE:
        dbl=(double*)addr;
		dbl[0]=(double)n;
		break;
	case EDIT_BOOL:
		BOL=(BOOL*)addr;
		BOL[0]=n==0 ? 0:1;
		break;
	case EDIT_bool:
		bol=(bool*)addr;
		bol[0]=n==0 ? 0:1;
		break;
    default:
		return;
		};
	GetParent()->GetParent()->SendMessage(WM_COMMAND,DataChanged,rec);
	
}

int litemctl::GetEditValue()  //·µ»Ø×Ö·û´®
{
	float  *flt;
	char   *ch;
	short  *sh;
	int    *in;
	BYTE   *by;
	WORD   *wd;
	DWORD  *dw;
	double *dbl;
	BOOL   *BOL;
	bool   *bol;
    int n;
	if(addr==NULL) 	return 0;
	switch(type){     
	case EDIT_FLOAT:
		flt=(float*)addr;
        n=(int)flt[0];
		break;
    case EDIT_STR:
		n=FindStringExact(0,addr);
		if(n==CB_ERR) n=0;
		break;
	case EDIT_CHAR:
        ch=(char*)addr;
		n=ch[0];
		break;
	case EDIT_SHORT:
		sh=(short*)addr;
		n=sh[0];
		break;
	case EDIT_INT:
        in=(int*)addr;
		n=in[0];
		break;
	case EDIT_BYTE:
		by=(BYTE*)addr;
		n=by[0];
		break;
	case EDIT_WORD:
		wd=(WORD*)addr;
		n=wd[0];
		break;
	case EDIT_DWORD:
		dw=(DWORD*)addr;
		n=(int)dw[0];
		break;
	case EDIT_DOUBLE:
		dbl=(double*)addr;
		n=(int)dbl[0];
		break;
	case EDIT_BOOL:
		BOL=(BOOL*)addr;
		n=BOL[0];
		break;
	case EDIT_bool:
		bol=(bool*)addr;
		n=bol[0];
		break;
    default:
		n=0;
	}
	return n;
}

LRESULT litemctl::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if(message==WM_KEYDOWN){
		if(wParam==VK_DOWN||wParam==VK_UP){
		 GetParent()->SendMessage(message,wParam,lParam);
		};
	};
	return CComboBox::WindowProc(message, wParam, lParam);
}