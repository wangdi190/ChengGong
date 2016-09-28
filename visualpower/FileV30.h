// FileV30.h: interface for the FileV30 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEV30_H__5F41B47D_B56B_498C_ADDF_BD7676C5F57E__INCLUDED_)
#define AFX_FILEV30_H__5F41B47D_B56B_498C_ADDF_BD7676C5F57E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "defv30.h"
#include "gdata.h"

class FileV30  
{
public:
	int GetBsFromV5(void *lp1, N_BASATTR &btr, void *lp2);
	int GetBsFromV4(void *lp1, N_BASATTR &btr, void *lp2);
	int GetBsFromV3(void *lp1, N_BASATTR &btr, void *lp2);
	int GetBsFromV2(void  *lp1,N_BASATTR&btr,void *lp2);
	int GetV3Size(DObj&bs,int mode=0);
	gdata *dbm;
	FileV30();
	virtual ~FileV30();
private:
	int V5SysPieToBs(void *lp, void *lp2);
	int V5MttextToBs(void *lp, void *lp2);
	int V5ZoneToBs(void *lp, void *lp2);
	int V5PctToBs(void *lp, void *lp2);
	int V5FlashToBs(void *lp, void *lp2);
	int V5ActToBs(void *lp, void *lp2);
	int V5BusToBs(void *lp, void *lp2);
	int V5ConlToBs(void *lp, void *lp2);
	int V5FlowToBs(void *lp, void *lp2);
	int V5SelfToBs(void *lp, void *lp2);
	int V5PushToBs(void *lp, void *lp2);
	int V5ScrtxtToBs(void *lp, void *lp2);
	int V5GifToBs(void *lp, void *lp2);
	int V5DateToBs(void *lp, void *lp2);
	int V5PieToBs(void *lp, void *lp2);
	int V5BarToBs(void *lp, void *lp2);
	int V5ElegToBs(void *lp, void *lp2);
	int V5YBToBs(void *lp, void *lp2);
	int V5Meter1ToBs(void *lp, void *lp2);
	int V5Meter2ToBs(void *lp, void *lp2);
	int V5Meter3ToBs(void *lp, void *lp2);
	int V5Meter4ToBs(void *lp, void *lp2);
	int V5ReservoirToBs(void *lp, void *lp2);
	int V5AnlToBs(void *lp, void *lp2);
	int V5PicToBs(void *lp, void *lp2);
	int V5PathToBs(void *lp, void *lp2);
	int V5SpicToBs(void *lp, void *lp2);
	int V5TableToBs(void *lp, void *lp2);
	int V5CoordToBs(void *lp, void *lp2);
	int V5MBoardToBs(void *lp, void *lp2);
	int V5SiteToBs(void *lp, void *lp2);
	int V5TextToBs(void *lp, void *lp2);
	int V5GlassToBs(void *lp, void *lp2);
	int V5ArrowToBs(void *lp, void *lp2);
	int V5ArcToBs(void *lp, void *lp2);
	int V5SinToBs(void *lp, void *lp2);
	int V5HsinToBs(void *lp, void *lp2);
	int V5RectToBs(void *lp, void *lp2);
	int V5DbxToBs(void *lp,void *lp2);

	int V4SysPieToBs(void *lp, void *lp2);
	int V4AnlToBs(void *lp, void *lp2);
	int V4ReservoirToBs(void *lp, void *lp2);
	int V4ElegToBs(void *lp, void *lp2);
	int V4YBToBs(void *lp, void *lp2);
	int V4GifToBs(void *lp, void *lp2);
	int V4PushToBs(void *lp, void *lp2);
	int V4FlowToBs(void *lp, void *lp2);
	int V4BusToBs(void *lp, void *lp2);
	int V4ActToBs(void *lp, void *lp2);
	int V4ZoneToBs(void *lp, void *lp2);
	int V4WtrToBs(void *lp, void *lp2);
	int V4BarToBs(void *lp, void *lp2);
	int V4PieToBs(void *lp, void *lp2);
	int V4DbxToBs(void *lp, void *lp2);
	int V4RectToBs(void *lp, void *lp2);
	int V4HsinToBs(void *lp, void *lp2);
	int V4SinToBs(void *lp, void *lp2);
	int V4ArcToBs(void *lp, void *lp2);
	int V4ArrowToBs(void *lp, void *lp2);
	int V4GlassToBs(void *lp, void *lp2);
	int V4TextToBs(void *lp, void *lp2);
	int V4SiteToBs(void *lp, void *lp2);
	int V4MBoardToBs(void *lp, void *lp2);
	int V4CoordToBs(void *lp, void *lp2);
	int V4TableToBs(void *lp, void *lp2);
	int V4SpicToBs(void *lp, void *lp2);
	int V4PathToBs(void *lp, void *lp2);
	int V4PicToBs(void *lp, void *lp2);
	int V4Meter1ToBs(void *lp, void *lp2);
	int V4Meter2ToBs(void *lp, void *lp2);
	int V4Meter3ToBs(void *lp, void *lp2);
	int V4Meter4ToBs(void *lp, void *lp2);
	int V4DateToBs(void *lp, void *lp2);
	int V4ScrtxtToBs(void *lp, void *lp2);
	int V4SelfToBs(void *lp, void *lp2);
	int V4ConlToBs(void *lp, void *lp2);
	int V4FlashToBs(void *lp, void *lp2);

	int V3MttextToBs(void *lp, void *lp2);
	int V3ZoneToBs(void *lp, void *lp2);
	int V3Meter1ToBs(void *lp, void *lp2);
	int V3Meter2ToBs(void *lp, void *lp2);
	int V3Meter3ToBs(void *lp, void *lp2);
	int V3Meter4ToBs(void *lp, void *lp2);
	int V3PctToBs(void *lp, void *lp2);
	int V3FlashToBs(void *lp, void *lp2);
	int V3ActToBs(void *lp, void *lp2);
	int V3BusToBs(void *lp, void *lp2);
	int V3ConlToBs(void *lp, void *lp2);
	int V3FlowToBs(void *lp, void *lp2);
	int V3SelfToBs(void *lp, void *lp2);
	int V3PushToBs(void *lp, void *lp2);
	int V3ScrtxtToBs(void *lp, void *lp2);
	int V3GifToBs(void *lp, void *lp2);
	int V3DateToBs(void *lp, void *lp2);
	int V3PieToBs(void *lp, void *lp2);
	int V3BarToBs(void *lp, void *lp2);
	int V3ElegToBs(void *lp, void *lp2);
	int V3YBToBs(void *lp, void *lp2);
	int V3AnlToBs(void *lp, void *lp2);
	int V3ReservoirToBs(void *lp, void *lp2);
	int V3PicToBs(void *lp, void *lp2);
	int V3PathToBs(void *lp, void *lp2);
	int V3SpicToBs(void *lp, void *lp2);
	int V3TableToBs(void *lp, void *lp2);
	int V3CoordToBs(void *lp, void *lp2);
	int V3MBoardToBs(void *lp, void *lp2);
	int V3SiteToBs(void *lp, void *lp2);
	int V3TextToBs(void *lp, void *lp2);
	int V3GlassToBs(void *lp, void *lp2);
	int V3ArrowToBs(void *lp, void *lp2);
	int V3ArcToBs(void *lp, void *lp2);
	int V3SinToBs(void *lp, void *lp2);
	int V3HsinToBs(void *lp, void *lp2);
	int V3RectToBs(void *lp, void *lp2);
	int V3DbxToBs(void *lp,void *lp2);

	int V2PctToBs(void *lp, void *lp2);
	int V2FlashToBs(void *lp, void *lp2);
	int V2ActToBs(void *lp, void *lp2);
	int V2BusToBs(void *lp, void *lp2);
	int V2ConlToBs(void *lp, void *lp2);
	int V2FlowToBs(void *lp, void *lp2);
	int V2SelfToBs(void *lp, void *lp2);
	int V2PushToBs(void *lp, void *lp2);
	int V2ScrtxtToBs(void *lp, void *lp2);
	int V2GifToBs(void *lp, void *lp2);
	int V2DateToBs(void *lp, void *lp2);
	int V2PieToBs(void *lp, void *lp2);
	int V2BarToBs(void *lp, void *lp2);
	int V2ElegToBs(void *lp, void *lp2);
	int V2AnlToBs(void *lp, void *lp2);
	int V2PicToBs(void *lp, void *lp2);
	int V2PathToBs(void *lp, void *lp2);
	int V2SpicToBs(void *lp, void *lp2);
	int V2TableToBs(void *lp, void *lp2);
	int V2CoordToBs(void *lp, void *lp2);
	int V2MBoardToBs(void *lp, void *lp2);
	int V2SiteToBs(void *lp, void *lp2);
	int V2TextToBs(void *lp, void *lp2);
	int V2GlassToBs(void *lp, void *lp2);
	int V2ArrowToBs(void *lp, void *lp2);
	int V2ArcToBs(void *lp, void *lp2);
	int V2SinToBs(void *lp, void *lp2);
	int V2HsinToBs(void *lp, void *lp2);
	int V2RectToBs(void *lp, void *lp2);
	int V2DbxToBs(void *lp,void *lp2);
	void AllPtTo4Pt(DPOINT *in,int ptsum,DPOINT *out);

	void  GetptFromDRECT(DRECT&rt,DPOINT *pt);
};

#endif // !defined(AFX_FILEV30_H__5F41B47D_B56B_498C_ADDF_BD7676C5F57E__INCLUDED_)
