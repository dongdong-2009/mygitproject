#ifndef _IVS_CCL_H__
#define _IVS_CCL_H__

#include "Boon_algo_type.h"
#include "ivs_track.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define  MAX_TAB_NUM 4096

typedef struct 
{
	BoonInt32 iLabel;
	BoonInt32 iXStart;
	BoonInt32 iXEnd;
	BoonInt32 iY;
} CCL_TAB_S;

BoonBool CCL_AreaRectGet(IVS_TRACK_RECT_S* _pstResult, BoonInt32* _piRectNum, BoonUint8* _pucBiImg, 
					   BoonInt32 _iAreaMin, BoonInt32 _iAreaMax, BoonInt32 _iWidth, BoonInt32 _iHeight);

#ifdef __cplusplus
}
#endif

#endif	/*_IVS_CCL_H__*/
