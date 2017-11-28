#ifndef _H_ivsconfig_H__
#define _H_ivsconfig_H__

//定义版本号；
#include "Boon_algo.h"
#define Boon_MAJOR_VERSION    3
#define Boon_MINOR_VERSION    0
#define Boon_SUBMINOR_VERSION 3

#define BOONAUX_STR_EXP(__A)  #__A
#define BOONAUX_STR(__A)      BOONAUX_STR_EXP(__A)
#define Boon_VERSION          BOONAUX_STR(Boon_MAJOR_VERSION) "." BOONAUX_STR(Boon_MINOR_VERSION) "." BOONAUX_STR(Boon_SUBMINOR_VERSION)

#ifndef Boon_ABS_REGION
#define Boon_ABS_REGION				65536						/* 适用于求距离、亮度差值的绝对值 */
#define Boon_ABS_ZEROPOS				Boon_ABS_REGION / 2
#endif

#define Boon_HITTRACK												/*碰撞跟踪*/

#define Boon_MAXMATCHNUM				4
#define Boon_MAXSUBMNUM				2							/*最大子模块数*/

#ifndef IVSMIN
#define IVSMIN(a, b)	((a)<(b) ? (a) : (b))
#endif

#ifndef IVSMAX
#define IVSMAX(a, b)	((a)>(b) ? (a) : (b))
#endif

#ifndef IVSABS
#define IVSABS(a)		((a) > 0 ? (a) : -(a))
#endif

#ifndef IVSSQUARE
#define IVSSQUARE(a)	((a) * (a))
#endif

//高级参数解析
#define PARSESTR_START \
	char para_value[256]; \
	const char * str_find; 
//	para_buffer[buffer_length-1] = '\000';

#define PARSESTR_UINT8(pcBuffer, name, value) \
	str_find = strstr( pcBuffer, (name) ); \
	if(str_find) \
{ \
	str_find += strlen( (name) ); \
	sscanf(str_find, "%s", para_value); \
	(value) = (unsigned char)atoi(para_value); \
}

#define PARSESTR_UINT32(pcBuffer, name, value) \
	str_find = strstr( (const char *)pcBuffer, ((const char *)name) ); \
	if(str_find) \
{ \
	str_find += strlen( (name) ); \
	sscanf(str_find, "%s", para_value); \
	(value) = (unsigned int)atoi(para_value); \
}

#define PARSESTR_DOUBLE(pcBuffer, name, value) \
	str_find = strstr((const char *)pcBuffer, ((const char *)name) ); \
	if(str_find) \
{ \
	str_find += strlen( (name) ); \
	sscanf(str_find, "%s", para_value); \
	(value) = (double)atof(para_value); \
}

/* fight in IVS */
//#define HAVE_IVS_FIGHT

/* get up in IVS */
//#define HAVE_IVS_GETUP

/* Court funcs in IVS */
//#define HAVE_IVS_COURT

/* usb key in IVS */
//#define HAVE_IVS_USBKEY

/* Mutex Lock in IVS */
//#define HAVE_IVS_MUTEX

#endif // _H_ivsconfig_H__
