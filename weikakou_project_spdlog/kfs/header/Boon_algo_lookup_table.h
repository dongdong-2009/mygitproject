#ifndef _Boon_ALGO_LOOKUP_TABLE_H_
#define _Boon_ALGO_LOOKUP_TABLE_H_


#include	"Boon_algo_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**********************************Example*****************************
//查询 201的倒数。
//在初始化函数中调用 _gstLookUpTable.pf32Rcp_512_Init(iSeg); 将表生成。
//
//BoonFloat32  f32Temp = _gstLookUpTable.pf32Rcp_512[201]; 得到倒数值
//说明：个人可自定义查找表，按固定格式放在结构体中，既可
**********************************************************************/
typedef struct
{
	///////////////////// 倒数表
	// 输入范围	[0, 512),
	BoonFloat32* 	pf32Rcp_512;
	BoonInt32 (*pf32Rcp_512_Init)(BoonInt32);

	BoonFloat32 	*pf32etable;						//小数的指数部分倒数表
	BoonInt32 	(*pf32etable_Init)(BoonInt32);  
	BoonFloat32 	*pf32decltable;						//小数的小数部分的倒数表精度小数点后6位
	BoonInt32 	(*pf32decltable_Init)(BoonInt32);
	
	BoonFloat32 	*pf32NexpHtable;					//负指数函数整数部分表
	BoonInt32  	(*pf32NexpHtable_Init)(BoonInt32);  
	BoonFloat32 	*pf32NexpLtable;					//负指数函数小数部分表
	BoonInt32  	(*pf32NexpLtable_Init)(BoonInt32);  
	BoonUint8  	**pucAngleScale;
	BoonInt32 	(*pucAngleScaleTable_Init)(BoonInt32);

	BoonFloat32 ** pf32npd_kernel;
	BoonInt32 (*pf32npd_kernel_Init)(BoonInt32);//(x-y)/(x+y+0.0001)

//	BoonFloat32 * pf32NexpInt;
//	BoonInt32 (*pf32NexpInt_Init)(BoonInt32);//Z - 0-262144

	BoonInt32 * pf32NexpInt;
	BoonInt32 (*pf32NexpInt_Init)(BoonInt32);//Z - 0-262144

	//计算公式 (x-y)/((x+y)+0.0001f);
	//x y 范围 0 -255 
	//BoonFloat32 pf32Rcp_255XY[256][256];
//	BoonInt32 (*pf32Rcp_255XY_Init)(BoonInt32);

}Boon_ALG_LOOKUPTABLET_S;

Boon_EXPORTS
Boon_ALG_LOOKUPTABLET_S  _gstLookUpTable;
#ifdef __cplusplus
}
#endif

#endif
