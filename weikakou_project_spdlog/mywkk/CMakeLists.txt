cmake_minimum_required(VERSION 2.8)
project(myGetStream)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -g")


set(CMAKE_USE_RELATIVE_PATHS ON)


set(src_dir "@PROJECT_SOURCE_DIR@")
set(bin_dir "@PROJECT_BINARY_DIR@")

INCLUDE_DIRECTORIES(./include)

set(SOURCE_FILES
        main.cpp
        ./include/mycommon.h
        ./include/Boon.h
        ./include/Boon_algo_ivs_config.h
        ./include/Boon_algo_ivs_result.h
        ./include/Boon_algo_tripwire_param.h
        ./include/Boon_algo_tripwire_private.h
        ./jovideo/jovideo.h
        ./jovideo/jovideo.cpp
        ./jovideo/Boon.h
        ./jovideo/Boon_algo_lpr_define.h
        ./jovideo/Boon_algo_lpr_struct.h
        ./jovideo/Boon_algo_type.h
        ./jovideo/alg.h
        ./common/codec.h
        ./common/codec.cpp
        ./common/common.h
        ./common/common.cpp
        ./common/concurrent_queue.h
        ./common/concurrent_queue.cpp
        cHttpClient.cpp
        cHttpClient.h include/myconf.h)

#指定库文件的目录
link_directories(/usr/lib
                /usr/local/lib
        )

#指定可执行文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../../mywkk/bin/)

add_executable(mywkk ${SOURCE_FILES})
#添加库文件
target_link_libraries(mywkk jcsdk dl curl jsoncpp pthread jpeg boost_system boost_thread avcodec avformat avutil swscale ssl crypto)
