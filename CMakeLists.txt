cmake_minimum_required(VERSION 3.22)
project(chess)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        "C:\\Program Files (x86)\\SFML\\include"
)
link_directories(
        "C:\\Program Files (x86)\\SFML\\lib"
)

add_executable(chess main.cpp)
target_link_libraries(chess sfml-audio sfml-window sfml-system sfml-network sfml-main sfml-graphics)
