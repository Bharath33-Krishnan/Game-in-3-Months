file(
    GLOB
    source_files
    CONFIGURE_DEPENDS
    "*.cpp"
    "collider/*.cpp"
)

target_sources(
    ${ENGINE_NAME} 
    PUBLIC
    ${source_files}
)
