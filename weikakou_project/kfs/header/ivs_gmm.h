#ifndef _IVS_GMM_H_
#define _IVS_GMM_H_

//#define ONLY_GMM //用于背景建模

#ifndef ONLY_GMM
#include "ivs_track.h"
#else
#include "Boon_algo_type.h"
#define IVS_STATUS_E			BoonInt32			/*代码简洁起见，这里转一次*/
//typedef BoonVoid IVS_TRACK_RECT_S;
#endif


#ifdef __cplusplus
extern "C"
{
#endif

#define FLT_EPSILON			1.192092896e-07F
#define Boon_MAX_FGRECTNUM	256	

#ifndef Boon_ABS_REGION
#define Boon_ABS_REGION				65536						/* 适用于求距离、亮度差值的绝对值 */
#define Boon_ABS_ZEROPOS				Boon_ABS_REGION / 2
#endif
/*Default parameters of GMM*/
#define IVS_GMM_BACKGROUND_THRESHOLD     0.9f			/*背景更新权重*/
#define IVS_GMM_SBoon_THRESHOLD            25			/*lambda值 */
#define IVS_GMM_WINDOW_SIZE              100			/*学习率*/
#define IVS_GMM_NGAUSSIANS               3				/*Mode最大个数*/
#define IVS_GMM_WEIGHT_INIT              0.3			/*初始权重*/
#define IVS_GMM_SIGMA_INIT               30				/*初始分割系数*/
#define IVS_GMM_MINAREA                  15.f			/*最小更新区域*/
#define IVS_GMM_MAX_BACKLEAN			 10				/*最大背景学习帧数*/

typedef BoonInt32 IVS_STATUS_E;

/*每个像素的GMM信息*/
typedef struct
{		
	BoonInt32			iGetBGTime;							/*背景的学习时间*/
	BoonFloat32       af32Weight[IVS_GMM_NGAUSSIANS];		/*各Model权重	*/		
	BoonFloat32       af32Variance[IVS_GMM_NGAUSSIANS];	/*各Model方差*/
	BoonFloat32       af32Mean[IVS_GMM_NGAUSSIANS];		/*各Model均值*/
	BoonFloat32		af32SortKey[IVS_GMM_NGAUSSIANS];	/*各Model排序关键字*/
	BoonInt32			aiOrder[IVS_GMM_NGAUSSIANS];		/*各Model次序号*/

	/*新增*/
	BoonInt32			iMvStartFrm;						/*运动目标标识*/
	BoonInt32			iMvConsistNum;						/*持续帧数*/
	BoonInt32			iStcStartFrm;						/*静止目标开始时间*/
	BoonInt32			iStcConsistNum;						/*静止目标持续帧数*/
} IVS_GMM_INFO_S;

/*GMM使用的图像指针*/
typedef struct
{
	BoonUint8*		pucSmoothImg;		/*平滑后的灰度图像*/
	BoonUint8*		pucDiffImg;			/*帧差图像*/
	BoonUint8*		pucFgImg;			/*前景图像*/
	BoonUint8*		pucSnImg;			/*连通区域检测得到的标号图像*/
	BoonUint8*		pucBgImg;			/*背景图像*/
	BoonUint8*		pucPrevImg;			/*上一帧灰度图像*/
	BoonUint8*        pucBoundaryImg;     /*外接多边形二值图，区域内为1，区域外为0*/
} IVS_GMM_IMGBuff_S;

/*混高斯背景建模模块参数*/
typedef struct
{
	BoonInt32			iTgtMaxArea;		/*最大区域*/	
	BoonInt32			iTgtMinArea;		/*最小区域*/
	BoonInt32			iTgtMaxFrame;		/*最大帧数*/
	BoonInt32			iTgtMergeRate;		/*合并系数*/
	BoonInt32			iWindowsSize;		/*学习率*/
	BoonInt32			iStilltoBgTime;		/*静止目标融入背景时间*/
	BoonFloat32		f32VarMin;			/*最小方差*/
	BoonFloat32		f32VarMax;			/*最大方差*/
	BoonFloat32		f32BgTh;			/*背景更新权重门限*/
} IVS_GMM_PARA_S;

/*混高斯背景建模模块高级参数*/
typedef struct
{
	BoonInt32			iTmp;
} IVS_GMM_ADVPARA_S;

/*使用TBB时的结构体*/
typedef struct
{
	BoonUint8*		pucFgImg;			/*前景图像指针（这里只是指针，不需要申请内存）*/
	BoonUint8*		pucBgImg;			/*背景图像指针（同上）*/
	BoonUint8*		pucCurrImg;			/*当前图像指针（同上）*/
	BoonUint8*		pucDiffImg;			/*差分图像指针（同上）*/
	BoonInt32			iHeight;			/*图像高度*/
	BoonInt32			iWidth;				/*图像宽度*/
	BoonInt32			iStillTime;			/**/
	BoonInt32			iFrameNo;			/*帧号*/
	BoonInt32			iModelNum;			/*高斯个数*/
	BoonFloat32		f32BgTh;			/*权重判决门限*/
	BoonFloat32		f32Alpha;			/**/
	BoonFloat32		f32VarMin;
	BoonFloat32		f32VarMax;
	BoonFloat32		f32VarRate;
	IVS_GMM_INFO_S* pstGmmInfo;			/*各像素点模型指针（这里只是指针，不需要申请内存）*/
} IVS_GMM_TBB_PARA_S;

/*混高斯背景建模模块结构体*/
typedef struct 
{
	BoonInt32			iFrameNo;			/*帧号*/
	BoonInt32			iHistory;			/**/
	BoonInt32			iMixtures;			/*Model最大个数*/
	BoonFloat32		f32VarTh;			/*方差门限*/
	BoonFloat32		f32BgRatio;			/**/
	BoonFloat32		f32NoiseSigma;
	BoonFloat32		f32InitVar;			/*初始方差*/
	BoonFloat32		f32InitWeight;		/*初始权重*/
	BoonFloat32		f32InitSortKey;		/*初始次序*/

	BoonInt32			iFgBigNum;			/*变化*/
	BoonFloat32		f32VarCorrectRate;	/*方差矫正系数*/
	BoonFloat32		f32GrayAve;			/*图像灰度均值，alpha滤波结果*/
		
	IVS_GMM_PARA_S			stGmmPara;	/*GMM设置参数*/
	IVS_GMM_INFO_S*			pstGmmInfo;	/*每个像素的GMM信息指针*/
	IVS_GMM_IMGBuff_S*		pstImgBuff;	/*GMM使用的图像指针*/
#ifdef HAVE_TBB
	IVS_GMM_TBB_PARA_S*		pstTbbPara;		/*使用TBB时的结构体*/
#endif
	BoonInt32    iImgWidth;
	BoonInt32    iImgHeight;

} IVS_GMM_S;
typedef   IVS_GMM_S  * GMM_Handle;



/***************************************************************************************

函数名称：IVS_GMM_Create

功能：创建算法引擎

参数：	Seg	算法内部动态申请内存的段地址
Key 创建引擎所需的密钥

返回值：创建成功返回引擎指针
创建失败返回空指针

其他：

***************************************************************************************/
Boon_EXPORTS Boon_HANDLE  IVS_GMM_Create(BoonInt32  _iSeg,BoonChar * _pcKey);

/**********************************************************
	名称：	IVS_GMM_Init

	功能：	混高斯背景建模——初始化

	参数：	Boon_HANDLE                _hModule		GMM模块指针
			BoonInt32				     _iFrmInterval	跳帧帧数
			BoonInt32				     _iImgWidth		图像宽度
			BoonInt32				     _iImgHeight    图像高度

	返回：	IVS_STATUS_E		Boon_ALG_OK/Boon_ALG_FAIL
**********************************************************/
Boon_EXPORTS IVS_STATUS_E IVS_GMM_Init(Boon_HANDLE _hModule, BoonInt32 _iFrmInterval, BoonInt32 _iImgWidth, BoonInt32 _iImgHeight);

/**********************************************************
	名称：	IVS_GMM_Process

	功能：	混高斯背景建模——处理函数

	参数：	Boon_HANDLE     _hModule		GMM模块指针
	  		IVS_TRACK_RECT_S*	_pstFgRect		前景目标框
			Boon_ALG_POLYGON_REGION_S* _pstBoundary   需要建模的区域
			BoonInt32				_iImgWidth		图像宽度
			BoonInt32				_iImgHeight		图像高度

	返回：	BoonInt32				iRectNum		前景目标数
**********************************************************/
Boon_EXPORTS BoonInt32 IVS_GMM_Process(Boon_HANDLE _hModule, BoonUint8* _pucSrc, 
#ifndef ONLY_GMM
						IVS_TRACK_RECT_S* _pstFgRect, 
#endif
						Boon_ALG_POLYGON_REGION_S* _pstBoundary, BoonInt32 _iImgWidth, BoonInt32 _iImgHeight);
/**********************************************************
	名称：	IVS_GMM_PostProcess
	功能：	混高斯背景建模——后处理
	参数：	IVS_MOVE_S*			_pstBgModel		背景模型
			IVS_TRACK_S*		_pstTrackInfo	跟踪信息
			IVS_TRACK_MLYRECT_S* _pstRect		目标框
			BoonInt32				_iRectNum		前景个数
			BoonInt32				_iImgW			图像宽度
			BoonInt32				_iImgH			图像高度
	返回：	Boon_ALG_OK
**********************************************************/
#ifndef ONLY_GMM
Boon_EXPORTS IVS_STATUS_E IVS_GMM_PostProcess(IVS_GMM_S* _pstGmm, IVS_TRACK_S* _pstTrackInfo, 
								 IVS_TRACK_RECT_S* _pstRect, BoonInt32 _iRectNum, 
								 BoonInt32 _iImgW, BoonInt32 _iImgH);
#endif

/**********************************************************
	名称：	IVS_GMM_Release

	功能：	混高斯背景建模——释放

	参数：	Boon_HANDLE _hModule	GMM模块指针

	返回：	IVS_STATUS_E		Boon_ALG_OK
**********************************************************/
Boon_EXPORTS IVS_STATUS_E  IVS_GMM_Release(Boon_HANDLE _hModule);


#ifdef __cplusplus
}
#endif

#endif	/*_IVS_GMM_H_*/
