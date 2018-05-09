cmake_minimum_required(VERSION 2.8)
project(Client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic -I.")

find_package(SDL2 REQUIRED)

#include_directories(${SDL2_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(client HelloWorld.cpp)

target_link_libraries(client SDL2)
target_link_libraries(client ${PROJECT_SOURCE_DIR}/libs/libBox2D.a)

