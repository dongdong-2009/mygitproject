/********************************************************************
    Copyright (C), 1994-2012, 山东博昂信息科技有限公司	
    文件名称: 	 Boon_algo_verification.h
    文件描述:    BOON算法部  文件校验头文件
    文件作者:    BOON算法部
    修改历史:	 20:12:6:28   规范化   孙希伟
	            
*********************************************************************/

#ifndef   _BOON_VERIFICATION_PRIVATE_H_
#define   _BOON_VERIFICATION_PRIVATE_H_

#include	"Boon_algo_type.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef enum 
{
	LPRV  = 0 ,		//LPR主程序
	LPRM,			//车牌识别汉字库
	TTV ,			//轨迹跟踪主程序
	TTMK,			//卡口车辆检测model
	TTMD,			//电警车辆检测model
	WMV,			//水印主程序
	EIV,			//增强源程序
	DFW,			//DSP固件
	IPDM
}Boon_ALG_FILETYPE_E;

typedef struct 									//文件附加信息结构体
{
	BoonUint32			uiFilesize;				//文件总大小，不含文件头
	BoonChar				acCompany[32];			//"山东博昂信息科技有限公司"--暂时不用
	BoonChar				acProduct[32];			//"LPR"   ---暂时不用
	Boon_ALG_FILETYPE_E	eProductID;				//产品ID，LPRV -0  LPRM -1 TTV -2 TTMK-3 TTMD -4 WMV -5 EIV -6
	BoonChar				acMasterVersion[32];	//主程序版本号	"V3.0.0.1"  //暂时不用
	BoonChar				acModelVersion[32];		//样本库版本号	"2.0.302.1" [文件版本]：6.5.705.1  （注：705是发布日期“0705”的后三位）
	BoonUint32			uiChecknum; 			//校验和，32位
	BoonUint32			uiCheckCrc;				//CRC校验
}Boon_ALG_FILEHEADER_S;


//	打包文件中的最大 file 个数
#define Boon_ALG_MAX_FILE_NUM		64

typedef struct			//	pack信息，size = 64
{
	BoonInt32				i32FileNums;			//	文件数
	BoonInt32				i32MaxFIleSize;			//	最大文件大小，可以不用
	BoonInt8				acDate[24];				//	打包文件日期
	BoonInt8				acReserved[32];			//	备注
}Boon_ALG_FILE_PACK_S;

typedef struct			//	file在pack中的信息，size = 64 + 20
{
	Boon_ALG_FILE_TYPE_E	eFileType;				//	类型
	BoonBool				bIsZip;					//	是否压缩		true: zip
	BoonInt8				acFileName[32];			//	文件名
	BoonInt8				acVersion[32];			//	文件版本号
	BoonInt32				i32FileLen;				//	文件大小，VERIFICATION_GetFile()申请内存使用
	BoonInt32				i32Offset;				//	在打包文件中的偏移量
	BoonInt32				i32Length;				//	在打包文件中的长度
}Boon_ALG_FILE_INFO_S;


/**********************************************************
	名称：	VERIFICATION_CheckFile

	功能：	检测文件的合法性

	参数：	BoonUint8 *_pucFile				检测文件
			BoonInt32 _iFileLen				检测文件长度
			Boon_ALG_FILETYPE_E  _eFileType	检测文件类型
			BoonChar *_pcFileVersion 			输出检测文件版本
			BoonInt32 *_piOffset				有效数据地址偏移


	返回：	正确： Boon_ALG_OK
			错误： Boon_ALG_PTR_NULL
				   Boon_ALG_FAIL

	其他：
**********************************************************/
BoonInt32	VERIFICATION_CheckFile( BoonUint8 *_pucFile,BoonInt32 _iFileLen,Boon_ALG_FILETYPE_E  _eFileType,BoonChar *_pcFileVersion,BoonInt32 *_piOffset);

#ifdef __cplusplus
}
#endif  

#endif 

