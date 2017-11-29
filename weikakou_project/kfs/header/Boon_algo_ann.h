/********************************************************************
    Copyright (C), 1994-2012, ɽ��������Ϣ�Ƽ����޹�˾	
	Filename: 	 Boon_algo_Ann.h
    Description: ������ʶ��
	Author:		 ��ϣΰ
    Created:	 20:12:2012   14:08	
*********************************************************************/

#ifndef   _BOON_ANN_H_
#define   _BOON_ANN_H_


#ifdef __cplusplus
extern "C" {
#endif


#include	"Boon_algo.h"


#define NAME_SPACE
#ifdef NAME_SPACE
namespace Boon_ann
{
#endif



#define MAX(a,b)  ((a) < (b) ? (b) : (a))
#define MIN(a,b)  ((a) > (b) ? (b) : (a))

#define CV_ELEM_SIZE(type) \
	(CV_MAT_CN(type) << ((((sizeof(size_t)/4+1)*16384|0x3a50) >> CV_MAT_DEPTH(type)*2) & 3))

#define CV_CN_MAX     512
#define CV_CN_SHIFT   3
#define CV_DEPTH_MAX  (1 << CV_CN_SHIFT)

#define CV_MAT_DEPTH_MASK       (CV_DEPTH_MAX - 1)
#define CV_MAT_DEPTH(flags)     ((flags) & CV_MAT_DEPTH_MASK)

#define CV_MAKETYPE(depth,cn) (CV_MAT_DEPTH(depth) + (((cn)-1) << CV_CN_SHIFT))
#define CV_MAKE_TYPE CV_MAKETYPE

#define CV_8UC1 CV_MAKETYPE(CV_8U,1)
#define CV_8UC2 CV_MAKETYPE(CV_8U,2)
#define CV_8UC3 CV_MAKETYPE(CV_8U,3)
#define CV_8UC4 CV_MAKETYPE(CV_8U,4)
#define CV_8UC(n) CV_MAKETYPE(CV_8U,(n))

#define CV_8SC1 CV_MAKETYPE(CV_8S,1)
#define CV_8SC2 CV_MAKETYPE(CV_8S,2)
#define CV_8SC3 CV_MAKETYPE(CV_8S,3)
#define CV_8SC4 CV_MAKETYPE(CV_8S,4)
#define CV_8SC(n) CV_MAKETYPE(CV_8S,(n))

#define CV_16UC1 CV_MAKETYPE(CV_16U,1)
#define CV_16UC2 CV_MAKETYPE(CV_16U,2)
#define CV_16UC3 CV_MAKETYPE(CV_16U,3)
#define CV_16UC4 CV_MAKETYPE(CV_16U,4)
#define CV_16UC(n) CV_MAKETYPE(CV_16U,(n))

#define CV_16SC1 CV_MAKETYPE(CV_16S,1)
#define CV_16SC2 CV_MAKETYPE(CV_16S,2)
#define CV_16SC3 CV_MAKETYPE(CV_16S,3)
#define CV_16SC4 CV_MAKETYPE(CV_16S,4)
#define CV_16SC(n) CV_MAKETYPE(CV_16S,(n))

#define CV_32SC1 CV_MAKETYPE(CV_32S,1)
#define CV_32SC2 CV_MAKETYPE(CV_32S,2)
#define CV_32SC3 CV_MAKETYPE(CV_32S,3)
#define CV_32SC4 CV_MAKETYPE(CV_32S,4)
#define CV_32SC(n) CV_MAKETYPE(CV_32S,(n))

#define CV_AUTO_STEP  0x7fffffff
#define CV_WHOLE_ARR  cvSlice( 0, 0x3fffffff )

#define CV_MAT_CN_MASK          ((CV_CN_MAX - 1) << CV_CN_SHIFT)
#define CV_MAT_CN(flags)        ((((flags) & CV_MAT_CN_MASK) >> CV_CN_SHIFT) + 1)
#define CV_MAT_TYPE_MASK        (CV_DEPTH_MAX*CV_CN_MAX - 1)
#define CV_MAT_TYPE(flags)      ((flags) & CV_MAT_TYPE_MASK)
#define CV_MAT_CONT_FLAG_SHIFT  14
#define CV_MAT_CONT_FLAG        (1 << CV_MAT_CONT_FLAG_SHIFT)
#define CV_IS_MAT_CONT(flags)   ((flags) & CV_MAT_CONT_FLAG)
#define CV_IS_CONT_MAT          CV_IS_MAT_CONT
#define CV_SUBMAT_FLAG_SHIFT    15
#define CV_SUBMAT_FLAG          (1 << CV_SUBMAT_FLAG_SHIFT)
#define CV_IS_SUBMAT(flags)     ((flags) & CV_MAT_SUBMAT_FLAG)

#define FLT_EPSILON     1.192092896e-07F        /* smallest such that 1.0+FLT_EPSILON != 1.0 */
#define CV_MALLOC_ALIGN 16

#define EXPTAB_SCALE 6
#define EXPTAB_MASK  ((1 << EXPTAB_SCALE) - 1)

#define EXPPOLY_32F_A0 .9670371139572337719125840413672004409288e-2

#define CV_MAGIC_MASK       0xFFFF0000
#define CV_MAT_MAGIC_VAL    0x42420000

#define CV_IS_MAT_HDR(mat) \
	((mat) != NULL && \
	(((const CvMat*)(mat))->type & CV_MAGIC_MASK) == CV_MAT_MAGIC_VAL && \
	((const CvMat*)(mat))->cols > 0 && ((const CvMat*)(mat))->rows > 0)

#define CV_IS_MAT_HDR_Z(mat) \
	((mat) != NULL && \
	(((const CvMat*)(mat))->type & CV_MAGIC_MASK) == CV_MAT_MAGIC_VAL && \
	((const CvMat*)(mat))->cols >= 0 && ((const CvMat*)(mat))->rows >= 0)

#define CV_IS_MATND_HDR(mat) \
	((mat) != NULL && (((const CvMatND*)(mat))->type & CV_MAGIC_MASK) == CV_MATND_MAGIC_VAL)

#define CV_IS_MAT(mat) \
	(CV_IS_MAT_HDR(mat) && ((const CvMat*)(mat))->data.ptr != NULL)

#define CV_SWAP(a,b,t) ((t) = (a), (a) = (b), (b) = (t))

#define INT_MAX       2147483647 


#define CV_8U   0
#define CV_8S   1
#define CV_16U  2
#define CV_16S  3
#define CV_32S  4
#define CV_32F  5
#define CV_64F  6
#define CV_USRTYPE1 7

#define CV_AUTOSTEP  0x7fffffff



typedef unsigned char uchar;
typedef void CvArr;
typedef unsigned short ushort;

typedef struct CvPoint
{
	int x;
	int y;
}
CvPoint;

typedef struct CvMat
{
	int type;
	int step;

	/* for internal use only */
	int* refcount;
	int  calloccount;
	int hdr_refcount;

	union
	{
		unsigned char* ptr;
		short* s;
		int* i;
		float* fl;
		double* db;
	} data;

#ifdef __cplusplus
	union
	{
		int rows;
		int height;
	};

	union
	{
		int cols;
		int width;
	};
#else
	int rows;
	int cols;
#endif

}
CvMat;


typedef struct CvANN_MLP
{
	CvMat* layer_sizes;
	CvMat* wbuf;
	CvMat* sample_weights;
	float* weights[6];
	float f_param1, f_param2;
	float min_val, max_val, min_val1, max_val1;
	int activ_func;
	int max_count, max_buf_sz;
	bool inited;

}CvANN_MLP;



typedef enum { IDENTITY = 0, SIGMOID_SYM = 1, GAUSSIAN = 2 };

typedef struct Size
{
	int width;
	int height;
}Size;

typedef union Cv32suf
{
	int i;
	unsigned u;
	float f;
}
Cv32suf;

typedef  struct
{
	BoonChar  		*pcModelAdd;//������model
	BoonInt32         iModelLen; //model����
	CvANN_MLP 	    stAnnMlp; //��������ڵ����
	CvMat          *pstMlpResponse;//�����Ӧ
	BoonInt32        iConfineType;
	BoonInt32        iLayerType;
}Boon_ALG_AnnPara_S;

typedef Boon_ALG_AnnPara_S  *AnnHandle;

/********************************************************************
	���ƣ�	BoonAlgo_Ann_Create

	���ܣ�	�����������㷨����

	������	BoonInt32  _iSeg		    �ڴ��
			BoonChar   _pcKey         ��Կ

	���أ�	Boon_HANDLE		�����㷨�����������

*********************************************************************/

Boon_EXPORTS  Boon_HANDLE BoonAlgo_Ann_Create(BoonInt32  _iSeg,BoonChar *_pcKey);

/********************************************************************
	���ƣ�	BoonAlgo_Ann_Init

	���ܣ�	�������ʼ��

	������	Boon_HANDLE            _hModule	   �㷨����
			BoonChar               _pcModelAdd   ѵ��ģ��·��
			BoonInt32              _iLen         ģ�峤��
	���أ�	Boon_ALG_OK		����ִ�гɹ�

*********************************************************************/
Boon_EXPORTS  BoonInt32     BoonAlgo_Ann_Init(Boon_HANDLE _hModule, BoonChar  *_pcModelAdd, BoonInt32  _iLen);


/********************************************************************
	���ƣ�	BoonAlgo_Ann_Process

	���ܣ�	������ʶ������

	������	Boon_HANDLE          _hModule		        �㷨����
			Boon_HANDLE          _hConf               ���ŶȾ��
			BoonFloat32          _pf32FeatureArray    ����ֵ
			BoonInt32            _iFeatureLen         ����ֵ����
			BoonFloat32          _pf32Confine         ���Ŷ�
			BoonFloat32          _pf32Response        ������ÿ��ֵʶ������Խ��
			BoonInt32            _piResponseCnt       ��Ҫ�������Ŀ
	���أ�	Boon_ALG_OK		   ����ִ�гɹ�
*********************************************************************/

Boon_EXPORTS  BoonInt32     BoonAlgo_Ann_Process(Boon_HANDLE _hModule, Boon_HANDLE _hConf,BoonFloat32  *_pf32FeatureArray,BoonInt32  _iFeatureLen, BoonFloat32 *_pf32Confine, BoonFloat32 *_pf32Response, BoonInt32 *_piResponseCnt);//������Ϊ�������

/********************************************************************
	���ƣ�	BoonAlgo_Ann_Release

	���ܣ�	ɾ��������ʶ���㷨����

	������	Boon_HANDLE _hModule		    �㷨����

	���أ�	BoonVoid		

*********************************************************************/
Boon_EXPORTS  BoonVoid    BoonAlgo_Ann_Release(Boon_HANDLE _hModule);


#ifdef NAME_SPACE
}
#endif

#ifdef __cplusplus
}
#endif


#endif 
