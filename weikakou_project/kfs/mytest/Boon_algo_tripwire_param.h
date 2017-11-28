#ifndef Boon_algo_tripwire_param_h__
#define Boon_algo_tripwire_param_h__

#include "Boon_algo_type.h"
#include "Boon_algo_ivs_config.h"

#ifdef __cplusplus
extern "C"
{
#endif

	/** 库相关信息 */
	typedef struct
	{
		BoonInt8		*pcVersion;			/**< 版本号 */
		BoonInt32		iAuthorChannel;		/**< 授权分类数 */
		BoonBool		bBetaRealse;		//是否调试版
	} Boon_ALG_TRIP_LIB_INFO_S;
	//输入参数

	/** 检测规则参数 */
	typedef struct
	{
		BoonInt32				iFps;
		BoonInt32				iTypeLimit;		/**< 目标类型限制 */
		//BoonInt32				iTypeHuman;		/**< 目标类别：人(限定类型时使用) */
		//BoonInt32				iTypeVehicle;	/**< 目标类别：车 */
		BoonBool				bDobDir;		/**< 表示该绊线是否为双向绊线(0: 否, 1: 是) */
		BoonInt32				iForDir;		/**< 单绊线禁止方向(0:左，1：右) */
		BoonInt32				iPointNum;		/**< 边界点数目 */
		BoonInt32					iSizeMin;		//最小尺寸(画面宽度的百分比) 取值范围[0, 100]，单位：无，默认值5			
		BoonInt32					iSizeMax;		//最大尺寸(画面宽度的百分比) 取值范围[0, 100]，单位：无，默认值30
		Boon_ALG_POINT_S		astLinePts[Boon_MAX_BoonUNDARY_POINT_NUM];	/**< 边界点集合 */
	} Boon_ALG_TRIP_RULE_PARA_S;

	/**处理结果 */

	/** 检测事件数据结构 */
	typedef struct
	{
		BoonInt32				Id;				/**< 目标标识 */
		BoonInt32				iTraceLen;
		Boon_ALG_POINT_S		astCenter[Boon_ALG_IVS_MAX_TRAJECT_LEN];
		Boon_ALG_EVT_STATUS_E	eStatus;		/**< 事件状态 */
		Boon_ALG_RECT_S		stRect;			/**< 事件位置 */
		BoonInt32				iAbnmlAngle;	/**< 绊线禁止方向角度(unit: degree) */
	} Boon_ALG_TRIP_RESULT_S;

#ifdef __cplusplus
}
#endif

#endif // Boon_algo_tripwire_param_h__
