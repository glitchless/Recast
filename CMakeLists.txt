cmake_minimum_required(VERSION 3.2)
project(Recast)

set(CMAKE_C_STANDARD 99)

file(GLOB_RECURSE SOURCE_FILES
        "src/*.h"
        "src/*.c"
        "src/*.cpp")

add_executable(Ivan2Project ${SOURCE_FILES})
