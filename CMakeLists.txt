cmake_minimum_required(VERSION 3.17)
project(EpicDungeons)

# I don't understand why, but this line is important for sfml library. It won't build without it.
add_compile_options(-I c:/SFML/include/)

set(CMAKE_CXX_STANDARD 20)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# fetch the graphic library from github! It locates in _deps folder. donwload sfml to your system (like with
# brew install sfml) if project builds too slow on your machine.
include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# demo.cpp IMPORTANT! Change executable back on main.cpp later. I need view/demo.cpp to test some sfml features.
# game-config.cpp NOT SO IMPORTANT! game-config.h is a configuration file that stores all potentially
# non-static info like framerate, window resolution or dungeon rooms count.
add_executable(EpicDungeons src/view/demo.cpp src/game-config.h)
file(GLOB_RECURSE SOURCES src/*.cpp)

target_link_libraries(EpicDungeons PRIVATE sfml-graphics)
# target_compile_features(EpicDungeons PRIVATE cxx_std_20)

target_include_directories(EpicDungeons PUBLIC src)
target_sources(EpicDungeons PUBLIC ${SOURCES})

install(TARGETS EpicDungeons)
