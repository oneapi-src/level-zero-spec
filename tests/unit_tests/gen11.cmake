if(SUPPORT_GEN11)
    set(HW_SOURCES
        ${HW_SOURCES}
        ${COMPUTE_RUNTIME_GEN11}
        cmdlist_icllp.cpp
        cmdqueue_icllp.cpp
        gen11.cmake
    )

    set(HW_SOURCES_ULT
        ${HW_SOURCES_ULT}
        ${COMPUTE_RUNTIME_ULT_GEN11}
        ${HW_SOURCES}
    )

    set(DEFAULT_PRODUCT_FAMILY IGFX_ICELAKE_LP)
endif()
