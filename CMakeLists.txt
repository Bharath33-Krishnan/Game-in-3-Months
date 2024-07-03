cmake_minimum_required(VERSION 3.29)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(
    ENGINE_NAME
    "Engine"
)

project(GIN3 VERSION 0.01)

file(GLOB source_files main.cpp)

add_executable(
    ${CMAKE_PROJECT_NAME}
    ${source_files}
)

target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    PUBLIC
    ${ENGINE_NAME}
)

add_subdirectory(${ENGINE_NAME})
