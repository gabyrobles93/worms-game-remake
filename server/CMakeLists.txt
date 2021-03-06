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
include_directories(${PROJECT_SOURCE_DIR}/src/entities/weather)
include_directories(${PROJECT_SOURCE_DIR}/src/game)
include_directories(${PROJECT_SOURCE_DIR}/src/physics)
include_directories(${PROJECT_SOURCE_DIR}/src/entities/weapons)
include_directories(${PROJECT_SOURCE_DIR}/src/physics/weapons)



add_executable(worms-server
		${PROJECT_SOURCE_DIR}/src/main.cpp
		${PROJECT_SOURCE_DIR}/src/client.cpp
		${PROJECT_SOURCE_DIR}/src/client.h
		${PROJECT_SOURCE_DIR}/src/server_game.cpp
		${PROJECT_SOURCE_DIR}/src/server_game.h
		${PROJECT_SOURCE_DIR}/src/server.cpp
		${PROJECT_SOURCE_DIR}/src/server.h
		${PROJECT_SOURCE_DIR}/src/server_error.cpp
		${PROJECT_SOURCE_DIR}/src/server_error.h
		${PROJECT_SOURCE_DIR}/src/lobby_attendant.cpp
		${PROJECT_SOURCE_DIR}/src/lobby_attendant.h
		${PROJECT_SOURCE_DIR}/src/waiting_game.cpp
		${PROJECT_SOURCE_DIR}/src/waiting_game.h
		${PROJECT_SOURCE_DIR}/src/protected_waiting_games.cpp
		${PROJECT_SOURCE_DIR}/src/protected_waiting_games.h		
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
		${PROJECT_SOURCE_DIR}/src/entities/Worm.cpp
		${PROJECT_SOURCE_DIR}/src/entities/Worm.h
		${PROJECT_SOURCE_DIR}/src/entities/structures/Girder.cpp
		${PROJECT_SOURCE_DIR}/src/entities/structures/Girder.h
		${PROJECT_SOURCE_DIR}/src/entities/structures/Wall.cpp
		${PROJECT_SOURCE_DIR}/src/entities/structures/Wall.h
		${PROJECT_SOURCE_DIR}/src/game/World.cpp
		${PROJECT_SOURCE_DIR}/src/game/World.h
		${PROJECT_SOURCE_DIR}/src/game/WeaponManager.cpp
		${PROJECT_SOURCE_DIR}/src/game/WeaponManager.h
		${PROJECT_SOURCE_DIR}/src/physics/world/WorldPhysic.cpp
		${PROJECT_SOURCE_DIR}/src/physics/world/WorldPhysic.h
		${PROJECT_SOURCE_DIR}/src/snapshot_sender.cpp
		${PROJECT_SOURCE_DIR}/src/snapshot_sender.h
		${PROJECT_SOURCE_DIR}/src/snapshot.cpp
		${PROJECT_SOURCE_DIR}/src/snapshot.h
		${PROJECT_SOURCE_DIR}/src/entities/Water.cpp
		${PROJECT_SOURCE_DIR}/src/entities/Water.h
		${PROJECT_SOURCE_DIR}/src/physics/PhysicEntity.h
		${PROJECT_SOURCE_DIR}/src/physics/ContactListener.cpp
		${PROJECT_SOURCE_DIR}/src/physics/ContactListener.h
		${PROJECT_SOURCE_DIR}/src/physics/RayCastClosestCallBack.h
		${PROJECT_SOURCE_DIR}/src/physics/RayCastClosestCallBack.cpp
		${PROJECT_SOURCE_DIR}/src/entities/Entity.h
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
		${PROJECT_SOURCE_DIR}/src/entities/weapons/Teleportation.cpp
		${PROJECT_SOURCE_DIR}/src/entities/weapons/Teleportation.h
		${PROJECT_SOURCE_DIR}/src/entities/weapons/Grenade.cpp
		${PROJECT_SOURCE_DIR}/src/entities/weapons/Grenade.h
		${PROJECT_SOURCE_DIR}/src/entities/weapons/AirStrike.cpp
		${PROJECT_SOURCE_DIR}/src/entities/weapons/AirStrike.h
		${PROJECT_SOURCE_DIR}/src/entities/weapons/Bazooka.cpp
		${PROJECT_SOURCE_DIR}/src/entities/weapons/Bazooka.h
		${PROJECT_SOURCE_DIR}/src/entities/weapons/Mortar.cpp
		${PROJECT_SOURCE_DIR}/src/entities/weapons/Mortar.h
		${PROJECT_SOURCE_DIR}/src/entities/weapons/RedGrenade.cpp
		${PROJECT_SOURCE_DIR}/src/entities/weapons/RedGrenade.h
		${PROJECT_SOURCE_DIR}/src/Configuration.h
		${PROJECT_SOURCE_DIR}/src/Configuration.cpp
		${PROJECT_SOURCE_DIR}/src/entities/weapons/Missil.h
		${PROJECT_SOURCE_DIR}/src/entities/weapons/Missil.cpp
		${PROJECT_SOURCE_DIR}/src/entities/weather/Wind.cpp
		${PROJECT_SOURCE_DIR}/src/entities/weather/Wind.h
		${PROJECT_SOURCE_DIR}/src/entities/weapons/Fragment.h
		${PROJECT_SOURCE_DIR}/src/entities/weapons/Fragment.cpp

		)

target_link_libraries(worms-server ${COMMON_SOURCE_DIR}/libs/libyaml-cpp.a)
target_link_libraries(worms-server ${PROJECT_SOURCE_DIR}/libs/libBox2D.a)
