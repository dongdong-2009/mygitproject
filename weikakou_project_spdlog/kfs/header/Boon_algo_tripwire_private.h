#ifndef Boon_algo_tripwire_private_h__
#define Boon_algo_tripwire_private_h__


#include "Boon_algo_type.h"
#include "Boon_algo_ivs_config.h"
#include "Boon_algo_ivs_result.h"
#include "ivs_track.h"
#include "ivs_gmm.h"
#include "Boon_algo_tripwire_param.h"
#include "Boon_algo_tripwire.h"
#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct
	{
		BoonInt32				iFrame;				//֡��
		BoonInt32				iLists;				//�켣��
		BoonInt32				iMinTime;			//��С����ʱ��
// 		BoonInt32				iTimeThresh;		//����ʱ����
// 		BoonInt32				iAlarmTimer;		//�������ʱ�������
		BoonInt32				iFrameSkipNum;		/* ��֡����ȡֵ��Χ[0,10]��0��ʾ����֡ */
		BoonInt32				iFrameSkipTimer;	/* ��֡��ʱ�����ﵽ��֡��ʱִ�м�⣬��������� */
		BoonUint8				*pucExtend;			//��չ����
		BoonFloat32			f32RatioW;			/* ������ű��� */
		BoonFloat32			f32RatioH;			/* �߶����ű��� */
		IVS_TRACK_S			*pstIVSTrack;		//����
#ifndef _Boon_IVS_COM_
		BoonInt32				iWidth;				//ͼ����
		BoonInt32				iHeight;			//ͼ��߶�
		BoonInt32				iImgOriW;			/* ͼ��ԭʼ��� */
		BoonInt32				iImgOriH;			/* ͼ��ԭʼ�߶� */
		IVS_GMM_S			*pstIVSGmm;			//������ģ
		Boon_ALG_IVS_RESULT_SET_S	*pstLastResult;		//�ϴδ�����
		Boon_ALG_IMAGE3_S		*pstImgRes;			/* ��ǰ��Сͼ�� */
#endif
		BoonInt32					 iRuleIndex;	/* ����������������� */
		Boon_ALG_TRIP_RULE_PARA_S *pstURPPara;
		BoonInt32					iSeg;
		Boon_HANDLE				hLog;				//��־ģ��
		BoonInt32					iSizeCheck;
	}IVS_TRIPMTER_S;

#ifdef __cplusplus
}
#endif

#endif // Boon_algo_tripwire_private_h__
