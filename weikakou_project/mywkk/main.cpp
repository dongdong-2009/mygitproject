#include <iostream>
#include <stdio.h>
#include <string.h>
#include "boonGetStream.h"
#include "concurrent_queue.h"
#include "./include/mycommon.h"
#include "./common/concurrent_queue.h"
#include "./jovideo/jovideo.h"

using std::cout;
using std::endl;


int main()
{
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

        pthread_t tid_video_a;
        pthread_attr_t attr_video_a;
        pthread_attr_init(&attr_video_a);
        pthread_create(&tid_video_a, &attr_video_a,
                       thread_video, NULL);

    }

    while(1){}

    return 0;
}