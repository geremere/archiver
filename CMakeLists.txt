cmake_minimum_required(VERSION 3.14)
project(KDZ)

set(CMAKE_CXX_STANDARD 14)

add_executable(KDZ main.cpp src/Shenon_Fano.cpp src/Shenon_Fano.h src/Encode.cpp src/Encode.h src/Decode.cpp src/Decode.h)