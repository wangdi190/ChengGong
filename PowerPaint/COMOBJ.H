// comobj.h: interface for the comobj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMOBJ_H__5A159CFD_9EC6_4AEA_B869_93948FE28E98__INCLUDED_)
#define AFX_COMOBJ_H__5A159CFD_9EC6_4AEA_B869_93948FE28E98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "workwin.h"
#include "canvas.h"
#include "pagectl.h"
#include "naviwin.h"
#include "mainwin.h"
#include "spiwin.h"
#include "egpwin.h"
#include "layerwin.h"
#include "undoop.h"
#include "tlswin.h"
#include "editobj.h"


//������������Сͼ�꣬λͼ�����ͼԪ��
typedef struct FONTLIST{
  char FaceName[LF_FACESIZE]; 
}FONTLIST;

typedef struct RUNPATH{
  char path[256];
}RUNPATH;


class comobj  
{
public:
	comobj();
	virtual ~comobj();

	BYTE  shadow;				//�Ƿ�ͶӰ
	BYTE  fill;					//�Ƿ����
	BYTE  fillmode;				//���ģʽ
	BYTE  outline;				//�Ƿ��б���
	DWORD outcolor;				//����ɫ
	DWORD bcolor1;				//������ɫ
	DWORD bcolor2;				//������ɫ
	DWORD tcolor;				//�ı���ɫ
	DWORD ncolor;				//ģ����������ɫ
	DWORD acolor;				//ģ�����澯��ɫ
	BYTE  close;				//�Ƿ���
	BYTE  linewd;				//�߿���
	BYTE  mcline;				//�Ƿ�������·
	BYTE  tmode;				//�ı�ģʽ 0=�� 1=��Ӱ 2=���� 3=�� 4=͹
	LOGFONT font;				//��ǰ����
	BYTE  vl;					//�豸��ѹ�ȼ�
	//������ɫ
	DWORD ebcolor;				//���ͼԪ�Ի��򱳾�
	//��������
	FONTLIST fontlist[100];		//��������
	int  fzs;					//��������
	int  fontindex;				//��������
	bool IsInfont(char *name);
	void GetFontName();
	//ͼ������
	int  patternID;				//����ID��,��ʼΪ-1;
	//СͼƬ
	N_SMALLPIC  spic[MAXSPIC];	//СͼƬ ���ΪMAXSPIC
	int spicsum;				//ͼƬ����
	//�ڴ�ͼƬ
	N_MemPic  mpic[100];		//�ڴ��е�ͼƬ
	int mpicsum;				//ͼƬ��,���=100
	//���ͼԪ
	N_ETNAME segp[MAXEGRP];		//SVGת��ʱ������
	N_ELEGRP egp[MAXEGRP];		//���ͼԪ
	int egpsum;					//��ǰ�����ͼԪ��
	int  typeidx[MAXEGRP];		//ѡ�����ͺ󱣴������
	int  selsum;				//ѡ�����͵�ͼԪ��
	//GIF����Ƭ
	N_MGifAml gal[MAXGIF];		//GIF����
	int cursor;					//��ǰ���
	RUNPATH path[2];			//�������·��

	LOGFONT sysfont;			//ϵͳ������
	CMenu   menu1;				//�˵�
	HCURSOR hcur[20];			//���
	int test;					//����״̬
    double curzoom;				//��ǰ�ķŴ���
	//�༭ѡ������
	DWORD vcolor[25];			//ϵͳ��ɫ

	WORD  gwide;				//�������
	BYTE  gstyle;				//����ʽ��
	DWORD gcolor;				//�ϴα༭ʱ������ɫ
	BYTE  gshow;				//�Ƿ���ʾ
	int edobj;					//�༭����״̬
	undoop  unp;				//UNDO����
	//��ע��ʾ--��־
	int nocondev;//δ���ӵ��豸
	int nocdev;  //δ��������豸
	int showsite;//��ʾ����
	//������CJH_PW0����
	UINT  clptype;
public:
	void ResetAEgpRt(int i,CDRect &rtr);
	void ResetEgpRt();
	void DelAMpic(int j);
	void SetVLColor(char *vlname,DWORD color);
	int  GetFontIndex(char *facename);
	void SetToLocalFile(char *infile,char *outfile);
	bool IsFileExist(char *filename);
	int  GetGifAnlRec(char *filename);
	void AddGifAnlUse(int i);
	void DelAGifAnl(int i);
	void OpenGifAnl(int i,char *filename);
	int  GetNoUseGal();
	void AddMpic(char *filename, int id);
	int  GetANoUseMPICID();
	int  GetEGPRecNo(int id);
	int  GetANoUseEGPID();
	void AddAEGP(int num, int index, N_BASATTR &attr, void *obuf);
	bool AddAEmptyEGP(int type);
	void LoadMemPic(FILE *fp);
	void LoadEGP(FILE *fp,WORD ver);
	void LoadSPic(FILE *fp);
	int  GetEleGrpSize(int num,int index);
	int  SaveEGrp(FILE *fp);
	int  SaveMPic(FILE *fp);
	int  colornums(int bits);
	int  SaveSpic(FILE *fp);
	int  GetANoUsePICID();
	void FreeMem();
	void InitParam();
	int  GetPICRecno(int id);
	void SpicAddSubUse(int id,int time);
	int  GetMPICRecno(int id);
	void MpicAddSubUse(int id,int time);
	void FreeEgp(int num, int index);
private:
	void InitPath();
//���е���Ҫ������Ӵ���ָ�붨��
public:
	bool IsSameWhithOther(int index);
	bool SetColor(char *vname,BYTE r,BYTE g,BYTE b);
	void ReadDefColor();
	NaviWin   *nwin;
	workwin   *wwin;
	canvas    *cvs;
	pagectl   *pgcw;
	CMainWin  *mwin;
	egpwin    *egpw;
	spiwin    *spiw;
	layerwin  *layw;
	tlswin    *tlsw;
	editobj   *objw;
};

#endif // !defined(AFX_COMOBJ_H__5A159CFD_9EC6_4AEA_B869_93948FE28E98__INCLUDED_)