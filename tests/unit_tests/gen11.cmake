if(SUPPORT_GEN11)
    target_sources(${TARGET_NAME}
        PRIVATE
            cmdlist_icllp.cpp
            cmdqueue_icllp.cpp
    )
    set(DEFAULT_PRODUCT_FAMILY IGFX_ICELAKE_LP)
endif()
