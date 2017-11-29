/********************************************************************
    Copyright (C), 1994-2012, ɽ��������Ϣ�Ƽ����޹�˾	
	Filename: 	 Boon_algo_gabor_feature.h
    Description: gabor������ȡ
	Author:		 ��ϣΰ
    Created:	 20:12:2012   14:10	
*********************************************************************/

#ifndef  _BOON_gaborFEATURE_H_
#define  _BOON_gaborFEATURE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "Boon_algo.h"



#define S_32_16_8_8_4
#define S_32_16_11_11_5

#ifdef S_32_16_8_8_4
	#define gabor_PHASE 6
	#define GABOR_WIDTH 8
	#define gabor_HEIGHT 8
	#define IMAGE_WIDTH 16
	#define IMAGE_HEIGHT 32
	#define STEP_X       4
	#define STEP_Y		4
	#define SUB_WIN      8

#endif

#ifdef S_32_16_11_11_5

	#define gabor_PHASE_BIG 6
	#define GABOR_WIDTH_BIG 11
	#define gabor_HEIGHT_BIG 11
	#define IMAGE_WIDTH_BIG 16
	#define IMAGE_HEIGHT_BIG 32
	#define STEP_BIG        5
	#define SUB_WIN_BIG     11

#endif
   
#define feature_vec_length  gabor_PHASE * ((IMAGE_WIDTH-SUB_WIN)/STEP_X+1)*((IMAGE_HEIGHT-SUB_WIN)/STEP_Y+1)+gabor_PHASE_BIG * ((IMAGE_WIDTH-SUB_WIN_BIG)/STEP_BIG+1) * ((IMAGE_HEIGHT-SUB_WIN_BIG)/STEP_BIG+1)

#define PROVINCES_MAX_CNT 30
#define  PROVINCES_NEARBY_CNT 5


typedef  struct 
{
	BoonUint8              *pucImg;      //ԭʼͼ��
	BoonInt32              iImgWidth;   //ͼ����
	BoonInt32              iImgHeight;  //ͼ��߶�
	BoonInt32              iImgType;    //��ʾ�����ͼ�����ַ������ֻ���������
}Boon_ALG_gaborFeature_S;

typedef  Boon_ALG_gaborFeature_S*  pstgaborHandle;
/********************************************************************
	���ƣ�	BoonAlgo_gaborFeature_Create

	���ܣ�	����������ȡ�㷨����

	������	BoonInt32  _iSeg		    �ڴ��
			BoonChar   _pcKey         ��Կ

	���أ�	Boon_HANDLE		�����㷨�����������

*********************************************************************/

Boon_EXPORTS Boon_HANDLE BoonAlgo_gaborFeature_Create(BoonInt32  _iSeg, BoonChar  *_pcKey);

/********************************************************************
	���ƣ�	BoonAlgo_gaborFeature_Process

	���ܣ�	����ʶ������

	������	BoonUint8     *_pucImg       //������ȡͼ��
			BoonInt32      _iImgWidth    //ͼ����
			BoonInt32      _iImgHeight   //ͼ��߶�
			BoonInt32      _iImgType     //ͼ�����ͣ�Ŀǰû������
			BoonFloat32   *_pf32ArrayFeature //��������ֵ
	���أ�	Boon_ALG_OK		����ִ�гɹ�

*********************************************************************/
Boon_EXPORTS BoonInt32  BoonAlgo_gaborFeature_Process(Boon_HANDLE _hModule,BoonUint8 * _pucImg,BoonInt32  _iImgWidth, BoonInt32  _iImgHeight,BoonInt32  _iImgType,BoonFloat32 *_pf32ArrayFeature );


/********************************************************************
	���ƣ�	BoonAlgo_gaborFeature_Release

	���ܣ�	ɾ��������ȡ�㷨����

	������	Boon_HANDLE _hModule		    �㷨����

	���أ�	Boon_ALG_OK		����ִ�гɹ�

*********************************************************************/
Boon_EXPORTS BoonInt32  BoonAlgo_gaborFeature_Release(Boon_HANDLE _hModule);
Boon_EXPORTS BoonVoid ImageNormalize(BoonUint8 * _pucImageInput, BoonInt32 _iImgWidth, BoonInt32 _iImgHeight, BoonUint8 *_pucImageOut);

#ifdef __cplusplus
}
#endif



#endif 
