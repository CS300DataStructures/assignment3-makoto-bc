cmake_minimum_required(VERSION 3.17)
project(assignment-3)

set(CMAKE_CXX_STANDARD 17)

set(
    SOURCES
    Packet.h
    Buffer.cpp
    Response.h
)

#add_subdirectory(tests)

add_executable(assignment-3 ass3.cpp ${SOURCES})

add_library(libassignment-3 STATIC ${SOURCES})