cmake_minimum_required(VERSION 3.12)

set(ENGINE_PROJECT_NAME 2DEngineCore)

include(FetchContent)

# Fetch raylib
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.0
)

FetchContent_MakeAvailable(raylib)

# Fetch ImGui
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG docking
)

FetchContent_GetProperties(imgui)
if(NOT imgui_POPULATED)
    FetchContent_Populate(imgui)
    file(GLOB IMGUI_SOURCES ${imgui_SOURCE_DIR}/*.cpp ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp)
    file(GLOB IMGUI_HEADERS ${imgui_SOURCE_DIR}/*.h ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.h)
    add_library(ImGui STATIC ${IMGUI_SOURCES} ${IMGUI_HEADERS})
    target_include_directories(ImGui PUBLIC ${imgui_SOURCE_DIR} ${imgui_SOURCE_DIR}/backends)
endif()

# Add imgui_raylib
add_subdirectory(../external/imgui_raylib ${CMAKE_CURRENT_BINARY_DIR}/imgui_raylib)

# Set up engine sources
set(ENGINE_PUBLIC_INCLUDES
    includes/2DEngineCore/test.h
)

set(ENGINE_PRIVATE_SOURCES
    src/2DEngineCore/test.cpp
)

set(ENGINE_ALL_SOURCE
    ${ENGINE_PUBLIC_INCLUDES}
    ${ENGINE_PRIVATE_SOURCES}
)

add_library(${ENGINE_PROJECT_NAME} STATIC ${ENGINE_ALL_SOURCE})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ENGINE_ALL_SOURCE})

target_include_directories(${ENGINE_PROJECT_NAME} PUBLIC includes ${raylib_SOURCE_DIR}/src)

target_compile_features(${ENGINE_PROJECT_NAME} PUBLIC cxx_std_17)

target_link_libraries(${ENGINE_PROJECT_NAME} raylib ImGui imgui_raylib)