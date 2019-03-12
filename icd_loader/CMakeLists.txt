add_library(level_zero_icd_loader 
    "${CMAKE_CURRENT_SOURCE_DIR}/icd_loader.cpp"
)

target_include_directories(level_zero_icd_loader 
    PUBLIC 
        "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_compile_definitions(level_zero_icd_loader
    PRIVATE
        XE_MAKEDLL
)

if(MSVC)
    add_subdirectory(config_md)
endif(MSVC)