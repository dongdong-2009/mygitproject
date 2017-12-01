# specify the source directory and the binary directory
# press configure
# set CMAKE_INSTALL_PREFIX to the path where you want to install the program
# press configure
# check BUILD_WITH_QT if you want to build the program with a QT-Config GUI
# check GENERATE_DEB_PACKAGE if you want to build a debian package (only on Linux)
#
# UNIX Makefile:
# 1) go to the binary folder and type "make" to build the project
# 2) (optional) type "make install all" to install the files into the install
#    directory
# 3) (optional) type "make package" to create a package of the install folder
#    (.tgz file if GENERATE_DEB_PACKAGE=false, .deb file if GENERATE_DEB_PACKAGE=true)
#
# Microsoft Visual C++:
# 1) open the .sln file
# 2) change the mode to "Release" -> only Release is supported!
# 3) build the project "ALL_BUILD" to build the opentld project
# 4) build the project "INSTALL" to install the files into the install
#    directory
# 5) build the project "PACKAGE" to create an NSIS-installer (NSIS is required)
#
# for Eclipse CDT
# cmake -G "Eclipse CDT4 - Unix Makefiles" ../src


project(WKK)

cmake_minimum_required(VERSION 2.6)

set(CMAKE_USE_RELATIVE_PATHS ON)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3  -fopenmp -mfpmath=sse  -msse4.2  -march=x86-64 -D HAVE_CBLAS  -D HAVE_GSL -D HAVE_SSE2 ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3  -fopenmp -mfpmath=sse -msse4.2 -march=x86-64 -D HAVE_CBLAS  -D HAVE_GSL -D HAVE_SSE2 ")

#find_package(OpenCV REQUIRED)

if(APPLE)
    add_definitions(-DHAVE_XLOCALE_H)
endif(APPLE)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

set(bin_dir "@PROJECT_BINARY_DIR@")
set(src_dir "@PROJECT_SOURCE_DIR@")

set(SOLUTION_INCLUDE_DIRS
        ${src_dir}/kfs
        ${src_dir}/mykkk
        )

#-------------------------------------------------------------------------------
#add subdirectorie
add_subdirectory(kfs)
add_subdirectory(mywkk)

