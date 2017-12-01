#include "codec.h"

#include <stdio.h>
#include <stdlib.h>

bool VideoDecoder::h264_init()
{
    codec = NULL;
    ctx= NULL;
    frame = NULL;
    pFrameRGB = NULL;
    img_convert_ctx = NULL;

    avcodec_register_all();
    av_init_packet(&avpkt);
    printf("code init\n");

    codec=avcodec_find_decoder(AV_CODEC_ID_H264);

    if(!codec)
    {
        printf("Codec not found\n");
    }

    ctx = avcodec_alloc_context3(codec);
    if(!ctx)
    {
        printf("Could not allocate video codec context\n");
    }
    ctx->pix_fmt = AV_PIX_FMT_YUV420P;
    //ctx->sw_pix_fmt =AV_PIX_FMT_YUV420P ;

    if(avcodec_open2(ctx,codec,NULL)<0)
    {
        printf("Could not open codec\n");
    }

    frame=avcodec_alloc_frame();
    if(!frame)
    {
        printf("Could not allocate video frame\n");
    }

    pFrameYUV=avcodec_alloc_frame();
    if(!pFrameYUV)
    {
        printf("Could not allocate video frame\n");
    }

    pFrameRGB=avcodec_alloc_frame();

    if(!pFrameRGB)
    {
        printf("Could not allocate video frame\n");
    }

    num = avpicture_get_size(AV_PIX_FMT_RGB24,WIDTH,HEIGHT);
    //printf("-------%d-----\n",num);
    //avpicture_alloc((AVPicture *)pFrameRGB,AV_PIX_FMT_RGB24,WIDTH,HEIGHT);
        rgbBuffer = (uint8_t *) av_malloc(num * sizeof(uint8_t));
    avpicture_fill((AVPicture *)pFrameRGB, rgbBuffer, AV_PIX_FMT_RGB24,WIDTH,HEIGHT);
    /*
    printf("111112344\n");
    int numBytes = avpicture_get_size(AV_PIX_FMT_RGB32, WIDTH,HEIGHT);
        avpicture_fill((AVPicture *) pFrameRGB, rgbBuffer,AV_PIX_FMT_RGB32,WIDTH, HEIGHT);
    */
    img_convert_ctx = sws_getContext(WIDTH,HEIGHT,AV_PIX_FMT_YUV420P,WIDTH,HEIGHT,AV_PIX_FMT_RGB24,SWS_BICUBIC,NULL,NULL,NULL);
    return true;
}

bool VideoDecoder::h264_2_rgb(unsigned char *inputbuf, int frame_size, unsigned char *outputbuf, unsigned int*outsize)
{
    avpkt.size=frame_size;
//    printf("frame size is %d\n",frame_size);
    if(avpkt.size==0)
    {
        printf("picture size is 0.\n");
        return false;
    }

    avpkt.data=inputbuf;


    if(avpkt.size>0)
    {
        int decode_size=0;
        int av_result=0;

        av_result=avcodec_decode_video2(ctx,frame,&decode_size,&avpkt);
        if(av_result<0)
        {
            //printf("decode failed: inputbuf = 0x%d , input_framesize = %d",(int)avpkt.data, avpkt.size);
            return false;
        }
        //printf("color space %d\n",frame->width);
        //avpicture_fill((AVPicture *)pFrameYUV,(uint8_t *)(frame->data),AV_PIX_FMT_YUV420P,WIDTH,HEIGHT);

        sws_scale(img_convert_ctx,(const uint8_t *const *)(frame->data),frame->linesize,0,HEIGHT,(uint8_t *const *)(pFrameRGB->data),pFrameRGB->linesize);

        //printf("width %d,height %d\n",pFrameRGB->width,pFrameRGB->height);
        memcpy(outputbuf,(unsigned char *)rgbBuffer,WIDTH*HEIGHT*3);
        return true;
    }
    else
    {
        return false;
    }
    free(rgbBuffer);
}

void VideoDecoder::h264_release(void)
{

}


VideoDecoder::VideoDecoder()
{
    printf("video init\n");
    h264_init();
}

VideoDecoder::~VideoDecoder()
{

}
