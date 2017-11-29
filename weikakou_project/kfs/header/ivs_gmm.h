#ifndef _IVS_GMM_H_
#define _IVS_GMM_H_

//#define ONLY_GMM //���ڱ�����ģ

#ifndef ONLY_GMM
#include "ivs_track.h"
#else
#include "Boon_algo_type.h"
#define IVS_STATUS_E			BoonInt32			/*���������������תһ��*/
//typedef BoonVoid IVS_TRACK_RECT_S;
#endif


#ifdef __cplusplus
extern "C"
{
#endif

#define FLT_EPSILON			1.192092896e-07F
#define Boon_MAX_FGRECTNUM	256	

#ifndef Boon_ABS_REGION
#define Boon_ABS_REGION				65536						/* ����������롢���Ȳ�ֵ�ľ���ֵ */
#define Boon_ABS_ZEROPOS				Boon_ABS_REGION / 2
#endif
/*Default parameters of GMM*/
#define IVS_GMM_BACKGROUND_THRESHOLD     0.9f			/*��������Ȩ��*/
#define IVS_GMM_SBoon_THRESHOLD            25			/*lambdaֵ */
#define IVS_GMM_WINDOW_SIZE              100			/*ѧϰ��*/
#define IVS_GMM_NGAUSSIANS               3				/*Mode������*/
#define IVS_GMM_WEIGHT_INIT              0.3			/*��ʼȨ��*/
#define IVS_GMM_SIGMA_INIT               30				/*��ʼ�ָ�ϵ��*/
#define IVS_GMM_MINAREA                  15.f			/*��С��������*/
#define IVS_GMM_MAX_BACKLEAN			 10				/*��󱳾�ѧϰ֡��*/

typedef BoonInt32 IVS_STATUS_E;

/*ÿ�����ص�GMM��Ϣ*/
typedef struct
{		
	BoonInt32			iGetBGTime;							/*������ѧϰʱ��*/
	BoonFloat32       af32Weight[IVS_GMM_NGAUSSIANS];		/*��ModelȨ��	*/		
	BoonFloat32       af32Variance[IVS_GMM_NGAUSSIANS];	/*��Model����*/
	BoonFloat32       af32Mean[IVS_GMM_NGAUSSIANS];		/*��Model��ֵ*/
	BoonFloat32		af32SortKey[IVS_GMM_NGAUSSIANS];	/*��Model����ؼ���*/
	BoonInt32			aiOrder[IVS_GMM_NGAUSSIANS];		/*��Model�����*/

	/*����*/
	BoonInt32			iMvStartFrm;						/*�˶�Ŀ���ʶ*/
	BoonInt32			iMvConsistNum;						/*����֡��*/
	BoonInt32			iStcStartFrm;						/*��ֹĿ�꿪ʼʱ��*/
	BoonInt32			iStcConsistNum;						/*��ֹĿ�����֡��*/
} IVS_GMM_INFO_S;

/*GMMʹ�õ�ͼ��ָ��*/
typedef struct
{
	BoonUint8*		pucSmoothImg;		/*ƽ����ĻҶ�ͼ��*/
	BoonUint8*		pucDiffImg;			/*֡��ͼ��*/
	BoonUint8*		pucFgImg;			/*ǰ��ͼ��*/
	BoonUint8*		pucSnImg;			/*��ͨ������õ��ı��ͼ��*/
	BoonUint8*		pucBgImg;			/*����ͼ��*/
	BoonUint8*		pucPrevImg;			/*��һ֡�Ҷ�ͼ��*/
	BoonUint8*        pucBoundaryImg;     /*��Ӷ���ζ�ֵͼ��������Ϊ1��������Ϊ0*/
} IVS_GMM_IMGBuff_S;

/*���˹������ģģ�����*/
typedef struct
{
	BoonInt32			iTgtMaxArea;		/*�������*/	
	BoonInt32			iTgtMinArea;		/*��С����*/
	BoonInt32			iTgtMaxFrame;		/*���֡��*/
	BoonInt32			iTgtMergeRate;		/*�ϲ�ϵ��*/
	BoonInt32			iWindowsSize;		/*ѧϰ��*/
	BoonInt32			iStilltoBgTime;		/*��ֹĿ�����뱳��ʱ��*/
	BoonFloat32		f32VarMin;			/*��С����*/
	BoonFloat32		f32VarMax;			/*��󷽲�*/
	BoonFloat32		f32BgTh;			/*��������Ȩ������*/
} IVS_GMM_PARA_S;

/*���˹������ģģ��߼�����*/
typedef struct
{
	BoonInt32			iTmp;
} IVS_GMM_ADVPARA_S;

/*ʹ��TBBʱ�Ľṹ��*/
typedef struct
{
	BoonUint8*		pucFgImg;			/*ǰ��ͼ��ָ�루����ֻ��ָ�룬����Ҫ�����ڴ棩*/
	BoonUint8*		pucBgImg;			/*����ͼ��ָ�루ͬ�ϣ�*/
	BoonUint8*		pucCurrImg;			/*��ǰͼ��ָ�루ͬ�ϣ�*/
	BoonUint8*		pucDiffImg;			/*���ͼ��ָ�루ͬ�ϣ�*/
	BoonInt32			iHeight;			/*ͼ��߶�*/
	BoonInt32			iWidth;				/*ͼ����*/
	BoonInt32			iStillTime;			/**/
	BoonInt32			iFrameNo;			/*֡��*/
	BoonInt32			iModelNum;			/*��˹����*/
	BoonFloat32		f32BgTh;			/*Ȩ���о�����*/
	BoonFloat32		f32Alpha;			/**/
	BoonFloat32		f32VarMin;
	BoonFloat32		f32VarMax;
	BoonFloat32		f32VarRate;
	IVS_GMM_INFO_S* pstGmmInfo;			/*�����ص�ģ��ָ�루����ֻ��ָ�룬����Ҫ�����ڴ棩*/
} IVS_GMM_TBB_PARA_S;

/*���˹������ģģ��ṹ��*/
typedef struct 
{
	BoonInt32			iFrameNo;			/*֡��*/
	BoonInt32			iHistory;			/**/
	BoonInt32			iMixtures;			/*Model������*/
	BoonFloat32		f32VarTh;			/*��������*/
	BoonFloat32		f32BgRatio;			/**/
	BoonFloat32		f32NoiseSigma;
	BoonFloat32		f32InitVar;			/*��ʼ����*/
	BoonFloat32		f32InitWeight;		/*��ʼȨ��*/
	BoonFloat32		f32InitSortKey;		/*��ʼ����*/

	BoonInt32			iFgBigNum;			/*�仯*/
	BoonFloat32		f32VarCorrectRate;	/*�������ϵ��*/
	BoonFloat32		f32GrayAve;			/*ͼ��ҶȾ�ֵ��alpha�˲����*/
		
	IVS_GMM_PARA_S			stGmmPara;	/*GMM���ò���*/
	IVS_GMM_INFO_S*			pstGmmInfo;	/*ÿ�����ص�GMM��Ϣָ��*/
	IVS_GMM_IMGBuff_S*		pstImgBuff;	/*GMMʹ�õ�ͼ��ָ��*/
#ifdef HAVE_TBB
	IVS_GMM_TBB_PARA_S*		pstTbbPara;		/*ʹ��TBBʱ�Ľṹ��*/
#endif
	BoonInt32    iImgWidth;
	BoonInt32    iImgHeight;

} IVS_GMM_S;
typedef   IVS_GMM_S  * GMM_Handle;



/***************************************************************************************

�������ƣ�IVS_GMM_Create

���ܣ������㷨����

������	Seg	�㷨�ڲ���̬�����ڴ�Ķε�ַ
Key ���������������Կ

����ֵ�������ɹ���������ָ��
����ʧ�ܷ��ؿ�ָ��

������

***************************************************************************************/
Boon_EXPORTS Boon_HANDLE  IVS_GMM_Create(BoonInt32  _iSeg,BoonChar * _pcKey);

/**********************************************************
	���ƣ�	IVS_GMM_Init

	���ܣ�	���˹������ģ������ʼ��

	������	Boon_HANDLE                _hModule		GMMģ��ָ��
			BoonInt32				     _iFrmInterval	��֡֡��
			BoonInt32				     _iImgWidth		ͼ����
			BoonInt32				     _iImgHeight    ͼ��߶�

	���أ�	IVS_STATUS_E		Boon_ALG_OK/Boon_ALG_FAIL
**********************************************************/
Boon_EXPORTS IVS_STATUS_E IVS_GMM_Init(Boon_HANDLE _hModule, BoonInt32 _iFrmInterval, BoonInt32 _iImgWidth, BoonInt32 _iImgHeight);

/**********************************************************
	���ƣ�	IVS_GMM_Process

	���ܣ�	���˹������ģ����������

	������	Boon_HANDLE     _hModule		GMMģ��ָ��
	  		IVS_TRACK_RECT_S*	_pstFgRect		ǰ��Ŀ���
			Boon_ALG_POLYGON_REGION_S* _pstBoundary   ��Ҫ��ģ������
			BoonInt32				_iImgWidth		ͼ����
			BoonInt32				_iImgHeight		ͼ��߶�

	���أ�	BoonInt32				iRectNum		ǰ��Ŀ����
**********************************************************/
Boon_EXPORTS BoonInt32 IVS_GMM_Process(Boon_HANDLE _hModule, BoonUint8* _pucSrc, 
#ifndef ONLY_GMM
						IVS_TRACK_RECT_S* _pstFgRect, 
#endif
						Boon_ALG_POLYGON_REGION_S* _pstBoundary, BoonInt32 _iImgWidth, BoonInt32 _iImgHeight);
/**********************************************************
	���ƣ�	IVS_GMM_PostProcess
	���ܣ�	���˹������ģ��������
	������	IVS_MOVE_S*			_pstBgModel		����ģ��
			IVS_TRACK_S*		_pstTrackInfo	������Ϣ
			IVS_TRACK_MLYRECT_S* _pstRect		Ŀ���
			BoonInt32				_iRectNum		ǰ������
			BoonInt32				_iImgW			ͼ����
			BoonInt32				_iImgH			ͼ��߶�
	���أ�	Boon_ALG_OK
**********************************************************/
#ifndef ONLY_GMM
Boon_EXPORTS IVS_STATUS_E IVS_GMM_PostProcess(IVS_GMM_S* _pstGmm, IVS_TRACK_S* _pstTrackInfo, 
								 IVS_TRACK_RECT_S* _pstRect, BoonInt32 _iRectNum, 
								 BoonInt32 _iImgW, BoonInt32 _iImgH);
#endif

/**********************************************************
	���ƣ�	IVS_GMM_Release

	���ܣ�	���˹������ģ�����ͷ�

	������	Boon_HANDLE _hModule	GMMģ��ָ��

	���أ�	IVS_STATUS_E		Boon_ALG_OK
**********************************************************/
Boon_EXPORTS IVS_STATUS_E  IVS_GMM_Release(Boon_HANDLE _hModule);


#ifdef __cplusplus
}
#endif

#endif	/*_IVS_GMM_H_*/
