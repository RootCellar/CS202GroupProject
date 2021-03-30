cmake_minimum_required(VERSION 3.17)
project(CS202GroupProject)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)

add_executable(CS202GroupProject
        src/debug.h
        src/main.cpp
        src/olcPixelGameEngine.h)

if (UNIX AND NOT APPLE)
    #do something
    target_link_libraries(CS202GroupProject -lX11 -lGL -lpthread -lpng -lstdc++fs)
endif (UNIX AND NOT APPLE)