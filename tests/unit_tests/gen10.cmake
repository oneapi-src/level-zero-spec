if(SUPPORT_GEN10)
    set(HW_SOURCES
        ${HW_SOURCES}
        ${COMPUTE_RUNTIME_GEN10}
#        cmdlist_cnl.cpp
#        cmdqueue_cnl.cpp
        gen10.cmake
    )

    set(HW_SOURCES_ULT
        ${HW_SOURCES_ULT}
        ${COMPUTE_RUNTIME_ULT_GEN10}
        ${HW_SOURCES}
    )

    set(DEFAULT_PRODUCT_FAMILY IGFX_CANNONLAKE)
endif()
