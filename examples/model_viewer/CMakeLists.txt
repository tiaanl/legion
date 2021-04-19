project(ModelViewer)

set(SOURCE_FILES
    src/model_viewer.cpp
    )

nucleus_add_executable(ModelViewer WIN32 ${SOURCE_FILES})
target_link_libraries(ModelViewer PRIVATE legion)
