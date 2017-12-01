#ifndef _BOON_JOVIDEO_H
#define _BOON_JOVIDEO_H

#include "../common/common.h"
#include "../common/bglobal.h"

#include "../include/jcsdk.h"
#include "../include/myconf.h"
#include "../common/concurrent_queue.h"
#include "../common/codec.h"

#include <spdlog/spdlog.h>

//
extern bool g_reconn_;
extern JCLink_t g_link_id;

//存储视频帧的结构体
typedef struct BoonMemoryStruct
{
	char *memory;
	size_t size;
} BMS, *PBMS;


//中维世纪相机视频流解码类
class JoveCameraVideo
{
public:
	std::string camera_ip;		//相机IP地址
	std::string username;		//用户名
	std::string password;		//密码
	int m_link_id_;				//连接码

public:
	JoveCameraVideo()
	{
		camera_ip = "";
		username = "";
		password = "";
		m_link_id_ = -1;
        decoder = new VideoDecoder;
    }
	JoveCameraVideo(const JoveCameraVideo &jcv)
	{
		camera_ip = jcv.camera_ip;
		username = jcv.username;
		password = jcv.password;
		m_link_id_ = jcv.m_link_id_;

	}
	JoveCameraVideo& operator=(const JoveCameraVideo &jcv)
	{
		camera_ip = jcv.camera_ip;
		username = jcv.username;
		password = jcv.password;
		m_link_id_ = jcv.m_link_id_;
		
		return *this;
	}
private:
public:
    VideoDecoder *decoder;

};

int connect(std::string server, int port, int channel, std::string netUser, std::string pwd, bool numOrIP, LPVOID userData);

void event_callback(JCLink_t nLinkID, JCEventType etType, DWORD_PTR pData1,
					DWORD_PTR pData2, LPVOID pUserData);
void data_callback(JCLink_t nLinkID, PJCStreamFrame pFrame, LPVOID pUserData);
void raw_data_callback(JCLink_t nLinkID, PJCRawFrame pFrame, LPVOID pUserData);
void search_callback(PJCLanDeviceInfo pDevice);

int LoadHZKResourse(void);

void * thread_connect(void * para);
void * thread_video(void* para);
#endif
