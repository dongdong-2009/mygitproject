/********************************************************************
    Copyright (C), 1994-2012, 山东博昂信息科技有限公司	
	Filename: 	 Boon_algo_log_private.h
    Description: 输出日志信息
	Author:		 孙希伟
    Created:	 20:12:2012   14:09	
*********************************************************************/

#ifndef  _Boon_ALGO_LOG_PRIVATE_H_
#define  _Boon_ALGO_LOG_PRIVATE_H_

#ifdef __cplusplus
extern "C"      //声明调用接口为C形式
{
#endif

#include	"Boon_algo_type.h"
#include	"Boon_algo_log.h"

#define BoonALG_LOG_IMGNUM 40
#define  BoonALG_LOG_RECTNUM   50 
typedef struct 
{
	BoonInt32   iSendFlag;
	BoonInt32   iDataLen;					//日志长度
	BoonChar	  acDataLog[256];          //日志信息
}LOG_INFO_S;

typedef struct
{
	BoonInt32				iWidth;                  //图片宽
	BoonInt32				iHeight;                 //图片高
	BoonInt32				iChannel;                //通道数
	BoonInt32				iSendFlag;
	BoonInt32				iRectNum;			//显示框的数量；
	Boon_ALG_RECT_S		iRect[BoonALG_LOG_RECTNUM];			//框信息；
	BoonUint8				*pucImgdata;			 //图片地址
	BoonChar				acImgName[50];			 //图片名称
	BoonFloat32			f32OtherInfo[16];
}LOG_IMG_S;

typedef struct 
{	
	BoonBool					iWindowPrint;    	//是否当前窗口打印
    BoonInt32					iDebugLevel;        //调试等级
	BoonInt32					iImgNum;            //图片号
	BoonInt32					iDebugNum;           //调试缓冲区内日志总条数
	BoonInt32                 iDebugMaxNum;
	BoonInt32					iSeg;
	LOG_INFO_S				* pstLogContex;      //动态创建日志数量。
	LOG_IMG_S				astdebugImg[BoonALG_LOG_IMGNUM];       //图片缓存
	BoonBool                  HandleFlag;
	BoonBool                  InitFlag;
}LOG_S;

typedef  LOG_S  * LOG_BoonHandle;  //LOG_Handle 和DSP系统文件LOG.h发生冲突
 
/********************************************************************
	名称：	BoonAlgo_LOG_ReadImage

	功能：	添加图片信息输出

	参数：	Boon_HANDLE           _hModule         算法引擎
			BoonChar				*_pcImgName		 图片名称
			BoonUint8				*_pucImageData   图片数据
			BoonInt32				*_iWidth          图片宽高
			BoonInt32				*_iHeigth
			BoonInt32				*_iChannel         通道数

	返回：  正确    剩余图片数
			错误    Boon_ALG_INVALID_PARAM         无效参数

	其他：	内部自己调试用，不对外
*********************************************************************/
Boon_EXPORTS BoonInt32	 BoonAlgo_LOG_ReadImage(Boon_HANDLE _hModule,BoonChar   *_pcImgName,BoonUint8 *_pucImageData,BoonInt32 *_piWidth, BoonInt32 *_piHeight,BoonInt32 *_piChannel,Boon_ALG_RECT_S *_pstRect,BoonInt32	 *_iRectNum,BoonFloat32 *_f32OtherInf);

#ifdef __cplusplus
}
#endif

#endif 
