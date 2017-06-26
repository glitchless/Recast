cmake_minimum_required(VERSION 3.2)
project(Recast-server)

set(CMAKE_CXX_STANDARD 14)


# libs
## vendored
add_subdirectory(libs)
include_directories(libs)

## boost
add_definitions(-DBOOST_LOG_DYN_LINK)
find_package(Boost 1.55 COMPONENTS system thread log program_options filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

## result
set(LIBRARIES ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} sqlite3)


# main source
include_directories(src/headers/)

file(GLOB_RECURSE SOURCE_FILES
        "src/*.h"
        "src/*.hpp"
        "src/*.c"
        "src/*.cpp")


# executable
add_executable(Recast-server ${SOURCE_FILES})
target_link_libraries(Recast-server ${LIBRARIES})


# tests
## unittest
add_executable(temperature-world-unittest test/temperature-world/unittest.cpp test/temperature-world/lib/catch.hpp ${SOURCE_FILES})
target_link_libraries(temperature-world-unittest ${LIBRARIES})

## demo
add_executable(temperature-world-demo test/temperature-world/demo.cpp test/temperature-world/lib/crow_all.h ${SOURCE_FILES})
target_link_libraries(temperature-world-demo ${LIBRARIES})

## performance
add_executable(temperature-world-performance test/temperature-world/performance.cpp ${SOURCE_FILES})
target_link_libraries(temperature-world-performance ${LIBRARIES})
