cmake_minimum_required(VERSION 3.17)
project(assignment-3)

set(CMAKE_CXX_STANDARD 17)

set(
    SOURCES
    Packet.h
    Buffer.cpp
    Response.h
    time.h)

add_subdirectory(tests)

add_executable(assignment-3 ass3.cpp ${SOURCES})
target_compile_options(assignment-3 PRIVATE -Wall -Wextra -pedantic)

add_library(libassignment-3 STATIC ${SOURCES})
target_compile_options(libassignment-3 PRIVATE -Wall -Wextra -pedantic)