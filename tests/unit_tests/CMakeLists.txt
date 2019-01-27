set(TARGET_NAME ${PROJECT_NAME}_unit_tests)

add_executable(${TARGET_NAME}
    main.cpp
    test_cmdqueue.cpp
    test_cmdlist.cpp
    test_event.cpp
    test_sample.cpp
)

if(COMPUTE_RUNTIME_SUPPORT)
    target_sources(${TARGET_NAME}
        PRIVATE
            environment.cpp
            device.cpp
            device.h
            driver.cpp
            driver.h
            mock_device.h
            mock_driver.h
            test_device.cpp
            test_driver.cpp
            test_platform.cpp
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
