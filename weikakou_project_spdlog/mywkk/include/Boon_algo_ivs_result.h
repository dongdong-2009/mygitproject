#ifndef algo_ivs_result_H__
#define algo_ivs_result_H__

#include "Boon_algo_type.h"
#include "Boon_algo_ivs_config.h"

#ifdef __cplusplus
extern "C"
{
#endif

	/* 规则参数 */
	typedef struct
	{
		BoonInt32				iZone;							/* 规则索引 */
		Boon_ALG_IVS_FUNC_E	eType;							/* 规则模式 */
		BoonUint8				aucBuf[Boon_ALG_MODULE_DATLEN*2];	/* 指针 */
	}Boon_ALG_IVS_RESULT_S;

	/* 规则结构定义 */
	typedef struct
	{
		BoonInt32				iEventNum;						/* 结果个数 */
		Boon_ALG_IVS_RESULT_S	astResult[Boon_ALG_MAX_TGT_CNT];	/* 结果数据 */
	} Boon_ALG_IVS_RESULT_SET_S;

	/** 库相关信息 */
	typedef struct
	{
		BoonInt8		*puVersion;			/* 版本号 */
		BoonUint32	iAuthorChannel;		/* 授权分类个数 */
		BoonBool		bBetaRealse;		/* 调试版本标识 */
	} Boon_ALG_LIB_INFO_S;
	

#ifdef __cplusplus
}
#endif

#endif 
