cmake_minimum_required(VERSION 2.8)
project(myGetStream)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -g")

#
set(CMAKE_USE_RELATIVE_PATHS ON)

#
set(src_dir "@PROJECT_SOURCE_DIR@")
set(bin_dir "@PROJECT_BINARY_DIR@")
set(lib_dir "@PROJECT_BINARY_DIR@")

SET(EXECUTABLE_OUTPUT_PATH ${bin_dir}/bin)
SET(LIBRARY_OUTPUT_PATH ${lib_dir}/lib)

set(SOURCE_FILES
        main.cpp
        boonGetStream.cpp
        boonGetStream.h)

link_directories(/usr/lib/)


add_executable(myGetStream ${SOURCE_FILES})
target_link_libraries(myGetStream jcsdk)