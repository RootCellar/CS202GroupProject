cmake_minimum_required(VERSION 3.17)
project(CS202GroupProject)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(CS202GroupProject
        src/main.cpp
        src/entity.cpp
        src/level.cpp
        src/Mob.cpp
        src/player.cpp
        src/projectile.cpp
        src/debug.cpp
        src/team.cpp
        )

if (UNIX AND NOT APPLE)
    #do something
    target_link_libraries(CS202GroupProject -lX11 -lGL -lpthread -lpng -lstdc++fs)
endif (UNIX AND NOT APPLE)

if(WIN32)
    target_link_libraries(CS202GroupProject -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi -lstdc++fs -static)
endif(WIN32)