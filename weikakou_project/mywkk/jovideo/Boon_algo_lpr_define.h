#ifndef __Boon_DEFINE_H__
#define __Boon_DEFINE_H__

#include "Boon_algo_type.h"

#define Boon_LPR_REGION_TYPE					0

#define Boon_ENABLE_SEPARATOR_POS_FIELD		1
#define Boon_REC_VEHICLE_BRAND				1

// 基本的常量

// 车牌字符串长度
#define Boon_LPR_PLATE_STR_LEN		22

// 车牌字符数目
#define Boon_LPR_NUM_CHAR			7
#define Boon_LPR_MAX_NUM_CHAR		7

// 最大的输出结果数目，预留
#define Boon_LPR_MAX_OUTPUT_NUM		32
#define Boon_LPR_MAX_FACES			4

#define Boon_LPR_MAX_REGIONS_PER_FRAME		32


//最大字母数目
#define Boon_LPR_MAX_ALPHA_NUM   26
//最大汉字数目（首汉字）
#define Boon_LPR_MAX_CHINESE_NUM  41


// 每一位字符的识别类型
typedef enum 
{
	Boon_INVALID		= 0,
	Boon_DigitAlpha	= 1,	// 数字及字母
	Boon_Digit		= 2,	// 数字
	Boon_Alpha		= 3,	// 字母
	Boon_XUEJING      = 4,    //add by wsj 20120711 for 学警
	Boon_HANZI        = 5,    //add by wsj for汉字
	Boon_GUAPAI         = 6,//add by wsj 20120927for 挂
	Boon_HKAO          = 7,//add by wsj 20140506for 港澳车牌
	// 汉字识别的地区类型	  
	Boon_China		= 20,	// 全国通用
	Boon_HeiLongJiang	= 21,	// 黑龙江
	Boon_ShangHai		= 22,	// 上海
	Boon_LiaoNing		= 23,	// 辽宁
	Boon_ShanDong		= 24,	// 山东
	Boon_GuangDong	= 25,	// 广东
	Boon_GuangXi		= 26,	// 广西
	Boon_TianJin		= 27,	// 天津
	Boon_BeiJing		= 28,	// 北京
	Boon_JiLin		= 29,	// 吉林
	Boon_HeNan		= 30,	// 河南
	Boon_HuBei		= 31,	// 湖北
	Boon_HuNan		= 32,	// 湖南
	Boon_JiangXi		= 33,	// 江西
	Boon_GanSu		= 34,	// 甘肃
	Boon_ZheJiang		= 35,	// 浙江
	Boon_JiangSu		= 36,	// 江苏
	Boon_HuaDong		= 37,	// 华东
	Boon_XiNan		= 38,	// 西南
	Boon_XiBei		= 39,	// 西北
	Boon_DongBei		= 40,	// 东北
	Boon_HuaBei		= 41,	// 华北
	Boon_HuaNan		= 42,	// 华南
	Boon_HuaZhong		= 43	// 华中

}Boon_ALG_LPRRecType_E;							

// 车牌颜色
typedef enum 
{
	Boon_UNKNOWN	= 0,	// 未知
	Boon_BLUE		= 1,	// 蓝底白字
	Boon_YELLOW	= 2,	// 黄底黑字
	Boon_WHITE	= 3,	// 白底黑字
	Boon_BLACK	= 4,	// 黑底白字	
	Boon_GREEN	= 5		// 绿底白字
}Boon_ALG_LPRPlateColor_E;

// 车牌类型
typedef enum 
{
	Boon_UNKOWN		= 0,	// 未知
	Boon_CAR_NORMAL	= 1,	// 普通小车，私家车，蓝色，黑色
	Boon_BIG_NORMAL	= 1<< 1,	// 普通大车，卡车，黄色
	Boon_POLICE		= 1<< 2,    // 警车（分割符在第一位和第二位字符之间），白色
	Boon_WJ			= 1<< 3,	// 武警车辆
	Boon_HK			= 1<< 4,	// 港澳车辆
	Boon_DOUBLELINE	= 1<< 5,	// 双层黄牌
	Boon_MILITARY		= 1<< 6,	// 军牌
	Boon_AMBASSADOR	= 1<< 7,	// 使馆车辆
	Boon_DGREEN_TYPE2	= 1<< 8,// 第二类绿牌车，电动自行车
	Boon_POLICE_TYPE2	= 1<< 9,  // 第二类警车（分割符在第二位和第三位字符之间），白色
	Boon_XUE			= 1<< 10,	// “学”车牌
	Boon_MOTOR		= 1<< 11,	// 摩托车
	Boon_LIAOTEMP		= 1<< 12, // 临字车牌
	Boon_DGREEN		= 1<< 13,	// 双层绿牌，农用车
	Boon_GUA			= 1<< 14,// “挂”车牌
}Boon_ALG_LPRPlateType_E;

typedef enum 
{
	Boon_VIDEO	= 0,		/// 视频版本，只适用于LPREngine调用
	Boon_FAST_VID = 1,		/// 预留
	Boon_ACC_VIDEO = 2,		/// 比普通视频版本可能更慢，但是更精确
	Boon_PICTURE	= 8,		/// 单张版本
	Boon_FAST_PIC = 9,		/// 快速单张版本
	Boon_FAST_PIC2= 10,		/// 更快速单张版本
	Boon_FAST_PIC3= 11,		/// 非常快速单张版本
	Boon_FAST_PIC4= 12,		/// 超快速单张版本
}Boon_ALG_LPRVersion_E;

typedef enum 
{
	Boon_ALG_LOGO_UNKNOWN     = 0,
	Boon_ALG_LOGO_VOLKSWAGEN	= 1,	//Volkswagen(福斯/大众)
	Boon_ALG_LOGO_HONDA		= 2,	//Honda 本田
	Boon_ALG_LOGO_TOYOTA		= 3,	//Toyota 丰田
	Boon_ALG_LOGO_DONGFENG	= 4,	//DongFeng(东风)
	Boon_ALG_LOGO_FAWCAR		= 5,	//First Automobile Works(一汽)
	Boon_ALG_LOGO_BUICK		= 6,	//别克
	Boon_ALG_LOGO_SUZUKI		= 7,	//Suzuki 铃木
	Boon_ALG_LOGO_CITROEN		= 8,	//Citroen 雪铁龙
	Boon_ALG_LOGO_KIA			= 9,	//Kia 起亚
	Boon_ALG_LOGO_XIALI		= 10,	//夏利（Xiali）。
	Boon_ALG_LOGO_AUDI		= 11,	//奥迪
	Boon_ALG_LOGO_HYUNDAI		= 12,	//Hyundai 现代
	Boon_ALG_LOGO_SGMW		= 13,	//上海通用五菱：SGMW
	Boon_ALG_LOGO_CHEERY		= 14,	//奇瑞汽车：Chery Automobile Corporation
	Boon_ALG_LOGO_MAZDA		= 15,	//Mazda 马自达
	Boon_ALG_LOGO_HAFEI		= 16,	//哈飞
	Boon_ALG_LOGO_CCAG		= 17,	//重庆长安
	Boon_ALG_LOGO_NISSAN		= 18,	//Nissan 日产
	Boon_ALG_LOGO_GREATWALL	= 19,	//GreatWall(长城)
	Boon_ALG_LOGO_BUILDYD		= 20,	//比亚迪build your dreams
	Boon_ALG_LOGO_FORD		= 21,	//Ford 福特
	Boon_ALG_LOGO_CHEVROLET	= 22,	//雪佛兰
	Boon_ALG_LOGO_BAOJUN		= 23,	//宝骏
	Boon_ALG_LOGO_BENZ		= 24,	//奔驰	
	Boon_ALG_LOGO_EMGRAND		= 25,	//帝豪
	Boon_ALG_LOGO_LEXUS		= 26,	//Lexus 雷克萨斯(凌志)	
	Boon_ALG_LOGO_MG			= 27,	//名爵
	Boon_ALG_LOGO_BMW			= 28,	//宝马
	Boon_ALG_LOGO_PEUGEOT		= 29,	//Peugeot 标致	
	Boon_ALG_LOGO_PEUGEOT2	= 30,	//Peugeot 标致
	Boon_ALG_LOGO_HAIMA		= 31,	//海马	
	Boon_ALG_LOGO_ZHONGHUA	= 32,	//中华
	Boon_ALG_LOGO_SKODA		= 33,	//斯柯达
	Boon_ALG_LOGO_SOUTHEAST	= 34,	//东南
	Boon_ALG_LOGO_CROWN		= 35,	//皇冠
	Boon_ALG_LOGO_JINBEI		= 36,	//金杯
	Boon_ALG_LOGO_MITSUBISHI	= 37,	//Mitsubishi 三菱	
	Boon_ALG_LOGO_ROEWE		= 38,	//荣威
	Boon_ALG_LOGO_GEELY		= 39,	//吉利
	Boon_ALG_LOGO_ENGLONCAR	= 40,	//英伦
	Boon_ALG_LOGO_GLEAGLE		= 41,	//全球鹰
}Boon_ALG_LPRVehicleBrand_E;

// 输入图像的颜色空间
typedef enum 
{
	Boon_CS_RGB24	= 0,
	Boon_CS_RGB565	= 1,
	Boon_CS_RGB555	= 2,
	Boon_CS_RGB32	= 3,	/// 以下暂不支持
	Boon_CS_GRAY		= 4,
	Boon_CS_YV12		= 8,
	Boon_CS_YV16		= 16,
	Boon_CS_YUY2		= 32,
	Boon_CS_YUV      = 64,
	Boon_CS_YUV420PLAN  = 33,    //YUV420平面
	Boon_CS_YUV420PACK  = 34,    //YUV420打包
	Boon_CS_YUV422PLAN  = 35,    //YUV422平面
	Boon_CS_YUV422PACK  = 36,    //YUV422打包
	Boon_CS_YUV444PLAN  = 37,    //YUV444平面
	Boon_CS_YUV444PACK  = 38,    //YUV444打包
	Boon_CS_YUV4208127  = 39     //YUV4208127格式	
}Boon_ALG_LPRColorSpace_S;

//目前所支持的车型，
typedef enum
{
	Boon_VT_UNKOWN = 0,    //未知车型
	Boon_VT_BUS = 1,    //公交和大客车
	Boon_VT_CAR = 2,    //小汽车
	Boon_VT_TRUCK = 3,  //货车，包括大货和小货
	Boon_VT_VAN = 4,   //面包车
	Boon_VT_BIG_TRUCK = 5,//大货车、
	Boon_VT_SMALL_TRUCK = 6,//小货车
	Boon_VT_NOMOTOR = 7,//非机动车
	Boon_VT_PERSON = 8 //行人	
}Boon_ALG_LPRVehicleType_E;

//目前所支持的违法类型，
typedef enum{
	Boon_IT_UNKOWN = 0,     //未知类型
	Boon_IT_NOSAFETYBELT=1,    //不系安全带
	Boon_IT_PHONE =2          //打电话
}Boon_ALG_LPRIllgalType_E;
//目前算法所有支持的类型
typedef enum{
	Boon_AT_UNKOWN = 0,     //未知类型
	Boon_AT_FACEEXTRACK = 1,//人脸提取
	Boon_AT_VEHICLEREC = 2,//车型识别
	Boon_AT_VEHICLELOGREC =4,//车标识别
	Boon_AT_ILLGALDETECT =8//违法类型检测
}Boon_ALG_LPRAlgorithmType_E;
/*
static const char * pacChineseCharacter[] =
{
	"津","京","苏","云","冀","晋","蒙","辽","吉","黑","沪","浙","皖","闽","赣",
	"鲁","豫","鄂","湘","粤","桂","琼","川","贵","藏","陕","甘","青","宁","新",
	"渝","军","海","空","沈","北","济","南","广","成","兰","警","使","领","学",
	"试","挂","临","境","港","澳","WJ","消","边","水","警","电","林","通","金"
};
*/
/*
static  const char *pacAlphaCharacter[] =
{
	"0","1","2","3","4","5","6","7","8","9",
	"A","B","C","D","E","F","G","H","I","J",
	"K","L","M","N","O","P","Q","R","S","T",
	"U","V","W","X","Y","Z","学","警","挂",
	"港","澳","临","超","试","领"
};
*/
#endif
