set(APP_NAME main)

set(SOURCES
    main.cpp
    script_python.cpp
    node.cpp
    log_window.cpp
    process_node.cpp
)

add_executable(${APP_NAME} ${SOURCES})

target_link_libraries(${APP_NAME} PRIVATE
    imgui::imgui
    implot::implot
    imguizmo::imguizmo
    imgui_node_editor
    pybind11::lto pybind11::embed pybind11::module pybind11::headers
    spdlog::spdlog
    opengl32.lib
    SDL2::SDL2main SDL2::SDL2
    tiny-process-library::tiny-process-library
)