cmake_minimum_required(VERSION 3.16.3)

project(console-renderer)

set(CMAKE_CXX_STANDARD 11)

include_directories(includes)

add_executable(console-renderer
                src/main.cpp)       