cmake_minimum_required(VERSION 3.10.0)
project(legion)

find_package(Catch2 CONFIG REQUIRED)

add_subdirectory(../canvas canvas)
add_subdirectory(../hive hive)
add_subdirectory(../silhouette silhouette)

file(GLOB_RECURSE legion_HEADER_FILES include/**/*.h)
file(GLOB_RECURSE legion_SOURCE_FILES src/**/*.cpp)

nucleus_add_library(legion ${legion_HEADER_FILES} ${legion_SOURCE_FILES})
target_link_libraries(legion canvas hive silhouette)

set(legion_TEST_FILES
    tests/Resources/TextureConverterTests.cpp
    tests/TestsMain.cpp
    )

nucleus_add_executable(legionTests ${legion_TEST_FILES})
target_link_libraries(legionTests legion Catch2::Catch2)
