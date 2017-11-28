/***************************bglobal.cpp***************************************
			  功能：全局变量
			  创建时间：2017-02-04
			  创建人：孙振行(孙希伟修改)
			  单位：山东博昂信息科技有限公司
			  修改时间：2017-02-06
***************************************************************************/
#include "bglobal.h"

UdpSender udp_sender;	//与Bcenter通讯专用udp发射器
UdpSender udp_sender1;	//与Bipc通讯专用udp发射器
UdpReceiver udp_receiver;	//与Bcenter通讯专用udp接收器

bool g_bipc_config_done;	//全局设备参数初始化

Machine g_machine;			//全局设备配置类

std::string g_ip_addr;			//本机IP地址
