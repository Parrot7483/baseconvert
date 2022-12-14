cmake_minimum_required(VERSION 3.14)
project(baseconvert)

enable_testing()

# require C++20
set(CMAKE_CXX_STANDARD 20)

# Set names
set(EXECUTABLE_NAME base-convert)
set(LIBRARY_NAME baseconvert)
set(TEST_NAME tests)

# find Doctest testing package
find_package(doctest REQUIRED)

# find GNU Multiple Precision Arithmetic Library
# find FMT formatting library
find_library(GMP_LIBXX gmpxx)
find_library(FMT fmt)

# Create library
add_library(${LIBRARY_NAME} SHARED BaseConvert.cpp BaseConvert.h)
target_link_libraries(${LIBRARY_NAME} ${GMP_LIBXX} ${FMT})

# Create Test
add_executable(${TEST_NAME} tests.cpp)
target_link_libraries(${TEST_NAME} PRIVATE ${LIBRARY_NAME} doctest::doctest)
add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})

# Create command line utility
add_executable(${EXECUTABLE_NAME} main.cpp)
target_link_libraries(${EXECUTABLE_NAME} PUBLIC ${LIBRARY_NAME})
