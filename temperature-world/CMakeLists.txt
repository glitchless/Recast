# libs
## boost
find_package(Boost COMPONENTS system thread serialization REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

## result
set(LIBRARIES ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})


# source
file(GLOB_RECURSE SOURCE_FILES
        "src/*.h"
        "src/*.hpp"
        "src/*.c"
        "src/*.cpp")

include_directories(src/headers/)


# executables
## main
add_library(temperature-world ${SOURCE_FILES})
target_link_libraries(temperature-world ${LIBRARIES})

## unittest
add_executable(temperature-world-unittest test/unittest.cpp test/lib/catch.hpp ${SOURCE_FILES})
target_link_libraries(temperature-world-unittest ${LIBRARIES})

## demo
add_executable(temperature-world-demo test/demo.cpp test/lib/crow_all.h ${SOURCE_FILES})
target_link_libraries(temperature-world-demo ${LIBRARIES})

## performance
add_executable(temperature-world-performance test/performance.cpp ${SOURCE_FILES})
target_link_libraries(temperature-world-performance ${LIBRARIES})
