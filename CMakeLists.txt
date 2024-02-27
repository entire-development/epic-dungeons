cmake_minimum_required(VERSION 3.17)
project(EpicDungeons)

add_compile_options(-I c:/SFML/include/)

set(CMAKE_CXX_STANDARD 20)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)

FetchContent_MakeAvailable(SFML)

# IMPORTANT! Change executable back on main.cpp later. I need view/demo.cpp to test some sfml features.
add_executable(EpicDungeons src/view/demo.cpp)
file(GLOB_RECURSE SOURCES src/*.cpp)

target_link_libraries(EpicDungeons PRIVATE sfml-graphics)
#target_compile_features(EpicDungeons PRIVATE cxx_std_20)

target_include_directories(EpicDungeons PUBLIC src)
target_sources(EpicDungeons PUBLIC ${SOURCES})

install(TARGETS EpicDungeons)
