if(SUPPORT_GEN12LP)
    target_sources(${TARGET_NAME}
        PRIVATE
            cmdlist_tgllp.cpp
            cmdqueue_tgllp.cpp
    )
    set(DEFAULT_PRODUCT_FAMILY IGFX_TIGERLAKE_LP)
endif()
