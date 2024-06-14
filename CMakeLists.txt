cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME 2DEngine)
project(${PROJECT_NAME})

add_subdirectory(2DEngineCore)

add_subdirectory(2DEngineEditor)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT 2DEngineEditor)