cmake_minimum_required(VERSION 3.2)
project(Recast-server)

# options
option(PROFILE "Enables google performance tools" OFF)
if(PROFILE)
    message("Profiling is enabled")
endif(PROFILE)

# settings
set(CMAKE_CXX_STANDARD 14)
if(PROFILE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")
endif(PROFILE)


# libs
set(LIBRARIES "")

## vendored
add_subdirectory(libs)
include_directories(libs)

## boost
add_definitions(-DBOOST_LOG_DYN_LINK)
find_package(Boost 1.55 COMPONENTS system thread log program_options filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
list(APPEND LIBRARIES ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

## sqlite3
list(APPEND LIBRARIES sqlite3)

## gprof
if(PROFILE)
    list(APPEND LIBRARIES profiler)
endif(PROFILE)


# main source
include_directories(src/headers/)

file(GLOB_RECURSE SOURCE_FILES
        "src/*.h"
        "src/*.hpp"
        "src/*.c"
        "src/*.cpp")

set(MAIN_CPP ${CMAKE_CURRENT_SOURCE_DIR}/src/Main.cpp)
list(REMOVE_ITEM SOURCE_FILES ${MAIN_CPP})


# executable
add_executable(Recast-server ${MAIN_CPP} ${SOURCE_FILES})
target_link_libraries(Recast-server ${LIBRARIES})


# tests
## temperature-world
### unittest
add_executable(temperature-world-unittest test/temperature-world/unittest.cpp test/temperature-world/lib/catch.hpp ${SOURCE_FILES})
target_link_libraries(temperature-world-unittest ${LIBRARIES})

### demo
add_executable(temperature-world-demo test/temperature-world/demo.cpp test/temperature-world/lib/crow_all.h ${SOURCE_FILES})
target_link_libraries(temperature-world-demo ${LIBRARIES})

### demo-multichunk
add_executable(temperature-world-demo-multichunk test/temperature-world/demo-multichunk.cpp test/temperature-world/lib/crow_all.h ${SOURCE_FILES})
target_link_libraries(temperature-world-demo-multichunk ${LIBRARIES})

### performance
add_executable(temperature-world-performance test/temperature-world/performance.cpp ${SOURCE_FILES})
target_link_libraries(temperature-world-performance ${LIBRARIES})

### performance-multichunk
add_executable(temperature-world-performance-multichunk test/temperature-world/performance-multichunk.cpp ${SOURCE_FILES})
target_link_libraries(temperature-world-performance-multichunk ${LIBRARIES})
