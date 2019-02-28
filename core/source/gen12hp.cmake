if(SUPPORT_GEN12HP)
    set(HW_SOURCES
        ${HW_SOURCES}
        ${COMPUTE_RUNTIME_GEN12HP}
        ${CMAKE_CURRENT_SOURCE_DIR}/gen12hp/cmdlist_ats.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gen12hp/cmdlist_gen12hp.inl
        ${CMAKE_CURRENT_SOURCE_DIR}/gen12hp/cmdqueue_ats.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gen12hp.cmake
    )

    set(HW_SOURCES_ULT
        ${HW_SOURCES_ULT}
        ${COMPUTE_RUNTIME_ULT_GEN12HP}
        ${HW_SOURCES}
    )

    set(DEFAULT_PRODUCT_FAMILY IGFX_TIGERLAKE_HP)
endif()
