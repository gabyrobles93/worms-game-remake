cmake_minimum_required(VERSION 2.8)
project(Server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic -I.")
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(Worms
	src/Worms.cpp
	src/Worm.cpp
	src/Worm.h
	src/Girder.h
	src/Girder.cpp)

target_link_libraries(Worms ${PROJECT_SOURCE_DIR}/libs/libBox2D.a)

