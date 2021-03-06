cmake_minimum_required(VERSION 2.8)
project(Client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic -pthread -I.")
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(COMMON_SOURCE_DIR ${PROJECT_SOURCE_DIR}/../common)
set(UI_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src/ui)
set(VIEW_WORM_STATE_DIR ${PROJECT_SOURCE_DIR}/src/ui/worm_state)

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
include_directories(${UI_SOURCE_DIR})
include_directories(${VIEW_WORM_STATE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${COMMON_SOURCE_DIR}/include)
include_directories(${COMMON_SOURCE_DIR}/include/yaml-cpp)

qt5_wrap_ui(UIS_HEADERS
	${PROJECT_SOURCE_DIR}/qtdesigner/clientlobby.ui
)

SET(UI_RESOURCES
	${PROJECT_SOURCE_DIR}/qtdesigner/client_lobby_resources.qrc
)

QT5_ADD_RESOURCES(UI_RESOURCES_RCC ${UI_RESOURCES})

add_executable(worms-client
		${PROJECT_SOURCE_DIR}/src/main.cpp
		${PROJECT_SOURCE_DIR}/src/event_sender.cpp
		${PROJECT_SOURCE_DIR}/src/client_lobby.cpp
		${PROJECT_SOURCE_DIR}/src/client_lobby.h
		${PROJECT_SOURCE_DIR}/src/client_game.cpp
		${PROJECT_SOURCE_DIR}/src/client_game.h
		${PROJECT_SOURCE_DIR}/src/waiting_match.cpp
		${PROJECT_SOURCE_DIR}/src/waiting_match.h
		${PROJECT_SOURCE_DIR}/src/model_receiver.cpp
		${PROJECT_SOURCE_DIR}/src/protected_dynamics.cpp
		${PROJECT_SOURCE_DIR}/src/client_configuration.cpp
		${PROJECT_SOURCE_DIR}/src/client_settings.cpp
		${PROJECT_SOURCE_DIR}/src/client_settings.h
		${COMMON_SOURCE_DIR}/src/paths.cpp
		${COMMON_SOURCE_DIR}/src/event.cpp
		${COMMON_SOURCE_DIR}/src/socket.cpp
		${COMMON_SOURCE_DIR}/src/thread.cpp
		${COMMON_SOURCE_DIR}/src/protocol.cpp
		${COMMON_SOURCE_DIR}/src/socket_error.cpp
		${COMMON_SOURCE_DIR}/src/protocol_error.cpp
		${COMMON_SOURCE_DIR}/src/sound_effect.cpp
		${COMMON_SOURCE_DIR}/src/sdl_timer.cpp
		${UI_SOURCE_DIR}/worms_status.cpp
		${UI_SOURCE_DIR}/camera.cpp
		${UI_SOURCE_DIR}/clock.cpp
		${UI_SOURCE_DIR}/girder.cpp
		${UI_SOURCE_DIR}/girder_long.cpp
		${UI_SOURCE_DIR}/girder_short.cpp
		${UI_SOURCE_DIR}/inventory.cpp
		${UI_SOURCE_DIR}/inventory_weapons.cpp
		${UI_SOURCE_DIR}/font.cpp
		${UI_SOURCE_DIR}/sprite_animation.cpp
		${UI_SOURCE_DIR}/texture.cpp
		${UI_SOURCE_DIR}/view_exceptions.cpp
		${UI_SOURCE_DIR}/water.cpp
		${UI_SOURCE_DIR}/window_game.cpp
		${UI_SOURCE_DIR}/worm.cpp
		${UI_SOURCE_DIR}/dynamite.cpp
		${UI_SOURCE_DIR}/explosion.cpp
		${UI_SOURCE_DIR}/projectil.cpp
		${UI_SOURCE_DIR}/projectiles.cpp
		${UI_SOURCE_DIR}/rectangle_text.cpp
		${UI_SOURCE_DIR}/sight.cpp
		${UI_SOURCE_DIR}/green_grenade.cpp
		${UI_SOURCE_DIR}/holy_grenade.cpp
		${UI_SOURCE_DIR}/shoot_power.cpp
		${UI_SOURCE_DIR}/banana.cpp
		${UI_SOURCE_DIR}/bazooka.cpp
		${UI_SOURCE_DIR}/air_strike.cpp
		${UI_SOURCE_DIR}/cluster.cpp
		${UI_SOURCE_DIR}/wind.cpp
		${UI_SOURCE_DIR}/teams_health.cpp
		${UI_SOURCE_DIR}/flash_notice.cpp
		${VIEW_WORM_STATE_DIR}/breathing.cpp
		${VIEW_WORM_STATE_DIR}/walking.cpp
		${VIEW_WORM_STATE_DIR}/falling.cpp
		${VIEW_WORM_STATE_DIR}/flying.cpp
		${VIEW_WORM_STATE_DIR}/dead.cpp
		${PROJECT_SOURCE_DIR}/src/event_sender.h
		${PROJECT_SOURCE_DIR}/src/model_receiver.h
		${PROJECT_SOURCE_DIR}/src/protected_dynamics.h
		${PROJECT_SOURCE_DIR}/src/client_configuration.h
		${COMMON_SOURCE_DIR}/src/paths.h
		${COMMON_SOURCE_DIR}/src/event.h
		${COMMON_SOURCE_DIR}/src/socket.h
		${COMMON_SOURCE_DIR}/src/thread.h
		${COMMON_SOURCE_DIR}/src/protocol.h
		${COMMON_SOURCE_DIR}/src/socket_error.h
		${COMMON_SOURCE_DIR}/src/protocol_error.h
		${COMMON_SOURCE_DIR}/src/types.h
		${COMMON_SOURCE_DIR}/src/blocking_queue.h
		${COMMON_SOURCE_DIR}/src/sound_effect.h
		${COMMON_SOURCE_DIR}/src/sdl_timer.h
		${UI_SOURCE_DIR}/worms_status.h
		${UI_SOURCE_DIR}/camera.h
		${UI_SOURCE_DIR}/clock.h
		${UI_SOURCE_DIR}/drawable.h
		${UI_SOURCE_DIR}/girder.h
		${UI_SOURCE_DIR}/girder_long.h
		${UI_SOURCE_DIR}/girder_short.h
		${UI_SOURCE_DIR}/inventory.h
		${UI_SOURCE_DIR}/inventory_weapons.h
		${UI_SOURCE_DIR}/font.h
		${UI_SOURCE_DIR}/sprite_animation.h
		${UI_SOURCE_DIR}/texture.h
		${UI_SOURCE_DIR}/view_exceptions.h
		${UI_SOURCE_DIR}/view_exceptions_messages.h
		${UI_SOURCE_DIR}/water.h
		${UI_SOURCE_DIR}/window_game.h
		${UI_SOURCE_DIR}/worm.h
		${UI_SOURCE_DIR}/dynamite.h
		${UI_SOURCE_DIR}/explosion.h
		${UI_SOURCE_DIR}/projectil.h
		${UI_SOURCE_DIR}/projectiles.h
		${UI_SOURCE_DIR}/rectangle_text.h
		${UI_SOURCE_DIR}/sight.h
		${UI_SOURCE_DIR}/green_grenade.h
		${UI_SOURCE_DIR}/holy_grenade.h
		${UI_SOURCE_DIR}/shoot_power.h
		${UI_SOURCE_DIR}/banana.h
		${UI_SOURCE_DIR}/bazooka.h
		${UI_SOURCE_DIR}/air_strike.h
		${UI_SOURCE_DIR}/flash_notice.h
		${UIS_HEADERS}
		${UI_RESOURCES_RCC}
		${UI_SOURCE_DIR}/cluster.h
		${UI_SOURCE_DIR}/wind.h
		${UI_SOURCE_DIR}/teams_health.h
		${VIEW_WORM_STATE_DIR}/worm_state.h
		${VIEW_WORM_STATE_DIR}/breathing.h
		${VIEW_WORM_STATE_DIR}/walking.h
		${VIEW_WORM_STATE_DIR}/falling.h
		${VIEW_WORM_STATE_DIR}/flying.h
		${VIEW_WORM_STATE_DIR}/dead.h
		)

target_link_libraries(worms-client Qt5::Widgets Qt5::DBus)
target_link_libraries(worms-client ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES} ${SDL2MIXER_LIBRARIES})
target_link_libraries(worms-client ${COMMON_SOURCE_DIR}/libs/libyaml-cpp.a)
