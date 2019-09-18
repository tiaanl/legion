cmake_minimum_required(VERSION 3.10.0)
project(reactor)

add_subdirectory(../canvas canvas)
add_subdirectory(../hive hive)
add_subdirectory(../silhouette silhouette)

set(reactor_HEADER_FILES
    include/reactor/Resources/Converters/TextureConverter.h
    include/reactor/Resources/Converters/ImageConverter.h
    include/reactor/Resources/Texture.h
    )

set(reactor_SOURCE_FILES
    src/Resources/Converters/ImageConverter.cpp
    src/Resources/Converters/TextureConverter.cpp
    )

set(reactor_TESTS_SOURCE_FILES
    tests/Resources/TextureConverterTests.cpp
    )

add_library(reactor ${reactor_HEADER_FILES} ${reactor_SOURCE_FILES})
target_include_directories(reactor PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(reactor canvas hive silhouette)
set_target_properties(reactor PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    FOLDER reactor
    )
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    # Enable warnings and multi-process compilation.
    target_compile_options(reactor PUBLIC /W3 /WX /MP)

    # Enable memory debugging.
    target_compile_definitions(reactor PUBLIC "-D_CRTDBG_MAP_ALLOC")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU")
    # Enable warnings.
    target_compile_options(reactor PUBLIC -Wall -Wextra -pedantic -Werror)
endif()

add_executable(reactorTests ${reactor_TESTS_SOURCE_FILES})
target_link_libraries(reactorTests reactor testing)
set_target_properties(reactorTests PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    FOLDER reactor
    )

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    # Enable warnings and multi-process compilation.
    target_compile_options(reactorTests PUBLIC /W3 /WX /MP)

    # Enable memory debugging.
    target_compile_definitions(reactorTests PUBLIC "-D_CRTDBG_MAP_ALLOC")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU")
    # Enable warnings.
    target_compile_options(reactorTests PUBLIC -Wall -Wextra -pedantic -Werror)
endif()
