cmake_minimum_required(VERSION 3.23)
project(lw2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-static")

include_directories(.)

        add_executable(lw2
        funcs.cpp
        funcs.h
        main.cpp
        TNode.h
        TPlayer.h
        TSensation.h)
