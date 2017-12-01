#ifndef _LPR_H_
#define _LPR_H_

#ifdef __cplusplus
Boon_EXPORTS "C"
{
#endif
#include  "Boon_algo_lpr_struct.h"

extern     int   BoonAlgo_LPR_Init(void* _hModule,   int _iWidth, int _iHeight );
extern   int BoonAlgo_LPR_Process(void* _hModule, Boon_ALG_IMAGE_S * _pstInput,Boon_ALG_LPROutput_S *_pstLPRDetect,Boon_ALG_LPROutputMulti_S* _pstOutput);
extern 	   int  BoonAlgo_LPR_Release(void* _hModule);
extern   void *  BoonAlgo_LPR_Create(int  _iSeg,char * _pcKey);
extern  int      BoonAlgo_LPR_Get_Version(Boon_HANDLE _hModule, unsigned char  *_pucVersion);
#ifdef __cplusplus
}
#endif
#endif
