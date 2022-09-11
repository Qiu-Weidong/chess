cmake_minimum_required(VERSION 3.22)
project(chess)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        "C:\\Program Files (x86)\\SFML\\include"
        "${CMAKW_SOURCE_DIR}\\src"
)
link_directories(
        "C:\\Program Files (x86)\\SFML\\lib"
)

add_executable(chess src/main.cpp src/game.cpp src/game.h src/stone.h src/stonemap.cpp src/stonemap.h
        src/settings.h src/settings.cpp
)
target_link_libraries(chess sfml-audio sfml-window sfml-system sfml-network sfml-main sfml-graphics)
