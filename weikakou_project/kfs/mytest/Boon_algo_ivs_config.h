#ifndef algo_ivs_config_H__
#define algo_ivs_config_H__

#define Boon_ALG_IVS_MAX_TRAJECT_LEN	40

#define Boon_ALG_MAX_TGT_CNT			64//20						/*最大跟踪目标数*/
#define Boon_TRACK_MAX_TGT_CNT		Boon_ALG_MAX_TGT_CNT * 5		/*跟踪过程中最多跟踪数*/

#ifndef IVS_STATUS_E
#define IVS_STATUS_E			BoonInt32			
#endif

#define Boon_ALG_MODULE_DATLEN				256		
#define Boon_ALG_MAX_RULE_NUM					16		
#define Boon_ALG_MAX_OSC_NUM					4		
#define Boon_ALG_MAX_OBJ_NUMBER				24		
#define Boon_ALG_MAX_GETUP_BOUNDARY_NUM_S		2		
#define Boon_ALG_MAX_REGION_NUM				6		

/* 算法功能码 */
typedef enum
{
	Boon_ALG_IVS_FUNC_NONE		= 0,		
	Boon_ALG_IVS_FUNC_HALT		= 1,		
	Boon_ALG_IVS_FUNC_PERI_I		= 1<<1,		
	Boon_ALG_IVS_FUNC_PERI_O		= 1<<2,		
	Boon_ALG_IVS_FUNC_TRIPWIRE	= 1<<3,		
	Boon_ALG_IVS_FUNC_MTRIPWIRE	= 1<<4,		
	Boon_ALG_IVS_FUNC_LOITER		= 1<<5,	
	Boon_ALG_IVS_FUNC_ABNMLVEL	= 1<<6,		
	Boon_ALG_IVS_FUNC_SLIPUP		= 1<<7,		
	Boon_ALG_IVS_FUNC_GETUP		= 1<<8,		
	Boon_ALG_IVS_FUNC_OSC			= 1<<9,		
	Boon_ALG_IVS_FUNC_OSR			= 1<<10,	
	Boon_ALG_IVS_FUNC_FIGHT		= 1<<11,	
	Boon_ALG_IVS_FUNC_HIGLIMIT	= 1<<12,	
	Boon_ALG_IVS_FUNC_DUTY		= 1<<13,
	Boon_ALG_IVS_FUNC_VFD			= 1<<14,	
	Boon_ALG_IVS_FUNC_CDE			= 1<<15,
	Boon_ALG_IVS_FUNC_TPC			= 1<<16,	
	Boon_ALG_IVS_FUNC_VPC			= 1<<17,
	Boon_ALG_IVS_FUNC_AVD			= 1<<18,
	Boon_ALG_IVS_FUNC_CONVERSE	= 1<<19,	
	Boon_ALG_IVS_FUNC_STRANDED	= 1<<20,
	Boon_ALG_IVS_FUNC_COURTSDC	= 1<<22,
	Boon_ALG_IVS_FUNC_COURBOONUTY	= 1<<23,	
	Boon_ALG_IVS_FUNC_COURTNPL	= 1<<24,	


}Boon_ALG_IVS_FUNC_E;

/** 事件状态 */
typedef enum
{
	Boon_ALG_EVT_STATUS_NOSTA         = 0,	/**< 无状态 */
	Boon_ALG_EVT_STATUS_START         = 1,	/**< 开始 */
	Boon_ALG_EVT_STATUS_END           = 2,	/**< 结束 */
	Boon_ALG_EVT_STATUS_PROCEDURE     = 3		/**< 过程中 */
} Boon_ALG_EVT_STATUS_E;

#endif 

