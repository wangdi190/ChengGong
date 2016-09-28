// PySel.h: interface for the PySel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PYSEL_H__488F2BE0_3452_4546_B7DB_56014E69A112__INCLUDED_)
#define AFX_PYSEL_H__488F2BE0_3452_4546_B7DB_56014E69A112__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



//ºº×Ö½á¹¹
typedef struct MYHZ
{
	int type;		//0=×Ö·û£¬1=ºº×Ö
	int hz;			//×Ö·û
}MYHZ;
class PySel  
{
public:
	PySel();
	virtual ~PySel();
	bool IsThisPy(char *inchar,char *str);
private:
	int GetWORD(MYHZ *zf,char *str);
	int GetIndex(int v);


};

#endif // !defined(AFX_PYSEL_H__488F2BE0_3452_4546_B7DB_56014E69A112__INCLUDED_)
