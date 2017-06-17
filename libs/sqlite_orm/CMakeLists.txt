PROJECT(sqlite_orm)
cmake_minimum_required(VERSION 2.8)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(sqlite_orm STATIC sqlite_orm.h)
add_executable(sqlite_or sqlite_orm.h)
set_target_properties(sqlite_or PROPERTIES OUTPUT_NAME sqlite_orm)

SET_TARGET_PROPERTIES(sqlite_orm PROPERTIES LINKER_LANGUAGE CXX)
SET_TARGET_PROPERTIES(sqlite_or PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(sqlite_orm ${CMAKE_DL_LIBS})
install(FILES sqlite_orm.h DESTINATION include)
install(TARGETS sqlite_orm LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
install(TARGETS sqlite_or RUNTIME DESTINATION bin)
