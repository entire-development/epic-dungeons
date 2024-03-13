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
set(SFML_DIR "/opt/homebrew/Cellar/sfml/2.6.1")

find_package(SFML 2.6.1 COMPONENTS graphics audio REQUIRED)
target_link_libraries(EpicDungeons PRIVATE sfml-graphics sfml-audio)

# include fonts
file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ${CMAKE_BINARY_DIR})
