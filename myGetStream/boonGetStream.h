//
// Created by boon on 17-11-21.
//

#ifndef MYGETSTREAM_BOONGETSTREAM_H
#define MYGETSTREAM_BOONGETSTREAM_H

#include <string>
#include "./include/jcsdk.h"

using std::string;

//存储视频帧的结构体
typedef struct BoonMemoryStruct
{
    char *memory;
    size_t size;
} BMS, *PBMS;


class boonGetStream {
public:
    boonGetStream(string server, int port, int channel, string netUser, string pwd, bool numOrIP, LPVOID userData);
    ~boonGetStream();
    int connect();

private:
    string szServer;
    int nPort;
    int nChannel;
    string szNetUser;
    string szPwd;
    bool bNumOrIP;
    LPVOID pUserData;


};


#endif //MYGETSTREAM_BOONGETSTREAM_H
