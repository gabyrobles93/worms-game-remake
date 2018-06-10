cmake_minimum_required(VERSION 2.8)
project(Client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -Wextra -pedantic -pthread -I.")
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(COMMON_SOURCE_DIR ${PROJECT_SOURCE_DIR}/../../common)

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

add_executable(	client
		${PROJECT_SOURCE_DIR}/src/main.cpp 
		${PROJECT_SOURCE_DIR}/src/client_lobby.cpp
		${PROJECT_SOURCE_DIR}/src/client_lobby.h
		${PROJECT_SOURCE_DIR}/src/waiting_match.cpp
		${PROJECT_SOURCE_DIR}/src/waiting_match.h
		${COMMON_SOURCE_DIR}/src/socket.cpp
		${COMMON_SOURCE_DIR}/src/thread.cpp
		${COMMON_SOURCE_DIR}/src/protocol.cpp
		${COMMON_SOURCE_DIR}/src/event.cpp
		${COMMON_SOURCE_DIR}/src/socket_error.cpp
		${COMMON_SOURCE_DIR}/src/protocol_error.cpp		
		${COMMON_SOURCE_DIR}/src/socket.h
		${COMMON_SOURCE_DIR}/src/thread.h
		${COMMON_SOURCE_DIR}/src/protocol.h
		${COMMON_SOURCE_DIR}/src/event.h
		${COMMON_SOURCE_DIR}/src/socket_error.h
		${COMMON_SOURCE_DIR}/src/protocol_error.h
		${COMMON_SOURCE_DIR}/src/types.h
		${UIS_HEADERS}
		${UI_RESOURCES_RCC}
		)

target_link_libraries(client Qt5::Widgets Qt5::DBus)
target_link_libraries(client ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES} ${SDL2MIXER_LIBRARIES})
target_link_libraries(client ${COMMON_SOURCE_DIR}/libs/libyaml-cpp.a)
