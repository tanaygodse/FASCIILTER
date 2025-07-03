cmake_minimum_required(VERSION 3.16)
project(ASCII_Webcam_Filter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED COMPONENTS core imgproc imgcodecs videoio highgui)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(include)

add_executable(ascii_webcam
    src/main.cpp
    src/ascii_converter.cpp
    src/webcam_capture.cpp
)

add_executable(test_ascii
    src/test_ascii.cpp
    src/ascii_converter.cpp
)

target_link_libraries(ascii_webcam ${OpenCV_LIBS})
target_link_libraries(test_ascii ${OpenCV_LIBS})

set(CMAKE_BUILD_TYPE Debug)