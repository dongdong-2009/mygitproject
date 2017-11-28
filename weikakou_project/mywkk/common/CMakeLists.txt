include_directories(
  /usr/local/include/libavcodec
  /usr/local/include/libavdevice
    )
link_directories(/usr/local/lib)
add_library(common
	common.h
	common.cpp
	net_udp.h
	net_udp.cpp
	codec.h
	codec.cpp
	bglobal.h
	bglobal.cpp
	concurrent_queue.h
	concurrent_queue.cpp
)

target_link_libraries(common pthread jpeg boost_system boost_thread avcodec avformat avutil swscale)

