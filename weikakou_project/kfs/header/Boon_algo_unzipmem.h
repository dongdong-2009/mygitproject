
#ifndef _BOON_UNZIPMEM_H_
#define _BOON_UNZIPMEM_H_


#include "Boon_algo_type.h"
#ifdef __cplusplus
extern "C"      //�����Էָ�ģ��ĵ��ýӿ�ΪC��ʽ
{
#endif

/**********************************************************
	���ƣ�	BoonAlgo_Unzip

	���ܣ�	��ѹ��

	������	BoonUint8 * pucZipData		ѹ������
	  		BoonInt32 _iZipDataLen 		ѹ�����ݳ���
			BoonUint8 *_pucUnzipData		��ѹ���ݴ洢ָ��
			BoonInt32 _iSeg				Ӧ���ڴ��


	���أ�	��ȷ����ѹ�����ݳ���
			���� 0

	������
**********************************************************/
Boon_EXPORTS BoonInt32 BoonAlgo_Unzip(BoonUint8 * pucZipData ,BoonInt32 _iZipDataLen, BoonUint8 *_pucUnzipData,BoonInt32 _iSeg );

#ifdef __cplusplus
}
#endif
#endif
