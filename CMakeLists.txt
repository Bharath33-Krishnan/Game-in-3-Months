cmake_minimum_required(VERSION 3.29)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


file(GLOB src "*.cpp")

project(GIN3 VERSION 0.01)
configure_file(version.h.in version.h)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src/utilities)


add_executable(${CMAKE_PROJECT_NAME} ${src})

foreach(subdir IN ITEMS assets utilities core) #Append extra subdirs to the end of the list for src
    add_subdirectory(${CMAKE_SOURCE_DIR}/src/${subdir})
endforeach()

target_link_libraries(
    ${CMAKE_PROJECT_NAME} 
    PRIVATE 
    raylib 
    -L${CMAKE_SOURCE_DIR}/lib/raylib/
)
