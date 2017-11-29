#ifndef  _Boon_ALGO_TYPE_H_
#define  _Boon_ALGO_TYPE_H_

/********************************************************************
    Copyright (C), 1994-2012, ɽ��������Ϣ�Ƽ����޹�˾	
    �ļ�����: 	 Boon_algo_type.h 
    �ļ�����:    Boon�㷨��-���ú���ͷ�ļ�
    �ļ�����:    ��ϣΰ
	���ܵȼ���	 ���ļ��ɹ�������
	�����㷨Ӧ���̿���
    �޸���ʷ:	 
		
	            
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <stdarg.h>
#include <time.h>

#ifdef __cplusplus
extern "C"
{
#endif

/********************************************************************
һ���������Ͷ���
********************************************************************/
typedef long long       		BoonInt64; 
typedef	int						BoonInt32;
typedef short           		BoonInt16;
typedef	char     				BoonInt8;
typedef	char     				BoonChar;


typedef unsigned long long 		BoonUint64;
typedef unsigned int 			BoonUint32;
typedef unsigned short			BoonUint16;
typedef unsigned char 			BoonUint8;
typedef long            		BoonInt40;		
typedef unsigned long   		BoonUint40;	

typedef double     				BoonFloat64;
typedef float      				BoonFloat32;

typedef	unsigned				BoonUns;
typedef	char *          		BoonString;
typedef	void *					BoonPtr;
typedef void					BoonVoid;
typedef BoonInt32 				BoonBool;
typedef	BoonPtr					Boon_HANDLE;


/********************************************************************
�������ú궨��
********************************************************************/
#define BoonFalse				0
#define BoonTrue				1

#ifndef NULL
	#define NULL	0
#endif 

#define Boon_EXPORTS					extern

#define	Boon_ALG_OK     				 0		//	����ִ�гɹ�
#define	Boon_ALG_ALREADY_INITED		 1		//	ģ���Ѿ���ʼ����
#define Boon_ALG_FRAME_SKIPPED		 2		//	��֡����֡����
#define	Boon_ALG_FAIL   				-1		//	����ִ��ʧ��
#define	Boon_ALG_INVALID_PARAM		-2		//	��Ч����
#define Boon_ALG_NOT_INITED			-3		//	ģ��û�г�ʼ��
#define Boon_ALG_KEY_INVALID			-4 		//	��Ч����Կ
#define Boon_ALG_EMPTY_FRAME			-5		//	����ͼ��Ϊ��
#define Boon_ALG_CANNOT_OPEN_FILE		-6		//	�޷����ļ�
#define Boon_ALG_VERIFY_ERROR         -7		//	У����� 
#define Boon_ALG_PTR_NULL				-8		//	����ָ���
#define Boon_ALG_MALLOC_ERR			-9		//	�����ڴ����

typedef enum
{
	IMAGE_FORMAT_Boon_YUV422	= 0,			//	ͼ����YUV422��ʽ��planar�洢��YUV�ֱ�Ų�ͬ�ڴ�
	IMAGE_FORMAT_Boon_YUV420	= 1,			//	ͼ����YUV420��ʽ��planar�洢��YUV�ֱ�Ų�ͬ�ڴ�			
	Boon_ALG_RGB888_PACKED	= 2,			//	ͼ����RGB888��ʽ��packed�洢��BGR��ϴ��:BGRBRG
	Boon_ALG_YUV422_PACKED	= 3,			//	ͼ����YUV422��ʽ��packed�洢��YUV��ϴ��:UYVY����DM6437ƽ̨
	Boon_ALG_YUV420_MIXED		= 4,			//	ͼ����YUV422��ʽ��Y����һ���ڴ棬UV����һ���ڴ棬��DM8127ƽ̨
	Boon_ALG_YUV422_MIXED		= 5,			//	ͼ����YUV420��ʽ��Y����һ���ڴ棬UV����һ���ڴ棬��DM6467ƽ̨
	Boon_ALG_GRAY				= 6,			//	�Ҷ�ͼ��ֻ��Y
 }Boon_ALG_IMAGE_FORMAT_E;

/********************************************************************
�������ýṹ��
********************************************************************/

/****************************************************
1.��������ƽ���е�һ����Ľṹ��
*****************************************************/
typedef struct
{
	BoonInt32		x;							//	���x����ֵ
	BoonInt32		y;							//	���y����ֵ
}Boon_ALG_POINT_S;							


/****************************************************
2.��������ƽ���е�һ����������Ľṹ��
*****************************************************/
typedef struct
{
	BoonInt32		x;							//	�������Ͻǵ��x����
	BoonInt32		y;							//	�������Ͻǵ��y����
	BoonInt32		width;						//	��������Ŀ��
	BoonInt32		height;						//	��������ĸ߶�
}Boon_ALG_RECTWH_S;

/****************************************************
3.��������ƽ���е�һ����������Ľṹ��
*****************************************************/
typedef struct
{
	BoonInt32		top;						//  ����ֱ��������Ľ�Сֵ
	BoonInt32		Boonttom;						//  ����ֱ��������Ľϴ�ֵ
	BoonInt32		left;						//  ����ˮƽ��������Ľ�Сֵ
	BoonInt32		right;						//  ����ˮƽ��������Ľϴ�ֵ
}Boon_ALG_RECT_S;

/****************************************************
4.��������ƽ���е�һ����������Χ������Ľṹ��
*****************************************************/
#define  Boon_MAX_BoonUNDARY_POINT_NUM		10					//	���������
typedef struct 
{
	BoonBool			bValid;									//  ��ǰ�������Ч�ԣ�1Ϊ����
	BoonInt32			iPointNum;								//	��ɸ�����Ķ���ĸ���
	Boon_ALG_POINT_S	astPoint[Boon_MAX_BoonUNDARY_POINT_NUM];	//  ������������
}Boon_ALG_POLYGON_REGION_S;

/****************************************************
5.���Ա�ʾһ֡ͼ��Ľṹ��
*****************************************************/
typedef struct
{
	BoonInt32					iWidth;				// ͼ����
    BoonInt32					iHeight;			// ͼ��߶�
	BoonUint8					*pucD1;				// ͼ�����1 ����ָ��
	BoonUint8					*pucD2;				// ͼ�����2 ����ָ��
	BoonUint8					*pucD3;				// ͼ�����3 ����ָ��
	BoonUint64				ui64Time;			// ʱ��
	BoonInt32					iFlag;				// ��־
	Boon_ALG_IMAGE_FORMAT_E	eFormat;			// ��ʽ
} Boon_ALG_IMAGE3_S;


/****************************************************
6.���Ա�ʾһ֡ͼ��Ľṹ��
*****************************************************/
typedef struct									//ʱ���
{	/* For pthread_cond_timedwait() */
	BoonInt32		iTimeSec;						//��
	BoonInt32		iTimeMsec;						//msΪ��λ
}Boon_ALG_TIMESTAMP_S; 

typedef struct 
{
	BoonInt32					iSize;				// LPRImage �ṹ��С
	BoonInt32					iChannels;			// ͨ����Ŀ��1��2��3��4
	BoonInt32					iDepth;				// ��ɫ��ȣ�8��16
	BoonInt32					iColorMode;			// ȡֵΪ LPRColorSpace ��ĳһ��
	BoonInt32					iDataOrder;			// 0
	BoonInt32					iOrigin;			// 0
	BoonInt32					iWidth;				// ���
	BoonInt32					iHeight;			// �߶�
	BoonInt32					iImageSize;			// ����buffer��С
	BoonUint8					*pucData;			// ����bufferָ��
	BoonInt32					iStep;				// ÿһ�еĳ��ȣ���һ���Ϳ����ȣ�
	Boon_ALG_TIMESTAMP_S		stTimeStamp;		// ʱ���
	BoonInt32					iFrameNum;
}Boon_ALG_IMAGE_S;

/****************************************************
7.
*****************************************************/
typedef struct 
{
	BoonUint8		R;
	BoonUint8		G;
	BoonUint8		B;
}Boon_ALG_RGB_S;

/****************************************************
8.���Ա�ʾһֱ�ߵĽṹ��
*****************************************************/
typedef struct 
{
	Boon_ALG_POINT_S		stFrom;					//�ߵĵ�1
	Boon_ALG_POINT_S		stTo;					//�ߵĵ�2
}Boon_ALG_LINE_S;

typedef struct 
{
	BoonInt8		x;
	BoonInt8		y;
}Boon_ALG_CENTER_S;
/****************************************************
9����Ƶ�����ڴ��ʽ	
****************************************************/
typedef enum
{
	Boon_ALG_PCM_MIXED_FMT =	1,					//��ϴ洢
	Boon_ALG_PCM_PLANAR_FMT						//�����洢
}Boon_ALG_PCM_FORMAT_E;
/****************************************************
10����Ƶ���ݸ�ʽ(64�ֽ�)

****************************************************/
typedef struct
{
	BoonInt32					iFlag;				//����Ϊ-1����ʶΪ���ṹ��
	BoonInt32					iSampleRate;		//�����ʣ������8K����Ϊ8000;
	BoonInt32					iBitWidth;			//�������ȣ���������λ��  �����16λ����Ϊ16  
	BoonInt32					iChanNum;			//ͨ��������ͨ��Ϊ1 ˫ͨ��Ϊ2
	Boon_ALG_PCM_FORMAT_E		eFrameFormat;		//�洢��ʽ����ϴ洢Ϊ2�������洢Ϊ1
	BoonUint32				uiVirAddr[2];		//��Ƶ���������ַָ��
	BoonUint32				uiPhyAddr[2];		//��Ƶ���������ַָ��
	BoonUint64				ui64TimeStamp;		//ʱ���
	BoonUint32				uiSeq;				//��Ƶ֡���
	BoonUint32				uiLen;				//ÿ��ͨ�������ݳ���
	BoonUint32				uiExtraPhyAddr;		//�������ݵ�����ָ�룬���ݺ�ƽ̨��ص�����
	BoonUint32				uiExtraVirAddr;		//�������ݵ�����ָ�룬���ݺ�ƽ̨��ص�����
	BoonUint32				uiReserved;
}Boon_ALG_PCM_FRAME_PARA_S;

/****************************************************
11����Ƶ���ݸ�ʽ(128�ֽ�)
 					
****************************************************/
typedef struct
{
	BoonInt32					iFlag;				//����Ϊ-1����ʶΪ�½ṹ��
	BoonUint32				uiWidth;			//��
	BoonUint32				uiHeight;			//��
	BoonUint32				uiStartX;			//�����Ч��ȣ�������
	BoonUint32				uiStartY;			//�ϱ���Ч��ȣ�������
	Boon_ALG_IMAGE_FORMAT_E	eImageFormat;		//���ظ�ʽ
	BoonUint32				uiPhyAddr[3];		//�����ַ
	BoonUint32				uiVirAddr[3];		//�����ַ
	BoonUint32				uiStride[3];		//���
	BoonUint64				ui64Pts;			//ʱ���
	BoonUint32				uiSeq;				//ͼ��֡���
	BoonUint32				uiExtraPhyAddr;		//�������ݵ�����ָ�룬���ݺ�ƽ̨��ص�����
	BoonUint32				uiExtraVirAddr;		//�������ݵ�����ָ�룬���ݺ�ƽ̨��ص�����
	BoonUint32				uiReserved[12];
}Boon_ALG_VIDEO_FRAME_PARA_S;

/****************************************************
12���㷨�ӿڰ汾
****************************************************/
typedef enum
{
	Boon_ALG_IF_IPC300W = 	1,					//20141101
	Boon_ALG_IF_COUNT
}Boon_ALG_INTERFACE_VERSION_E;

#ifdef __cplusplus
}
#endif
#endif 