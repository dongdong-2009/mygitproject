
/********************************************************************
    Copyright (C), 1994-2012, 山东博昂信息科技有限公司	
    文件名称: 	 Boon_algo_crc.h
    文件描述:    BOON算法部  CRC校验头文件
    文件作者:    BOON算法部
    修改历史:	 20:12:6:28   规范化   孙希伟
	            
*********************************************************************/


#ifndef  _Boon_ALGO_CRC_H_
#define  _Boon_ALGO_CRC_H_

#include "Boon_algo_type.h"

#ifdef __cplusplus
Boon_EXPORTS "C"
{
#endif

/********************************************************************
	名称：	CRC_Crc32

	功能：	求32CRC校验值

	参数：	BoonUint8*	_pucBuf  	要校验数据开始指针
			BoonInt32		_iLen		要校验数据的长度

	返回：	校验值

	其他：	
********************************************************************/
BoonUint32  CRC_Crc32( BoonUint8* _pucBuf, BoonInt32 _iLen );



/********************************************************************
	名称：	CRC_Crc16

	功能：	求16位CRC校验值

	参数：	BoonUint8* _pucBuf,  	要校验数据开始指针
			BoonInt32  _iLen		要校验数据的长度

	返回：	校验值

	其他：	
********************************************************************/
BoonUint16  CRC_Crc16( BoonUint8* _pucBuf, BoonInt32 _iLen );

#ifdef __cplusplus
}
#endif
#endif 

