set(TARGET_NAME ${PROJECT_NAME}_unit_tests)

add_executable(${TARGET_NAME}
    main.cpp
)

if(COMPUTE_RUNTIME_SUPPORT)
    configure_file(${COMPUTE_RUNTIME_DIR}/config.h.in ${CMAKE_BINARY_DIR}/config.h)

    target_compile_definitions(${TARGET_NAME}
        PRIVATE
            -DGMM_OCL
            -DWDDM_VERSION_NUMBER=23
            -DCL_TARGET_OPENCL_VERSION=210
    )

    target_sources(${TARGET_NAME}
        PRIVATE
            test_cmdqueue.cpp
            test_cmdlist.cpp
            test_device.cpp
            test_driver.cpp
            test_event.cpp
            test_sample.cpp
    )

    target_sources(${TARGET_NAME}
        PRIVATE
            ${COMPUTE_RUNTIME_DIR}/runtime/aub/aub_stream_interface.cpp
            ${COMPUTE_RUNTIME_DIR}/runtime/dll/create_command_stream.cpp
            ${COMPUTE_RUNTIME_DIR}/runtime/dll/source_level_debugger.cpp
            ${COMPUTE_RUNTIME_DIR}/runtime/dll/windows/environment_variables.cpp
            ${COMPUTE_RUNTIME_DIR}/runtime/dll/windows/options.cpp
            ${COMPUTE_RUNTIME_DIR}/runtime/dll/windows/os_interface.cpp
            ${COMPUTE_RUNTIME_DIR}/runtime/helpers/built_ins_helper.cpp
            ${COMPUTE_RUNTIME_DIR}/runtime/gmm_helper/gmm_memory.cpp
            ${COMPUTE_RUNTIME_DIR}/runtime/gmm_helper/gmm_memory_base.cpp
            ${COMPUTE_RUNTIME_DIR}/runtime/gmm_helper/page_table_mngr.cpp
            ${COMPUTE_RUNTIME_DIR}/runtime/gmm_helper/resource_info.cpp
            ${COMPUTE_RUNTIME_DIR}/runtime/helpers/abort.cpp
            ${COMPUTE_RUNTIME_DIR}/runtime/helpers/debug_helpers.cpp
            ${COMPUTE_RUNTIME_DIR}/runtime/os_interface/windows/os_interface.cpp
            ${COMPUTE_RUNTIME_DIR}/runtime/os_interface/windows/sys_calls.cpp
            ${COMPUTE_RUNTIME_DIR}/runtime/os_interface/windows/wddm/wddm_calls.cpp
            ${COMPUTE_RUNTIME_DIR}/runtime/os_interface/windows/wddm/wddm_create.cpp
            ${COMPUTE_RUNTIME_DIR}/runtime/program/evaluate_unhandled_token.cpp
            ${COMPUTE_RUNTIME_DIR}/runtime/utilities/debug_settings_reader_creator.cpp
    )

    target_include_directories(${TARGET_NAME}
        PRIVATE
            ${COMPUTE_RUNTIME_DIR}
            ${COMPUTE_RUNTIME_DIR}/runtime/command_stream/definitions
            ${COMPUTE_RUNTIME_DIR}/runtime/gmm_helper/client_context
            ${COMPUTE_RUNTIME_DIR}/runtime/gmm_helper/gmm_memory
            ${COMPUTE_RUNTIME_DIR}/runtime/instrumentation
            ${COMPUTE_RUNTIME_DIR}/runtime/mem_obj/definitions
            ${COMPUTE_RUNTIME_DIR}/runtime/os_interface/definitions
            ${COMPUTE_RUNTIME_DIR}/runtime/sku_info/definitions
            ${CMAKE_BINARY_DIR}
    )
    
    target_link_libraries(${TARGET_NAME} 
        igdrcl_lib_release
        dxgi
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
