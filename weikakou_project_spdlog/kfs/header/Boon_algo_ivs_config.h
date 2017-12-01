#ifndef algo_ivs_config_H__
#define algo_ivs_config_H__

#define Boon_ALG_IVS_MAX_TRAJECT_LEN	40

#define Boon_ALG_MAX_TGT_CNT			64//20						/*最大跟踪目标数*/
#define Boon_TRACK_MAX_TGT_CNT		Boon_ALG_MAX_TGT_CNT * 5		/*跟踪过程中最多跟踪数*/

#ifndef IVS_STATUS_E
#define IVS_STATUS_E			BoonInt32			/*代码简洁起见，这里转一次*/
#endif

#define Boon_ALG_MODULE_DATLEN				256		/* 模块数据长度定义 */	
#define Boon_ALG_MAX_RULE_NUM					16		/* 最大规则数目		*/
#define Boon_ALG_MAX_OSC_NUM					4		//物品遗留-begin
#define Boon_ALG_MAX_OBJ_NUMBER				24		//最大检测目标数(目标检测类算法共用)
#define Boon_ALG_MAX_GETUP_BOUNDARY_NUM_S		2		//起身  bhz 20130415
#define Boon_ALG_MAX_REGION_NUM				6		//监控区域最大个数(值岗、法庭离席、法庭不规范着装共用)

/* 算法功能码 */
typedef enum
{
	Boon_ALG_IVS_FUNC_NONE		= 0,		/* 无效 */
	Boon_ALG_IVS_FUNC_HALT		= 1,		//停驶
	Boon_ALG_IVS_FUNC_PERI_I		= 1<<1,		/* 周界检测 2*/
	Boon_ALG_IVS_FUNC_PERI_O		= 1<<2,		/* 周界检测 4*/
	Boon_ALG_IVS_FUNC_TRIPWIRE	= 1<<3,		/* 单绊线检测 8*/
	Boon_ALG_IVS_FUNC_MTRIPWIRE	= 1<<4,		/* 多绊线检测 16*/
	Boon_ALG_IVS_FUNC_LOITER		= 1<<5,		/* 徘徊检测 32*/
	Boon_ALG_IVS_FUNC_ABNMLVEL	= 1<<6,		/* 奔跑检测 64*/
	Boon_ALG_IVS_FUNC_SLIPUP		= 1<<7,		/* 跌倒检测 128*/
	Boon_ALG_IVS_FUNC_GETUP		= 1<<8,		/* 起身检测 256*/
	Boon_ALG_IVS_FUNC_OSC			= 1<<9,		/* 物品遗留检测 512*/
	Boon_ALG_IVS_FUNC_OSR			= 1<<10,	/* 物品丢失检测 1024*/
	Boon_ALG_IVS_FUNC_FIGHT		= 1<<11,	/* 打架检测 2048*/
	Boon_ALG_IVS_FUNC_HIGLIMIT	= 1<<12,	/* 限高检测 4096*/
	Boon_ALG_IVS_FUNC_DUTY		= 1<<13,	/* 值岗检测 8192*/	
	Boon_ALG_IVS_FUNC_VFD			= 1<<14,	/* 人脸检测 16384*/
	Boon_ALG_IVS_FUNC_CDE			= 1<<15,	/* 人群密度 32768*/
	Boon_ALG_IVS_FUNC_TPC			= 1<<16,	/* 倾斜人数统计 65536*/
	Boon_ALG_IVS_FUNC_VPC			= 1<<17,	/* 垂直人数统计 131072*/
	Boon_ALG_IVS_FUNC_AVD			= 1<<18,	/* 视频诊断算法 */
	Boon_ALG_IVS_FUNC_CONVERSE	= 1<<19,	/* IVS逆行 */
	Boon_ALG_IVS_FUNC_STRANDED	= 1<<20,	/* IVS滞留 */
	Boon_ALG_IVS_FUNC_COURTSDC	= 1<<22,	/* 法庭不规范着装检测 */
	Boon_ALG_IVS_FUNC_COURBOONUTY	= 1<<23,	/* 法庭离席检测 */
	Boon_ALG_IVS_FUNC_COURTNPL	= 1<<24,	/* 法庭标牌识别 */
	/*1<<21 已被使用，请保留 add mhm by*/

}Boon_ALG_IVS_FUNC_E;

/** 事件状态 */
typedef enum
{
	Boon_ALG_EVT_STATUS_NOSTA         = 0,	/**< 无状态 */
	Boon_ALG_EVT_STATUS_START         = 1,	/**< 开始 */
	Boon_ALG_EVT_STATUS_END           = 2,	/**< 结束 */
	Boon_ALG_EVT_STATUS_PROCEDURE     = 3		/**< 过程中 */
} Boon_ALG_EVT_STATUS_E;

#endif // _td_algo_ivs_config_H__

