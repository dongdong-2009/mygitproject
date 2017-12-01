/********************************************************************
    Copyright (C), 1994-2012, ɽ��������Ϣ�Ƽ����޹�˾	
    �ļ�����: 	 Boon_algo_list.h
    �ļ�����:    BOON�㷨��  �������ͷ�ļ�
    �ļ�����:    BOON�㷨��
    �޸���ʷ:	 20:12:6:28   �淶��   ��ϣΰ
	            
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
	���ƣ�	LIST_AddNode

	���ܣ�	���һ����ڵ�

	������	BoonInt32 _iSeg						��ӽڵ��ڴ��
			Boon_ALG_CT_CCLIST_S * _pstCurPrt		��ӽڵ�λ��ָ��

	���أ�	Boon_ALG_CT_CCLIST_S *				��ӽڵ�ָ��
	������
**********************************************************/
Boon_EXPORTS  Boon_ALG_CT_CCLIST_S * LIST_AddNode(BoonInt32 _iSeg, Boon_ALG_CT_CCLIST_S * _pstCurPrt);

/**********************************************************
	���ƣ�	LIST_DelNode

	���ܣ�	ɾ��һ����ڵ�

	������	BoonInt32 _iSeg						ɾ���ڵ��ڴ��
			Boon_ALG_CT_CCLIST_S * _pstCurPrt		ɾ���ڵ�λ��ָ��

	���أ�	
	������
**********************************************************/
Boon_EXPORTS  BoonVoid	LIST_DelNode(BoonInt32 _iSeg,Boon_ALG_CT_CCLIST_S *_pstCurPrt);


/**********************************************************
	���ƣ�	LIST_DelAllNode

	���ܣ�	ɾ��˫�������ڵ����нڵ㣨ͷβ���⣩

	������	BoonInt32 _iSeg						ɾ���ڵ��ڴ��
			Boon_ALG_CT_CCLIST_S * _pstCurPrt		ɾ���ڵ�λ��ָ��

	���أ�	
	������
**********************************************************/
Boon_EXPORTS  BoonVoid	LIST_DelAllNode(BoonInt32 _iSeg,Boon_ALG_CT_CCLIST_S *_pstCurPrt);

#ifdef __cplusplus
}
#endif
#endif 
