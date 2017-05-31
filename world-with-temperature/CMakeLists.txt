# libs
find_package(Boost COMPONENTS system thread serialization REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

set(LIBRARIES ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

# main
set(SOURCE_FILES src/ITemperatureWorld.h src/scalars/Coord.h src/scalars/Temperature.h src/ITemperatureWorldUpdater.h src/utils/MathUtils.h src/utils/TimeUtils.h src/utils/TemperatureWorldUtils.h src/scalars/Size.h src/ITimer.h src/IBlockingTimer.h src/IBoundTemperatureWorld.h src/SynchronizedVectorTemperatureWorld.cpp src/SynchronizedVectorTemperatureWorld.h src/SynchronizedBlockingTimer.cpp src/SynchronizedBlockingTimer.h src/AverageShareTemperatureWorldUpdater.cpp src/AverageShareTemperatureWorldUpdater.h)

# unittest
add_executable(world-with-temperature-unittest test/unittest.cpp test/lib/catch.hpp ${SOURCE_FILES})
target_link_libraries(world-with-temperature-unittest ${LIBRARIES})

# demo
add_executable(world-with-temperature-demo test/demo.cpp test/lib/crow_all.h ${SOURCE_FILES})
target_link_libraries(world-with-temperature-demo ${LIBRARIES})

# highload
add_executable(world-with-temperature-performance test/performance.cpp ${SOURCE_FILES})
target_link_libraries(world-with-temperature-performance ${LIBRARIES})
