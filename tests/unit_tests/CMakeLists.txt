set(TARGET_NAME ${PROJECT_NAME}_unit_tests)

add_executable(${TARGET_NAME}
    main.cpp
    test_event.cpp
)

if(COMPUTE_RUNTIME_SUPPORT)
    target_sources(${TARGET_NAME}
        PRIVATE
            environment.cpp
            cmdlist.cpp
            cmdlist.h
            cmdlist_hw.h
            cmdlist_hw.inl
            cmdlist_imp.cpp
            cmdlist_imp.h
            cmdqueue.cpp
            cmdqueue.h
            cmdqueue_hw.h
            cmdqueue_hw.inl
            cmdqueue_imp.h
            device.cpp
            device.h
            driver.cpp
            driver.h
            event.cpp
            event.h
            graphics_allocation.cpp
            graphics_allocation.h
            memory_manager.cpp
            memory_manager.h
            mock.h
            mock_cmdlist.cpp
            mock_cmdlist.h
            mock_cmdqueue.cpp
            mock_cmdqueue.h
            mock_device.cpp
            mock_device.h
            mock_driver.cpp
            mock_driver.h
            mock_event.cpp
            mock_event.h
            mock_memory_manager.cpp
            mock_memory_manager.h
            test_cmdlist.cpp
            test_cmdlist_close.cpp
            test_cmdlist_encodewaitonevent.cpp
            test_cmdqueue.cpp
            test_cmdqueue_enqueuecommandlist.cpp
            test_device.cpp
            test_driver.cpp
            test_graphics_allocation.cpp
            test_memory_manager.cpp
            test_platform.cpp
            test_sample.cpp
            white_box.h
            ${COMPUTE_RUNTIME_HW_ENABLE}
            ${COMPUTE_RUNTIME_HW_ENABLE_ULT}
    )

    if(SUPPORT_GEN8)
        target_sources(${TARGET_NAME}
            PRIVATE
                cmdlist_bdw.cpp
                cmdqueue_bdw.cpp
        )
        set(DEFAULT_PRODUCT_FAMILY IGFX_BROADWELL)
    endif()

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

    #if(SUPPORT_GEN10)
    if(FALSE)
        target_sources(${TARGET_NAME}
            PRIVATE
                cmdlist_cnl.cpp
                cmdqueue_cnl.cpp
        )
        set(DEFAULT_PRODUCT_FAMILY IGFX_CANNONLAKE)
    endif()

    if(SUPPORT_GEN11)
        target_sources(${TARGET_NAME}
            PRIVATE
                cmdlist_icllp.cpp
                cmdqueue_icllp.cpp
        )
        set(DEFAULT_PRODUCT_FAMILY IGFX_ICELAKE_LP)
    endif()

    if(SUPPORT_GEN12LP)
        target_sources(${TARGET_NAME}
            PRIVATE
                cmdlist_tgllp.cpp
                cmdqueue_tgllp.cpp
        )
        set(DEFAULT_PRODUCT_FAMILY IGFX_TIGERLAKE_LP)
    endif()

    if(SUPPORT_GEN12HP)
        target_sources(${TARGET_NAME}
            PRIVATE
                cmdlist_ats.cpp
                cmdqueue_ats.cpp
        )
        set(DEFAULT_PRODUCT_FAMILY IGFX_TIGERLAKE_HP)
    endif()

    target_compile_definitions(${TARGET_NAME}
        PUBLIC
            DEFAULT_PRODUCT_FAMILY=${DEFAULT_PRODUCT_FAMILY}
    )

    target_link_libraries(${TARGET_NAME} 
        compute_runtime_mockable
        compute_runtime_mockable_extra
    )

    add_dependencies(${TARGET_NAME} mock_gmm)
endif(COMPUTE_RUNTIME_SUPPORT)

set_target_properties(${TARGET_NAME}
    PROPERTIES
        VS_DEBUGGER_COMMAND_ARGUMENTS "--gtest_filter=* --gtest_catch_exceptions=0"
        VS_DEBUGGER_WORKING_DIRECTORY "$(OutDir)"
)

target_link_libraries(${TARGET_NAME}
    xe
    gmock
)
