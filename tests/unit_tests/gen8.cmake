if(SUPPORT_GEN8)
    set(HW_SOURCES
        ${HW_SOURCES}
        ${COMPUTE_RUNTIME_GEN8}
        cmdlist_bdw.cpp
        cmdqueue_bdw.cpp
        gen8.cmake
    )

    set(HW_SOURCES_ULT
        ${HW_SOURCES_ULT}
        ${COMPUTE_RUNTIME_ULT_GEN8}
        ${HW_SOURCES}
    )

    set(DEFAULT_PRODUCT_FAMILY IGFX_BROADWELL)
endif()
