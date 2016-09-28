// editobj.h: interface for the editobj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EDITOBJ_H__E3A664AB_D15F_4509_974E_E106010073E3__INCLUDED_)
#define AFX_EDITOBJ_H__E3A664AB_D15F_4509_974E_E106010073E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Objwin.h"
#include "base0.h"

class editobj : public Objwin  
{
public:
	void EmptyEdit();
	void EditSysParam();
	void EditSelObject();
	editobj();
	virtual ~editobj();
	CRect showRect;
private:
	void EditPie(BASE0 *bs);
	void EditSysPie(BASE0 *bs);
	void Editmttext(BASE0 *bs);
	void EditZone(BASE0 *bs);
	void EditReservoir(BASE0 *bs);
	void EditMeter4(BASE0 *bs);
	void EditMeter3(BASE0 *bs);
	void EditMeter2(BASE0 *bs);
	void EditMeter1(BASE0 *bs);
	void EditPPie(BASE0 *bs);
	void EditCircle(BASE0 *bs);
	void EditRect(BASE0 *bs);
	void EditFlash(BASE0 *bs);
	void EditActObj(BASE0 *bs);
	void EditPath(BASE0 *bs);
	void EditBus(BASE0 *bs);
	void EditConLine(BASE0 *bs);
	void EditArc(BASE0 *bs);
	void EditMb(BASE0 *bs);
	void EditBar(BASE0 *bs);
	void EditEsit(BASE0 *bs);
	void EditFLow(BASE0 *bs);
	void EditSpic(BASE0 *bs);
	void EditSlfCtl(BASE0 *bs);
	void EditPush(BASE0 *bs);
	void EditScrText(BASE0 *bs);
	void EditGml(BASE0 *bs);
	void EditTime(BASE0 *bs);
	void EditDate(BASE0 *bs);
	void EditElegrp(BASE0 *bs);
	void EditAnl(BASE0 *bs);
	void EditImg(BASE0 *bs);
	void EditText(BASE0 *bs);
	void EditArrow(BASE0 *bs);
	void EditGlass(BASE0 *bs);
	void EditSin(BASE0 *bs);
	void EditHSin(BASE0 *bs);
	void EditEgrp(BASE0*bs);
	void EditDbx(BASE0 *bs);
	void EditCoordinate(BASE0 *bs);
	void EditTable(BASE0 *bs);
	bool SetEditParam();
};

#endif // !defined(AFX_EDITOBJ_H__E3A664AB_D15F_4509_974E_E106010073E3__INCLUDED_)
