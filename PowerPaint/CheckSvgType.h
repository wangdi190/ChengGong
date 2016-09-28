// CheckSvgType.h: interface for the CCheckSvgType class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHECKSVGTYPE_H__42D34A72_5E16_403E_94D3_25B0A14E3656__INCLUDED_)
#define AFX_CHECKSVGTYPE_H__42D34A72_5E16_403E_94D3_25B0A14E3656__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCheckSvgType  
{
public:
	int GetSvgType(char *svgfilename);
	CCheckSvgType();
	virtual ~CCheckSvgType();
	char *lbuf;			//ÐÐ»º³åÇø
	int lbmax;
	FILE *fp;
	int type;
private:
	int ReadALine();
	void CheckType();
};

#endif // !defined(AFX_CHECKSVGTYPE_H__42D34A72_5E16_403E_94D3_25B0A14E3656__INCLUDED_)
