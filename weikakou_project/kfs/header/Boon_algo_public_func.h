#ifndef _Boon_ALGO_PUBLICFUNC_H_
#define _Boon_ALGO_PUBLICFUNC_H_
/********************************************************************
    Copyright (C), 1994-2012, 山东博昂信息科技有限公司	
    文件名称: 	 Boon_ALGo_public_func.h 
    文件描述:    BOON算法部-共用函数头文件
    文件作者:    孙希伟
    修改历史:	 17:12:2012   14:08	create 
	            
*********************************************************************/
#include	"Boon_algo_type.h"
#include	"Boon_algo_log.h"


#ifdef __cplusplus
Boon_EXPORTS "C"
{
#endif
 static int sdiv_table[256];
  static int hdiv_table180[256];
static int initialized;
//#if ( defined( DEBUG_PRINT_ENABLE ) && defined( LOCAL_DBG_PRT_EN ) )
	#define 	DEBUG_COM_PRINT			BoonAlgo_LOG_AddLog
//#else
//	#define 	DEBUG_COM_PRINT		
//#endif

#if ( defined( DEBUG_PRINT_ENABLE ) && defined( LOCAL_DBG_PRT_EN ) && defined( LOCAL_TIME_PRT_EN ) )
	#define 	DEBUG_GET_TIME_MS(x)	Public_GetTimeMs2(x)
#else
	#define 	DEBUG_GET_TIME_MS(x)		
#endif

#define		MaxValue(a,b)            (((a) > (b)) ? (a) : (b))		//
#define		MinValue(a,b)            (((a) < (b)) ? (a) : (b)) 
	
#define CV_SUM_OFFSETS( p0, p1, p2, p3, rect, step )                      \
	/* (x, y) */                                                          \
	(p0) = (rect).x + (step) * (rect).y;                                  \
	/* (x + w, y) */                                                      \
	(p1) = (rect).x + (rect).width + (step) * (rect).y;                   \
	/* (x + w, y) */                                                      \
	(p2) = (rect).x + (step) * ((rect).y + (rect).height);                \
	/* (x + w, y + h) */                                                  \
	(p3) = (rect).x + (rect).width + (step) * ((rect).y + (rect).height);

#define CV_SUM_PTRS( p0, p1, p2, p3, sum, astRect, step )                 \
	/* (x, y) */                                                          \
	(p0) = sum + (astRect).x + (step) * (astRect).y,                      \
	/* (x + w, y) */                                                      \
	(p1) = /*sum + (astRect).x + (step) * (astRect).y*/ (p0) + (astRect).width, \
	/* (x + w, y) */                                                      \
	(p2) = /*sum + (astRect).x + (step) * ((astRect).y + (astRect).height),*/ \
	       (p0) + (step) * ((astRect).height),\
	/* (x + w, y + h) */                                                  \
	(p3) = /*sum + (astRect).x + (step) * ((astRect).y + (astRect).height)*/ (p2) + (astRect).width

#define CALC_SUM_(p0, p1, p2, p3, offset) \
	((p0)[offset] - (p1)[offset] - (p2)[offset] + (p3)[offset])

	
typedef union 
{
	struct
	{
		BoonUint32		uiTimeLow;
		BoonUint32		uiTimeHigh;
	};
	BoonUint64   ui64Time;
}SYSTIME_S;

typedef struct 
{
	BoonInt32   iUsedMem;
	BoonInt32   iUsedMaxMem;
	BoonInt32	  iMemChange;
}MEMINF_S;

typedef struct
{
	BoonUint32   u32PhyAddr;
	BoonUint8    *pu8VirAddr;
	BoonUint32    u32Size;
	BoonInt32     s32PoolID;	
	BoonUint32    u32Blk;
	BoonInt32     s32MyPoolsID;	
	BoonUint32    u32MyPoolsBlk;
	BoonUint32    u32CacheFlag;

	BoonUint32    u32ReallSize;
	BoonUint32    u32RealPhyAddr;
	BoonUint8    *pu8RealVirAddr;
}Boon_IVE_MEM_INFO_S;



Boon_EXPORTS	MEMINF_S   stMemInformation;
typedef enum
{
	 CHIP_ID  =	0,			//针对DM8127应用，取16字节ID中6字节
	 CUSTOM_ID = 1			//针对DM8127应用，对16字节ID进行加密处理后得到6字节
}DEVICE_ID_TYPE_E;

/********************************************************************
	名称：	Public_ImageInterpolation

	功能：	双线性插值方法对图像归一化

	参数：	BoonUint8 *_pucSrcImage		原始图像指针
	  		BoonUint8 *_pucDstImage  		归一化图像指针
			BoonInt32 _iSrcWidth			原始图像宽度
			BoonInt32 _iSrcHeight			原始图像高度
			BoonInt32 _iNewWidth			归一化图像宽度
			BoonInt32 _iNewHeight			归一化图像高度

	返回：	Boon_ALG_OK		操作执行成功

	其他：	_uSrcImage、_uDstImage为不相关的图像数据指针。
*********************************************************************/

Boon_EXPORTS	BoonInt32 Public_ImageInterpolation(BoonUint8 *_pucSrcImage, BoonUint8 *_pucDstImage, BoonInt32 _iSrcWidth,BoonInt32 _iSrcHeight, BoonInt32 _iNewWidth, BoonInt32 _iNewHeight);
Boon_EXPORTS    BoonInt32 Public_ImageInterpolation1(BoonUint8 *_pucSrcImage, BoonUint8 *_pucDstImage, BoonInt32 _iSrcWidth,BoonInt32 _iSrcHeight, BoonInt32 _iNewWidth, BoonInt32 _iNewHeight);
/********************************************************************
	名称：	Public_PointInPolygon

	功能：	判断点是否在多边形内

	参数：	Boon_ALG_POINT_S _ptSrc		                点的坐标
	  		Boon_ALG_POLYGON_REGION_S _PolyRegion 		多边形区域

	返回：	1表示在内  0不在内
*********************************************************************/
Boon_EXPORTS	BoonInt32 Public_PointInPolygon(Boon_ALG_POINT_S _stPtSrc, Boon_ALG_POLYGON_REGION_S *_pstPolyRegion);

/********************************************************************
	名称：	Public_GeBooneviceID

	功能：  读取算法运行平台芯片内部的序列号

	参数：	BoonUint8 * pucID		     读取序列号到输出指针区域
			Boon_ALG_IDTYPE_E _eReadIdType   读取指定类型的ID号

	返回：	无 
//Boon_EXPORTS  BoonVoid	Public_GeBooneviceID( BoonUint8 * _pucID );
*********************************************************************/
Boon_EXPORTS BoonVoid	Public_GeBooneviceID( BoonUint8 * _pucID ,DEVICE_ID_TYPE_E _eReadIdType);

/**********************************************************
	名称：	Public_ImageGray

	功能：	对RGB图像灰度化

	参数：	BoonUint8 *_pucSrcImage		原始彩色图像指针
	  		BoonUint8 *_pucDstImage  		灰度化化图像指针
			BoonInt32 _iWidth			    图像宽度
			BoonInt32 _iHeight			图像高度

	返回：	无

	其他：	_uSrcImage、_uDstImage为不相关的图像数据指针。
**********************************************************/
BoonInt32 LPL_Filter3(BoonUint8 *_pucImgbuf, BoonUint32 _iWidth, BoonUint32 _iHeight, BoonUint32 _iValue1, BoonUint32 _iValue2);
BoonVoid LPL_Fill3( BoonUint8   *_pucImgbuf, BoonUint8* _pucDst, BoonInt32 _iWidth, BoonInt32 _iHeight, BoonInt32 _iValue1, BoonInt32 _iValue2 );
BoonVoid LPL_Fill4( BoonUint8   *_pucImgbuf, BoonUint8* _pucDst, BoonInt32 _iWidth, BoonInt32 _iHeight, BoonInt32 _iValue1, BoonInt32 _iValue2 );
BoonInt32 LPL_AdaptiveThreshold3(BoonUint8*  _pucInput,BoonUint8*  _pucBin	, BoonUint32 _iWidth, BoonUint32 _iHeight);
Boon_EXPORTS BoonVoid Public_ImageGray( BoonUint8 *_pucSrcImage, BoonUint8 *_pucDstImage, BoonInt32 _iWidth, BoonInt32 _iHeight);
Boon_EXPORTS BoonVoid Public_ImageGray1( BoonUint8 *_pucSrcImage, BoonUint8 *_pucDstImage, BoonInt32 _iWidth, BoonInt32 _iHeight);
Boon_EXPORTS BoonVoid Public_ImageGray2( BoonUint8 *_pucSrcImage, BoonUint8 *_pucDstImage, BoonInt32 _iWidth, BoonInt32 _iHeight);
Boon_EXPORTS BoonVoid Public_ImageGray3( BoonUint8 *_pucSrcImage, BoonUint8 *_pucDstImage, BoonInt32 _iWidth, BoonInt32 _iHeight);

/**********************************************************
	名称：	Public_ImageIntMultipleReduse

	功能：	双线性插值方法对图像归一化

	参数：	BoonUint8 *_pucSrcImage		原始图像指针
	  		BoonUint8 *_pucDstImage  		归一化图像指针
			BoonInt32 _iSrcWidth			原始图像宽度
			BoonInt32 _iSrcHeight			原始图像高度
			BoonInt32 _iNewWidth			归一化图像宽度
			BoonInt32 _iNewHeight			归一化图像高度

	返回：	Boon_ALG_OK		操作执行成功

	其他：	_uSrcImage、_uDstImage为不相关的图像数据指针,缩小前后必须成整数比例。
**********************************************************/
Boon_EXPORTS BoonInt32	Public_ImageIntMultipleReduse(BoonUint8 *_pucSrcImage, BoonUint8 *_pucDstImage, BoonInt32 _iSrcWidth,BoonInt32 _iSrcHeight, BoonInt32 _iNewWidth, BoonInt32 _iNewHeight);
/**********************************************************
	名称：	Public_Malloc

	功能：	动态申请内存

	参数：	BoonInt32  _iMemSeg		内存段
	  		BoonInt32  _iMemSize 		申请内存大小
			BoonUint8  _ucMemAlign    内存对齐方式


	返回：	申请内存起始指针

	其他：	申请内存数据为随机值，速度相对清0要快。
**********************************************************/
Boon_EXPORTS	BoonVoid  *Public_Malloc(BoonInt32  _iMemSeg,BoonInt32  _iMemSize,BoonUint8 _ucMemAlign);

/**********************************************************
	名称：	Public_Calloc

	功能：	动态申请内存

	参数：	BoonInt32  _iMemSeg		内存段
	  		BoonInt32  _iMemSize 		申请内存大小
			BoonUint8  _ucMemAlign      内存对齐方式


	返回：	申请内存起始指针

	其他：	申请内存内部含初始化为0
**********************************************************/
Boon_EXPORTS	BoonVoid  *Public_Calloc(BoonInt32  _iMemSeg,BoonInt32  _iMemSize,BoonUint8 _ucMemAlign);
/**********************************************************
	名称：	Public_Free

	功能：	内存释放

	参数：	BoonInt32  _iMemSeg		内存段
	  		BoonVoid	* _pPtr 		释放内存地址
			BoonInt32  _iMemSize      释放内存大小。


	返回：

	其他：
**********************************************************/
Boon_EXPORTS BoonVoid  Public_Free(BoonInt32  _iMemSeg,BoonVoid * _pPtr,BoonInt32  _iMemSize);

/**********************************************************
	名称：	Public_DebugPrint

	功能：	

	参数：	BoonChar * _pcFileName		日志文件名
	  		BoonChar * _pcDbBuf			日志内存地址
			const BoonChar * _pcFormat    日志输出格式
			...						    可变日志参数

	返回：

	其他：
**********************************************************/
Boon_EXPORTS BoonVoid  Public_DebugPrint(BoonChar * _pcFileName, BoonChar * _pcDbBuf, const BoonChar * _pcFormat,...);

/**********************************************************
	名称：	Public_GetTimeMs

	功能：	获取系统时间 单位：ms 

	参数：	

	返回：SYSTIME_S 系统当前时间

	其他：
**********************************************************/
Boon_EXPORTS SYSTIME_S Public_GetTimeMs(void );
Boon_EXPORTS	BoonVoid 	Public_GetTimeMs2(SYSTIME_S* _pstSysTime  );



/**********************************************************
	名称：	Public_GetTimeUs

	功能：	获取系统时间 单位：us 

	参数：	

	返回：SYSTIME_S 系统当前时间

	其他： （DSP平台） 时间过长数据可能溢出。时间段求取出现异常值
**********************************************************/
Boon_EXPORTS SYSTIME_S Public_GetTimeUs(void );
Boon_EXPORTS BoonVoid Public_BGR2HSV( BoonUint8 *_pucSrcImage, BoonUint8 *_pucDstImage, BoonInt32 _iWidth, BoonInt32 _iHeight);
Boon_EXPORTS BoonVoid Public_RGB2HSV( BoonUint8 *_pucSrcImage, BoonUint8 *_pucDstImage, BoonInt32 _iWidth, BoonInt32 _iHeight);
void InteEqualize(BoonUint8 *_pucSrcImage, BoonInt32 lWidth, BoonInt32 lHeight);

/**********************************************************
	名称：	Public_OutputMemInformation

	功能：	

	参数：	BoonChar * _pcFileName		信息保存文件名
	  		BoonChar * _pcDbBuf			信息保存内存地址
			BoonChar * _pcTestFalg        信息标志。


	返回：

	其他：
**********************************************************/
Boon_EXPORTS BoonVoid  Public_OutputMemInformation(BoonChar * _pcFileName, BoonChar * _pcDbBuf,BoonChar * _pcTestFalg);
Boon_EXPORTS	BoonVoid  Public_OutputMemInf(Boon_HANDLE _hModule,Boon_ALG_LOG_LEVEL_E  _eLevel,const BoonChar  * _pcFrm,...);


/**********************************************************
	名称：	Public_Round

	功能：	浮点数转换成整形，返回和输入浮点参数最接近的整数值

	参数：	BoonFloat32   _f32Value	输入浮点数

	返回：  BoonInt32                 返回转换后的整数值

	其他：
**********************************************************/
Boon_EXPORTS  BoonInt32  Public_Round( BoonFloat32   _f32Value );

/**********************************************************
	名称：	Public_Floor

	功能：	浮点数转换成整形，返回不大于输入浮点参数的最大整数值

	参数：	BoonFloat32   _f32Value	输入浮点数

	返回：  BoonInt32                 返回转换后的整数值

	其他：
**********************************************************/
Boon_EXPORTS  BoonInt32  Public_Floor( BoonFloat32   _f32Value );

/**********************************************************
	名称：	Public_Ceil

	功能：	浮点数转换成整形，返回不小于输入浮点参数的最小整数值

	参数：	BoonFloat32   _f32Value	输入浮点数

	返回：  BoonInt32                 返回转换后的整数值

	其他：
**********************************************************/
Boon_EXPORTS  BoonInt32  Public_Ceil( BoonFloat32   _f32Value );


 /********************************************************************
	名称：	Public_PloygonClockwise

	功能：	修改周界点传入的顺序，统一为顺时针

	参数：	Boon_ALG_POLYGON_REGION_S _PolyRegion 	多边形区域

	返回：	无

	说明：	要求凸点数大于凹点数
*********************************************************************/
Boon_EXPORTS BoonVoid Public_PloygonClockwise(Boon_ALG_POLYGON_REGION_S *_pstPolyRegion);


/********************************************************************
	名称：	Public_LineXLine

	功能：	判断两线是否交叉

	参数：	Boon_ALG_LINE_S _stLineFrt	第一条线
	  		Boon_ALG_LINE_S _stLineSec	第二条线

	返回：	BoonTrue表示有交点  BoonFalse无交点
*********************************************************************/
Boon_EXPORTS BoonBool Public_LineXLine(Boon_ALG_LINE_S _stLineFrt,Boon_ALG_LINE_S _stLineSec);


/********************************************************************
	名称：	Public_GetLineAngle

	功能：	获取线与水平线的夹角

	参数：	Boon_ALG_LINE_S _stLine	要求角度的线段

	返回：	线与水平线的夹角
*********************************************************************/
Boon_EXPORTS BoonInt32 Public_GetLineAngle(Boon_ALG_LINE_S _stLine);


/********************************************************************
	名称：	Public_GeBooniffCount

	功能：	取得算法判断图像中的锐度值，进行多点聚焦

	参数：	Boon_ALG_IMAGE_S  * _pstSrcImg 原始灰度图
			Boon_ALG_RECTWH_S *_pstRect    聚焦区域指针,
			BoonInt32         _iRectCount  区域数量 

	返回：  锐度值           
	其他：	无
*********************************************************************/
Boon_EXPORTS BoonInt32     Public_GeBooniffCount(Boon_ALG_IMAGE_S * _pstSrcImg,Boon_ALG_RECTWH_S *_pstRect,BoonInt32 _iRectCount);



/********************************************************************
	名称：	Public_f32Compute

	功能：	单精度浮点数倒数(牛顿迭代估计算法)

	参数：	BoonFloat32  _f32x  输入单精度浮点数


	返回：  单精度浮点数倒数。           
	其他：	无
*********************************************************************/
Boon_EXPORTS BoonFloat32 Public_f32Compute(BoonFloat32  _f32x);

/********************************************************************
	名称：	Public_FloatInverse

	功能：	浮点数倒数 (分离小数指数和小数部分，查表得倒数乘积)

	参数：	BoonFloat32  _f32xAny  输入单精度浮点数


	返回：  单精度浮点数倒数。           
	其他：	无
*********************************************************************/

Boon_EXPORTS BoonFloat32 Public_FloatInverse(BoonFloat32 _f32xAny);

/********************************************************************
	名称：	Public_Sleep

	功能：	系统延时函数

	参数：	BoonInt32    _iMillisecond   输入延时时间

	返回：  无     

	其他：	系统延时时间单位为毫秒
*********************************************************************/
Boon_EXPORTS  BoonVoid  Public_SleepMs( BoonInt32   _iMillisecond);



#ifdef __cplusplus
}
#endif
#endif
