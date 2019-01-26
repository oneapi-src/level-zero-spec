set(TARGET_NAME ${PROJECT_NAME}_unit_tests)

add_executable(${TARGET_NAME}
    main.cpp
)
if(COMPUTE_RUNTIME_SUPPORT)
    target_sources(${TARGET_NAME}
        PRIVATE
            test_cmdqueue.cpp
            test_cmdlist.cpp
            test_device.cpp
            test_driver.cpp
            test_event.cpp
            test_sample.cpp
    )

    target_link_libraries(${TARGET_NAME} 
        compute_runtime_lib_full
    )
endif(COMPUTE_RUNTIME_SUPPORT)

set_target_properties(${TARGET_NAME}
    PROPERTIES
        VS_DEBUGGER_COMMAND_ARGUMENTS "--gtest_filter=* --gtest_catch_exceptions=0"
)

target_link_libraries(${TARGET_NAME}
    xe
    gmock
)
