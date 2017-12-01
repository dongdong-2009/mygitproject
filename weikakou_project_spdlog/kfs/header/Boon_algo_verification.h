/********************************************************************
    Copyright (C), 1994-2012, ɽ��������Ϣ�Ƽ����޹�˾	
    �ļ�����: 	 Boon_algo_verification.h
    �ļ�����:    BOON�㷨��  �ļ�У��ͷ�ļ�
    �ļ�����:    BOON�㷨��
    �޸���ʷ:	 20:12:6:28   �淶��   ��ϣΰ
	            
*********************************************************************/
#ifndef   _BOON_VERIFICATION_H_
#define   _BOON_VERIFICATION_H_

#include	"Boon_algo_type.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum					/////////////////���� model�͹̼�
{
	//	�̼�

	//	����ʶ�����
	CHINESE_MODEL = 20,							//����
	CHARACTER_MODEL = 21,						//�ַ�
	DIGIT_MODEL = 22,							//����
	ALPHA_MODEL = 23,							//
	XUE_MODEL = 24, 							//ѧ
	CONFIDENCE_MODEL = 25,						//���Ŷ�
	GUA_MODEL = 26,								//��
	CARTYEP_MODEL = 27,							//����
	LOGO_MODEL = 28,							//����
	HEADTAIL_MODEL = 29,						//��ͷ��β
	HKAO_MODEL = 30,							//�۰�
	TRAFFICBELT_MODEL = 31,						//��ȫ�����

	//	����������
	VEHICLEDET_KK_MODEL = 40,
	VEHICLEDET_DJ_MODEL = 41,
	VEHICLEDET_IPD_MODEL = 42,

	CARTYEP_MODEL_TAIL = 43,                       //��β����ʶ��


}Boon_ALG_FILE_TYPE_E;

/**********************************************************
	���ƣ�	VERIFICATION_GetFile
	���ܣ�	�Ӵ���ļ�����_pcBoonxBuf ��ȡָ��_eType�����ļ�    \
			1������ļ�У��				\
			2�������ļ�ID�����Ϣ			\
			3�������ڴ棬��ȡ���ݵ��ڴ���	\
			4�����汾�š��ڴ��С��ֵ

	������	BoonInt8* _pcBoonxBuf			//	����ļ�����
			BoonInt32 _i32BoonxLen			//	����ļ���С
			Boon_ALG_FILE_TYPE_E _eFileType	//	FILE type
			BoonInt8* _pcFileVersion		//	�ļ��汾�ţ��ⲿ���� [32]
			BoonInt8** _pcFileBuf			//	��ȡ(��ѹ��)�ļ����ݻ��������ڲ������ڴ�
			BoonInt32* _pi32FileLen		//	�����ڴ�Ĵ�С
			BoonInt32 _i32Seg				//	�����ڴ��

	���أ�	Boon_ALG_OK						�ɹ�
			Boon_ALG_VERIFY_ERROR				У��ʧ�ܷ���
			Boon_ALG_INVALID_PARAM			�ļ���Ϣ����
			Boon_ALG_MALLOC_ERR				�����ڴ����
			Boon_ALG_FAIL						��ѹ����

	������	�������ڴ���Ҫ���ⲿ�ͷ�
**********************************************************/
Boon_EXPORTS BoonInt32 VERIFICATION_GetFile(
		BoonInt8* _pcBoonxBuf, BoonInt32 _i32BoonxLen,
		Boon_ALG_FILE_TYPE_E _eFileType,
		BoonInt8* _pcFileVersion,
		BoonInt8** _pcFileBuf, BoonInt32* _pi32FileLen, BoonInt32 _i32Seg);

#ifdef __cplusplus
}
#endif  

#endif 

