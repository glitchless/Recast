set(SOURCE_FILES src/TemperatureWorld.cpp src/TemperatureWorld.h src/Coord.h src/Temperature.h src/TemperatureWorldUpdater.cpp src/TemperatureWorldUpdater.h src/MathUtils.cpp src/MathUtils.h)
add_executable(world-with-temperature src/main.cpp ${SOURCE_FILES})

enable_testing()
add_executable(world-with-temperature-test test/test.cpp test/catch.hpp ${SOURCE_FILES})
add_test(world-with-temperature-test world-with-temperature-test)
