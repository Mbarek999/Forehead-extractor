cmake_minimum_required(VERSION 3.12)
project(ForeheadExtractor)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(Forehead_extractor main.cpp)
target_link_libraries(Forehead_extractor ${OpenCV_LIBS})
