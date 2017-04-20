set(SOURCE_FILES src/TemperatureWorld.cpp src/TemperatureWorld.h src/Coord.h src/Temperature.h src/TemperatureWorldUpdater.cpp src/TemperatureWorldUpdater.h src/MathUtils.h)
add_executable(world-with-temperature src/main.cpp ${SOURCE_FILES})

add_executable(world-with-temperature-unittest test/test.cpp test/catch.hpp ${SOURCE_FILES})

find_package(Boost 1.52 COMPONENTS system thread REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
add_executable(world-with-temperature-demo test/demo.cpp test/crow_all.h ${SOURCE_FILES})
target_link_libraries(world-with-temperature-demo ${Boost_LIBRARIES})
target_link_libraries(world-with-temperature-demo ${CMAKE_THREAD_LIBS_INIT})
