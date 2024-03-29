﻿#include "demo.h"
#include <iconv.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <unistd.h>
#include <sys/time.h>
static unsigned char 	*g_u8Hzk24 = NULL;
static unsigned char 	*g_u8Asc24 = NULL;

#define HZK24SIZE 588822
#define ASC24SIZE 6150




typedef	void * (*video_create)(int  _iSeg, char * _pcKey);
	
typedef int (*video_init)(int _iImgW, int _iImgH);
typedef int (*video_process)(Boon_ALG_IMAGE3_S* _pstImage);
typedef int (*video_get_result)(char *plate,int *color);


int Code_Convert(char *from_charset,char *to_charset,char *inbuf,size_t inlen,char *outbuf,size_t outlen)
{
iconv_t cd;
int rc;
char **pin = &inbuf;
char **pout = &outbuf;

cd = iconv_open(to_charset,from_charset);
if (cd==0) return -1;
memset(outbuf,0,outlen);
if (iconv(cd,pin,&inlen,pout,&outlen)==-1) return -1;
iconv_close(cd);
return 0;
}
int Utf8toGb2312(char *inbuf,size_t inlen,char *outbuf,size_t outlen)
{
return Code_Convert("utf-8","gb2312",inbuf,inlen,outbuf,outlen);
}

int Gb2312toUtf8(char *inbuf,size_t inlen,char *outbuf,size_t outlen)
{
return Code_Convert("gb2312","utf-8",inbuf,inlen,outbuf,outlen);
}


void osd_DrawDot(int _x,int _y,unsigned long _u32Color,unsigned char* _btSurface,int _width)
{
    int bitCount = 3;   //RGB1555
    int dist = _width*bitCount;
    unsigned char* btOff = _btSurface + dist*_y + _x*bitCount;

	*((unsigned char*)btOff) = _u32Color;
	*((unsigned char*)btOff + 1) = _u32Color;
	//黑边，当前点的右侧及下方的点为黑色
	*((unsigned char *)(btOff+2)) 	= 0x0033;
	*((unsigned char *)(btOff+dist)) = 0x0000;
	
}
void osd_DrawStringToRGBEx(int _iPx, int _iPy,int _ix,int _iy,int _iWidth,
	unsigned long _FontColor, unsigned long _BackColor,char* _cChar,unsigned char* _btSurface)
{
	int i, j, k, n, ix, iy;
	int qh,wh,offset;
	 int nn;
	unsigned char * buf;
	unsigned char dot16bufQ[32];  /*存放16*16全角字符点阵*/
	unsigned char dot16bufB[16];  /*存放16*16半角字符点阵*/
	unsigned char dot24bufQ[72];  /*存放24*24全角字符点阵*/
	unsigned char dot24bufB[48];  /*存放24*24半角字符点阵*/
    int iSum = 0;
	int iPx = (_iPx)?_iPx:1;
	int iPy = (_iPx)?_iPx:1;
	int y = _iy;
	int iPos=_ix; 
	
	const int Mask[] = {0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};

	int width = _iWidth;
	i=0;
    n=0;  
			
   
    buf  = (unsigned char *)_cChar;
	nn = strlen((char *)buf);

	while(buf[i] )
	{   iSum++;
		if(iSum>64)break;
		
		if((buf[i]>=0xa0)&&(buf[i+1]>=0xa0))
		{
			qh=buf[i]-0xa0;
			wh=buf[i+1]-0xa0;
			n = n - 2;
			if(_iPy == 0)
			{
				
			}
			else if(_iPy == 1)
			{
                               
				offset=(94*(qh-1)+(wh-1))*72;
				if(offset>HZK24SIZE)
				{
					//Boon_printf(0xff0000, "HZK24 overflow!!, %x, %x, %x\n",qh,wh, buf[i]);
					buf[i] = ' ';
					buf[i+1] = ' ';
					continue;
				}
				memcpy(dot24bufQ,g_u8Hzk24+offset,72);
                       
				for(n=0;n<24;n++)
				{
					for(j=0;j<3;j++)
					{
						for(k=0;k<8;k++)
						{
							if(dot24bufQ[n*3+j]&Mask[k])
							{
                                                     
								for(ix=0; ix<iPx; ix++)
								{
									for(iy=0; iy<iPy; iy++)
									{
										osd_DrawDot(iPos+j*8*iPx+k*(iPx)+ix, y+n*iPy+iy+2,_FontColor,_btSurface,width);
									}
								} 
							}
							else if(_BackColor != 0)
							{
                                                     
								for(ix=0; ix<iPx; ix++)
								{
									for(iy=0; iy<iPy; iy++)
									{
										osd_DrawDot(iPos+j*8*iPx+k*(iPx)+ix, y+n*iPy+iy+2,_BackColor,_btSurface,width);
									}
								}
							}
						}
					}
				}
				
				iPos+=24*iPx;
			}
			
			i+=2;
		}
		else if(buf[i]<0xa0)
		{
                         nn = nn -1;
			if(_iPy == 0)
			{
				
			}
			else if(_iPy == 1)
			{
				offset = (buf[i])*48;
				if(offset>ASC24SIZE)
				{
					//Boon_printf(0xff0000, "ASC24 overflow!!, %x, %x, %x\n",qh,wh, buf[i]);
					buf[i] = ' ';
					continue;
				}
                                //printf("offset is %d\n",offset);
				memcpy(dot24bufB,g_u8Asc24+offset,48);
                                
				for(n=0;n<24;n++)
				{
					for(j=0;j<2;j++)
					{
						for(k=0;k<8;k++)
						{
							if(dot24bufB[n*2+j]&Mask[k])
							{
                                                           //printf("11\n");
								for(ix=0; ix<iPx; ix++)
								{
									for(iy=0; iy<iPy; iy++)
									{
										osd_DrawDot(iPos+j*8*iPx+k*iPx+ix,y+n*iPy+iy+4,_FontColor,_btSurface,width);
									}
								}
							}
							else if(_BackColor != 0)
							{
                                                          // printf("22\n");
								for(ix=0; ix<iPx; ix++)
								{
									for(iy=0; iy<iPy; iy++)
									{
										osd_DrawDot(iPos+j*8*iPx+k*iPx+ix,y+n*iPy+iy+4,_BackColor,_btSurface,width);
									}
								}
							}
						}
					}
				}
				
				iPos+=12*iPx;
			}
			
			i+=1;
		}
	}
}
int LoadHZKResourse(void)
{
	FILE *pFontFile = NULL;
	int iReadLen;

	
	if(!g_u8Hzk24)
		g_u8Hzk24=(unsigned char*)malloc(HZK24SIZE);
	if(!g_u8Asc24)
		g_u8Asc24=(unsigned char*)malloc(ASC24SIZE);


	memset(g_u8Hzk24, 0, HZK24SIZE);
	memset(g_u8Asc24, 0, ASC24SIZE);
	
	

	
	pFontFile = fopen("../data/ASC24", "rb");
	if(pFontFile == NULL)
	{
		//Boon_printf(0xFF0000,"hzk24 read error!");
		return 0;
	}
	iReadLen = fread(g_u8Asc24, sizeof(char), ASC24SIZE, pFontFile);
	if(iReadLen<ASC24SIZE)
	{
		//Boon_printf(0xFF0000,"Asc24 read error!");
		return 0;
	}
	fclose(pFontFile);
	
	pFontFile = fopen("../data/HZK24", "rb");
	if(pFontFile == NULL)
	{
		return 0;
	}
	iReadLen = fread(g_u8Hzk24, sizeof(char), HZK24SIZE, pFontFile);
	if(iReadLen<HZK24SIZE)
	{
		//Boon_printf(0,"hzk24 read error!");
		return 0;
	}
	fclose(pFontFile);

	//到这里,说明支持24*24字库tzl add 2013.10.29
	
	
	return 0;
}


int main(int argc,char*argv[])
{
  
  void *PtrOut;
  BoonUint8  *srcImg;
  int result;
  int i = 0;
  int j = 0;
  int num = 1;
  int num1 = 0;
  float maxconid = 0;
  int maxheight = 0;
  int params[3];
  void *LibHandle = NULL;
  IplImage* img;
	 IplImage* frame;
 IplImage* logpolar_frame;
  Boon_ALG_IMAGE_S image;
 
  FILE *fp;
  FILE *fp1;
  FILE *fp2;
  long int time1 = 0;
  long int time2 = 0;
  char str[160];   // 假定文件数不超过30个
  char str1[160];   // 假定文件数不超过30个
  char str2[160];   // 假定文件数不超过30个
  int n=0;


  video_create Video_create;
  video_init Video_init;
  video_process Video_process;
  video_get_result Video_get_result;
LoadHZKResourse();

	 LibHandle = dlopen("../lib/libalg_video.so", RTLD_LAZY);
 
    if(NULL == LibHandle)
  {
     printf("LoadLibrary fail %s \n",dlerror());
     return 0;
  }
  Video_create = (video_create)dlsym(LibHandle,"BoonAlgo_TRIP_Creat");
 if(NULL ==   Video_create)
  {
	 printf("LCreate fail \n");
	 return 0;
  }
  Video_init = (video_init)dlsym(LibHandle,"BoonAlgo_TRIP_Init");
  Video_process = (video_process)dlsym(LibHandle,"BoonAlgo_TRIP_Process");
  Video_get_result = (video_get_result)dlsym(LibHandle,"BoonAlgo_TRIP_GetResults");

  Video_create(0,NULL);

  

  
   int rtn = Video_init(1920,1080);




 
   unsigned char rty[50];


  
 
 //system("dir /n *.jpg  /B  > log.txt");
 fp=fopen("../conf/log.txt","r");
 fp2=fopen("../conf/data.txt","r");
 fp1=fopen("../conf/chepai.txt","w+");
 
  

char name[48];
 char lastname[48];
 // cvNamedWindow("1");
  //  cvNamedWindow("11");
//    cvNamedWindow("111");
   image.iColorMode = 0;
   image.iChannels = 3;
   image.iDepth = 8;
   image.iImageSize = sizeof(Boon_ALG_IMAGE_S);  

char s[64] = "rtsp://192.168.1.201:554/live0.h264";
	//char s[64] = "rtsp://211.87.227.248:50035/live0.h264";
//char s[64] = "rtsp://123.233.246.99:50009/live0.h264";
//char s[64] = "rtsp://192.168.1.11/stream_main";
//	CvCapture *capture=cvCreateFileCapture(argv[1]);
//
//	char s[64] = argv[1];
	retry:
	CvCapture *capture=cvCreateFileCapture(s);
		struct timeval tv1;
	struct timeval tv2;
	char plate[22];
//	CvVideoWriter *writer =cvCreateVideoWriter("111.avi", CV_FOURCC('X', 'V', 'I', 'D'), 25, cvSize(960,540));
     int fuji_num = 0;
     int pic_num = 0;
   while(1)
   {
	
        frame = cvQueryFrame(capture);
	pic_num++;
	/*if(num1 < 20)
	{
		frame = cvLoadImage("44.jpg",CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
	}
	else if(num1 >= 20 && num1 < 40  )
	{
		frame = cvLoadImage("55.jpg",CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
	}
	else 
	{
		frame = cvLoadImage("44.jpg",CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
	}
	if(num1 > 60)
	{
	break;

	}*/
	if(!frame)break;
	num1++;

	  
	//cvWriteFrame(writer,frame); 
	
	
    //  cvWaitKey(1);
   gettimeofday(&tv1,NULL);
 //  cvShowImage("11",frame);
//cvSaveImage("111.jpg",frame);
	
	
	srcImg = (BoonUint8  *)frame->imageData;
	
	
	  image.iWidth = frame->width;
	  image.iHeight = frame->height;
	  image.pucData = (BoonUint8  *)malloc(image.iWidth * image.iHeight *image.iChannels );
	  if(image.pucData == NULL)
	  {
	   printf("malloc2 error \n");
	   return 0;
	  }
	  memcpy(image.pucData,srcImg,image.iWidth * image.iHeight *image.iChannels);
	
	
	int color = 0;
	 Boon_ALG_IMAGE3_S image1;
	image1.iWidth = 1920;
   image1.iHeight = 1080;  
	image1.pucD1 = image.pucData;

	int rtn = Video_process(&image1);
 	
	if(rtn < 0)
		{
            printf("process fail \n");
	    }
	int fuji;
	rtn = Video_get_result(plate,&color);
gettimeofday(&tv2,NULL);
char plate_gbk[100];
bzero(plate_gbk,100);
Utf8toGb2312(plate,strlen(plate),plate_gbk,100);

  
	//printf("A time is %d ms \n",tv2.tv_sec*1000 + tv2.tv_usec/1000 - tv1.tv_sec*1000 - tv1.tv_usec/1000);		
	if(rtn == 5)
	{
		params[0] = CV_IMWRITE_JPEG_QUALITY;
		params[1] = 90;//设置s压缩度
		//IplImage *desc;  
   		// CvSize sz;  
		//sz.width = 640;  
        	//sz.height = 480; 
		//desc = cvCreateImage(sz,frame->depth,frame->nChannels);   
		//cvResize(frame,desc,CV_INTER_CUBIC); 
		cvSaveImage("/home/boon/a.jpg",frame,params); 
		//cvReleaseImage(&desc);  
		   printf("车牌 is %s  corlor is %d\n",plate,color);   

		  time_t now ;
             struct tm *tm_now ;
             time(&now) ;
             tm_now = localtime(&now) ;
	     char nowtime[1024];
        sprintf(nowtime,"%d-%d-%d %d:%d:%d", tm_now->tm_year+1900, tm_now->tm_mon+1, tm_now->tm_mday, tm_now->tm_hour, tm_now->tm_min, tm_now->tm_sec) ;


		                char qingbao[1024];
    		  char buf[] = "Expect:";
		 curl_global_init(CURL_GLOBAL_ALL);

            curl_httppost *post = NULL;
            curl_httppost *last =NULL;



            sprintf(qingbao,"{\"time\":\"%s\",\"dev\":\"%s\",\"name\":\"%s\",\"channel\":\"%s\",\"vehicle\":{\"plate\":\"%s\",\"color\":\"%s\",\"brand\":\"%s\",\"type\":\"%s\"}}",nowtime,"110","明湖小区","",plate,"","","");
            CURL*easy_handle = curl_easy_init();
            curl_slist *headerlist=NULL;
	    CURLcode res;
            headerlist = curl_slist_append(headerlist, buf);
            //curl_slist *headerlist = curl_slist_append(NULL,"Content-Type:application/json;charset=UTF-8");
            if(easy_handle)
            {
             
                curl_formadd(&post, &last, CURLFORM_COPYNAME, "qingbao", CURLFORM_COPYCONTENTS,qingbao, CURLFORM_END);
                curl_formadd(&post, &last, CURLFORM_COPYNAME, "data",CURLFORM_FILE,"/home/boon/a.jpg", CURLFORM_END);
          
                curl_easy_setopt(easy_handle, CURLOPT_HTTPHEADER, headerlist);

                curl_easy_setopt(easy_handle, CURLOPT_SSL_VERIFYPEER, 0);
                curl_easy_setopt(easy_handle, CURLOPT_SSL_VERIFYHOST, 1);
//		curl_easy_setopt(easy_handle, CURLOPT_PROXY, "211.87.227.249:3128"); 
                curl_easy_setopt(easy_handle, CURLOPT_CAINFO,"../data/ca-sj.crt");
                curl_easy_setopt(easy_handle,CURLOPT_SSLCERT,"../data/client-sj.crt");
                curl_easy_setopt(easy_handle,CURLOPT_SSLCERTPASSWD,"hellohello");
                curl_easy_setopt(easy_handle,CURLOPT_SSLCERTTYPE,"PEM");
                curl_easy_setopt(easy_handle,CURLOPT_SSLKEY,"../data/client-sj.key.pem");
                curl_easy_setopt(easy_handle,CURLOPT_SSLKEYPASSWD,"hellohello");
                curl_easy_setopt(easy_handle,CURLOPT_SSLKEYTYPE,"PEM");
                curl_easy_setopt(easy_handle,CURLOPT_VERBOSE,1);
                 curl_easy_setopt(easy_handle,CURLOPT_TIMEOUT,3);
                curl_easy_setopt(easy_handle, CURLOPT_URL, "http://123.233.246.99:120/picUpload1.php");
                //curl_easy_setopt(easy_handle, CURLOPT_URL, "http://127.0.0.1/xampp/picUpload.php");
                curl_easy_setopt(easy_handle, CURLOPT_HTTPPOST, post);

                res = curl_easy_perform(easy_handle);
                if(res != CURLE_OK)
                {

                    printf("            [error]         [eroor %d]\n","123",res);
                }
                else
                {

                    printf("%s successs\n","123");
                }


             
            }

            curl_easy_cleanup(easy_handle);
            curl_formfree(post);
            curl_slist_free_all (headerlist);
            curl_global_cleanup();
	}
	if(rtn == 6)
	{
		//cvShowImage("111",frame);	
		//fuji_num = pic_num;
	}
	
	free(image.pucData);
//	cvReleaseImage(&frame);
	
	if(num1 > 500)
	{
		break;	
	}
		
}
     // printf("error num is %d\n",num1);
     cvReleaseCapture(&capture);
     num1 = 0;
     goto retry;
     printf("load img avg time is %03d   process  avg time  is %03d\n",time1,time2);
     free(g_u8Asc24);
	 free(g_u8Hzk24);
	
	 fclose(fp);
	 fclose(fp1);

	
  return 0;
}
