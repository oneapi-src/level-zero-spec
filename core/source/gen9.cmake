if(SUPPORT_GEN9)
    set(HW_SOURCES
        ${HW_SOURCES}
        ${COMPUTE_RUNTIME_GEN9}
        ${CMAKE_CURRENT_SOURCE_DIR}/gen9/kbl/cmdlist_kbl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gen9/kbl/cmdqueue_kbl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gen9/skl/cmdlist_skl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gen9/skl/cmdqueue_skl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gen9.cmake
    )

    set(HW_SOURCES_ULT
        ${HW_SOURCES_ULT}
        ${COMPUTE_RUNTIME_ULT_GEN9}
        ${HW_SOURCES}
    )

    set(DEFAULT_PRODUCT_FAMILY IGFX_SKYLAKE)
endif()
