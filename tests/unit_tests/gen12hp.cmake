if(SUPPORT_GEN12HP)
    target_sources(${TARGET_NAME}
        PRIVATE
            cmdlist_ats.cpp
            cmdqueue_ats.cpp
    )
    set(DEFAULT_PRODUCT_FAMILY IGFX_TIGERLAKE_HP)
endif()
