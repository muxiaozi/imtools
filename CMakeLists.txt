cmake_minimum_required(VERSION 3.12.0)

project(ImTools)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(imgui CONFIG REQUIRED)
find_package(pybind11 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(implot CONFIG REQUIRED)
find_package(sdl2 CONFIG REQUIRED)

add_executable(main WIN32 main.cpp)

target_link_libraries(main PRIVATE
    imgui::imgui
    pybind11::lto pybind11::embed pybind11::module pybind11::headers
    spdlog::spdlog
    implot::implot
    opengl32.lib
    SDL2::SDL2main SDL2::SDL2
)