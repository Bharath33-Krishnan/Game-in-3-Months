cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


file(GLOB src "*.cpp")

project(GIN3 VERSION 0.01)
configure_file(version.h.in version.h)

include_directories(${CMAKE_SOURCE_DIR}/include)


add_executable(${CMAKE_PROJECT_NAME}.out ${src})

#Adding our subdir => light_lib is made
add_subdirectory(${CMAKE_SOURCE_DIR}/src/Test)

add_library(raylib STATIC IMPORTED)
set_target_properties(raylib PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/raylib/libraylib.a)
target_link_libraries(${CMAKE_PROJECT_NAME}.out PRIVATE raylib test_lib)
add_dependencies(${CMAKE_PROJECT_NAME}.out test_lib)

# add_library(raylib PRIVATE )
# target_link_libraries(${CMAKE_PROJECT_NAME}.out PUBLIC ${CMAKE_SOURCE_DIR}/lib/libraylib.a)
# target_include_directories(${CMAKE_PROJECT_NAME}.out PUBLIC "${PROJECT_BINARY_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/src/lighting")
# target_include_directories(main_executable PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/subdirectory_name")
