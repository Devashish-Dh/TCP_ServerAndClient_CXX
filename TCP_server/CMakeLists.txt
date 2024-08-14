CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

PROJECT(tcp_server
        VERSION 1.0
        DESCRIPTION "A bare bones TCP server on linux." 
        LANGUAGES CXX       
)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)

SET(SOURCES ${CMAKE_SOURCE_DIR}/src/)







ADD_EXECUTABLE(tcp_server ${SOURCES}/main.cpp)









