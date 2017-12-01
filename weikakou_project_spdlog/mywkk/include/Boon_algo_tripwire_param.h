#ifndef Boon_algo_tripwire_param_h__
#define Boon_algo_tripwire_param_h__

#include "Boon_algo_type.h"
#include "Boon_algo_ivs_config.h"

#ifdef __cplusplus
extern "C"
{
#endif

	/** �������Ϣ */
	typedef struct
	{
		BoonInt8		*pcVersion;			/**< �汾�� */
		BoonInt32		iAuthorChannel;		/**< ��Ȩ������ */
		BoonBool		bBetaRealse;		//�Ƿ���԰�
	} Boon_ALG_TRIP_LIB_INFO_S;
	//�������

	/** ��������� */
	typedef struct
	{
		BoonInt32				iFps;
		BoonInt32				iTypeLimit;		/**< Ŀ���������� */
		//BoonInt32				iTypeHuman;		/**< Ŀ�������(�޶�����ʱʹ��) */
		//BoonInt32				iTypeVehicle;	/**< Ŀ����𣺳� */
		BoonBool				bDobDir;		/**< ��ʾ�ð����Ƿ�Ϊ˫�����(0: ��, 1: ��) */
		BoonInt32				iForDir;		/**< �����߽�ֹ����(0:��1����) */
		BoonInt32				iPointNum;		/**< �߽����Ŀ */
		BoonInt32					iSizeMin;		//��С�ߴ�(�����ȵİٷֱ�) ȡֵ��Χ[0, 100]����λ���ޣ�Ĭ��ֵ5			
		BoonInt32					iSizeMax;		//���ߴ�(�����ȵİٷֱ�) ȡֵ��Χ[0, 100]����λ���ޣ�Ĭ��ֵ30
		Boon_ALG_POINT_S		astLinePts[Boon_MAX_BoonUNDARY_POINT_NUM];	/**< �߽�㼯�� */
	} Boon_ALG_TRIP_RULE_PARA_S;

	/**������ */

	/** ����¼����ݽṹ */
	typedef struct
	{
		BoonInt32				Id;				/**< Ŀ���ʶ */
		BoonInt32				iTraceLen;
		Boon_ALG_POINT_S		astCenter[Boon_ALG_IVS_MAX_TRAJECT_LEN];
		Boon_ALG_EVT_STATUS_E	eStatus;		/**< �¼�״̬ */
		Boon_ALG_RECT_S		stRect;			/**< �¼�λ�� */
		BoonInt32				iAbnmlAngle;	/**< ���߽�ֹ����Ƕ�(unit: degree) */
	} Boon_ALG_TRIP_RESULT_S;

#ifdef __cplusplus
}
#endif

#endif // Boon_algo_tripwire_param_h__
