cmake_minimum_required(VERSION 3.23)
project(lw3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-static")

include_directories(.)

add_executable(lw3
        funcs.cpp
        funcs.h
        main.cpp)
