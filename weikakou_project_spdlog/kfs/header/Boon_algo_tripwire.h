
#ifndef _Boon_algo_TRIPmeter_H__
#define _Boon_algo_TRIPmeter_H__

#include "Boon_algo_type.h"
#include "Boon_algo_tripwire_param.h"
#include "Boon_algo_tripwire_private.h"
#include "Boon_algo_ivs_result.h"
#include "ivs_gmm.h"

#ifdef __cplusplus
extern "C"
{
#endif

	/********************************************************
	���ƣ�	BOONAlgo_TRIP_Creat
	���ܣ�	�����㷨����
	������	BoonInt32  _iSeg    �㷨ռ���ڴ��
	BoonChar  *_pcKey   �㷨��Կ(128���ֽ�)
	���أ�  ��ȷ   ����ָ��
	����    NULL
	������	��
	*********************************************************/
	Boon_HANDLE BoonAlgo_TRIP_Creat(BoonInt32  _iSeg, BoonChar * _pcKey);
	/**************************************************************************
	Function:		BOONAlgo_TRIP_Creat
	Description:	��������ģ�鲢��ʼ��
	Returns:   	Boon_ALG_STATUS_E ����״̬
	Parameter: 	Boon_HANDLE _hModule ģ����
	**************************************************************************/
	Boon_EXPORTS BoonInt32 BoonAlgo_TRIP_Init(BoonInt32 _iImgW, BoonInt32 _iImgH);
	/**************************************************************************
	Function:		BOONAlgo_TRIP_Release
	Description:	��ֹ����ģ�鲢�ͷ��ڴ�
	Returns:   	Boon_ALG_STATUS_E ����״̬
	Parameter: 	Boon_HANDLE _hModule ģ����
	**************************************************************************/
	Boon_EXPORTS BoonInt32 BoonAlgo_TRIP_Release(Boon_HANDLE _hModule);
	/**************************************************************************
	Function:		BOONAlgo_TRIP_Process
	Description:	����һ��ͼ��
	Returns:   	Boon_ALG_STATUS_E ����״̬
	Parameter: 	Boon_HANDLE _hModule ģ����
	Parameter: 	BOONUint8 * _pucImage �Ҷ�ͼ��ָ��
	**************************************************************************/
	Boon_EXPORTS BoonInt32 BoonAlgo_TRIP_Process(Boon_ALG_IMAGE3_S* _pstImage);

	/**************************************************************************
	Function:		BOONAlgo_TRIP_GetResults
	Description:	��ȡ������
	Returns:   	Boon_ALG_STATUS_E ����״̬
	Parameter: 	Boon_HANDLE _hModule ģ����
	Parameter: 	Boon_ALG_RESULT_S * _pstResult ������
	**************************************************************************/
	Boon_EXPORTS BoonInt32 BoonAlgo_TRIP_GetResults(char *plate);
	/**************************************************************************
	Function:		BOONAlgo_TRIP_GetLibInfo
	Description:	��ȡ�㷨�İ汾��Ϣ
	Returns:   	Boon_ALG_STATUS_E ����״̬
	Parameter: 	Boon_ALGO_LIB_INFO_S * _pstLibInfo ����Ϣ
	**************************************************************************/
	Boon_EXPORTS BoonInt32 BoonAlgo_TRIP_GetLibInfo( Boon_ALG_TRIP_LIB_INFO_S *_pstLibInfo);

#ifdef __cplusplus
}
#endif

#endif // _Boon_algo_TRIPmeter_H__
