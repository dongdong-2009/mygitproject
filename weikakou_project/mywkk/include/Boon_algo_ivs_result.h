#ifndef algo_ivs_result_H__
#define algo_ivs_result_H__

#include "Boon_algo_type.h"
#include "Boon_algo_ivs_config.h"

#ifdef __cplusplus
extern "C"
{
#endif

	/* ������� */
	typedef struct
	{
		BoonInt32				iZone;							/* �������� */
		Boon_ALG_IVS_FUNC_E	eType;							/* ����ģʽ */
		BoonUint8				aucBuf[Boon_ALG_MODULE_DATLEN*2];	/* ָ�� */
	}Boon_ALG_IVS_RESULT_S;

	/* ����ṹ���� */
	typedef struct
	{
		BoonInt32				iEventNum;						/* ������� */
		Boon_ALG_IVS_RESULT_S	astResult[Boon_ALG_MAX_TGT_CNT];	/* ������� */
	} Boon_ALG_IVS_RESULT_SET_S;

	/** �������Ϣ */
	typedef struct
	{
		BoonInt8		*puVersion;			/* �汾�� */
		BoonUint32	iAuthorChannel;		/* ��Ȩ������� */
		BoonBool		bBetaRealse;		/* ���԰汾��ʶ */
	} Boon_ALG_LIB_INFO_S;
	

#ifdef __cplusplus
}
#endif

#endif 
