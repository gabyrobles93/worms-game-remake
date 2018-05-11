cmake_minimum_required(VERSION 2.8)
project(Client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic -I.")
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(SDL2 REQUIRED)
find_package(Qt5 COMPONENTS Widgets DBus REQUIRED)

INCLUDE(FindPkgConfig) 
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer>=2.0.0)


message("Directorio actual: ${PROJECT_SOURCE_DIR}")
include_directories(${PROJECT_SOURCE_DIR})

qt5_wrap_ui(UIS_HEADERS
        client_connector.ui
)

add_executable(	client
		main.cpp 
		client_connector.cpp
		client_connector.h
		client_connector_resources.qrc 
		${UIS_HEADERS}
		)

target_link_libraries(client Qt5::Widgets Qt5::DBus)
target_link_libraries(client ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES} ${SDL2MIXER_LIBRARIES})

