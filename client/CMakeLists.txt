cmake_minimum_required(VERSION 2.8)
project(Client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic -pthread -I.")
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(SDL2 REQUIRED)
find_package(Qt5 COMPONENTS Widgets DBus REQUIRED)
find_package(Threads)

INCLUDE(FindPkgConfig) 
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer>=2.0.0)


message("Directorio actual: ${PROJECT_SOURCE_DIR}")
include_directories(${PROJECT_SOURCE_DIR})

qt5_wrap_ui(UIS_HEADERS
        client_connector.ui
	client_lobby.ui
)

SET(UI_RESOURCES
	client_connector_resources.qrc
)

QT5_ADD_RESOURCES(UI_RESOURCES_RCC ${UI_RESOURCES})

add_executable(	client
		main.cpp 
		client_connector.cpp
		socket_error.cpp
		client_lobby.cpp
		protocol.cpp
		client_lobby_feeder.cpp
		socket.cpp
		thread.cpp
		protocol_error.cpp
		protocol_error.h
		client_connector.h
		socket.h
		socket_error.h
		client_lobby.h
		protocol.h
		client_lobby_feeder.h
		thread.h
		types.h
		${UIS_HEADERS}
		${UI_RESOURCES_RCC}
		)

target_link_libraries(client Qt5::Widgets Qt5::DBus)
target_link_libraries(client ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES} ${SDL2MIXER_LIBRARIES})
target_link_libraries(client ${PROJECT_SOURCE_DIR}/libs/libyaml-cpp.a)
