cmake_minimum_required(VERSION 3.22)
project(Semestralka)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)


# Set the path to the SDL2 and SDL2_ttf libraries
set(SDL2_PATH "libs/SDL2/x86_64-w64-mingw32")
set(SDL2_TTF_PATH "libs/SDL2_ttf/x86_64-w64-mingw32")


find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

# Find SDL2_ttf package
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIR})
include_directories(${SDL2_TTF_PATH}/include/SDL2)



include_directories("${SDL2_PATH}/include" "${SDL2_TTF_PATH}/include")
link_directories("${SDL2_PATH}/lib" "${SDL2_TTF_PATH}/lib")


add_executable(Semestralka main.cpp Tower.cpp Disk.cpp
        GameView.cpp
        GameController.cpp)

# Link SDL2 and SDL2_ttf libraries
target_link_libraries(${PROJECT_NAME}
        ${SDL2_LIBRARY}
        SDL2_ttf)
