add_library(level_zero_icd_loader
    "${CMAKE_CURRENT_SOURCE_DIR}/loader.cpp"
)

target_include_directories(level_zero_icd_loader
    PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_compile_definitions(level_zero_icd_loader
    PRIVATE
    XE_MAKEDLL
)

target_include_directories(level_zero_icd_loader
    INTERFACE
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/level_zero>
)

if(UNIX)
    target_link_libraries(level_zero_icd_loader INTERFACE dl)
endif()

if(MSVC)
    add_subdirectory(config_md)
endif(MSVC)

if(UNIX)
    install(TARGETS level_zero_icd_loader
        EXPORT LevelZeroICD
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT loki-devel
    )
    install(FILES loader.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/level_zero
        COMPONENT loki-devel
    )
    install(EXPORT LevelZeroICD
        NAMESPACE "LevelZero::"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/level_zero"
        COMPONENT loki-devel
    )
endif()
