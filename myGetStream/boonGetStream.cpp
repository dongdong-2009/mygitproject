//
// Created by boon on 17-11-21.
//

#include "boonGetStream.h"
#include "./include/jcsdk.h"

boonGetStream::boonGetStream(string server, int port, int channel, string netUser, string pwd, bool numOrIP,
                             LPVOID userData) {
    szServer = server;
    nPort = port;
    nChannel = channel;
    szNetUser = netUser;
    szPwd = pwd;
    bNumOrIP = numOrIP;
    pUserData = userData;
}

boonGetStream::~boonGetStream() {

}

int boonGetStream::connect() {
    JCLink_t link_id = 0;
    link_id = JCSDK_Connect((char*)szServer.c_str(), nPort, nChannel, (char*)szNetUser.c_str(), (char*)szPwd.c_str(), bNumOrIP, pUserData);
    printf("connect:\t%s\t%s\t%s\n", (char*)szServer.c_str(), (char*)szNetUser.c_str(), (char*)szPwd.c_str());
    return link_id;
}