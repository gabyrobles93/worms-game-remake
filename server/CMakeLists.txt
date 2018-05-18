cmake_minimum_required(VERSION 2.8)
project(Server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -Wextra -pedantic -pthread -I.")
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(COMMON_SOURCE_DIR ${PROJECT_SOURCE_DIR}/../common)

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

file (GLOB PHYSIC_SRC ${PROJECT_SOURCE_DIR}/src/physics/structures
	"*.cpp"
	"*.h"
)

add_executable(	server
		${PROJECT_SOURCE_DIR}/src/main.cpp 
		${PROJECT_SOURCE_DIR}/src/client.cpp
		${PROJECT_SOURCE_DIR}/src/server.cpp
		${PROJECT_SOURCE_DIR}/src/server_error.cpp
		${PROJECT_SOURCE_DIR}/src/server_acceptor.cpp
		${PROJECT_SOURCE_DIR}/src/server_lobby_feeder.cpp
		${PROJECT_SOURCE_DIR}/src/server_protected_clients.cpp
		${COMMON_SOURCE_DIR}/src/socket.cpp
		${COMMON_SOURCE_DIR}/src/socket_error.cpp
		${COMMON_SOURCE_DIR}/src/thread.cpp
		${COMMON_SOURCE_DIR}/src/protocol.cpp
		${COMMON_SOURCE_DIR}/src/protocol_error.cpp
		${PROJECT_SOURCE_DIR}/src/client.h
		${PROJECT_SOURCE_DIR}/src/server.h
		${PROJECT_SOURCE_DIR}/src/server_error.h
		${PROJECT_SOURCE_DIR}/src/server_acceptor.h
		${PROJECT_SOURCE_DIR}/src/server_lobby_feeder.h
		${PROJECT_SOURCE_DIR}/src/server_protected_clients.h
		${COMMON_SOURCE_DIR}/src/socket.h
		${COMMON_SOURCE_DIR}/src/socket_error.h
		${COMMON_SOURCE_DIR}/src/thread.h
		${COMMON_SOURCE_DIR}/src/protocol.h
		${COMMON_SOURCE_DIR}/src/protocol_error.h
		src/physics/worm/WormPhysic.cpp
		src/physics/worm/WormPhysic.h
		src/server_acceptor.h
		src/entities/Worm.cpp
		src/entities/Worm.h
		src/entities
		src/physics/structures/GirderPhysic.cpp
		src/physics/structures/GirderPhysic.h
		src/entities/structures/Girder.cpp
		src/entities/structures/Girder.h)

target_link_libraries(server ${COMMON_SOURCE_DIR}/libs/libyaml-cpp.a)
target_link_libraries(server ${PROJECT_SOURCE_DIR}/libs/libBox2D.a)
