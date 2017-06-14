# libs
find_package(Boost COMPONENTS system thread serialization REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

find_library(FRUIT_LIBRARY NAMES fruit)

set(LIBRARIES ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${FRUIT_LIBRARY})

# main
set(SOURCE_FILES
        src/interfaces/ITemperatureWorld.h
        src/scalars/Coord.h
        src/scalars/Temperature.h
        src/interfaces/ITemperatureWorldUpdater.h
        src/utils/MathUtils.h
        src/utils/TimeUtils.h
        src/utils/TemperatureWorldUtils.h
        src/scalars/Size.h
        src/interfaces/ITimer.h
        src/interfaces/IBlockingTimer.h
        src/interfaces/IBoundTemperatureWorld.h
        src/implementation/SynchronizedVectorBoundTemperatureWorld.cpp
        src/implementation/SynchronizedVectorBoundTemperatureWorld.h
        src/implementation/SynchronizedBlockingTimer.cpp
        src/implementation/SynchronizedBlockingTimer.h
        src/implementation/AverageShareTemperatureWorldUpdater.cpp
        src/implementation/AverageShareTemperatureWorldUpdater.h
        src/utils/FileUtils.h
        src/module.h
        src/implementation/annotations/TemperatureWorldUpdaterAnnotations.h
        src/implementation/annotations/BoundTemperatureWorldAnnotations.h
        src/module.cpp
        src/implementation/annotations/BlockingTimerAnnotations.h
        src/implementation/BasicTimer.cpp
        src/implementation/BasicTimer.h
        src/interfaces/IChunkedTemperatureWorld.h
        src/implementation/SynchronizedListGenericChunkedTemperatureWorld.inc.h
        src/implementation/SynchronizedListGenericChunkedTemperatureWorld.h
        src/implementation/ScalableSynchronizedListChunkedTemperatureWorld.cpp
        src/implementation/ScalableSynchronizedListChunkedTemperatureWorld.h
        src/scalars/Parallelepiped.h
        src/scalars/ScaledParallelepiped.h src/scalars/GenericScalar.h)

# unittest
add_executable(world-with-temperature-unittest test/unittest.cpp test/lib/catch.hpp ${SOURCE_FILES})
target_link_libraries(world-with-temperature-unittest ${LIBRARIES})

# demo
add_executable(world-with-temperature-demo test/demo.cpp test/lib/crow_all.h ${SOURCE_FILES})
target_link_libraries(world-with-temperature-demo ${LIBRARIES})

# performance
add_executable(world-with-temperature-performance test/performance.cpp ${SOURCE_FILES})
target_link_libraries(world-with-temperature-performance ${LIBRARIES})
