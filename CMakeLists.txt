cmake_minimum_required(VERSION 3.15)
project(EpicDungeons)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(EpicDungeons main.cpp ${SOURCES})
target_include_directories(EpicDungeons PRIVATE src)
