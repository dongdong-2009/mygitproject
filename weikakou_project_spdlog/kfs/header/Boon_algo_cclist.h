#ifndef __Boon_ALGO_CCLIST_H__
#define __Boon_ALGO_CCLIST_H__

/********************************************************************
    Copyright (C), 1994-2012, ɽ��������Ϣ�Ƽ����޹�˾
    �ļ�����: 	  Boon_algo_publicfunc.h
    �ļ�����:    BOON�㷨��-�ſ���ģ��ͷ�ļ�
    �ļ�����:    ��ϣΰ
    �޸���ʷ:	  2013.04.03   	create

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
}Boon_ALG_CCLISTRECT_S;      //�ſ����ṹ��

/********************************************************************************
	���ƣ�	CCLIST_RectXSort

	���ܣ�	�ſ��������X��������

	������	Boon_CClistRect *_pstRect		�����ſ�ṹ��ָ��
	  		BoonInt32 _iNum				����������ſ�����

	���أ�	��

	������      �ڶԱȲ�ͬƽ̨���ſ�����ʱ���õ��˺������ſ������������
			�ſ������x,y�����width,height˳�򣬿��Ը�����Ҫ�����޸ıȽϴ�С������
*********************************************************************************/
Boon_EXPORTS  BoonVoid  CCLIST_RectXSort(Boon_ALG_CCLISTRECT_S *_pstRect, BoonInt32 _iNum);

/********************************************************************************
	���ƣ�	CCLIST_RectYSort

	���ܣ�	�ſ��������Y��������

	������	Boon_CClistRect *_pstRect		�����ſ�ṹ��ָ��
	  		BoonInt32 _iNum				����������ſ�����

	���أ�	��

	������      �ڶԱȲ�ͬƽ̨���ſ�����ʱ���õ��˺������ſ������������
			�ſ������x,y�����width,height˳�򣬿��Ը�����Ҫ�����޸ıȽϴ�С������
*********************************************************************************/
Boon_EXPORTS  BoonVoid  CCLIST_RectYSort(Boon_ALG_CCLISTRECT_S *_pstRect, BoonInt32 _iNum);

/********************************************************************************
	���ƣ�	CCLIST_AreaRectGet

	���ܣ�	�ſ��⺯��

	������	Boon_CClistRect	*_pstRectResult		������ſ������ṹ������
	        BoonInt32			*_piRectNum			������ſ������ṹ���������������������ſ���������
			BoonInt32			_iLinkNum			������ͨ����ͨ��ѡ��4��ͨ��8��ͨ������ֵ4��8
	        BoonInt8 *_pucBinaryImg			����ԭʼ��ֵͼ��
	        BoonInt32 _iMinArea				�����ſ���С���
	        BoonInt32 _iImgWidth				����ԭʼ��ֵͼ����
	        BoonInt32 _iImgHeight				���ԭʼ��ֵͼ��߶�
	���أ�	BoonTrue							�ſ���ɹ�
			BoonFalse							�ſ���ʧ��

	������      ע������洢�ſ�ṹ������ʱ��������Ҫ�����ſ��������������ֵ����
*********************************************************************************/
Boon_EXPORTS  BoonBool  CCLIST_AreaRectGet(Boon_ALG_CCLISTRECT_S *_pstRectResult, BoonInt32 *_piRectNum, BoonInt32 _iLinkNum, BoonUint8 *_pucBinaryImg,  BoonInt32 _iMinArea, BoonInt32 _iImgWidth, BoonInt32 _iImgHeight);

 
#ifdef __cplusplus
}
#endif  /* extern "C" ��ƽ̨��ֲ*/

#endif
