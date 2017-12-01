#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/core/core.hpp"
#include "opencv2/core/core_c.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>
#include <math.h>
#define min(x,y) (x)<(y)?(x):(y)
static unsigned char 	*g_u8Hzk24 = NULL;
static unsigned char 	*g_u8Asc24 = NULL;

#define HZK24SIZE 588822
#define ASC24SIZE 6150
#define BoonVoid void
#define BoonUint8 unsigned char 
#define BoonInt32 int
BoonVoid Public_ImageGray( BoonUint8 *_pucSrcImage, BoonUint8 *_pucDstImage, BoonInt32 _iWidth, BoonInt32 _iHeight)
{
	BoonInt32		i;
	BoonInt32		iGray;
	BoonUint8		*pucSrc, *pucDst;

	pucSrc = _pucSrcImage;
	pucDst = _pucDstImage;
	#pragma omp parallel for   
	for( i = 0;i < _iHeight * _iWidth; i++ )
	{
		BoonUint8 * pucSrc1 = 3*i + pucSrc;
		BoonInt32 iGray1 = ( (BoonInt32)pucSrc1[2] * 306 + (BoonInt32)pucSrc1[1] * 601 + (BoonInt32)pucSrc1[0] * 117 + 512 );
		pucDst[i] = iGray1>>10;
	}
}

int FastSobel(unsigned char *in, int width, int height, int widthStep,unsigned char *edg)
{
	
	int para = 6;

	for (int i=1;i<height-1;i++)
	{
		for (int j=1;j<width-1;j++)
		{
			  int tmp = 0;
                          tmp  = (in[i * widthStep + j + 1]* para + in[i * widthStep + j + 2]) - (in[i * widthStep + j - 2] + in[i * widthStep + j - 1]  * para );
			  edg[i * width + j] = min(255,sqrt(tmp * tmp)/2);
			  if(edg[i * width + j] < 100)
			    edg[i * width + j] = 0;
			  else
			    edg[i * width + j] = 255;
		}
		   int     Filline[1500];
		
		   int      pixNUM=0;
		   for (int j = 2; j < width-1; j++)
		   {
			
			if (edg[i * width + j] != edg[i * width + j -1] && edg[i * width + j] == 255)
			{
				
			   Filline[pixNUM++] = j;
				
			}			
		   }
		   
		   for (int j = 3; j < pixNUM - 2; j++)
		   {
			int zerotmp1 = Filline[j+2] -Filline[j+1];
			int zerotmp = Filline[j] - Filline[j-1];
			
			if(zerotmp < 20)
			{
				//printf("dd %d %d %d \n",i,Filline[j-1],zerotmp);
				for(int h = 0;h<zerotmp;h++)
				{
			  		if(edg[i * width + h + Filline[j-1] ]  == 0)
					{
					 	edg[i * width + h + Filline[j-1] ] = 255;
					}
				
				}
			}
		      
		  }



         }

	

         return 0;

}


int main(int argc,char*argv[])
{
 
  IplImage* img;
	 IplImage* frame;
 IplImage* logpolar_frame;

 

 
  

char name[48];
 char lastname[48];
  cvNamedWindow("1");
     cvNamedWindow("11");

	 CvCapture *capture=cvCreateFileCapture(argv[1]);

	
        frame = cvQueryFrame(capture);
	printf("width is %d height is %d \n",frame->width,frame->height);
	unsigned char * m1 = (unsigned char *)malloc(frame->width*frame->height);
	unsigned char * m2 = (unsigned char *)malloc(frame->width*frame->height);
	Public_ImageGray((unsigned char *)frame->imageData,m1,frame->width,frame->height);

 FastSobel(m1,frame->width,frame->height,frame->width,m2);
    

    cvShowImage("11",frame);

	
	CvMat* show_img6 = cvCreateMatHeader(frame->height,frame->width, CV_8UC1);
									show_img6->data.ptr = m2;
									cvNamedWindow("show6", 0);
							
									cvShowImage("show6", show_img6);
									cvSaveImage("qa.jpg",show_img6);
	     cvWaitKey(10000);							

  return 0;
}
