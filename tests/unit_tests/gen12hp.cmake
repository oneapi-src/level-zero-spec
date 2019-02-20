if(SUPPORT_GEN12HP)
    set(HW_SOURCES
        ${HW_SOURCES}
        ${COMPUTE_RUNTIME_GEN12HP}
        cmdlist_ats.cpp
        cmdqueue_ats.cpp
        gen12hp.cmake
    )

    set(HW_SOURCES_ULT
        ${HW_SOURCES_ULT}
        ${COMPUTE_RUNTIME_ULT_GEN12HP}
        ${HW_SOURCES}
    )

    set(DEFAULT_PRODUCT_FAMILY IGFX_TIGERLAKE_HP)
endif()
