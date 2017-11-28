/********************************************************************
    Copyright (C), 1994-2012, 山东博昂信息科技有限公司	
	Filename: 	 Boon_algo_gabor_feature.h
    Description: gabor特征提取
	Author:		 孙希伟
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
	BoonUint8              *pucImg;      //原始图像
	BoonInt32              iImgWidth;   //图像宽度
	BoonInt32              iImgHeight;  //图像高度
	BoonInt32              iImgType;    //表示输入的图像是字符、数字还是其他。
}Boon_ALG_gaborFeature_S;

typedef  Boon_ALG_gaborFeature_S*  pstgaborHandle;
/********************************************************************
	名称：	BoonAlgo_gaborFeature_Create

	功能：	创建特征提取算法引擎

	参数：	BoonInt32  _iSeg		    内存段
			BoonChar   _pcKey         密钥

	返回：	Boon_HANDLE		返回算法引擎句柄或对象

*********************************************************************/

Boon_EXPORTS Boon_HANDLE BoonAlgo_gaborFeature_Create(BoonInt32  _iSeg, BoonChar  *_pcKey);

/********************************************************************
	名称：	BoonAlgo_gaborFeature_Process

	功能：	跟踪识别处理函数

	参数：	BoonUint8     *_pucImg       //特征提取图像
			BoonInt32      _iImgWidth    //图像宽度
			BoonInt32      _iImgHeight   //图像高度
			BoonInt32      _iImgType     //图像类型，目前没有作用
			BoonFloat32   *_pf32ArrayFeature //返回特征值
	返回：	Boon_ALG_OK		操作执行成功

*********************************************************************/
Boon_EXPORTS BoonInt32  BoonAlgo_gaborFeature_Process(Boon_HANDLE _hModule,BoonUint8 * _pucImg,BoonInt32  _iImgWidth, BoonInt32  _iImgHeight,BoonInt32  _iImgType,BoonFloat32 *_pf32ArrayFeature );


/********************************************************************
	名称：	BoonAlgo_gaborFeature_Release

	功能：	删除特征提取算法引擎

	参数：	Boon_HANDLE _hModule		    算法引擎

	返回：	Boon_ALG_OK		操作执行成功

*********************************************************************/
Boon_EXPORTS BoonInt32  BoonAlgo_gaborFeature_Release(Boon_HANDLE _hModule);
Boon_EXPORTS BoonVoid ImageNormalize(BoonUint8 * _pucImageInput, BoonInt32 _iImgWidth, BoonInt32 _iImgHeight, BoonUint8 *_pucImageOut);

#ifdef __cplusplus
}
#endif



#endif 
