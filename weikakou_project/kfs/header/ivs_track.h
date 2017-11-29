#ifndef _Boon_IVS_TRACK_H_
#define _Boon_IVS_TRACK_H_

#include "Boon_algo_type.h"
#include "Boon_algo.h"
#include "Boon_algo_ivs_config.h"
#include "ivsconfig.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*������*/
typedef struct
{
	BoonInt32 iMode;			/*����λ��*/
	BoonInt32 iDirection;		/*���߷���*/
} IVS_TGTINFO_TRIPWIRE_S;

/*˫����*/
typedef struct
{
	BoonInt32	aiIdList[Boon_ALG_MAX_RULE_NUM];	/*ID(Boon_ALG_MAX_NUM_RULE_NUM)*/
	BoonInt32	aiFrList[Boon_ALG_MAX_RULE_NUM];	/*֡��(Boon_ALG_MAX_NUM_RULE_NUM)*/
 	BoonInt32	iMode;			/*����λ��*/
 	BoonInt32	iDirection;		/*���߷���*/
} IVS_TGTINFO_MTRIPWIRE_S;

/*�޸�*/
//typedef struct
//{
//	BoonInt32	iTimeOver;		/*����ʱ��*/
//	BoonInt32	iOverTresh;		/*�ݴ�*/
//} IVS_TGTINFO_HIGLIMT_PARA_S;

/*�ǻ�*/
typedef struct
{
	Boon_ALG_RECT_S stBoundary;	/*��Ӿ���*/
	BoonInt32		iCount;			/*�����ĵ�Ĵ���*/
	BoonInt32		iInPolygon;		/*��������*/
} IVS_TGTINFO_LOITER_S;

///*����*/
//typedef struct
//{
//	BoonInt32 iTimeSlip;		/*����ʱ��*/
//	BoonInt32 iOverTresh;		/*�ݴ�*/
//} IVS_TGTINFO_SLIPUP_S;

typedef struct
{
	BoonInt32 iMatchNum;					/*ƥ����Ŀ*/
	BoonInt32 aiMatchId[Boon_MAXMATCHNUM];	/*���ƥ��5��*/
	BoonInt32 aiMatchPro[Boon_MAXMATCHNUM];	/*ƥ�����*/
	BoonBool  bConBin;					/*�Ƿ�ϲ�*/
	BoonBool	bSepaRate;					/**/
} IVS_TRACK_MATCHINFO_S;

/*���������*/
typedef struct 
{
	BoonInt32 iGradMore;	/*�ݶȱ��*/
	BoonInt32 iGradLess;	/*�ݶȱ�С*/
	BoonInt32	iFgConsis;	/*һ���Ա���*/
	BoonInt32 iAveGray;	/*ƽ���Ҷ�*/
}IVS_TRACK_FEATURE_S;

/*���Ŀ��*/
typedef struct
{
	BoonInt32	iRealTarFrame;	/*��Ŀ��*/
	BoonInt32	iOscFlag;		/*��Ŀ��*/		
} IVS_TRACK_TGT_S;

typedef struct 
{ 
	BoonInt32 iSn;			/*���*/
	BoonInt32 top;
	BoonInt32 bottom;
	BoonInt32 left;
	BoonInt32 right;
	BoonInt32 still;
	BoonInt32 iCenterX;		/*���ĵ�x*/
	BoonInt32 iCenterY;		/*���ĵ�y*/
	BoonInt32 iAreaNum;		/*�����С*/
	BoonInt32 iDiffRate;		/*�仯����*/
	BoonInt32 iNewSn;			/*��ʼ��Ϊ0*/
	IVS_TRACK_MATCHINFO_S stMatchInfo;	/*ƥ����Ϣ*/
	IVS_TRACK_FEATURE_S stFeature;	/*��������*/
} IVS_TRACK_RECT_S;

typedef struct 
{
	BoonBool		bIdle;			/*��ֹ��ʶ*/
	BoonBool		bLastIdle;		/*��֡��ֹ*/
	BoonBool		bNew;			/*��Ŀ���ʶ*/
	BoonBool		bSubmFlg;		/*���أ����ϲ���־*/
	BoonBool		bFatherFlg;		/*��ģ��*/
	BoonBool		bDeleteFlg;		/*ɾ����־*/
	BoonInt32		iHisId;			/*��ʷid��Ψһ����ͣ��*/
	BoonInt32		iTraceLen;		/*�켣����*/
	BoonInt32		iRbpnt;			/*δ֪*/
	BoonInt32		iAlarm;			/*��������*/
	BoonInt32		iLastAlarm;		/*��֡����*/		
	BoonInt32		iLifeTime;		/*��������*/
	BoonInt32		iStatusMov;		/*�˶�״̬��0-δ�ж���1-�˶���2-��ֹ*/
	BoonInt32		iStillLife;		/*��ֹ״̬�����ھ����⡢Ҫ��ʼ���˶�����������ײ�ȵ�*/
	BoonInt32		iLosTime;		/*��ʧʱ�䣬��ʧʱ�����һ��ֵ��ɾ��*/
	BoonInt32		iVolecX;		/*x�����ٶȣ��ٶȳ�10����߾���*/
	BoonInt32		iVolecY;		/*y�����ٶȣ��ٶȳ�10*/
	BoonInt32		iSubLide;		/*��ģ����������*/
	BoonInt32		iSubNum;		/*��ģ������*/
	BoonInt32		iSeprateNum;	/*seprate����*/
	BoonInt32		iMoreAreaNum;	/*������ƽ���ϲ������⣬���������֡����һ�±���ҳ���һ����Χ����ֱ�Ӳ��ٺϲ�*/
	BoonInt32		iOSCStatus;		/*0-�ޣ�1-������2-��ʧ*/
	BoonInt32		iStaticNum;		//Ŀ��λ��δ�����仯��ʱ��
	int flag;
	BoonInt32				aiOnTimer[5];							/*add by mhm ��ʱ��*/
	BoonInt32				aiSubId[Boon_MAXSUBMNUM];					/*��ģ���id*/
	BoonInt32				aiFthSubLife[Boon_MAXSUBMNUM];			/*��ģ������ģ����������*/
	Boon_ALG_POINT_S		astCenter[Boon_ALG_IVS_MAX_TRAJECT_LEN];	/*�켣�����ĵ�*/
	IVS_TRACK_RECT_S	astObjRect[Boon_ALG_IVS_MAX_TRAJECT_LEN];	/*�켣����Ӿ���*/
	IVS_TRACK_RECT_S			stPredict;				/*Ԥ��λ��*/
	IVS_TRACK_RECT_S			stFatherRect;			/*��ģ��ԭʼrect��Ϣ*/	
	IVS_TRACK_MATCHINFO_S		stMatchInfo;			/*������Ϣ*/
	BoonInt32                     aiCount[Boon_ALG_MAX_RULE_NUM];//ʱ�����
	BoonInt32						aiOverTresh[Boon_ALG_MAX_RULE_NUM];	/*�ݴ� 05.25 add by mhm*/
	//IVS_TGTINFO_SLIPUP_S		stSlipup;				/*add by mhm ������*/
	IVS_TGTINFO_LOITER_S		stLoiter;				/*add by mhm �ǻ��ã��켣�����Ӿ���*/
	IVS_TGTINFO_TRIPWIRE_S		stTripWire;				/*add by mhm ��������*/
	IVS_TGTINFO_MTRIPWIRE_S		stMTripWire;			/*add by mhm ˫������*/
	//IVS_TGTINFO_HIGLIMT_PARA_S	stHiglimit;				/*add by mhm �޸���*/
} IVS_TRACK_TRAJECT_S;

typedef struct
{
	BoonInt32			iHisId;
	BoonInt32			iFrame;				/*֡��*/
	BoonInt32			iLists;				/*�켣��*/
	BoonInt32			iWidth;
	BoonInt32			iHeight;
	IVS_TRACK_TGT_S		 stTrackPara;
	IVS_TRACK_TRAJECT_S* pstTrackRult;	/*���*/
	BoonInt32   iSeg;
} IVS_TRACK_S;


/**********************************************************
	���ƣ�	IVS_TRACK_Init
	���ܣ�	����ģ�顪����ʼ��
	������	IVS_TRACK_S*		_pstModelTrack	����ģ��
			BoonInt32				_iRealTgtFrame	ȷ��ΪĿ���֡��
			BoonInt32				_OscFlag		��Ʒ������ʧ��ʶ
			BoonInt32				_iImgW			ͼ����
			BoonInt32				_iImgH			ͼ��߶�
	���أ�	IVS_STATUS_E		Boon_ALG_OK/Boon_ALG_FAIL
**********************************************************/
IVS_STATUS_E IVS_TRACK_Init(IVS_TRACK_S* _pstModelTrack, BoonInt32 _iRealTgtFrame, BoonInt32 _OscFlag, 
							BoonInt32 _iImgW, BoonInt32 _iImgH);

/**********************************************************
	���ƣ�	IVS_TRACK_Process
	���ܣ�	����ģ�顪������
	������	IVS_TRACK_S*		_pstModelTrack	����ģ��
			Boon_ALG_IMAGE3_S*	_pstImage		����ͼ��
	  		IVS_TRACK_RECT_S*	_pstFgRect		ǰ����Ϣ
			BoonInt32				_iFgRectNum		ǰ����Ŀ
	���أ�	IVS_STATUS_E		Boon_ALG_OK
**********************************************************/
IVS_STATUS_E IVS_TRACK_Process(IVS_TRACK_S* _pstModelTrack, IVS_TRACK_RECT_S* _pstFgRect, BoonInt32 _iFgRectNum);

/**********************************************************
	���ƣ�	IVS_TRACK_Release
	���ܣ�	����ģ�顪���ͷ�
	������	IVS_TRACK_S*		_pstModelTrack	����ģ��
	���أ�	IVS_STATUS_E		Boon_ALG_OK
**********************************************************/
IVS_STATUS_E IVS_TRACK_Release(IVS_TRACK_S* _pstModelTrack);

/**********************************************************
	���ƣ�	IVS_TRACK_GetSize
	���ܣ�	����ģ�顪�������ڴ��С
	������	
	���أ�	BoonInt32				iSize
**********************************************************/
BoonInt32 IVS_TRACK_GetSize();

#ifdef __cplusplus
}
#endif

#endif	/*end _Boon_IVS_TRACK_H_*/
