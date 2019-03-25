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

if(UNIX)
    install(TARGETS level_zero_icd_loader
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT l0-devel)
    install(FILES icd_loader.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/level_zero
        COMPONENT l0-devel)
endif()
