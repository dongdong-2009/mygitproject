#include "jovideo.h"
//#include "shmem.h"
#include <stdlib.h>
#include <dlfcn.h>
#include "alg.h"
#include "Boon_algo_type.h"
#include "Boon.h"
#include <jsoncpp/json/json.h>
#include "../cHttpClient.h"

#define HZK24SIZE 588822
#define ASC24SIZE 6150
#define	SM_BUF_SIZE	(960*540*3)

using std::cout;
using std::endl;

//定义全局变量 sdk链接返回值
JCLink_t g_link_id = JCSDK_INVALID_LINKVALUE;

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
JoveCameraVideo camera_video; //通道视频解码


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

int connect(std::string server, int port, int channel, std::string netUser, std::string pwd, bool numOrIP, LPVOID userData)
{
    JCLink_t link_id = 0;
    link_id = JCSDK_Connect((char*)server.c_str(), port, channel, (char*)netUser.c_str(), (char*)pwd.c_str(), numOrIP, userData);
//    spdlog::get("console")->info("connect to:{0} {1} {2}", (char*)server.c_str(), (char*)netUser.c_str(), (char*)pwd.c_str());
    return link_id;
}


//事件回调
void event_callback(JCLink_t nLinkID, JCEventType etType, DWORD_PTR pData1,
                    DWORD_PTR pData2, LPVOID pUserData)
{
//    spdlog::get("console")->info("event_callback:{0} {1}", nLinkID, etType);
    if(etType == JCET_ConnectOK)			//连接成功
    {
        g_reconn_ = false;
//        g_reconn_ = true;
//        spdlog::get("console")->info("通道链接成功");
    }
    else if(etType == JCET_UserAccessError)	//密码错误
    {
//        spdlog::get("console")->info("通道密码错误");
    }
    else if(etType==JCET_ConTimeout)	//连接超时
    {
        g_reconn_ = true;
//        spdlog::get("console")->info("通道链接超时");
//        spdlog::get("console")->info("JCET_ConTimeout reconnect ...");
        JCSDK_Disconnect(g_link_id);
    }
    else if (etType==JCET_ConAbout)	//异常断开
    {
        g_reconn_ = true;
//        spdlog::get("console")->info("通道异常断开");
//        spdlog::get("console")->info("JCET_ConAbout reconnect ...");
        JCSDK_Disconnect(g_link_id);
    }
}

//数据回调
void data_callback(JCLink_t nLinkID, PJCStreamFrame pFrame, LPVOID pUserData)
{
    if (pFrame->sType != JCFT_Audio) {  //忽略掉音频数据
        PBMS pbms = (PBMS)malloc(sizeof(BMS));
        pbms->size = pFrame->nFrameSize;
        pbms->memory = (char*)malloc(pbms->size);
        memcpy(pbms->memory, pFrame->pFrameData, pbms->size);

//        spdlog::get("console")->info("data_callback,video:{0} {1}", nLinkID, pFrame->nFrameSize);

//        std::string str_ms = get_time_ms();
//        cout << "data_callback" << str_ms << endl;

        video_queue.push((void *)pbms);
        //设置休眠，控制每秒获取帧数为10
        usleep(50000);

    }
    else
    {
//        spdlog::get("console")->info("data_callback,audio:continue...");
    }
}
//裸数据回调
void raw_data_callback(JCLink_t nLinkID, PJCRawFrame pFrame, LPVOID pUserData)
{
//    spdlog::get("console")->info("raw_data_callback");
}
//设备搜索回调
void search_callback(PJCLanDeviceInfo pDevice)
{
//    spdlog::get("console")->info("search_callback");
}


void * thread_connect(void * para)
{
    do
     {
//         spdlog::get("console")->info("thread_connect,g_reconn_:{0}", g_reconn_);

        std::string strIP = CAMERA_IP;
        std::string strUser = CAMERA_USER;
        std::string strPwd = CAMERA_PWD;
        int nPort = CAMERA_PORT;
        g_link_id = connect(strIP, nPort, 1, strUser, strPwd, 0, NULL);

//        usleep(200000);
        sleep(2);
    }while (g_reconn_);
    return NULL;
}

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
        return 0;
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
        return 0;
    }
    int ret = LInit(ptr_out,1920,1080);
    if (ret != 0)
    {
        printf("alg1 init fail \n");
        return 0;
    }


    struct timeval tv1;
    struct timeval tv2;
    char plate[22];
    int color_plate;

    //Http Post Msg
    Json::Value hpm;
    Json::FastWriter writer;

    hpm["time"] = "";
    hpm["dev"] = "";
    hpm["channel"] = "";
    hpm["direction"] = "";
    hpm["plate"] = "";
    hpm["pcolor"] = "";
    hpm["brand"] = "";
    hpm["type"] = "";

    std::string url = HTTP_URL;
    std::string response = "";
    int res = 0;

    CHttpClient* cHttpClient = new CHttpClient;


    std::string local_ip = get_local_ip();
    while (true) {
        //防止一直占用CPU资源
        usleep(100);

//        spdlog::get("console")->info("111");

        void * p = NULL;

        video_queue.wait_and_pop(p);
//        spdlog::get("console")->info("222");

        PBMS pFrame = (PBMS)p;
//        spdlog::get("console")->info("A decode");
        unsigned char *buf = (unsigned char *)malloc(SM_BUF_SIZE);
        camera_video.decoder->h264_2_rgb((unsigned char *)pFrame->memory,pFrame->size,buf,nullptr);
//        spdlog::get("console")->info("333");

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
//        spdlog::get("console")->info("444");
        std::string str_time = get_time_sec();
        std::string str_date = get_time_date();
        std::string str_ms = get_time_ms();

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

//            spdlog::get("console")->info("result is {0} color is {1}",plate,color);
            char str_msg[1024];
            char path[1024];
            char pic_path[1024];
            char dir_path[1024];
            memset(str_msg,0,1024);
            memset(path,0,1024);
            memset(pic_path,0,1024);
            memset(dir_path,0,1024);



            sprintf(pic_path,"%s/%s/%s%s.jpg",JPEG_SAVE_DIR,str_date.c_str(),str_ms.c_str(),plate);
            sprintf(dir_path,"%s/%s",JPEG_SAVE_DIR,str_date.c_str());
            create_dir(dir_path);
//            spdlog::get("console")->info("555");

            write_jpeg_file(pic_path,buf,960,540,90);
//            spdlog::get("console")->info("666");

//            spdlog::get("console")->info("save jpeg file to:{0}", pic_path);

            hpm["time"] = str_time;
            hpm["dev"] = "";
            hpm["channel"] = "";
            hpm["direction"] = "";
            hpm["plate"] = plate;
            hpm["pcolor"] = color;
            hpm["brand"] = "";
            hpm["type"] = "";

            std::string json_str = writer.write(hpm);
            std::string jpeg_str = pic_path;
//            spdlog::get("console")->info("777");

            res = cHttpClient->Post(url, json_str, jpeg_str, response);
            if (!res)
            {
//                spdlog::get("console")->info("http post success");
            }
            else
            {
//                spdlog::get("console")->info("http post failed");
            }
//            spdlog::get("console")->info("888");

        }


        free( image.pucD1);

        if(pFrame->memory)
            free(pFrame->memory);
        if(pFrame)
            free(pFrame);
        if(buf)
            free(buf);
    }
    delete cHttpClient;
    return NULL;
}
