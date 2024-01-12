cmake_minimum_required(VERSION 3.22)
project(Semestralka)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)

set(SDL2_PATH "libs/SDL2/x86_64-w64-mingw32")


find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(Semestralka main.cpp Tower.cpp Disk.cpp
        GameView.cpp
        GameController.cpp)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})



