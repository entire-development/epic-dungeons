cmake_minimum_required(VERSION 3.17)
project(EpicDungeons)

set(CMAKE_CXX_STANDARD 20)

add_executable(EpicDungeons main.cpp)
file(GLOB_RECURSE SOURCES src/*.cpp)

target_include_directories(EpicDungeons PUBLIC src)
target_sources(EpicDungeons PUBLIC ${SOURCES})