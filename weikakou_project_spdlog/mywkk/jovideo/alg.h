#ifndef _ALG_H_
#define _ALG_H_

typedef enum
{
	IMAGE_FORMAT_Boon_YUV422	= 0,			//	图像是YUV422格式，planar存储，YUV分别放不同内存
	IMAGE_FORMAT_Boon_YUV420	= 1,			//	图像是YUV420格式，planar存储，YUV分别放不同内存			
	Boon_ALG_RGB888_PACKED	= 2,			//	图像是RGB888格式，packed存储，BGR混合存放:BGRBRG
	Boon_ALG_YUV422_PACKED	= 3,			//	图像是YUV422格式，packed存储，YUV混合存放:UYVY，如DM6437平台
	Boon_ALG_YUV420_MIXED		= 4,			//	图像是YUV422格式，Y单独一块内存，UV共用一块内存，如DM8127平台
	Boon_ALG_YUV422_MIXED		= 5,			//	图像是YUV420格式，Y单独一块内存，UV共用一块内存，如DM6467平台
	Boon_ALG_GRAY				= 6,			//	灰度图，只有Y
 }Boon_ALG_IMAGE_FORMAT_E;

typedef struct
{
	int					iWidth;				// 图像宽度
    int					iHeight;			// 图像高度
	char 					*pucD1;				// 图像分量1 数据指针
		unsigned char			*pucD2;				// 图像分量2 数据指针
	unsigned char				*pucD3;				// 图像分量3 数据指针
	unsigned long long 			ui64Time;			// 时间
	int					iFlag;				// 标志
	Boon_ALG_IMAGE_FORMAT_E	eFormat;			// 格式
} Boon_ALG_IMAGE3_S;

typedef	void * (*video_create)(int  _iSeg, char * _pcKey);
	
typedef int (*video_init)(int _iImgW, int _iImgH);
typedef int (*video_process)(Boon_ALG_IMAGE3_S* _pstImage);

typedef int (*video_get_result)(char *plate,int *color);



#endif
