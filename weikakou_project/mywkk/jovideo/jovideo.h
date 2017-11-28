#ifndef _BOON_JOVIDEO_H
#define _BOON_JOVIDEO_H

#include "../common/common.h"
#include "../common/bglobal.h"

#include "../include/jcsdk.h"
#include "../common/concurrent_queue.h"
#include "../common/codec.h"


//存储视频帧的结构体
typedef struct BoonMemoryStruct
{
	char *memory;
	size_t size;
} BMS, *PBMS;

//相机视频解码初始化
//void jovideo_start();

//中维世纪相机视频流解码类
class JoveCameraVideo
{
public:
	std::string camera_ip;		//相机IP地址
	std::string username;		//用户名
	std::string password;		//密码
	int link_id;				//连接码

public:
	//bool connect();             //连接相机，连接之后就会收到码流

	JoveCameraVideo()
	{
		camera_ip = "";
		username = "";
		password = "";
		link_id = -1;
        decoder = new VideoDecoder;
    }
	JoveCameraVideo(const JoveCameraVideo &jcv)
	{
		camera_ip = jcv.camera_ip;
		username = jcv.username;
		password = jcv.password;
		link_id = jcv.link_id;

	}
	JoveCameraVideo& operator=(const JoveCameraVideo &jcv)
	{
		camera_ip = jcv.camera_ip;
		username = jcv.username;
		password = jcv.password;
		link_id = jcv.link_id;
		
		return *this;
	}
private:
public:
    VideoDecoder *decoder;

};

//void sendMsg(bool in_out,bool aux,std::string plate,std::string color,std::string path);

void event_callback(JCLink_t nLinkID, JCEventType etType, DWORD_PTR pData1,
					DWORD_PTR pData2, LPVOID pUserData);
void data_callback(JCLink_t nLinkID, PJCStreamFrame pFrame, LPVOID pUserData);
void raw_data_callback(JCLink_t nLinkID, PJCRawFrame pFrame, LPVOID pUserData);
void search_callback(PJCLanDeviceInfo pDevice);

int LoadHZKResourse(void);
void * thread_video(void* para);
#endif
