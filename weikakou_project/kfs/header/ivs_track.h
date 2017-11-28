#ifndef _Boon_IVS_TRACK_H_
#define _Boon_IVS_TRACK_H_

#include "Boon_algo_type.h"
#include "Boon_algo.h"
#include "Boon_algo_ivs_config.h"
#include "ivsconfig.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*单拌线*/
typedef struct
{
	BoonInt32 iMode;			/*拌线位置*/
	BoonInt32 iDirection;		/*拌线方向*/
} IVS_TGTINFO_TRIPWIRE_S;

/*双拌线*/
typedef struct
{
	BoonInt32	aiIdList[Boon_ALG_MAX_RULE_NUM];	/*ID(Boon_ALG_MAX_NUM_RULE_NUM)*/
	BoonInt32	aiFrList[Boon_ALG_MAX_RULE_NUM];	/*帧号(Boon_ALG_MAX_NUM_RULE_NUM)*/
 	BoonInt32	iMode;			/*拌线位置*/
 	BoonInt32	iDirection;		/*拌线方向*/
} IVS_TGTINFO_MTRIPWIRE_S;

/*限高*/
//typedef struct
//{
//	BoonInt32	iTimeOver;		/*超高时间*/
//	BoonInt32	iOverTresh;		/*容错*/
//} IVS_TGTINFO_HIGLIMT_PARA_S;

/*徘徊*/
typedef struct
{
	Boon_ALG_RECT_S stBoundary;	/*外接矩形*/
	BoonInt32		iCount;			/*过中心点的次数*/
	BoonInt32		iInPolygon;		/*在区域内*/
} IVS_TGTINFO_LOITER_S;

///*跌倒*/
//typedef struct
//{
//	BoonInt32 iTimeSlip;		/*倒地时间*/
//	BoonInt32 iOverTresh;		/*容错*/
//} IVS_TGTINFO_SLIPUP_S;

typedef struct
{
	BoonInt32 iMatchNum;					/*匹配数目*/
	BoonInt32 aiMatchId[Boon_MAXMATCHNUM];	/*最多匹配5个*/
	BoonInt32 aiMatchPro[Boon_MAXMATCHNUM];	/*匹配概率*/
	BoonBool  bConBin;					/*是否合并*/
	BoonBool	bSepaRate;					/**/
} IVS_TRACK_MATCHINFO_S;

/*区域块特征*/
typedef struct 
{
	BoonInt32 iGradMore;	/*梯度变大*/
	BoonInt32 iGradLess;	/*梯度变小*/
	BoonInt32	iFgConsis;	/*一致性比例*/
	BoonInt32 iAveGray;	/*平均灰度*/
}IVS_TRACK_FEATURE_S;

/*真假目标*/
typedef struct
{
	BoonInt32	iRealTarFrame;	/*真目标*/
	BoonInt32	iOscFlag;		/*假目标*/		
} IVS_TRACK_TGT_S;

typedef struct 
{ 
	BoonInt32 iSn;			/*编号*/
	BoonInt32 top;
	BoonInt32 bottom;
	BoonInt32 left;
	BoonInt32 right;
	BoonInt32 still;
	BoonInt32 iCenterX;		/*中心点x*/
	BoonInt32 iCenterY;		/*中心点y*/
	BoonInt32 iAreaNum;		/*区域大小*/
	BoonInt32 iDiffRate;		/*变化比例*/
	BoonInt32 iNewSn;			/*初始化为0*/
	IVS_TRACK_MATCHINFO_S stMatchInfo;	/*匹配信息*/
	IVS_TRACK_FEATURE_S stFeature;	/*区域特征*/
} IVS_TRACK_RECT_S;

typedef struct 
{
	BoonBool		bIdle;			/*静止标识*/
	BoonBool		bLastIdle;		/*上帧静止*/
	BoonBool		bNew;			/*新目标标识*/
	BoonBool		bSubmFlg;		/*隐藏，被合并标志*/
	BoonBool		bFatherFlg;		/*父模块*/
	BoonBool		bDeleteFlg;		/*删除标志*/
	BoonInt32		iHisId;			/*历史id，唯一，不停加*/
	BoonInt32		iTraceLen;		/*轨迹个数*/
	BoonInt32		iRbpnt;			/*未知*/
	BoonInt32		iAlarm;			/*报警类型*/
	BoonInt32		iLastAlarm;		/*上帧报警*/		
	BoonInt32		iLifeTime;		/*生命周期*/
	BoonInt32		iStatusMov;		/*运动状态，0-未判定，1-运动，2-静止*/
	BoonInt32		iStillLife;		/*静止状态，用于静物检测、要求开始不运动，不参与碰撞等等*/
	BoonInt32		iLosTime;		/*丢失时间，丢失时间大于一定值则删掉*/
	BoonInt32		iVolecX;		/*x方向速度，速度乘10以提高精度*/
	BoonInt32		iVolecY;		/*y方向速度，速度乘10*/
	BoonInt32		iSubLide;		/*子模块生命周期*/
	BoonInt32		iSubNum;		/*子模块数量*/
	BoonInt32		iSeprateNum;	/*seprate数量*/
	BoonInt32		iMoreAreaNum;	/*变大趋势解决合并的问题，如果连续多帧区域一致变大且超过一定范围，则直接不再合并*/
	BoonInt32		iOSCStatus;		/*0-无，1-遗留，2-丢失*/
	BoonInt32		iStaticNum;		//目标位置未发生变化的时长
	int flag;
	BoonInt32				aiOnTimer[5];							/*add by mhm 定时器*/
	BoonInt32				aiSubId[Boon_MAXSUBMNUM];					/*子模块的id*/
	BoonInt32				aiFthSubLife[Boon_MAXSUBMNUM];			/*父模块中子模块生命周期*/
	Boon_ALG_POINT_S		astCenter[Boon_ALG_IVS_MAX_TRAJECT_LEN];	/*轨迹，中心点*/
	IVS_TRACK_RECT_S	astObjRect[Boon_ALG_IVS_MAX_TRAJECT_LEN];	/*轨迹，外接矩形*/
	IVS_TRACK_RECT_S			stPredict;				/*预测位置*/
	IVS_TRACK_RECT_S			stFatherRect;			/*父模块原始rect信息*/	
	IVS_TRACK_MATCHINFO_S		stMatchInfo;			/*跟踪信息*/
	BoonInt32                     aiCount[Boon_ALG_MAX_RULE_NUM];//时间计数
	BoonInt32						aiOverTresh[Boon_ALG_MAX_RULE_NUM];	/*容错 05.25 add by mhm*/
	//IVS_TGTINFO_SLIPUP_S		stSlipup;				/*add by mhm 跌倒用*/
	IVS_TGTINFO_LOITER_S		stLoiter;				/*add by mhm 徘徊用，轨迹点的外接矩形*/
	IVS_TGTINFO_TRIPWIRE_S		stTripWire;				/*add by mhm 单拌线用*/
	IVS_TGTINFO_MTRIPWIRE_S		stMTripWire;			/*add by mhm 双拌线用*/
	//IVS_TGTINFO_HIGLIMT_PARA_S	stHiglimit;				/*add by mhm 限高用*/
} IVS_TRACK_TRAJECT_S;

typedef struct
{
	BoonInt32			iHisId;
	BoonInt32			iFrame;				/*帧数*/
	BoonInt32			iLists;				/*轨迹数*/
	BoonInt32			iWidth;
	BoonInt32			iHeight;
	IVS_TRACK_TGT_S		 stTrackPara;
	IVS_TRACK_TRAJECT_S* pstTrackRult;	/*结果*/
	BoonInt32   iSeg;
} IVS_TRACK_S;


/**********************************************************
	名称：	IVS_TRACK_Init
	功能：	跟踪模块——初始化
	参数：	IVS_TRACK_S*		_pstModelTrack	跟踪模块
			BoonInt32				_iRealTgtFrame	确定为目标的帧数
			BoonInt32				_OscFlag		物品遗留丢失标识
			BoonInt32				_iImgW			图像宽度
			BoonInt32				_iImgH			图像高度
	返回：	IVS_STATUS_E		Boon_ALG_OK/Boon_ALG_FAIL
**********************************************************/
IVS_STATUS_E IVS_TRACK_Init(IVS_TRACK_S* _pstModelTrack, BoonInt32 _iRealTgtFrame, BoonInt32 _OscFlag, 
							BoonInt32 _iImgW, BoonInt32 _iImgH);

/**********************************************************
	名称：	IVS_TRACK_Process
	功能：	跟踪模块——处理
	参数：	IVS_TRACK_S*		_pstModelTrack	跟踪模块
			Boon_ALG_IMAGE3_S*	_pstImage		输入图像
	  		IVS_TRACK_RECT_S*	_pstFgRect		前景信息
			BoonInt32				_iFgRectNum		前景数目
	返回：	IVS_STATUS_E		Boon_ALG_OK
**********************************************************/
IVS_STATUS_E IVS_TRACK_Process(IVS_TRACK_S* _pstModelTrack, IVS_TRACK_RECT_S* _pstFgRect, BoonInt32 _iFgRectNum);

/**********************************************************
	名称：	IVS_TRACK_Release
	功能：	跟踪模块——释放
	参数：	IVS_TRACK_S*		_pstModelTrack	跟踪模块
	返回：	IVS_STATUS_E		Boon_ALG_OK
**********************************************************/
IVS_STATUS_E IVS_TRACK_Release(IVS_TRACK_S* _pstModelTrack);

/**********************************************************
	名称：	IVS_TRACK_GetSize
	功能：	跟踪模块——计算内存大小
	参数：	
	返回：	BoonInt32				iSize
**********************************************************/
BoonInt32 IVS_TRACK_GetSize();

#ifdef __cplusplus
}
#endif

#endif	/*end _Boon_IVS_TRACK_H_*/
