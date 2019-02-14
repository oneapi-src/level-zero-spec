if(SUPPORT_GEN8)
    target_sources(${TARGET_NAME}
        PRIVATE
            cmdlist_bdw.cpp
            cmdqueue_bdw.cpp
    )
    set(DEFAULT_PRODUCT_FAMILY IGFX_BROADWELL)
endif()
