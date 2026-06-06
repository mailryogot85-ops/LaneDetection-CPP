cmake_minimum_required(VERSION 3.10)
project(LaneDetection)

# C++20の強固な環境を指定
set(CMAKE_CXX_STANDARD 20)

# OpenCVライブラリを探してリンクする
find_package(OpenCV REQUIRED)

# main.cpp をコンパイルして LaneDetection という実行ファイルを作る
add_executable(LaneDetection main.cpp)
target_link_libraries(LaneDetection ${OpenCV_LIBS})