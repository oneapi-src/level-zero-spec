#if(SUPPORT_GEN10)
if(FALSE)
    target_sources(${TARGET_NAME}
        PRIVATE
            cmdlist_cnl.cpp
            cmdqueue_cnl.cpp
    )
    set(DEFAULT_PRODUCT_FAMILY IGFX_CANNONLAKE)
endif()
