/********************************************************************
    Copyright (C), 1994-2012, 山东博昂信息科技有限公司	
    文件名称: 	 Boon_algo_verification.h
    文件描述:    BOON算法部  文件校验头文件
    文件作者:    BOON算法部
    修改历史:	 20:12:6:28   规范化   孙希伟
	            
*********************************************************************/
#ifndef   _BOON_VERIFICATION_H_
#define   _BOON_VERIFICATION_H_

#include	"Boon_algo_type.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum					/////////////////兼容 model和固件
{
	//	固件

	//	车牌识别相关
	CHINESE_MODEL = 20,							//汉字
	CHARACTER_MODEL = 21,						//字符
	DIGIT_MODEL = 22,							//数字
	ALPHA_MODEL = 23,							//
	XUE_MODEL = 24, 							//学
	CONFIDENCE_MODEL = 25,						//置信度
	GUA_MODEL = 26,								//挂
	CARTYEP_MODEL = 27,							//车型
	LOGO_MODEL = 28,							//车标
	HEADTAIL_MODEL = 29,						//车头车尾
	HKAO_MODEL = 30,							//港澳
	TRAFFICBELT_MODEL = 31,						//安全带检测

	//	车辆检测相关
	VEHICLEDET_KK_MODEL = 40,
	VEHICLEDET_DJ_MODEL = 41,
	VEHICLEDET_IPD_MODEL = 42,

	CARTYEP_MODEL_TAIL = 43,                       //车尾车型识别


}Boon_ALG_FILE_TYPE_E;

/**********************************************************
	名称：	VERIFICATION_GetFile
	功能：	从打包文件数据_pcBoonxBuf 提取指定_eType类型文件    \
			1、打包文件校验				\
			2、搜索文件ID相关信息			\
			3、开辟内存，提取数据到内存中	\
			4、给版本号、内存大小赋值

	参数：	BoonInt8* _pcBoonxBuf			//	打包文件数据
			BoonInt32 _i32BoonxLen			//	打包文件大小
			Boon_ALG_FILE_TYPE_E _eFileType	//	FILE type
			BoonInt8* _pcFileVersion		//	文件版本号，外部数组 [32]
			BoonInt8** _pcFileBuf			//	获取(解压后)文件数据缓冲区，内部申请内存
			BoonInt32* _pi32FileLen		//	申请内存的大小
			BoonInt32 _i32Seg				//	申请内存段

	返回：	Boon_ALG_OK						成功
			Boon_ALG_VERIFY_ERROR				校验失败返回
			Boon_ALG_INVALID_PARAM			文件信息错误
			Boon_ALG_MALLOC_ERR				申请内存错误
			Boon_ALG_FAIL						解压错误

	其他：	所申请内存需要在外部释放
**********************************************************/
Boon_EXPORTS BoonInt32 VERIFICATION_GetFile(
		BoonInt8* _pcBoonxBuf, BoonInt32 _i32BoonxLen,
		Boon_ALG_FILE_TYPE_E _eFileType,
		BoonInt8* _pcFileVersion,
		BoonInt8** _pcFileBuf, BoonInt32* _pi32FileLen, BoonInt32 _i32Seg);

#ifdef __cplusplus
}
#endif  

#endif 

