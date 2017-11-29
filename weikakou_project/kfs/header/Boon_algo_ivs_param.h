#ifndef _Boon_ALGO_IVS_PARAM_H_
#define _Boon_ALGO_IVS_PARAM_H_

#include "Boon_algo_type.h"
#include "Boon_algo_ivs_config.h"

#ifdef __cplusplus
extern "C"
{
#endif

	/* ������� */
	typedef struct
	{
		BoonBool				bValid;				//�Ƿ���Ч
		Boon_ALG_IVS_FUNC_E	eType;				/* ����ģʽ */
		BoonUint8				*pucBuf;			/* ָ�� */
	}Boon_ALG_IVS_RULE_PARA_S;

	/** �߼����� */ 
	typedef struct
	{
		BoonBool		bEnable;			/**< �Ƿ����ø߼�����(0:�� 1:��) */
		BoonInt32		iBGUpdataSpeed;		//���������ٶ� ����Χ1-10��Ĭ�� 5
		BoonInt32		iBGUpdatatime;		//���뱳��ʱ�䣬 ��Χ1-20s Ĭ�� 10
		BoonInt32		iBGForbackDiffMin;	//ǰ����С����ȣ�	 ��Χ5-15�� Ĭ�� 6
		BoonInt32		iBGForbackDiffMax;	//ǰ��������ȣ�	 ��Χ15-30��Ĭ�� 16
		BoonInt32		iRealTgtTime;		//Ŀ��ȷ��֡����     ��Χ10-30��Ĭ�� 16
		BoonInt32		iTgtAreaMin;		//Ŀ����С����     ��Χ10-10000    Ĭ�� 10
		BoonInt32		iTgtAreaMax;		//Ŀ���������	 ��Χ100-120000  Ĭ�� 40000
		BoonInt32		iTgtRergRate;		//Ŀ��ϲ������ȣ�	 ��Χ1-10��Ĭ�� 5
	}Boon_ALG_IVS_ADVANCE_PARA_S;

	/* ��չ�����ṹ���� */
	typedef struct
	{
		BoonInt32		iDatLen;					/* ���ݳ��� */
		BoonUint8*	pucBuf;						/* ָ�� */
	} Boon_ALG_IVS_EXTEND_PARA_S;

	/* �����ṹ���� */
	typedef struct
	{
		Boon_ALG_IVS_ADVANCE_PARA_S	stAdvance;	/* �߼����� */
		Boon_ALG_IVS_EXTEND_PARA_S	stExtend;	/* ��չ���� */
	} Boon_ALG_IVS_SUPER_PARA_S;

	/* ����ṹ���� */
	typedef struct
	{
		BoonInt32					iFps;
		Boon_ALG_IVS_RULE_PARA_S	astPara[Boon_ALG_MAX_RULE_NUM];	/* ������� */
		Boon_ALG_IVS_SUPER_PARA_S	stSuperParam;					/* �ֳ����� */
		BoonInt32					iWidth;
		BoonInt32					iHeight;
		Boon_HANDLE				hLog;				//��־ģ��
		BoonInt32					iCheckSize;
	} Boon_ALG_IVS_RULE_S;

#ifdef __cplusplus
}
#endif

#endif
