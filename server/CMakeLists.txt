cmake_minimum_required(VERSION 2.8)
project(Server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC -Wall -Wextra -pedantic -pthread -I.")
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
include_directories(${PROJECT_SOURCE_DIR}/src/physics/world)
include_directories(${PROJECT_SOURCE_DIR}/src/entities/structures)
include_directories(${PROJECT_SOURCE_DIR}/src/entities)
include_directories(${PROJECT_SOURCE_DIR}/src/game)


add_executable(	server
		${PROJECT_SOURCE_DIR}/src/main.cpp 
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
		${PROJECT_SOURCE_DIR}/src/physics/worm/WormPhysic.cpp
		${PROJECT_SOURCE_DIR}/src/physics/worm/WormPhysic.h
		${PROJECT_SOURCE_DIR}/src/entities/Worm.cpp
		${PROJECT_SOURCE_DIR}/src/entities/Worm.h
		${PROJECT_SOURCE_DIR}/src/physics/structures/GirderPhysic.cpp
		${PROJECT_SOURCE_DIR}/src/physics/structures/GirderPhysic.h
		${PROJECT_SOURCE_DIR}/src/entities/structures/Girder.cpp
		${PROJECT_SOURCE_DIR}/src/entities/structures/Girder.h
		${PROJECT_SOURCE_DIR}/src/game/World.cpp
		${PROJECT_SOURCE_DIR}/src/game/World.h
		${PROJECT_SOURCE_DIR}/src/physics/world/WorldPhysic.cpp
		${PROJECT_SOURCE_DIR}/src/physics/world/WorldPhysic.h
		${PROJECT_SOURCE_DIR}/src/client_handler.cpp
		${PROJECT_SOURCE_DIR}/src/client_handler.h
		${PROJECT_SOURCE_DIR}/src/SnapshotPusher.cpp
		${PROJECT_SOURCE_DIR}/src/SnapshotPusher.h
		${PROJECT_SOURCE_DIR}/src/SnapshotSender.cpp
		${PROJECT_SOURCE_DIR}/src/SnapshotSender.h
		)

target_link_libraries(server ${COMMON_SOURCE_DIR}/libs/libyaml-cpp.a)
target_link_libraries(server ${PROJECT_SOURCE_DIR}/libs/libBox2D.a)
