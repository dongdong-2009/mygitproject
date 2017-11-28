/********************************************************************
    Copyright (C), 1994-2012, 山东博昂信息科技有限公司	
    文件名称: 	 Boon_algo_list.h
    文件描述:    BOON算法部  链表操作头文件
    文件作者:    BOON算法部
    修改历史:	 20:12:6:28   规范化   孙希伟
	            
*********************************************************************/
#ifndef  _Boon_ALGO_LIST_H_
#define  _Boon_ALGO_LIST_H_

#ifdef __cplusplus
extern "C" {
#endif
#include	"Boon_algo_type.h"

typedef struct CT_CC
{
	BoonInt32		iID;
	BoonInt32		iArea;
	BoonInt32		iXSum;
	BoonInt32		iYSum;
	BoonInt32		iXMin;
	BoonInt32		iYMin;
	BoonInt32		iXMax;
	BoonInt32		iYMax;
	BoonInt32		iSeedx;
	BoonInt32		iSeedy;
	struct CT_CC * pstNext;
	struct CT_CC * pstPrev;
} Boon_ALG_CT_CCLIST_S;

/**********************************************************
	名称：	LIST_AddNode

	功能：	添加一链表节点

	参数：	BoonInt32 _iSeg						添加节点内存段
			Boon_ALG_CT_CCLIST_S * _pstCurPrt		添加节点位置指针

	返回：	Boon_ALG_CT_CCLIST_S *				添加节点指针
	其他：
**********************************************************/
Boon_EXPORTS  Boon_ALG_CT_CCLIST_S * LIST_AddNode(BoonInt32 _iSeg, Boon_ALG_CT_CCLIST_S * _pstCurPrt);

/**********************************************************
	名称：	LIST_DelNode

	功能：	删除一链表节点

	参数：	BoonInt32 _iSeg						删除节点内存段
			Boon_ALG_CT_CCLIST_S * _pstCurPrt		删除节点位置指针

	返回：	
	其他：
**********************************************************/
Boon_EXPORTS  BoonVoid	LIST_DelNode(BoonInt32 _iSeg,Boon_ALG_CT_CCLIST_S *_pstCurPrt);


/**********************************************************
	名称：	LIST_DelAllNode

	功能：	删除双向链表内的所有节点（头尾除外）

	参数：	BoonInt32 _iSeg						删除节点内存段
			Boon_ALG_CT_CCLIST_S * _pstCurPrt		删除节点位置指针

	返回：	
	其他：
**********************************************************/
Boon_EXPORTS  BoonVoid	LIST_DelAllNode(BoonInt32 _iSeg,Boon_ALG_CT_CCLIST_S *_pstCurPrt);

#ifdef __cplusplus
}
#endif
#endif 
