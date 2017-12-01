/********************************************************************
    Copyright (C), 1994-2012, ɽ��������Ϣ�Ƽ����޹�˾	
    �ļ�����: 	 Boon_algo_verification.h
    �ļ�����:    BOON�㷨��  �ļ�У��ͷ�ļ�
    �ļ�����:    BOON�㷨��
    �޸���ʷ:	 20:12:6:28   �淶��   ��ϣΰ
	            
*********************************************************************/

#ifndef   _BOON_VERIFICATION_PRIVATE_H_
#define   _BOON_VERIFICATION_PRIVATE_H_

#include	"Boon_algo_type.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef enum 
{
	LPRV  = 0 ,		//LPR������
	LPRM,			//����ʶ���ֿ�
	TTV ,			//�켣����������
	TTMK,			//���ڳ������model
	TTMD,			//�羯�������model
	WMV,			//ˮӡ������
	EIV,			//��ǿԴ����
	DFW,			//DSP�̼�
	IPDM
}Boon_ALG_FILETYPE_E;

typedef struct 									//�ļ�������Ϣ�ṹ��
{
	BoonUint32			uiFilesize;				//�ļ��ܴ�С�������ļ�ͷ
	BoonChar				acCompany[32];			//"ɽ��������Ϣ�Ƽ����޹�˾"--��ʱ����
	BoonChar				acProduct[32];			//"LPR"   ---��ʱ����
	Boon_ALG_FILETYPE_E	eProductID;				//��ƷID��LPRV -0  LPRM -1 TTV -2 TTMK-3 TTMD -4 WMV -5 EIV -6
	BoonChar				acMasterVersion[32];	//������汾��	"V3.0.0.1"  //��ʱ����
	BoonChar				acModelVersion[32];		//������汾��	"2.0.302.1" [�ļ��汾]��6.5.705.1  ��ע��705�Ƿ������ڡ�0705���ĺ���λ��
	BoonUint32			uiChecknum; 			//У��ͣ�32λ
	BoonUint32			uiCheckCrc;				//CRCУ��
}Boon_ALG_FILEHEADER_S;


//	����ļ��е���� file ����
#define Boon_ALG_MAX_FILE_NUM		64

typedef struct			//	pack��Ϣ��size = 64
{
	BoonInt32				i32FileNums;			//	�ļ���
	BoonInt32				i32MaxFIleSize;			//	����ļ���С�����Բ���
	BoonInt8				acDate[24];				//	����ļ�����
	BoonInt8				acReserved[32];			//	��ע
}Boon_ALG_FILE_PACK_S;

typedef struct			//	file��pack�е���Ϣ��size = 64 + 20
{
	Boon_ALG_FILE_TYPE_E	eFileType;				//	����
	BoonBool				bIsZip;					//	�Ƿ�ѹ��		true: zip
	BoonInt8				acFileName[32];			//	�ļ���
	BoonInt8				acVersion[32];			//	�ļ��汾��
	BoonInt32				i32FileLen;				//	�ļ���С��VERIFICATION_GetFile()�����ڴ�ʹ��
	BoonInt32				i32Offset;				//	�ڴ���ļ��е�ƫ����
	BoonInt32				i32Length;				//	�ڴ���ļ��еĳ���
}Boon_ALG_FILE_INFO_S;


/**********************************************************
	���ƣ�	VERIFICATION_CheckFile

	���ܣ�	����ļ��ĺϷ���

	������	BoonUint8 *_pucFile				����ļ�
			BoonInt32 _iFileLen				����ļ�����
			Boon_ALG_FILETYPE_E  _eFileType	����ļ�����
			BoonChar *_pcFileVersion 			�������ļ��汾
			BoonInt32 *_piOffset				��Ч���ݵ�ַƫ��


	���أ�	��ȷ�� Boon_ALG_OK
			���� Boon_ALG_PTR_NULL
				   Boon_ALG_FAIL

	������
**********************************************************/
BoonInt32	VERIFICATION_CheckFile( BoonUint8 *_pucFile,BoonInt32 _iFileLen,Boon_ALG_FILETYPE_E  _eFileType,BoonChar *_pcFileVersion,BoonInt32 *_piOffset);

#ifdef __cplusplus
}
#endif  

#endif 

