cmake_minimum_required(VERSION 2.8)
project(Client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic -pthread -I.")
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(COMMON_SOURCE_DIR ${PROJECT_SOURCE_DIR}/../common)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/yaml-cpp)

add_executable(	client
		${PROJECT_SOURCE_DIR}/main.cpp 
		${PROJECT_SOURCE_DIR}/socket.cpp
		${PROJECT_SOURCE_DIR}/socket_error.cpp
		${PROJECT_SOURCE_DIR}/socket.h
		${PROJECT_SOURCE_DIR}/socket_error.h
		)

target_link_libraries(client ${PROJECT_SOURCE_DIR}/libyaml-cpp.a)
