##
## Core library settings
##
set_target_properties(igdrcl_lib_release
    PROPERTIES 
        PROJECT_LABEL "compute_runtime_lib"
        OUTPUT_NAME "compute_runtime_lib"
        FOLDER "compute runtime"
)

# Alias existing target name for cleanliness
add_library(compute_runtime_lib
    ALIAS
        igdrcl_lib_release 
)

#Extract compute runtime COMPILE_DEFINITIONS
get_property(COMPUTE_RUNTIME_DEFINITIONS
    TARGET compute_runtime_lib
    PROPERTY COMPILE_DEFINITIONS
)

#Extract compute runtime INCLUDE_DIRECTORIES
get_property(COMPUTE_RUNTIME_INCLUDES
    TARGET compute_runtime_lib
    PROPERTY INCLUDE_DIRECTORIES
)

#Append additional definitions
set(COMPUTE_RUNTIME_DEFINITIONS
    ${COMPUTE_RUNTIME_DEFINITIONS}
    CL_TARGET_OPENCL_VERSION=210
    GMM_OCL
)

if(WIN32)
    set(COMPUTE_RUNTIME_DEFINITIONS
        ${COMPUTE_RUNTIME_DEFINITIONS}
        WDDM_VERSION_NUMBER=23
    )
endif()

configure_file(${COMPUTE_RUNTIME_DIR}/config.h.in ${CMAKE_BINARY_DIR}/config.h)

# These need to be added to a project to enable platform support
set(COMPUTE_RUNTIME_HW_ENABLE
    # Gen8 support
    ${COMPUTE_RUNTIME_DIR}/runtime/gen8/enable_gen8.cpp
    ${COMPUTE_RUNTIME_DIR}/runtime/gen8/enable_family_full_gen8.cpp
    ${COMPUTE_RUNTIME_DIR}/runtime/gen8/enable_hw_info_config_gen8.cpp
    # Gen9 support
    ${COMPUTE_RUNTIME_DIR}/runtime/gen9/enable_gen9.cpp
    ${COMPUTE_RUNTIME_DIR}/runtime/gen9/enable_family_full_gen9.cpp
    ${COMPUTE_RUNTIME_DIR}/runtime/gen9/enable_hw_info_config_gen9.cpp
    # Gen10 support
    ${COMPUTE_RUNTIME_DIR}/runtime/gen10/enable_gen10.cpp
    ${COMPUTE_RUNTIME_DIR}/runtime/gen10/enable_family_full_gen10.cpp
    ${COMPUTE_RUNTIME_DIR}/runtime/gen10/enable_hw_info_config_gen10.cpp
)

# Create a library that has the missing ingredients to link
add_library(compute_runtime_lib_full
    STATIC
    EXCLUDE_FROM_ALL
        ${COMPUTE_RUNTIME_DIR}/runtime/aub/aub_stream_interface.cpp
        ${COMPUTE_RUNTIME_DIR}/runtime/dll/create_command_stream.cpp
        ${COMPUTE_RUNTIME_DIR}/runtime/dll/create_deferred_deleter.cpp
        ${COMPUTE_RUNTIME_DIR}/runtime/dll/create_tbx_sockets.cpp
        ${COMPUTE_RUNTIME_DIR}/runtime/dll/source_level_debugger.cpp
        ${COMPUTE_RUNTIME_DIR}/runtime/helpers/built_ins_helper.cpp
        ${COMPUTE_RUNTIME_DIR}/runtime/gmm_helper/gmm_memory.cpp
        ${COMPUTE_RUNTIME_DIR}/runtime/gmm_helper/page_table_mngr.cpp
        ${COMPUTE_RUNTIME_DIR}/runtime/gmm_helper/resource_info.cpp
        ${COMPUTE_RUNTIME_DIR}/runtime/helpers/abort.cpp
        ${COMPUTE_RUNTIME_DIR}/runtime/helpers/debug_helpers.cpp
        ${COMPUTE_RUNTIME_DIR}/runtime/program/evaluate_unhandled_token.cpp
        ${COMPUTE_RUNTIME_DIR}/runtime/utilities/debug_settings_reader_creator.cpp
)

#Aggregate all ingredients to link
target_link_libraries(compute_runtime_lib_full 
    compute_runtime_lib
)

if(WIN32)
    target_sources(compute_runtime_lib_full
        PRIVATE
            ${COMPUTE_RUNTIME_DIR}/runtime/gmm_helper/gmm_memory_base.cpp
            ${COMPUTE_RUNTIME_DIR}/runtime/dll/windows/environment_variables.cpp
            ${COMPUTE_RUNTIME_DIR}/runtime/dll/windows/options.cpp
            ${COMPUTE_RUNTIME_DIR}/runtime/dll/windows/os_interface.cpp
            ${COMPUTE_RUNTIME_DIR}/runtime/os_interface/windows/os_interface.cpp
            ${COMPUTE_RUNTIME_DIR}/runtime/os_interface/windows/sys_calls.cpp
            ${COMPUTE_RUNTIME_DIR}/runtime/os_interface/windows/wddm/wddm_calls.cpp
            ${COMPUTE_RUNTIME_DIR}/runtime/os_interface/windows/wddm/wddm_create.cpp
    )

    target_link_libraries(compute_runtime_lib_full
        dxgi
        ws2_32
    )
endif()

#Put all compute runtime items into the same folder
set_target_properties(compute_runtime_lib_full
                      elflib
                      biksim
    PROPERTIES 
        FOLDER "compute runtime"
)


##
## ULT related settings
##
set_target_properties(igdrcl_lib_mockable
    PROPERTIES 
        PROJECT_LABEL "compute_runtime_mockable"
        OUTPUT_NAME "compute_runtime_mockable"
        FOLDER "compute runtime"
)

# Alias existing target name for cleanliness
add_library(compute_runtime_mockable
    ALIAS
        igdrcl_lib_mockable 
)

# Create a library that has the missing ingredients to link
add_library(compute_runtime_mockable_full
    STATIC
    EXCLUDE_FROM_ALL
        ${COMPUTE_RUNTIME_DIR}/runtime/aub/aub_stream_interface.cpp
        ${COMPUTE_RUNTIME_DIR}/unit_tests/abort.cpp
        ${COMPUTE_RUNTIME_DIR}/unit_tests/helpers/built_ins_helper.cpp
        ${COMPUTE_RUNTIME_DIR}/unit_tests/helpers/debug_helpers.cpp
        ${COMPUTE_RUNTIME_DIR}/unit_tests/helpers/test_files.cpp
        ${COMPUTE_RUNTIME_DIR}/unit_tests/libult/create_command_stream.cpp
        ${COMPUTE_RUNTIME_DIR}/unit_tests/libult/os_interface.cpp
        ${COMPUTE_RUNTIME_DIR}/unit_tests/libult/source_level_debugger.cpp
        ${COMPUTE_RUNTIME_DIR}/unit_tests/libult/source_level_debugger_library.cpp
        ${COMPUTE_RUNTIME_DIR}/unit_tests/mocks/mock_cif.cpp
        ${COMPUTE_RUNTIME_DIR}/unit_tests/mocks/mock_compilers.cpp
        ${COMPUTE_RUNTIME_DIR}/unit_tests/mocks/mock_gmm_resource_info.cpp
        ${COMPUTE_RUNTIME_DIR}/unit_tests/mocks/mock_program.cpp
        ${COMPUTE_RUNTIME_DIR}/unit_tests/mocks/mock_sip.cpp
        ${COMPUTE_RUNTIME_DIR}/unit_tests/program/evaluate_unhandled_token_ult.cpp
        ${COMPUTE_RUNTIME_DIR}/unit_tests/utilities/debug_settings_reader_creator.cpp
        ${COMPUTE_RUNTIME_DIR}/unit_tests/libult/create_tbx_sockets.cpp
        ${COMPUTE_RUNTIME_DIR}/unit_tests/mocks/mock_deferred_deleter.cpp
        ${COMPUTE_RUNTIME_DIR}/unit_tests/mocks/mock_gmm_page_table_mngr.cpp
        ${COMPUTE_RUNTIME_DIR}/unit_tests/ult_configuration.cpp
)

# These need to be added to a project to enable platform support in ULTs
set(COMPUTE_RUNTIME_HW_ENABLE_ULT
    ${COMPUTE_RUNTIME_DIR}/unit_tests/libult/gen8.cpp
    ${COMPUTE_RUNTIME_DIR}/unit_tests/libult/gen9.cpp
    ${COMPUTE_RUNTIME_DIR}/unit_tests/libult/gen10.cpp
    ${COMPUTE_RUNTIME_DIR}/unit_tests/gen8/cmd_parse_gen8.cpp
    ${COMPUTE_RUNTIME_DIR}/unit_tests/gen9/cmd_parse_gen9.cpp
    ${COMPUTE_RUNTIME_DIR}/unit_tests/gen10/cmd_parse_gen10.cpp
)

#Additional includes for ULT builds
target_include_directories(compute_runtime_mockable_full
    PUBLIC
        ${COMPUTE_RUNTIME_INCLUDES}
        ${COMPUTE_RUNTIME_DIR}/unit_tests/mocks/gmm_memory
)

#Additional compile definitions for ULT builds
target_compile_definitions(compute_runtime_mockable_full
    PUBLIC
        ${COMPUTE_RUNTIME_DEFINITIONS}
        DEFAULT_PLATFORM=SKL
        NEO_ARCH="x64"
)

if(WIN32)
    target_sources(compute_runtime_mockable_full
        PRIVATE
            ${COMPUTE_RUNTIME_DIR}/unit_tests/mocks/mock_gmm_memory_base.cpp
            ${COMPUTE_RUNTIME_DIR}/unit_tests/mocks/mock_wddm.cpp
            ${COMPUTE_RUNTIME_DIR}/unit_tests/os_interface/windows/options.cpp
            ${COMPUTE_RUNTIME_DIR}/unit_tests/os_interface/windows/sys_calls.cpp
            ${COMPUTE_RUNTIME_DIR}/unit_tests/os_interface/windows/ult_dxgi_factory.cpp
            ${COMPUTE_RUNTIME_DIR}/unit_tests/os_interface/windows/wddm_calls.cpp
            ${COMPUTE_RUNTIME_DIR}/unit_tests/os_interface/windows/wddm_create.cpp
    )

    target_link_libraries(compute_runtime_mockable_full
        ws2_32
    )
endif()

if(UNIX)
    target_link_libraries(compute_runtime_mockable_full
        dl
    )
endif()

#Aggregate all ingredients to link
target_link_libraries(compute_runtime_mockable_full
    compute_runtime_mockable
    gmock
    dl
)

#Put all compute runtime items into the same folder
set_target_properties(compute_runtime_mockable_full
    PROPERTIES 
        FOLDER "compute runtime"
)
