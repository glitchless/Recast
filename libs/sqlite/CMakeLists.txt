PROJECT(sqlite3)
cmake_minimum_required(VERSION 2.8)

link_libraries(pthread)
link_libraries(dl)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(sqlite3 STATIC src/sqlite3.c src/sqlite3.h src/sqlite3ext.h)
add_executable(sqlite src/sqlite3.c src/shell.c src/sqlite3.h src/sqlite3ext.h)
set_target_properties(sqlite PROPERTIES OUTPUT_NAME sqlite3)

add_definitions(-DSQLITE_ENABLE_RTREE)
add_definitions(-DSQLITE_ENABLE_FTS4)
add_definitions(-DSQLITE_ENABLE_JSON1)

target_link_libraries(sqlite3 ${CMAKE_DL_LIBS})
install(FILES src/sqlite3.h src/sqlite3ext.h DESTINATION include)
install(TARGETS sqlite3 LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
install(TARGETS sqlite RUNTIME DESTINATION bin)
