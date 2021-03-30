cmake_minimum_required(VERSION 3.17)
project(CS202GroupProject)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(CS202GroupProject
        src/debug.h
        src/main.cpp
        src/olcPixelGameEngine.h)
