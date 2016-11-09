cmake_minimum_required(VERSION 3.6)
project(SignalEncoding)

find_package( OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp .idea/WavHeader.c WavHeader.h WavData.h Constants.h Graphs.h Graphs.cpp)
add_executable(SignalEncoding ${SOURCE_FILES} WavHeader.h)

target_link_libraries( SignalEncoding ${OpenCV_LIBS} )