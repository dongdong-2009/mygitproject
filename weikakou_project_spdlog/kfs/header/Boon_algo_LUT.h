
#include "Boon_algo_type.h"

#ifndef _Boon_ALGO_LUT_H_
#define _Boon_ALGO_LUT_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	BoonInt32 i32Size;

	///////////////////// 倒数表
	// 分割
	BoonInt32* pi32Rcp_360_SQ16;
	// 分割
	// 输入范围	[0, 255), 求倒后保留19位小数
	BoonInt32* pi32Rcp_256_SQ19;
	// 分割
	// 输入范围	[0, 64),
	BoonFloat32* pf32Rcp_64;

	///////////////////// sin 表
	// 分割
	//三角函数横坐标以四分之一度递增，纵坐标以1024定标
	BoonInt32* pi32Sin_360_SQ10;
	// 分割
	//三角函数横坐标以四分之一度递增，纵坐标以65536定标
	BoonInt32* pi32Sin_360_SQ16;

	///////////////////// cos 表
	// 分割
	//三角函数横坐标以四分之一度递增，纵坐标以1024定标
	BoonInt32* pi32Cos_360_SQ10;
	// 分割
	//三角函数横坐标以四分之一度递增，纵坐标以65536定标
	BoonInt32* pi32Cos_360_SQ16;

	///////////////////// tan 表
	// 分割
	//三角函数横坐标以四分之一度递增，纵坐标以1024定标
	BoonInt32* pi32Tan_360_SQ10;
	// 分割
	//三角函数横坐标以四分之一度递增，纵坐标以1024定标
	BoonInt32* pi32Tan_360_SQ16;

	///////////////////// atan 表
	// 分割
	BoonInt32* pi32ATan_360_SQ10;
	
	///////////////////// 表
	// 分割
	BoonFloat32* pf32ExpDivision;

	///////////////////// 类型转换表
	// 光流
	// opencv整形转浮点表，[-128, 255]
	BoonFloat32* pf32Int2F32_OpenCV; // int->float 

}Boon_ALG_LOOKUPTABLE_S;

Boon_EXPORTS Boon_ALG_LOOKUPTABLE_S 	g_stLookUpTable;

#ifdef __cplusplus
}
#endif

#endif
