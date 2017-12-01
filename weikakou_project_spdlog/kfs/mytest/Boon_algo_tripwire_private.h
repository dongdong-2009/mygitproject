#ifndef Boon_algo_tripwire_private_h__
#define Boon_algo_tripwire_private_h__


#include "Boon_algo_type.h"
#include "Boon_algo_ivs_config.h"
#include "Boon_algo_ivs_result.h"

#include "Boon_algo_tripwire_param.h"
#include "Boon_algo_tripwire.h"
#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct
	{
		BoonInt32				iFrame;				//帧数
		BoonInt32				iLists;				//轨迹数
		BoonInt32				iMinTime;			//最小报警时间
// 		BoonInt32				iTimeThresh;		//报警时间间隔
// 		BoonInt32				iAlarmTimer;		//报警间隔时间计数器
		BoonInt32				iFrameSkipNum;		/* 跳帧数，取值范围[0,10]，0表示不跳帧 */
		BoonInt32				iFrameSkipTimer;	/* 跳帧计时器，达到跳帧数时执行检测，并将其归零 */
		BoonUint8				*pucExtend;			//扩展参数
		BoonFloat32			f32RatioW;			/* 宽度缩放比例 */
		BoonFloat32			f32RatioH;			/* 高度缩放比例 */
		IVS_TRACK_S			*pstIVSTrack;		//跟踪

		BoonInt32					 iRuleIndex;	/* 规则索引，用于输出 */
		Boon_ALG_TRIP_RULE_PARA_S *pstURPPara;
		BoonInt32					iSeg;
		Boon_HANDLE				hLog;				//日志模块
		BoonInt32					iSizeCheck;
	}IVS_TRIPMTER_S;

#ifdef __cplusplus
}
#endif

#endif // Boon_algo_tripwire_private_h__
