/********************************************************************
	Copyright (C) ɽ��������Ϣ�Ƽ����޹�˾
	
	�ļ�����: 	Boon.h
	�ļ�����:	����ʶ��ͷ�ļ�
				
	�ļ����ߣ�	��ϣΰ
	�޸���ʷ��	2015.10.14 creat V1.0.001 
*********************************************************************/
#ifndef _LPR_H_
#define _LPR_H_
#ifdef __cplusplus
Boon_EXPORTS "C"
{
#endif
#include ""
extern __declspec(dllexport)	void * BoonAlgo_TRIP_Creat(int  _iSeg, char * _pcKey);
	
extern __declspec(dllexport) int BoonAlgo_TRIP_Init(void * _hModule, Boon_ALG_TRIP_RULE_PARA_S *_pstURPPara,
		int _iImgW, int _iImgH);
	
extern __declspec(dllexport)	 int BoonAlgo_TRIP_Release(void * _hModule);

extern __declspec(dllexport) int BoonAlgo_TRIP_Process(void * _hModule, Boon_ALG_IMAGE3_S* _pstImage);

extern __declspec(dllexport) int BoonAlgo_TRIP_GetResults(void * _hModule, Boon_ALG_IVS_RESULT_SET_S * _pstResult);
#ifdef __cplusplus
}
#endif
#endif
