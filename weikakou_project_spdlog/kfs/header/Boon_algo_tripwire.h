
#ifndef _Boon_algo_TRIPmeter_H__
#define _Boon_algo_TRIPmeter_H__

#include "Boon_algo_type.h"
#include "Boon_algo_tripwire_param.h"
#include "Boon_algo_tripwire_private.h"
#include "Boon_algo_ivs_result.h"
#include "ivs_gmm.h"

#ifdef __cplusplus
extern "C"
{
#endif

	/********************************************************
	名称：	BOONAlgo_TRIP_Creat
	功能：	创建算法引擎
	参数：	BoonInt32  _iSeg    算法占用内存段
	BoonChar  *_pcKey   算法密钥(128个字节)
	返回：  正确   引擎指针
	错误    NULL
	其他：	无
	*********************************************************/
	Boon_HANDLE BoonAlgo_TRIP_Creat(BoonInt32  _iSeg, BoonChar * _pcKey);
	/**************************************************************************
	Function:		BOONAlgo_TRIP_Creat
	Description:	创建各个模块并初始化
	Returns:   	Boon_ALG_STATUS_E 操作状态
	Parameter: 	Boon_HANDLE _hModule 模块句柄
	**************************************************************************/
	Boon_EXPORTS BoonInt32 BoonAlgo_TRIP_Init(BoonInt32 _iImgW, BoonInt32 _iImgH);
	/**************************************************************************
	Function:		BOONAlgo_TRIP_Release
	Description:	终止各个模块并释放内存
	Returns:   	Boon_ALG_STATUS_E 操作状态
	Parameter: 	Boon_HANDLE _hModule 模块句柄
	**************************************************************************/
	Boon_EXPORTS BoonInt32 BoonAlgo_TRIP_Release(Boon_HANDLE _hModule);
	/**************************************************************************
	Function:		BOONAlgo_TRIP_Process
	Description:	处理一幅图像
	Returns:   	Boon_ALG_STATUS_E 操作状态
	Parameter: 	Boon_HANDLE _hModule 模块句柄
	Parameter: 	BOONUint8 * _pucImage 灰度图像指针
	**************************************************************************/
	Boon_EXPORTS BoonInt32 BoonAlgo_TRIP_Process(Boon_ALG_IMAGE3_S* _pstImage);

	/**************************************************************************
	Function:		BOONAlgo_TRIP_GetResults
	Description:	获取处理结果
	Returns:   	Boon_ALG_STATUS_E 操作状态
	Parameter: 	Boon_HANDLE _hModule 模块句柄
	Parameter: 	Boon_ALG_RESULT_S * _pstResult 处理结果
	**************************************************************************/
	Boon_EXPORTS BoonInt32 BoonAlgo_TRIP_GetResults(char *plate);
	/**************************************************************************
	Function:		BOONAlgo_TRIP_GetLibInfo
	Description:	获取算法的版本信息
	Returns:   	Boon_ALG_STATUS_E 操作状态
	Parameter: 	Boon_ALGO_LIB_INFO_S * _pstLibInfo 库信息
	**************************************************************************/
	Boon_EXPORTS BoonInt32 BoonAlgo_TRIP_GetLibInfo( Boon_ALG_TRIP_LIB_INFO_S *_pstLibInfo);

#ifdef __cplusplus
}
#endif

#endif // _Boon_algo_TRIPmeter_H__
