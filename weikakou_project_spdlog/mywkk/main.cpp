//
// Created by boon/liupeng on 17-11-29.
//

#include "../jovideo/jovideo.h"
#include "../include/mycommon.h"

#include <iostream>
#include <memory>
#include <stdio.h>
#include <string.h>
#include <spdlog/spdlog.h>

using std::cout;
using std::endl;
namespace  spd = spdlog;

//定义全局变量 重新链接标志
bool g_reconn_ = false;

int main()
{
    int ret = 0;
    std::string logFilename = "../logs/spdlog_boonWKK.txt";

    try
    {
        auto console = spd::stdout_logger_mt("console");
        //创建日志文件
        auto my_logger = spd::basic_logger_mt("basic_logger", "../logs/basic.txt");

        //spdlog 自定义消息输出格式
        spd::set_pattern("----[%Y-%m-%d %H:%M:%S %l] [thread %t] %v ----");

        //运行日志级别
        spd::set_level(spd::level::info);

        my_logger->info("Some log message");

        console->info("main running...");
        console->info("Creating file {0}...", logFilename);


        //sdk初始化
        if (!JCSDK_InitSDK(9200,NULL))
        {
            console->info("{0}, line[{1}]:sdk init failed.", __FUNCTION__, __LINE__);
            return false;
        }
        else
        {
            console->info("sdk init success");
        }

        JCSDK_RegisterCallback(event_callback, data_callback, NULL,raw_data_callback, search_callback);

        //链接相机线程
        pthread_t tid_connect;
        ret = pthread_create(&tid_connect, NULL, thread_connect, NULL);
        if (!ret)
        {
            console->info("thread_connect run...");
        }
        else
        {
            console->info("{0}, line[{1}]:thread create failed.", __FUNCTION__, __LINE__);
        }

        //码流处理线程
        pthread_t tid_video;
        ret = pthread_create(&tid_video, NULL, thread_video, NULL);
        if (!ret)
        {
            console->info("thread_video run...");
        }
        else
        {
            console->info("{0}, line[{1}]:thread create failed.", __FUNCTION__, __LINE__);
        }


        pthread_join(tid_connect, NULL);
        pthread_join(tid_video, NULL);

//        while(1)
//        {
//           usleep(500);
//        }
    }
    catch (const spd::spdlog_ex& ex)
    {
        std::cout << "Log init failed: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}