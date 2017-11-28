
include_directories(
    ${SOLUTION_INCLUDE_DIRS}
)

add_library(jovideo
	jovideo.h
	jovideo.cpp
)

target_link_libraries(jovideo common dl jcsdk jsoncpp)

