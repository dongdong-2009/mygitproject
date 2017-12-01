//
// Created by boon/liupeng on 17-12-1.
//

#ifndef WKK_MYCONF_H
#define WKK_MYCONF_H

// 相机登录参数
#define CAMERA_IP ("192.168.88.22")
#define CAMERA_USER ("abc")
#define CAMERA_PWD ("123")
#define CAMERA_PORT (9101)

// 日志缓冲区大小
#ifndef LOG_BUF_SIZE
#define LOG_BUF_SIZE (1024*4)
#endif

//日志输出的目录位置
#define LOG_DIR_NAME    "BoonCamera/log/weikaikou"
#define LOG_FILE_NAME   "wkk"

//http url
#define HTTP_URL ("http://123.233.246.99:120/dqz1.php")

//jpeg save dir
#define JPEG_SAVE_DIR ("/home/boon/carPicture")


#endif //WKK_MYCONF_H
