cmake_minimum_required(VERSION 3.10.0)
project(legion)

add_subdirectory(../canvas canvas)
add_subdirectory(../hive hive)
add_subdirectory(../silhouette silhouette)

file(GLOB_RECURSE legion_HEADER_FILES include/**/*.h)
file(GLOB_RECURSE legion_SOURCE_FILES src/**/*.cpp)
file(GLOB_RECURSE legionTests_SOURCE_FILES tests/**/*.cpp)

nucleus_add_library(legion ${legion_HEADER_FILES} ${legion_SOURCE_FILES})
target_link_libraries(legion canvas hive silhouette)

nucleus_add_executable(legionTests ${legionTests_SOURCE_FILES})
target_link_libraries(legionTests legion testing)
