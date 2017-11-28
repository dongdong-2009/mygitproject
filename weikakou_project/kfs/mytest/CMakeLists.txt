include_directories(
    ${SOLUTION_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIB_DIR})

add_executable(mytest
    Boon.h

Boon_algo_type.h
demo.cpp
demo.h)

target_link_libraries(mytest  dl m    ${OpenCV_LIBS}  curl opencv_highgui opencv_core opencv_imgproc)
