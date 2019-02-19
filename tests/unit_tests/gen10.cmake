set(HW_TARGET gen10)

set(HW_SOURCES
    ${COMPUTE_RUNTIME_GEN10}
#    cmdlist_cnl.cpp
#    cmdqueue_cnl.cpp
    gen10.cmake
)

set(HW_SOURCES_ULT
    ${COMPUTE_RUNTIME_ULT_GEN10}
    ${HW_SOURCES}
)

if(SUPPORT_GEN10)
    add_library(${HW_TARGET}
        OBJECT
            ${HW_SOURCES}
    )

    target_link_libraries(${HW_TARGET}
        compute_runtime_lib
        compute_runtime_lib_full
    )

    target_include_directories(${HW_TARGET} 
        PRIVATE 
            ${COMPUTE_RUNTIME_INCLUDES}
    )

    target_compile_definitions(${HW_TARGET} 
        PRIVATE 
            ${COMPUTE_RUNTIME_DEFINITIONS}
    )

    add_library(${HW_TARGET}_ult
        OBJECT
            ${HW_SOURCES_ULT}
    )

    target_link_libraries(${HW_TARGET}_ult
        compute_runtime_mockable
        compute_runtime_mockable_extra
    )

    set(HW_LIBS
        ${HW_LIBS}
        ${HW_TARGET}
    )

    set(HW_LIBS_ULT
        ${HW_LIBS_ULT}
        ${HW_TARGET}_ult
    )

    set(DEFAULT_PRODUCT_FAMILY IGFX_ICELAKE_LP)
endif()
