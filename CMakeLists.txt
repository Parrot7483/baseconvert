cmake_minimum_required(VERSION 3.14)
project(base-convert)

# require C++20
set(CMAKE_CXX_STANDARD 20)
set(EXECUTABLE_NAME base-convert)
set(LIBRARY_NAME baseconvert)

# find GNU Multiple Precision Arithmetic Library
find_library(GMP_LIBXX gmpxx)
find_library(FMT fmt)

add_library(${LIBRARY_NAME} SHARED BaseConvert.cpp BaseConvert.h)
target_link_libraries(${LIBRARY_NAME} ${GMP_LIBXX} ${FMT})

add_executable(${EXECUTABLE_NAME} main.cpp)
target_link_libraries(${EXECUTABLE_NAME} PUBLIC ${LIBRARY_NAME})
