#ifndef  _Boon_ALGO_CONFIG_H_
#define	 _Boon_ALGO_CONFIG_H_

/********************************************************************
    Copyright (C), 1994-2012, ɽ��������Ϣ�Ƽ����޹�˾	
    �ļ�����: 	 Boon_algo_config.h 
    �ļ�����:    BOON�㷨��-�㷨Ӧ��ƽ̨ѡ��ͷ�ļ�
    �ļ�����:    ��ϣΰ
	���ܵȼ���	 ���ļ����ɹ������ڲ����ã����ṩ���㷨Ӧ���̿���
    �޸���ʷ:	 
	    
*********************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/********************************************************************
һ������ϵͳѡ�������㷨�Ż��ͱ��룬��ѡ
********************************************************************/
#define		WIN32_PLATFORM			0				//WIN32
#define		BIOS_PLATFORM			1				//DSP/BIOS
#define		LINUX_PLATFORM			2				//ARM/LINUX
#define		ALGORITHM_PLATFORM		LINUX_PLATFORM	//**�㷨���в���ϵͳ�������Ӧ��ѡ�񣬱���ѡ��**

/********************************************************************
����оƬ�ͺ�ѡ�������C674x��C64x+���Ż��������в�ͬ���Ǳ�ѡ
********************************************************************/
#define		PC_X86					10
#define		DSP_DM8127				11				//C674x��
#define		DSP_DM648				12				//C64x+��
#define		DSP_DM6467				13				//C64x+��
#define		DSP_DM6437				14				//C64x+��
#define		ARM_HI3531				21				//Cortex-A9˫��
#define		ARM_HI3516				22				//Cortex-A9����
#define		ARM_HI3518				23				//ARM926��,440M
#define		CHIP_TYPE				PC_X86		//**�㷨����оƬ�ͺ�ѡ��**
/********************************************************************
������Ʒ��̬ѡ����羯һ����뿨��һ�����ѡ�񣬷Ǳ�ѡ
********************************************************************/
#define		Boon_IPC_S3				10				//S3������
#define		Boon_IPC_S3E				11				//S3E������

#define		Boon_ITS_T217				20				//ITS���ڻ�
#define		RS_ITS_T217				21				//ROSEEK���ڻ�
#define		Boon_ITS_T218				22				//ITS�羯��

#define		Boon_DOM_SMART			30				//SMART���
#define		Boon_DOM_COOPER			31				//COOPER���
#define     Boon_DOM_S6				32				//S6�߶���ʹ��DM8127ƽ̨

#define		Boon_DVR_M7				40				//M7 DVR/NVR,Hi3531


#define		DJ_HOTRT_LAYER			Boon_ITS_T218		//�羯     
#define		ROAD_GATE				Boon_ITS_T217		//����

#define		PRODUCT_TYPE			Boon_ITS_T217     	//**�㷨���в�Ʒ�ͺ�ѡ��**

//#define		DEBUG_PRINT_ENABLE						//������Ϣ��ӡʹ���ܿ��أ���ģ���ڲ�ʹ�÷ֿ��أ���ʹ�ô�ӡ��Ϣʱע�͵����м���
//#define	DSP_TO_PC_ENABLE						//��Ҫ��PC�ϲ���DSP�汾����ʱ��ʹ��DSP_TO_PC_ENABLE 

#define		LOG_FILE_PATH			"D:\\log.txt"		


#ifdef __cplusplus
}
#endif
#endif 
