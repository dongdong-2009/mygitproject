#include <iostream>
#include <stdio.h>
#include <string.h>
#include "boonGetStream.h"

using std::cout;
using std::endl;

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
}

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

    }
    else
    {
        printf("audio\n");
    }
}

void raw_data_callback(JCLink_t nLinkID, PJCRawFrame pFrame, LPVOID pUserData)
{
    printf("raw_data_callback\n");
}

void search_callback(PJCLanDeviceInfo pDevice)
{
    printf("search_callback\n");
}


int main() {
    if (!JCSDK_InitSDK(9200,NULL))
    {
        return false;
    }
    JCSDK_RegisterCallback(event_callback, data_callback, NULL,raw_data_callback, search_callback);
    string strIP="192.168.88.22";
    string strUser = "abc";
    string strPwd = "123";
    int nPort = 9101;

    boonGetStream bgs = boonGetStream(strIP, nPort, 1, strUser, strPwd, 0, NULL);
    JCLink_t link_id =  bgs.connect();
    if (link_id != JCSDK_INVALID_LINKVALUE)
    {
        cout << "connect success." << endl;
    }

    while(1){}

    return 0;
}