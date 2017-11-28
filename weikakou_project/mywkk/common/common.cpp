#include "common.h"
#include <string.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <fstream>

extern "C"
{
#include <jpeglib.h>
}

std::fstream g_log_file;

std::string get_time_us()
{
	char t[256];
	struct timeval tv;
	struct timezone tz;
	struct tm *p;
	gettimeofday(&tv, &tz);
	p = localtime(&tv.tv_sec);

	sprintf(t, "%04d%02d%02d-%02d:%02d:%02d.%06d", 1900 + p->tm_year,
			1 + p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min,
			p->tm_sec, (int) tv.tv_usec);
	std::string str = t;
	return str;
}

std::string get_time_ms()
{
	char t[256];
	struct timeval tv;
	struct timezone tz;
	struct tm *p;
	gettimeofday(&tv, &tz);
	p = localtime(&tv.tv_sec);

	sprintf(t, "%04d%02d%02d-%02d%02d%02d.%03d", 1900 + p->tm_year,
			1 + p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min,
			p->tm_sec, (int) tv.tv_usec/1000);
	std::string str = t;
	return str;
}

std::string get_time_sec()
{
	char t[256];
	struct timeval tv;
	struct timezone tz;
	struct tm *p;
	gettimeofday(&tv, &tz);
	p = localtime(&tv.tv_sec);

	sprintf(t, "%04d-%02d-%02d %02d:%02d:%02d", 1900 + p->tm_year,
			1 + p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min,
			p->tm_sec);
	std::string str = t;
	return str;
}

std::string get_time_date()
{
	char t[256];
	struct timeval tv;
	struct timezone tz;
	struct tm *p;
	gettimeofday(&tv, &tz);
	p = localtime(&tv.tv_sec);
	sprintf(t, "%04d%02d%02d", 1900 + p->tm_year, 1 + p->tm_mon,
			p->tm_mday);
	std::string str = t;
	return str;
}

void msg_print(std::string msg)
{
	std::cout << "[" << get_time_us() << "]\t" << msg << std::endl;
}

void log_init()
{
	//创建log文件夹
	create_dir("../log");
	std::string log_file_name = "../log/bipc_" + get_time_date() + ".log";
	g_log_file.open(log_file_name.c_str(), std::ios::out | std::ios::app);
	if (g_log_file.good())
		msg_print("日志系统初始化完成。");
	else
		msg_print("日志系统初始化失败，程序将在无日志状态下运行。");
}

void log_output(std::string msg)
{
	if (g_log_file.good())
	{
		std::string log_msg = "[" + get_time_us() + "]" + msg;
		g_log_file << log_msg << std::endl;
	}
}

bool get_local_ip(std::string dev, std::string & str_ip)
{
	bool result = false;
	struct ifaddrs * ifAddrStruct = NULL;
	void * tmpAddrPtr = NULL;

	getifaddrs(&ifAddrStruct);

	while (ifAddrStruct != NULL)
	{
		if (ifAddrStruct->ifa_addr->sa_family == AF_INET) // check it is IP4
		{
			tmpAddrPtr =
					&((struct sockaddr_in *) ifAddrStruct->ifa_addr)->sin_addr;
			char addressBuffer[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, tmpAddrPtr, addressBuffer,
			INET_ADDRSTRLEN);
			if (dev == ifAddrStruct->ifa_name)
			{
				str_ip = addressBuffer;
				result = true;
				break;
			}
		}
		ifAddrStruct = ifAddrStruct->ifa_next;
	}
	return result;
}

std::string get_local_ip()
{
	std::string ip_addr="127.0.0.1";
	for(int i = 0;i<10;i++)
	{
		char dev[10]="";
		sprintf(dev, "eth%d", i);
		if(get_local_ip(dev, ip_addr))
		{
			return ip_addr;
		}
	}
	return ip_addr;
}

int create_dir(const char *s_path_name)
{
	char DirName[256];
	strcpy(DirName, s_path_name);
	int i, len = strlen(DirName);
	if (DirName[len - 1] != '/')
		strcat(DirName, "/");

	len = strlen(DirName);

	for (i = 1; i < len; i++)
	{
		if (DirName[i] == '/')
		{
			DirName[i] = 0;
			if (access(DirName, F_OK) != 0)
			{
				if (mkdir(DirName, 0755) == -1)
				{
					perror("mkdir   error");
					return -1;
				}
			}
			DirName[i] = '/';
		}
	}

	return 0;
}

/*********************进程互斥（用文件）***********************************/
bool is_have_instance()
{
	int file_id = open("./bvs.tmp", O_RDWR | O_CREAT, 0640);
	if (file_id < 0)
	{
		return true;
	}

	if (flock(file_id, LOCK_EX | LOCK_NB) < 0)
	{
		return true;
	}

	return false;
}
/*********************end**********************************************/

std::vector<std::string> string_split(std::string str,std::string pattern)
{
    std::string::size_type pos;
    std::vector<std::string> result;
    str+=pattern;
    int size=str.size();

    for(int i=0; i<size; i++)
    {
        pos=str.find(pattern,i);
        if(pos<size)
        {
            std::string s=str.substr(i,pos-i);
            result.push_back(s);
            i=pos+pattern.size()-1;
        }
    }
    return result;
}

int write_jpeg_file(const char* jpeg_file, unsigned char* rgb_buffer, int width, int height, int quality)  
{  

 //   BGRFromRGB(rgb_buffer,width,height);

    struct jpeg_compress_struct cinfo;  
    struct jpeg_error_mgr jerr;  
    int row_stride = 0;  
    FILE* fp = NULL;  
    JSAMPROW row_pointer[1];  
  
    cinfo.err = jpeg_std_error(&jerr);  
  
    jpeg_create_compress(&cinfo);  
    fp = fopen(jpeg_file, "wb");  
    if (fp == NULL)  
    {  
        printf("open file %s failed.\n", jpeg_file);  
        return -1;  
    }  
    jpeg_stdio_dest(&cinfo, fp);  
    cinfo.image_width = width;  
    cinfo.image_height = height;  
    cinfo.input_components = 3;  
    cinfo.in_color_space = JCS_RGB;  //JCS_YCbCr  JCS_RGB
  
    jpeg_set_defaults(&cinfo);  
    jpeg_set_quality(&cinfo, quality, TRUE);  // todo 1 == true  
    jpeg_start_compress(&cinfo, TRUE);  
    row_stride = width * cinfo.input_components;  
  
    while (cinfo.next_scanline < cinfo.image_height)  
    {  
        row_pointer[0] = &rgb_buffer[cinfo.next_scanline * row_stride];  
        jpeg_write_scanlines(&cinfo, row_pointer, 1);  
    }  
  
    jpeg_finish_compress(&cinfo);  
    jpeg_destroy_compress(&cinfo);  
    fclose(fp);  
  
    return 0;  
}  

