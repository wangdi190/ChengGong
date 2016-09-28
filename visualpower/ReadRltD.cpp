// ReadRltD.cpp: implementation of the ReadRltD class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VisualPower.h"
#include "ReadRltD.h"
#include "dbapi.h"
#include "math.h"
#include <algorithm>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
//数据库字符串
char *dbfstr[]={"visualpw","studypw"};
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ReadRltD::ReadRltD()
{
	curdb=0;
	Npt=0;	
	Ngen=0;
	Nswt=0;
	Nld=0;
	Nsht=0;;
	Nsrt=0;
	Ntfm1=0;	
	Ntfm2=0;
	Nsvc=0;
	Nbus=0;
	Nlin=0;
	Ndclin=0;
	Ncvt=0;
	Ngnd=0;
	Nzone=0;
	Nsta=0;
	Nvot=0;
	Nlint=0;
	Nallt=0;
	Nsys=0;
	Nsym=0;
	Nsen=0;
	Npdf=0;
	Nuequ=0;
	Nrel=0;
	//首次初始化
	InitRltDbf();
	GetRltTable1();

	tmdx=CTimeSpan(1,0,0,0);
	m_pDynDM=NULL;
	m_dyndm=0;

}

ReadRltD::~ReadRltD()
{
	if(m_pDynDM!=NULL)
		delete []m_pDynDM;
	m_pDynDM=NULL;
}
//初始化实时数据库
bool ReadRltD::InitRltDbf()
{
	dbok=LSI_InitNTDbi();
	if(!dbok)
	{
		MessageBox(0,"数据库平台未启动","错误",MB_OK|MB_ICONSTOP);	
		return false;
	}
	LSI_CheckUser("sa","");
	return true;
}

//设置当前数据库
void ReadRltD::SetCurDbf(int dbno)
{
	if(dbno<0||dbno>1)  return;
	curdb=dbno;
	GetRltTable1();
}
//读入仪表运行参数
bool ReadRltD::ReadYbData(YBDATA&data)
{	
	switch(data.dtype)
	{
	case 0:  //系统指标k
		return ReadSysGd(data);
	case 1:  //发电机
		return YbReadGen(data);
	case 2:  //2绕变
		return YbReadTfm1(data);
	case 3:  //3绕变
		return YbReadTfm2(data);
	case 4:  //交流线路
		return YbReadLine(data);
	case 5:  //直流线路
		return YbReadDCLine(data);
	case 6:  //负荷
		return YbReadLoad(data);
	case 7:
		return ReadMeter(data);
	}
	return false;
}


//读取仪表数据
bool ReadRltD::ReadMeter(YBDATA&data)
{
	DWORD aid;
	bool canread=false;
	int i,j,field;
	if(data.recno>=0&&data.recno<Nmtr){ //验证带来的号是否可用
		j=data.recno;
		if(mtr[j].ID==data.did) canread=true;
	}
	if(!canread){ //如不能直接读，再查找序号
		for(i=0;i<Nmtr;i++){
			if(mtr[i].ID==data.did)
			{
				j=i;
				canread=true;
				break;
			}
		}
	}
	if(canread){
		aid=mtr[j].AreaNo;
		field=mtr[j].FieldNo;
		if(aid>0&&field>0) data.curval=ReadAreaVal(aid,field);
		else data.curval=mtr[j].Value;
		data.vmax=mtr[j].Vmax;
		data.vmin=mtr[j].Vmin;
		data.vmax1=mtr[j].Vmax1;
		data.vmin1=mtr[j].Vmin1;
		data.vmax2=mtr[j].Vmax2;
		data.vmin2=mtr[j].Vmin2;
		data.recno=j;
	}
	return canread;
}

//读取分区指定域
float ReadRltD::ReadAreaVal(DWORD aid,int field)
{
	int i;
	for(i=0;i<Nare;i++)
	{
		if(are[i].NU!=aid) continue;
		switch(field)
		{
		case 1:		return are[i].Security;
		case 2:		return are[i].LDFactor;
		case 3:		return are[i].LDFactorT;
		case 4:		return are[i].LDFactorL;
		case 5:		return are[i].LDFactorG;
		case 6:		return are[i].LDFactorS;
		case 7:		return are[i].Energy;
		case 8:		return are[i].VolRate;	
		case 9:		return are[i].LDRate;	
		case 10:	return are[i].OverLoading;	
		case 11:	return are[i].OverLoadingT;
		case 12:	return are[i].OverLoadingL;
		default:
			return 0;
		}
	}
	return 0;
}


//读入一个设备运行参数
bool ReadRltD::ReadDevData(READDEV&data)
{
	PWSYSSUM ps;
	curtm=CTime::GetCurrentTime();
	//先将输出参数清零
	memset(data.value,0,sizeof(float)*16);
	data.ele=0;
	data.sta=0;
	data.rp=0;
	switch(data.dtype){
	case 0:  //发电机
		return ReadGenAnl(data);
	case 1:  //交流线路
		return ReadLineAnl(data);
	case 2:  //直流线
		return ReadDCLineAnl(data);
	case 3:  //母线
		return ReadBusAnl(data);
	case 4:  //负荷
		return ReadLoadAnl(data);
	case 5:  //2绕组变压器
		return ReadTRan1(data);
	case 6:  //3绕组变压器
		return ReadTRan2(data);
	case 7:  //电容器
		return ReadShuAnl(data);
	case 8:  //电抗器
		return ReadSreAnl(data);
	case 9:  //SVC
		return ReadSvcAnl(data);
	case 10: //读入区域数据
		return ReadZoneAnl(data);
	case 11: //读入系统数据
		if(ReadSystj(ps))
		{
			data.value[0]=ps.GenP;
			data.value[1]=ps.GenQ;
			data.value[2]=ps.GenMax;
			data.value[3]=ps.LoadMax;
			data.value[4]=ps.LoadP;
			data.value[5]=0;
			return true;
		};
		break;
	case 12:
		return ReadMTxtAnl(data);
	case 13:
		return ReadDmAnl(data);
	case 14:
		return ReadRelEquAnl(data);
	case 15:
		return ReadUnEquAnl(data);
	case 100:
		return ReadStation(data);
	}
	return false;
}

//读入一个设备的浏览信息
bool ReadRltD::ReadDevViewMsg(void *data,int dtype)
{
	GenData		*gd;
	LinData		*ld;
	DLinData	*dd;
	BusData		*bd;
	LoadData	*ldd;
	TrfData1	*td1;
	TrfData2	*td2;
	ShuData		*sd;
	SvcData		*svd;
	SrdData		*srd;
	switch(dtype){
	case 0:  //发电机
		gd=(GenData*)data;
		return ReadGenData(gd[0]);
	case 1:  //线路
		ld=(LinData	*)data;
		return ReadLineData(ld[0]);
	case 2:  //直流线
		dd=(DLinData*)data;
		return ReadDCData(dd[0]);
	case 3:  //母线
		bd=(BusData*)data;
		return ReadBusAnl(bd[0]);
	case 4:  //负荷
		ldd=(LoadData*)data;
		return ReadLoadData(ldd[0]);
	case 5:  //2绕组变压器
		td1=(TrfData1*)data;
		return ReadTranData1(td1[0]);
	case 6:  //3绕组变压器
		td2=(TrfData2*)data;
		return ReadTranData2(td2[0]);
		break;
	case 7:  //电容器
		sd=(ShuData*)data;
		return ReadShuData(sd[0]);
	case 8:  //电抗器
		srd=(SrdData*)data;
		return ReadSrdData(srd[0]);
	case 9:  //SVC
		svd=(SvcData*)data;
		return ReadSvcData(svd[0]);
	}
	return false;
}


//读入一个设备的状态
bool ReadRltD::ReadStaData(READDEV_STA&data)
{
	READDEV dev;
	curtm=CTime::GetCurrentTime();
	memset(&dev,0,sizeof(READDEV));
	dev.recno=data.recno;
	dev.did=data.did;
	data.tm=0;
	dev.rp=0;
	switch(data.subtype){
	case 0: //PT  
		if(!ReadPTSta(dev)) return false;
		break;
	case 1: //发电机
		if(!ReadGenAnl(dev)) return false;
		break;
	case 2:	//开关
		if(!ReadSwitchSta(dev,data.tm)) return false;
		break;
	case 3: //负荷
		if(!ReadLoadAnl(dev)) return false;
		break;
	case 4: //电容
		if(!ReadShuAnl(dev)) return false;
		break;
	case 5: //电抗
		if(!ReadSreAnl(dev)) return false;
		break;
	case 6: //接地
		if(!ReadGndSta(dev)) return false;
		break;
	case 7: //二绕组
		if(!ReadTRan1(dev)) return false;
		break;
	case 8: //三绕组
		if(!ReadTRan2(dev)) return false;
		break;
	case 9: //scv
		if(!ReadSvcAnl(dev)) return false;
		break;
	case 10://逆变器
		if(!ReadCVTSta(dev)) return false;
		break;
	case 11: //保护信号
		if(!ReadRelaySta(dev)) return false;
		break;
	case 12:
		if(!ReadStusSta(dev)) return false;
		break;
	case 33:		//母线
		if(!ReadBusAnl(dev)) return false;
		break;
	case 34:		//线路
		if(!ReadLineAnl(dev)) return false;
		break;
	case 35:		//直流
		if(!ReadDCLineAnl(dev)) return false;
		break;
	default:
		return false;
	}
	data.ele=dev.ele;
	data.zt=dev.sta;
	data.recno=dev.recno;
	data.rp=dev.rp;
	return true;
}

bool ReadRltD::ReadN1Data(int n1type,int &num,N1Data *data,int bufnum)
{
	switch(n1type)
	{
	case 0:  return Readn1bus(num,data,bufnum);
	case 1:  return Readn1Bra(num,data,bufnum);
	case 2:  return Readn1All(num,data,bufnum);
	}
	return false;
}


//读取8点负荷预测
bool ReadRltD::ReadLF8Data(FLOADDATA *pfl,int &num)
{
	return ReadnFload8(pfl,num);
}

//读入系统告警结果

bool ReadRltD::ReadSysAlarm(SYSALARM *alm,int &num)
{
	return ReadSAlarm(alm,num);
}

//发布文件到所有节点
void ReadRltD::PutFileToAllNode(char *file)
{
	LSI_SendHmiFile(file);
}


bool ReadRltD::ReadPreAlarm(common_PreDefSF *rpd,int &num,int maxnum)
{
	return ReadPreDMDB(rpd,num,maxnum);
}

//读入灵敏度数据
bool ReadRltD::ReadSenData(READSEN&sn)
{
	return ReadSen(sn);
}
//读入统计数据
bool ReadRltD::ReadPwSys(PWSYSSUM&ps)
{
	return ReadSystj(ps);
}

//返回HMI界面文件路径
bool ReadRltD::GetHmiPath(char*path)
{
	return LSI_GetHmiPath(path);
}

//注册一个文件通知窗口
void ReadRltD::RegistFileOK(HWND hwnd)
{
	LSI_RegistWindow(hwnd,notify_FILEOK,0);
}

//取消注册一个文件通知窗口
void ReadRltD::UnRegistFileOK(HWND hwnd)
{
	LSI_UnRegistWindow(hwnd);
}

//发送界面文件到服务器
bool ReadRltD::SendHmiFile(char *filename)
{
	return LSI_SendHmiFile(filename);
}

//发送界面文件到服务器
bool ReadRltD::GetLastRecFile(char *filename)
{
	return LSI_GetLastRecFile(filename);
}


//返回需要的表ID
void ReadRltD::GetRltTable1()
{
	char dbfnm[32];
	strcpy(dbfnm,dbfstr[curdb]);
	pt=(visualpw_PT	*)GetTblAdd(dbfnm,"PT",Npt,&mpt);	
	gen=(visualpw_Gen *)GetTblAdd(dbfnm,"Gen",Ngen,&mgen);
	swt=(visualpw_Switch *)GetTblAdd(dbfnm,"Switch",Nswt,&mswt);
	ld=(visualpw_Load *)GetTblAdd(dbfnm,"Load",Nld,&mld);
	sht=(visualpw_Shunt	*)GetTblAdd(dbfnm,"Shunt",Nsht,&msht);
	srt=(visualpw_Sreact *)GetTblAdd(dbfnm,"Sreact",Nsrt,&msrt);
	tfm1=(visualpw_Tfm1 *)GetTblAdd(dbfnm,"Tfm1",Ntfm1,&mtfm1);	
	tfm2=(visualpw_Tfm2	*)GetTblAdd(dbfnm,"Tfm2",Ntfm2,&mtfm2);
	svc=(visualpw_SVC *)GetTblAdd(dbfnm,"SVC",Nsvc,&msvc);
	bus=(visualpw_Bus *)GetTblAdd(dbfnm,"Bus",Nbus,&mbus);
	lin=(visualpw_Line *)GetTblAdd(dbfnm,"Line",Nlin,&mlin);
	dclin=(visualpw_DCLine *)GetTblAdd(dbfnm,"DCLine",Ndclin,&mdclin);
	cvt=(visualpw_CVT *)GetTblAdd(dbfnm,"CVT",Ncvt,&mcvt);
	gnd=(visualpw_GND *)GetTblAdd(dbfnm,"GND",Ngnd,&mgnd);
	zone=(visualpw_Zone	*)GetTblAdd(dbfnm,"Zone",Nzone,&mzone);
	sta=(visualpw_Station *)GetTblAdd(dbfnm,"Station",Nsta,&msta);
	vot=(visualpw_VotOutage *)GetTblAdd(dbfnm,"VotOutage",Nvot,&mvot);
	lint=(visualpw_LineOutage *)GetTblAdd(dbfnm,"LineOutage",Nlint,&mlint);
	allt=(visualpw_AllOutage  *)GetTblAdd(dbfnm,"AllOutage",Nallt,&mallt);
	sys=(visualpw_SysGD	*)GetTblAdd(dbfnm,"SysGD",Nsys,&msys);
	sym=(visualpw_SysAlarm *)GetTblAdd(dbfnm,"SysAlarm",Nsym,&msym);
	clr=(common_Color *)GetTblAdd("common","Color",Nclr,&mclr);
	sen=(common_Sen *)GetTblAdd("common","Sen",Nsen,&msen);
	pdf=(common_PreDefSF*)GetTblAdd("common","PreDefSF",Npdf,&mpdf);
	mtr=(visualpw_Meter		*)GetTblAdd(dbfnm,"Meter",Nmtr,&mmtr);
	are=(visualpw_Area		*)GetTblAdd(dbfnm,"Area",Nare,&mare);
	grd=(visualpw_Grid		*)GetTblAdd(dbfnm,"Grid",Ngrd,&mgrd);
	ctg=(visualpw_CtgEffect	*)GetTblAdd(dbfnm,"CtgEffect",Nctg,&mctg);
	uequ=(common_UnEquMeas	*)GetTblAdd("common","UnEquMeas",Nuequ,&muequ);
	rel=(common_Relation	*)GetTblAdd("common","Relation",Nrel,&mrel);

	pro_bus = (ProcessData_Bus *)GetTblAdd("ProcessData","Bus", Nprobus, &mprobus);
	pro_line = (ProcessData_Line *)GetTblAdd("ProcessData","Line", Nproline, &mproline);
	pro_load = (ProcessData_Load *)GetTblAdd("ProcessData","Load", Nproload, &mproload);
	pro_gen = (ProcessData_Gen *)GetTblAdd("ProcessData","Gen", Nprogen, &mprogen);
	pro_shunt = (ProcessData_Shunt *)GetTblAdd("ProcessData","Shunt", Nproshunt, &mproshunt);
	pro_sreact = (ProcessData_Sreact *)GetTblAdd("ProcessData","Sreact", Nprosreact, &mprosreact);
	pro_tfm1 = (ProcessData_Tfm1 *)GetTblAdd("ProcessData","Tfm1", Nprotfm1, &mprotfm1);
	pro_tfm2 = (ProcessData_Tfm2 *)GetTblAdd("ProcessData","Tfm2", Nprotfm2, &mprotfm2);
	pro_switch = (ProcessData_Switch *)GetTblAdd("ProcessData","Switch", Nproswitch, &mproswitch);
	pro_sta = (ProcessData_Station *)GetTblAdd("ProcessData","Station", Nprosta, &mprosta);

}

//返回需要的表ID
void ReadRltD::GetRltTable2()
{
	char dbfnm[32];
	strcpy(dbfnm,dbfstr[curdb]);
	clr=(common_Color *)GetTblAdd("common","Color",Nclr,&mclr);
	sen=(common_Sen *)GetTblAdd("common","Sen",Nsen,&msen);
	pdf=(common_PreDefSF*)GetTblAdd("common","PreDefSF",Npdf,&mpdf);
	uequ=(common_UnEquMeas*)GetTblAdd("common","UnEquMeas",Nuequ,&muequ);
}


void * ReadRltD::GetTblAdd(char *dbstr,char *tblstr,int &num,MEMTABLE **mm)
{
	DWORD did;
	int id;
	MEMTABLE *tbl;
	if(LSI_GetTableID(dbstr,tblstr,did))  id=LOWORD(did);
	else return NULL;
	tbl=(MEMTABLE *)LSI_GetTableAdd(id);
	if(tbl==NULL) return NULL; 
	num=tbl->userec;//取得数据库中的记录数
	*mm=tbl;
	return tbl->data;
}


//读入电压颜色表
bool ReadRltD::ReadColorData(DEFCOLOR*cr,int &crsum)
{
	int i,n;
	n=Nclr;
	n=n>21 ? 21:n;
	for(i=0;i<n;i++){
		strcpy(cr[i].VLName,clr[i].VLName);
		cr[i].R=clr[i].R;
		cr[i].G=clr[i].G;
		cr[i].B=clr[i].B;
	}
	crsum=n;
	return true;
}

//检修状态合成
/*
	0=正常
	1=正在检修
	2=已有计划，但还没到时候
	3=时间到，检修还没有开始
	4=正在检修，但超过检修时间
*/
int ReadRltD::CombineRpSta(CTime tm1,CTime tm2,int ele,int sta)
{
	int rp=0;
	switch(ele)
	{
	case 0:
		if(curtm>tm1&&curtm<tm2) rp=1;
		else if(curtm>tm2&&tmdx>(curtm-tm2)) rp=4; //只限定在一天之内
		break;
	case 1:
		if(curtm>tm1&&curtm<tm2) rp=2;
		else if(curtm<tm1) rp=3; 
		break;
	}	
	return rp;
}


bool ReadRltD::ReadGenAnl(READDEV&data)
{
	bool canread=false;
	int i,j;
	if(bShowProcessData == false)
	{
		if(data.recno>=0&&data.recno<Ngen){ //验证带来的号是否可用
			j=data.recno;
			if(gen[j].NU==(DWORD)data.did) canread=true;
		}
		if(!canread){ //如不能直接读，再查找序号
			for(i=0;i<Ngen;i++){
				if(gen[i].NU==(DWORD)data.did)
				{
					j=i;
					canread=true;
					break;
				}
			}
		}
		if(canread){
			data.ele=gen[j].ele;
			data.sta=gen[j].sta;
			data.trb=gen[j].Tsta;
			data.value[0]=gen[j].P;
			data.value[1]=gen[j].Q;
			data.value[2]=gen[j].MaxP;
			data.value[3]=gen[j].Pchk;
			data.value[4]=gen[j].angle;
			//data.rp=(BYTE)CombineRpSta(gen[j].rptm1,gen[j].rptm2,gen[j].ele,gen[j].sta);
			//if(curtm>gen[j].rptm1&&curtm<gen[j].rptm2) data.rp=1;else data.rp=0;
			data.recno=j;
		}
	}
	else
	{
		if(data.recno>=0&&data.recno<Nprogen){ //验证带来的号是否可用
			j=data.recno;
			if(pro_gen[j].NU==(DWORD)data.did) canread=true;
		}
		if(!canread){ //如不能直接读，再查找序号
			for(i=0;i<Nprogen;i++){
				if(pro_gen[i].NU==(DWORD)data.did)
				{
					j=i;
					canread=true;
					break;
				}
			}
		}
		if(canread){
			data.ele=pro_gen[j].ele;
			data.sta=pro_gen[j].sta;
		//	data.trb=gen[j].Tsta;
			data.value[0]=pro_gen[j].P;
			data.value[1]=pro_gen[j].Q;
			data.value[2]=pro_gen[j].MaxP;
			data.value[5]=pro_gen[j].SeP;
			data.value[6]=pro_gen[j].SeQ;
			data.value[7]=pro_gen[j].OpfP;
			data.value[8]=pro_gen[j].OpfQ;
			//data.rp=(BYTE)CombineRpSta(gen[j].rptm1,gen[j].rptm2,gen[j].ele,gen[j].sta);
			//if(curtm>gen[j].rptm1&&curtm<gen[j].rptm2) data.rp=1;else data.rp=0;
			data.recno=j;
		}
	}
	
	return canread;
}

bool ReadRltD::ReadMTxtAnl(READDEV&data)
{
	bool canread=false;
	/*int i,j;
	if(data.recno>=0&&data.recno<Nhvc){ //验证带来的号是否可用
		j=data.recno;
		if(hvc[j].ID==(DWORD)data.did) canread=true;
	}
	if(!canread){ //如不能直接读，再查找序号
		for(i=0;i<Nhvc;i++){
			if(hvc[i].ID==(DWORD)data.did)
			{
				j=i;
				canread=true;
				break;
			}
		}
	}
	if(canread)
	{
		data.ele=1;
		data.sta=hvc[j].sta;
		data.value[0]=hvc[j].Curval;
		data.value[1]=hvc[j].Vlimit;
		if(hvc[j].Curval>hvc[j].Vlimit) data.alarmhilo=1;
		else data.alarmhilo=0;
		data.recno=j;
	}*/
	return canread;
}

//读入交流线路的参数
bool ReadRltD::ReadLineAnl(READDEV&data)
{
	bool canread=false;
	int i,j;
	if(bShowProcessData==false)
	{
		if(data.recno>=0&&data.recno<Nlin){ //验证带来的号是否可用
			j=data.recno;
			if(lin[j].NU==(DWORD)data.did) canread=true;
		}
		if(!canread){ //如不能直接读，再查找序号
			for(i=0;i<Nlin;i++){
				if(lin[i].NU==(DWORD)data.did)
				{
					j=i;
					canread=true;
					break;
				}
			}
		}
		
		if(canread){
			data.ele=lin[j].ele;
			data.sta=lin[j].sta;
			data.trb=lin[j].Tsta;
			data.value[0] = lin[j].Pf ;
			data.value[1] =lin[j].Qf ;
			data.value[2] =lin[j].Pt ;
			data.value[3] =lin[j].Qt ;
			data.value[4] = lin[j].MaxP;
			data.value[5] = 0;
			//data.rp=(BYTE)CombineRpSta(lin[j].rptm1,lin[j].rptm2,lin[j].ele,lin[j].sta);
			//if(curtm>lin[j].rptm1&&curtm<lin[j].rptm2) data.rp=1;else data.rp=0;
			data.value[6] = lin[j].Imax;
			data.value[7] = lin[j].I;
			data.recno=j;
			
		}
	}
	else
	{
		if(data.recno>=0&&data.recno<Nproline){ //验证带来的号是否可用
			j=data.recno;
			if(pro_line[j].NU==(DWORD)data.did) canread=true;
		}
		if(!canread){ //如不能直接读，再查找序号
			for(i=0;i<Nproline;i++){
				if(pro_line[i].NU==(DWORD)data.did)
				{
					j=i;
					canread=true;
					break;
				}
			}
		}
		
		if(canread){
			data.ele=pro_line[j].ele;
			data.sta=pro_line[j].sta;
			data.recno=j;
			//data.trb=lin[j].Tsta;
			
			data.value[0] = pro_line[j].Pf;
			data.value[1] = pro_line[j].Qf;
			data.value[2] = pro_line[j].Pt;
			data.value[3] = pro_line[j].Qt;
			data.value[4] = pro_line[j].MaxP;
			data.value[7] = pro_line[j].I;

			data.rp = 1;
			//data.rp=(BYTE)CombineRpSta(lin[j].rptm1,lin[j].rptm2,lin[j].ele,lin[j].sta);
			//if(curtm>lin[j].rptm1&&curtm<lin[j].rptm2) data.rp=1;else data.rp=0;

			data.value[5] = pro_line[j].SePf;
			data.value[6] = pro_line[j].SeQf;
			data.value[8] = pro_line[j].SePt;
			data.value[9] = pro_line[j].SeQt;
			data.value[10] = pro_line[j].SeI;
			
			data.value[11] = pro_line[j].OpfPf;
			data.value[12] = pro_line[j].OpfQf;
			data.value[13] = pro_line[j].OpfPt;
			data.value[14] = pro_line[j].OpfQt;
			data.value[15] = pro_line[j].OpfI;
		}
	}

	return canread;
}


bool ReadRltD::ReadStation(READDEV&data)
{
	bool canread=false;
	int i,j;

	if(bShowProcessData == false)
	{
		if(data.recno>=0&&data.recno<Nsta){ //验证带来的号是否可用
			j=data.recno;
			if(sta[j].NU==(DWORD)data.did) canread=true;
		}
		if(!canread){ //如不能直接读，再查找序号
			for(i=0;i<Nprosta;i++){
				if(sta[i].NU==(DWORD)data.did)
				{
					j=i;
					canread=true;
					break;
				}
			}
		} 
		if(canread)
		{
			data.alarmband = 0;//sta[j].CtrlSta;
			data.recno=j;
		}
	}
	else
	{
		if(data.recno>=0&&data.recno<Nprosta){ //验证带来的号是否可用
			j=data.recno;
			if(pro_sta[j].NU==(DWORD)data.did) canread=true;
		}
		if(!canread){ //如不能直接读，再查找序号
			for(i=0;i<Nprosta;i++){
				if(pro_sta[i].NU==(DWORD)data.did)
				{
					j=i;
					canread=true;
					break;
				}
			}
		} 
		if(canread)
		{
			data.alarmband = pro_sta[j].CtrlSta;
			data.recno=j;
		}
	}
	return canread;
}

//读入直流线数据
bool ReadRltD::ReadDCLineAnl(READDEV&data)
{
	bool canread=false;
	int i,j;
	if(data.recno>=0&&data.recno<Ndclin){ //验证带来的号是否可用
		j=data.recno;
		if(dclin[j].NU==(DWORD)data.did) canread=true;
	}
	if(!canread){ //如不能直接读，再查找序号
		for(i=0;i<Ndclin;i++){
			if(dclin[i].NU==(DWORD)data.did)
			{
				j=i;
				canread=true;
				break;
			}
		}
	}
	if(canread){
		data.ele=dclin[j].ele;
		data.sta=dclin[j].sta;
		data.trb=dclin[j].Tsta;
		data.value[0]=dclin[j].Pf;
		data.value[1]=dclin[j].Qf;
		data.value[2]=dclin[j].Pt;
		data.value[3]=dclin[j].Qt;
		data.value[4]=dclin[j].Maxp;
		data.value[5]=0;
		//data.rp=(BYTE)CombineRpSta(dclin[j].rptm1,dclin[j].rptm2,dclin[j].ele,dclin[j].sta);
		//if(curtm>dclin[j].rptm1&&curtm<dclin[j].rptm2) data.rp=1;else data.rp=0;
		data.value[6]=dclin[j].Imax;
		data.value[7]=dclin[j].I;
		data.recno=j;
	}
	return canread;
}

//读母线的参数
bool ReadRltD::ReadBusAnl(READDEV&data)
{
	bool canread=false;
	int i,j;

	if(bShowProcessData == false)
	{
		if(data.recno>=0&&data.recno<Nbus){ //验证带来的号是否可用
			j=data.recno;
			if(bus[j].NU==(DWORD)data.did) canread=true;
		}
		if(!canread){ //如不能直接读，再查找序号
			for(i=0;i<Nbus;i++){
				if(bus[i].NU==(DWORD)data.did)
				{
					j=i;
					canread=true;
					break;
				}
			}
		} 
		if(canread){
			data.ele=bus[j].ele;
			data.sta=bus[j].sta;
			data.trb=bus[j].Tsta;
			data.alarmhilo=bus[j].AlarmHiLo;
			data.alarmband=0;//bus[j].AlarmBand;
			data.value[0]=0;
			data.value[1]=bus[j].V;
			data.value[2]=bus[j].deg;
			data.value[3]=bus[j].MaxV;
			data.value[4]=bus[j].MinV;
			data.value[5]=0;
			data.value[6]=0;
			data.value[7]=bus[j].Vb;
			data.value[8]=bus[j].DayMax;
			data.value[9]=bus[j].DayMin;

			//data.rp=(BYTE)CombineRpSta(bus[j].rptm1,bus[j].rptm2,bus[j].ele,bus[j].sta);
			//if(curtm>bus[j].rptm1&&curtm<bus[j].rptm2) data.rp=1;else data.rp=0;
			data.recno=j;
		}
	}
	else
	{
		if(data.recno>=0&&data.recno<Nprobus){ //验证带来的号是否可用
			j=data.recno;
			if(pro_bus[j].NU==(DWORD)data.did) canread=true;
		}
		if(!canread){ //如不能直接读，再查找序号
			for(i=0;i<Nprobus;i++){
				if(pro_bus[i].NU==(DWORD)data.did)
				{
					j=i;
					canread=true;
					break;
				}
			}
		} 
		if(canread){
			data.ele=pro_bus[j].ele;
			data.sta=pro_bus[j].sta;
			//data.trb=bus[j].Tsta;
		//	data.alarmhilo=bus[j].AlarmHiLo;
		//	data.alarmband=pro_bus[j].AlarmBand;
			data.value[0]=0;
			data.value[1]=pro_bus[j].V;
			//data.value[2]=pro_bus[j].deg;
			data.value[3]=pro_bus[j].MaxV;
			data.value[4]=pro_bus[j].MinV;
			data.value[5]=0;
			data.value[6]=0;
			data.value[7]=pro_bus[j].Vb;
//			data.value[8]=bus[j].DayMax;
//			data.value[9]=bus[j].DayMin;

			//data.value[10]=pro_bus[j].Vb;
			data.value[11]=pro_bus[j].deg;
			data.value[12]=pro_bus[j].SeVb;
			data.value[13]=pro_bus[j].Sedeg;
			data.value[14]=pro_bus[j].OpfVb;
			data.value[15]=pro_bus[j].Opfdeg;
			
			data.alarmband = pro_bus[j].CtrlSta;
			//data.rp=(BYTE)CombineRpSta(bus[j].rptm1,bus[j].rptm2,bus[j].ele,bus[j].sta);
			//if(curtm>bus[j].rptm1&&curtm<bus[j].rptm2) data.rp=1;else data.rp=0;
			data.recno=j;
		}
	}
	
	return canread;
}

//读负荷参数
bool ReadRltD::ReadLoadAnl(READDEV&data)
{
	bool canread=false;
	int i,j;
	if(bShowProcessData == false)
	{
		if(data.recno>=0&&data.recno<Nld){ //验证带来的号是否可用
			j=data.recno;
			if(ld[j].NU==(DWORD)data.did) canread=true;
		}
		if(!canread){ //如不能直接读，再查找序号
			for(i=0;i<Nld;i++){
				if(ld[i].NU==(DWORD)data.did)
				{
					j=i;
					canread=true;
					break;
				}
			}
		}
		if(canread){
			data.ele=ld[j].ele;
			data.sta=ld[j].sta;
			data.trb=0;
			data.value[0]=ld[j].P;
			data.value[1]=ld[j].Q;
			data.value[2]=ld[j].MaxP;
			data.value[3]=ld[j].MinP;
			data.rp=0;
			data.recno=j;
		}
	}
	else
	{
		if(data.recno>=0&&data.recno<Nproload){ //验证带来的号是否可用
			j=data.recno;
			if(pro_load[j].NU==(DWORD)data.did) canread=true;
		}
		if(!canread){ //如不能直接读，再查找序号
			for(i=0;i<Nproload;i++){
				if(pro_load[i].NU==(DWORD)data.did)
				{
					j=i;
					canread=true;
					break;
				}
			}
		}
		if(canread){
			data.ele=pro_load[j].ele;
			data.sta=pro_load[j].sta;
			data.trb=0;
			data.value[0]=pro_load[j].P;
			data.value[1]=pro_load[j].Q;
			data.value[4]=pro_load[j].SeP;
			data.value[5]=pro_load[j].SeQ;
			data.value[6]=pro_load[j].OpfP;
			data.value[7]=pro_load[j].OpfQ;
			data.rp=0;
			data.recno=j;
		}
	}
	
	return canread;
}

//读2绕组变压器
bool ReadRltD::ReadTRan1(READDEV&data)
{
	bool canread=false;
	int i,j;
	if (bShowProcessData == false)
	{
		if(data.recno>=0&&data.recno<Ntfm1){ //验证带来的号是否可用
			j=data.recno;
			if(tfm1[j].NU==(DWORD)data.did) canread=true;
		}
		if(!canread){ //如不能直接读，再查找序号
			for(i=0;i<Ntfm1;i++){
				if(tfm1[i].NU==(DWORD)data.did)
				{
					j=i;
					canread=true;
					break;
				}
			}
		}
		if(canread){
			data.ele=tfm1[j].ele;
			data.sta=tfm1[j].sta;
			data.trb=tfm1[j].Tsta;
			data.value[0]=tfm1[j].tap;
			data.value[1]=tfm1[j].Pmax;
			data.value[2]=tfm1[j].P;
			data.value[3]=(float)(tfm1[j].Tover-tfm1[j].Tallow); //超限时间
			data.value[4]=tfm1[j].Tcur;
			data.value[5]=tfm1[j].Tmax;
			data.value[6]=tfm1[j].Q;
			data.value[7]=tfm1[j].P2;
			data.value[8]=tfm1[j].Q2;
			data.value[9]=tfm1[j].I;
			data.value[10]=tfm1[j].I2;
			data.alarmband=0;
			//data.rp=(BYTE)CombineRpSta(tfm1[j].rptm1,tfm1[j].rptm2,tfm1[j].ele,tfm1[j].sta);
			//if(curtm>tfm1[j].rptm1&&curtm<tfm1[j].rptm2) data.rp=1;else data.rp=0;
			data.recno=j;
		}
	}
	else
	{
		if(data.recno>=0&&data.recno<Nprotfm1){ //验证带来的号是否可用
			j=data.recno;
			if(pro_tfm1[j].NU==(DWORD)data.did) canread=true;
		}
		if(!canread){ //如不能直接读，再查找序号
			for(i=0;i<Nprotfm1;i++){
				if(pro_tfm1[i].NU==(DWORD)data.did)
				{
					j=i;
					canread=true;
					break;
				}
			}
		}
		if(canread){
			data.ele=pro_tfm1[j].ele;
			data.sta=pro_tfm1[j].sta;
			//data.trb=tfm1[j].Tsta;
			data.value[0]=pro_tfm1[j].tap;
			data.value[1]=pro_tfm1[j].Pmax;
			data.value[2]=pro_tfm1[j].P;
			//data.value[3]=(float)(tfm1[j].Tover-tfm1[j].Tallow); //超限时间
			//data.value[4]=pro_tfm1[j].Tcur;
			//data.value[5]=pro_tfm1[j].Tmax;
			data.value[6]=pro_tfm1[j].Q; 
			data.value[7]=pro_tfm1[j].P2;
			data.value[8]=pro_tfm1[j].Q2;
			data.value[9]=pro_tfm1[j].I;
			data.value[10]=pro_tfm1[j].I2;

			data.alarmband = pro_tfm1[j].CtrlSta;
			//data.rp=(BYTE)CombineRpSta(tfm1[j].rptm1,tfm1[j].rptm2,tfm1[j].ele,tfm1[j].sta);
			//if(curtm>tfm1[j].rptm1&&curtm<tfm1[j].rptm2) data.rp=1;else data.rp=0;

			data.value[11]=pro_tfm1[j].SeP;
			data.value[12]=pro_tfm1[j].SeQ;
			data.value[13]=pro_tfm1[j].SeP2;
			data.value[14]=pro_tfm1[j].SeQ2;
			data.value[15]=pro_tfm1[j].Setap;

			data.value[16]=pro_tfm1[j].OpfP;
			data.value[17]=pro_tfm1[j].OpfQ;
			data.value[18]=pro_tfm1[j].OpfP2;
			data.value[19]=pro_tfm1[j].OpfQ2;
			data.value[20]=pro_tfm1[j].Opftap;

			data.recno=j;
		}
	}
	
	return canread;
}

//读3绕组变压器wd
bool ReadRltD::ReadTRan2(READDEV&data)
{
	bool canread=false;
	int i,j;
	if(bShowProcessData == false)
	{
		if(data.recno>=0&&data.recno<Ntfm2){ //验证带来的号是否可用
			j=data.recno;
			if(tfm2[j].NU==(DWORD)data.did) canread=true;
		}
		if(!canread){ //如不能直接读，再查找序号
			for(i=0;i<Ntfm2;i++){
				if(tfm2[i].NU==(DWORD)data.did)
				{
					j=i;
					canread=true;
					break;
				}
			}
		}
		if(canread){
			data.ele=tfm2[j].ele;
			data.sta=tfm2[j].sta;
			data.trb=tfm2[j].Tsta;
			if(tfm2[j].TapM>0 && tfm2[j].TapH==0.0f)
				data.value[0]=tfm2[j].TapM;
			else
				data.value[0]=tfm2[j].TapH;
			data.value[1]=tfm2[j].TapM;
			data.value[2]=tfm2[j].TapL;
			data.value[3]=tfm2[j].Pmax;
			data.value[4]=tfm2[j].P;
			data.value[5]=(float)(tfm2[j].Tover-tfm2[j].Tallow); //超限时间
			data.value[6]=tfm2[j].Tcur;
			data.value[7]=tfm2[j].Tmax;
			data.value[8]=tfm2[j].Q;
			data.value[9]=tfm2[j].P2;
			data.value[10]=tfm2[j].Q2;
			data.value[11]=tfm2[j].P3;
			data.value[12]=tfm2[j].Q3;
			data.value[13]=tfm2[j].I;
			data.value[14]=tfm2[j].I2;
			data.value[15]=tfm2[j].I3;
			data.alarmband=0;
			//data.rp=(BYTE)CombineRpSta(tfm2[j].rptm1,tfm2[j].rptm2,tfm2[j].ele,tfm2[j].sta);
			//if(curtm>tfm2[j].rptm1&&curtm<tfm2[j].rptm2) data.rp=1;else data.rp=0;
			data.recno=j;
		}
	}
	else
	{
		if(data.recno>=0&&data.recno<Nprotfm2){ //验证带来的号是否可用
			j=data.recno;
			if(pro_tfm2[j].NU==(DWORD)data.did) canread=true;
		}
		if(!canread){ //如不能直接读，再查找序号
			for(i=0;i<Nprotfm2;i++){
				if(pro_tfm2[i].NU==(DWORD)data.did)
				{
					j=i;
					canread=true;
					break;
				}
			}
		}
		if(canread){
			data.ele=pro_tfm2[j].ele;
			data.sta=pro_tfm2[j].sta;
			//data.trb=tfm2[j].Tsta;
			if(pro_tfm2[j].TapM>0 && pro_tfm2[j].TapH==0.0f)
				data.value[0]=pro_tfm2[j].TapM;
			else
				data.value[0]=pro_tfm2[j].TapH;
			data.value[1]=pro_tfm2[j].TapM;
			//data.value[2]=pro_tfm2[j].TapL;
			data.value[3]=pro_tfm2[j].Pmax;
			data.value[4]=pro_tfm2[j].P; 
			//data.value[5]=(float)(tfm2[j].Tover-tfm2[j].Tallow); //超限时间
			//data.value[6]=pro_tfm2[j].Tcur;
			//data.value[7]=pro_tfm2[j].Tmax;
			data.value[8]=pro_tfm2[j].Q;
			data.value[9]=pro_tfm2[j].P2;
			data.value[10]=pro_tfm2[j].Q2;
			data.value[11]=pro_tfm2[j].P3;
			data.value[12]=pro_tfm2[j].Q3;
			data.value[13]=pro_tfm2[j].I;
			data.value[14]=pro_tfm2[j].I2;
			data.value[15]=pro_tfm2[j].I3;
			data.alarmband = pro_tfm2[j].CtrlSta;
			//data.rp=(BYTE)CombineRpSta(tfm2[j].rptm1,tfm2[j].rptm2,tfm2[j].ele,tfm2[j].sta);
			//if(curtm>tfm2[j].rptm1&&curtm<tfm2[j].rptm2) data.rp=1;else data.rp=0;

			data.value[16]=pro_tfm2[j].SeP;
			data.value[17]=pro_tfm2[j].SeP2;
			data.value[18]=pro_tfm2[j].SeP3;
			data.value[19]=pro_tfm2[j].SeQ;
			data.value[20]=pro_tfm2[j].SeQ2;
			data.value[21]=pro_tfm2[j].SeQ3;
			data.value[22]=pro_tfm2[j].SeTapH;
			data.value[23]=pro_tfm2[j].SeTapM;

			data.value[24]=pro_tfm2[j].OpfP;
			data.value[25]=pro_tfm2[j].OpfP2;
			data.value[26]=pro_tfm2[j].OpfP3;
			data.value[27]=pro_tfm2[j].OpfQ;
			data.value[28]=pro_tfm2[j].OpfQ2;
			data.value[29]=pro_tfm2[j].OpfQ3;
			data.value[30]=pro_tfm2[j].OpfTapH;
			data.value[31]=pro_tfm2[j].OpfTapM;

			data.recno=j;
		}
	}
	
	return canread;
}

//读入电容
bool ReadRltD::ReadShuAnl(READDEV&data)
{
	bool canread=false;
	int i,j;
	if(bShowProcessData == false)
	{
		if(data.recno>=0&&data.recno<Nsht){ //验证带来的号是否可用
			j=data.recno;
			if(sht[j].NU==(DWORD)data.did) canread=true;
		}
		if(!canread){ //如不能直接读，再查找序号
			for(i=0;i<Nsht;i++){
				if(sht[i].NU==(DWORD)data.did)
				{
					j=i;
					canread=true;
					break;
				}
			}
		}
		if(canread){
			data.ele=sht[j].ele;
			data.sta=sht[j].sta;
			data.trb=sht[j].Tsta;
			data.value[0]=sht[j].Q;
			data.value[1]=0;
			data.value[2]=sht[j].Qmax;
			data.recno=j;
			data.alarmband=0;
		}
	}
	else
	{
		if(data.recno>=0&&data.recno<Nproshunt){ //验证带来的号是否可用
			j=data.recno;
			if(pro_shunt[j].NU==(DWORD)data.did) canread=true;
		}
		if(!canread){ //如不能直接读，再查找序号
			for(i=0;i<Nproshunt;i++){
				if(pro_shunt[i].NU==(DWORD)data.did)
				{
					j=i;
					canread=true;
					break;
				}
			}
		}
		if(canread){
			data.ele=pro_shunt[j].ele;
			data.sta=pro_shunt[j].sta;
			//data.trb=sht[j].Tsta;
			data.value[0]=pro_shunt[j].Q;
			data.value[1]=0;
			data.value[2]=pro_shunt[j].Qmax;

			data.value[3]=pro_shunt[j].SeQ;
			data.value[4]=pro_shunt[j].OpfQ;
			data.alarmband = pro_shunt[j].CtrlSta;
			data.recno=j;
		}
	}
	
	return canread;
}


//读入电抗

bool ReadRltD::ReadSreAnl(READDEV&data)
{
	bool canread=false;
	int i,j;
	if(bShowProcessData == false)
	{
		if(data.recno>=0&&data.recno<Nsrt){ //验证带来的号是否可用
			j=data.recno;
			if(srt[j].NU==(DWORD)data.did) canread=true;
		}
		if(!canread){ //如不能直接读，再查找序号
			for(i=0;i<Nsrt;i++){
				if(srt[i].NU==(DWORD)data.did)
				{
					j=i;
					canread=true;
					break;
				}
			}
		}
		if(canread){
			data.ele=srt[j].ele;
			data.sta=srt[j].sta;
			data.trb=srt[j].Tsta;
			data.value[0]=srt[j].Zx;
			data.value[1]=0;
			data.recno=j;
			data.rp=0;
			data.alarmband=0;
		}
	}
	else
	{
		if(data.recno>=0&&data.recno<Nprosreact){ //验证带来的号是否可用
			j=data.recno;
			if(pro_sreact[j].NU==(DWORD)data.did) canread=true;
		}
		if(!canread){ //如不能直接读，再查找序号
			for(i=0;i<Nprosreact;i++){
				if(pro_sreact[i].NU==(DWORD)data.did)
				{
					j=i;
					canread=true;
					break;
				}
			}
		}
		if(canread){
			data.ele=pro_sreact[j].ele;
			data.sta=pro_sreact[j].sta;
			//data.trb=srt[j].Tsta;
			//data.value[0]=pro_sreact[j].Zx;

			data.value[1]=0;

			data.value[3]=pro_sreact[j].Q;
			data.value[4]=pro_sreact[j].I;
			data.value[5]=pro_sreact[j].SeQ;
			data.value[6]=pro_sreact[j].SeI;
			data.value[7]=pro_sreact[j].OpfQ;
			data.value[8]=pro_sreact[j].OpfI;
			data.alarmband = pro_sreact[j].CtrlSta;

			data.recno=j;
			data.rp=0;
		}
	}
	
	return canread;
}

//读SVC参数

bool ReadRltD::ReadSvcAnl(READDEV&data)
{
	bool canread=false;
	int i,j;
	if(data.recno>=0&&data.recno<Nsvc){ //验证带来的号是否可用
		j=data.recno;
		if(svc[j].NU==(DWORD)data.did) canread=true;
	}
	if(!canread){ //如不能直接读，再查找序号
		for(i=0;i<Nsvc;i++){
			if(svc[i].NU==(DWORD)data.did)
			{
				j=i;
				canread=true;
				break;
			}
		}
	}
	if(canread){
		data.ele=svc[j].ele;
		data.sta=svc[j].sta;
		data.trb=svc[j].Tsta;
		data.value[0]=svc[j].Q;
		data.value[1]=svc[j].Qmax;
		data.value[2]=svc[j].Qmin;
		data.recno=j;
		data.rp=0;
	}
	return canread;
}


//读区域参数
bool ReadRltD::ReadZoneAnl(READDEV&data)
{
	switch(data.xsmode)
	{
	case 0:
		return ReadZoneAnl0(data);
		break;
	case 1:
		return ReadZoneAnl1(data);
		break;
	case 2:
		return ReadDmAnl(data);
		break;
	}
	return false;
}

bool ReadRltD::ReadZoneAnl0(READDEV&data)
{
	bool canread=false;
	int i,j;
	if(data.recno>=0&&data.recno<Nzone){ //验证带来的号是否可用
		j=data.recno;
		if(zone[j].NU==(DWORD)data.did) canread=true;
	}
	if(!canread){ //如不能直接读，再查找序号
		for(i=0;i<Nzone;i++){
			if(zone[i].NU==(DWORD)data.did)
			{
				j=i;
				canread=true;
			}
		}
	}
	if(canread){
		data.ele=1;
		data.sta=1;
		data.value[0]=zone[j].Pgen;
		data.value[1]=zone[j].Qgen;
		data.value[2]=zone[j].GenMax;
		data.value[3]=zone[j].Pld;						
		data.value[4]=zone[j].Qld;						
		data.value[5]=zone[j].LdMax;	
		data.value[6]=zone[j].ZoneLP;						
		data.value[7]=zone[j].ZoneLQ;
		data.recno=j;
	}
	return canread;
}

bool ReadRltD::ReadZoneAnl1(READDEV&data)
{
	bool canread=false;
	int i,j;
	if(data.recno>=0&&data.recno<Nzone){ //验证带来的号是否可用
		j=data.recno;
		if(zone[j].NU==(DWORD)data.did) canread=true;
	}
	if(!canread){ //如不能直接读，再查找序号
		for(i=0;i<Nzone;i++){
			if(zone[i].NU==(DWORD)data.did)
			{
				j=i;
				canread=true;
			}
		}
	}
	if(canread){
		data.ele=1;
		data.sta=1;
		data.value[0]=zone[j].Pld;
		data.value[1]=zone[j].Qld;
		data.value[2]=zone[j].LdMax;
		data.recno=j;
	}
	return canread;
}

bool ReadRltD::ReadDmAnl(READDEV&data)
{
	bool canread=false;
	int i,j;
	if(data.recno>=0&&data.recno<Npdf){ //验证带来的号是否可用
		j=data.recno;
		if(pdf[j].ID==(DWORD)data.did) canread=true;
	}
	if(!canread){ //如不能直接读，再查找序号
		for(i=0;i<Npdf;i++){
			if(pdf[i].ID==(DWORD)data.did)
			{
				j=i;
				canread=true;
			}
		}
	}
	if(canread){
		data.ele=1;
		data.sta=1;
		data.value[0]=pdf[j].curval;
		data.value[1]=pdf[j].Qcur;
		data.value[2]=pdf[j].Vmax;
		data.value[3]=pdf[j].Pcur;//实际是最小值
		data.recno=j;
	}
	return canread;
}


bool ReadRltD::ReadSysAnl(READDEV&data)
{
	bool canread=false;
	int i,j;
	if(data.recno>=0&&data.recno<Nsys){ //验证带来的号是否可用
		j=data.recno;
		if(sys[j].ID==(DWORD)data.did) canread=true;
	}
	if(!canread){ //如不能直接读，再查找序号
		for(i=0;i<Nsys;i++){
			if(sys[i].ID==(DWORD)data.did)
			{
				j=i;
				canread=true;
			}
		}
	}
	if(canread){
		data.ele=1;
		data.sta=1;
		data.value[0]=sys[j].zb;
		data.recno=j;
	}
	return canread;
}

bool ReadRltD::ReadUnEquAnl(READDEV&data)
{
	bool canread=false;
	int i,j;
	if(data.recno>=0&&data.recno<Nuequ){ //验证带来的号是否可用
		j=data.recno;
		if(uequ[j].NU==(DWORD)data.did) canread=true;
	}
	if(!canread){ //如不能直接读，再查找序号
		for(i=0;i<Nuequ;i++){
			if(uequ[i].NU==(DWORD)data.did)
			{
				j=i;
				canread=true;
				break;
			}
		}
	}
	if(canread){
		data.ele=1;
		data.sta=1;
		data.value[0]=uequ[j].val;
		data.recno=j;
	}
	return canread;
}

bool ReadRltD::ReadRelEquAnl(READDEV&data)
{
	bool canread=false;
	int i,j;
	if(data.recno>=0&&data.recno<Nrel){ //验证带来的号是否可用
		j=data.recno;
		if(rel[j].NU==(DWORD)data.did) canread=true;
	}
	if(!canread){ //如不能直接读，再查找序号
		for(i=0;i<Nrel;i++){
			if(rel[i].NU==(DWORD)data.did)
			{
				j=i;
				canread=true;
				break;
			}
		}
	}
	if(canread){
		data.ele=1;
		data.sta=1;
		data.value[0]=rel[j].SectVal;
		data.value[1]=rel[j].SeVal;
		data.value[2]=rel[j].EmVal;
		data.value[3]=rel[j].SndVal;
		data.recno=j;
	}
	return canread;
}

//读取系统指标
bool ReadRltD::ReadSysGd(YBDATA&data)
{
	bool canread=false;
	int i,j;
	if(data.recno>=0&&data.recno<Nsys){ //验证带来的号是否可用
		j=data.recno;
		if(sys[j].ID==(DWORD)data.did) canread=true;
	}
	if(!canread){ //如不能直接读，再查找序号
		for(i=0;i<Nsys;i++){
			if(sys[i].ID==(DWORD)data.did)
			{
				j=i;
				canread=true;
				break;
			}
		}
	}
	if(canread){
		data.curval=sys[j].zb;
		data.vmax=sys[j].Vmax;
		data.vmin=sys[j].Vmin;
		data.vmax1=sys[j].Vmax1;
		data.vmin1=sys[j].Vmin1;
		data.vmax2=sys[j].Vmax2;
		data.vmin2=sys[j].Vmin2;
		data.recno=j;
	}
	return canread;
}


//读预定义断面
bool ReadRltD::ReadPreDMDB(common_PreDefSF *rpd,int &num,int maxnum)
{
	bool canread=false;
	int i;
	num=0;
	for(i=0;i<Npdf;i++)
	{
		if(num>=maxnum) break;
		rpd[i]=pdf[i];
		num++;
	}
	return true;
}



//读PT参数
bool ReadRltD::ReadPTSta(READDEV&data)
{
	bool canread=false;
	int i,j;
	if(data.recno>=0&&data.recno<Npt){ //验证带来的号是否可用
		j=data.recno;
		if(pt[j].NU==(DWORD)data.did) canread=true;
	}
	if(!canread){ //如不能直接读，再查找序号
		for(i=0;i<Npt;i++){
			if(pt[i].NU==(DWORD)data.did)
			{
				j=i;
				canread=true;
				break;
			}
		}
	}
	if(canread){
		data.ele=pt[j].ele;
		data.sta=pt[j].sta;
		data.trb=0;
		data.rp=0;
		data.recno=j;
	}
	return canread;
}

//读Switch参数
bool ReadRltD::ReadSwitchSta(READDEV&data,CTime &tm)
{
	bool canread=false;
	int i,j;
	if(bShowProcessData == false)
	{
		if(data.recno>=0&&data.recno<Nswt){ //验证带来的号是否可用
			j=data.recno;
			if(swt[j].NU==(DWORD)data.did) canread=true;
		}
		if(!canread){ //如不能直接读，再查找序号
			for(i=0;i<Nswt;i++){
				if(swt[i].NU==(DWORD)data.did)
				{
					j=i;
					canread=true;
					break;
				}
			}
		}
		if(canread){
			data.ele=swt[j].ele;
			data.sta=swt[j].sta;
			data.trb=swt[j].Tsta;
			data.recno=j;
			tm=0;
			data.rp=(BYTE)CombineRpSta(swt[j].rptm1,swt[j].rptm2,swt[j].ele,swt[j].sta);
			//if(curtm>swt[j].rptm1&&curtm<swt[j].rptm2) data.rp=1;else data.rp=0;
		}
	}
	else
	{
		if(data.recno>=0&&data.recno<Nproswitch){ //验证带来的号是否可用
			j=data.recno;
			if(pro_switch[j].NU==(DWORD)data.did) canread=true;
		}
		if(!canread){ //如不能直接读，再查找序号
			for(i=0;i<Nproswitch;i++){
				if(pro_switch[i].NU==(DWORD)data.did)
				{
					j=i;
					canread=true;
					break;
				}
			}
		}
		if(canread){
			data.ele=pro_switch[j].ele;
			data.sta=pro_switch[j].sta;
			data.trb=pro_switch[j].Tsta;
			data.recno=j;
			tm=0;
			data.rp=(BYTE)CombineRpSta(pro_switch[j].rptm1,pro_switch[j].rptm2,pro_switch[j].ele,pro_switch[j].sta);
			//if(curtm>swt[j].rptm1&&curtm<swt[j].rptm2) data.rp=1;else data.rp=0;
		}
	}
	
	return canread;
}

//读Relay参数
bool ReadRltD::ReadRelaySta(READDEV&data)
{
	bool canread=false;
	/*int i,j;
	if(data.recno>=0&&data.recno<Nrly){ //验证带来的号是否可用
		j=data.recno;
		if(rly[j].NU==data.did) canread=true;
	}
	if(!canread){ //如不能直接读，再查找序号
		for(i=0;i<Nrly;i++)
		{
			if(rly[i].NU==data.did)
			{
				j=i;
				canread=true;
				break;
			}
		}
	}
	if(canread){
		data.ele=1;
		data.sta=rly[j].sta;
		data.recno=j;
		data.rp=0;
	}*/
	return canread;
}

//读Relay参数
bool ReadRltD::ReadStusSta(READDEV&data)
{
	bool canread=false;
/*	int i,j;
	if(data.recno>=0&&data.recno<Nstus){//验证带来的号是否可用
		j=data.recno;
		if(stus[j].NU==data.did) canread=true;
	}
	if(!canread){ //如不能直接读，再查找序号
		for(i=0;i<Nstus;i++)
		{
			if(stus[i].NU==data.did)
			{
				j=i;
				canread=true;
				break;
			}
		}
	}
	if(canread){
		data.ele=1;
		data.sta=stus[j].sta;
		data.recno=j;
		data.rp=0;
	}*/
	return canread;
}
//读逆变器、变流器参数
bool ReadRltD::ReadCVTSta(READDEV&data)
{
	bool canread=false;
	int i,j;
	if(data.recno>=0&&data.recno<Ncvt){ //验证带来的号是否可用
		j=data.recno;
		if(cvt[j].NU==(DWORD)data.did) canread=true;
	}
	if(!canread){ //如不能直接读，再查找序号
		for(i=0;i<Ncvt;i++){
			if(cvt[i].NU==(DWORD)data.did)
			{
				j=i;
				canread=true;
				break;
			}
		}
	}
	if(canread){
		data.ele=cvt[j].ele;
		data.sta=cvt[j].sta;
		data.trb=cvt[j].Tsta;
		data.rp=0;
		data.recno=j;
	}
	return canread;
}

//读接地参数
bool ReadRltD::ReadGndSta(READDEV&data)
{
	bool canread=false;
	int i,j;
	if(data.recno>=0&&data.recno<Ngnd){ //验证带来的号是否可用
		j=data.recno;
		if(gnd[j].NU==(DWORD)data.did) canread=true;
	}
	if(!canread){ //如不能直接读，再查找序号
		for(i=0;i<Ngnd;i++){
			if(gnd[i].NU==(DWORD)data.did)
			{
				j=i;
				canread=true;
				break;
			}
		}
	}
	if(canread){
		data.ele=gnd[j].ele;
		data.sta=gnd[j].sta;
		data.trb=0;
		data.rp=0;
		data.recno=j;
	}
	return canread;
}

bool ReadRltD::WriteVlColor(char *vname,BYTE R,BYTE G,BYTE B)
{
	DWORD idi;
	char sql[256];
	MEMTABLE *mtb;
	common_Color *crl,tr;
	int i,j,n,rtn;
	if(!LSI_GetTableID("common","Color",idi)) return false;
	j=LOWORD(idi);
	mtb=(MEMTABLE *)LSI_GetTableAdd(j);
	if(mtb==NULL) return false;
	n=mtb->userec;
	n=n>21 ? 21:n;
	crl=(common_Color*)mtb->data;
	for(i=0;i<n;i++){
		if(strcmp(crl[i].VLName,vname)==0){
			tr=crl[i];
			tr.R=R;
			tr.G=G;
			tr.B=B;
			sprintf(sql,"%s.%s","common","Color");
			rtn=LSI_UpdateARecord(sql,&tr,i);
			if(rtn>0) return true;
		}
	}
	//需要添加
	strcpy(tr.VLName,vname);
	tr.R=R;
	tr.G=G;
	tr.B=B;
	sprintf(sql,"%s.%s","common","Color");
	rtn=LSI_AppendRec(sql,&tr);
	if(rtn>0) return true;
	return false;
}

//读入灵敏度
bool ReadRltD::ReadSen(READSEN&sn)
{
	bool canread=false;
	int i,n;
	sen=(common_Sen *)GetTblAdd("common","Sen",Nsen,&msen);
	n=Nsen;
	n=n>15 ? 15:n;
	for(i=0;i<n;i++){
		sn.se[i].NU=(DWORD)sen[i].NU;
		sn.se[i].type=sen[i].type;
		sn.se[i].senval=sen[i].senval;
	}
	sn.ssum=n;
	return true;
}


////////////////////////////////////////////////////////////////////////////////////////////
//读取低频震荡中定义的线路
int ReadRltD::ReadLowFLine(LowFLPam *lfbuf,int maxbuf)
{
	/*lf=(pmu_lfline *)GetTblAdd("pmu","lfline",Nlf,&mlf);

	int i;
	for(i=0;i<Nlf;i++)
	{
		if(lf[i].DotPs==0)
			continue;
		if(i>maxbuf)
			break;
		lfbuf[i].DotPs=lf[i].DotPs;
		lfbuf[i].Index=lf[i].Index;
		lfbuf[i].LineID=lf[i].LineID;
		lfbuf[i].MaxV=lf[i].MaxV;
		lfbuf[i].Type=lf[i].Type;
		lfbuf[i].UnitNo=lf[i].UnitNo;
	}
	return i;*/
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////
//读入pmu数据服务器地址及服务口号
int ReadRltD::ReadPmuSvrIpPort(PSvrIpPort *pip)
{
	/*DWORD idi;
	MEMTABLE *mtb;
	pmu_pmusvr *svr;
	int i,j,n;
	if(!LSI_GetTableID("pmu","pmusvr",idi)) return 0;
	j=LOWORD(idi);
	mtb=(MEMTABLE *)LSI_GetTableAdd(j);
	if(mtb==NULL) return 0;
	n=mtb->userec;
	n=n>2 ? 2:n;
	if(n<=0) return 0;
	svr=(pmu_pmusvr*)mtb->data;
	for(i=0;i<n;i++){
		pip[i].ip=svr[i].ip;
		pip[i].port=svr[i].port;
	}
	return n;*/
	return 0;
}

//读入n-1节点电压越限严重程度的故障排序
bool ReadRltD::Readn1bus(int &num,N1Data *data,int bufnum)
{
	bool canread=false;
	int i,n;
	n=Nvot;
	n=n>bufnum ? bufnum:n;
	for(i=0;i<n;i++){
		data[i].id=vot[i].NU;
		data[i].val=vot[i].Defl;
		data[i].type=vot[i].type;
	}
	num=n;
	return true;
}

//读入n-1支路潮流越限严重程度的故障排序
bool ReadRltD::Readn1Bra(int &num,N1Data *data,int bufnum)
{
	int i,n;
	n=Nlint;
	n=n>bufnum ? bufnum:n;
	for(i=0;i<n;i++){
		data[i].id=lint[i].NU;
		data[i].val=lint[i].Defl;
		data[i].type=lint[i].type;
	}
	num=n;
	return true;
}


//读入n-1综合故障排序
bool ReadRltD::Readn1All(int &num,N1Data *data,int bufnum)
{
	int i,n;
	n=Nallt;
	n=n>bufnum ? bufnum:n;
	for(i=0;i<n;i++){
		data[i].id=allt[i].NU;
		data[i].val=allt[i].Defl;
		data[i].type=allt[i].type;
	}
	num=n;
	return true;
}

//读入8点负荷预测数据和实时数据
//缓冲区最大为8

bool ReadRltD::ReadnFload8(FLOADDATA *pfl,int &num)
{
	DWORD idi;
	bool canread=false;
	MEMTABLE *mtb;
	common_FLoad *fl;
	int i,j,n;
	return false;
	if(!LSI_GetTableID("common","FLoad",idi)) return false;
	j=LOWORD(idi);
	mtb=(MEMTABLE *)LSI_GetTableAdd(j);
	if(mtb==NULL) return false;
	n=mtb->userec;
	fl=(common_FLoad*)mtb->data;
	n=n>8 ? 8:n;
	for(i=0;i<n;i++)
	{
		pfl[i].FValue=fl[i].FValue;
		pfl[i].RValue=fl[i].RValue;
		pfl[i].hour=fl[i].hour;
	}
	num=n;
	return true;
}


//读入系统告警结果

bool ReadRltD::ReadSAlarm(SYSALARM *alm,int &num)
{
	int i,n;
	n=Nsym;
	n=n>5 ? 5:n;
	for(i=0;i<n;i++)
	{
		alm[i].Alarm=sym[i].Alarm;
		alm[i].num=sym[i].num;
		strcpy(alm[i].picname,sym[i].picname);
		alm[i].picno=sym[i].picno;
	}
	num=n;
	return true;
}

//写入系统告警结果

bool ReadRltD::WriteSAlarm(int j,int alarm)
{
	if(j>4||j<0) return false;
	sym[j].Alarm=alarm;
	if(alarm==0) sym[j].num=0;
	return true;
}


//读入母线名称
void ReadRltD::ReadBusName(char *name,int busnu)
{
	int i;
	for(i=0;i<Nbus;i++)
	{
		if(bus[i].NU==(DWORD)busnu){
			strcpy(name,bus[i].Name);
			return;
		}
	}
}



//0.读入发电机参数
bool ReadRltD::ReadGenData(GenData&gd)
{
	int i;
	for(i=0;i<Ngen;i++){
		if(gen[i].NU==(DWORD)gd.gid){
			strcpy(gd.gname,gen[i].Name);
			gd.bid=0;
			gd.sngKV_LVL=0;
			gd.sngMAX_MW=gen[i].MaxP;
			gd.sngChk_MW=gen[i].Pchk;
			gd.sngGEN_MW=gen[i].P;
			gd.sngGEN_MVAR=gen[i].Q;
			ReadBusName(gd.bname,gd.bid); //读取母线名称
			return true;
		}
	}
	return false;
}
//1.交流线路
//读入线路的参数
bool ReadRltD::ReadLineData(LinData&ld)
{
	int i;
	for(i=0;i<Nlin;i++)
	{
		if(lin[i].NU==(DWORD)ld.lid){
			strcpy(ld.lname,lin[i].Name);
			ld.bus_idf=0;
			ld.bus_idt=0;
			ld.vl=0;
			ld.sngMW=lin[i].Pf;
			ld.sngMVAR=lin[i].Qf;		
			ReadBusName(ld.bfnm,ld.bus_idf); //读取母线名称
			ReadBusName(ld.btnm,ld.bus_idt); //读取母线名称
			ld.Pmax=lin[i].MaxP;
			return true;
		}
	}
	return false;
}
//2.读入直流线路
bool ReadRltD::ReadDCData(DLinData&dd)
{
	int i;
	for(i=0;i<Ndclin;i++){
		if(dclin[i].NU==(DWORD)dd.lid){
			strcpy(dd.lname,dclin[i].Name);
			dd.bus_idf=0;
			dd.bus_idt=0;
			dd.vl=0;
			dd.sngMW=dclin[i].Pf;
			dd.sngMVAR=dclin[i].Qf;		
			ReadBusName(dd.bfnm,dd.bus_idf); //读取母线名称
			ReadBusName(dd.btnm,dd.bus_idt); //读取母线名称
			dd.Pmax=dclin[i].Maxp;
			return true;
		}
	}
	return false;
}
//3.读入母线数据
//读母线的参数
bool ReadRltD::ReadBusAnl(BusData&bd)
{
	int i;
	for(i=0;i<Nbus;i++){
		if(bus[i].NU==(DWORD)bd.bid){
			strcpy(bd.bname,bus[i].Name);
			bd.sngKV_LVL=0;
			bd.sngVOLTAGE_PU=bus[i].V;
			bd.sngVOLTAGE_DEG=bus[i].deg;
			bd.vb=bus[i].Vb;
			bd.Vmax=bus[i].MaxV;
			bd.Vmin=bus[i].MinV;
			bd.Hilimit=bus[i].HiLimit;
			bd.Lolimit=bus[i].LoLimit;
			return true;
		}
	}
	return false;
}
//4.读负荷参数
bool ReadRltD::ReadLoadData(LoadData&ldd)
{
	int i;
	for(i=0;i<Nld;i++){
		if(ld[i].NU==(DWORD)ldd.lid){
			strcpy(ldd.lname,ld[i].Name);
			ldd.vl=0;
			ldd.sngPL=ld[i].P;
			ldd.sngQL=ld[i].Q;
			ldd.intsta=ld[i].sta;
			return true;
		}
	}
	return false;
}
//5.读入变压器数据2绕组
bool ReadRltD::ReadTranData1(TrfData1&td)
{
	int i;
	for(i=0;i<Ntfm1;i++){
		if(tfm1[i].NU==(DWORD)td.tid){
			strcpy(td.tname,tfm1[i].Name);
			td.hlv=0;
			td.tagh=tfm1[i].tap;
			td.maxp=tfm1[i].Pmax;
			td.curp=tfm1[i].P;
			td.curq=tfm1[i].Q;
			td.Tcur=tfm1[i].Tcur;
			td.Tmax=tfm1[i].Tmax;
			return true;
		}
	}
	return false;
}

//6.读入变压器数据3绕组

bool ReadRltD::ReadTranData2(TrfData2&td)
{
	int i;
	for(i=0;i<Ntfm2;i++){
		if(tfm2[i].NU==(DWORD)td.tid){
			strcpy(td.tname,tfm2[i].Name);
			td.hlv=0;
			td.tagh=tfm2[i].TapH;
			td.mlv=0;
			td.tagm=tfm2[i].TapM;
			td.llv=tfm2[i].TapL;
			td.tagl=tfm2[i].TapL;
			td.maxp=tfm2[i].Pmax;
			td.curp=tfm2[i].P;
			td.Tcur=tfm2[i].Tcur;
			td.Tmax=tfm2[i].Tmax;
			td.curq=tfm2[i].Q;
			return true;
		}
	}
	return false;
}

//7.读入电容
bool ReadRltD::ReadShuData(ShuData&sd)
{
	int i;
	for(i=0;i<Nsht;i++){
		if(sht[i].NU==(DWORD)sd.devid){
			strcpy(sd.sname,sht[i].Name);
			sd.busid=0;
			sd.vl=0;
			sd.qst=0;
			sd.c=sht[i].Q;
			sd.sta=sht[i].sta;
			ReadBusName(sd.bname,sd.busid); //读取母线名称
			return true;
		}
	}
	return false;
}


//8.读串联电抗参数
bool ReadRltD::ReadSrdData(SrdData&srd)
{
	int i;
	for(i=0;i<Nsrt;i++){
		if(srt[i].NU==(DWORD)srd.id){
			strcpy(srd.name,srt[i].Name);
			srd.vl=0;
			srd.sngZX=srt[i].Zx;
			srd.sta=srt[i].sta;
			return true;
		}
	}
	return false;
}

//9.读SVC参数
bool ReadRltD::ReadSvcData(SvcData&svd)
{
	int i;
	for(i=0;i<Nsvc;i++){
		if(svc[i].NU==(DWORD)svd.id){
			strcpy(svd.sname,svc[i].Name);
			svd.busid=0;
			svd.vl=0;
			svd.Q=svc[i].Q;
			svd.sta=svc[i].sta;
			ReadBusName(svd.bname,svd.busid); //读取母线名称
			return true;
		}
	}
	return false;
}

bool ReadRltD::YbReadGen(YBDATA&data)
{
	READDEV tmp;
	tmp.did=data.did;
	tmp.recno=data.recno;
	if(!ReadGenAnl(tmp)) return false;
	switch(data.vtype)
	{
	case 0:
		data.curval=tmp.value[0];
		break;
	case 1:
		data.curval=tmp.value[1];
		break;
	default:
		data.curval=0;
	}
	data.vmax=tmp.value[2];
	data.vmin=0;
	data.vmax1=0;
	data.vmin1=0;
	data.vmax2=0;
	data.vmin2=0;
	data.recno=tmp.recno;
	return true;
}

bool ReadRltD::YbReadTfm1(YBDATA&data)
{
	READDEV tmp;
	tmp.did=data.did;
	tmp.recno=data.recno;
	if(!ReadTRan1(tmp)) return false;
	switch(data.vtype)
	{
	case 0:
		data.curval=tmp.value[2];
		break;
	case 1:
		data.curval=tmp.value[6];
		break;
	default:
		data.curval=0;
	}
	data.vmax=tmp.value[1];
	data.vmin=0;
	data.vmax1=0;
	data.vmin1=0;
	data.vmax2=0;
	data.vmin2=0;
	data.recno=tmp.recno;
	return true;
}

bool ReadRltD::YbReadTfm2(YBDATA&data)
{
	READDEV tmp;
	tmp.did=data.did;
	tmp.recno=data.recno;
	if(!ReadTRan2(tmp)) return false;
	switch(data.vtype)
	{
	case 0:
		data.curval=tmp.value[4];
		break;
	case 1:
		data.curval=tmp.value[8];
		break;
	default:
		data.curval=0;
	}
	data.vmax=tmp.value[3];
	data.vmin=0;
	data.vmax1=0;
	data.vmin1=0;
	data.vmax2=0;
	data.vmin2=0;
	data.recno=tmp.recno;
	return true;
}


bool ReadRltD::YbReadLine(YBDATA&data)
{
	READDEV tmp;
	tmp.did=data.did;
	tmp.recno=data.recno;
	if(!ReadLineAnl(tmp)) return false;
	switch(data.vtype)
	{
	case 0:
		data.curval=tmp.value[0];
		break;
	case 1:
		data.curval=tmp.value[1];
		break;
	default:
		data.curval=0;
	}
	data.vmax=tmp.value[4];
	data.vmin=0;
	data.vmax1=0;
	data.vmin1=0;
	data.vmax2=0;
	data.vmin2=0;
	data.recno=tmp.recno;
	return true;
}

bool ReadRltD::YbReadDCLine(YBDATA&data)
{
	READDEV tmp;
	tmp.did=data.did;
	tmp.recno=data.recno;
	if(!ReadDCLineAnl(tmp)) return false;
	switch(data.vtype)
	{
	case 0:
		data.curval=tmp.value[0];
		break;
	case 1:
		data.curval=tmp.value[1];
		break;
	default:
		data.curval=0;
	}
	data.vmax=tmp.value[4];
	data.vmin=0;
	data.vmax1=0;
	data.vmin1=0;
	data.vmax2=0;
	data.vmin2=0;
	data.recno=tmp.recno;
	return true;
}

bool ReadRltD::YbReadLoad(YBDATA&data)
{
	READDEV tmp;
	tmp.did=data.did;
	tmp.recno=data.recno;
	if(!ReadLoadAnl(tmp)) return false;
	switch(data.vtype)
	{
	case 0:
		data.curval=tmp.value[0];
		break;
	case 1:
		data.curval=tmp.value[1];
		break;
	default:
		data.curval=0;
	}
	data.vmax=tmp.value[2];
	data.vmin=tmp.value[3];
	data.vmax1=0;
	data.vmin1=0;
	data.vmax2=0;
	data.vmin2=0;
	data.recno=tmp.recno;
	return true;
}


//读入系统统计值
bool ReadRltD::ReadSystj(PWSYSSUM&ps)
{
	memset(&ps,0,sizeof(PWSYSSUM));
	if(Ngrd<=0) return false;
	ps.GenMax=grd[0].GenMax;					//全网发电总容量
	ps.GenP=grd[0].GenP;						//全网发电有功
	ps.GenQ=grd[0].GenQ;						//全网发电无功
	ps.StopP=grd[0].StopP;						//全网停机总容量
	ps.UpRes=grd[0].UpRes;						//全网上旋转备用
	ps.DownRes=grd[0].DownRes;					//全网下旋转备用
	ps.LoadMax=grd[0].LoadMax;					//全网设计总负荷
	ps.LoadP=grd[0].LoadP;						//全网用电负荷
	return true;
}

//读取预警参数
int ReadRltD::ReadLimit(common_PreLimit *prl,int maxbuf)
{
	DWORD idi;
	MEMTABLE *mtb;
	common_PreLimit *ld;
	int i,j,n;
	if(!LSI_GetTableID("common","PreLimit",idi)) return 0;
	j=LOWORD(idi);
	mtb=(MEMTABLE *)LSI_GetTableAdd(j);
	if(mtb==NULL) return 0;
	n=mtb->userec;
	if(n>maxbuf) n=maxbuf;
	ld=(common_PreLimit*)mtb->data;
	for(i=0;i<n;i++) prl[i]=ld[i];
	return n;
}

//读取预警参数
int ReadRltD::WriteLimit(common_PreLimit *prl,int n)
{
	return LSI_UpdateAll("common.PreLimit", prl,n);
}

//读取短路电流计算结果集
int ReadRltD::ReadShtCC(DLDL *rsc,int maxbuf)
{
	/*int n,m,i,j;
	float maxv;
	double zm;
	DLDL tmp;
	n=Nscc;
	n=n>maxbuf ? maxbuf:n;
	for(i=0;i<n;i++)
	{
		rsc[i].DTime=scc[i].DTime;
		rsc[i].GType=scc[i].GType;
		rsc[i].Imax=scc[i].Imax;
		rsc[i].Isc=scc[i].Isc;
		rsc[i].LineNU=scc[i].LineNU;
		rsc[i].LineType=scc[i].LineType;
		rsc[i].SwtNU=scc[i].SwtNU;
		rsc[i].TrPos=scc[i].TrPos;
		rsc[i].Usc=scc[i].Usc;
		if(rsc[i].Imax!=0)
		{
			rsc[i].over=(float)(rsc[i].Isc/rsc[i].Imax);
		}else rsc[i].over=0;
	}
	//处理数据
	//排序
	for(i=0;i<n-1;i++)
	{
		for(j=i;j<n;j++)
		{
			if(rsc[i].over<rsc[j].over)
			{
				tmp=rsc[i];
				rsc[i]=rsc[j];
				rsc[j]=tmp;
			}
		}
	}
	//获取有效个数,将无效数据剔出
	maxv=0;
	m=0;
	for(i=0;i<n;i++)
	{
		if(rsc[i].over<=0) break;
		if(rsc[i].over>maxv) maxv=rsc[i].over;
		rsc[i].enable=1;
		m++;
	}
	//计算高度
	if(maxv==0) zm=0;
	else zm=200/maxv;
	for(i=0;i<m;i++)
	{
		rsc[i].high=(WORD)(rsc[i].over*zm);
	}
	

	return m;*/
	return 0;
}


bool ReadRltD::Readn1Eft(DWORD n1dev,int n1type,int &num,N1Data *data,int bufnum)
{
	bool canread=false;
	int i;
	
	int index=0;
	data[0].id=n1dev;
	data[0].type=n1type;
	data[0].val=-999;
	data[0].Group=1;
	index++;
	for(i=0;i<Nctg;i++)
	{
		if((ctg[i].CtgNU==0 || (n1dev==ctg[i].CtgNU && n1type==ctg[i].CtgType)) && index<bufnum)
		{
			if(data[0].val==-999) data[0].val=ctg[i].fSecurity;
			data[index].id=ctg[i].EftNU;
			data[index].val=ctg[i].EftVal;
			data[index].type=ctg[i].EftType;
			data[index].Group=0;
			index++;
		}
	}
	num=index;
	return true;
}


int ReadRltD::ReadAllTfmData(SHOW_EQU* pShow,int imax)
{
	int i,index;
	index=0;
	for(i=0;i<Ntfm1;i++)
	{
		if(index>=imax) return 0;
		strcpy(pShow[index].devname,tfm1[i].Name);
		pShow[index].devtype=7;
		pShow[index++].bshow=1;
	}

	for(i=0;i<Ntfm2;i++)
	{
		if(index>=imax) return 0;
		strcpy(pShow[index].devname,tfm2[i].Name);
		pShow[index].devtype=8;
		pShow[index++].bshow=1;
	}
	return index;
}

void ReadRltD::SortPreDm()
{
	if(m_dyndm!=Npdf)
	{
		if(m_pDynDM!=NULL)
			delete []m_pDynDM;
		m_pDynDM=NULL;

		m_pDynDM=new DYNDM[Npdf];
		m_dyndm=Npdf;
	}

	float fMax;
	for(int i=0;i<Npdf;i++)
	{
		m_pDynDM[i].NU=pdf[i].ID;    //序号
		strcpy(m_pDynDM[i].Name,pdf[i].Name);//名称
		fMax=m_pDynDM[i].fMax=pdf[i].Vmax;		//最大值
		m_pDynDM[i].fMin=pdf[i].Pcur;		//最小值
		m_pDynDM[i].fVale=pdf[i].curval;    //值
		if(m_pDynDM[i].fMin<0 && pdf[i].curval<0)
			fMax=m_pDynDM[i].fMin;
		if(fabs(fMax)>0)
			m_pDynDM[i].fRate=fabs(pdf[i].curval/fMax);	//负载率
		m_pDynDM[i].recno=i;		//记录号
	}

	//前十个排序
	DYNDM dyn;
	for(i=0;i<10;i++)
	{
		if(i+1<Npdf)
		{
			for(int j=i+1;j<Npdf;j++)
			{
				if(m_pDynDM[i].fRate<m_pDynDM[j].fRate)
				{
					memcpy(&dyn,&m_pDynDM[i],sizeof(DYNDM));
					memcpy(&m_pDynDM[i],&m_pDynDM[j],sizeof(DYNDM));
					memcpy(&m_pDynDM[j],&dyn,sizeof(DYNDM));
				}
			}
		}
	}
}

bool ReadRltD::GetDynPreDm(int xsmode, N_BAR *pBar)
{
	int index=xsmode-1;
	if(m_dyndm<=index && index<0)
		return false;

	DYNDM* pDynDm=&m_pDynDM[index];
	pBar->dsrc.did=pDynDm->NU;
	strcpy(pBar->dsrc.name,pDynDm->Name);
	pBar->id=pDynDm->recno;

	pBar->max=pDynDm->fMax;
	pBar->min=pDynDm->fMin;
	pBar->rval.curval=pDynDm->fVale;
	return true;
}

