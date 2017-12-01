/********************************************************************
    Copyright (C), 1994-2012, ɽ��������Ϣ�Ƽ����޹�˾	
	Filename: 	 Boon_algo_log_private.h
    Description: �����־��Ϣ
	Author:		 ��ϣΰ
    Created:	 20:12:2012   14:09	
*********************************************************************/

#ifndef  _Boon_ALGO_LOG_PRIVATE_H_
#define  _Boon_ALGO_LOG_PRIVATE_H_

#ifdef __cplusplus
extern "C"      //�������ýӿ�ΪC��ʽ
{
#endif

#include	"Boon_algo_type.h"
#include	"Boon_algo_log.h"

#define BoonALG_LOG_IMGNUM 40
#define  BoonALG_LOG_RECTNUM   50 
typedef struct 
{
	BoonInt32   iSendFlag;
	BoonInt32   iDataLen;					//��־����
	BoonChar	  acDataLog[256];          //��־��Ϣ
}LOG_INFO_S;

typedef struct
{
	BoonInt32				iWidth;                  //ͼƬ��
	BoonInt32				iHeight;                 //ͼƬ��
	BoonInt32				iChannel;                //ͨ����
	BoonInt32				iSendFlag;
	BoonInt32				iRectNum;			//��ʾ���������
	Boon_ALG_RECT_S		iRect[BoonALG_LOG_RECTNUM];			//����Ϣ��
	BoonUint8				*pucImgdata;			 //ͼƬ��ַ
	BoonChar				acImgName[50];			 //ͼƬ����
	BoonFloat32			f32OtherInfo[16];
}LOG_IMG_S;

typedef struct 
{	
	BoonBool					iWindowPrint;    	//�Ƿ�ǰ���ڴ�ӡ
    BoonInt32					iDebugLevel;        //���Եȼ�
	BoonInt32					iImgNum;            //ͼƬ��
	BoonInt32					iDebugNum;           //���Ի���������־������
	BoonInt32                 iDebugMaxNum;
	BoonInt32					iSeg;
	LOG_INFO_S				* pstLogContex;      //��̬������־������
	LOG_IMG_S				astdebugImg[BoonALG_LOG_IMGNUM];       //ͼƬ����
	BoonBool                  HandleFlag;
	BoonBool                  InitFlag;
}LOG_S;

typedef  LOG_S  * LOG_BoonHandle;  //LOG_Handle ��DSPϵͳ�ļ�LOG.h������ͻ
 
/********************************************************************
	���ƣ�	BoonAlgo_LOG_ReadImage

	���ܣ�	���ͼƬ��Ϣ���

	������	Boon_HANDLE           _hModule         �㷨����
			BoonChar				*_pcImgName		 ͼƬ����
			BoonUint8				*_pucImageData   ͼƬ����
			BoonInt32				*_iWidth          ͼƬ���
			BoonInt32				*_iHeigth
			BoonInt32				*_iChannel         ͨ����

	���أ�  ��ȷ    ʣ��ͼƬ��
			����    Boon_ALG_INVALID_PARAM         ��Ч����

	������	�ڲ��Լ������ã�������
*********************************************************************/
Boon_EXPORTS BoonInt32	 BoonAlgo_LOG_ReadImage(Boon_HANDLE _hModule,BoonChar   *_pcImgName,BoonUint8 *_pucImageData,BoonInt32 *_piWidth, BoonInt32 *_piHeight,BoonInt32 *_piChannel,Boon_ALG_RECT_S *_pstRect,BoonInt32	 *_iRectNum,BoonFloat32 *_f32OtherInf);

#ifdef __cplusplus
}
#endif

#endif 
