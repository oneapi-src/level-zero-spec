if(SUPPORT_GEN12LP)
    set(HW_SOURCES
        ${HW_SOURCES}
        ${COMPUTE_RUNTIME_GEN12LP}
        ${CMAKE_CURRENT_SOURCE_DIR}/gen12lp/cmdlist_tgllp.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gen12lp/cmdqueue_tgllp.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gen12lp/encode_tgllp.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gen12lp/image_tgllp.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gen12lp.cmake
    )

    set(HW_SOURCES_ULT
        ${HW_SOURCES_ULT}
        ${COMPUTE_RUNTIME_ULT_GEN12LP}
        ${HW_SOURCES}
    )

    set(DEFAULT_PRODUCT_FAMILY IGFX_TIGERLAKE_LP)
endif()
