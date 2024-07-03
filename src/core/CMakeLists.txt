file(
    GLOB
    source_files
    CONFIGURE_DEPENDS
    "*.cpp"
)


target_sources(
    ${CMAKE_PROJECT_NAME} 
    PRIVATE 
    ${source_files}
)
