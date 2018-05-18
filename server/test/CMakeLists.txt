cmake_minimum_required(VERSION 2.8)
project(ServerTest)

set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/../src)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/../include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
	${SOURCE_DIR}/entities/Worm.cpp
	${SOURCE_DIR}/entities/Worm.h
	${SOURCE_DIR}/physics/worm/WormPhysic.cpp
	${SOURCE_DIR}/physics/worm/WormPhysic.h
	${SOURCE_DIR}/entities/structures/Girder.cpp
	${SOURCE_DIR}/entities/structures/Girder.h
	${SOURCE_DIR}/physics/world/WorldPhysic.cpp
	${SOURCE_DIR}/physics/world/WorldPhysic.h
	${SOURCE_DIR}/physics/structures/GirderPhysic.cpp
	${SOURCE_DIR}/physics/structures/GirderPhysic.h
	${SOURCE_DIR}/game/World.cpp
	${SOURCE_DIR}/game/World.h
)

include_directories(${SOURCE_DIR}/entities
	${SOURCE_DIR}/physics/world
	${SOURCE_DIR}/physics/structures
	${SOURCE_DIR}/physics/worm
	${SOURCE_DIR}/entities/structures
	${SOURCE_DIR}/game	
	${SOURCE_DIR}/../../common/include/yaml-cpp
	${SOURCE_DIR}/../../common/include
	${INCLUDE_DIR})

add_executable(runner
	runner.cpp
	${SOURCE_FILES}
)

target_link_libraries(runner ${SOURCE_DIR}/../libs/libBox2D.a)
target_link_libraries(runner ${SOURCE_DIR}/../../common/libs/libyaml-cpp.a)
