cmake_minimum_required(VERSION 2.8)
project( DisplayImage )
find_package( OpenCV REQUIRED )

FILE(GLOB sources *.cpp */*.cpp)
include_directories( ${OpenCV_INCLUDE_DIRS} headers)
list (REMOVE_ITEM sources ${CMAKE_CURRENT_SOURCE_DIR}/main2.cpp)
list( APPEND CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall -g -ftest-coverage -fprofile-arcs")
add_executable(main ${sources})
target_link_libraries( main ${OpenCV_LIBS} )

