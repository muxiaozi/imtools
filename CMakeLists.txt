cmake_minimum_required(VERSION 3.12.0)

project(ImTools)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(sdl2 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(implot CONFIG REQUIRED)
find_package(imguizmo CONFIG REQUIRED)
find_package(pybind11 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(tiny-process-library CONFIG REQUIRED)

add_subdirectory(lib/imgui_node_editor)

add_subdirectory(src/imtools)
add_subdirectory(src/test)