set(SOURCE_FILES )
add_executable(world-with-temperature src/main.cpp ${SOURCE_FILES})

enable_testing()
add_executable(world-with-temperature-test test/test.cpp test/catch.hpp ${SOURCE_FILES})
add_test(world-with-temperature-test world-with-temperature-test)
