cmake_minimum_required(VERSION 3.2)
project(Recast-server)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(libs)
include_directories(libs)

file(GLOB_RECURSE SOURCE_FILES
        "src/*.h"
        "src/*.hpp"
        "src/*.c"
        "src/*.cpp")

include_directories(src/headers/)

set(Boost_NO_SYSTEM_PATHS TRUE)
if (Boost_NO_SYSTEM_PATHS)
    set(BOOST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/libs/boost")
    set(BOOST_INCLUDE_DIRS "${BOOST_ROOT}/include")
    set(BOOST_LIBRARY_DIRS "${BOOST_ROOT}/lib")
endif (Boost_NO_SYSTEM_PATHS)
add_definitions(-DBOOST_LOG_DYN_LINK)
find_package(Boost 1.61 COMPONENTS system thread log program_options filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_executable(recast-server ${SOURCE_FILES})

target_link_libraries(recast-server ${Boost_LIBRARIES})
target_link_libraries(recast-server ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(recast-server sqlite3)