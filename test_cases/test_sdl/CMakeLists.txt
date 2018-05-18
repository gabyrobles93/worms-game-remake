cmake_minimum_required(VERSION 2.8)
project(test_sdl)

#set(CMAKE_MODULE_PACH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
set(COMMON_SOURCE_DIR ${PROJECT_SOURCE_DIR}/../../common)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic -pthread -I.")

#find_package(SDL2 REQUIRED)
#find_package(SDL"_image REQUIRED)

#include_directories(${SDL2_INCLUDE_DIR})

INCLUDE(FindPkgConfig) 
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer>=2.0.0)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${COMMON_SOURCE_DIR}/include)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRs})
include_directories(${COMMON_SOURCE_DIR}/include/yaml-cpp)


add_executable(
  test_sdl 
    main.cpp 
    girder.cpp 
    girder_short.cpp 
    girder_long.cpp 
    texture.cpp 
    view_exceptions.cpp 
    thread.cpp 
    sprite_animation.cpp 
    worm.cpp
    map_game.cpp
)

target_link_libraries(test_sdl ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES} ${SDL2MIXER_LIBRARIES})
target_link_libraries(test_sdl ${COMMON_SOURCE_DIR}/libs/libyaml-cpp.a)

