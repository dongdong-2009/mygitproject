/********************************************************************
    Copyright (C), 1994-2012, 山东博昂信息科技有限公司	
	Filename: 	 Boon_algo_log.h
    Description: 输出日志信息
	Author:		 孙希伟
    Created:	 20:12:2012   14:09	
*********************************************************************/

#ifndef  _Boon_ALGO_LOG_H_
#define  _Boon_ALGO_LOG_H_

#include "Boon_algo_type.h"

#ifdef __cplusplus
extern "C"      //声明调用接口为C形式
{
#endif

//调试信息，OSD显示小图的图像结构体
typedef  struct
{
	BoonInt32				iWidth;
	BoonInt32				iHeight;
	BoonInt32				iFlag;
}Boon_ALG_OSD_IMG_S;

//OSD显示信息
typedef  struct
{
	//图像信息
	BoonUint8*			pucImgPtr;
	BoonInt32 			iImgNum;
	Boon_ALG_OSD_IMG_S    astImg[10];

	//字符信息
	BoonBool				bShowChar;		//使能标识
	BoonChar				acCharSet[128];
}Boon_ALG_OSD_S;
	
typedef enum
{
	//LOG_IMAGE =0 ,      //输出图片
    LOG_INVALID ,
	LOG_ERR,			//错误，系统错误
	LOG_ALERT,			//警惕, 警报
    LOG_INFO,			//标准信息，系统运行基本信息
    LOG_DEBUG,			//调试模式
	
    LOG_PIPE,			//	1	各个模块过程，在系统异常时保存
    LOG_COM_INVALID,		//	1
    LOG_COM_BASIC,			//	2	添加各个模块的结果和时间等基本信息
    LOG_COM_DEBUG			//	3	详细对比
}Boon_ALG_LOG_LEVEL_E;

/********************************************************************
	名称：	BoonAlgo_LOG_Create

	功能：	创建跟踪算法引擎

	参数：	BoonInt32  _iSeg    算法占用内存段
			BoonChar  *_pcKey   算法密钥(128个字节)

	返回：  正确   引擎指针
		    错误    NULL				

	其他：	无
*********************************************************************/
Boon_EXPORTS Boon_HANDLE	BoonAlgo_LOG_Create(BoonInt32  _iSeg,BoonChar *_pcKey);


/********************************************************************
	名称：	BoonAlgo_LOG_Init

	功能：	日志算法初始化

	参数：	Boon_HANDLE					_hModule         算法引擎
			Boon_ALG_LOG_LEVEL_E		_eLevel		     初始化日志等级

	返回：  成功    Boon_ALG_OK
			失败    Boon_ALG_FAIL    
					Boon_ALG_INVALID_PARAM

	其他：	无
*********************************************************************/
Boon_EXPORTS BoonInt32		BoonAlgo_LOG_Init(Boon_HANDLE _hModule,Boon_ALG_LOG_LEVEL_E  _eLevel ,BoonInt32   _iLogMaxNum);



/********************************************************************
	名称：	BoonAlgo_LOG_SetLevel

	功能：	设置输出日志等级

	参数：	Boon_HANDLE           _hModule         算法引擎
			TBoon_ALG_LOG_LEVEL_E  _eLevel		 输出等级

	返回：  成功   Boon_ALG_OK
			失败   Boon_ALG_NOT_INITED		    未初始化
				   Boon_ALG_INVALID_PARAM			无效参数
					

	其他：	无
*********************************************************************/
Boon_EXPORTS  BoonInt32		BoonAlgo_LOG_SetLevel(Boon_HANDLE _hModule,Boon_ALG_LOG_LEVEL_E  _eLevel);


/********************************************************************
  	名称：	BoonAlgo_Debug_SetLevel

  	功能：	设置输出调试信息等级

  	参数：	BoonString _hModule        		 外部传 入调试内存 指针
  			TBoon_ALG_LOG_LEVEL_E  _eLevel		 输出等级 范围
												OG_PIPE,			    //	1	各个模块过程，在系统异常时保存
												LOG_COM_INVALID,		//	1
												LOG_COM_BASIC,			//	2	添加各个模块的结果和时间等基本信息
												LOG_COM_DEBUG

  	返回：  成功   Boon_ALG_OK
  		     失败   Boon_ALG_NOT_INITED		    未初始化
  				Boon_ALG_INVALID_PARAM			无效参数


  	其他：	无
  *********************************************************************/
Boon_EXPORTS  BoonInt32		BoonAlgo_Debug_SetLevel(BoonString _hModule,Boon_ALG_LOG_LEVEL_E  _eLevel);

/********************************************************************
	名称：	BoonAlgo_LOG_WindowPrint

	功能：	终端输出使能

	参数：	Boon_HANDLE           _hModule         算法引擎
			BoonBool				_bSwitch		 使能开关

	返回：   正确   Boon_ALG_OK 
			 错误   Boon_ALG_NOT_INITED		 未初始化
					Boon_ALG_INVALID_PARAM     无效参数
					
	其他：	无
*********************************************************************/
Boon_EXPORTS BoonInt32		BoonAlgo_LOG_WindowPrint(Boon_HANDLE _hModule,BoonBool  _bSwitch);



/********************************************************************
	名称：	BoonAlgo_LOG_AddLog

	功能：	终端输出使能

	参数：	Boon_HANDLE           _hModule         算法引擎
			Boon_ALG_LOG_LEVEL_E  _eLevel			 日志等级
			const BoonChar  * _pcFrm               数据格式
			...									 变参	
	返回：  

	其他：	无
*********************************************************************/

Boon_EXPORTS BoonVoid		BoonAlgo_LOG_AddLog(Boon_HANDLE _hModule,Boon_ALG_LOG_LEVEL_E  _eLevel,const BoonChar  * _pcFrm,...);
/********************************************************************
	名称：	BoonAlgo_LOG_ReadLog

	功能：	读取一条日志。

	参数：	Boon_HANDLE					_hModule         算法引擎
			
	返回：  正确     日志条数    
			错误	 Boon_ALG_INVALID_PARAM    无效参数 
					 Boon_ALG_NOT_INITED       未初始化 
	其他：	无
*********************************************************************/
Boon_EXPORTS BoonInt32		BoonAlgo_LOG_ReadLog(Boon_HANDLE _hModule,BoonChar *_pcLogBuf);


/********************************************************************
	名称：	BoonAlgo_LOG_Release

	功能：	日志算法释放函数

	参数：	Boon_HANDLE                _hModule         算法引擎

	返回：  正确    Boon_ALG_OK
			错误 	Boon_ALG_FAIL			   
					 Boon_ALG_NOT_INITED 	 未初始化	
	其他：	无
*********************************************************************/
Boon_EXPORTS BoonInt32     BoonAlgo_LOG_Release(Boon_HANDLE _hModule);





/********************************************************************
	名称：	BoonAlgo_LOG_AddImage

	功能：	添加图片信息输出

	参数：	Boon_HANDLE           _hModule         算法引擎
			BoonChar				*_pcImgName		 图片名称
			BoonUint8				*_pucImageData   图片数据
			BoonInt32				_iWidth          图片宽高
			BoonInt32				_iHeigth
			BoonInt32				_iChannel         通道数

	返回：  正确    Boon_ALG_OK
			错误    Boon_ALG_FAIL            失败
	其他：	此函数只用于内部人员测试用，接口可自定义。
*********************************************************************/
Boon_EXPORTS BoonInt32	 BoonAlgo_LOG_AddImage(Boon_HANDLE _hModule,  BoonChar   *_pcImgName,BoonUint8 *_pucImageData,BoonInt32 _iWidth, BoonInt32 _iHeight,BoonInt32 _iChannel,Boon_ALG_RECT_S *_pstRect,BoonInt32	 _iRectNum,BoonFloat32 *_f32OtherInf);

#ifdef __cplusplus
}
#endif

#endif 
