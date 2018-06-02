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
include_directories(${PROJECT_SOURCE_DIR}/src/physics)
include_directories(${PROJECT_SOURCE_DIR}/src/entities/weapons)
include_directories(${PROJECT_SOURCE_DIR}/src/physics/weapons)



add_executable(	server
		${PROJECT_SOURCE_DIR}/src/main.cpp
		${PROJECT_SOURCE_DIR}/src/team.cpp
		${PROJECT_SOURCE_DIR}/src/team.h
		${PROJECT_SOURCE_DIR}/src/event_receiver.cpp
		${PROJECT_SOURCE_DIR}/src/event_receiver.h
		${PROJECT_SOURCE_DIR}/src/match.cpp
		${PROJECT_SOURCE_DIR}/src/match.h
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
		${PROJECT_SOURCE_DIR}/src/snapshot_sender.cpp
		${PROJECT_SOURCE_DIR}/src/snapshot_sender.h
		${PROJECT_SOURCE_DIR}/src/physics/world/WaterPhysic.cpp
		${PROJECT_SOURCE_DIR}/src/physics/world/WaterPhysic.h
		${PROJECT_SOURCE_DIR}/src/entities/Water.cpp
		${PROJECT_SOURCE_DIR}/src/entities/Water.h
		${PROJECT_SOURCE_DIR}/src/physics/PhysicEntity.h
		${PROJECT_SOURCE_DIR}/src/physics/ContactListener.cpp
		${PROJECT_SOURCE_DIR}/src/physics/ContactListener.h
		${PROJECT_SOURCE_DIR}/src/physics/RayCastClosestCallBack.h
		${PROJECT_SOURCE_DIR}/src/physics/RayCastClosestCallBack.cpp
		${PROJECT_SOURCE_DIR}/src/entities/Entity.h
		${PROJECT_SOURCE_DIR}/src/physics/weapons/DynamitePhysic.cpp
		${PROJECT_SOURCE_DIR}/src/physics/weapons/DynamitePhysic.h
		${PROJECT_SOURCE_DIR}/src/entities/weapons/Dynamite.cpp
		${PROJECT_SOURCE_DIR}/src/entities/weapons/Dynamite.h
		${PROJECT_SOURCE_DIR}/src/physics/ExplosionManager.cpp
		${PROJECT_SOURCE_DIR}/src/physics/ExplosionManager.h
		${PROJECT_SOURCE_DIR}/src/physics/QueryCallback.cpp
		${PROJECT_SOURCE_DIR}/src/physics/QueryCallback.h
		${PROJECT_SOURCE_DIR}/src/entities/weapons/Weapon.cpp
		${PROJECT_SOURCE_DIR}/src/entities/weapons/Weapon.h
		${PROJECT_SOURCE_DIR}/src/entities/weapons/Bat.cpp
		${PROJECT_SOURCE_DIR}/src/entities/weapons/Bat.h
		${PROJECT_SOURCE_DIR}/src/physics/weapons/BatPhysic.cpp
		${PROJECT_SOURCE_DIR}/src/physics/weapons/BatPhysic.h
		${PROJECT_SOURCE_DIR}/src/entities/weapons/Teleportation.cpp
		${PROJECT_SOURCE_DIR}/src/entities/weapons/Teleportation.h

		)

target_link_libraries(server ${COMMON_SOURCE_DIR}/libs/libyaml-cpp.a)
target_link_libraries(server ${PROJECT_SOURCE_DIR}/libs/libBox2D.a)
