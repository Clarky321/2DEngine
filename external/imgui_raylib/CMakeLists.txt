cmake_minimum_required(VERSION 3.12)

project(imgui_raylib)

add_library(imgui_raylib STATIC
	include/imgui_impl_raylib.h
	src/imgui_impl_raylib.cpp
)

target_include_directories(imgui_raylib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${raylib_SOURCE_DIR}/src
)

target_link_libraries(imgui_raylib PUBLIC raylib ImGui)

target_compile_features(imgui_raylib PUBLIC cxx_std_17)