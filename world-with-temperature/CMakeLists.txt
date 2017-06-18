# libs
find_package(Boost COMPONENTS system thread serialization REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

find_library(FRUIT_LIBRARY NAMES fruit)

set(LIBRARIES ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${FRUIT_LIBRARY})

# main
set(SOURCE_FILES
        src/interfaces/ITemperatureWorld.h
        src/types/Coord.h
        src/types/Temperature.h
        src/interfaces/IUpdater.h
        src/utils/MathUtils.h
        src/utils/TimeUtils.h
        src/utils/TemperatureWorldUtils.h
        src/types/Size.h
        src/interfaces/ITimer.h
        src/interfaces/ITimerBlockable.h
        src/interfaces/ITemperatureWorldBoundable.h
        src/implementation/BoundTemperatureWorldOnSynchronizedVector.cpp
        src/implementation/BoundTemperatureWorldOnSynchronizedVector.h
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
        src/interfaces/ITemperatureWorldChunkable.h
        src/implementation/GenericChunkedTemperatureWorldOnSynchronizedList.inc.h
        src/implementation/GenericChunkedTemperatureWorldOnSynchronizedList.h
        src/implementation/ScalingOnDemandChunkedTemperatureWorldOnSynchronizedList.inc.h
        src/implementation/ScalingOnDemandGeneratableChunkedTemperatureWorldOnSynchronizedList.h
        src/types/Parallelepiped.h
        src/types/IntScaleParallelepiped.h
        src/types/GenericScalar.h
        src/implementation/BoundTemperatureWorldOnSynchronizedVector.inc.h
        src/implementation/OnDemandGeneratableGenericChunkedTemperatureWorldOnSynchronizedList.inc.h
        src/implementation/OnDemandGeneratableGenericChunkedTemperatureWorldOnSynchronizedList.h
        src/implementation/ScalableBoundTemperatureWorldOnSynchronizedVector.cpp
        src/implementation/ScalableBoundTemperatureWorldOnSynchronizedVector.h
        src/interfaces/ITemperatureWorldScalable.h
        src/types/IntScale.h
        src/interfaces/ITemperatureWorldChunkableMutable.h
        src/interfaces/ITemperatureWorldPointPrioritizable.h
        src/types/Point.h
        src/implementation/annotations/OnDemandGeneratableChunkedTemperatureWorldAnnotations.h
        src/implementation/annotations/ScaledTemperatureWorldAnnotations.h
        src/fixes/fruit.h
        src/implementation/ThreadedChunkedTemperatureWorldUpdater.inc.h
        src/implementation/ThreadedChunkedTemperatureWorldUpdater.h
        src/interfaces/ITemperatureWorldChunkableOnDemandGeneratableObservable.h
        src/implementation/annotations/ThreadedChunkedTemperatureWorldUpdaterAnnotations.h)

# unittest
add_executable(world-with-temperature-unittest test/unittest.cpp test/lib/catch.hpp ${SOURCE_FILES})
target_link_libraries(world-with-temperature-unittest ${LIBRARIES})

# demo
add_executable(world-with-temperature-demo test/demo.cpp test/lib/crow_all.h ${SOURCE_FILES})
target_link_libraries(world-with-temperature-demo ${LIBRARIES})

# performance
add_executable(world-with-temperature-performance test/performance.cpp ${SOURCE_FILES})
target_link_libraries(world-with-temperature-performance ${LIBRARIES})
