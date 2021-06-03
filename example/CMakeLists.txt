set(ProjectName expirable_example)
project(${ProjectName})

cmake_minimum_required(VERSION 2.8.8)

set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type(Debug, Release)" FORCE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

option(EXPIRABLE_ENABLE_THREADS "enabling thread safe support for expirable values" ON)

if (EXPIRABLE_ENABLE_THREADS)
    add_definitions(-DEXPIRABLE_ENABLE_THREADS)
    #set(EXTERNAL_LINK_LIBRARIES ${EXTERNAL_LINK_LIBRARIES} pthread)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)

add_executable(${ProjectName} main.cpp)
