cmake_minimum_required(VERSION 2.8)
project(Editor)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic -pthread -I.")
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(COMMON_SOURCE_DIR ${PROJECT_SOURCE_DIR}/../common)
set(CLIENT_RESOURCES ${PROJECT_SOURCE_DIR}/../client/src/ui)

find_package(SDL2 REQUIRED)
find_package(Threads)

INCLUDE(FindPkgConfig) 
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer>=2.0.0)


include_directories(${PROJECT_SOURCE_DIR})
include_directories(${COMMON_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${COMMON_SOURCE_DIR}/src)
include_directories(${CLIENT_RESOURCES})
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${COMMON_SOURCE_DIR}/include)
include_directories(${COMMON_SOURCE_DIR}/include/yaml-cpp)

add_executable(	editor
		${PROJECT_SOURCE_DIR}/src/main.cpp
		${COMMON_SOURCE_DIR}/src/thread.cpp
		${CLIENT_RESOURCES}/camera.cpp
		${CLIENT_RESOURCES}/girder.cpp
		${CLIENT_RESOURCES}/girder_long.cpp
		${CLIENT_RESOURCES}/girder_short.cpp
		${CLIENT_RESOURCES}/inventory.cpp
		${CLIENT_RESOURCES}/inventory_weapons.cpp
		${CLIENT_RESOURCES}/inventory_editor.cpp
		${CLIENT_RESOURCES}/font.cpp
		${CLIENT_RESOURCES}/texture.cpp
		${CLIENT_RESOURCES}/view_exceptions.cpp
		${CLIENT_RESOURCES}/sprite_animation.cpp
		${CLIENT_RESOURCES}/water.cpp
		${CLIENT_RESOURCES}/window_game.cpp
		${CLIENT_RESOURCES}/worm.cpp
		${COMMON_SOURCE_DIR}/src/thread.h
		${COMMON_SOURCE_DIR}/src/types.h
		${CLIENT_RESOURCES}/camera.h
		${CLIENT_RESOURCES}/drawable.h
		${CLIENT_RESOURCES}/girder.h
		${CLIENT_RESOURCES}/girder_long.h
		${CLIENT_RESOURCES}/girder_short.h
		${CLIENT_RESOURCES}/inventory.h
		${CLIENT_RESOURCES}/inventory_weapons.h
		${CLIENT_RESOURCES}/inventory_editor.h
		${CLIENT_RESOURCES}/font.h
		${CLIENT_RESOURCES}/sprite_animation.h
		${CLIENT_RESOURCES}/texture.h
		${CLIENT_RESOURCES}/view_exceptions.h
		${CLIENT_RESOURCES}/view_exceptions_messages.h
		${CLIENT_RESOURCES}/water.h
		${CLIENT_RESOURCES}/window_game.h
		${CLIENT_RESOURCES}/worm.h
		)

target_link_libraries(editor ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES} ${SDL2MIXER_LIBRARIES})
target_link_libraries(editor ${COMMON_SOURCE_DIR}/libs/libyaml-cpp.a)
