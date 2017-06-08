cmake_minimum_required(VERSION 3.2)
project(Recast-server)

set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE SOURCE_FILES
        "src/*.h"
        "src/*.c"
        "src/*.cpp")

include_directories(src/headers/)

set(Boost_USE_STATIC_LIBS   ON)
set(Boost_USE_MULTITHREADED ON)

add_definitions(-DBOOST_LOG_DYN_LINK)

find_package(Boost 1.55 COMPONENTS  system
                                    thread
                                    log
                                    log_setup
                                    program_options
                                    filesystem
             REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_executable(Recast-server ${SOURCE_FILES})

target_link_libraries(Recast-server ${Boost_LIBRARIES})
target_link_libraries(Recast-server ${CMAKE_THREAD_LIBS_INIT})
