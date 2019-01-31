set(TARGET_NAME ${PROJECT_NAME}_unit_tests)

add_executable(${TARGET_NAME}
    main.cpp
    test_cmdqueue.cpp
    test_event.cpp
    test_sample.cpp
)

if(COMPUTE_RUNTIME_SUPPORT)
    target_sources(${TARGET_NAME}
        PRIVATE
            environment.cpp
            cmd_list.cpp
            cmd_list.h
            cmd_list_bdw.cpp
            cmd_list_hw.h
            cmd_list_hw.inl
            cmd_list_imp.cpp
            cmd_list_imp.h
            cmd_list_kbl.cpp
            cmd_list_skl.cpp
            cmd_queue.cpp
            cmd_queue.h
            cmd_queue_imp.h
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
            mock_cmd_list.h
            mock_cmdqueue.h
            mock_device.h
            mock_driver.h
            mock_event.h
            mock_memory_manager.h
            test_cmdlist.cpp
            test_cmdlist_close.cpp
            test_cmdlist_encodewaitonevent.cpp
            test_cmdqueue_enqueuecommandlist.cpp
            test_device.cpp
            test_driver.cpp
            test_graphics_allocation.cpp
            test_memory_manager.cpp
            test_platform.cpp
            white_box.h
            ${COMPUTE_RUNTIME_HW_ENABLE}
            ${COMPUTE_RUNTIME_HW_ENABLE_ULT}
    )

    target_link_libraries(${TARGET_NAME} 
        compute_runtime_mockable_full
    )
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
