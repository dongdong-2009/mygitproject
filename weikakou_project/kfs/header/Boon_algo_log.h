/********************************************************************
    Copyright (C), 1994-2012, ɽ��������Ϣ�Ƽ����޹�˾	
	Filename: 	 Boon_algo_log.h
    Description: �����־��Ϣ
	Author:		 ��ϣΰ
    Created:	 20:12:2012   14:09	
*********************************************************************/

#ifndef  _Boon_ALGO_LOG_H_
#define  _Boon_ALGO_LOG_H_

#include "Boon_algo_type.h"

#ifdef __cplusplus
extern "C"      //�������ýӿ�ΪC��ʽ
{
#endif

//������Ϣ��OSD��ʾСͼ��ͼ��ṹ��
typedef  struct
{
	BoonInt32				iWidth;
	BoonInt32				iHeight;
	BoonInt32				iFlag;
}Boon_ALG_OSD_IMG_S;

//OSD��ʾ��Ϣ
typedef  struct
{
	//ͼ����Ϣ
	BoonUint8*			pucImgPtr;
	BoonInt32 			iImgNum;
	Boon_ALG_OSD_IMG_S    astImg[10];

	//�ַ���Ϣ
	BoonBool				bShowChar;		//ʹ�ܱ�ʶ
	BoonChar				acCharSet[128];
}Boon_ALG_OSD_S;
	
typedef enum
{
	//LOG_IMAGE =0 ,      //���ͼƬ
    LOG_INVALID ,
	LOG_ERR,			//����ϵͳ����
	LOG_ALERT,			//����, ����
    LOG_INFO,			//��׼��Ϣ��ϵͳ���л�����Ϣ
    LOG_DEBUG,			//����ģʽ
	
    LOG_PIPE,			//	1	����ģ����̣���ϵͳ�쳣ʱ����
    LOG_COM_INVALID,		//	1
    LOG_COM_BASIC,			//	2	��Ӹ���ģ��Ľ����ʱ��Ȼ�����Ϣ
    LOG_COM_DEBUG			//	3	��ϸ�Ա�
}Boon_ALG_LOG_LEVEL_E;

/********************************************************************
	���ƣ�	BoonAlgo_LOG_Create

	���ܣ�	���������㷨����

	������	BoonInt32  _iSeg    �㷨ռ���ڴ��
			BoonChar  *_pcKey   �㷨��Կ(128���ֽ�)

	���أ�  ��ȷ   ����ָ��
		    ����    NULL				

	������	��
*********************************************************************/
Boon_EXPORTS Boon_HANDLE	BoonAlgo_LOG_Create(BoonInt32  _iSeg,BoonChar *_pcKey);


/********************************************************************
	���ƣ�	BoonAlgo_LOG_Init

	���ܣ�	��־�㷨��ʼ��

	������	Boon_HANDLE					_hModule         �㷨����
			Boon_ALG_LOG_LEVEL_E		_eLevel		     ��ʼ����־�ȼ�

	���أ�  �ɹ�    Boon_ALG_OK
			ʧ��    Boon_ALG_FAIL    
					Boon_ALG_INVALID_PARAM

	������	��
*********************************************************************/
Boon_EXPORTS BoonInt32		BoonAlgo_LOG_Init(Boon_HANDLE _hModule,Boon_ALG_LOG_LEVEL_E  _eLevel ,BoonInt32   _iLogMaxNum);



/********************************************************************
	���ƣ�	BoonAlgo_LOG_SetLevel

	���ܣ�	���������־�ȼ�

	������	Boon_HANDLE           _hModule         �㷨����
			TBoon_ALG_LOG_LEVEL_E  _eLevel		 ����ȼ�

	���أ�  �ɹ�   Boon_ALG_OK
			ʧ��   Boon_ALG_NOT_INITED		    δ��ʼ��
				   Boon_ALG_INVALID_PARAM			��Ч����
					

	������	��
*********************************************************************/
Boon_EXPORTS  BoonInt32		BoonAlgo_LOG_SetLevel(Boon_HANDLE _hModule,Boon_ALG_LOG_LEVEL_E  _eLevel);


/********************************************************************
  	���ƣ�	BoonAlgo_Debug_SetLevel

  	���ܣ�	�������������Ϣ�ȼ�

  	������	BoonString _hModule        		 �ⲿ�� ������ڴ� ָ��
  			TBoon_ALG_LOG_LEVEL_E  _eLevel		 ����ȼ� ��Χ
												OG_PIPE,			    //	1	����ģ����̣���ϵͳ�쳣ʱ����
												LOG_COM_INVALID,		//	1
												LOG_COM_BASIC,			//	2	��Ӹ���ģ��Ľ����ʱ��Ȼ�����Ϣ
												LOG_COM_DEBUG

  	���أ�  �ɹ�   Boon_ALG_OK
  		     ʧ��   Boon_ALG_NOT_INITED		    δ��ʼ��
  				Boon_ALG_INVALID_PARAM			��Ч����


  	������	��
  *********************************************************************/
Boon_EXPORTS  BoonInt32		BoonAlgo_Debug_SetLevel(BoonString _hModule,Boon_ALG_LOG_LEVEL_E  _eLevel);

/********************************************************************
	���ƣ�	BoonAlgo_LOG_WindowPrint

	���ܣ�	�ն����ʹ��

	������	Boon_HANDLE           _hModule         �㷨����
			BoonBool				_bSwitch		 ʹ�ܿ���

	���أ�   ��ȷ   Boon_ALG_OK 
			 ����   Boon_ALG_NOT_INITED		 δ��ʼ��
					Boon_ALG_INVALID_PARAM     ��Ч����
					
	������	��
*********************************************************************/
Boon_EXPORTS BoonInt32		BoonAlgo_LOG_WindowPrint(Boon_HANDLE _hModule,BoonBool  _bSwitch);



/********************************************************************
	���ƣ�	BoonAlgo_LOG_AddLog

	���ܣ�	�ն����ʹ��

	������	Boon_HANDLE           _hModule         �㷨����
			Boon_ALG_LOG_LEVEL_E  _eLevel			 ��־�ȼ�
			const BoonChar  * _pcFrm               ���ݸ�ʽ
			...									 ���	
	���أ�  

	������	��
*********************************************************************/

Boon_EXPORTS BoonVoid		BoonAlgo_LOG_AddLog(Boon_HANDLE _hModule,Boon_ALG_LOG_LEVEL_E  _eLevel,const BoonChar  * _pcFrm,...);
/********************************************************************
	���ƣ�	BoonAlgo_LOG_ReadLog

	���ܣ�	��ȡһ����־��

	������	Boon_HANDLE					_hModule         �㷨����
			
	���أ�  ��ȷ     ��־����    
			����	 Boon_ALG_INVALID_PARAM    ��Ч���� 
					 Boon_ALG_NOT_INITED       δ��ʼ�� 
	������	��
*********************************************************************/
Boon_EXPORTS BoonInt32		BoonAlgo_LOG_ReadLog(Boon_HANDLE _hModule,BoonChar *_pcLogBuf);


/********************************************************************
	���ƣ�	BoonAlgo_LOG_Release

	���ܣ�	��־�㷨�ͷź���

	������	Boon_HANDLE                _hModule         �㷨����

	���أ�  ��ȷ    Boon_ALG_OK
			���� 	Boon_ALG_FAIL			   
					 Boon_ALG_NOT_INITED 	 δ��ʼ��	
	������	��
*********************************************************************/
Boon_EXPORTS BoonInt32     BoonAlgo_LOG_Release(Boon_HANDLE _hModule);





/********************************************************************
	���ƣ�	BoonAlgo_LOG_AddImage

	���ܣ�	���ͼƬ��Ϣ���

	������	Boon_HANDLE           _hModule         �㷨����
			BoonChar				*_pcImgName		 ͼƬ����
			BoonUint8				*_pucImageData   ͼƬ����
			BoonInt32				_iWidth          ͼƬ���
			BoonInt32				_iHeigth
			BoonInt32				_iChannel         ͨ����

	���أ�  ��ȷ    Boon_ALG_OK
			����    Boon_ALG_FAIL            ʧ��
	������	�˺���ֻ�����ڲ���Ա�����ã��ӿڿ��Զ��塣
*********************************************************************/
Boon_EXPORTS BoonInt32	 BoonAlgo_LOG_AddImage(Boon_HANDLE _hModule,  BoonChar   *_pcImgName,BoonUint8 *_pucImageData,BoonInt32 _iWidth, BoonInt32 _iHeight,BoonInt32 _iChannel,Boon_ALG_RECT_S *_pstRect,BoonInt32	 _iRectNum,BoonFloat32 *_f32OtherInf);

#ifdef __cplusplus
}
#endif

#endif 
