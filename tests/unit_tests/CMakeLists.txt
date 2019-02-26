set(TARGET_NAME ${PROJECT_NAME}_unit_tests)

add_executable(${TARGET_NAME}
    ${L0_RUNTIME_SOURCES}            
    environment.cpp
    main.cpp
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
    mock_module.cpp
    mock_module.h
    mock_module_precompiled.h
    test_cmdlist.cpp
    test_cmdlist_close.cpp
    test_cmdlist_encodedispatchfunction.cpp
    test_cmdlist_encodesignalevent.cpp
    test_cmdlist_encodewaitonevent.cpp
    test_cmdqueue.cpp
    test_cmdqueue_enqueuecommandlist.cpp
    test_device.cpp
    test_driver.cpp
    test_event.cpp
    test_graphics_allocation.cpp
    test_memory_manager.cpp
    test_module.cpp
    test_platform.cpp
    test_sample.cpp
    test_shared_memalloc.cpp
    white_box.h
    ${HW_SOURCES_ULT}
    ${L0_RUNTIME_SOURCES}
)

target_compile_definitions(${TARGET_NAME}
    PUBLIC
        DEFAULT_PRODUCT_FAMILY=${DEFAULT_PRODUCT_FAMILY}
        XE_MAKEDLL
)

target_include_directories(${TARGET_NAME}
    BEFORE
    PRIVATE
        $<TARGET_PROPERTY:${PROJECT_NAME},SOURCE_DIR>/source
)

target_link_libraries(${TARGET_NAME} 
    compute_runtime_mockable
    compute_runtime_mockable_extra
    ${HW_LIBS_ULT}
    gmock
)

if(AUB_STREAM_SUPPORT)
    target_sources(${TARGET_NAME}
        PRIVATE
            $<TARGET_OBJECTS:aub_stream_all_hw>
    )

    target_link_libraries(${TARGET_NAME} 
        aub_stream
    )
endif()

add_dependencies(${TARGET_NAME} mock_gmm)
    
add_subdirectory(precompiled_function_mock_data)

add_custom_target(copy_test_files)

add_custom_command(
    TARGET copy_test_files
    POST_BUILD
    COMMAND echo deleting and re-creating "${CUSTOM_COMMAND_BINARY_DIR}/test_files" ...
    COMMAND ${CMAKE_COMMAND} -E remove_directory "${CUSTOM_COMMAND_BINARY_DIR}/test_files"
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CUSTOM_COMMAND_BINARY_DIR}/test_files"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/test_files" "${CUSTOM_COMMAND_BINARY_DIR}/test_files"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/test_files"
)

add_dependencies(${TARGET_NAME} 
    copy_test_files 
    copy_third_party_files
)

if(MSVC)
    set_target_properties(${TARGET_NAME}
        PROPERTIES
            VS_DEBUGGER_COMMAND_ARGUMENTS "--gtest_filter=* --gtest_catch_exceptions=0"
            VS_DEBUGGER_WORKING_DIRECTORY "$(OutDir)"
    )
    set(RUN_ULT_CMD $<TARGET_FILE:${TARGET_NAME}>)
else()
    set(RUN_ULT_CMD LD_LIBRARY_PATH=$<TARGET_FILE_DIR:${TARGET_NAME}> $<TARGET_FILE:${TARGET_NAME}>)
endif()

add_custom_target(run_${TARGET_NAME} ALL DEPENDS ${TARGET_NAME})
add_custom_command(
  TARGET run_${TARGET_NAME}
  POST_BUILD
  COMMAND WORKING_DIRECTORY ${CUSTOM_COMMAND_BINARY_DIR}
  COMMAND echo Running \"${RUN_ULT_CMD}\" in \"${CUSTOM_COMMAND_BINARY_DIR}\"
  COMMAND ${RUN_ULT_CMD} --gtest_filter=* --gtest_catch_exceptions=0
)
