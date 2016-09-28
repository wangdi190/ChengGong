// ReadRltD.h: interface for the ReadRltD class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_READRLTD_H__73B659A5_9DEC_4CD1_88FF_9C2E8ECAA4B7__INCLUDED_)
#define AFX_READRLTD_H__73B659A5_9DEC_4CD1_88FF_9C2E8ECAA4B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "visualdb.h"
#include "userapi.h"
#include "pwptdef.h"
#include "publicpw.h"
#include "PublicAvcDef.h"

struct DYNDM   //动态断面
{
	DYNDM(){memset(this,0,sizeof(DYNDM));};
	DWORD NU;    //序号
	char Name[45];//名称
	float fMax;		//最大值
	float fMin;		//最小值
	float fVale;    //值
	float fRate;	//负载率
	int recno;		//记录号
};

/////////////////////////////////////////////////////////////
//本类用于读取实时数据取代旧的READDATA.DLL
//取代原因是因为提高读取效率

class ReadRltD  
{
public:
	ReadRltD();
	virtual ~ReadRltD();
	bool InitRltDbf();
	int dbok;
	int curdb;				//当前数据库
	CTime curtm;			//读取数据时的时间
public:
	bool GetDynPreDm(int xsmode,N_BAR* pBar);
	void SortPreDm();
	int  ReadAllTfmData(SHOW_EQU* pShow,int imax);
	bool Readn1Eft(DWORD n1dev,int n1type,int &num,N1Data *data,int bufnum);
	int  ReadShtCC(DLDL *rsc,int maxbuf);
	int  WriteLimit(common_PreLimit *prl,int n);
	int  ReadLimit(common_PreLimit *prl,int maxbuf);
	bool WriteSAlarm(int j,int alarm);
	bool ReadDevViewMsg(void *data,int dtype);
	int  ReadPmuSvrIpPort(PSvrIpPort *pip);
	int  ReadLowFLine(LowFLPam *lfbuf,int maxbuf);
	bool ReadN1Data(int n1type,int &num,N1Data *data,int bufnum);
	bool ReadLF8Data(FLOADDATA *pfl,int &num);
	bool ReadSysAlarm(SYSALARM *alm,int &num);
	void PutFileToAllNode(char *file);
	bool ReadPreAlarm(common_PreDefSF *rpd,int &num,int maxnum);
	bool GetLastRecFile(char *filename);
	bool SendHmiFile(char *filename);
	void UnRegistFileOK(HWND hwnd);
	void RegistFileOK(HWND hwnd);
	bool GetHmiPath(char*path);
	bool ReadPwSys(PWSYSSUM&ps);
	bool ReadSenData(READSEN&sn);
	void SetCurDbf(int dbno);
	bool ReadStaData(READDEV_STA&data);
	bool ReadDevData(READDEV&data);
	bool ReadYbData(YBDATA&data);
	bool WriteVlColor(char *vname,BYTE R,BYTE G,BYTE B);
	bool ReadColorData(DEFCOLOR*cr,int &crsum);
	void GetRltTable2();
	void GetRltTable1();
	bool ReadZoneAnl(READDEV&data);
private:
	bool ReadRelEquAnl(READDEV&data);
	bool ReadUnEquAnl(READDEV&data);
	bool ReadSysAnl(READDEV&data);
	bool ReadDmAnl(READDEV&data);
	bool ReadZoneAnl1(READDEV&data);
	bool ReadZoneAnl0(READDEV&data);
	bool ReadMeter(YBDATA&data);
	float ReadAreaVal(DWORD aid,int field);
	int  CombineRpSta(CTime tm1,CTime tm2,int ele,int sta);
	bool ReadStusSta(READDEV&data);
	bool ReadSystj(PWSYSSUM&ps);
	bool YbReadLoad(YBDATA&data);
	bool YbReadDCLine(YBDATA&data);
	bool YbReadLine(YBDATA&data);
	bool YbReadTfm2(YBDATA&data);
	bool YbReadTfm1(YBDATA&data);
	bool YbReadGen(YBDATA&data);
	void ReadBusName(char *name,int busnu);
	bool ReadMTxtAnl(READDEV&data);
	bool ReadGenData(GenData&gd);
	bool ReadLineData(LinData&ld);
	bool ReadDCData(DLinData&dd);
	bool ReadBusAnl(BusData&bd);
	bool ReadLoadData(LoadData&ldd);
	bool ReadTranData1(TrfData1&td);
	bool ReadTranData2(TrfData2&td);
	bool ReadShuData(ShuData&sd);
	bool ReadSrdData(SrdData&srd);
	bool ReadSvcData(SvcData&svd);
	bool ReadSAlarm(SYSALARM *alm,int &num);
	bool ReadnFload8(FLOADDATA *pfl,int &num);
	bool Readn1All(int &num,N1Data *data,int bufnum);
	bool Readn1Bra(int &num,N1Data *data,int bufnum);
	bool Readn1bus(int &num,N1Data *data,int bufnum);
	bool ReadSen(READSEN&sn);
	bool ReadGndSta(READDEV&data);
	bool ReadCVTSta(READDEV&data);
	bool ReadRelaySta(READDEV&data);
	bool ReadSwitchSta(READDEV&data,CTime &tm);
	bool ReadPTSta(READDEV&data);
	bool ReadPreDMDB(common_PreDefSF *rpd,int &num,int maxnum);
	bool ReadSysGd(YBDATA&data);
	bool ReadGenAnl(READDEV&data);
	bool ReadLineAnl(READDEV&data);
	bool ReadDCLineAnl(READDEV&data);
	bool ReadBusAnl(READDEV&data);
	bool ReadLoadAnl(READDEV&data);
	bool ReadTRan1(READDEV&data);
	bool ReadTRan2(READDEV&data);
	bool ReadShuAnl(READDEV&data);
	bool ReadSreAnl(READDEV&data);
	bool ReadSvcAnl(READDEV&data);

	bool ReadStation(READDEV&data);
	
	void *GetTblAdd(char *dbstr,char *tblstr,int &num,MEMTABLE **mm);
	//定义数据库相关指针
	visualpw_PT			*pt;	int Npt;	
	visualpw_Gen		*gen;	int Ngen;
	visualpw_Switch		*swt;	int Nswt;
	visualpw_Load		*ld;	int Nld;
	visualpw_Shunt		*sht;	int Nsht;
	visualpw_Sreact     *srt;	int Nsrt;
	visualpw_Tfm1       *tfm1;	int Ntfm1;	
	visualpw_Tfm2		*tfm2;	int Ntfm2;
	visualpw_SVC		*svc;	int Nsvc;
	visualpw_Bus		*bus;	int Nbus;
	visualpw_Line		*lin;	int Nlin;
	visualpw_DCLine		*dclin;	int Ndclin;
	visualpw_CVT		*cvt;	int Ncvt;
	visualpw_GND		*gnd;	int Ngnd;
	visualpw_Zone		*zone;	int Nzone;
	visualpw_Station    *sta;	int Nsta;
	visualpw_VotOutage  *vot;	int Nvot;
	visualpw_LineOutage *lint;	int Nlint;
	visualpw_AllOutage  *allt;	int Nallt;
	visualpw_SysGD		*sys;	int Nsys;
	visualpw_SysAlarm	*sym;	int Nsym;
	common_Sen			*sen;	int Nsen;
	common_Color		*clr;	int Nclr;
	common_PreDefSF     *pdf;	int Npdf;
	visualpw_Meter		*mtr;	int Nmtr;
	visualpw_Area		*are;	int Nare;
	visualpw_Grid		*grd;	int Ngrd;
	visualpw_CtgEffect  *ctg;	int Nctg;
	common_UnEquMeas  *uequ;	int Nuequ;
	common_Relation  *rel;	int Nrel;

	//wd新增
	ProcessData_Bus *pro_bus; int Nprobus;
	MEMTABLE *mprobus;

	ProcessData_Line *pro_line; int Nproline;
	MEMTABLE *mproline;

	ProcessData_Load *pro_load; int Nproload;
	MEMTABLE *mproload;

	ProcessData_Gen *pro_gen; int Nprogen;
	MEMTABLE *mprogen;

	ProcessData_Shunt *pro_shunt; int Nproshunt;
	MEMTABLE *mproshunt;

	ProcessData_Sreact *pro_sreact; int Nprosreact;
	MEMTABLE *mprosreact;

	ProcessData_Tfm1 *pro_tfm1; int Nprotfm1;
	MEMTABLE *mprotfm1;

	ProcessData_Tfm2 *pro_tfm2; int Nprotfm2;
	MEMTABLE *mprotfm2;

	ProcessData_Switch *pro_switch; int Nproswitch;
	MEMTABLE *mproswitch;

	ProcessData_Station    *pro_sta;	int Nprosta;
	MEMTABLE *mprosta;


	MEMTABLE	*mpt;	
	MEMTABLE	*mgen;	
	MEMTABLE	*mswt;
	MEMTABLE	*mld;
	MEMTABLE	*msht;
	MEMTABLE    *msrt;
	MEMTABLE    *mtfm1;	
	MEMTABLE	*mtfm2;
	MEMTABLE	*msvc;
	MEMTABLE	*mbus;
	MEMTABLE	*mlin;
	MEMTABLE	*mdclin;
	MEMTABLE	*mcvt;
	MEMTABLE	*mgnd;
	MEMTABLE	*mzone;
	MEMTABLE    *msta;
	MEMTABLE	*mvot;
	MEMTABLE	*mlint;
	MEMTABLE	*mallt;
	MEMTABLE	*mvotf;
	MEMTABLE	*mlintf;
	MEMTABLE	*mallf;
	MEMTABLE	*msys;
	MEMTABLE	*msym;
	MEMTABLE	*mstus;
	MEMTABLE	*mrly;
	MEMTABLE	*mclr;
	MEMTABLE	*msen;
	MEMTABLE	*mpdf;
	MEMTABLE	*mlf;
	MEMTABLE	*mpsv;
	MEMTABLE	*mmtr;
	MEMTABLE	*mare;
	MEMTABLE	*mgrd;
	MEMTABLE	*mctg;
	MEMTABLE	*muequ;
	MEMTABLE	*mrel;
	
	CTimeSpan   tmdx;
	DYNDM* m_pDynDM; int m_dyndm;
};

int CmpDMByRate(DYNDM* pOne,DYNDM* pTwo);
inline int CmpDMByRate(DYNDM* pOne,DYNDM* pTwo)
{
	if(pOne->fRate<pTwo->fRate)
		return FALSE;
	else
		return TRUE;
};
#endif // !defined(AFX_READRLTD_H__73B659A5_9DEC_4CD1_88FF_9C2E8ECAA4B7__INCLUDED_)
