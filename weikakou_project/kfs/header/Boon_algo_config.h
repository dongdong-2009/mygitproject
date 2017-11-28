#ifndef  _Boon_ALGO_CONFIG_H_
#define	 _Boon_ALGO_CONFIG_H_

/********************************************************************
    Copyright (C), 1994-2012, 山东博昂信息科技有限公司	
    文件名称: 	 Boon_algo_config.h 
    文件描述:    BOON算法部-算法应用平台选择头文件
    文件作者:    孙希伟
	保密等级：	 本文件不可公开，内部公用，不提供给算法应用商开发
    修改历史:	 
	    
*********************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/********************************************************************
一、操作系统选择，用于算法优化和编译，必选
********************************************************************/
#define		WIN32_PLATFORM			0				//WIN32
#define		BIOS_PLATFORM			1				//DSP/BIOS
#define		LINUX_PLATFORM			2				//ARM/LINUX
#define		ALGORITHM_PLATFORM		LINUX_PLATFORM	//**算法运行操作系统，需根据应用选择，必须选择**

/********************************************************************
二、芯片型号选择，如针对C674x与C64x+的优化方法会有不同，非必选
********************************************************************/
#define		PC_X86					10
#define		DSP_DM8127				11				//C674x核
#define		DSP_DM648				12				//C64x+核
#define		DSP_DM6467				13				//C64x+核
#define		DSP_DM6437				14				//C64x+核
#define		ARM_HI3531				21				//Cortex-A9双核
#define		ARM_HI3516				22				//Cortex-A9单核
#define		ARM_HI3518				23				//ARM926核,440M
#define		CHIP_TYPE				PC_X86		//**算法运行芯片型号选择**
/********************************************************************
三、产品形态选择，如电警一体机与卡口一体机的选择，非必选
********************************************************************/
#define		Boon_IPC_S3				10				//S3监控相机
#define		Boon_IPC_S3E				11				//S3E监控相机

#define		Boon_ITS_T217				20				//ITS卡口机
#define		RS_ITS_T217				21				//ROSEEK卡口机
#define		Boon_ITS_T218				22				//ITS电警机

#define		Boon_DOM_SMART			30				//SMART球机
#define		Boon_DOM_COOPER			31				//COOPER球机
#define     Boon_DOM_S6				32				//S6高端球，使用DM8127平台

#define		Boon_DVR_M7				40				//M7 DVR/NVR,Hi3531


#define		DJ_HOTRT_LAYER			Boon_ITS_T218		//电警     
#define		ROAD_GATE				Boon_ITS_T217		//卡口

#define		PRODUCT_TYPE			Boon_ITS_T217     	//**算法运行产品型号选择**

//#define		DEBUG_PRINT_ENABLE						//调试信息打印使能总开关，各模块内部使用分开关，不使用打印信息时注释掉本行即可
//#define	DSP_TO_PC_ENABLE						//需要在PC上测试DSP版本代码时，使能DSP_TO_PC_ENABLE 

#define		LOG_FILE_PATH			"D:\\log.txt"		


#ifdef __cplusplus
}
#endif
#endif 
