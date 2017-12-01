#ifndef _Boon_ALGO_PUBLICFUNC_H_
#define _Boon_ALGO_PUBLICFUNC_H_
/********************************************************************
    Copyright (C), 1994-2012, ɽ��������Ϣ�Ƽ����޹�˾	
    �ļ�����: 	 Boon_ALGo_public_func.h 
    �ļ�����:    BOON�㷨��-���ú���ͷ�ļ�
    �ļ�����:    ��ϣΰ
    �޸���ʷ:	 17:12:2012   14:08	create 
	            
*********************************************************************/
#include	"Boon_algo_type.h"
#include	"Boon_algo_log.h"


#ifdef __cplusplus
Boon_EXPORTS "C"
{
#endif
 static int sdiv_table[256];
  static int hdiv_table180[256];
static int initialized;
//#if ( defined( DEBUG_PRINT_ENABLE ) && defined( LOCAL_DBG_PRT_EN ) )
	#define 	DEBUG_COM_PRINT			BoonAlgo_LOG_AddLog
//#else
//	#define 	DEBUG_COM_PRINT		
//#endif

#if ( defined( DEBUG_PRINT_ENABLE ) && defined( LOCAL_DBG_PRT_EN ) && defined( LOCAL_TIME_PRT_EN ) )
	#define 	DEBUG_GET_TIME_MS(x)	Public_GetTimeMs2(x)
#else
	#define 	DEBUG_GET_TIME_MS(x)		
#endif

#define		MaxValue(a,b)            (((a) > (b)) ? (a) : (b))		//
#define		MinValue(a,b)            (((a) < (b)) ? (a) : (b)) 
	
#define CV_SUM_OFFSETS( p0, p1, p2, p3, rect, step )                      \
	/* (x, y) */                                                          \
	(p0) = (rect).x + (step) * (rect).y;                                  \
	/* (x + w, y) */                                                      \
	(p1) = (rect).x + (rect).width + (step) * (rect).y;                   \
	/* (x + w, y) */                                                      \
	(p2) = (rect).x + (step) * ((rect).y + (rect).height);                \
	/* (x + w, y + h) */                                                  \
	(p3) = (rect).x + (rect).width + (step) * ((rect).y + (rect).height);

#define CV_SUM_PTRS( p0, p1, p2, p3, sum, astRect, step )                 \
	/* (x, y) */                                                          \
	(p0) = sum + (astRect).x + (step) * (astRect).y,                      \
	/* (x + w, y) */                                                      \
	(p1) = /*sum + (astRect).x + (step) * (astRect).y*/ (p0) + (astRect).width, \
	/* (x + w, y) */                                                      \
	(p2) = /*sum + (astRect).x + (step) * ((astRect).y + (astRect).height),*/ \
	       (p0) + (step) * ((astRect).height),\
	/* (x + w, y + h) */                                                  \
	(p3) = /*sum + (astRect).x + (step) * ((astRect).y + (astRect).height)*/ (p2) + (astRect).width

#define CALC_SUM_(p0, p1, p2, p3, offset) \
	((p0)[offset] - (p1)[offset] - (p2)[offset] + (p3)[offset])

	
typedef union 
{
	struct
	{
		BoonUint32		uiTimeLow;
		BoonUint32		uiTimeHigh;
	};
	BoonUint64   ui64Time;
}SYSTIME_S;

typedef struct 
{
	BoonInt32   iUsedMem;
	BoonInt32   iUsedMaxMem;
	BoonInt32	  iMemChange;
}MEMINF_S;

typedef struct
{
	BoonUint32   u32PhyAddr;
	BoonUint8    *pu8VirAddr;
	BoonUint32    u32Size;
	BoonInt32     s32PoolID;	
	BoonUint32    u32Blk;
	BoonInt32     s32MyPoolsID;	
	BoonUint32    u32MyPoolsBlk;
	BoonUint32    u32CacheFlag;

	BoonUint32    u32ReallSize;
	BoonUint32    u32RealPhyAddr;
	BoonUint8    *pu8RealVirAddr;
}Boon_IVE_MEM_INFO_S;



Boon_EXPORTS	MEMINF_S   stMemInformation;
typedef enum
{
	 CHIP_ID  =	0,			//���DM8127Ӧ�ã�ȡ16�ֽ�ID��6�ֽ�
	 CUSTOM_ID = 1			//���DM8127Ӧ�ã���16�ֽ�ID���м��ܴ����õ�6�ֽ�
}DEVICE_ID_TYPE_E;

/********************************************************************
	���ƣ�	Public_ImageInterpolation

	���ܣ�	˫���Բ�ֵ������ͼ���һ��

	������	BoonUint8 *_pucSrcImage		ԭʼͼ��ָ��
	  		BoonUint8 *_pucDstImage  		��һ��ͼ��ָ��
			BoonInt32 _iSrcWidth			ԭʼͼ����
			BoonInt32 _iSrcHeight			ԭʼͼ��߶�
			BoonInt32 _iNewWidth			��һ��ͼ����
			BoonInt32 _iNewHeight			��һ��ͼ��߶�

	���أ�	Boon_ALG_OK		����ִ�гɹ�

	������	_uSrcImage��_uDstImageΪ����ص�ͼ������ָ�롣
*********************************************************************/

Boon_EXPORTS	BoonInt32 Public_ImageInterpolation(BoonUint8 *_pucSrcImage, BoonUint8 *_pucDstImage, BoonInt32 _iSrcWidth,BoonInt32 _iSrcHeight, BoonInt32 _iNewWidth, BoonInt32 _iNewHeight);
Boon_EXPORTS    BoonInt32 Public_ImageInterpolation1(BoonUint8 *_pucSrcImage, BoonUint8 *_pucDstImage, BoonInt32 _iSrcWidth,BoonInt32 _iSrcHeight, BoonInt32 _iNewWidth, BoonInt32 _iNewHeight);
/********************************************************************
	���ƣ�	Public_PointInPolygon

	���ܣ�	�жϵ��Ƿ��ڶ������

	������	Boon_ALG_POINT_S _ptSrc		                �������
	  		Boon_ALG_POLYGON_REGION_S _PolyRegion 		���������

	���أ�	1��ʾ����  0������
*********************************************************************/
Boon_EXPORTS	BoonInt32 Public_PointInPolygon(Boon_ALG_POINT_S _stPtSrc, Boon_ALG_POLYGON_REGION_S *_pstPolyRegion);

/********************************************************************
	���ƣ�	Public_GeBooneviceID

	���ܣ�  ��ȡ�㷨����ƽ̨оƬ�ڲ������к�

	������	BoonUint8 * pucID		     ��ȡ���кŵ����ָ������
			Boon_ALG_IDTYPE_E _eReadIdType   ��ȡָ�����͵�ID��

	���أ�	�� 
//Boon_EXPORTS  BoonVoid	Public_GeBooneviceID( BoonUint8 * _pucID );
*********************************************************************/
Boon_EXPORTS BoonVoid	Public_GeBooneviceID( BoonUint8 * _pucID ,DEVICE_ID_TYPE_E _eReadIdType);

/**********************************************************
	���ƣ�	Public_ImageGray

	���ܣ�	��RGBͼ��ҶȻ�

	������	BoonUint8 *_pucSrcImage		ԭʼ��ɫͼ��ָ��
	  		BoonUint8 *_pucDstImage  		�ҶȻ���ͼ��ָ��
			BoonInt32 _iWidth			    ͼ����
			BoonInt32 _iHeight			ͼ��߶�

	���أ�	��

	������	_uSrcImage��_uDstImageΪ����ص�ͼ������ָ�롣
**********************************************************/
BoonInt32 LPL_Filter3(BoonUint8 *_pucImgbuf, BoonUint32 _iWidth, BoonUint32 _iHeight, BoonUint32 _iValue1, BoonUint32 _iValue2);
BoonVoid LPL_Fill3( BoonUint8   *_pucImgbuf, BoonUint8* _pucDst, BoonInt32 _iWidth, BoonInt32 _iHeight, BoonInt32 _iValue1, BoonInt32 _iValue2 );
BoonVoid LPL_Fill4( BoonUint8   *_pucImgbuf, BoonUint8* _pucDst, BoonInt32 _iWidth, BoonInt32 _iHeight, BoonInt32 _iValue1, BoonInt32 _iValue2 );
BoonInt32 LPL_AdaptiveThreshold3(BoonUint8*  _pucInput,BoonUint8*  _pucBin	, BoonUint32 _iWidth, BoonUint32 _iHeight);
Boon_EXPORTS BoonVoid Public_ImageGray( BoonUint8 *_pucSrcImage, BoonUint8 *_pucDstImage, BoonInt32 _iWidth, BoonInt32 _iHeight);
Boon_EXPORTS BoonVoid Public_ImageGray1( BoonUint8 *_pucSrcImage, BoonUint8 *_pucDstImage, BoonInt32 _iWidth, BoonInt32 _iHeight);
Boon_EXPORTS BoonVoid Public_ImageGray2( BoonUint8 *_pucSrcImage, BoonUint8 *_pucDstImage, BoonInt32 _iWidth, BoonInt32 _iHeight);
Boon_EXPORTS BoonVoid Public_ImageGray3( BoonUint8 *_pucSrcImage, BoonUint8 *_pucDstImage, BoonInt32 _iWidth, BoonInt32 _iHeight);

/**********************************************************
	���ƣ�	Public_ImageIntMultipleReduse

	���ܣ�	˫���Բ�ֵ������ͼ���һ��

	������	BoonUint8 *_pucSrcImage		ԭʼͼ��ָ��
	  		BoonUint8 *_pucDstImage  		��һ��ͼ��ָ��
			BoonInt32 _iSrcWidth			ԭʼͼ����
			BoonInt32 _iSrcHeight			ԭʼͼ��߶�
			BoonInt32 _iNewWidth			��һ��ͼ����
			BoonInt32 _iNewHeight			��һ��ͼ��߶�

	���أ�	Boon_ALG_OK		����ִ�гɹ�

	������	_uSrcImage��_uDstImageΪ����ص�ͼ������ָ��,��Сǰ����������������
**********************************************************/
Boon_EXPORTS BoonInt32	Public_ImageIntMultipleReduse(BoonUint8 *_pucSrcImage, BoonUint8 *_pucDstImage, BoonInt32 _iSrcWidth,BoonInt32 _iSrcHeight, BoonInt32 _iNewWidth, BoonInt32 _iNewHeight);
/**********************************************************
	���ƣ�	Public_Malloc

	���ܣ�	��̬�����ڴ�

	������	BoonInt32  _iMemSeg		�ڴ��
	  		BoonInt32  _iMemSize 		�����ڴ��С
			BoonUint8  _ucMemAlign    �ڴ���뷽ʽ


	���أ�	�����ڴ���ʼָ��

	������	�����ڴ�����Ϊ���ֵ���ٶ������0Ҫ�졣
**********************************************************/
Boon_EXPORTS	BoonVoid  *Public_Malloc(BoonInt32  _iMemSeg,BoonInt32  _iMemSize,BoonUint8 _ucMemAlign);

/**********************************************************
	���ƣ�	Public_Calloc

	���ܣ�	��̬�����ڴ�

	������	BoonInt32  _iMemSeg		�ڴ��
	  		BoonInt32  _iMemSize 		�����ڴ��С
			BoonUint8  _ucMemAlign      �ڴ���뷽ʽ


	���أ�	�����ڴ���ʼָ��

	������	�����ڴ��ڲ�����ʼ��Ϊ0
**********************************************************/
Boon_EXPORTS	BoonVoid  *Public_Calloc(BoonInt32  _iMemSeg,BoonInt32  _iMemSize,BoonUint8 _ucMemAlign);
/**********************************************************
	���ƣ�	Public_Free

	���ܣ�	�ڴ��ͷ�

	������	BoonInt32  _iMemSeg		�ڴ��
	  		BoonVoid	* _pPtr 		�ͷ��ڴ��ַ
			BoonInt32  _iMemSize      �ͷ��ڴ��С��


	���أ�

	������
**********************************************************/
Boon_EXPORTS BoonVoid  Public_Free(BoonInt32  _iMemSeg,BoonVoid * _pPtr,BoonInt32  _iMemSize);

/**********************************************************
	���ƣ�	Public_DebugPrint

	���ܣ�	

	������	BoonChar * _pcFileName		��־�ļ���
	  		BoonChar * _pcDbBuf			��־�ڴ��ַ
			const BoonChar * _pcFormat    ��־�����ʽ
			...						    �ɱ���־����

	���أ�

	������
**********************************************************/
Boon_EXPORTS BoonVoid  Public_DebugPrint(BoonChar * _pcFileName, BoonChar * _pcDbBuf, const BoonChar * _pcFormat,...);

/**********************************************************
	���ƣ�	Public_GetTimeMs

	���ܣ�	��ȡϵͳʱ�� ��λ��ms 

	������	

	���أ�SYSTIME_S ϵͳ��ǰʱ��

	������
**********************************************************/
Boon_EXPORTS SYSTIME_S Public_GetTimeMs(void );
Boon_EXPORTS	BoonVoid 	Public_GetTimeMs2(SYSTIME_S* _pstSysTime  );



/**********************************************************
	���ƣ�	Public_GetTimeUs

	���ܣ�	��ȡϵͳʱ�� ��λ��us 

	������	

	���أ�SYSTIME_S ϵͳ��ǰʱ��

	������ ��DSPƽ̨�� ʱ��������ݿ��������ʱ�����ȡ�����쳣ֵ
**********************************************************/
Boon_EXPORTS SYSTIME_S Public_GetTimeUs(void );
Boon_EXPORTS BoonVoid Public_BGR2HSV( BoonUint8 *_pucSrcImage, BoonUint8 *_pucDstImage, BoonInt32 _iWidth, BoonInt32 _iHeight);
Boon_EXPORTS BoonVoid Public_RGB2HSV( BoonUint8 *_pucSrcImage, BoonUint8 *_pucDstImage, BoonInt32 _iWidth, BoonInt32 _iHeight);
void InteEqualize(BoonUint8 *_pucSrcImage, BoonInt32 lWidth, BoonInt32 lHeight);

/**********************************************************
	���ƣ�	Public_OutputMemInformation

	���ܣ�	

	������	BoonChar * _pcFileName		��Ϣ�����ļ���
	  		BoonChar * _pcDbBuf			��Ϣ�����ڴ��ַ
			BoonChar * _pcTestFalg        ��Ϣ��־��


	���أ�

	������
**********************************************************/
Boon_EXPORTS BoonVoid  Public_OutputMemInformation(BoonChar * _pcFileName, BoonChar * _pcDbBuf,BoonChar * _pcTestFalg);
Boon_EXPORTS	BoonVoid  Public_OutputMemInf(Boon_HANDLE _hModule,Boon_ALG_LOG_LEVEL_E  _eLevel,const BoonChar  * _pcFrm,...);


/**********************************************************
	���ƣ�	Public_Round

	���ܣ�	������ת�������Σ����غ����븡�������ӽ�������ֵ

	������	BoonFloat32   _f32Value	���븡����

	���أ�  BoonInt32                 ����ת���������ֵ

	������
**********************************************************/
Boon_EXPORTS  BoonInt32  Public_Round( BoonFloat32   _f32Value );

/**********************************************************
	���ƣ�	Public_Floor

	���ܣ�	������ת�������Σ����ز��������븡��������������ֵ

	������	BoonFloat32   _f32Value	���븡����

	���أ�  BoonInt32                 ����ת���������ֵ

	������
**********************************************************/
Boon_EXPORTS  BoonInt32  Public_Floor( BoonFloat32   _f32Value );

/**********************************************************
	���ƣ�	Public_Ceil

	���ܣ�	������ת�������Σ����ز�С�����븡���������С����ֵ

	������	BoonFloat32   _f32Value	���븡����

	���أ�  BoonInt32                 ����ת���������ֵ

	������
**********************************************************/
Boon_EXPORTS  BoonInt32  Public_Ceil( BoonFloat32   _f32Value );


 /********************************************************************
	���ƣ�	Public_PloygonClockwise

	���ܣ�	�޸��ܽ�㴫���˳��ͳһΪ˳ʱ��

	������	Boon_ALG_POLYGON_REGION_S _PolyRegion 	���������

	���أ�	��

	˵����	Ҫ��͹�������ڰ�����
*********************************************************************/
Boon_EXPORTS BoonVoid Public_PloygonClockwise(Boon_ALG_POLYGON_REGION_S *_pstPolyRegion);


/********************************************************************
	���ƣ�	Public_LineXLine

	���ܣ�	�ж������Ƿ񽻲�

	������	Boon_ALG_LINE_S _stLineFrt	��һ����
	  		Boon_ALG_LINE_S _stLineSec	�ڶ�����

	���أ�	BoonTrue��ʾ�н���  BoonFalse�޽���
*********************************************************************/
Boon_EXPORTS BoonBool Public_LineXLine(Boon_ALG_LINE_S _stLineFrt,Boon_ALG_LINE_S _stLineSec);


/********************************************************************
	���ƣ�	Public_GetLineAngle

	���ܣ�	��ȡ����ˮƽ�ߵļн�

	������	Boon_ALG_LINE_S _stLine	Ҫ��Ƕȵ��߶�

	���أ�	����ˮƽ�ߵļн�
*********************************************************************/
Boon_EXPORTS BoonInt32 Public_GetLineAngle(Boon_ALG_LINE_S _stLine);


/********************************************************************
	���ƣ�	Public_GeBooniffCount

	���ܣ�	ȡ���㷨�ж�ͼ���е����ֵ�����ж��۽�

	������	Boon_ALG_IMAGE_S  * _pstSrcImg ԭʼ�Ҷ�ͼ
			Boon_ALG_RECTWH_S *_pstRect    �۽�����ָ��,
			BoonInt32         _iRectCount  �������� 

	���أ�  ���ֵ           
	������	��
*********************************************************************/
Boon_EXPORTS BoonInt32     Public_GeBooniffCount(Boon_ALG_IMAGE_S * _pstSrcImg,Boon_ALG_RECTWH_S *_pstRect,BoonInt32 _iRectCount);



/********************************************************************
	���ƣ�	Public_f32Compute

	���ܣ�	�����ȸ���������(ţ�ٵ��������㷨)

	������	BoonFloat32  _f32x  ���뵥���ȸ�����


	���أ�  �����ȸ�����������           
	������	��
*********************************************************************/
Boon_EXPORTS BoonFloat32 Public_f32Compute(BoonFloat32  _f32x);

/********************************************************************
	���ƣ�	Public_FloatInverse

	���ܣ�	���������� (����С��ָ����С�����֣����õ����˻�)

	������	BoonFloat32  _f32xAny  ���뵥���ȸ�����


	���أ�  �����ȸ�����������           
	������	��
*********************************************************************/

Boon_EXPORTS BoonFloat32 Public_FloatInverse(BoonFloat32 _f32xAny);

/********************************************************************
	���ƣ�	Public_Sleep

	���ܣ�	ϵͳ��ʱ����

	������	BoonInt32    _iMillisecond   ������ʱʱ��

	���أ�  ��     

	������	ϵͳ��ʱʱ�䵥λΪ����
*********************************************************************/
Boon_EXPORTS  BoonVoid  Public_SleepMs( BoonInt32   _iMillisecond);



#ifdef __cplusplus
}
#endif
#endif
