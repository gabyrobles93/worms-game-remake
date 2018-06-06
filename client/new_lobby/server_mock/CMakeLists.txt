cmake_minimum_required(VERSION 2.8)
project(server_mock)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -Wextra -pedantic -pthread -I.")
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(COMMON_SOURCE_DIR ${PROJECT_SOURCE_DIR}/../../../common)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${COMMON_SOURCE_DIR})
include_directories(${COMMON_SOURCE_DIR}/src)
include_directories(${COMMON_SOURCE_DIR}/include)
include_directories(${COMMON_SOURCE_DIR}/include/yaml-cpp)

add_executable(	server_mock
		${PROJECT_SOURCE_DIR}/server_mock_main.cpp
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
		)
target_link_libraries(server_mock ${COMMON_SOURCE_DIR}/libs/libyaml-cpp.a)
