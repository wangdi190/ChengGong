// editobj.cpp: implementation of the editobj class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "editobj.h"
#include "gdata.h"
#include "comobj.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
extern gdata  dbm;
extern comobj cobj;

char *lst_fw[]={"同画线方向","反画线方向"};
char *lst_fw1[]={"交流","直流"};
char *lst_yesno[]={"否","是"};
char *lst_fillmd[]={"单色","过渡"};
char *lst_egrp[]={"平面","凹矩形","凸矩形"};
char *lst_sgrp[]={"椭园","矩型","球体","带边矩形"};
char *lst_vh[]={"水平","垂直"};
char *lst_bar[]={"左下原点","中间原点","右上原点"};
char *lst_btype[]={"平面","3D","普通圆形","用组合图元"};
char *lst_ltype[]={"实心线","点线","点划线","划线段","划点点线"};
char *lst_lmode[]={"正常","加外框"};
char *lst_tstyle[]={"正常显示","凹体显示","凸体显示"};
char *lst_shw[]={"无阴影","有阴影"};
char *lst_sta[]={"状态量","设备","站","局","自动"};
char *lst_day[]={"今日","昨日","上周","无效"};
char *lst_date[]={"yyyy-mm-dd","mm/dd/yyyy","yyyy年mm月dd日","星期W"};
char *lst_lstyle[]={"无","正常","凹","凸"};
char *lst_time[]={"hh:mm:ss","hh:mm","hh时mm分ss秒","hh点mm分ss秒","mm分ss秒"};
char *lst_tsty[]={"静止","上下","左右","下上","右左"};
char *lst_alg[]={"居左","居中","居右"};
char *lst_ptype[]={"普通按钮","不可见按钮","滑过凸形按钮","滑过凹形按钮","滑过变色按钮","位图按钮","组合图元按钮"};
char *lst_ctype[]={"RunExe(执行程序)","打开画面","WM_COMMAND(命令)","自助控件COMMAND","打开WEB页面","打开google earth"};
char *lst_edt2[]={"WEB浏览器"};
char *lst_flsty[]={"一般单线","只显有功","只显无功","同时显示"};
char *lst_lfsty[]={"圆形","方形","线条"};
char *lst_spl[]={"无边框","简易边框","一般凹框","立体凹框","双边立体框"};
char *lst_spl1[]={"自然位置","1/2处","1/3处","1/4处","2/3处","3/4处","底端","顶端"};
char *lst_es[]={"显示","不显示"};
char *lst_shn[]={"不显数字","数字上边","数字下边"};
char *lst_shn1[]={"不显数字","数字左边","数字右边"};
char *lst_me[]={"指针1","指针2","指针3","指针4","指针5"};
char *lst_snm[]={"不显","外侧","内侧"};
char *lst_wdt[]={"正常显示","单线加强","1倍宽度","2倍宽度","3倍宽度"};

char *lst_zone1[]={"区域发电","区域负荷","断面潮流"};

char *lst_vl[]={"1100kV","750kV","500kV","330kV","220kV","110kV",
			  "66kV","38kV","35kV","22kV","20kV","18kV","15kV","14kV",
			  "10kV","6kV","3kV","1kV","0.38kV","0.22kV"};
const unsigned char LST_VL_COUNT=sizeof(lst_vl)/sizeof(char*);

char *lst_sft[]={"编辑位置","其它-暂未用"};
char *lst_fsh[]={"一次","循环"};

char *lst_dtype[]={"未知","电力设备","厂站","区域","模拟量"};
char *lst_subtype[]={"PT","发电机","开关,刀闸","负荷","电容","电抗","接地","二绕组变压器",
					"三绕组变压器","静态无功补偿器","逆变、变流器","母线","线路"};

char *lst_anldev[]={"发电机","交流线路","直流线路","母线(节点)","负荷","2绕组变压器","3绕组变压器","电容器","电抗器","静态无功","区域","电网数据","特高压","预定义断面","设备量测","非设备量测"};
char *lst_yh[]={"优化前","优化后"};
char *lst_mode[]={"自动","同步"};
char *lst_ppie[]={"交流输电线","直流输电线","发电机"};
char *lst_phi[]={"正常","电压等高线","线路等高线","发电机备用","无功及备用","变压器备用","低频振荡","断面潮流","灵敏度计算","历史数据库回放","N-1故障分析",
				 "开关SOE动作回放","短路电流监视","短路电流计算"};

char *msg_dbx[]={"ID", "是否填充?","边线宽度","线颜色","填充颜色","边线线型","背景","自动封闭"};
char *msg_rect[]={"ID","是否填充?","式样","线颜色","填充颜色"};

char *msg_egrp[]={"ID","类型","线颜色","线宽度","阴影"};
char *msg_sgrp[]={"ID","类型","填充方式0-7","填充第一颜色","填充第二颜色","阴影"};
char *msg_hsin[]={"ID","周期数","线宽度","线颜色","水平或垂直"};
char *msg_sin[]={"ID","周期数","线颜色","水平或垂直","开始角度"};
char *msg_glass[]={"ID","深度","颜色","画边线","边线色"};
char *msg_arrow[]={"ID","线宽度","线颜色"};
char *msg_text[]={"ID","字体","颜色","自动充满","文本"};
char *msg_img[]={"ID","阴影","放缩?","透明度"};
char *msg_anl[]={"设备名","设备ID","设备类型","字体修饰","字体","告警颜色",
				 "正常颜色","小数位","显示方向"};

char *msg_elegrp[]={"关联设备名","设备编号","类型","名称","运行时显示","端子1电压等级","端子2电压等级","端子3电压等级"};
char *msg_grpgen[]={"关联设备名","设备编号","类型","名称","运行时显示","端子1电压等级","是否显示备用"};


char *msg_date[]={"ID","日期格式","边框","边线色","字符颜色","背景色","字体显示","字体","背景透明"};
char *msg_time[]={"ID","时间格式","边框","边线色","字符颜色","背景色","字体显示","字体","背景透明"};
char *msg_gml[]={"GIF文件名","设备名","设备ID","设备类型"};
char *msg_src[]={"方向","文本样式","用玻璃层","有外框","深度","边框","玻璃颜色",
				"文本颜色","文字字体","排列方式","阴影","id"};
char *msg_oph[]={"按钮ID","按钮式样","按钮标题","阴影","命令类型","wParam","命令串","本色","变色","关联ID","字体","自动边线","标题显示","画面状态"};
char *msg_ctl[]={"控制类型","ID值","左对齐","右对齐","上对齐","下对齐","显示模式 "};
char *msg_flw[]={"关联设备名","设备ID","电压等级","方向","输电类型","线宽"};
char *msg_est[]={"缺省颜色","焊接"};
char *msg_bar[]={"方向","设备名","设备ID","最大值","最小值","外框","正常颜色","告警颜色","告警值","样式"};
char *msg_spl[]={"VH类型","边框","左对齐","右对齐","上对齐","下对齐","初始分割位置","保留高度"};
char *msg_mb[]={"是否显示","显示颜色"};
char *msg_arc[]={"颜色","宽度","开始角度","结束角度","线条自动放大"};
char *msg_cln[]={"图形ID","线宽度","电压等级","焊接点1显示","焊接点2显示"};
char *msg_bus[]={"设备名","设备ID","样式","阴影","电压等级","电压取值"};
char *msg_path[]={"路经ID","起点坐标","终点坐标","编辑时显示颜色"};
char *msg_act[]={"设备名","设备ID","图形ID","所属路经ID","运行模式","自动运行延时","自动步长"};	
char *msg_rstype[]={"原码","转换值"};
char *msg_coor[]={"X方向最小值","X方向最大值","Y方向最小值","Y方向最大值","坐标线颜色",
			"水线颜色","文本颜色","X坐标点数","Y坐标点数","X方向水线是否画","y方向水线是否画",
			"x坐标值显示","y坐标值显示","坐标线宽","水线线宽","X字符显示字体","Y字符显示字体"};
char *msg_tbl[]={"线颜色","线宽度","边线加粗","行数"};

char *msg_sys[]={"填充颜色1","填充颜色2","画线颜色","画线宽度","文本颜色","是否填充","填充模式",
				"多边形封闭","设备电压等级","正常颜色","告警颜色","是否联动"};
char *msg_fsh[]={"swf文件名","播放模式","左对齐","上对齐","右对齐","下对齐"};
char *msg_ppie[]={"设备名","设备ID","类型","字体","字体颜色","饼图颜色","空白颜色"};

char *msg_mtr1[]={"最小值","最大值","显示弧线","显示数字","数字字体","小数位","刻度数","刻度线长度","小刻度数","仪表倾角","指针式样",
				"指针颜色","指针轴大小","指针箭头","刻度颜色","告警刻度数","Val11","Val12","Val21","Val22","颜色1","颜色2","大刻度类型"};
char *msg_mtr2[]={"最小值","最大值","刻度数","小刻度数","显示底线","显示数字","小数点","指针颜色",
				"刻度颜色", "告警刻度数","Val11","Val12","Val21","Val22","颜色1","颜色2"};
	
char *msg_mtr3[]={"最小值","最大值","刻度数","小刻度数","显示底线","显示数字","小数点","指针颜色",
				"刻度颜色", "告警刻度数","Val11","Val12","Val21","Val22","颜色1","颜色2"};
char *msg_mtr4[]={"总位数","小数位数","边框颜色","整数颜色","小数颜色"};
char *msg_resv[]={"水库名","水库ID","边线颜色","正常时颜色","高水位颜色","低水位颜色"};
char *msg_zone[]={"区域名","区域ID","边线颜色","字体","字体颜色"};
char *msg_zone1[]={"名称","ID","类型","字体颜色","颜色1","颜色2","字体"};
char *msg_mttext[]={"ID","名字","类型","字体","字体颜色","文本行"};


char *lst_kd[]={"线条","园形"};
char *msg_spie[]={"类型","字符色","字体","边线色","饼1色","饼2色","饼3色","饼4色"};
char *lst_spie[]={"全系统发电","全系统负荷"};

////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

editobj::editobj()
{

}
 
editobj::~editobj()
{

}
//编辑选择的对象
void editobj::EditSelObject()
{
	CRect rt;
	if(!SetEditParam()) return;
	Invalidate();
}
//编辑一个对象
bool editobj::SetEditParam()
{
	int j;
	BASE0 *bs;
	j=dbm.GetFirstSelObj();	//返回选择的对象
	bs=&dbm.clayer->obj[j];
	ReSet();
	switch(bs->attr.type){
	case 1:EditDbx(bs);		break;
	case 2:EditRect(bs);	break;
	case 3:EditCircle(bs);	break;
	case 4:EditHSin(bs);	break;
	case 5:EditSin(bs);		break;
	case 6:EditArc(bs);		break;
	case 7:EditArrow(bs);	break;
	case 8:EditGlass(bs);	break;
	case 10:EditText(bs);	break;
	case 11:EditEsit(bs);	break;
	case 12:EditMb(bs);		break;
	case 13:EditCoordinate(bs);break;
	case 14:EditTable(bs);	break;
	case 15:EditImg(bs);	break;
	case 16:EditPath(bs);	break;
	case 17:EditSpic(bs);	break;
	case 32:EditMeter1(bs); break;
	case 33:EditMeter2(bs); break;
	case 34:EditMeter3(bs); break;
	case 35:EditMeter4(bs); break;
	case 64:EditAnl(bs);	break;
	case 65:EditReservoir(bs);break;
	case 66:EditElegrp(bs);	break;
	case 68:EditSysPie(bs); break;
	case 69:EditBar(bs);	break;
	case 70:EditPie(bs);	break;
	case 71:EditDate(bs);	break;
	case 72:EditTime(bs);	break;
	case 73:EditGml(bs);	break;
	case 74:EditScrText(bs);break;
	case 75:EditPush(bs);	break;
	case 76:EditSlfCtl(bs);	break;
	case 77:EditFLow(bs);	break;
	case 78:EditConLine(bs);break;
	case 79:EditBus(bs);	break;
	case 80:EditActObj(bs);	break;
	case 81:EditFlash(bs);	break;
	case 82:EditPPie(bs);	break;
	case 83:EditZone(bs);	break;
	case 84:Editmttext(bs);	break;
	default:
		return false;
	};
	return true;
}
//编辑多边形
void editobj::EditDbx(BASE0 *bs)
{
	int i;
	N_DBX *dbx;
	dbx=(N_DBX*)bs->buf;
	SetCaptionName("多边形属性修改");
	SetColLinNum(8);
	SetListSum(3);
	for(i=0;i<2;i++) ADDSubListItem(0,lst_yesno[i]);
	for(i=0;i<3;i++) ADDSubListItem(1,lst_ltype[i]); 
	for(i=0;i<2;i++) ADDSubListItem(2,lst_lmode[i]); 
	for(i=0;i<8;i++) SetLineName(msg_dbx[i],i%12,i,120);
  	AddEditItem(0,&bs->attr.ID,EDIT_DWORD,sizeof(DWORD),1);
	AddEditItem(1,&dbx->fill,EDIT_BYTE,sizeof(BYTE),1,0);
	AddEditItem(2,&dbx->width,EDIT_DOUBLE,sizeof(double),1);
	AddEditItem(3,&dbx->lcolor,EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(4,&dbx->bcolor1,EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(5,&dbx->ltype,EDIT_BYTE,sizeof(BYTE),1,1);
	AddEditItem(6,&dbx->bgmode,EDIT_BYTE,sizeof(BYTE),1,0);
	AddEditItem(7,&dbx->close,EDIT_BYTE,sizeof(BYTE),1,0);
	SetScrollBar();
}

void editobj::EditReservoir(BASE0 *bs)
{
	int i;
	N_RESERVOIR*lp=(N_RESERVOIR*)bs->buf;
	SetCaptionName("水库属性修改");
	SetColLinNum(6);
    for(i=0;i<6;i++) SetLineName(msg_resv[i],i%12,i,123); 
	AddEditItem(0,lp->dev_name,EDIT_STR,24,1);
	AddEditItem(1,&lp->did,EDIT_INT,sizeof(int),1);
	AddEditItem(2,&lp->color,EDIT_COLOR,4,1);
	AddEditItem(3,&lp->ncolor,EDIT_COLOR,4,1);
	AddEditItem(4,&lp->hcolor,EDIT_COLOR,4,1);
	AddEditItem(5,&lp->lcolor,EDIT_COLOR,4,1);
	SetScrollBar();
}

void editobj::EditZone(BASE0 *bs)
{
	int i;
	N_ZONE *lp=(N_ZONE*)bs->buf;
	SetCaptionName("区域属性修改");
	SetColLinNum(5);
    for(i=0;i<5;i++) SetLineName(msg_zone[i],i%12,i,123); 
	AddEditItem(0,lp->zone_name,EDIT_STR,24,1);
	AddEditItem(1,&lp->did,EDIT_INT,sizeof(int),1);
	AddEditItem(2,&lp->lcolor,EDIT_COLOR,4,1);
	AddEditItem(3,&lp->lf,EDIT_FONT,sizeof(LOGFONT),1);
	AddEditItem(4,&lp->fcolor,EDIT_COLOR,4,1);
	SetScrollBar();
}

void editobj::Editmttext(BASE0 *bs)
{
	int i;
	N_MTTEXT *lp=(N_MTTEXT*)bs->buf;
	SetCaptionName("动态文本属性修改");
	SetColLinNum(6);
    for(i=0;i<6;i++) SetLineName(msg_mttext[i],i%12,i,123); 
	AddEditItem(0,&lp->did,EDIT_INT,4,1);
	AddEditItem(1,lp->name,EDIT_STR,40,1);
	AddEditItem(2,&lp->type,EDIT_BYTE,1,1);
	AddEditItem(3,&lp->lf,EDIT_FONT,sizeof(LOGFONT),1);
	AddEditItem(4,&lp->fcolor,EDIT_COLOR,4,1);
	AddEditItem(5,lp->text,EDIT_STR,255,1);
	SetScrollBar();
}

void editobj::EditPie(BASE0 *bs)
{
	int i;
	//"名称",ID","类型","边线颜色","字体颜色","颜色1","颜色2"};
	N_PIE *lp=(N_PIE*)bs->buf;
	SetCaptionName("饼图属性");
	SetListSum(1);
	SetColLinNum(7);
	for(i=0;i<3;i++) ADDSubListItem(0,lst_zone1[i]); 
    for(i=0;i<7;i++) SetLineName(msg_zone1[i],i%12,i,123); 
	AddEditItem(0,lp->name,EDIT_STR,24,1);
	AddEditItem(1,&lp->did,EDIT_INT,sizeof(int),1);
	AddEditItem(2,&lp->type,EDIT_BYTE,1,1,0);
	AddEditItem(3,&lp->fcolor,EDIT_COLOR,4,1);
	AddEditItem(4,&lp->color[0],EDIT_COLOR,4,1);
	AddEditItem(5,&lp->color[1],EDIT_COLOR,4,1);
	AddEditItem(6,&lp->lf, EDIT_FONT,sizeof(LOGFONT),1);
	SetScrollBar();
}


void editobj::EditSysPie(BASE0 *bs)
{
	int i;
	N_SYSPIE *lp=(N_SYSPIE*)bs->buf;
	SetCaptionName("系统饼图属性");
	SetListSum(1);
	SetColLinNum(8);
	for(i=0;i<2;i++) ADDSubListItem(0,lst_spie[i]); 
    for(i=0;i<8;i++) SetLineName(msg_spie[i],i%12,i,100); 
	AddEditItem(0,&lp->type,EDIT_BYTE,1,1,0);
	AddEditItem(1,&lp->fcolor,EDIT_COLOR,4,1);
	AddEditItem(2,&lp->lf, EDIT_FONT,sizeof(LOGFONT),1);
	AddEditItem(3,&lp->color[0],EDIT_COLOR,4,1);
	AddEditItem(4,&lp->color[1],EDIT_COLOR,4,1);
	AddEditItem(5,&lp->color[2],EDIT_COLOR,4,1);
	AddEditItem(6,&lp->color[3],EDIT_COLOR,4,1);
	AddEditItem(7,&lp->color[4],EDIT_COLOR,4,1);
	SetScrollBar();
}

//编辑多边形
void editobj::EditRect(BASE0 *bs)
{
	int i;
	N_RECT *nrt;
	nrt=(N_RECT*)bs->buf;
	SetCaptionName("矩形属性修改");
	SetListSum(2);
	SetColLinNum(5);
	for(i=0;i<2;i++) ADDSubListItem(0,lst_yesno[i]); 
	for(i=0;i<3;i++) ADDSubListItem(1,lst_egrp[i]);
	for(i=0;i<5;i++) SetLineName(msg_rect[i],i%12,i,120);
  	AddEditItem(0,&bs->attr.ID,EDIT_DWORD,sizeof(DWORD),0);
	AddEditItem(1,&nrt->fill,EDIT_BYTE,sizeof(BYTE),1,0);
	AddEditItem(2,&nrt->type,EDIT_BYTE,sizeof(BYTE),1,1);
	AddEditItem(3,&nrt->lcolor,EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(4,&nrt->bcolor1,EDIT_COLOR,sizeof(DWORD),1);
	SetScrollBar();
}


void editobj::EditCircle(BASE0 *bs)
{
	int i;
	N_CIRCLE *ncr;
	ncr=(N_CIRCLE*)bs->buf;
	SetCaptionName("园属性修改");
	SetListSum(2);
	SetColLinNum(5);
	for(i=0;i<2;i++) ADDSubListItem(0,lst_yesno[i]); 
	for(i=0;i<3;i++) ADDSubListItem(1,lst_egrp[i]);
	for(i=0;i<5;i++) SetLineName(msg_rect[i],i%12,i,120); 
  	AddEditItem(0,&bs->attr.ID,EDIT_DWORD,sizeof(DWORD),0);
	AddEditItem(1,&ncr->fill,EDIT_BYTE,sizeof(BYTE),1,0);
	AddEditItem(2,&ncr->type,EDIT_BYTE,sizeof(BYTE),1,1);
	AddEditItem(3,&ncr->lcolor,EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(4,&ncr->bcolor1,EDIT_COLOR,sizeof(DWORD),1);
	SetScrollBar();
}


void editobj::EditHSin(BASE0 *bs)
{
	int i;
	N_HSIN *hsin;
	hsin=(N_HSIN*)bs->buf;
	SetCaptionName("半波图形属性修改");
	SetListSum(1);
	SetColLinNum(5);
    for(i=0;i<5;i++) SetLineName(msg_hsin[i],i%12,i,120); 
	for(i=0;i<2;i++) ADDSubListItem(0,lst_vh[i]);
	AddEditItem(0,&bs->attr.ID,EDIT_DWORD,sizeof(DWORD),0);
	AddEditItem(1,&hsin->pirodic,EDIT_BYTE,sizeof(BYTE),1);
	AddEditItem(2,&hsin->width,EDIT_DOUBLE,sizeof(double),1);
	AddEditItem(3,&hsin->color,EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(4,&hsin->ltype,EDIT_BYTE,sizeof(DWORD),1,0);
	SetScrollBar();
}

void editobj::EditSin(BASE0 *bs)
{
	int i;
	N_SIN *hsin;
	hsin=(N_SIN*)bs->buf;
	SetCaptionName("正弦波图形属性修改");
	SetListSum(1);
	SetColLinNum(5);
    for(i=0;i<5;i++) SetLineName(msg_sin[i],i%12,i,120); 
	for(i=0;i<2;i++) ADDSubListItem(0,lst_vh[i]);
	AddEditItem(0,&bs->attr.ID,EDIT_DWORD,sizeof(DWORD),0);
 	AddEditItem(1,&hsin->pirodic,EDIT_BYTE,sizeof(BYTE),1);
	AddEditItem(2,&hsin->color,EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(3,&hsin->ltype,EDIT_BYTE,sizeof(BYTE),1,0);
	AddEditItem(4,&hsin->startdeg,EDIT_WORD,sizeof(WORD),1);
	SetScrollBar();
}

void editobj::EditGlass(BASE0 *bs)
{
	int i;
	N_GLASS *glass;
	glass=(N_GLASS*)bs->buf;
	SetCaptionName("玻璃层属性修改");
	SetListSum(1);
	SetColLinNum(5);
    for(i=0;i<5;i++) SetLineName(msg_glass[i],i%12,i,80); 
	for(i=0;i<2;i++) ADDSubListItem(0,lst_yesno[i]);  
	AddEditItem(0,&bs->attr.ID,EDIT_DWORD,sizeof(DWORD),1);
  	AddEditItem(1,&glass->depth,EDIT_BYTE,sizeof(BYTE),1);
	AddEditItem(2,&glass->color,EDIT_COLOR,4,1);
	AddEditItem(3,&glass->outline,EDIT_BYTE,sizeof(BYTE),1,0);
	AddEditItem(4,&glass->ocolor,EDIT_COLOR,sizeof(DWORD),1);
	SetScrollBar();
}

void editobj::EditArrow(BASE0 *bs)
{
	int i;
	N_ARROW *arrow;
	arrow=(N_ARROW*)bs->buf;
	SetCaptionName("方向箭头属性修改");
	SetListSum(0);
	SetColLinNum(3);
    for(i=0;i<3;i++) SetLineName(msg_arrow[i],i%12,i,120); 
	AddEditItem(0,&bs->attr.ID,EDIT_DWORD,sizeof(DWORD),1);
  	AddEditItem(1,&arrow->width,EDIT_DOUBLE,sizeof(BYTE),1);
	AddEditItem(2,&arrow->color,EDIT_COLOR,4,1);
	SetScrollBar();
}


void editobj::EditText(BASE0 *bs)
{
	int i;
	N_TEXT *text;
	text=(N_TEXT*)bs->buf;
	SetCaptionName("文本字符串属性修改");
	SetListSum(2);
	SetColLinNum(5);
    for(i=0;i<5;i++) SetLineName(msg_text[i],i%12,i,100); 
	for(i=0;i<3;i++) ADDSubListItem(0,lst_tstyle[i]);  
	for(i=0;i<2;i++) ADDSubListItem(1,lst_yesno[i]); 
	AddEditItem(0,&bs->attr.ID, EDIT_WORD,sizeof(WORD),1);
	AddEditItem(1,&text->font, EDIT_FONT,sizeof(LOGFONT),1);
	AddEditItem(2,&text->color,EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(3,&text->autofill,EDIT_BYTE,sizeof(BYTE),1,1);
	AddEditItem(4,&text->text,EDIT_STR,44,1);
	SetScrollBar();
}

void editobj::EditImg(BASE0 *bs)
{
	int i;
	N_IMG *img;
	img=(N_IMG*)bs->buf;
	SetCaptionName("位图属性修改");
	SetListSum(1);
	SetColLinNum(4);
    for(i=0;i<4;i++) SetLineName(msg_img[i],i%12,i,80); 
	for(i=0;i<2;i++) ADDSubListItem(0,lst_yesno[i]);  
	AddEditItem(0,&bs->attr.ID,EDIT_WORD,sizeof(WORD),1);
	AddEditItem(1,&img->shadow,EDIT_BYTE,sizeof(BYTE),1,0);
	AddEditItem(2,&img->zoom,  EDIT_BYTE,sizeof(BYTE),1,0);
	AddEditItem(3,&img->depth, EDIT_BYTE,sizeof(BYTE),1);
	SetScrollBar();
}

void editobj::EditAnl(BASE0 *bs)
{
	int i;
	N_ANL *anl;
	anl=(N_ANL*)bs->buf;
	SetCaptionName("设备模拟量属性修改");
	SetListSum(4);
	SetColLinNum(9);
    for(i=0;i<9;i++)  SetLineName(msg_anl[i],i%12,i,102); 
	for(i=0;i<3;i++)  ADDSubListItem(0,lst_tstyle[i]); 
	for(i=0;i<16;i++)  ADDSubListItem(1,lst_anldev[i]);
	for(i=0;i<2;i++)  ADDSubListItem(2,lst_vh[i]);
	for(i=0;i<2;i++)  ADDSubListItem(3,lst_yh[i]);
	AddEditItem(0,anl->dev_name,EDIT_STR,24,1);
	AddEditItem(1,&anl->did,   EDIT_INT, sizeof(int),1);
	AddEditItem(2,&anl->dtype, EDIT_BYTE, sizeof(BYTE),0,1);
	AddEditItem(3,&anl->style, EDIT_BYTE, sizeof(BYTE),1,0);
	AddEditItem(4,&anl->lf,    EDIT_FONT, sizeof(LOGFONT),1);
	AddEditItem(5,&anl->acolor,EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(6,&anl->ncolor,EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(7,&anl->xs,   EDIT_BYTE, sizeof(BYTE),1);
	AddEditItem(8,&anl->direction,EDIT_BYTE, sizeof(BYTE),1,2);
	SetScrollBar();
}


void editobj::EditElegrp(BASE0 *bs)
{
	int i,n;
	N_ELEGRPA *elegrp;
	elegrp=(N_ELEGRPA*)bs->buf;
	SetCaptionName("组合图元属性修改");
	SetListSum(5);
	for(i=0;i<4;i++)  ADDSubListItem(0,lst_dtype[i]);
	for(i=0;i<LST_VL_COUNT;i++) ADDSubListItem(1,lst_vl[i]);
	for(i=0;i<11;i++) ADDSubListItem(2,lst_subtype[i]);
	for(i=0;i<2;i++)  ADDSubListItem(3,lst_yesno[i]);
	for(i=0;i<2;i++)  ADDSubListItem(4,lst_es[i]);
	if(elegrp->type==1&&(elegrp->subtype==7||elegrp->subtype==8)) n=5+elegrp->sitesum;
	else n=6;
	
	if(elegrp->type==1&&elegrp->subtype==1){
		SetColLinNum(7);
		for(i=0;i<7;i++)  SetLineName(msg_grpgen[i],i%12,i,130); 
	}else{
		SetColLinNum(n);
		for(i=0;i<n;i++)  SetLineName(msg_elegrp[i],i%12,i,130); 
	}
    AddEditItem(0,elegrp->dev_name,EDIT_STR,23,1);
	AddEditItem(1,&elegrp->did,EDIT_INT,sizeof(int),1);
  	AddEditItem(2,&elegrp->type,EDIT_BYTE,sizeof(BYTE),0,0);
	AddEditItem(3,&elegrp->subtype,EDIT_BYTE,sizeof(BYTE),0,2);
	AddEditItem(4,&elegrp->runshow,EDIT_BYTE,sizeof(BYTE),1,4);
	AddEditItem(5,&elegrp->site[0].vl,EDIT_BYTE,sizeof(BYTE),1,1);
	AddEditItem(6,&elegrp->site[1].vl,EDIT_BYTE,sizeof(BYTE),1,1);
	AddEditItem(7,&elegrp->site[2].vl,EDIT_BYTE,sizeof(BYTE),1,1);
	if(elegrp->type==1&&elegrp->subtype==1){
		AddEditItem(6,&elegrp->genrev,EDIT_BYTE,sizeof(BYTE),1,3);
	}
	SetScrollBar();
}





void editobj::EditDate(BASE0 *bs)
{
	int i;
	N_DATE *date;
	date=(N_DATE*)bs->buf;
	SetCaptionName("日期属性修改");
	SetListSum(4);
	SetColLinNum(9);
    for(i=0;i<9;i++) SetLineName(msg_date[i],i%12,i,100); 
	for(i=0;i<3;i++)  ADDSubListItem(0,lst_tstyle[i]);
	for(i=0;i<4;i++)  ADDSubListItem(1,lst_lstyle[i]);
	for(i=0;i<4;i++)  ADDSubListItem(2,lst_date[i]);
	for(i=0;i<2;i++)  ADDSubListItem(3,lst_yesno[i]);
	AddEditItem(0,&bs->attr.ID,EDIT_WORD,sizeof(WORD),1);
  	AddEditItem(1,&date->fmt,EDIT_BYTE,sizeof(BYTE),1,2);
	AddEditItem(2,&date->outline,EDIT_BYTE,sizeof(BYTE),1,1);
	AddEditItem(3,&date->outcolor, EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(4,&date->fcolor, EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(5,&date->bcolor, EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(6,&date->style, EDIT_BYTE,sizeof(BYTE),1,0);
	AddEditItem(7,&date->font, EDIT_FONT,sizeof(LOGFONT),1);
	AddEditItem(8,&date->tran, EDIT_BYTE,sizeof(BYTE),1,3);
	SetScrollBar();
}

void editobj::EditTime(BASE0 *bs)
{
	int i;
	N_TIME *tim;
	tim=(N_TIME*)bs->buf;
	SetCaptionName("时间属性修改");
	SetListSum(4);
	SetColLinNum(9);
    for(i=0;i<9;i++) SetLineName(msg_time[i],i%12,i,100); 
	for(i=0;i<3;i++)  ADDSubListItem(0,lst_tstyle[i]);
	for(i=0;i<4;i++)  ADDSubListItem(1,lst_lstyle[i]);
	for(i=0;i<5;i++)  ADDSubListItem(2,lst_time[i]);
	for(i=0;i<2;i++)  ADDSubListItem(3,lst_yesno[i]);
	AddEditItem(0,&bs->attr.ID,EDIT_WORD,sizeof(WORD),1);
  	AddEditItem(1,&tim->fmt,EDIT_BYTE,sizeof(BYTE),1,2);
	AddEditItem(2,&tim->outline,EDIT_BYTE,sizeof(BYTE),1,1);
	AddEditItem(3,&tim->outcolor, EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(4,&tim->fcolor, EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(5,&tim->bcolor, EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(6,&tim->style, EDIT_BYTE,sizeof(BYTE),1,0);
	AddEditItem(7,&tim->font, EDIT_FONT,sizeof(LOGFONT),1);
	AddEditItem(8,&tim->tran, EDIT_BYTE,sizeof(BYTE),1,3);
	SetScrollBar();
}
//动画文件
void editobj::EditGml(BASE0 *bs)
{
	int i;
	N_GIFAML *gml;
	gml=(N_GIFAML*)bs->buf;
	SetCaptionName("Gif动画属性修改");
	SetListSum(1);
	SetColLinNum(4);
	for(i=0;i<7;i++) ADDSubListItem(0,lst_anldev[i]);
	for(i=0;i<4;i++) SetLineName(msg_gml[i],i,i,94); 
	AddEditItem(0,&gml->fname,EDIT_GIF,63,1);
	AddEditItem(1,gml->dsrc.name,EDIT_STR,24,1);
	AddEditItem(2,&gml->dsrc.did,EDIT_INT,sizeof(int),1);
	AddEditItem(3,&gml->dsrc.dtype,EDIT_BYTE,sizeof(BYTE),0,0);
	SetScrollBar();
}

void editobj::EditScrText(BASE0 *bs)
{
	int i;
	N_SRLTEXT *scr;
	scr=(N_SRLTEXT*)bs->buf;
	SetCaptionName("滚动文本属性修改");
	SetListSum(5);
	SetColLinNum(12);
    for(i=0;i<12;i++) SetLineName(msg_src[i],i%12,i,100); 
	for(i=0;i<2;i++)  ADDSubListItem(0,lst_yesno[i]);
	for(i=0;i<5;i++)  ADDSubListItem(1,lst_tsty[i]);
	for(i=0;i<3;i++)  ADDSubListItem(2,lst_tstyle[i]);
	for(i=0;i<4;i++)  ADDSubListItem(3,lst_alg[i]);
	for(i=0;i<2;i++)  ADDSubListItem(4,lst_shw[i]);

  	AddEditItem(0,&scr->direct,EDIT_BYTE,sizeof(BYTE),1,1);
	AddEditItem(1,&scr->tstyle,EDIT_BYTE,sizeof(BYTE),1,2);
	AddEditItem(2,&scr->glass, EDIT_BYTE,sizeof(BYTE),1,0);
	AddEditItem(3,&scr->outline, EDIT_BYTE,sizeof(BYTE),1,0);
	AddEditItem(4,&scr->depth, EDIT_BYTE,sizeof(BYTE),1);
	AddEditItem(5,&scr->fcolor, EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(6,&scr->gcolor, EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(7,&scr->tcolor, EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(8,&scr->lf, EDIT_FONT,sizeof(LOGFONT),1);
	AddEditItem(9,&scr->align, EDIT_BYTE,sizeof(BYTE),1,3);
	AddEditItem(10,&scr->shadow,EDIT_BYTE,sizeof(BYTE),1,4);
	AddEditItem(11,&scr->id, EDIT_BYTE,sizeof(BYTE),1);
	SetScrollBar();
}

void editobj::EditPush(BASE0 *bs)
{
	int i;
	N_PUSH*lp=(N_PUSH*)bs->buf;
	SetCaptionName("按钮属性修改");
	SetListSum(6);
	SetColLinNum(14);

    for(i=0;i<5;i++) ADDSubListItem(0,lst_ptype[i]);
	for(i=0;i<6;i++) ADDSubListItem(1,lst_ctype[i]);
	for(i=0;i<2;i++) ADDSubListItem(2,lst_shw[i]);
	for(i=0;i<2;i++) ADDSubListItem(3,lst_yesno[i]);
	for(i=0;i<3;i++) ADDSubListItem(4,lst_tstyle[i]);
	for(i=0;i<14;i++) ADDSubListItem(5,lst_phi[i]);
	for(i=0;i<14;i++) SetLineName(msg_oph[i],i%12,i,100);
	if(lp->style>4) lp->style=4;
	AddEditItem(0,&lp->id,EDIT_WORD,sizeof(WORD),1);
	AddEditItem(1,&lp->style,EDIT_BYTE,sizeof(BYTE),1,0);
	AddEditItem(2,lp->title,EDIT_STR,32,1);
	AddEditItem(3,&lp->shadow,EDIT_BYTE,sizeof(BYTE),1,2);
	AddEditItem(4,&lp->cmdtype,EDIT_BYTE,sizeof(BYTE),1,1);
	AddEditItem(5,&lp->cmdnum,EDIT_WORD,sizeof(WORD),1);
	AddEditItem(6,lp->command,EDIT_STR,44,1);
	AddEditItem(7,&lp->color1,EDIT_COLOR,4,1);
	AddEditItem(8,&lp->color2,EDIT_COLOR,4,1);
	AddEditItem(9,&lp->selfid,EDIT_INT,4,1);
	AddEditItem(10,&lp->lf,EDIT_FONT,sizeof(LOGFONT),1);
	AddEditItem(11,&lp->autlin,EDIT_BYTE,sizeof(BYTE),1,3);
	AddEditItem(12,&lp->fstyle,EDIT_BYTE,sizeof(BYTE),1,4);
	AddEditItem(13,&lp->tosta,EDIT_BYTE,sizeof(BYTE),1,5);
	SetScrollBar();
}

void editobj::EditSlfCtl(BASE0 *bs)
{
	int i;
	N_SELFCTL*lp=(N_SELFCTL*)bs->buf;
	SetCaptionName("自助控件属性修改");
	SetListSum(2);
	SetColLinNum(7);
    for(i=0;i<2;i++) ADDSubListItem(0,lst_yesno[i]);   
	for(i=0;i<2;i++) ADDSubListItem(1,lst_sft[i]);  
    for(i=1;i<7;i++) SetLineName(msg_ctl[i],i%12,i,100); 
	SetLineName("DLL文件",0,0,100); 
	AddEditItem(0,&lp->dllname,EDIT_DLL,63,1);
	AddEditItem(1,&lp->id,EDIT_INT,sizeof(int),1);
	AddEditItem(2,&lp->aleft,EDIT_BYTE,sizeof(BYTE),1,0);
	AddEditItem(3,&lp->aright,EDIT_BYTE,sizeof(BYTE),1,0);
	AddEditItem(4,&lp->atop,EDIT_BYTE,sizeof(BYTE),1,0);
	AddEditItem(5,&lp->abottom,EDIT_BYTE,sizeof(BYTE),1,0);
	AddEditItem(6,&lp->mode,EDIT_BYTE,sizeof(BYTE),1,1);
	SetScrollBar();
}

void editobj::EditSpic(BASE0 *bs)
{
	int i;
	N_SPIC *sc;
	sc=(N_SPIC*)bs->buf;
	SetCaptionName("小图标属性修改");
	SetListSum(1);
	SetColLinNum(2);
    SetLineName("ID号",1,0,80); 
	SetLineName("阴影",2,1,80); 
	for(i=0;i<2;i++) ADDSubListItem(0,lst_yesno[i]);  
	AddEditItem(0,&sc->picID,EDIT_WORD,sizeof(WORD),0);
	AddEditItem(1,&sc->zoom,EDIT_BYTE,sizeof(BYTE),1,0);
	SetScrollBar();
}


void editobj::EditFLow(BASE0 *bs)
{
	int i;
	N_FLOW*lp=(N_FLOW*)bs->buf;
	SetCaptionName("线路(潮流)属性修改");
	SetListSum(4);
	SetColLinNum(6);
    for(i=0;i<LST_VL_COUNT;i++) ADDSubListItem(0,lst_vl[i]);
	for(i=0;i<2;i++) ADDSubListItem(1,lst_fw[i]);
	for(i=0;i<2;i++) ADDSubListItem(2,lst_fw1[i]);
	for(i=0;i<5;i++) ADDSubListItem(3,lst_wdt[i]);
	for(i=0;i<6;i++) SetLineName(msg_flw[i],i%12,i,123); 
	AddEditItem(0,lp->dev_name,EDIT_STR,15,1);
	AddEditItem(1,&lp->did,EDIT_INT,sizeof(int),1);
	AddEditItem(2,&lp->vl,EDIT_BYTE,sizeof(BYTE),1,0);
	AddEditItem(3,&lp->direct,EDIT_BYTE,sizeof(BYTE),1,1);
	AddEditItem(4,&lp->type,EDIT_BYTE,sizeof(BYTE),1,2);
	AddEditItem(5,&lp->linewidth,EDIT_BYTE,sizeof(BYTE),1,3);
	SetScrollBar();
}
void editobj::EditConLine(BASE0 *bs)
{
	int i;
	N_CONLINE*lp=(N_CONLINE*)bs->buf;
	SetCaptionName("连接线属性修改");
	SetListSum(2);
	SetColLinNum(5);
    for(i=0;i<2;i++) ADDSubListItem(0,lst_yesno[i]);
	for(i=0;i<LST_VL_COUNT;i++) ADDSubListItem(1,lst_vl[i]);
	for(i=0;i<5;i++) SetLineName(msg_cln[i],i%12,i,120); 
	AddEditItem(0,&bs->attr.ID,EDIT_WORD,2,1);
	AddEditItem(1,&lp->width,EDIT_DOUBLE,sizeof(double),1);
	AddEditItem(2,&lp->vl,EDIT_BYTE,1,1,1);
	AddEditItem(3,&lp->solder1,EDIT_BYTE,sizeof(BYTE),1,0);
	AddEditItem(4,&lp->solder2,EDIT_BYTE,sizeof(BYTE),1,0);
	SetScrollBar();
}
void editobj::EditEsit(BASE0 *bs)
{
	int i;
	N_ESITE*lp=(N_ESITE*)bs->buf;
	SetCaptionName("电气端子属性修改");
	SetListSum(1);
	SetColLinNum(2);
    for(i=0;i<2;i++) ADDSubListItem(0,lst_yesno[i]);   
    for(i=0;i<2;i++) SetLineName(msg_est[i],i%12,i,120);
	AddEditItem(0,&lp->color,EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(1,&lp->solder,EDIT_BYTE,sizeof(BYTE),1,0);
	SetScrollBar();
}

void editobj::EditMb(BASE0 *bs)
{
	int i;
	N_EGPMB*lp=(N_EGPMB*)bs->buf;
	SetCaptionName("组合图元母板属性修改");
	SetListSum(1);
	SetColLinNum(2);
    for(i=0;i<2;i++) ADDSubListItem(0,lst_yesno[i]);   
    for(i=0;i<2;i++) SetLineName(msg_mb[i],i,i,120); 
	AddEditItem(0,&lp->mode,EDIT_BYTE,sizeof(BYTE),1,0);
	AddEditItem(1,&lp->color,EDIT_COLOR,sizeof(DWORD),1);
	SetScrollBar();
}
void editobj::EditArc(BASE0 *bs)
{
	int i;
	N_ARC*lp=(N_ARC*)bs->buf;
	SetCaptionName("弧形属性修改");
	SetColLinNum(5);
	SetListSum(1);
	for(i=0;i<2;i++) ADDSubListItem(0,lst_yesno[i]);  
    for(i=0;i<5;i++) SetLineName(msg_arc[i],i,i,120); 
	AddEditItem(0,&lp->color,EDIT_COLOR,4,1);
	AddEditItem(1,&lp->width,EDIT_DOUBLE,1);
	AddEditItem(2,&lp->start,EDIT_SHORT,2,1);
	AddEditItem(3,&lp->end,EDIT_SHORT,2,1);
	AddEditItem(4,&lp->autozoom,EDIT_BYTE,sizeof(BYTE),1,0);
	SetScrollBar();
}

void editobj::EditPath(BASE0 *bs)
{
	int i;
	N_PATH*lp=(N_PATH*)bs->buf;
	SetCaptionName("路径属性修改");
	SetColLinNum(4);
    for(i=0;i<4;i++) SetLineName(msg_path[i],i,i,140);
	AddEditItem(0,&lp->ID,EDIT_WORD,sizeof(WORD),1);
	AddEditItem(1,&lp->start,EDIT_DOUBLE,sizeof(double),1);
	AddEditItem(2,&lp->end,EDIT_DOUBLE,sizeof(double),1);
	AddEditItem(3,&lp->color,EDIT_COLOR,4,1);
	SetScrollBar();
}



void editobj::EditBar(BASE0 *bs)
{
	int i;
	N_BAR*lp=(N_BAR*)bs->buf;
	SetCaptionName("棒图属性修改");
	SetListSum(3);
	SetColLinNum(10);
    for(i=0;i<2;i++) ADDSubListItem(0,lst_yesno[i]);   
	for(i=0;i<2;i++) ADDSubListItem(1,lst_vh[i]);
	for(i=0;i<3;i++) ADDSubListItem(2,lst_bar[i]);
    for(i=0;i<10;i++) SetLineName(msg_bar[i],i%12,i,120); 
	AddEditItem(0,&lp->xy,EDIT_BYTE,sizeof(BYTE),1,1);
	AddEditItem(1,lp->dsrc.name,EDIT_STR,24,0);
	AddEditItem(2,&lp->dsrc.did,EDIT_INT,sizeof(int),0);
	AddEditItem(3,&lp->max, EDIT_FLOAT,sizeof(float),1);
	AddEditItem(4,&lp->min, EDIT_FLOAT,sizeof(float),1);
	AddEditItem(5,&lp->outline,EDIT_BYTE,sizeof(BYTE),1,0);
	AddEditItem(6,&lp->ncolor,EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(7,&lp->acolor,EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(8,&lp->aval,EDIT_FLOAT,sizeof(float),1);
	AddEditItem(9,&lp->style,EDIT_BYTE,sizeof(BYTE),1,2);
	SetScrollBar();
}

void editobj::EditBus(BASE0 *bs)
{
	int i;
	N_BUS*lp=(N_BUS*)bs->buf;
	SetCaptionName("母线属性修改");
	SetListSum(3);
	SetColLinNum(5);
    for(i=0;i<LST_VL_COUNT;i++) ADDSubListItem(0,lst_vl[i]);   
	for(i=0;i<4;i++)  ADDSubListItem(1,lst_btype[i]);
	for(i=0;i<2;i++)  ADDSubListItem(2,lst_yh[i]);
    for(i=0;i<5;i++)  SetLineName(msg_bus[i],i%12,i,90); 
	AddEditItem(0,lp->dev_name,EDIT_STR,23,1);
	AddEditItem(1,&lp->did,EDIT_INT,sizeof(int),1);
	AddEditItem(2,&lp->type,EDIT_BYTE,sizeof(BYTE),1,1);
	AddEditItem(3,&lp->shadow,EDIT_BYTE,1,1);
	AddEditItem(4,&lp->vl,EDIT_BYTE,sizeof(BYTE),1,0);
	AddEditItem(5,&lp->yh,EDIT_BYTE,sizeof(BYTE),1,2);
	SetScrollBar();
}


void editobj::EditFlash(BASE0 *bs)
{
	int i;
	N_FLASH*lp=(N_FLASH*)bs->buf;
	SetCaptionName("Flash对象");
	SetListSum(2);
	SetColLinNum(6);
    for(i=0;i<2;i++) ADDSubListItem(0,lst_fsh[i]); 
	for(i=0;i<2;i++) ADDSubListItem(1,lst_yesno[i]);  
	for(i=0;i<6;i++) SetLineName(msg_fsh[i],i%12,i,110); 
	AddEditItem(0,lp->fname,EDIT_SWF,127,1);
	AddEditItem(1,&lp->playmode,EDIT_BYTE,sizeof(BYTE),1,0);
	AddEditItem(2,&lp->align_left,EDIT_BYTE,sizeof(BYTE),1,1);
	AddEditItem(3,&lp->align_top,EDIT_BYTE,sizeof(BYTE),1,1);
	AddEditItem(4,&lp->align_right,EDIT_BYTE,sizeof(BYTE),1,1);
	AddEditItem(5,&lp->align_buttom,EDIT_BYTE,sizeof(BYTE),1,1);
	SetScrollBar();
}

void editobj::EditActObj(BASE0 *bs)
{
	int i;
	N_ACTOBJ*lp=(N_ACTOBJ*)bs->buf;
	SetCaptionName("活动对象属性修改");
	SetListSum(2);
	SetColLinNum(7);
    for(i=0;i<2;i++) ADDSubListItem(0,lst_mode[i]);
	for(i=0;i<2;i++) ADDSubListItem(1,lst_yesno[i]);  
    for(i=0;i<7;i++) SetLineName(msg_act[i],i%12,i,120); 
	AddEditItem(0,lp->dsrc.name,EDIT_STR,15,1);
	AddEditItem(1,&lp->dsrc.did,EDIT_INT,sizeof(int),1);
	AddEditItem(2,&lp->gid,EDIT_SHORT,sizeof(WORD),0);
	AddEditItem(3,&lp->pathid,EDIT_WORD,sizeof(WORD),1);
	AddEditItem(4,&lp->runmode,EDIT_BYTE,sizeof(BYTE),1,0);
	AddEditItem(5,&lp->speed,EDIT_BYTE,sizeof(BYTE),1);
	AddEditItem(6,&lp->skip,EDIT_FLOAT,sizeof(float),1);
	SetScrollBar();
}

void editobj::EditCoordinate(BASE0 *bs)
{
	int i;
	N_COORDINATE*lp=(N_COORDINATE*)bs->buf;
	SetCaptionName("坐标图元属性修改");
	SetListSum(1);
	SetColLinNum(17);
    for(i=0;i<2;i++) ADDSubListItem(0,lst_yesno[i]);   
	for(i=0;i<17;i++) SetLineName(msg_coor[i],i%12,i,160); 
	AddEditItem(0,&lp->xmin,   EDIT_INT,sizeof(DWORD),1);
	AddEditItem(1,&lp->xmax,   EDIT_INT,sizeof(DWORD),1);
	AddEditItem(2,&lp->ymin,   EDIT_INT,sizeof(DWORD),1);
	AddEditItem(3,&lp->ymax,   EDIT_INT,sizeof(DWORD),1);
	AddEditItem(4,&lp->colorc, EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(5,&lp->colorw, EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(6,&lp->colort, EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(7,&lp->xdot,   EDIT_BYTE,sizeof(BYTE),1);
	AddEditItem(8,&lp->ydot,   EDIT_BYTE,sizeof(BYTE),1);
	AddEditItem(9,&lp->wxdraw, EDIT_BYTE,sizeof(BYTE),1,0);
	AddEditItem(10,&lp->wydraw,EDIT_BYTE,sizeof(BYTE),1,0);
	AddEditItem(11,&lp->xvshow,EDIT_BYTE,sizeof(BYTE),1,0);
	AddEditItem(12,&lp->yvshow,EDIT_BYTE,sizeof(BYTE),1,0);
	AddEditItem(13,&lp->width1,EDIT_DOUBLE,sizeof(double),1);
	AddEditItem(14,&lp->width2,EDIT_DOUBLE,sizeof(double),1);
	AddEditItem(15,&lp->fontx, EDIT_FONT,sizeof(LOGFONT),1);
	AddEditItem(16,&lp->fonty, EDIT_FONT,sizeof(LOGFONT),1);
	SetScrollBar();
}

void editobj::EditTable(BASE0 *bs)
{
	int i;
	N_TABLE*lp=(N_TABLE*)bs->buf;
	SetCaptionName("表格属性修改");
	SetListSum(1);
	SetColLinNum(4);
    for(i=0;i<2;i++) ADDSubListItem(0,lst_yesno[i]);
	for(i=0;i<4;i++) SetLineName(msg_tbl[i],i%12,i,120); 
	AddEditItem(0,&lp->color,  EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(1,&lp->width,  EDIT_DOUBLE,sizeof(double),1);
	AddEditItem(2,&lp->dbline, EDIT_BYTE,sizeof(BYTE),1,0);
	AddEditItem(3,&lp->line,   EDIT_WORD,sizeof(WORD),1);
	SetScrollBar();
}

void editobj::EditSysParam()
{
	int i;
	CRect rt;
	CPoint pt;
	SetCaptionName("系统绘图属性");
	SetListSum(2);
	SetColLinNum(12);
    for(i=0;i<12;i++) SetLineName(msg_sys[i],i%12,i,130); 
	for(i=0;i<2;i++) ADDSubListItem(0,lst_yesno[i]); 
	for(i=0;i<LST_VL_COUNT;i++) ADDSubListItem(1,lst_vl[i]); 

	AddEditItem(0,&cobj.bcolor1,EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(1,&cobj.bcolor2,EDIT_COLOR,sizeof(DWORD),1);
  	AddEditItem(2,&cobj.outcolor,EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(3,&cobj.linewd,EDIT_BYTE,sizeof(BYTE),1);
	AddEditItem(4,&cobj.tcolor,EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(5,&cobj.fill,EDIT_BYTE,sizeof(BYTE),1,0);
	AddEditItem(6,&cobj.fillmode,EDIT_BYTE,sizeof(BYTE),1);
	AddEditItem(7,&cobj.close,EDIT_BYTE,sizeof(BYTE),1,0);
	AddEditItem(8,&cobj.vl,EDIT_BYTE,sizeof(BYTE),1,1);
	AddEditItem(9,&cobj.ncolor,EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(10,&cobj.acolor,EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(11,&cobj.mcline,EDIT_BYTE,sizeof(DWORD),1,0);
	SetScrollBar();
	Invalidate();
}
//清空编辑
void editobj::EmptyEdit()
{
	SetCaptionName("请选择对象编辑");
	SetListSum(0);
	SetColLinNum(0);
	ed.ShowWindow(SW_HIDE);
	li.ShowWindow(SW_HIDE);
	Invalidate();
}


void editobj::EditPPie(BASE0 *bs)
{
	int i;
	N_PCTPIE *lp=(N_PCTPIE*)bs->buf;
	SetCaptionName("百分饼图属性修改");
	SetListSum(2);
	SetColLinNum(7);
    for(i=0;i<3;i++) ADDSubListItem(0,lst_ppie[i]);
	for(i=0;i<2;i++) ADDSubListItem(1,lst_yesno[i]);  
    for(i=0;i<7;i++) SetLineName(msg_ppie[i],i%12,i,120); 
	AddEditItem(0,lp->dev_name,EDIT_STR,15,1);
	AddEditItem(1,&lp->did,EDIT_INT,sizeof(int),1);
	AddEditItem(2,&lp->type,EDIT_BYTE,sizeof(BYTE),0,0);
	AddEditItem(3,&lp->lf,EDIT_FONT,sizeof(LOGFONT),1);
	AddEditItem(4,&lp->fcolor,EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(5,&lp->color1,EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(6,&lp->color2,EDIT_COLOR,sizeof(DWORD),1);
	SetScrollBar();
}

void editobj::EditMeter1(BASE0 *bs)
{
	int i;
	N_METER1*lp=(N_METER1*)bs->buf;
	SetCaptionName("仪表1属性修改");
	SetListSum(4);
	SetColLinNum(23);
    for(i=0;i<3;i++) ADDSubListItem(0,lst_snm[i]);
	for(i=0;i<5;i++) ADDSubListItem(1,lst_me[i]);
	for(i=0;i<2;i++) ADDSubListItem(2,lst_yesno[i]);
	for(i=0;i<2;i++) ADDSubListItem(3,lst_kd[i]);

	for(i=0;i<23;i++) SetLineName(msg_mtr1[i],i%12,i,120);
	AddEditItem(0,&lp->Vmin,EDIT_FLOAT,sizeof(float),1);
	AddEditItem(1,&lp->Vmax,EDIT_FLOAT,sizeof(float),1);
	AddEditItem(2,&lp->showarc,EDIT_BYTE,sizeof(BYTE),1,2);
	AddEditItem(3,&lp->shownum,EDIT_BYTE,sizeof(BYTE),1,0);
	AddEditItem(4,&lp->font,EDIT_FONT,sizeof(LOGFONT),1);
	AddEditItem(5,&lp->numdot,EDIT_BYTE,sizeof(BYTE),1);
	AddEditItem(6,&lp->scale,EDIT_BYTE,sizeof(BYTE),1);
	AddEditItem(7,&lp->slen,EDIT_BYTE,sizeof(BYTE),1);
	AddEditItem(8,&lp->scales,EDIT_BYTE,sizeof(BYTE),1);
	AddEditItem(9,&lp->angle,EDIT_BYTE,sizeof(BYTE),1);
	AddEditItem(10,&lp->pstyle,EDIT_BYTE,sizeof(BYTE),1,1);
	AddEditItem(11,&lp->pcr,EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(12,&lp->axw,EDIT_BYTE,sizeof(BYTE),1);
	AddEditItem(13,&lp->pw,EDIT_BYTE,sizeof(BYTE),1);
	AddEditItem(14,&lp->scr,EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(15,&lp->alarm,EDIT_BYTE,sizeof(BYTE),1);
	AddEditItem(16,&lp->val[0],EDIT_FLOAT,sizeof(float),1);
	AddEditItem(17,&lp->val[1],EDIT_FLOAT,sizeof(float),1);
	AddEditItem(18,&lp->val[2],EDIT_FLOAT,sizeof(float),1);
	AddEditItem(19,&lp->val[3],EDIT_FLOAT,sizeof(float),1);
	AddEditItem(20,&lp->cr[0],EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(21,&lp->cr[1],EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(22,&lp->stype,EDIT_BYTE,sizeof(BYTE),1,3);
	SetScrollBar();
}


void editobj::EditMeter2(BASE0 *bs)
{
	int i;
	N_METER2*lp=(N_METER2*)bs->buf;
	SetCaptionName("仪表2属性修改");
	SetListSum(2);
	SetColLinNum(16);
    for(i=0;i<2;i++) ADDSubListItem(0,lst_yesno[i]);
	for(i=0;i<3;i++) ADDSubListItem(1,lst_shn[i]);
	for(i=0;i<16;i++) SetLineName(msg_mtr2[i],i%12,i,120);
	AddEditItem(0,&lp->Vmin,EDIT_FLOAT,sizeof(float),1);
	AddEditItem(1,&lp->Vmax,EDIT_FLOAT,sizeof(float),1);
	AddEditItem(2,&lp->scale,EDIT_BYTE,sizeof(BYTE),1);
	AddEditItem(3,&lp->scales,EDIT_BYTE,sizeof(BYTE),1);
	AddEditItem(4,&lp->showbl,EDIT_BYTE,sizeof(BYTE),1,0);
	AddEditItem(5,&lp->shownum,EDIT_BYTE,sizeof(BYTE),1,1);
	AddEditItem(6,&lp->numdot,EDIT_BYTE,sizeof(BYTE),1);
	AddEditItem(7,&lp->pcr,EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(8,&lp->scr,EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(9,&lp->alarm,EDIT_BYTE,sizeof(BYTE),1);
	AddEditItem(10,&lp->val[0],EDIT_FLOAT,sizeof(float),1);
	AddEditItem(11,&lp->val[1],EDIT_FLOAT,sizeof(float),1);
	AddEditItem(12,&lp->val[2],EDIT_FLOAT,sizeof(float),1);
	AddEditItem(13,&lp->val[3],EDIT_FLOAT,sizeof(float),1);
	AddEditItem(14,&lp->cr[0],EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(15,&lp->cr[1],EDIT_COLOR,sizeof(DWORD),1);
	SetScrollBar();
}

void editobj::EditMeter3(BASE0 *bs)
{
	int i;
	N_METER3*lp=(N_METER3*)bs->buf;
	SetCaptionName("仪表3属性修改");
	SetListSum(2);
	SetColLinNum(16);
    for(i=0;i<2;i++) ADDSubListItem(0,lst_yesno[i]);
	for(i=0;i<3;i++) ADDSubListItem(1,lst_shn1[i]);
	for(i=0;i<16;i++) SetLineName(msg_mtr3[i],i%12,i,120);
	AddEditItem(0,&lp->Vmin,EDIT_FLOAT,sizeof(float),1);
	AddEditItem(1,&lp->Vmax,EDIT_FLOAT,sizeof(float),1);
	AddEditItem(2,&lp->scale,EDIT_BYTE,sizeof(BYTE),1);
	AddEditItem(3,&lp->scales,EDIT_BYTE,sizeof(BYTE),1);
	AddEditItem(4,&lp->showbl,EDIT_BYTE,sizeof(BYTE),1,0);
	AddEditItem(5,&lp->shownum,EDIT_BYTE,sizeof(BYTE),1,1);
	AddEditItem(6,&lp->numdot,EDIT_BYTE,sizeof(BYTE),1);
	AddEditItem(7,&lp->pcr,EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(8,&lp->scr,EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(9,&lp->alarm,EDIT_BYTE,sizeof(BYTE),1);
	AddEditItem(10,&lp->val[0],EDIT_FLOAT,sizeof(float),1);
	AddEditItem(11,&lp->val[1],EDIT_FLOAT,sizeof(float),1);
	AddEditItem(12,&lp->val[2],EDIT_FLOAT,sizeof(float),1);
	AddEditItem(13,&lp->val[3],EDIT_FLOAT,sizeof(float),1);
	AddEditItem(14,&lp->cr[0],EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(15,&lp->cr[1],EDIT_COLOR,sizeof(DWORD),1);
	SetScrollBar();
}

void editobj::EditMeter4(BASE0 *bs)
{
	int i;
	N_METER4*lp=(N_METER4*)bs->buf;
	SetCaptionName("仪表4属性修改");
	SetListSum(0);
	SetColLinNum(5);
    for(i=0;i<5;i++) SetLineName(msg_mtr4[i],i%12,i,120);
	AddEditItem(0,&lp->num,EDIT_BYTE,sizeof(BYTE),1);
	AddEditItem(1,&lp->numdot,EDIT_BYTE,sizeof(BYTE),1);
	AddEditItem(2,&lp->bcr,EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(3,&lp->ncr[0],EDIT_COLOR,sizeof(DWORD),1);
	AddEditItem(4,&lp->ncr[1],EDIT_COLOR,sizeof(DWORD),1);
	SetScrollBar();
}