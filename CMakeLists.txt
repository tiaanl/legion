cmake_minimum_required(VERSION 3.19)

project(legion)

add_subdirectory(../elastic elastic)
add_subdirectory(../hive hive)
add_subdirectory(../silhouette silhouette)

set(HEADER_FILES
    include/legion/controllers/camera_controller.h
    include/legion/controllers/first_person_camera_controller.h
    include/legion/controllers/orbit_camera_controller.h
    include/legion/controllers/top_down_camera_controller.h
    include/legion/engine/engine.hpp
    include/legion/engine/engine_layer.h
    include/legion/engine/engine_window_delegate.h
    include/legion/engine/user_interface_engine_layer.hpp
    include/legion/rendering/rendering.h
    include/legion/resources/converters/collada_model_importer.h
    include/legion/resources/converters/font_importer.hpp
    include/legion/resources/converters/obj_scene_importer.h
    include/legion/resources/converters/png_imageImporter.h
    include/legion/resources/converters/renderer_importer.h
    include/legion/resources/converters/shader_source_importer.h
    include/legion/resources/converters/texture_converter.h
    include/legion/resources/render_model.h
    include/legion/resources/resource_manager.h
    include/legion/resources/texture.h
    include/legion/world/camera.h
    )

set(SOURCE_FILES
    src/controllers/first_person_camera_controller.cpp
    src/controllers/orbit_camera_controller.cpp
    src/controllers/top_down_camera_controller.cpp
    src/engine/engine.cpp
    src/engine/engine_window_delegate.cpp
    src/engine/user_interface_engine_layer.cpp
    src/rendering/rendering.cpp
    src/resources/converters/collada_model_importer.cpp
    src/resources/converters/font_importer.cpp
    src/resources/converters/obj_scene_importer.cpp
    src/resources/converters/png_imageImporter.cpp
    src/resources/converters/shader_source_importer.cpp
    src/resources/converters/texture_converter.cpp
    src/resources/render_model.cpp
    src/resources/resource_manager.cpp
    src/world/camera.cpp
    )

nucleus_add_library(legion ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(legion PUBLIC canvas elastic hive silhouette)

set(TEST_FILES
    tests/resources/texture_converter_tests.cpp
    )

nucleus_add_executable(legion_tests ${TEST_FILES})
target_link_libraries(legion_tests PRIVATE legion tests_main)

add_subdirectory(examples)
