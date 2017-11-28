#ifndef _BOON_CODEC_H
#define _BOON_CODEC_H
#define WIDTH  		960
#define HEIGHT 		540

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libswscale/swscale.h>
};

class VideoDecoder
{
public:
	AVCodec         *codec;
    AVCodecContext  *ctx;
	AVFrame         *frame;
    AVFrame 		*pFrameYUV;
	AVFrame         *pFrameRGB;
	AVPacket        avpkt;
	SwsContext      *img_convert_ctx;
    uint8_t * rgbBuffer;
    int num;
public:
    VideoDecoder();
    ~VideoDecoder();
    bool h264_init();
	bool h264_2_rgb(unsigned char *inputbuf, int frame_size, unsigned char *outputbuf, unsigned int*outsize);
	void h264_release(void);
};

#endif
