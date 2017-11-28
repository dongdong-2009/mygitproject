#include "jovideo.h"
//#include "shmem.h"
#include <stdlib.h>
#include <dlfcn.h>
#include "alg.h"
#include "Boon_algo_type.h"
#include "Boon.h"
#include <jsoncpp/json/json.h>

#define HZK24SIZE 588822
#define ASC24SIZE 6150
#define	SM_BUF_SIZE	(960*540*3)


static unsigned char 	*g_u8Hzk24 = NULL;
static unsigned char 	*g_u8Asc24 = NULL;


typedef Boon_HANDLE (*lCreate)(BoonInt32 _iSeg, BoonChar * _pcKey);
typedef BoonInt32 (*lInit)(Boon_HANDLE _hModule, BoonInt32 _iWidth,
                           BoonInt32 _iHeight);
typedef BoonInt32 (*lProcess)(Boon_HANDLE _hModule,
                              Boon_ALG_IMAGE_S * _pstInput, Boon_ALG_LPROutput_S *_pstLPRDetect,
                              Boon_ALG_LPROutputMulti_S* _pstOutput);
typedef BoonInt32 (*lRelease)(Boon_HANDLE _hModule);
typedef BoonInt32 (*lGetversion)(Boon_HANDLE _hModule, BoonUint8 *_pucVersion);
BoonInt32	Public_ImageInterpolation1(BoonUint8 *_pucSrcImage, BoonUint8 *_pucDstImage, BoonInt32 _iSrcWidth,BoonInt32 _iSrcHeight, BoonInt32 _iNewWidth, BoonInt32 _iNewHeight)
{
    BoonUint32 precision = 11;

    BoonInt32	k = 0;
    BoonInt32	iTemp1 = 0;
    BoonInt32 iTemp2 = 0;
    BoonInt32 i = 0;
    BoonInt32 j = 0;
    BoonInt32 iSrcX = 0;
    BoonInt32 iSrcY = 0;
    BoonInt32 ly = 0;
    BoonInt32 lx = 0;
    BoonInt32 x = 0;
    BoonInt32 y = 0;
    BoonInt32 iSrcStep = _iSrcWidth / sizeof(BoonUint8);
    BoonInt32 iDstStep = _iNewWidth / sizeof(BoonUint8);
    BoonUint8	* pucSrcData = _pucSrcImage;
    BoonUint8	* pucDstdata = _pucDstImage;
    BoonInt32	iScaleX = ((_iSrcWidth) << precision) / (_iNewWidth);
    BoonInt32 iScaleY = ((_iSrcHeight) << precision) / (_iNewHeight);
    BoonInt32	iTempSrc1 = 0;
    BoonInt32 iTempSrc2 = 0;
    BoonInt32 iTempRound = 0;

    BoonUint32 precision1 = (1 <<precision -1);
    BoonUint32 precision2 = 1;
    BoonInt32 aSrcX  =0;

    BoonUint32 xz = 0;
    BoonUint16 xx = 0;
    BoonInt32 iTemp3 = 0;
    BoonUint8 d1 = 0;
    BoonUint8 d3 = 0;
    BoonUint8 d2 = 0;
    BoonUint8 d4 = 0;
    for(j = 0; j<precision-1; j++)
    {
        precision2 <<= 1;
        precision2 ++;
    }

    for(j = 0; j<_iNewHeight-1; j++)
    {
        k = j * iDstStep;
        i = _iNewWidth - 1;
        iSrcX = _iSrcWidth - 1;
        iSrcY = j * iScaleY;
        ly = (iSrcY >> precision);
        y = iSrcY - (ly << precision);
        iTempSrc1 = ly * iSrcStep + iSrcX;

        if((ly + 1) > _iSrcHeight - 1)
        {
            iTempSrc2 = ly * iSrcStep + iSrcX;
        }
        else
        {
            iTempSrc2 = (ly + 1) * iSrcStep + iSrcX;
        }

        pucDstdata[3*k + 3*i] = (((pucSrcData[iTempSrc1*3] << precision) + y * (pucSrcData[iTempSrc2*3] -
                                 pucSrcData[iTempSrc1*3])) >> precision);
        pucDstdata[3*k + 3*i + 1] = (((pucSrcData[iTempSrc1*3 + 1] << precision) + y * (pucSrcData[iTempSrc2*3 + 1] -
                                     pucSrcData[iTempSrc1*3 + 1])) >> precision);
        pucDstdata[3*k + 3*i + 2] = (((pucSrcData[iTempSrc1*3 + 2] << precision) + y * (pucSrcData[iTempSrc2*3 + 2] -
                                     pucSrcData[iTempSrc1*3 + 2])) >> precision);

    }


    for(i=0; i<_iNewWidth-1; i++)
    {
        k = (_iNewHeight - 1) * iDstStep;
        iSrcX = i * iScaleX;
        iSrcY = _iSrcHeight - 1;
        lx = (iSrcX >> precision);
        x = iSrcX - (lx << precision);
        iTempSrc1 = iSrcY * iSrcStep + lx;

        if((lx + 1) > (_iSrcWidth - 1))
        {
            iTempSrc2 = iSrcY * iSrcStep + lx;
        }
        else
        {
            iTempSrc2 = iSrcY * iSrcStep + lx +1 ;
        }

        pucDstdata[3*k + i*3] = (((pucSrcData[iTempSrc1*3] << precision) + x * (pucSrcData[iTempSrc2*3]-
                                 pucSrcData[iTempSrc1*3]))>> precision);
        pucDstdata[3*k + i*3 + 1] = (((pucSrcData[iTempSrc1*3+1] << precision) + x * (pucSrcData[iTempSrc2*3+1]-
                                     pucSrcData[iTempSrc1*3+1]))>> precision);
        pucDstdata[3*k + i*3 + 2] = (((pucSrcData[iTempSrc1*3+2] << precision) + x * (pucSrcData[iTempSrc2*3+2]-
                                     pucSrcData[iTempSrc1*3+2]))>> precision);


    }

    for(j=0; j<_iNewHeight-1; j++)
    {
        int ly1 =0;
        int ly2 =0;
        k = j * iDstStep;
        iSrcY = j * iScaleY + (iScaleY >> 1) - precision1;
        if(iSrcY < 0)
        {
            iSrcY = 0;
        }
        ly = (iSrcY >> precision);
        y = iSrcY - (ly << precision);

        ly1 = ly * iSrcStep;
        ly2 = (ly +1) * iSrcStep;
        if((ly + 1) > (_iSrcHeight - 1))
            ly2 = ly * iSrcStep;

        aSrcX = (iScaleX >> 1) - precision1;
        for (i=0; i<_iNewWidth-1; i++)
        {

            iSrcX = aSrcX;
            aSrcX += iScaleX;
            if(iSrcX < 0)
            {
                iSrcX = 0;
            }

            xz = iSrcX >> precision;
            xx = iSrcX & precision2;
            iTempSrc1 = (ly1 + xz)*3;
            iTempSrc2 = (ly2 + xz)*3;


            d1 = pucSrcData[iTempSrc1];
            d3 = pucSrcData[iTempSrc2];
            d2 = pucSrcData[(iTempSrc1 +1)];
            d4 = pucSrcData[(iTempSrc2 +1)];

            iTemp1 = (d1 << precision);
            iTemp2 = (d3 << precision);
            if((xz + 1) <= (_iSrcWidth - 1))
            {
                iTemp1 += xx * (d2 - d1);
                iTemp2 += xx * (d4 - d3);
            }
            iTemp3 = iTemp2 - iTemp1;

            iTempRound = (((iTemp1 << precision) + y * ((iTemp3))) >> precision) + precision1;

            pucDstdata[3*k + i*3 ] = (BoonUint8)(iTempRound >> precision);





            d1 = pucSrcData[iTempSrc1+ 1];
            d3 = pucSrcData[iTempSrc2 + 1];
            d2 = pucSrcData[iTempSrc1 +1*3 + 1];
            d4 = pucSrcData[iTempSrc2 +1*3 + 1];

            iTemp1 = (d1 << precision);
            iTemp2 = (d3 << precision);
            if((xz + 1) <= (_iSrcWidth - 1))
            {
                iTemp1 += xx * (d2 - d1);
                iTemp2 += xx * (d4 - d3);
            }
            iTemp3 = iTemp2 - iTemp1;

            iTempRound = (((iTemp1 << precision) + y * ((iTemp3))) >> precision) + precision1;

            pucDstdata[3*k + i*3 + 1 ] = (BoonUint8)(iTempRound >> precision);




            d1 = pucSrcData[iTempSrc1 + 2];
            d3 = pucSrcData[iTempSrc2 + 2];
            d2 = pucSrcData[iTempSrc1 +1*3 + 2];
            d4 = pucSrcData[iTempSrc2 +1*3 + 2];

            iTemp1 = (d1 << precision);
            iTemp2 = (d3 << precision);
            if((xz + 1) <= (_iSrcWidth - 1))
            {
                iTemp1 += xx * (d2 - d1);
                iTemp2 += xx * (d4 - d3);
            }
            iTemp3 = iTemp2 - iTemp1;

            iTempRound = (((iTemp1 << precision) + y * ((iTemp3))) >> precision) + precision1;

            pucDstdata[3*k + i*3 + 2 ] = (BoonUint8)(iTempRound >> precision);


        }
    }
    pucDstdata[_iNewHeight * _iNewWidth*3 - 1] = pucSrcData[_iSrcHeight * _iSrcWidth*3 - 1];
    pucDstdata[_iNewHeight * _iNewWidth*3 - 2] = pucSrcData[_iSrcHeight * _iSrcWidth*3 - 2];
    pucDstdata[_iNewHeight * _iNewWidth*3 - 3] = pucSrcData[_iSrcHeight * _iSrcWidth*3 - 3];
    return Boon_ALG_OK;
}

concurrent_queue<void *> video_queue;

//待连接摄像头队列
concurrent_queue<void *> camera_videos;

//A通道视频队列
concurrent_queue<void *> video_queue_a;
//AA通道视频队列
concurrent_queue<void *> video_queue_aA;
//B通道视频队列
concurrent_queue<void *> video_queue_b;
//BA通道视频队列
concurrent_queue<void *> video_queue_bA;

//A通道视频队列
concurrent_queue<void *> video_queue_aa;
//AA通道视频队列
concurrent_queue<void *> video_queue_aaA;
//B通道视频队列
concurrent_queue<void *> video_queue_bb;
//BA通道视频队列
concurrent_queue<void *> video_queue_bbA;

JoveCameraVideo camera_video_a; //A通道视频解码
JoveCameraVideo camera_video_b; //B通道视频解码
JoveCameraVideo camera_video_aA; //AA通道视频解码
JoveCameraVideo camera_video_bA; //BA通道视频解码

JoveCameraVideo camera_video_aa; //A通道视频解码
JoveCameraVideo camera_video_bb; //B通道视频解码
JoveCameraVideo camera_video_aaA; //AA通道视频解码
JoveCameraVideo camera_video_bbA; //BA通道视频解码
static int A=0,B=0;

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




    pFontFile = fopen("./data/ASC24", "rb");
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

    pFontFile = fopen("./data/HZK24", "rb");
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


//事件回调
void event_callback(JCLink_t nLinkID, JCEventType etType, DWORD_PTR pData1,
                    DWORD_PTR pData2, LPVOID pUserData)
{
    printf("event_callback:\t%d\t%d\n", nLinkID, etType);
    if(etType == JCET_ConnectOK)			//连接成功
    {
        cout << "通道链接成功" << endl;
    }
    else if(etType == JCET_UserAccessError)	//密码错误
    {
        cout << "通道密码错误" << endl;
    }
    else if(etType==JCET_ConTimeout)	//连接超时
    {
        cout << "通道链接超时" << endl;
    }
    else if (etType==JCET_ConAbout)	//异常断开
    {
        cout << "通道异常断开" << endl;
    }

//    printf("event_callback:\t%d\t%d\n", nLinkID, etType);
//    if(etType == JCET_ConnectOK)			//连接成功
//    {
//        if (nLinkID==camera_video_a.link_id) {
//            log_output("[jovideo]A通道连接成功");
//        }
//        if (nLinkID==camera_video_b.link_id) {
//            log_output("[jovideo]B通道连接成功");
//        }
//        if (nLinkID==camera_video_aA.link_id) {
//            log_output("[jovideo]AA通道连接成功");
//        }
//        if (nLinkID==camera_video_bA.link_id) {
//            log_output("[jovideo]BA通道连接成功");
//        }
//    }
//    else if(etType == JCET_UserAccessError)	//密码错误
//    {
//        if (nLinkID==camera_video_a.link_id) {
//            log_output("[jovideo]A通道密码错误");
//        }
//        if (nLinkID==camera_video_b.link_id) {
//            log_output("[jovideo]B通道密码错误");
//        }
//        if (nLinkID==camera_video_aA.link_id) {
//            log_output("[jovideo]AA通道密码错误");
//        }
//        if (nLinkID==camera_video_bA.link_id) {
//            log_output("[jovideo]BA通道密码错误");
//        }
//    }
//    else if(etType==JCET_ConTimeout)	//连接超时
//    {
//        if (nLinkID==camera_video_a.link_id) {
//            log_output("[jovideo]A通道连接超时，重新连接");
//            camera_videos.push((void*)&camera_video_a);
//        }
//        if (nLinkID==camera_video_b.link_id) {
//            log_output("[jovideo]B通道连接超时，重新连接");
//            camera_videos.push((void*)&camera_video_b);
//        }
//        if (nLinkID==camera_video_aA.link_id) {
//            log_output("[jovideo]AA通道连接超时，重新连接");
//            camera_videos.push((void*)&camera_video_aA);
//        }
//        if (nLinkID==camera_video_bA.link_id) {
//            log_output("[jovideo]BA通道连接超时，重新连接");
//            camera_videos.push((void*)&camera_video_bA);
//        }
//    }
//    else if (etType==JCET_ConAbout)	//异常断开
//    {
//        if (nLinkID==camera_video_a.link_id) {
//            log_output("[jovideo]A通道异常断开，重新连接");
//            camera_videos.push((void*)&camera_video_a);
//        }
//        if (nLinkID==camera_video_b.link_id) {
//            log_output("[jovideo]B通道异常断开，重新连接");
//            camera_videos.push((void*)&camera_video_b);
//        }
//        if (nLinkID==camera_video_aA.link_id) {
//            log_output("[jovideo]AA通道异常断开，重新连接");
//            camera_videos.push((void*)&camera_video_aA);
//        }
//        if (nLinkID==camera_video_bA.link_id) {
//            log_output("[jovideo]BA通道异常断开，重新连接");
//            camera_videos.push((void*)&camera_video_bA);
//        }
//    }
}
//数据回调
void data_callback(JCLink_t nLinkID, PJCStreamFrame pFrame, LPVOID pUserData)
{
    printf("data_callback:\t%d\t%d\t%s\n", nLinkID, pFrame->nFrameSize, pFrame->pFrameData);
    if (pFrame->sType != JCFT_Audio) {  //忽略掉音频数据
        printf("video\t%d\t%d\n", nLinkID, pFrame->nFrameSize);
        PBMS pbms = (PBMS)malloc(sizeof(BMS));
        pbms->size = pFrame->nFrameSize;
        pbms->memory = (char*)malloc(pbms->size);
        memcpy(pbms->memory, pFrame->pFrameData, pbms->size);

        printf("video:%s\n", pbms->memory);

        video_queue.push((void *)pbms);
    }
    else
    {
        printf("audio\n");
    }

//    //printf("data_callback:\t%d\t%d\t%x\n", nLinkID, pFrame->nFrameSize, pFrame->pFrameData);
//    if (pFrame->sType != JCFT_Audio) {  //忽略掉音频数据
//        //printf("video\t%d\t%d\t%d\n", nLinkID, camera_video_a.link_id, camera_video_b.link_id);
//        PBMS pbms = (PBMS)malloc(sizeof(BMS));
//        pbms->size = pFrame->nFrameSize;
//        pbms->memory = (char*)malloc(pbms->size);
//        memcpy(pbms->memory, pFrame->pFrameData, pbms->size);
//
//        PBMS pbms1 = (PBMS)malloc(sizeof(BMS));
//        pbms1->size = pFrame->nFrameSize;
//        pbms1->memory = (char*)malloc(pbms->size);
//        memcpy(pbms1->memory, pFrame->pFrameData, pbms1->size);
//        if (nLinkID==camera_video_a.link_id) {
//            video_queue_a.push((void*)pbms); //A通道摄像头的回调数据流加入到对应的队列
//            video_queue_aa.push((void*)pbms1); //A通道摄像头的回调数据流加入到对应的队列
//            //printf("video_a\n");
//        }
//        if (nLinkID==camera_video_b.link_id) {
//            video_queue_b.push((void*)pbms); //B通道摄像头的回调数据流加入到对应的队列
//            video_queue_bb.push((void*)pbms1); //B通道摄像头的回调数据流加入到对应的队列
//            //printf("video_b\n");
//        }
//        if (nLinkID==camera_video_aA.link_id) {
//            video_queue_aA.push((void*)pbms); //AA通道摄像头的回调数据流加入到对应的队列
//            video_queue_aaA.push((void*)pbms1); //AA通道摄像头的回调数据流加入到对应的队列
//            //printf("video_aA\n");
//        }
//        if (nLinkID==camera_video_bA.link_id) {
//            video_queue_bA.push((void*)pbms); //BA通道摄像头的回调数据流加入到对应的队列
//            video_queue_bbA.push((void*)pbms1); //BA通道摄像头的回调数据流加入到对应的队列
//            //printf("video_bA\n");
//        }
//    }
//    else
//    {
//        //printf("audio\n");
//    }
//
}
//裸数据回调
void raw_data_callback(JCLink_t nLinkID, PJCRawFrame pFrame, LPVOID pUserData)
{
    printf("raw_data_callback\n");
}
//设备搜索回调
void search_callback(PJCLanDeviceInfo pDevice)
{
    printf("search_callback\n");
}

////线程：连接断线的相机
//void * thread_connect_camera(void* para)
//{
//    while(true)
//    {
//        void * p = NULL;
//        camera_videos.wait_and_pop(p);
//        JoveCameraVideo *p_camera_video = (JoveCameraVideo*)p;
//        p_camera_video->connect();
//        usleep(200000);
//    }
//    return NULL;
//}


void * thread_video(void* para)
{

    void *LibHandle = NULL;

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
    Video_init(960,540);


    lCreate LCreate;
    lInit LInit;
    lProcess LProcess;
    lRelease LRelease;
    lGetversion Lversion;
    void * lib_handle1 = dlopen("../lib/libalg1.so", RTLD_LAZY);
    if (lib_handle1 == NULL)
    {
        printf("load alg1 fail \n");
        return false;
    }
    LCreate = (lCreate) dlsym(lib_handle1, "BoonAlgo_LPR_Create");
    LInit = (lInit) dlsym(lib_handle1, "BoonAlgo_LPR_Init");
    LProcess = (lProcess) dlsym(lib_handle1, "BoonAlgo_LPR_Process");
    LRelease = (lRelease) dlsym(lib_handle1, "BoonAlgo_LPR_Release");
    Lversion = (lGetversion) dlsym(lib_handle1, "BoonAlgo_LPR_Get_Version");

    void *ptr_out = LCreate(0, NULL);
    if (ptr_out == 0)
    {
        printf("alg1 creat fail \n");
        return false;
    }
    int ret = LInit(ptr_out,1920,1080);
    if (ret != 0)
    {
        printf("alg1 init fail \n");
        return false;
    }


    struct timeval tv1;
    struct timeval tv2;
    char plate[22];
    int color_plate;

    //Http Post Msg
    Json::Value hpm;
    hpm["time"] = "";
    hpm["dev"] = "";
    hpm["channel"] = "";
    hpm["direction"] = "";
    hpm["plate"] = "";
    hpm["pcolor"] = "";
    hpm["brand"] = "";
    hpm["type"] = "";


    std::string local_ip = get_local_ip();
    while (true) {
        void * p = NULL;

        video_queue.wait_and_pop(p);

        PBMS pFrame = (PBMS)p;
        //        printf("A decode\n");
        unsigned char *buf = (unsigned char *)malloc(SM_BUF_SIZE);
        camera_video_aa.decoder->h264_2_rgb((unsigned char *)pFrame->memory,pFrame->size,buf,nullptr);
        //  write_video_a((char *)buf);
        Boon_ALG_IMAGE3_S image;
        image.iWidth = 960;
        image.iHeight = 540;
        image.pucD1 = (char  *)malloc(image.iWidth * image.iHeight *3 );
        memcpy(image.pucD1,(char *)buf,960*540*3);
        gettimeofday(&tv1,NULL);
        Video_process(&image);
        memset(plate,0,22);
        color_plate=0;
        int rtn = Video_get_result(plate,&color_plate);

        gettimeofday(&tv2,NULL);
        std::string str_time = get_time_sec();
        std::string str_date = get_time_date();
        std::string str_ms = get_time_ms();
        //printf("A time is %d ms \n",tv2.tv_sec*1000 + tv2.tv_usec/1000 - tv1.tv_sec*1000 - tv1.tv_usec/1000);
        if(rtn == 5)
        {

            char color[16];
            memset(color,0,16);
            if(color_plate == 1)
            {
                strcpy(color,"blue");
            }
            else
            {
                strcpy(color,"yellow");
            }

            printf("result is %s color is %s \n",plate,color);
            char str_msg[1024];
            char path[1024];
            char pic_path[1024];
            char dir_path[1024];
            memset(str_msg,0,1024);
            memset(path,0,1024);
            memset(pic_path,0,1024);
            memset(dir_path,0,1024);



            sprintf(pic_path,"/home/boon/carPicture/%s/A/%s%s.jpg",str_date.c_str(),str_ms.c_str(),plate);
            sprintf(dir_path,"/home/boon/carPicture/%s/A",str_date.c_str());
            create_dir(dir_path);
            write_jpeg_file(pic_path,buf,960,540,90);
            sprintf(path,"http://%s/piclog/%s/A/%s%s.jpg",local_ip.c_str(),str_date.c_str(),str_ms.c_str(),plate);

            //sprintf(str_msg,"{\"cmd\":\"car_come\",\"time\":\"%s\",\"channel_id\":\"%s\",\"in_out\":\"入口\",\"car_info\":[{\"ipc_ip\":\"%s\",\"vehicle\":{\"plate\":\"%s\",\"pcolor\":\"%s\",\"brand\":\"\",\"type\":\"\",\"color\":\"\",\"path\":\"%s\"}}]}",str_time.c_str(),g_machine.channel_a.channel_id.c_str(),g_machine.channel_a.main_camera.device_ip_id.c_str(),plate,color,path);

            //udp_sender1.send(str_msg);
            //sendMsg(true,false,plate,color,path);
            //log_output(str_msg);
        }
        if(A == 1 || rtn == 6)
        {
            int ret, i, j = 0;
            float maxconid = 0;

            Boon_ALG_IMAGE_S image1;
            Boon_ALG_LPROutput_S outPut;
            Boon_ALG_LPROutputMulti_S outPut_M;

            image1.iColorMode = 0;
            image1.iChannels = 3;
            image1.iDepth = 8;
            image1.iImageSize = sizeof(Boon_ALG_IMAGE_S);

            image1.iWidth = 1920;
            image1.iHeight = 1080;
            image1.pucData = (BoonUint8 *) malloc(image1.iWidth * image1.iHeight * 3);


            Public_ImageInterpolation1((BoonUint8 *)image.pucD1,image1.pucData,960,540,1920,1080);

            ret = LProcess(ptr_out, &image1, &outPut, &outPut_M);

            if (ret != 0)
            {
                A = 0;
                return false;
            }
            maxconid = 0;

            for (i = 0; i < outPut_M.iNumOutputs; i++)
            {
                if (outPut_M.astOutputs[i].f32Confid > maxconid)
                {
                    j = i;
                    maxconid = outPut_M.astOutputs[i].f32Confid;
                }
            }
            if (strlen(outPut_M.astOutputs[j].acPlateRec) < 5)
            {
                strcpy(outPut_M.astOutputs[j].acPlateRec,"无车牌");
            }

            color_plate = outPut_M.astOutputs[j].eColor;
            strcpy(plate, (const char *) (outPut_M.astOutputs[j].acPlateRec));
            char color[16];
            memset(color,0,16);
            if(color_plate == 1)
            {
                strcpy(color,"blue");
            }
            else
            {
                strcpy(color,"yellow");
            }
            printf("result is %s color is %s \n",plate,color);
            char str_msg[1024];
            char path[1024];
            char pic_path[1024];
            char dir_path[1024];
            memset(str_msg,0,1024);
            memset(path,0,1024);
            memset(pic_path,0,1024);
            memset(dir_path,0,1024);



            sprintf(pic_path,"/home/boon/carPicture/%s/a/%s%s.jpg",str_date.c_str(),str_ms.c_str(),plate);
            sprintf(dir_path,"/home/boon/carPicture/%s/a",str_date.c_str());
            create_dir(dir_path);
            write_jpeg_file(pic_path,image1.pucData,1920,1080,90);
            free(image1.pucData);
            sprintf(path,"http://%s/piclog/%s/a/%s%s.jpg",local_ip.c_str(),str_date.c_str(),str_ms.c_str(),plate);
            if(rtn == 6 && strcmp(plate,"无车牌") == 0)
            {

            }
            else
            {
                //sendMsg(true,false,plate,color,path);
            }
            A = 0;
        }



        free( image.pucD1);

        if(pFrame->memory)
            free(pFrame->memory);
        if(pFrame)
            free(pFrame);
        if(buf)
            free(buf);
    }
    return NULL;
}


////线程：A通道视频解码
//void * thread_video_a(void* para)
//{
//    while (true) {
//        void * p = NULL;
//        video_queue_a.wait_and_pop(p);
//        PBMS pFrame = (PBMS)p;
//        //        printf("A decode\n");
//        unsigned char *buf = (unsigned char *)malloc(SM_BUF_SIZE);
//        camera_video_a.decoder->h264_2_rgb((unsigned char *)pFrame->memory,pFrame->size,buf,nullptr);
//        write_video_a((char *)buf);
//
//        if(pFrame->memory)
//            free(pFrame->memory);
//        if(pFrame)
//            free(pFrame);
//        if(buf)
//            free(buf);
//    }
//    return NULL;
//}
////线程：AA通道视频解码
//void * thread_video_aA(void* para)
//{
//    while (true) {
//        void * p = NULL;
//        video_queue_aA.wait_and_pop(p);
//        PBMS pFrame = (PBMS)p;
//        //        printf("AA decode\n");
//        unsigned char *buf = (unsigned char *)malloc(SM_BUF_SIZE);
//        camera_video_aA.decoder->h264_2_rgb((unsigned char *)pFrame->memory,pFrame->size,buf,nullptr);
//        write_video_aA((char *)buf);
//
//        if(pFrame->memory)
//            free(pFrame->memory);
//        if(pFrame)
//            free(pFrame);
//        if(buf)
//            free(buf);
//    }
//    return NULL;
//}

//线程：A通道视频解码
//void * thread_video_aa(void* para)
//{
//
//    void *LibHandle = NULL;
//
//    video_create Video_create;
//    video_init Video_init;
//    video_process Video_process;
//    video_get_result Video_get_result;
//
//    LibHandle = dlopen("../lib/libalg_video.so", RTLD_LAZY);
//
//    if(NULL == LibHandle)
//    {
//        printf("LoadLibrary fail %s \n",dlerror());
//        return 0;
//    }
//
//    Video_create = (video_create)dlsym(LibHandle,"BoonAlgo_TRIP_Creat");
//    if(NULL ==   Video_create)
//    {
//        printf("LCreate fail \n");
//        return 0;
//    }
//    Video_init = (video_init)dlsym(LibHandle,"BoonAlgo_TRIP_Init");
//    Video_process = (video_process)dlsym(LibHandle,"BoonAlgo_TRIP_Process");
//    Video_get_result = (video_get_result)dlsym(LibHandle,"BoonAlgo_TRIP_GetResults");
//
//    Video_create(0,NULL);
//    Video_init(960,540);
//
//
//    lCreate LCreate;
//    lInit LInit;
//    lProcess LProcess;
//    lRelease LRelease;
//    lGetversion Lversion;
//    void * lib_handle1 = dlopen("../lib/libalg1.so", RTLD_LAZY);
//    if (lib_handle1 == NULL)
//    {
//        printf("load alg1 fail \n");
//        return false;
//    }
//    LCreate = (lCreate) dlsym(lib_handle1, "BoonAlgo_LPR_Create");
//    LInit = (lInit) dlsym(lib_handle1, "BoonAlgo_LPR_Init");
//    LProcess = (lProcess) dlsym(lib_handle1, "BoonAlgo_LPR_Process");
//    LRelease = (lRelease) dlsym(lib_handle1, "BoonAlgo_LPR_Release");
//    Lversion = (lGetversion) dlsym(lib_handle1, "BoonAlgo_LPR_Get_Version");
//
//    void *ptr_out = LCreate(0, NULL);
//    if (ptr_out == 0)
//    {
//        printf("alg1 creat fail \n");
//        return false;
//    }
//    int ret = LInit(ptr_out,1920,1080);
//    if (ret != 0)
//    {
//        printf("alg1 init fail \n");
//        return false;
//    }
//
//
//    struct timeval tv1;
//    struct timeval tv2;
//    char plate[22];
//    int color_plate;
//
//    std::string local_ip = get_local_ip();
//    while (true) {
//        void * p = NULL;
//
//        video_queue_aa.wait_and_pop(p);
//
//        PBMS pFrame = (PBMS)p;
//        //        printf("A decode\n");
//        unsigned char *buf = (unsigned char *)malloc(SM_BUF_SIZE);
//        camera_video_aa.decoder->h264_2_rgb((unsigned char *)pFrame->memory,pFrame->size,buf,nullptr);
//        //  write_video_a((char *)buf);
//        Boon_ALG_IMAGE3_S image;
//        image.iWidth = 960;
//        image.iHeight = 540;
//        image.pucD1 = (char  *)malloc(image.iWidth * image.iHeight *3 );
//        memcpy(image.pucD1,(char *)buf,960*540*3);
//        gettimeofday(&tv1,NULL);
//        Video_process(&image);
//        memset(plate,0,22);
//        color_plate=0;
//        int rtn = Video_get_result(plate,&color_plate);
//
//        gettimeofday(&tv2,NULL);
//        std::string str_time = get_time_sec();
//        std::string str_date = get_time_date();
//        std::string str_ms = get_time_ms();
//        //printf("A time is %d ms \n",tv2.tv_sec*1000 + tv2.tv_usec/1000 - tv1.tv_sec*1000 - tv1.tv_usec/1000);
//        if(rtn == 5)
//        {
//
//            char color[16];
//            memset(color,0,16);
//            if(color_plate == 1)
//            {
//                strcpy(color,"blue");
//            }
//            else
//            {
//                strcpy(color,"yellow");
//            }
//
//            printf("result is %s color is %s \n",plate,color);
//            char str_msg[1024];
//            char path[1024];
//            char pic_path[1024];
//            char dir_path[1024];
//            memset(str_msg,0,1024);
//            memset(path,0,1024);
//            memset(pic_path,0,1024);
//            memset(dir_path,0,1024);
//
//
//
//            sprintf(pic_path,"/home/boon/carPicture/%s/A/%s%s.jpg",str_date.c_str(),str_ms.c_str(),plate);
//            sprintf(dir_path,"/home/boon/carPicture/%s/A",str_date.c_str());
//            create_dir(dir_path);
//            write_jpeg_file(pic_path,buf,960,540,90);
//            sprintf(path,"http://%s/piclog/%s/A/%s%s.jpg",local_ip.c_str(),str_date.c_str(),str_ms.c_str(),plate);
//
//            //sprintf(str_msg,"{\"cmd\":\"car_come\",\"time\":\"%s\",\"channel_id\":\"%s\",\"in_out\":\"入口\",\"car_info\":[{\"ipc_ip\":\"%s\",\"vehicle\":{\"plate\":\"%s\",\"pcolor\":\"%s\",\"brand\":\"\",\"type\":\"\",\"color\":\"\",\"path\":\"%s\"}}]}",str_time.c_str(),g_machine.channel_a.channel_id.c_str(),g_machine.channel_a.main_camera.device_ip_id.c_str(),plate,color,path);
//
//            //udp_sender1.send(str_msg);
//            sendMsg(true,false,plate,color,path);
//            //log_output(str_msg);
//        }
//        if(A == 1 || rtn == 6)
//        {
//            int ret, i, j = 0;
//            float maxconid = 0;
//
//            Boon_ALG_IMAGE_S image1;
//            Boon_ALG_LPROutput_S outPut;
//            Boon_ALG_LPROutputMulti_S outPut_M;
//
//            image1.iColorMode = 0;
//            image1.iChannels = 3;
//            image1.iDepth = 8;
//            image1.iImageSize = sizeof(Boon_ALG_IMAGE_S);
//
//            image1.iWidth = 1920;
//            image1.iHeight = 1080;
//            image1.pucData = (BoonUint8 *) malloc(image1.iWidth * image1.iHeight * 3);
//
//
//            Public_ImageInterpolation1((BoonUint8 *)image.pucD1,image1.pucData,960,540,1920,1080);
//
//            ret = LProcess(ptr_out, &image1, &outPut, &outPut_M);
//
//            if (ret != 0)
//            {
//                A = 0;
//                return false;
//            }
//            maxconid = 0;
//
//            for (i = 0; i < outPut_M.iNumOutputs; i++)
//            {
//                if (outPut_M.astOutputs[i].f32Confid > maxconid)
//                {
//                    j = i;
//                    maxconid = outPut_M.astOutputs[i].f32Confid;
//                }
//            }
//            if (strlen(outPut_M.astOutputs[j].acPlateRec) < 5)
//            {
//                strcpy(outPut_M.astOutputs[j].acPlateRec,"无车牌");
//            }
//
//            color_plate = outPut_M.astOutputs[j].eColor;
//            strcpy(plate, (const char *) (outPut_M.astOutputs[j].acPlateRec));
//            char color[16];
//            memset(color,0,16);
//            if(color_plate == 1)
//            {
//                strcpy(color,"blue");
//            }
//            else
//            {
//                strcpy(color,"yellow");
//            }
//            printf("result is %s color is %s \n",plate,color);
//            char str_msg[1024];
//            char path[1024];
//            char pic_path[1024];
//            char dir_path[1024];
//            memset(str_msg,0,1024);
//            memset(path,0,1024);
//            memset(pic_path,0,1024);
//            memset(dir_path,0,1024);
//
//
//
//            sprintf(pic_path,"/home/boon/carPicture/%s/a/%s%s.jpg",str_date.c_str(),str_ms.c_str(),plate);
//            sprintf(dir_path,"/home/boon/carPicture/%s/a",str_date.c_str());
//            create_dir(dir_path);
//            write_jpeg_file(pic_path,image1.pucData,1920,1080,90);
//            free(image1.pucData);
//            sprintf(path,"http://%s/piclog/%s/a/%s%s.jpg",local_ip.c_str(),str_date.c_str(),str_ms.c_str(),plate);
//            if(rtn == 6 && strcmp(plate,"无车牌") == 0)
//            {
//
//            }
//            else
//            {
//                sendMsg(true,false,plate,color,path);
//            }
//            A = 0;
//        }
//
//
//
//        free( image.pucD1);
//
//        if(pFrame->memory)
//            free(pFrame->memory);
//        if(pFrame)
//            free(pFrame);
//        if(buf)
//            free(buf);
//    }
//    return NULL;
//}
//线程：AA通道视频解码
//void * thread_video_aaA(void* para)
//{
//
//    void *LibHandle = NULL;
//
//    video_create Video_create;
//    video_init Video_init;
//    video_process Video_process;
//    video_get_result Video_get_result;
//
//    LibHandle = dlopen("../lib/libalg_video3.so", RTLD_LAZY);
//
//    if(NULL == LibHandle)
//    {
//        printf("LoadLibrary fail %s \n",dlerror());
//        return 0;
//    }
//
//    Video_create = (video_create)dlsym(LibHandle,"BoonAlgo_TRIP_Creat");
//    if(NULL ==   Video_create)
//    {
//        printf("LCreate fail \n");
//        return 0;
//    }
//    Video_init = (video_init)dlsym(LibHandle,"BoonAlgo_TRIP_Init");
//    Video_process = (video_process)dlsym(LibHandle,"BoonAlgo_TRIP_Process");
//    Video_get_result = (video_get_result)dlsym(LibHandle,"BoonAlgo_TRIP_GetResults");
//
//    Video_create(0,NULL);
//    Video_init(960,540);
//
//
//    lCreate LCreate;
//    lInit LInit;
//    lProcess LProcess;
//    lRelease LRelease;
//    lGetversion Lversion;
//    void * lib_handle1 = dlopen("../lib/libalg2.so", RTLD_LAZY);
//    if (lib_handle1 == NULL)
//    {
//        printf("load alg2 fail \n");
//        return false;
//    }
//    LCreate = (lCreate) dlsym(lib_handle1, "BoonAlgo_LPR_Create");
//    LInit = (lInit) dlsym(lib_handle1, "BoonAlgo_LPR_Init");
//    LProcess = (lProcess) dlsym(lib_handle1, "BoonAlgo_LPR_Process");
//    LRelease = (lRelease) dlsym(lib_handle1, "BoonAlgo_LPR_Release");
//    Lversion = (lGetversion) dlsym(lib_handle1, "BoonAlgo_LPR_Get_Version");
//
//    void *ptr_out = LCreate(0, NULL);
//    if (ptr_out == 0)
//    {
//        printf("alg2 create fail \n");
//        return false;
//    }
//    int ret = LInit(ptr_out,1920,1080);
//    if (ret != 0)
//    {
//        printf("alg2 init fail \n");
//        return false;
//    }
//    struct timeval tv1;
//    struct timeval tv2;
//    char plate[22];
//    int color_plate;
//    std::string local_ip = get_local_ip();
//
//    while (true) {
//        void * p = NULL;
//
//        video_queue_aaA.wait_and_pop(p);
//
//        PBMS pFrame = (PBMS)p;
//        //        printf("AA decode\n");
//        unsigned char *buf = (unsigned char *)malloc(SM_BUF_SIZE);
//        camera_video_aaA.decoder->h264_2_rgb((unsigned char *)pFrame->memory,pFrame->size,buf,nullptr);
//        //  write_video_a((char *)buf);
//        Boon_ALG_IMAGE3_S image;
//        image.iWidth = 960;
//        image.iHeight = 540;
//        image.pucD1 = (char  *)malloc(image.iWidth * image.iHeight *3 );
//        memcpy(image.pucD1,(char *)buf,960*540*3);
//        gettimeofday(&tv1,NULL);
//        Video_process(&image);
//        memset(plate,0,22);
//        color_plate=0;
//        int rtn = Video_get_result(plate,&color_plate);
//        std::string str_time = get_time_sec();
//        std::string str_date = get_time_date();
//        std::string str_ms = get_time_ms();
//        gettimeofday(&tv2,NULL);
//        //printf("A time is %d ms \n",tv2.tv_sec*1000 + tv2.tv_usec/1000 - tv1.tv_sec*1000 - tv1.tv_usec/1000);
//        if(rtn == 5)
//        {
//
//            char color[16];
//            memset(color,0,16);
//            if(color_plate == 1)
//            {
//                strcpy(color,"blue");
//            }
//            else
//            {
//                strcpy(color,"yellow");
//            }
//
//            printf("result is %s color is %s \n",plate,color);
//            char str_msg[1024];
//            char path[1024];
//            char pic_path[1024];
//            char dir_path[1024];
//            memset(str_msg,0,1024);
//            memset(path,0,1024);
//            memset(pic_path,0,1024);
//            memset(dir_path,0,1024);
//
//
//
//            sprintf(pic_path,"/home/boon/carPicture/%s/AA/%s%s.jpg",str_date.c_str(),str_ms.c_str(),plate);
//            sprintf(dir_path,"/home/boon/carPicture/%s/AA",str_date.c_str());
//            create_dir(dir_path);
//            write_jpeg_file(pic_path,buf,960,540,90);
//            sprintf(path,"http://%s/piclog/%s/AA/%s%s.jpg",local_ip.c_str(),str_date.c_str(),str_ms.c_str(),plate);
//            /*--------------*/
//            //sprintf(str_msg,"{\"cmd\":\"car_come\",\"time\":\"%s\",\"channel_id\":\"%s\",\"in_out\":\"入口\",\"car_info\":[{\"ipc_ip\":\"%s\",\"vehicle\":{\"plate\":\"%s\",\"pcolor\":\"%s\",\"brand\":\"\",\"type\":\"\",\"color\":\"\",\"path\":\"%s\"}}]}",str_time.c_str(),g_machine.channel_a.channel_id.c_str(),g_machine.channel_a.main_camera.device_ip_id.c_str(),plate,color,path);
//            /*--------------*/
//            //udp_sender1.send(str_msg);
//            sendMsg(true,true,plate,color,path);
//            //log_output(str_msg);
//        }
//
//        if(A == 1 || rtn == 6)
//        {
//            int ret, i, j = 0;
//            float maxconid = 0;
//
//            Boon_ALG_IMAGE_S image1;
//            Boon_ALG_LPROutput_S outPut;
//            Boon_ALG_LPROutputMulti_S outPut_M;
//
//            image1.iColorMode = 0;
//            image1.iChannels = 3;
//            image1.iDepth = 8;
//            image1.iImageSize = sizeof(Boon_ALG_IMAGE_S);
//
//            image1.iWidth = 1920;
//            image1.iHeight = 1080;
//            image1.pucData = (BoonUint8 *) malloc(image1.iWidth * image1.iHeight * 3);
//
//
//            Public_ImageInterpolation1((BoonUint8 *)image.pucD1,image1.pucData,960,540,1920,1080);
//
//            ret = LProcess(ptr_out, &image1, &outPut, &outPut_M);
//
//            if (ret != 0)
//            {
//                A = 0;
//                return false;
//            }
//            maxconid = 0;
//
//            for (i = 0; i < outPut_M.iNumOutputs; i++)
//            {
//                if (outPut_M.astOutputs[i].f32Confid > maxconid)
//                {
//                    j = i;
//                    maxconid = outPut_M.astOutputs[i].f32Confid;
//                }
//            }
//            if (strlen(outPut_M.astOutputs[j].acPlateRec) < 5)
//            {
//                strcpy(outPut_M.astOutputs[j].acPlateRec,"无车牌");
//            }
//
//            color_plate = outPut_M.astOutputs[j].eColor;
//            strcpy(plate, (const char *) (outPut_M.astOutputs[j].acPlateRec));
//            char color[16];
//            memset(color,0,16);
//            if(color_plate == 1)
//            {
//                strcpy(color,"blue");
//            }
//            else
//            {
//                strcpy(color,"yellow");
//            }
//            printf("result is %s color is %s \n",plate,color);
//            char str_msg[1024];
//            char path[1024];
//            char pic_path[1024];
//            char dir_path[1024];
//            memset(str_msg,0,1024);
//            memset(path,0,1024);
//            memset(pic_path,0,1024);
//            memset(dir_path,0,1024);
//
//
//
//            sprintf(pic_path,"/home/boon/carPicture/%s/aa/%s%s.jpg",str_date.c_str(),str_ms.c_str(),plate);
//            sprintf(dir_path,"/home/boon/carPicture/%s/aa",str_date.c_str());
//            create_dir(dir_path);
//            write_jpeg_file(pic_path,image1.pucData,1920,1080,90);
//            free(image1.pucData);
//            sprintf(path,"http://%s/piclog/%s/aa/%s%s.jpg",local_ip.c_str(),str_date.c_str(),str_ms.c_str(),plate);
//            if(rtn == 6 && strcmp(plate,"无车牌") == 0)
//            {
//            }
//            else
//            {
//                sendMsg(true,false,plate,color,path);
//            }
//
//            A = 0;
//        }
//
//        free( image.pucD1);
//
//        if(pFrame->memory)
//            free(pFrame->memory);
//        if(pFrame)
//            free(pFrame);
//        if(buf)
//            free(buf);
//    }
//    return NULL;
//}
//
////线程：B通道视频解码
//void * thread_video_b(void* para)
//{
//    while (true) {
//        void * p = NULL;
//        video_queue_b.wait_and_pop(p);
//        PBMS pFrame = (PBMS)p;
//        //        printf("B decode\n");
//        unsigned char *buf = (unsigned char *)malloc(SM_BUF_SIZE);
//        camera_video_b.decoder->h264_2_rgb((unsigned char *)pFrame->memory,pFrame->size,buf,nullptr);
//        write_video_b((char *)buf);
//        if(pFrame->memory)
//            free(pFrame->memory);
//        if(pFrame)
//            free(pFrame);
//        if(buf)
//            free(buf);
//    }
//    return NULL;
//}
////线程：BA通道视频解码
//void * thread_video_bA(void* para)
//{
//    while (true) {
//        void * p = NULL;
//        video_queue_bA.wait_and_pop(p);
//        PBMS pFrame = (PBMS)p;
//        //        printf("BA decode\n");
//        unsigned char *buf = (unsigned char *)malloc(SM_BUF_SIZE);
//        camera_video_bA.decoder->h264_2_rgb((unsigned char *)pFrame->memory,pFrame->size,buf,nullptr);
//        write_video_bA((char *)buf);
//        if(pFrame->memory)
//            free(pFrame->memory);
//        if(pFrame)
//            free(pFrame);
//        if(buf)
//            free(buf);
//    }
//    return NULL;
//}
////线程：B通道视频解码
//void * thread_video_bb(void* para)
//{
//    void *LibHandle = NULL;
//
//    video_create Video_create;
//    video_init Video_init;
//    video_process Video_process;
//    video_get_result Video_get_result;
//
//    LibHandle = dlopen("../lib/libalg_video1.so", RTLD_LAZY);
//
//    if(NULL == LibHandle)
//    {
//        printf("LoadLibrary fail %s \n",dlerror());
//        return 0;
//    }
//
//    Video_create = (video_create)dlsym(LibHandle,"BoonAlgo_TRIP_Creat");
//    if(NULL ==   Video_create)
//    {
//        printf("LCreate fail \n");
//        return 0;
//    }
//    Video_init = (video_init)dlsym(LibHandle,"BoonAlgo_TRIP_Init");
//    Video_process = (video_process)dlsym(LibHandle,"BoonAlgo_TRIP_Process");
//    Video_get_result = (video_get_result)dlsym(LibHandle,"BoonAlgo_TRIP_GetResults");
//
//    Video_create(0,NULL);
//    Video_init(960,540);
//
//
//    lCreate LCreate;
//    lInit LInit;
//    lProcess LProcess;
//    lRelease LRelease;
//    lGetversion Lversion;
//    void * lib_handle1 = dlopen("../lib/libalg3.so", RTLD_LAZY);
//    if (lib_handle1 == NULL)
//        return false;
//    LCreate = (lCreate) dlsym(lib_handle1, "BoonAlgo_LPR_Create");
//    LInit = (lInit) dlsym(lib_handle1, "BoonAlgo_LPR_Init");
//    LProcess = (lProcess) dlsym(lib_handle1, "BoonAlgo_LPR_Process");
//    LRelease = (lRelease) dlsym(lib_handle1, "BoonAlgo_LPR_Release");
//    Lversion = (lGetversion) dlsym(lib_handle1, "BoonAlgo_LPR_Get_Version");
//
//    void *ptr_out = LCreate(0, NULL);
//    if (ptr_out == 0)
//        return false;
//    int ret = LInit(ptr_out,1920,1080);
//    if (ret != 0)
//        return false;
//
//    struct timeval tv1;
//    struct timeval tv2;
//    char plate[22];
//    int color_plate;
//        std::string local_ip = get_local_ip();
//    while (true) {
//        void * p = NULL;
//        video_queue_bb.wait_and_pop(p);
//        PBMS pFrame = (PBMS)p;
//        //        printf("B decode\n");
//        unsigned char *buf = (unsigned char *)malloc(SM_BUF_SIZE);
//        camera_video_bb.decoder->h264_2_rgb((unsigned char *)pFrame->memory,pFrame->size,buf,nullptr);
//        //   write_video_b((char *)buf);
//        Boon_ALG_IMAGE3_S image;
//        image.iWidth = 960;
//        image.iHeight = 540;
//        image.pucD1 = (char  *)malloc(image.iWidth * image.iHeight *3 );
//        memcpy(image.pucD1,(char *)buf,960*540*3);
//        gettimeofday(&tv1,NULL);
//        Video_process(&image);
//
//        memset(plate,0,22);
//        color_plate=0;
//        int rtn = Video_get_result(plate,&color_plate);
//        gettimeofday(&tv2,NULL);
//        std::string str_time = get_time_sec();
//        std::string str_date = get_time_date();
//        std::string str_ms = get_time_ms();
//
//        //printf(" B time is %d ms \n",tv2.tv_sec*1000 + tv2.tv_usec/1000 - tv1.tv_sec*1000 - tv1.tv_usec/1000);
//        if(rtn == 5)
//        {
//
//            char color[16];
//            memset(color,0,16);
//            if(color_plate == 1)
//            {
//                strcpy(color,"blue");
//            }
//            else
//            {
//                strcpy(color,"yellow");
//            }
//            printf("result is %s color is %s \n",plate,color);
//            char str_msg[1024];
//            char path[1024];
//            char pic_path[1024];
//            char dir_path[1024];
//            memset(str_msg,0,1024);
//            memset(path,0,1024);
//            memset(pic_path,0,1024);
//            memset(dir_path,0,1024);
//
//
//            sprintf(pic_path,"/home/boon/carPicture/%s/B/%s%s.jpg",str_date.c_str(),str_ms.c_str(),plate);
//            sprintf(dir_path,"/home/boon/carPicture/%s/B",str_date.c_str());
//            create_dir(dir_path);
//            write_jpeg_file(pic_path,buf,960,540,90);
//            sprintf(path,"http://%s/piclog/%s/B/%s%s.jpg",local_ip.c_str(),str_date.c_str(),str_ms.c_str(),plate);
//
//            //sprintf(str_msg,"{\"cmd\":\"car_come\",\"time\":\"%s\",\"channel_id\":\"%s\",\"in_out\":\"出口\",\"car_info\":[{\"ipc_ip\":\"%s\",\"vehicle\":{\"plate\":\"%s\",\"pcolor\":\"%s\",\"brand\":\"\",\"type\":\"\",\"color\":\"\",\"path\":\"%s\"}}]}",str_time.c_str(),g_machine.channel_b.channel_id.c_str(),g_machine.channel_b.main_camera.device_ip_id.c_str(),plate,color,path);
//            //udp_sender1.send(str_msg);
//            sendMsg(false,false,plate,color,path);
//            //log_output(str_msg);
//        }
//
//
//        if(B == 1 || rtn == 6)
//        {
//            int ret, i, j = 0;
//            float maxconid = 0;
//
//            Boon_ALG_IMAGE_S image1;
//            Boon_ALG_LPROutput_S outPut;
//            Boon_ALG_LPROutputMulti_S outPut_M;
//
//            image1.iColorMode = 0;
//            image1.iChannels = 3;
//            image1.iDepth = 8;
//            image1.iImageSize = sizeof(Boon_ALG_IMAGE_S);
//
//            image1.iWidth = 1920;
//            image1.iHeight = 1080;
//            image1.pucData = (BoonUint8 *) malloc(image1.iWidth * image1.iHeight * 3);
//
//
//            Public_ImageInterpolation1((BoonUint8 *)image.pucD1,image1.pucData,960,540,1920,1080);
//
//            ret = LProcess(ptr_out, &image1, &outPut, &outPut_M);
//
//            if (ret != 0)
//            {
//                B = 0;
//                return false;
//            }
//            maxconid = 0;
//
//            for (i = 0; i < outPut_M.iNumOutputs; i++)
//            {
//                if (outPut_M.astOutputs[i].f32Confid > maxconid)
//                {
//                    j = i;
//                    maxconid = outPut_M.astOutputs[i].f32Confid;
//                }
//            }
//            if (strlen(outPut_M.astOutputs[j].acPlateRec) < 5)
//            {
//                strcpy(outPut_M.astOutputs[j].acPlateRec,"无车牌");
//            }
//
//            color_plate = outPut_M.astOutputs[j].eColor;
//            strcpy(plate, (const char *) (outPut_M.astOutputs[j].acPlateRec));
//            char color[16];
//            memset(color,0,16);
//            if(color_plate == 1)
//            {
//                strcpy(color,"blue");
//            }
//            else
//            {
//                strcpy(color,"yellow");
//            }
//            printf("result is %s color is %s \n",plate,color);
//            char str_msg[1024];
//            char path[1024];
//            char pic_path[1024];
//            char dir_path[1024];
//            memset(str_msg,0,1024);
//            memset(path,0,1024);
//            memset(pic_path,0,1024);
//            memset(dir_path,0,1024);
//
//
//
//            sprintf(pic_path,"/home/boon/carPicture/%s/b/%s%s.jpg",str_date.c_str(),str_ms.c_str(),plate);
//            sprintf(dir_path,"/home/boon/carPicture/%s/b",str_date.c_str());
//            create_dir(dir_path);
//            write_jpeg_file(pic_path,image1.pucData,1920,1080,90);
//            free(image1.pucData);
//            sprintf(path,"http://%s/piclog/%s/b/%s%s.jpg",local_ip.c_str(),str_date.c_str(),str_ms.c_str(),plate);
//            if(rtn == 6 && strcmp(plate,"无车牌") == 0)
//            {
//
//            }
//            else
//            {
//                sendMsg(false,false,plate,color,path);
//            }
//            B = 0;
//        }
//
//        free( image.pucD1);
//        if(pFrame->memory)
//            free(pFrame->memory);
//        if(pFrame)
//            free(pFrame);
//        if(buf)
//            free(buf);
//    }
//    return NULL;
//}
////线程：BA通道视频解码
//void * thread_video_bbA(void* para)
//{
//    void *LibHandle = NULL;
//
//    video_create Video_create;
//    video_init Video_init;
//    video_process Video_process;
//    video_get_result Video_get_result;
//
//    LibHandle = dlopen("../lib/libalg_video2.so", RTLD_LAZY);
//
//    if(NULL == LibHandle)
//    {
//        printf("LoadLibrary fail %s \n",dlerror());
//        return 0;
//    }
//
//    Video_create = (video_create)dlsym(LibHandle,"BoonAlgo_TRIP_Creat");
//    if(NULL ==   Video_create)
//    {
//        printf("LCreate fail \n");
//        return 0;
//    }
//    Video_init = (video_init)dlsym(LibHandle,"BoonAlgo_TRIP_Init");
//    Video_process = (video_process)dlsym(LibHandle,"BoonAlgo_TRIP_Process");
//    Video_get_result = (video_get_result)dlsym(LibHandle,"BoonAlgo_TRIP_GetResults");
//
//    Video_create(0,NULL);
//    Video_init(960,540);
//
//
//
//    lCreate LCreate;
//    lInit LInit;
//    lProcess LProcess;
//    lRelease LRelease;
//    lGetversion Lversion;
//    void * lib_handle1 = dlopen("../lib/libalg4.so", RTLD_LAZY);
//    if (lib_handle1 == NULL)
//        return false;
//    LCreate = (lCreate) dlsym(lib_handle1, "BoonAlgo_LPR_Create");
//    LInit = (lInit) dlsym(lib_handle1, "BoonAlgo_LPR_Init");
//    LProcess = (lProcess) dlsym(lib_handle1, "BoonAlgo_LPR_Process");
//    LRelease = (lRelease) dlsym(lib_handle1, "BoonAlgo_LPR_Release");
//    Lversion = (lGetversion) dlsym(lib_handle1, "BoonAlgo_LPR_Get_Version");
//
//    void *ptr_out = LCreate(0, NULL);
//    if (ptr_out == 0)
//        return false;
//    int ret = LInit(ptr_out,1920,1080);
//    if (ret != 0)
//        return false;
//
//
//    struct timeval tv1;
//    struct timeval tv2;
//    char plate[22];
//    int color_plate;
//        std::string local_ip = get_local_ip();
//    while (true) {
//        void * p = NULL;
//        video_queue_bbA.wait_and_pop(p);
//        PBMS pFrame = (PBMS)p;
//        //        printf("BA decode\n");
//        unsigned char *buf = (unsigned char *)malloc(SM_BUF_SIZE);
//        camera_video_bbA.decoder->h264_2_rgb((unsigned char *)pFrame->memory,pFrame->size,buf,nullptr);
//        //   write_video_b((char *)buf);
//        Boon_ALG_IMAGE3_S image;
//        image.iWidth = 960;
//        image.iHeight = 540;
//        image.pucD1 = (char  *)malloc(image.iWidth * image.iHeight *3 );
//        memcpy(image.pucD1,(char *)buf,960*540*3);
//        gettimeofday(&tv1,NULL);
//        Video_process(&image);
//
//        memset(plate,0,22);
//        color_plate=0;
//        int rtn = Video_get_result(plate,&color_plate);
//        gettimeofday(&tv2,NULL);
//        std::string str_time = get_time_sec();
//        std::string str_date = get_time_date();
//        std::string str_ms = get_time_ms();
//        //printf(" B time is %d ms \n",tv2.tv_sec*1000 + tv2.tv_usec/1000 - tv1.tv_sec*1000 - tv1.tv_usec/1000);
//        if(rtn == 5)
//        {
//
//            char color[16];
//            memset(color,0,16);
//            if(color_plate == 1)
//            {
//                strcpy(color,"blue");
//            }
//            else
//            {
//                strcpy(color,"yellow");
//            }
//            printf("result is %s color is %s \n",plate,color);
//            char str_msg[1024];
//            char path[1024];
//            char pic_path[1024];
//            char dir_path[1024];
//            memset(str_msg,0,1024);
//            memset(path,0,1024);
//            memset(pic_path,0,1024);
//            memset(dir_path,0,1024);
//
//
//
//            sprintf(pic_path,"/home/boon/carPicture/%s/BB/%s%s.jpg",str_date.c_str(),str_ms.c_str(),plate);
//            sprintf(dir_path,"/home/boon/carPicture/%s/BB",str_date.c_str());
//            create_dir(dir_path);
//            write_jpeg_file(pic_path,buf,960,540,90);
//            sprintf(path,"http://%s/piclog/%s/BB/%s%s.jpg",local_ip.c_str(),str_date.c_str(),str_ms.c_str(),plate);
//            /*-----------*/
//            //sprintf(str_msg,"{\"cmd\":\"car_come\",\"time\":\"%s\",\"channel_id\":\"%s\",\"in_out\":\"出口\",\"car_info\":[{\"ipc_ip\":\"%s\",\"vehicle\":{\"plate\":\"%s\",\"pcolor\":\"%s\",\"brand\":\"\",\"type\":\"\",\"color\":\"\",\"path\":\"%s\"}}]}",str_time.c_str(),g_machine.channel_b.channel_id.c_str(),g_machine.channel_b.main_camera.device_ip_id.c_str(),plate,color,path);
//            sendMsg(false,true,plate,color,path);
//            /*-----------*/
//            //udp_sender1.send(str_msg);
//            //log_output(str_msg);
//        }
//
//        if(B == 1 || rtn == 6)
//        {
//            int ret, i, j = 0;
//            float maxconid = 0;
//
//            Boon_ALG_IMAGE_S image1;
//            Boon_ALG_LPROutput_S outPut;
//            Boon_ALG_LPROutputMulti_S outPut_M;
//
//            image1.iColorMode = 0;
//            image1.iChannels = 3;
//            image1.iDepth = 8;
//            image1.iImageSize = sizeof(Boon_ALG_IMAGE_S);
//
//            image1.iWidth = 1920;
//            image1.iHeight = 1080;
//            image1.pucData = (BoonUint8 *) malloc(image1.iWidth * image1.iHeight * 3);
//
//
//            Public_ImageInterpolation1((BoonUint8 *)image.pucD1,image1.pucData,960,540,1920,1080);
//
//            ret = LProcess(ptr_out, &image1, &outPut, &outPut_M);
//
//            if (ret != 0)
//            {
//                B = 0;
//                return false;
//            }
//            maxconid = 0;
//
//            for (i = 0; i < outPut_M.iNumOutputs; i++)
//            {
//                if (outPut_M.astOutputs[i].f32Confid > maxconid)
//                {
//                    j = i;
//                    maxconid = outPut_M.astOutputs[i].f32Confid;
//                }
//            }
//            if (strlen(outPut_M.astOutputs[j].acPlateRec) < 5)
//            {
//                strcpy(outPut_M.astOutputs[j].acPlateRec,"无车牌");
//            }
//
//            color_plate = outPut_M.astOutputs[j].eColor;
//            strcpy(plate, (const char *) (outPut_M.astOutputs[j].acPlateRec));
//            char color[16];
//            memset(color,0,16);
//            if(color_plate == 1)
//            {
//                strcpy(color,"blue");
//            }
//            else
//            {
//                strcpy(color,"yellow");
//            }
//            printf("result is %s color is %s \n",plate,color);
//            char str_msg[1024];
//            char path[1024];
//            char pic_path[1024];
//            char dir_path[1024];
//            memset(str_msg,0,1024);
//            memset(path,0,1024);
//            memset(pic_path,0,1024);
//            memset(dir_path,0,1024);
//
//
//
//            sprintf(pic_path,"/home/boon/carPicture/%s/bb/%s%s.jpg",str_date.c_str(),str_ms.c_str(),plate);
//            sprintf(dir_path,"/home/boon/carPicture/%s/bb",str_date.c_str());
//            create_dir(dir_path);
//            write_jpeg_file(pic_path,image1.pucData,1920,1080,90);
//            free(image1.pucData);
//            sprintf(path,"http://%s/piclog/%s/bb/%s%s.jpg",local_ip.c_str(),str_date.c_str(),str_ms.c_str(),plate);
//            if(rtn == 6 && strcmp(plate,"无车牌") == 0)
//            {
//
//            }
//            else
//            {
//                sendMsg(false,false,plate,color,path);
//            }
//            B = 0;
//        }
//        free( image.pucD1);
//        if(pFrame->memory)
//            free(pFrame->memory);
//        if(pFrame)
//            free(pFrame);
//        if(buf)
//            free(buf);
//    }
//    return NULL;
//}
//
//
//void* bled_recv_thread(void *)
//{
//    char time_now[64];
//    char recv_buffer[4096];
//    Json::Reader reader;
//    Json::Value value;
//    time_t tm;
//    int recv_len = 0;
//
//
//    int server_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
//    struct sockaddr_in server_addr;
//    memset(&server_addr, 0, sizeof(server_addr));
//    server_addr.sin_family = AF_INET;
//    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
//    server_addr.sin_port = htons(5016);
//
//    struct sockaddr_in client_addr;
//    memset(&client_addr, 0, sizeof(client_addr));
//    int client_addr_len = sizeof(client_addr);
//
//    if(bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) //绑定地址
//    {
//
//        printf("bled_recv_thread bind error\n");
//        return 0;
//    }
//
//    printf("bled_recv_thread 启动成功 \n");
//
//    while(1)
//    {
//        usleep(200);
//        memset(recv_buffer, 0, sizeof(recv_buffer));
//        recv_len = recvfrom(server_sock, recv_buffer, sizeof(recv_buffer), 0,(struct sockaddr*)&client_addr, (socklen_t*)&client_addr_len); //接收数据
//
//
//        std::string cmd;
//        if(!reader.parse(recv_buffer, value)) //解析json数据
//        {
//            printf("%s##bled_recv_thread 解析json数据失败\n",time_now);
//            continue;
//        }
//        else
//        {
//            printf("收到数据 %s\n",recv_buffer);
//        }
//
//        cmd = value["in_out"].asString(); //解析cmd命令
//        printf("in_out is %s \n",cmd.c_str());
//        if(strcmp("入口",cmd.c_str()) == 0)
//        {
//            A = 1;
//        }
//        else if(strcmp("出口",cmd.c_str()) == 0)
//        {
//            B = 1;
//        }
//
//    }
//}

//相机视频解码初始化
//void jovideo_start()
//{
//    //中维世纪SDK初始化
//    if(!JCSDK_InitSDK(9200,NULL))
//    {
//        return;
//    }
//    //设置回调函数
//    JCSDK_RegisterCallback(event_callback, data_callback, NULL,raw_data_callback, search_callback);
//    //分析g_machine里面的摄像头配置，生成待连接的摄像头队列
//    if (g_machine.channel_a_enable) {
//        camera_video_a.camera_ip = g_machine.channel_a.main_camera.device_ip_id;
//        camera_video_a.username = g_machine.channel_a.main_camera.device_username;
//        camera_video_a.password = g_machine.channel_a.main_camera.device_password;
//        camera_videos.push((void*)&camera_video_a);
//        if(g_machine.a_aux_camera){
//            camera_video_aA.camera_ip = g_machine.channel_a.aux_camera.device_ip_id;
//            camera_video_aA.username = g_machine.channel_a.aux_camera.device_username;
//            camera_video_aA.password = g_machine.channel_a.aux_camera.device_password;
//            camera_videos.push((void*)&camera_video_aA);
//        }
//    }
//    if (g_machine.channel_b_enable) {
//        camera_video_b.camera_ip = g_machine.channel_b.main_camera.device_ip_id;
//        camera_video_b.username = g_machine.channel_b.main_camera.device_username;
//        camera_video_b.password = g_machine.channel_b.main_camera.device_password;
//        camera_videos.push((void*)&camera_video_b);
//        if(g_machine.b_aux_camera){
//            camera_video_bA.camera_ip = g_machine.channel_b.aux_camera.device_ip_id;
//            camera_video_bA.username = g_machine.channel_b.aux_camera.device_username;
//            camera_video_bA.password = g_machine.channel_b.aux_camera.device_password;
//            camera_videos.push((void*)&camera_video_bA);
//        }
//    }
//    //连接摄像头线程
//    pthread_t tid_connect_camera;
//    pthread_attr_t attr_connect_camera;
//    pthread_attr_init(&attr_connect_camera);
//    pthread_create(&tid_connect_camera, &attr_connect_camera,
//                   thread_connect_camera, NULL);
//    //A通道视频解码发送线程
//    pthread_t tid_video_a;
//    pthread_attr_t attr_video_a;
//    pthread_attr_init(&attr_video_a);
//    pthread_create(&tid_video_a, &attr_video_a,
//                   thread_video_a, NULL);
//
//    //A通道视频解码发送线程
//    pthread_t tid_video_aa;
//    pthread_attr_t attr_video_aa;
//    pthread_attr_init(&attr_video_aa);
//    pthread_create(&tid_video_aa, &attr_video_aa,
//                   thread_video_aa, NULL);
//    //B通道视频解码发送线程
//    pthread_t tid_video_b;
//    pthread_attr_t attr_video_b;
//    pthread_attr_init(&attr_video_b);
//    pthread_create(&tid_video_b, &attr_video_b,
//                   thread_video_b, NULL);
//
//    //B通道视频解码发送线程
//    pthread_t tid_video_bb;
//    pthread_attr_t attr_video_bb;
//    pthread_attr_init(&attr_video_bb);
//    pthread_create(&tid_video_bb, &attr_video_bb,
//                   thread_video_bb, NULL);
//
//    //AA通道视频解码发送线程
//    pthread_t tid_video_aA;
//    pthread_attr_t attr_video_aA;
//    pthread_attr_init(&attr_video_aA);
//    pthread_create(&tid_video_aA, &attr_video_aA,
//                   thread_video_aA, NULL);
//
//    //AA通道视频解码发送线程
//    pthread_t tid_video_aaA;
//    pthread_attr_t attr_video_aaA;
//    pthread_attr_init(&attr_video_aaA);
//    pthread_create(&tid_video_aaA, &attr_video_aaA,
//                   thread_video_aaA, NULL);
//    //BA通道视频解码发送线程
//    pthread_t tid_video_bA;
//    pthread_attr_t attr_video_bA;
//    pthread_attr_init(&attr_video_bA);
//    pthread_create(&tid_video_bA, &attr_video_bA,
//                   thread_video_bA, NULL);
//
//    //BA通道视频解码发送线程
//    pthread_t tid_video_bbA;
//    pthread_attr_t attr_video_bbA;
//    pthread_attr_init(&attr_video_bbA);
//    pthread_create(&tid_video_bbA, &attr_video_bbA,
//                   thread_video_bbA, NULL);
//
//    //接收bled发送地感信号
//    pthread_t tid_video_bled;
//    pthread_attr_t attr_video_bled;
//    pthread_attr_init(&attr_video_bled);
//    pthread_create(&tid_video_bled, &attr_video_bled,
//                   bled_recv_thread, NULL);
//}

////相机SDK连接设备
//bool JoveCameraVideo::connect()
//{
//    link_id = JCSDK_Connect((char*)camera_ip.c_str(), 9101, 1, (char*)username.c_str(), (char*)password.c_str(), 0, NULL);
//    printf("connect:\t%s\t%s\t%s\n", (char*)camera_ip.c_str(), (char*)username.c_str(), (char*)password.c_str());
//    return (link_id >= 0);
//}
//
//void sendMsg(bool in_out, bool aux, std::string plate, std::string color, std::string path)
//{
//    Json::Value json_car;
//    json_car.clear();
//    Json::Value json_car_info;
//    json_car_info.clear();
//    Json::Value json_vehicle;
//    json_vehicle.clear();
//    Json::Value json_car_info_aux;
//    json_car_info_aux.clear();
//    Json::Value json_vehicle_aux;
//    json_vehicle_aux.clear();
//    if(in_out)
//    {
//        json_car["cmd"] = Json::Value("car_come");
//        json_car["time"] = Json::Value(get_time_sec());
//        json_car["channel_id"] = Json::Value(g_machine.channel_a.channel_id);
//        json_car["in_out"] = Json::Value("入口");
//        if(!aux)
//        {
//            json_car_info["ipc_ip"] = Json::Value(g_machine.channel_a.main_camera.device_ip_id);
//            json_vehicle["plate"] = Json::Value(plate);
//            json_vehicle["pcolor"] = Json::Value(color);
//            json_vehicle["brand"] = Json::Value("");
//            json_vehicle["type"] = Json::Value("");
//            json_vehicle["color"] = Json::Value("");
//            json_vehicle["path"] = Json::Value(path);
//            json_car_info["vehicle"] = json_vehicle;
//            json_car["car_info"].append(json_car_info);
//        }
//        else
//        {
//            json_car_info_aux["ipc_ip"] = Json::Value(g_machine.channel_a.aux_camera.device_ip_id);
//            json_vehicle_aux["plate"] = Json::Value(plate);
//            json_vehicle_aux["pcolor"] = Json::Value(color);
//            json_vehicle_aux["brand"] = Json::Value("");
//            json_vehicle_aux["type"] = Json::Value("");
//            json_vehicle_aux["color"] = Json::Value("");
//            json_vehicle_aux["path"] = Json::Value(path);
//            json_car_info_aux["vehicle"] = json_vehicle_aux;
//            json_car["car_info"].append(json_car_info_aux);
//        }
//    }
//    else
//    {
//        json_car["cmd"] = Json::Value("car_come");
//        json_car["time"] = Json::Value(get_time_sec());
//        json_car["channel_id"] = Json::Value(g_machine.channel_b.channel_id);
//        json_car["in_out"] = Json::Value("出口");
//        if(!aux)
//        {
//            json_car_info["ipc_ip"] = Json::Value(g_machine.channel_b.main_camera.device_ip_id);
//            json_vehicle["plate"] = Json::Value(plate);
//            json_vehicle["pcolor"] = Json::Value(color);
//            json_vehicle["brand"] = Json::Value("");
//            json_vehicle["type"] = Json::Value("");
//            json_vehicle["color"] = Json::Value("");
//            json_vehicle["path"] = Json::Value(path);
//            json_car_info["vehicle"] = json_vehicle;
//            json_car["car_info"].append(json_car_info);
//        }
//        else
//        {
//            json_car_info_aux["ipc_ip"] = Json::Value(g_machine.channel_b.aux_camera.device_ip_id);
//            json_vehicle_aux["plate"] = Json::Value(plate);
//            json_vehicle_aux["pcolor"] = Json::Value(color);
//            json_vehicle_aux["brand"] = Json::Value("");
//            json_vehicle_aux["type"] = Json::Value("");
//            json_vehicle_aux["color"] = Json::Value("");
//            json_vehicle_aux["path"] = Json::Value(path);
//            json_car_info_aux["vehicle"] = json_vehicle_aux;
//            json_car["car_info"].append(json_car_info_aux);
//        }
//    }
//
//    std::string car_come_msg = json_car.toStyledString();
//    udp_sender1.send(car_come_msg);
//    log_output(car_come_msg);
//}
