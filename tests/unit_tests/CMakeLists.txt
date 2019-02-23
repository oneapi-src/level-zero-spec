include(gen8.cmake)
include(gen9.cmake)
include(gen10.cmake)
include(gen11.cmake)
include(gen12lp.cmake)
include(gen12hp.cmake)

# Create our shared library/DLL
set(TARGET_NAME ${PROJECT_NAME})

set(L0_RUNTIME_SOURCES 
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
    memory.cpp
    memory.h
    memory_manager.cpp
    memory_manager.h
    module.cpp
    module.h
)

add_library(${TARGET_NAME} 
    SHARED
        ${L0_RUNTIME_SOURCES}
)

target_compile_definitions(${TARGET_NAME}
    PRIVATE
        ${COMPUTE_RUNTIME_DEFINITIONS}
)

target_include_directories(${TARGET_NAME}
    PRIVATE
        ${COMPUTE_RUNTIME_INCLUDES}
)

target_link_libraries(${TARGET_NAME}
    compute_runtime_lib
    compute_runtime_lib_full
)

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
    ${COMPUTE_RUNTIME_HW_ENABLE}
    ${COMPUTE_RUNTIME_HW_ENABLE_ULT}
)

target_compile_definitions(${TARGET_NAME}
    PUBLIC
        DEFAULT_PRODUCT_FAMILY=${DEFAULT_PRODUCT_FAMILY}
)

target_link_libraries(${TARGET_NAME} 
    compute_runtime_mockable
    compute_runtime_mockable_extra
    ${HW_LIBS_ULT}
    xe
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
    
#get_target_property(ult_sources ${TARGET_NAME} SOURCES)
#get_target_property(ult_includes ${TARGET_NAME} INCLUDE_DIRECTORIES)
#get_target_property(ult_library_dependencies ${TARGET_NAME} LINK_LIBRARIES)

#set(GENERATED_FILES_DIR "${XE_ROOT_DIR}/tests/generated/")
#set(EXPORTS_FILENAME "${CMAKE_CURRENT_BINARY_DIR}/driver_exports.def")
#set(MSVC_DEF_LIB_NAME "level_zero_dll")
#configure_file("${GENERATED_FILES_DIR}/driver_exports.def" "${EXPORTS_FILENAME}")
#add_library(level_zero_dll SHARED ${dll_sources} "${EXPORTS_FILENAME}" "${GENERATED_FILES_DIR}/driver_exports_switches.cpp")

#target_include_directories(level_zero_dll PRIVATE ${ult_includes} ${COMPUTE_RUNTIME_INCLUDES})
        
#target_link_libraries(level_zero_dll ${dll_library_dependencies} compute_runtime_lib ${HW_LIBS})
#target_compile_definitions(level_zero_dll PUBLIC RUNTIME_DLL ${COMPUTE_RUNTIME_DEFINITIONS} MOCKABLE_VIRTUAL=)
#set_target_properties(level_zero_dll PROPERTIES OUTPUT_NAME level_zero)

if(MSVC)
    set_target_properties(${TARGET_NAME}
        PROPERTIES
            VS_DEBUGGER_COMMAND_ARGUMENTS "--gtest_filter=* --gtest_catch_exceptions=0"
            VS_DEBUGGER_WORKING_DIRECTORY "$(OutDir)"
    )
endif()

add_custom_target(copy_test_files)

add_custom_command(
    TARGET copy_test_files
    POST_BUILD
    COMMAND echo deleting and re-creating "${PROJECT_BINARY_DIR}/bin/$<CONFIG>/test_files" ...
    COMMAND ${CMAKE_COMMAND} -E remove_directory "${PROJECT_BINARY_DIR}/bin/$<CONFIG>/test_files"
    COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_BINARY_DIR}/bin/$<CONFIG>/test_files"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/test_files" "${PROJECT_BINARY_DIR}/bin/$<CONFIG>/test_files"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/test_files"
)

add_custom_command(
    TARGET copy_test_files
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${IGC_DIR}/lib" "${PROJECT_BINARY_DIR}/bin/$<CONFIG>/"
    DEPENDS "${IGC_DIR}/lib"
)

add_dependencies(${TARGET_NAME} copy_test_files)


