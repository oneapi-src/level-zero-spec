if(SUPPORT_GEN9)
    set(HW_SOURCES
        ${HW_SOURCES}
        ${COMPUTE_RUNTIME_GEN9}
        cmdlist_kbl.cpp
        cmdqueue_kbl.cpp
        cmdlist_skl.cpp
        cmdqueue_skl.cpp
        gen9.cmake
    )

    set(HW_SOURCES_ULT
        ${HW_SOURCES_ULT}
        ${COMPUTE_RUNTIME_ULT_GEN9}
        ${HW_SOURCES}
    )

    set(DEFAULT_PRODUCT_FAMILY IGFX_SKYLAKE)
endif()
