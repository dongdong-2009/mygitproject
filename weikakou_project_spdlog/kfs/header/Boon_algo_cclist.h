#ifndef __Boon_ALGO_CCLIST_H__
#define __Boon_ALGO_CCLIST_H__

/********************************************************************
    Copyright (C), 1994-2012, 山东博昂信息科技有限公司
    文件名称: 	  Boon_algo_publicfunc.h
    文件描述:    BOON算法部-团块检测模块头文件
    文件作者:    孙希伟
    修改历史:	  2013.04.03   	create

*********************************************************************/

#include	"Boon_algo_type.h"

#ifdef __cplusplus
extern "C" {
#endif


extern BoonInt32	GLOBAL_iAlgoRecType;
extern BoonInt32  GLOBAL_SEG_BLOCK_WIDTH;
extern BoonInt32  GLOBAL_SEG_BLOCK_HEIGHT;
extern BoonInt32  GLOBAL_SEG_MAXMEMSIZE;
typedef struct
{
	BoonInt32		x;
	BoonInt32		y;
	BoonInt32		iWidth;
	BoonInt32		iHeight;
	BoonInt32		iArea;
}Boon_ALG_CCLISTRECT_S;      //团块结果结构体

/********************************************************************************
	名称：	CCLIST_RectXSort

	功能：	团块矩形坐标X方向排序

	参数：	Boon_CClistRect *_pstRect		输入团块结构体指针
	  		BoonInt32 _iNum				输入待排序团块数量

	返回：	无

	其他：      在对比不同平台的团块检测结果时，用到此函数对团块坐标进行排序，
			团块的坐标x,y及宽高width,height顺序，可以根据需要进行修改比较大小条件。
*********************************************************************************/
Boon_EXPORTS  BoonVoid  CCLIST_RectXSort(Boon_ALG_CCLISTRECT_S *_pstRect, BoonInt32 _iNum);

/********************************************************************************
	名称：	CCLIST_RectYSort

	功能：	团块矩形坐标Y方向排序

	参数：	Boon_CClistRect *_pstRect		输入团块结构体指针
	  		BoonInt32 _iNum				输入待排序团块数量

	返回：	无

	其他：      在对比不同平台的团块检测结果时，用到此函数对团块坐标进行排序，
			团块的坐标x,y及宽高width,height顺序，可以根据需要进行修改比较大小条件。
*********************************************************************************/
Boon_EXPORTS  BoonVoid  CCLIST_RectYSort(Boon_ALG_CCLISTRECT_S *_pstRect, BoonInt32 _iNum);

/********************************************************************************
	名称：	CCLIST_AreaRectGet

	功能：	团块检测函数

	参数：	Boon_CClistRect	*_pstRectResult		输出：团块检测结果结构体数组
	        BoonInt32			*_piRectNum			输出：团块检测结果结构体数组个数，不超过最大团块数量限制
			BoonInt32			_iLinkNum			输入连通区域，通常选择4连通或8连通，即赋值4或8
	        BoonInt8 *_pucBinaryImg			输入原始二值图像
	        BoonInt32 _iMinArea				输入团块最小面积
	        BoonInt32 _iImgWidth				输入原始二值图像宽度
	        BoonInt32 _iImgHeight				输出原始二值图像高度
	返回：	BoonTrue							团块检测成功
			BoonFalse							团块检测失败

	其他：      注意输入存储团块结构体数组时，根据需要设置团块检测结果数量的最大值限制
*********************************************************************************/
Boon_EXPORTS  BoonBool  CCLIST_AreaRectGet(Boon_ALG_CCLISTRECT_S *_pstRectResult, BoonInt32 *_piRectNum, BoonInt32 _iLinkNum, BoonUint8 *_pucBinaryImg,  BoonInt32 _iMinArea, BoonInt32 _iImgWidth, BoonInt32 _iImgHeight);

 
#ifdef __cplusplus
}
#endif  /* extern "C" 跨平台移植*/

#endif
