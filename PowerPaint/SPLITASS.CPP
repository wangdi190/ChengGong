#include "stdafx.h"
#include "splitass.h"

SplitAss::SplitAss(){
	pwin=NULL;
	wnd1=NULL;
	wnd2=NULL;
	style=0;
	title[0]=0;
	position=0;
	font.CreateFont(16, 8,0,0,400,0,0,0,1,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH,"宋体" );
	pen.CreatePen(PS_SOLID,4,RGB(0x44,0x44,0x44));
	dnbz=0;		  //压下鼠标标志
	cursor=0;     //当前鼠标
	closebz=0;
	hcurx=LoadCursor(NULL,IDC_SIZEWE);
	hcury=LoadCursor(NULL,IDC_SIZENS);
};
SplitAss::~SplitAss(){
	font.DeleteObject();
	pen.DeleteObject();
	DeleteObject(hcurx);
	DeleteObject(hcury);
};

void SplitAss::Create(CWnd *cwnd,CWnd *cwnd1,CWnd *cwnd2,char *text,int sty){
  	pwin=cwnd;
	wnd1=cwnd1;
	wnd2=cwnd2;
	titlebz=0;
	if(text!=NULL){
		if(strlen(text)>0){
		strcpy(title,text);
		titlebz=1;
		};
	};
	style=sty==0 ? 0:1;
};
void SplitAss::SetInitPosition(int pos){
	position=pos;
	ComputRect();
	if(pwin==NULL||wnd1==NULL||wnd2==NULL) return;
	wnd1->MoveWindow(rw1);
	wnd2->MoveWindow(rw2);
	pwin->Invalidate();
};
void SplitAss::OnMouseMove(CPoint point){
	CRect rt;
	if(dnbz==0&&closebz!=1){
	switch(style){
	case 0:
	  rt.left=position-3;
	  rt.right=position+3;
	  rt.top=titlebz*28;
	  rt.bottom=wy;
	  if(rt.PtInRect(point)){
		cursor=1;
		SetCursor(hcurx);
		pwin->SetCapture();
	  }else{
		  cursor=0; 
		  ReleaseCapture();
	  };
  	  break;
	case 1:
	  rt.left=0;
	  rt.right=wx;
	  rt.top=wy-position-3;
	  rt.bottom=rt.top+6;
	  if(rt.PtInRect(point)) {
		  SetCursor(hcury);
		  pwin->SetCapture();
		  cursor=2;
	  }else {
		  cursor=0;
		  ReleaseCapture();
	  };
   	  break;
	};
	};
	if(cursor>0&&dnbz==1){  //移动时画线
		switch(cursor){
		case 1:
			position=point.x;
			break;
		case 2:
			position=wy-point.y;
			break;
		};
		drawxorline(opos);
		drawxorline(point);
	};
};
void SplitAss::OnLButtonDown(CPoint point){
	if(pwin==NULL||wnd1==NULL||wnd2==NULL) return;
	CClientDC dc(pwin);
	if(cursor>0){
	 dnbz=1;
	 drawxorline(point); 
	};
	CRect rt(wx-28,2,wx-6,22);
	if(rt.PtInRect(point)){
      dc.Draw3dRect(rt,RGB(0x00,0x00,0x00),RGB(0xff,0xff,0xff));
	  closebz=1;
	};
	pwin->SetCapture();
};
void SplitAss::OnLButtonUp(CPoint point){
	CRect rt;
	if(pwin==NULL||wnd1==NULL||wnd2==NULL) return;
	if(closebz=1){
		rt=CRect(wx-28,2,wx-6,22);
		pwin->InvalidateRect(rt);
		closebz=0;
		if(rt.PtInRect(point)) pwin->SendMessage(WM_COMMAND,1200,0);
		};
	if(cursor>0){
		switch(style){
		case 0:
		 position=point.x;	
		 position=position<2 ? 2:position;
		 position=position>wx-3 ? wx-3:position;
		 position=position>240 ? 240:position;
		 break;
		case 1:
		 position=wy-point.y;
		 position=position>wy-3 ? wy-3:position;
		 position=position<2 ? 2:position;
		 break;
		};
		ComputRect();
		wnd1->MoveWindow(rw1);
		wnd2->MoveWindow(rw2);
		pwin->Invalidate();
	};
	ReleaseCapture();
	dnbz=0;
};
void SplitAss::OnSize(int cx,int cy){
	if(pwin==NULL||wnd1==NULL||wnd2==NULL) return;
	wx=cx;
	wy=cy;	
	switch(style){
		case 0:
		 position=position<2 ? 2:position;
		 position=position>wx-3 ? wx-3:position;
		 break;
		case 1:
		 position=position>wy-3 ? wy-3:position;
		 position=position<2 ? 2:position;
		 break;
		};
	ComputRect();
	wnd1->MoveWindow(rw1);
	wnd2->MoveWindow(rw2);
};

void SplitAss::OnPaint(CDC&dc){
	CRect rt;
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(0x00,0x00,0x00));
	dc.SelectObject(&font);
    if(titlebz==1){
	 dc.FillSolidRect(CRect(0,0,wx,29),GetSysColor(COLOR_3DFACE));
	 dc.DrawText(title,strlen(title),CRect(10,4,wx-8,24),DT_LEFT);
	 dc.Draw3dRect(CRect(0,0,wx,24),RGB(0x7f,0x7f,0x7f),RGB(0xff,0xff,0xff));
	 dc.Draw3dRect(CRect(1,1,wx-1,23),RGB(0xff,0xff,0xff),RGB(0x7f,0x7f,0x7f));
	 dc.DrawFrameControl(CRect(wx-28,2,wx-6,22),DFC_CAPTION,DFCS_CAPTIONCLOSE|DFCS_FLAT   );
	 dc.Draw3dRect(CRect(wx-28,2,wx-6,22),GetSysColor(COLOR_3DFACE),GetSysColor(COLOR_3DFACE)); 
	};
	
	switch(style){
	case 0:
		rt.left=position-3;
		rt.right=position+3;
		rt.top=titlebz*28;
		rt.bottom=wy;
		dc.FillSolidRect(rt,GetSysColor(COLOR_3DFACE));
	    break;
	case 1:
		rt.left=0;
		rt.right=wx;
		rt.top=wy-position-3;
		rt.bottom=wy-position+3;
		dc.FillSolidRect(rt,GetSysColor(COLOR_3DFACE));
	    break;
	};

};

void SplitAss::ComputRect(){
	switch(style){
	case 0:   //x方向
	 rw1.left=0;
	 rw1.right=position-2;
	 rw1.top=titlebz*28;
	 rw1.bottom=wy;
	 rw2.left=position+3;
	 rw2.right=wx;
	 rw2.top=titlebz*28;
	 rw2.bottom=wy;
 	 break;
	case 1:   //y方向
	 rw1.left=0;
	 rw1.right=wx-1;
	 rw1.top=titlebz*28;
	 rw1.bottom=wy-position-3;
	 rw2.left=0;
	 rw2.right=wx-1;
	 rw2.top=wy-position+3;
	 rw2.bottom=wy;
	break;
	};
	};

void SplitAss::drawxorline(CPoint point)  //移动竖条时画线
{
	if(pwin==NULL||wnd1==NULL||wnd2==NULL) return;
	CClientDC dc(pwin);
	dc.SetROP2(R2_XORPEN);
	dc.SelectObject(&pen);
	switch(style){
	case 0:
	 dc.MoveTo(point.x,titlebz*28);
	 dc.LineTo(point.x,wy);
	 opos=point;
	 break;
	case 1:
	 dc.MoveTo(0,point.y);
	 dc.LineTo(wx,point.y);
	 opos=point;
	 break;
	}
}