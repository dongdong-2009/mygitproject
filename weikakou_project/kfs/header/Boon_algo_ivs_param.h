#ifndef _Boon_ALGO_IVS_PARAM_H_
#define _Boon_ALGO_IVS_PARAM_H_

#include "Boon_algo_type.h"
#include "Boon_algo_ivs_config.h"

#ifdef __cplusplus
extern "C"
{
#endif

	/* 规则参数 */
	typedef struct
	{
		BoonBool				bValid;				//是否有效
		Boon_ALG_IVS_FUNC_E	eType;				/* 规则模式 */
		BoonUint8				*pucBuf;			/* 指针 */
	}Boon_ALG_IVS_RULE_PARA_S;

	/** 高级参数 */ 
	typedef struct
	{
		BoonBool		bEnable;			/**< 是否启用高级参数(0:否 1:是) */
		BoonInt32		iBGUpdataSpeed;		//背景更新速度 ，范围1-10，默认 5
		BoonInt32		iBGUpdatatime;		//融入背景时间， 范围1-20s 默认 10
		BoonInt32		iBGForbackDiffMin;	//前景最小差异度，	 范围5-15； 默认 6
		BoonInt32		iBGForbackDiffMax;	//前景最大差异度，	 范围15-30；默认 16
		BoonInt32		iRealTgtTime;		//目标确认帧数；     范围10-30；默认 16
		BoonInt32		iTgtAreaMin;		//目标最小区域；     范围10-10000    默认 10
		BoonInt32		iTgtAreaMax;		//目标最大区域；	 范围100-120000  默认 40000
		BoonInt32		iTgtRergRate;		//目标合并灵敏度；	 范围1-10；默认 5
	}Boon_ALG_IVS_ADVANCE_PARA_S;

	/* 扩展参数结构定义 */
	typedef struct
	{
		BoonInt32		iDatLen;					/* 数据长度 */
		BoonUint8*	pucBuf;						/* 指针 */
	} Boon_ALG_IVS_EXTEND_PARA_S;

	/* 场景结构定义 */
	typedef struct
	{
		Boon_ALG_IVS_ADVANCE_PARA_S	stAdvance;	/* 高级参数 */
		Boon_ALG_IVS_EXTEND_PARA_S	stExtend;	/* 扩展参数 */
	} Boon_ALG_IVS_SUPER_PARA_S;

	/* 规则结构定义 */
	typedef struct
	{
		BoonInt32					iFps;
		Boon_ALG_IVS_RULE_PARA_S	astPara[Boon_ALG_MAX_RULE_NUM];	/* 规则参数 */
		Boon_ALG_IVS_SUPER_PARA_S	stSuperParam;					/* 现场参数 */
		BoonInt32					iWidth;
		BoonInt32					iHeight;
		Boon_HANDLE				hLog;				//日志模块
		BoonInt32					iCheckSize;
	} Boon_ALG_IVS_RULE_S;

#ifdef __cplusplus
}
#endif

#endif
