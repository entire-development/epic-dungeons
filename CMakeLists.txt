cmake_minimum_required(VERSION 3.18)
project(EpicDungeons)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(EpicDungeons main.cpp ${SOURCES})
target_include_directories(EpicDungeons PRIVATE src)

# add spdlog
find_package(spdlog 1.8.1 REQUIRED)
target_link_libraries(EpicDungeons PRIVATE spdlog::spdlog)

# add chrono
find_package(Threads REQUIRED)
target_link_libraries(EpicDungeons PRIVATE Threads::Threads)

# add sfml
# set(SFML_DIR "/opt/homebrew/Cellar/sfml/2.5.1")
find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)
target_link_libraries(EpicDungeons PRIVATE sfml-graphics sfml-audio)

#clean res folder
file(REMOVE_RECURSE ${CMAKE_BINARY_DIR}/res)

# include res folder
file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ${CMAKE_BINARY_DIR})

# unpack gif into frames
file(GLOB_RECURSE GIFS ${CMAKE_SOURCE_DIR}/res/*.gif)
foreach(GIF ${GIFS})
    message(STATUS "GIF: ${GIF}")
    file(RELATIVE_PATH RELATIVE_GIF ${CMAKE_SOURCE_DIR}/res ${GIF})
    string(REPLACE ".gif" "" FRAME_DIR ${RELATIVE_GIF})
    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/res/${FRAME_DIR})
    execute_process(COMMAND convert -coalesce ${GIF} ${CMAKE_BINARY_DIR}/res/${FRAME_DIR}/frame.png)
endforeach()

# add define for debug mode
if (CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(EpicDungeons PRIVATE DEBUG)
endif()

# add define for release mode
if (CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_definitions(EpicDungeons PRIVATE RELEASE)
endif()

# add define for profiling mode
if (CMAKE_BUILD_TYPE MATCHES MinSizeRel)
    target_compile_definitions(EpicDungeons PRIVATE PROFILING)
endif()