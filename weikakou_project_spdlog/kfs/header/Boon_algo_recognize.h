/********************************************************************
    Copyright (C), 1994-2012, 山东博昂信息科技有限公司	
	Filename: 	 Boon_algo_recognize.h
    Description: 车牌识别
	Author:		 孙希伟
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
	

//最大字母数目
#define Boon_LPR_MAX_ALPHA_NUM   26
//最大汉字数目（首汉字）
#define Boon_LPR_MAX_CHINESE_NUM  41

typedef enum 
{
	Boon_INVALID		= 0,
	Boon_DigitAlpha	= 1,	// 数字及字母
	Boon_Digit		= 2,	// 数字
	Boon_Alpha		= 3,	// 字母
	Boon_XUEJING      = 4,    //add by wsj 20120711 for 学警
	Boon_HANZI        = 5,    //add by wsj for汉字
	Boon_GUAPAI         = 6,//add by wsj 20120927for 挂
	Boon_HKAO          = 7,//add by wsj 20140506for 港澳车牌
	// 汉字识别的地区类型	  
	Boon_China		= 20,	// 全国通用
	Boon_HeiLongJiang	= 21,	// 黑龙江
	Boon_ShangHai		= 22,	// 上海
	Boon_LiaoNing		= 23,	// 辽宁
	Boon_ShanDong		= 24,	// 山东
	Boon_GuangDong	= 25,	// 广东
	Boon_GuangXi		= 26,	// 广西
	Boon_TianJin		= 27,	// 天津
	Boon_BeiJing		= 28,	// 北京
	Boon_JiLin		= 29,	// 吉林
	Boon_HeNan		= 30,	// 河南
	Boon_HuBei		= 31,	// 湖北
	Boon_HuNan		= 32,	// 湖南
	Boon_JiangXi		= 33,	// 江西
	Boon_GanSu		= 34,	// 甘肃
	Boon_ZheJiang		= 35,	// 浙江
	Boon_JiangSu		= 36,	// 江苏
	Boon_HuaDong		= 37,	// 华东
	Boon_XiNan		= 38,	// 西南
	Boon_XiBei		= 39,	// 西北
	Boon_DongBei		= 40,	// 东北
	Boon_HuaBei		= 41,	// 华北
	Boon_HuaNan		= 42,	// 华南
	Boon_HuaZhong		= 43	// 华中

}Boon_ALG_LPRRecType_E;	


	typedef struct  
	{
	  Boon_HANDLE hgaborHandle;     //特征提取模块
	  Boon_HANDLE hBinaryHandle;    //二值特征模块
	  Boon_HANDLE hAnnChineseHandle;       //神经网络识别模块
	  Boon_HANDLE hAnnCharacterHandle;//字符识别
	  Boon_HANDLE hAnnBinaryHandle;//二值化
	  Boon_HANDLE hAnnXueHandle;//学警识别
	  Boon_HANDLE hAnnDigit;//数字
	  Boon_HANDLE hAnnAlpha;//字母
	  Boon_HANDLE hAnnGuaHandle;//挂 
	  Boon_HANDLE hAnnHKAoHandle;//港澳
	  Boon_HANDLE hAnnConfidence;//置信度
	  Boon_HANDLE hAnnCarTypeHandle;//add by wsj for车型分类0906
	  Boon_HANDLE hAnnLogoHandle;//add by wsj for车标分类0906
	  Boon_HANDLE hAnnHeadTailHandle;//add by wsj for车头车尾分类0906
	  Boon_HANDLE hAnnTrafficBeltHandle;//add by wsj for安全带分类20140619
	  BoonChar    acModelVersion[50];
	
	}Boon_ALG_Recognize_S;

	typedef Boon_ALG_Recognize_S  * RecognizeHandle;


	/********************************************************************
	名称：	BoonAlgo_REC_Create

	功能：	创建字符识别算法引擎

	参数：	BoonInt32  _iSeg		    内存段
			BoonChar   _pcKey         密钥

	返回：	Boon_HANDLE		返回算法引擎句柄或对象

*********************************************************************/
	Boon_EXPORTS   Boon_HANDLE      BoonAlgo_REC_Create(BoonInt32  _iSeg,BoonChar *_pcKey);

/********************************************************************
	名称：	BoonAlgo_REC_Init

	功能：	字符识别初始化

	参数：	Boon_HANDLE               _hModule	   算法引擎
	        BoonChar                 *_pcModelAdd    字符model指针
			BoonInt32                 _iModelLen     model长度
	返回：	Boon_ALG_OK		操作执行成功

	*********************************************************************/

	Boon_EXPORTS   BoonInt32        BoonAlgo_REC_Init(BoonChar  *_pcModelAdd, BoonInt32  _iModelLen);
	/********************************************************************
	名称：	BoonAlgo_REC_Process

	功能：	字符识别处理函数

	参数：	Boon_HANDLE        _hModule	        算法引擎
			Boon_ALG_IMAGE_S  *_pstGrayLocalImage 小图像
			Boon_ALG_LPRRecType_E _eType          识别字符类型 
			BoonInt32              _iMirror       黑白牌，暂时不用
			BoonChar               *_pcRult       识别结果
			BoonFloat32*            _pf32Weight   权重
			BoonFloat32 *          _pf32Confine   返回字符置信度
	返回：	Boon_ALG_OK		操作执行成功

*********************************************************************/
	Boon_EXPORTS   BoonInt32 	    BoonAlgo_REC_Process(Boon_ALG_IMAGE_S *_pstGrayLocalImage,Boon_ALG_LPRRecType_E _eType,BoonInt32 _iMirror, BoonChar *_pcRult, const BoonFloat32* _pf32Weight,BoonFloat32 * _pf32Confine);

/********************************************************************
	名称：	BoonAlgo_REC_ModelVersion

	功能：	得到字符识别model版本

	参数：	Boon_HANDLE               _hModule	   算法引擎
	        BoonUint8               * _pucVersion    model版本信息
	返回：	Boon_ALG_OK		操作执行成功

*********************************************************************/
	Boon_EXPORTS   BoonInt32        BoonAlgo_REC_ModelVersion(Boon_HANDLE _hModule,BoonUint8  * _pucVersion);

   /********************************************************************
	名称：	BoonAlgo_REC_Release

	功能：	删除字符识别算法引擎

	参数：	Boon_HANDLE _hModule		    算法引擎

	返回：	Boon_ALG_OK		操作执行成功

	*********************************************************************/
	Boon_EXPORTS   BoonInt32	    BoonAlgo_REC_Release(Boon_HANDLE _hModule);

	#ifdef __cplusplus
	}
	#endif
#endif 
