
#ifndef _BOON_UNZIPMEM_H_
#define _BOON_UNZIPMEM_H_


#include "Boon_algo_type.h"
#ifdef __cplusplus
extern "C"      //声明对分割模块的调用接口为C形式
{
#endif

/**********************************************************
	名称：	BoonAlgo_Unzip

	功能：	解压缩

	参数：	BoonUint8 * pucZipData		压缩数据
	  		BoonInt32 _iZipDataLen 		压缩数据长度
			BoonUint8 *_pucUnzipData		解压数据存储指针
			BoonInt32 _iSeg				应用内存段


	返回：	正确：解压后数据长度
			错误： 0

	其他：
**********************************************************/
Boon_EXPORTS BoonInt32 BoonAlgo_Unzip(BoonUint8 * pucZipData ,BoonInt32 _iZipDataLen, BoonUint8 *_pucUnzipData,BoonInt32 _iSeg );

#ifdef __cplusplus
}
#endif
#endif
