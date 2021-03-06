cmake_minimum_required(VERSION 2.8)
project(Editor)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic -pthread -I.")
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(COMMON_SOURCE_DIR ${PROJECT_SOURCE_DIR}/../common)
set(CLIENT_RESOURCES ${PROJECT_SOURCE_DIR}/../client/src/ui)
set(CLIENT_SRC ${PROJECT_SOURCE_DIR}/../client/src)
set(VIEW_WORM_STATE_DIR ${PROJECT_SOURCE_DIR}/../client/src/ui/worm_state)

find_package(SDL2 REQUIRED)
find_package(Qt5 COMPONENTS Widgets DBus REQUIRED)
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
include_directories(${VIEW_WORM_STATE_DIR})
include_directories(${CLIENT_SRC})
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${COMMON_SOURCE_DIR}/include)
include_directories(${COMMON_SOURCE_DIR}/include/yaml-cpp)

qt5_wrap_ui(UIS_HEADERS
        ${PROJECT_SOURCE_DIR}/qtdesigner/editor_launcher.ui
)

SET(UI_RESOURCES
	${PROJECT_SOURCE_DIR}/qtdesigner/resources.qrc
)

QT5_ADD_RESOURCES(UI_RESOURCES_RCC ${UI_RESOURCES})

add_executable(worms-editor
		${PROJECT_SOURCE_DIR}/src/main.cpp
		${PROJECT_SOURCE_DIR}/src/editor_launcher.cpp
		${PROJECT_SOURCE_DIR}/src/editor.cpp
		${PROJECT_SOURCE_DIR}/src/map_state.cpp
		${PROJECT_SOURCE_DIR}/src/map_state.h
		${PROJECT_SOURCE_DIR}/src/map_game.cpp
		${COMMON_SOURCE_DIR}/src/thread.cpp
		${COMMON_SOURCE_DIR}/src/paths.cpp
		${COMMON_SOURCE_DIR}/src/sound_effect.cpp
		${COMMON_SOURCE_DIR}/src/sdl_timer.cpp
		${CLIENT_RESOURCES}/camera.cpp
		${CLIENT_RESOURCES}/rectangle_text.cpp
		${CLIENT_RESOURCES}/explosion.cpp
		${CLIENT_RESOURCES}/sight.cpp
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
		${CLIENT_RESOURCES}/flash_notice.cpp
		${VIEW_WORM_STATE_DIR}/breathing.cpp
		${VIEW_WORM_STATE_DIR}/walking.cpp
		${VIEW_WORM_STATE_DIR}/falling.cpp
		${VIEW_WORM_STATE_DIR}/flying.cpp
		${VIEW_WORM_STATE_DIR}/dead.cpp
		${PROJECT_SOURCE_DIR}/src/map_game.h
		${COMMON_SOURCE_DIR}/src/paths.h
		${COMMON_SOURCE_DIR}/src/thread.h
		${COMMON_SOURCE_DIR}/src/types.h
		${COMMON_SOURCE_DIR}/src/sound_effect.h
		${COMMON_SOURCE_DIR}/src/sdl_timer.h
		${PROJECT_SOURCE_DIR}/src/editor_launcher.h
		${PROJECT_SOURCE_DIR}/src/editor.h
		${CLIENT_RESOURCES}/camera.h
		${CLIENT_RESOURCES}/rectangle_text.h
		${CLIENT_RESOURCES}/explosion.h
		${CLIENT_RESOURCES}/sight.h
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
		${CLIENT_RESOURCES}/flash_notice.h
		${UIS_HEADERS}
		${UI_RESOURCES_RCC}
		${VIEW_WORM_STATE_DIR}/worm_state.h
		${VIEW_WORM_STATE_DIR}/breathing.h
		${VIEW_WORM_STATE_DIR}/walking.h
		${VIEW_WORM_STATE_DIR}/falling.h
		${VIEW_WORM_STATE_DIR}/flying.h
		${VIEW_WORM_STATE_DIR}/dead.h
		)

target_link_libraries(worms-editor Qt5::Widgets Qt5::DBus)
target_link_libraries(worms-editor ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES} ${SDL2MIXER_LIBRARIES})
target_link_libraries(worms-editor ${COMMON_SOURCE_DIR}/libs/libyaml-cpp.a)
