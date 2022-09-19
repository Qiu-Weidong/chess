cmake_minimum_required(VERSION 3.22)
project(chess)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        "C:\\Program Files (x86)\\SFML\\include"
        "${CMAKW_SOURCE_DIR}\\src"
)
link_directories(
        # "C:\\Users\\56838\\Downloads\\SFML-2.5.1-sources\\SFML-2.5.1\\build\\lib"
        "C:\\Users\\56838\\Downloads\\SFML-2.5.1-sources\\SFML-2.5.1\\release\\lib"
        # "C:\\Program Files (x86)\\SFML\\lib"
)

add_executable(chess # WIN32
        src/main.cpp src/game.cpp src/game.h src/stone.h src/stonemap.cpp src/stonemap.h
        src/settings.h src/settings.cpp src/asset.h src/asset.cpp src/app.h src/app.cpp
        src/computerplayer.h src/computerplayer.cpp src/icon.rc 
)
target_link_libraries(chess sfml-audio sfml-window sfml-system sfml-network sfml-main sfml-graphics)
