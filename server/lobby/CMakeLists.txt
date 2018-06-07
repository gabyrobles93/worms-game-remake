cmake_minimum_required(VERSION 2.8)
project(Server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC -Wall -Wextra -pedantic -pthread -I.")
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(COMMON_SOURCE_DIR ${PROJECT_SOURCE_DIR}/../../common)

find_package(Threads)


include_directories(${PROJECT_SOURCE_DIR})
include_directories(${COMMON_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${COMMON_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${COMMON_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/Box2D)
include_directories(${COMMON_SOURCE_DIR}/include/yaml-cpp)
include_directories(${PROJECT_SOURCE_DIR}/src/physics/worm)
include_directories(${PROJECT_SOURCE_DIR}/src/physics/structures)
include_directories(${PROJECT_SOURCE_DIR}/src/physics/world)
include_directories(${PROJECT_SOURCE_DIR}/src/entities/structures)
include_directories(${PROJECT_SOURCE_DIR}/src/entities)
include_directories(${PROJECT_SOURCE_DIR}/src/game)
include_directories(${PROJECT_SOURCE_DIR}/src/physics)
include_directories(${PROJECT_SOURCE_DIR}/src/entities/weapons)
include_directories(${PROJECT_SOURCE_DIR}/src/physics/weapons)



add_executable(	server
		${PROJECT_SOURCE_DIR}/src/main.cpp
		${PROJECT_SOURCE_DIR}/src/client.cpp
		${PROJECT_SOURCE_DIR}/src/server.cpp
		${PROJECT_SOURCE_DIR}/src/server_error.cpp
		${PROJECT_SOURCE_DIR}/src/client.h
		${PROJECT_SOURCE_DIR}/src/server.h
		${PROJECT_SOURCE_DIR}/src/server_error.h
		${PROJECT_SOURCE_DIR}/src/protected_matchs_status.cpp
		${PROJECT_SOURCE_DIR}/src/protected_matchs_status.h
		${PROJECT_SOURCE_DIR}/src/lobby_attendant.cpp
		${PROJECT_SOURCE_DIR}/src/lobby_attendant.h
		${COMMON_SOURCE_DIR}/src/socket.cpp
		${COMMON_SOURCE_DIR}/src/socket_error.cpp
		${COMMON_SOURCE_DIR}/src/thread.cpp
		${COMMON_SOURCE_DIR}/src/protocol.cpp
		${COMMON_SOURCE_DIR}/src/protocol_error.cpp
		${COMMON_SOURCE_DIR}/src/event.cpp
		${COMMON_SOURCE_DIR}/src/socket.h
		${COMMON_SOURCE_DIR}/src/socket_error.h
		${COMMON_SOURCE_DIR}/src/thread.h
		${COMMON_SOURCE_DIR}/src/protocol.h
		${COMMON_SOURCE_DIR}/src/event.h
		${COMMON_SOURCE_DIR}/src/protocol_error.h
		${COMMON_SOURCE_DIR}/src/types.h
		${COMMON_SOURCE_DIR}/src/blocking_queue.h
		)

target_link_libraries(server ${COMMON_SOURCE_DIR}/libs/libyaml-cpp.a)