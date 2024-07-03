file(GLOB source_files "*.cpp")

configure_file(version.h.in version.h)

include_directories(${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/include)
include_directories(${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/src/)
include_directories(${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/src/utilities)

add_library(${ENGINE_NAME} ${source_files})

foreach(subdir IN ITEMS assets utilities core) #Append extra subdirs to the end of the list for src
    add_subdirectory(${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/src/${subdir})
endforeach()

target_link_libraries(
    ${ENGINE_NAME} 
    PUBLIC
    raylib
    ${CMAKE_SOURCE_DIR}/${ENGINE_NAME}/lib/raylib/libraylib.a
)
