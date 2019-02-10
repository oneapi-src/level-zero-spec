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
            cmdlist_bdw.cpp
            cmdlist_hw.h
            cmdlist_hw.inl
            cmdlist_imp.cpp
            cmdlist_imp.h
            cmdlist_kbl.cpp
            cmdlist_skl.cpp
            cmdqueue.cpp
            cmdqueue.h
            cmdqueue_bdw.cpp
            cmdqueue_hw.h
            cmdqueue_hw.inl
            cmdqueue_imp.h
            cmdqueue_kbl.cpp
            cmdqueue_skl.cpp
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
