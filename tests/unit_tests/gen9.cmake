if(SUPPORT_GEN9)
    target_sources(${TARGET_NAME}
        PRIVATE
            cmdlist_kbl.cpp
            cmdlist_skl.cpp
            cmdqueue_kbl.cpp
            cmdqueue_skl.cpp
    )
    set(DEFAULT_PRODUCT_FAMILY IGFX_SKYLAKE)
endif()
