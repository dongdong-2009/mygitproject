#ifndef  _Boon_ALGO_TYPE_H_
#define  _Boon_ALGO_TYPE_H_

/********************************************************************
    Copyright (C), 1994-2012, 山东博昂信息科技有限公司	
    文件名称: 	 Boon_algo_type.h 
    文件描述:    Boon算法部-共用函数头文件
    文件作者:    孙希伟
	保密等级：	 本文件可公开，提
	供给算法应用商开发
    修改历史:	 
		
	            
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <stdarg.h>
#include <time.h>

#ifdef __cplusplus
extern "C"
{
#endif

/********************************************************************
一、数据类型定义
********************************************************************/
typedef long long       		BoonInt64; 
typedef	int						BoonInt32;
typedef short           		BoonInt16;
typedef	char     				BoonInt8;
typedef	char     				BoonChar;


typedef unsigned long long 		BoonUint64;
typedef unsigned int 			BoonUint32;
typedef unsigned short			BoonUint16;
typedef unsigned char 			BoonUint8;
typedef long            		BoonInt40;		
typedef unsigned long   		BoonUint40;	

typedef double     				BoonFloat64;
typedef float      				BoonFloat32;

typedef	unsigned				BoonUns;
typedef	char *          		BoonString;
typedef	void *					BoonPtr;
typedef void					BoonVoid;
typedef BoonInt32 				BoonBool;
typedef	BoonPtr					Boon_HANDLE;


/********************************************************************
二、常用宏定义
********************************************************************/
#define BoonFalse				0
#define BoonTrue				1

#ifndef NULL
	#define NULL	0
#endif 

#define Boon_EXPORTS					extern

#define	Boon_ALG_OK     				 0		//	操作执行成功
#define	Boon_ALG_ALREADY_INITED		 1		//	模块已经初始化过
#define Boon_ALG_FRAME_SKIPPED		 2		//	该帧被跳帧处理
#define	Boon_ALG_FAIL   				-1		//	操作执行失败
#define	Boon_ALG_INVALID_PARAM		-2		//	无效参数
#define Boon_ALG_NOT_INITED			-3		//	模块没有初始化
#define Boon_ALG_KEY_INVALID			-4 		//	无效的秘钥
#define Boon_ALG_EMPTY_FRAME			-5		//	传入图像为空
#define Boon_ALG_CANNOT_OPEN_FILE		-6		//	无法打开文件
#define Boon_ALG_VERIFY_ERROR         -7		//	校验错误 
#define Boon_ALG_PTR_NULL				-8		//	传入指针空
#define Boon_ALG_MALLOC_ERR			-9		//	分配内存错误

typedef enum
{
	IMAGE_FORMAT_Boon_YUV422	= 0,			//	图像是YUV422格式，planar存储，YUV分别放不同内存
	IMAGE_FORMAT_Boon_YUV420	= 1,			//	图像是YUV420格式，planar存储，YUV分别放不同内存			
	Boon_ALG_RGB888_PACKED	= 2,			//	图像是RGB888格式，packed存储，BGR混合存放:BGRBRG
	Boon_ALG_YUV422_PACKED	= 3,			//	图像是YUV422格式，packed存储，YUV混合存放:UYVY，如DM6437平台
	Boon_ALG_YUV420_MIXED		= 4,			//	图像是YUV422格式，Y单独一块内存，UV共用一块内存，如DM8127平台
	Boon_ALG_YUV422_MIXED		= 5,			//	图像是YUV420格式，Y单独一块内存，UV共用一块内存，如DM6467平台
	Boon_ALG_GRAY				= 6,			//	灰度图，只有Y
 }Boon_ALG_IMAGE_FORMAT_E;

/********************************************************************
二、常用结构体
********************************************************************/

/****************************************************
1.用以描述平面中的一个点的结构体
*****************************************************/
typedef struct
{
	BoonInt32		x;							//	点的x坐标值
	BoonInt32		y;							//	点的y坐标值
}Boon_ALG_POINT_S;							


/****************************************************
2.用以描述平面中的一个矩形区域的结构体
*****************************************************/
typedef struct
{
	BoonInt32		x;							//	区域左上角点的x坐标
	BoonInt32		y;							//	区域左上角点的y坐标
	BoonInt32		width;						//	矩形区域的宽度
	BoonInt32		height;						//	矩形区域的高度
}Boon_ALG_RECTWH_S;

/****************************************************
3.用以描述平面中的一个矩形区域的结构体
*****************************************************/
typedef struct
{
	BoonInt32		top;						//  区域垂直方向坐标的较小值
	BoonInt32		Boonttom;						//  区域垂直方向坐标的较大值
	BoonInt32		left;						//  区域水平方向坐标的较小值
	BoonInt32		right;						//  区域水平方向坐标的较大值
}Boon_ALG_RECT_S;

/****************************************************
4.用以描述平面中的一个任意条边围成区域的结构体
*****************************************************/
#define  Boon_MAX_BoonUNDARY_POINT_NUM		10					//	最大坐标数
typedef struct 
{
	BoonBool			bValid;									//  当前区域的有效性，1为可用
	BoonInt32			iPointNum;								//	组成该区域的顶点的个数
	Boon_ALG_POINT_S	astPoint[Boon_MAX_BoonUNDARY_POINT_NUM];	//  任意边形坐标点
}Boon_ALG_POLYGON_REGION_S;

/****************************************************
5.用以表示一帧图像的结构体
*****************************************************/
typedef struct
{
	BoonInt32					iWidth;				// 图像宽度
    BoonInt32					iHeight;			// 图像高度
	BoonUint8					*pucD1;				// 图像分量1 数据指针
	BoonUint8					*pucD2;				// 图像分量2 数据指针
	BoonUint8					*pucD3;				// 图像分量3 数据指针
	BoonUint64				ui64Time;			// 时间
	BoonInt32					iFlag;				// 标志
	Boon_ALG_IMAGE_FORMAT_E	eFormat;			// 格式
} Boon_ALG_IMAGE3_S;


/****************************************************
6.用以表示一帧图像的结构体
*****************************************************/
typedef struct									//时间戳
{	/* For pthread_cond_timedwait() */
	BoonInt32		iTimeSec;						//秒
	BoonInt32		iTimeMsec;						//ms为单位
}Boon_ALG_TIMESTAMP_S; 

typedef struct 
{
	BoonInt32					iSize;				// LPRImage 结构大小
	BoonInt32					iChannels;			// 通道数目，1、2、3、4
	BoonInt32					iDepth;				// 颜色深度，8、16
	BoonInt32					iColorMode;			// 取值为 LPRColorSpace 中某一个
	BoonInt32					iDataOrder;			// 0
	BoonInt32					iOrigin;			// 0
	BoonInt32					iWidth;				// 宽度
	BoonInt32					iHeight;			// 高度
	BoonInt32					iImageSize;			// 数据buffer大小
	BoonUint8					*pucData;			// 数据buffer指针
	BoonInt32					iStep;				// 每一行的长度（不一定和宽度相等）
	Boon_ALG_TIMESTAMP_S		stTimeStamp;		// 时间戳
	BoonInt32					iFrameNum;
}Boon_ALG_IMAGE_S;

/****************************************************
7.
*****************************************************/
typedef struct 
{
	BoonUint8		R;
	BoonUint8		G;
	BoonUint8		B;
}Boon_ALG_RGB_S;

/****************************************************
8.用以表示一直线的结构体
*****************************************************/
typedef struct 
{
	Boon_ALG_POINT_S		stFrom;					//线的点1
	Boon_ALG_POINT_S		stTo;					//线的点2
}Boon_ALG_LINE_S;

typedef struct 
{
	BoonInt8		x;
	BoonInt8		y;
}Boon_ALG_CENTER_S;
/****************************************************
9、音频数据内存格式	
****************************************************/
typedef enum
{
	Boon_ALG_PCM_MIXED_FMT =	1,					//混合存储
	Boon_ALG_PCM_PLANAR_FMT						//独立存储
}Boon_ALG_PCM_FORMAT_E;
/****************************************************
10、音频数据格式(64字节)

****************************************************/
typedef struct
{
	BoonInt32					iFlag;				//总是为-1，标识为本结构体
	BoonInt32					iSampleRate;		//采样率，如果是8K则设为8000;
	BoonInt32					iBitWidth;			//采样精度，采样数据位数  如果是16位就设为16  
	BoonInt32					iChanNum;			//通道数，单通道为1 双通道为2
	Boon_ALG_PCM_FORMAT_E		eFrameFormat;		//存储格式，混合存储为2，独立存储为1
	BoonUint32				uiVirAddr[2];		//音频数据虚拟地址指针
	BoonUint32				uiPhyAddr[2];		//音频数据物理地址指针
	BoonUint64				ui64TimeStamp;		//时间戳
	BoonUint32				uiSeq;				//音频帧序号
	BoonUint32				uiLen;				//每个通道的数据长度
	BoonUint32				uiExtraPhyAddr;		//额外数据的物理指针，传递和平台相关的数据
	BoonUint32				uiExtraVirAddr;		//额外数据的虚拟指针，传递和平台相关的数据
	BoonUint32				uiReserved;
}Boon_ALG_PCM_FRAME_PARA_S;

/****************************************************
11、视频数据格式(128字节)
 					
****************************************************/
typedef struct
{
	BoonInt32					iFlag;				//总是为-1，标识为新结构体
	BoonUint32				uiWidth;			//宽
	BoonUint32				uiHeight;			//高
	BoonUint32				uiStartX;			//左边无效宽度，像素数
	BoonUint32				uiStartY;			//上边无效宽度，像素数
	Boon_ALG_IMAGE_FORMAT_E	eImageFormat;		//像素格式
	BoonUint32				uiPhyAddr[3];		//物理地址
	BoonUint32				uiVirAddr[3];		//虚拟地址
	BoonUint32				uiStride[3];		//跨度
	BoonUint64				ui64Pts;			//时间戳
	BoonUint32				uiSeq;				//图像帧序号
	BoonUint32				uiExtraPhyAddr;		//额外数据的物理指针，传递和平台相关的数据
	BoonUint32				uiExtraVirAddr;		//额外数据的虚拟指针，传递和平台相关的数据
	BoonUint32				uiReserved[12];
}Boon_ALG_VIDEO_FRAME_PARA_S;

/****************************************************
12、算法接口版本
****************************************************/
typedef enum
{
	Boon_ALG_IF_IPC300W = 	1,					//20141101
	Boon_ALG_IF_COUNT
}Boon_ALG_INTERFACE_VERSION_E;

#ifdef __cplusplus
}
#endif
#endif 