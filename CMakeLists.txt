cmake_minimum_required(VERSION 3.17)
project(EpicDungeons)

set(CMAKE_CXX_STANDARD 20)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(EpicDungeons main.cpp
        src/view/demo.cpp)
file(GLOB_RECURSE SOURCES src/*.cpp)

target_link_libraries(EpicDungeons PRIVATE sfml-graphics)
target_compile_features(EpicDungeons PRIVATE cxx_std_20)

target_include_directories(EpicDungeons PUBLIC src)
target_sources(EpicDungeons PUBLIC ${SOURCES})

install(TARGETS CMakeSFMLProject)