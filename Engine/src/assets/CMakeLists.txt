file(
    GLOB
    source_files
    CONFIGURE_DEPENDS
    "*.cpp"
)


target_sources(
    ${ENGINE_NAME} 
    PRIVATE 
    ${source_files}
)
