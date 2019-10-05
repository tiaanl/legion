cmake_minimum_required(VERSION 3.10.0)
project(legion)

add_subdirectory(../canvas canvas)
add_subdirectory(../hive hive)
add_subdirectory(../silhouette silhouette)

set(legion_HEADER_FILES
    include/legion/Resources/Converters/ImageConverter.h
    include/legion/Resources/Converters/ModelConverter.h
    include/legion/Resources/Converters/RendererConverter.h
    include/legion/Resources/Converters/ShaderSourceConverter.h
    include/legion/Resources/Converters/TextureConverter.h

    include/legion/Resources/Texture.h
    include/legion/Resources/Model.h
    )

set(legion_SOURCE_FILES
    src/Resources/Converters/ImageConverter.cpp
    src/Resources/Converters/ModelConverter.cpp
    src/Resources/Converters/ShaderSourceConverter.cpp
    src/Resources/Converters/TextureConverter.cpp

    src/Resources/Model.cpp
    )

set(legion_TESTS_SOURCE_FILES
    tests/Resources/TextureConverterTests.cpp
    )

add_library(legion ${legion_HEADER_FILES} ${legion_SOURCE_FILES})
target_include_directories(legion PUBLIC include)
target_link_libraries(legion canvas hive silhouette)
set_target_properties(legion PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    FOLDER legion
    )
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    # Enable warnings and multi-process compilation.
    target_compile_options(legion PUBLIC /W3 /WX /MP)

    # Enable memory debugging.
    target_compile_definitions(legion PUBLIC "-D_CRTDBG_MAP_ALLOC")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU")
    # Enable warnings.
    target_compile_options(legion PUBLIC -Wall -Wextra -pedantic -Werror)
endif()

add_executable(legionTests ${legion_TESTS_SOURCE_FILES})
target_link_libraries(legionTests legion testing)
set_target_properties(legionTests PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    FOLDER legion
    )

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    # Enable warnings and multi-process compilation.
    target_compile_options(legionTests PUBLIC /W3 /WX /MP)

    # Enable memory debugging.
    target_compile_definitions(legionTests PUBLIC "-D_CRTDBG_MAP_ALLOC")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU")
    # Enable warnings.
    target_compile_options(legionTests PUBLIC -Wall -Wextra -pedantic -Werror)
endif()
