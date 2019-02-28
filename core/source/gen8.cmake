if(SUPPORT_GEN8)
    set(HW_SOURCES
        ${HW_SOURCES}
        ${COMPUTE_RUNTIME_GEN8}
        ${CMAKE_CURRENT_SOURCE_DIR}/gen8/cmdlist_bdw.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gen8/cmdqueue_bdw.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gen8.cmake
    )

    set(HW_SOURCES_ULT
        ${HW_SOURCES_ULT}
        ${COMPUTE_RUNTIME_ULT_GEN8}
        ${HW_SOURCES}
    )

    set(DEFAULT_PRODUCT_FAMILY IGFX_BROADWELL)
endif()
