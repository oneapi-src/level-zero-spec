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

    target_include_directories(${TARGET_NAME}
        PRIVATE
            ${COMPUTE_RUNTIME_DIR}
            ${COMPUTE_RUNTIME_DIR}/runtime/command_stream/definitions
            ${COMPUTE_RUNTIME_DIR}/runtime/os_interface/definitions
            ${COMPUTE_RUNTIME_DIR}/runtime/sku_info/definitions
            ${COMPUTE_RUNTIME_DIR}/runtime/instrumentation
    )
    
    target_link_libraries(${TARGET_NAME} 
        igdrcl_lib_release
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
