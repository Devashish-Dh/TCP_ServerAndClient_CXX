CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

PROJECT(tcp_client
        VERSION 1.0
        DESCRIPTION "A bare bones TCP client on linux." 
        LANGUAGES CXX       
)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include) # for header files if any
SET(SOURCES ${CMAKE_SOURCE_DIR}/src/)# source files of the project







ADD_EXECUTABLE(tcp_client ${SOURCES}/main.cpp)









