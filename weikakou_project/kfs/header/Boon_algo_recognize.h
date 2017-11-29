/********************************************************************
    Copyright (C), 1994-2012, ɽ��������Ϣ�Ƽ����޹�˾	
	Filename: 	 Boon_algo_recognize.h
    Description: ����ʶ��
	Author:		 ��ϣΰ
    Created:	 20:12:2012   14:14	
*********************************************************************/
#ifndef  _BOON_RECOGNIZE_H_
#define  _BOON_RECOGNIZE_H_

	#ifdef __cplusplus
	extern "C" {
	#endif

#include "Boon_algo.h"



		#include "Boon_algo_verification.h"
		#include "Boon_algo_unzipmem.h"
	

//�����ĸ��Ŀ
#define Boon_LPR_MAX_ALPHA_NUM   26
//�������Ŀ���׺��֣�
#define Boon_LPR_MAX_CHINESE_NUM  41

typedef enum 
{
	Boon_INVALID		= 0,
	Boon_DigitAlpha	= 1,	// ���ּ���ĸ
	Boon_Digit		= 2,	// ����
	Boon_Alpha		= 3,	// ��ĸ
	Boon_XUEJING      = 4,    //add by wsj 20120711 for ѧ��
	Boon_HANZI        = 5,    //add by wsj for����
	Boon_GUAPAI         = 6,//add by wsj 20120927for ��
	Boon_HKAO          = 7,//add by wsj 20140506for �۰ĳ���
	// ����ʶ��ĵ�������	  
	Boon_China		= 20,	// ȫ��ͨ��
	Boon_HeiLongJiang	= 21,	// ������
	Boon_ShangHai		= 22,	// �Ϻ�
	Boon_LiaoNing		= 23,	// ����
	Boon_ShanDong		= 24,	// ɽ��
	Boon_GuangDong	= 25,	// �㶫
	Boon_GuangXi		= 26,	// ����
	Boon_TianJin		= 27,	// ���
	Boon_BeiJing		= 28,	// ����
	Boon_JiLin		= 29,	// ����
	Boon_HeNan		= 30,	// ����
	Boon_HuBei		= 31,	// ����
	Boon_HuNan		= 32,	// ����
	Boon_JiangXi		= 33,	// ����
	Boon_GanSu		= 34,	// ����
	Boon_ZheJiang		= 35,	// �㽭
	Boon_JiangSu		= 36,	// ����
	Boon_HuaDong		= 37,	// ����
	Boon_XiNan		= 38,	// ����
	Boon_XiBei		= 39,	// ����
	Boon_DongBei		= 40,	// ����
	Boon_HuaBei		= 41,	// ����
	Boon_HuaNan		= 42,	// ����
	Boon_HuaZhong		= 43	// ����

}Boon_ALG_LPRRecType_E;	


	typedef struct  
	{
	  Boon_HANDLE hgaborHandle;     //������ȡģ��
	  Boon_HANDLE hBinaryHandle;    //��ֵ����ģ��
	  Boon_HANDLE hAnnChineseHandle;       //������ʶ��ģ��
	  Boon_HANDLE hAnnCharacterHandle;//�ַ�ʶ��
	  Boon_HANDLE hAnnBinaryHandle;//��ֵ��
	  Boon_HANDLE hAnnXueHandle;//ѧ��ʶ��
	  Boon_HANDLE hAnnDigit;//����
	  Boon_HANDLE hAnnAlpha;//��ĸ
	  Boon_HANDLE hAnnGuaHandle;//�� 
	  Boon_HANDLE hAnnHKAoHandle;//�۰�
	  Boon_HANDLE hAnnConfidence;//���Ŷ�
	  Boon_HANDLE hAnnCarTypeHandle;//add by wsj for���ͷ���0906
	  Boon_HANDLE hAnnLogoHandle;//add by wsj for�������0906
	  Boon_HANDLE hAnnHeadTailHandle;//add by wsj for��ͷ��β����0906
	  Boon_HANDLE hAnnTrafficBeltHandle;//add by wsj for��ȫ������20140619
	  BoonChar    acModelVersion[50];
	
	}Boon_ALG_Recognize_S;

	typedef Boon_ALG_Recognize_S  * RecognizeHandle;


	/********************************************************************
	���ƣ�	BoonAlgo_REC_Create

	���ܣ�	�����ַ�ʶ���㷨����

	������	BoonInt32  _iSeg		    �ڴ��
			BoonChar   _pcKey         ��Կ

	���أ�	Boon_HANDLE		�����㷨�����������

*********************************************************************/
	Boon_EXPORTS   Boon_HANDLE      BoonAlgo_REC_Create(BoonInt32  _iSeg,BoonChar *_pcKey);

/********************************************************************
	���ƣ�	BoonAlgo_REC_Init

	���ܣ�	�ַ�ʶ���ʼ��

	������	Boon_HANDLE               _hModule	   �㷨����
	        BoonChar                 *_pcModelAdd    �ַ�modelָ��
			BoonInt32                 _iModelLen     model����
	���أ�	Boon_ALG_OK		����ִ�гɹ�

	*********************************************************************/

	Boon_EXPORTS   BoonInt32        BoonAlgo_REC_Init(BoonChar  *_pcModelAdd, BoonInt32  _iModelLen);
	/********************************************************************
	���ƣ�	BoonAlgo_REC_Process

	���ܣ�	�ַ�ʶ������

	������	Boon_HANDLE        _hModule	        �㷨����
			Boon_ALG_IMAGE_S  *_pstGrayLocalImage Сͼ��
			Boon_ALG_LPRRecType_E _eType          ʶ���ַ����� 
			BoonInt32              _iMirror       �ڰ��ƣ���ʱ����
			BoonChar               *_pcRult       ʶ����
			BoonFloat32*            _pf32Weight   Ȩ��
			BoonFloat32 *          _pf32Confine   �����ַ����Ŷ�
	���أ�	Boon_ALG_OK		����ִ�гɹ�

*********************************************************************/
	Boon_EXPORTS   BoonInt32 	    BoonAlgo_REC_Process(Boon_ALG_IMAGE_S *_pstGrayLocalImage,Boon_ALG_LPRRecType_E _eType,BoonInt32 _iMirror, BoonChar *_pcRult, const BoonFloat32* _pf32Weight,BoonFloat32 * _pf32Confine);

/********************************************************************
	���ƣ�	BoonAlgo_REC_ModelVersion

	���ܣ�	�õ��ַ�ʶ��model�汾

	������	Boon_HANDLE               _hModule	   �㷨����
	        BoonUint8               * _pucVersion    model�汾��Ϣ
	���أ�	Boon_ALG_OK		����ִ�гɹ�

*********************************************************************/
	Boon_EXPORTS   BoonInt32        BoonAlgo_REC_ModelVersion(Boon_HANDLE _hModule,BoonUint8  * _pucVersion);

   /********************************************************************
	���ƣ�	BoonAlgo_REC_Release

	���ܣ�	ɾ���ַ�ʶ���㷨����

	������	Boon_HANDLE _hModule		    �㷨����

	���أ�	Boon_ALG_OK		����ִ�гɹ�

	*********************************************************************/
	Boon_EXPORTS   BoonInt32	    BoonAlgo_REC_Release(Boon_HANDLE _hModule);

	#ifdef __cplusplus
	}
	#endif
#endif 
