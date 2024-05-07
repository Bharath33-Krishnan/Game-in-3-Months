file(GLOB src "*.cpp")

add_library(core_lib ${src})

# If your subdir has dependencies specify them here as well 
add_library(raylib STATIC IMPORTED)
set_target_properties(raylib PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/raylib/libraylib.a)
target_link_libraries(core_lib PRIVATE raylib)


# file(GLOB_RECURSE ADDITIONAL_SOURCES "*.cpp")
