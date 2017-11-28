#ifndef __Boon_STRUCTURE_H__
#define __Boon_STRUCTURE_H__

#include "Boon_algo_lpr_define.h"

// LPR参数

// 车牌模型
typedef struct 
{
	BoonInt32		iPlateType;//需要输出的车牌种类，//Boon_ALG_LPRPlateType_E的数值相加
	BoonInt32		aiPlateCharType[Boon_LPR_MAX_NUM_CHAR];	// CharType，每一位的类型
}Boon_ALG_LPRPlateModel_S;

typedef struct 
{
	BoonInt32				    iSize;   //Boon_ALG_LPRParam_S结构体大小
	BoonInt32				    iMaxPlate;//最多输出车牌数量
	BoonInt32				    iMinPlateWidth;//最小车牌宽度
	BoonInt32				    iMaxPlateWidth;//最大车牌宽度
	Boon_ALG_LPRPlateModel_S	stPlateModel;//字符规则
	BoonFloat32				f32Confid;	// 整个车牌的置信度，高于此置信度输出
	BoonChar*                 pcModelAdd;//字符模板路径
	BoonInt32                 iModelLen; //字符文件长度
	Boon_HANDLE				hLog;				//日志模块
    BoonInt32                 iRegStatus;  			 //算法的注册状态
	BoonInt32                 iRatio;  		//图像缩放比
	BoonInt32                 iPlatePattern;	//车牌样式0表示正常车牌 1表示大尺寸车牌(用于天津演示) 2表示大角度车牌(用于违停球车牌倾斜角度大)
	BoonInt32                 iReserved2;
}Boon_ALG_LPRParam_S;




/// 车牌检测的输出信息
typedef struct 
{
	BoonInt32                      iSize;         // Boon_ALG_LPROutput_S 结构大小
	Boon_ALG_RGB_S                 stCarColor;                     // 车身颜色
	Boon_ALG_LPRPlateColor_E	     eColor;						// 车牌颜色
	Boon_ALG_LPRVehicleType_E      eCarType;                      //车辆类型
	Boon_ALG_LPRPlateType_E	     eType;						// 车牌类型
	Boon_ALG_LPRVehicleBrand_E     eBrandType;                  //车标类型
	BoonInt32                      iIllgalType;                 //违法类型//如果是0表示无违法，1表示不系安全带，2表示打电话，3表示(1+2)两种违规
	BoonInt32                      iCarColorDepth;              //车身颜色深浅色，0表示深色，1表示浅色
	Boon_ALG_RECT_S			     stRectPlate;					// 车牌位置矩形
	Boon_ALG_RECT_S                stRectFace;                     //人脸坐标矩形
	Boon_ALG_RECT_S                stRectLogo;                     //车标坐标矩形
	Boon_ALG_RECT_S			     astCharRect[Boon_LPR_MAX_NUM_CHAR];	// 车牌各位字符的位置矩形，在全图中的坐标
	 char			             acPlateRec[Boon_LPR_PLATE_STR_LEN];	// 车牌号
	BoonFloat32			         af32Confid[Boon_LPR_MAX_NUM_CHAR];	// 车牌各位字符的置信度
	BoonFloat32			         f32Confid;					// 整个车牌的置信度
	BoonInt32				         iNumChar;					// 车牌中字符数目
	BoonInt32                      iAvgGray;                    //车牌的平均灰度
	BoonInt32                      iHeadTail;                   //车头还是车尾0未知,1车头,2车尾
}Boon_ALG_LPROutput_S;

/// 多输出的接口
typedef struct 
{
	Boon_ALG_LPROutput_S	astOutputs[Boon_LPR_MAX_OUTPUT_NUM];	// 多个输出结果。
	BoonInt32			    iNumOutputs;					// 输出结果的数目。
}Boon_ALG_LPROutputMulti_S;

// 局部参数
// 用于描述图像中的一个待识别的矩形区域
typedef struct 
{
	Boon_ALG_RECT_S	stRectRegion;		// 用一个矩形框表示的识别区域，描述图像中的需要识别识别区域，该区域外的部分将不做识别，
	// 矩形框的上下左右边界值都以像素为单位。
	BoonInt32			iMinPlateWidth;	// 最小车牌宽度，小于该宽度的车牌将不做识别。
	BoonInt32			iMaxPlateWidth;	// 最大车牌宽度，大于该宽度的车牌将不做识别。
	BoonInt32         iAlgorithmType; //支持算法的类型，与Boon_ALG_LPRAlgorithmType_E的枚举做位运算
	BoonInt32         iLprDetectMotor;//0表示不支持机非人，1表示支持机非人
	BoonInt32		    iReserved0;		     // 保留参数，设为0。
	BoonInt32		    iReserved1;		     // 保留参数，设为0。
	BoonFloat32		f32Reserved2;		// 保留参数，设为0。
	BoonFloat32		f32Reserved3;		// 保留参数，设为0。
}Boon_ALG_LPRParamLocal_S;

typedef struct 
{
	Boon_ALG_LPRParamLocal_S	astParams[Boon_LPR_MAX_REGIONS_PER_FRAME];	// 多个局部参数，一般情况下使用一个局部参数即可。
	BoonInt32				iNumParams;							// astParams数组中局部参数的实际数目。
}Boon_ALG_LPRParamMulti_S;



#endif
