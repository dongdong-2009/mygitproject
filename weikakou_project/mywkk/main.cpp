//
// Created by boon/liupeng on 17-11-29.
//

#include "jovideo.h"
#include "mycommon.h"
#include "boon_log.h"
#include "myconf.h"

#include <iostream>
#include <memory>
#include <stdio.h>
#include <string.h>

using std::cout;
using std::endl;
using namespace BASE;

//定义全局变量 重新链接标志
bool g_connected_ = false;

// 写日志文件
void writelog(const char* _buf);
// 日志缓冲区
char g_log_buf_[LOG_BUF_SIZE] = {0};

int main()
{
    int ret = 0;

    writelog("\n");
    snprintf(g_log_buf_, sizeof(g_log_buf_), "************mywkk main 启动********** line[%d]", __LINE__);
    writelog(g_log_buf_);

    //sdk初始化
    if (!JCSDK_InitSDK(9200,NULL))
    {
        snprintf(g_log_buf_, sizeof(g_log_buf_), "[%s] error! JCSDK_InitSDK failed! {请检查端口号9200是否正确} line[%d]", __FUNCTION__, __LINE__);
        writelog(g_log_buf_);
        return false;
    }
    else
    {
        snprintf(g_log_buf_, sizeof(g_log_buf_), "[%s] 初始化sdk成功! line[%d]", __FUNCTION__, __LINE__);
        writelog(g_log_buf_);
    }

    JCSDK_RegisterCallback(event_callback, data_callback, NULL,raw_data_callback, search_callback);

    //链接相机线程
    pthread_t tid_connect;
    ret = pthread_create(&tid_connect, NULL, thread_connect, NULL);
    if (!ret)
    {
        snprintf(g_log_buf_, sizeof(g_log_buf_), "[%s] 连接相机线程启动成功! line[%d]", __FUNCTION__, __LINE__);
        writelog(g_log_buf_);
    }
    else
    {
        snprintf(g_log_buf_, sizeof(g_log_buf_), "[%s] error! 连接相机线程启动失败! line[%d]", __FUNCTION__, __LINE__);
        writelog(g_log_buf_);
    }

    //码流处理线程
    pthread_t tid_video;
    ret = pthread_create(&tid_video, NULL, thread_video, NULL);
    if (!ret)
    {
        snprintf(g_log_buf_, sizeof(g_log_buf_), "[%s] 采集视频流线程启动成功! line[%d]", __FUNCTION__, __LINE__);
        writelog(g_log_buf_);
    }
    else
    {
        snprintf(g_log_buf_, sizeof(g_log_buf_), "[%s] error! 采集视频流线程启动失败! line[%d]", __FUNCTION__, __LINE__);
        writelog(g_log_buf_);
    }


    pthread_join(tid_connect, NULL);
    pthread_join(tid_video, NULL);

    while(1)
    {
       usleep(1);
    }

    return 0;
}

/**
 * @brief: 写日志，注意日志的文件目录
 * @param _buf :日志缓冲区
 * @attention: 注意日志缓冲区的的大小，写缓冲区时请用snprintf()安全函数写入
 */
void writelog(const char* _buf) {
    BLog::writelog(_buf, PKGDATA, LOG_DIR_NAME, LOG_FILE_NAME);

    std::cout << (char*)_buf << endl;
}