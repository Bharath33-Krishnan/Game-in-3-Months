cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


file(GLOB src "*.cpp")

project(GIN3 VERSION 0.01)
configure_file(version.h.in version.h)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src/utilities)


add_executable(${CMAKE_PROJECT_NAME}.out ${src})

#Adding our subdir => light_lib is made
foreach(subdir IN ITEMS test utilities) #Append extra subdirs to the end of the list for src
    add_subdirectory(${CMAKE_SOURCE_DIR}/src/${subdir})
    target_link_libraries(${CMAKE_PROJECT_NAME}.out PRIVATE ${subdir}_lib)
    add_dependencies(${CMAKE_PROJECT_NAME}.out ${subdir}_lib)
endforeach()

add_library(raylib STATIC IMPORTED)
set_target_properties(raylib PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/raylib/libraylib.a)
target_link_libraries(${CMAKE_PROJECT_NAME}.out PRIVATE raylib)


