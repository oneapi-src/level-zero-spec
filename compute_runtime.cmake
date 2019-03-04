set(DISABLED_GTPIN_SUPPORT TRUE)
add_subdirectory(${COMPUTE_RUNTIME_DIR} ${PROJECT_BINARY_DIR}/compute-runtime EXCLUDE_FROM_ALL)

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
    CL_USE_DEPRECATED_OPENCL_1_1_APIS
    CL_USE_DEPRECATED_OPENCL_1_2_APIS
    CL_USE_DEPRECATED_OPENCL_2_0_APIS
    __INTEL_EMBARGO__
)

if(WIN32)
    set(COMPUTE_RUNTIME_DEFINITIONS
        ${COMPUTE_RUNTIME_DEFINITIONS}
        CONST_FROM_WDK_10_0_18328_0=
        GMM_OCL
    )
endif()

configure_file(${COMPUTE_RUNTIME_DIR}/config.h.in ${CMAKE_BINARY_DIR}/config.h)

# These need to be added to a project to enable platform support in ULTs
if(SUPPORT_GEN8)
    set(COMPUTE_RUNTIME_GEN8
        ${COMPUTE_RUNTIME_DIR}/runtime/gen8/enable_gen8.cpp
        ${COMPUTE_RUNTIME_DIR}/runtime/gen8/enable_family_full_gen8.cpp
        ${COMPUTE_RUNTIME_DIR}/runtime/gen8/enable_hw_info_config_gen8.cpp
    )

    set(COMPUTE_RUNTIME_ULT_GEN8
        ${COMPUTE_RUNTIME_DIR}/unit_tests/libult/gen8.cpp
        ${COMPUTE_RUNTIME_DIR}/unit_tests/gen8/cmd_parse_gen8.cpp
    )
endif()

if(SUPPORT_GEN9)
    set(COMPUTE_RUNTIME_GEN9
        ${COMPUTE_RUNTIME_DIR}/runtime/gen9/enable_gen9.cpp
        ${COMPUTE_RUNTIME_DIR}/runtime/gen9/enable_family_full_gen9.cpp
        ${COMPUTE_RUNTIME_DIR}/runtime/gen9/enable_hw_info_config_gen9.cpp
    )

    set(COMPUTE_RUNTIME_ULT_GEN9
        ${COMPUTE_RUNTIME_DIR}/unit_tests/libult/gen9.cpp
        ${COMPUTE_RUNTIME_DIR}/unit_tests/gen9/cmd_parse_gen9.cpp
    )
endif()

if(SUPPORT_GEN10)
    set(COMPUTE_RUNTIME_GEN10
        ${COMPUTE_RUNTIME_DIR}/runtime/gen10/enable_gen10.cpp
        ${COMPUTE_RUNTIME_DIR}/runtime/gen10/enable_family_full_gen10.cpp
        ${COMPUTE_RUNTIME_DIR}/runtime/gen10/enable_hw_info_config_gen10.cpp
    )

    set(COMPUTE_RUNTIME_ULT_GEN10
        ${COMPUTE_RUNTIME_DIR}/unit_tests/libult/gen10.cpp
        ${COMPUTE_RUNTIME_DIR}/unit_tests/gen10/cmd_parse_gen10.cpp
    )
endif()

if(SUPPORT_GEN11)
    set(COMPUTE_RUNTIME_GEN11
        ${COMPUTE_RUNTIME_DIR}/runtime/gen11/enable_gen11.cpp
        ${COMPUTE_RUNTIME_DIR}/runtime/gen11/enable_family_full_gen11.cpp
        ${COMPUTE_RUNTIME_DIR}/runtime/gen11/enable_hw_info_config_gen11.cpp
    )

    set(COMPUTE_RUNTIME_ULT_GEN11
        ${COMPUTE_RUNTIME_DIR}/unit_tests/libult/gen11.cpp
        ${COMPUTE_RUNTIME_DIR}/unit_tests/gen11/cmd_parse_gen11.cpp
    )
endif()

if(SUPPORT_GEN12LP)
    set(COMPUTE_RUNTIME_GEN12LP
        ${COMPUTE_RUNTIME_DIR}/runtime/gen12lp/enable_gen12lp.cpp
        ${COMPUTE_RUNTIME_DIR}/runtime/gen12lp/enable_family_full_gen12lp.cpp
        ${COMPUTE_RUNTIME_DIR}/runtime/gen12lp/enable_hw_info_config_gen12lp.cpp
    )

    set(COMPUTE_RUNTIME_ULT_GEN12LP
        ${COMPUTE_RUNTIME_DIR}/unit_tests/libult/gen12lp.cpp
        ${COMPUTE_RUNTIME_DIR}/unit_tests/gen12lp/cmd_parse_gen12lp.cpp
    )
endif()

if(SUPPORT_GEN12HP)
    set(COMPUTE_RUNTIME_GEN12HP
        ${COMPUTE_RUNTIME_DIR}/runtime/gen12hp/enable_gen12hp.cpp
        ${COMPUTE_RUNTIME_DIR}/runtime/gen12hp/enable_family_full_gen12hp.cpp
        ${COMPUTE_RUNTIME_DIR}/runtime/gen12hp/enable_hw_info_config_gen12hp.cpp
    )

    set(COMPUTE_RUNTIME_ULT_GEN12HP
        ${COMPUTE_RUNTIME_DIR}/unit_tests/libult/gen12hp.cpp
        ${COMPUTE_RUNTIME_DIR}/unit_tests/gen12hp/cmd_parse_gen12hp.cpp
    )
endif()

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
        ${COMPUTE_RUNTIME_DIR}/runtime/gmm_helper/page_table_mngr.cpp
        ${COMPUTE_RUNTIME_DIR}/runtime/gmm_helper/resource_info.cpp
        ${COMPUTE_RUNTIME_DIR}/runtime/helpers/abort.cpp
        ${COMPUTE_RUNTIME_DIR}/runtime/helpers/debug_helpers.cpp
        ${COMPUTE_RUNTIME_DIR}/runtime/program/evaluate_unhandled_token.cpp
        ${COMPUTE_RUNTIME_DIR}/runtime/utilities/debug_settings_reader_creator.cpp
)

get_target_property(COMPUTE_RUNTIME_LIB_INCLUDES compute_runtime_lib INCLUDE_DIRECTORIES)
target_include_directories(compute_runtime_lib_full PUBLIC ${COMPUTE_RUNTIME_LIB_INCLUDES})

#Aggregate all ingredients to link
target_link_libraries(compute_runtime_lib_full 
    compute_runtime_lib
)

if(WIN32)
    target_sources(compute_runtime_lib_full
        PRIVATE
            ${COMPUTE_RUNTIME_DIR}/runtime/gmm_helper/gmm_memory_base.cpp
            ${COMPUTE_RUNTIME_DIR}/runtime/gmm_helper/gmm_memory.cpp
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
else()
    target_sources(compute_runtime_lib_full
    PRIVATE
        ${COMPUTE_RUNTIME_DIR}/runtime/dll/linux/allocator_helper.cpp
        ${COMPUTE_RUNTIME_DIR}/runtime/dll/linux/devices/${BRANCH_DIR_SUFFIX}/devices.inl
        ${COMPUTE_RUNTIME_DIR}/runtime/dll/linux/devices/devices_base.inl      
        ${COMPUTE_RUNTIME_DIR}/runtime/dll/linux/options.cpp
        ${COMPUTE_RUNTIME_DIR}/runtime/dll/linux/os_interface.cpp
    )
    target_include_directories(compute_runtime_lib_full PUBLIC ${COMPUTE_RUNTIME_DIR}/runtime/dll/linux/devices${BRANCH_DIR_SUFFIX})
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

#Extract compute runtime COMPILE_DEFINITIONS
get_property(COMPUTE_RUNTIME_MOCKABLE_DEFINITIONS
    TARGET compute_runtime_mockable
    PROPERTY COMPILE_DEFINITIONS
)

#Append additional definitions
set(COMPUTE_RUNTIME_MOCKABLE_DEFINITIONS
    ${COMPUTE_RUNTIME_MOCKABLE_DEFINITIONS}
    CL_TARGET_OPENCL_VERSION=210
    NEO_ARCH="x64"
    CL_USE_DEPRECATED_OPENCL_1_1_APIS
    CL_USE_DEPRECATED_OPENCL_1_2_APIS
    CL_USE_DEPRECATED_OPENCL_2_0_APIS
    __INTEL_EMBARGO__
)

if(WIN32)
    set(COMPUTE_RUNTIME_DEFINITIONS
        ${COMPUTE_RUNTIME_DEFINITIONS}
        WDDM_VERSION_NUMBER=23
    )

    set(COMPUTE_RUNTIME_MOCKABLE_DEFINITIONS
        ${COMPUTE_RUNTIME_MOCKABLE_DEFINITIONS}
        WDDM_VERSION_NUMBER=23
        CONST_FROM_WDK_10_0_18328_0=
    )
endif()

#Extract compute runtime INCLUDE_DIRECTORIES
get_property(COMPUTE_RUNTIME_MOCKABLE_INCLUDES
    TARGET compute_runtime_mockable
    PROPERTY INCLUDE_DIRECTORIES
)

# Create a library that has the missing ingredients to link
add_library(compute_runtime_mockable_extra
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
        ${COMPUTE_RUNTIME_DIR}/unit_tests/mocks/mock_csr.cpp
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

target_compile_definitions(compute_runtime_lib_full PUBLIC ${COMPUTE_RUNTIME_DEFINITIONS})

# These need to be added to a project to enable platform support in ULTs

#Additional includes for ULT builds
target_include_directories(compute_runtime_mockable_extra
    PUBLIC
        ${COMPUTE_RUNTIME_MOCKABLE_INCLUDES}
        ${COMPUTE_RUNTIME_DIR}/unit_tests/mocks/gmm_memory
)

#Additional compile definitions for ULT builds
target_compile_definitions(compute_runtime_mockable_extra
    PUBLIC
        ${COMPUTE_RUNTIME_MOCKABLE_DEFINITIONS}
)

target_link_libraries(compute_runtime_mockable_extra
    gmock
)

if(WIN32)
    target_sources(compute_runtime_mockable_extra
        PRIVATE
            ${COMPUTE_RUNTIME_DIR}/runtime/dll/windows/environment_variables.cpp
            ${COMPUTE_RUNTIME_DIR}/unit_tests/mocks/mock_gmm_memory_base.cpp
            ${COMPUTE_RUNTIME_DIR}/unit_tests/mocks/mock_wddm.cpp
            ${COMPUTE_RUNTIME_DIR}/unit_tests/os_interface/windows/options.cpp
            ${COMPUTE_RUNTIME_DIR}/unit_tests/os_interface/windows/sys_calls.cpp
            ${COMPUTE_RUNTIME_DIR}/unit_tests/os_interface/windows/ult_dxgi_factory.cpp
            ${COMPUTE_RUNTIME_DIR}/unit_tests/os_interface/windows/wddm_calls.cpp
            ${COMPUTE_RUNTIME_DIR}/unit_tests/os_interface/windows/wddm_create.cpp
    )

    target_link_libraries(compute_runtime_mockable_extra
        ws2_32
    )
endif()

if(UNIX)
    target_sources(compute_runtime_mockable_extra
        PRIVATE
            ${COMPUTE_RUNTIME_DIR}/runtime/command_stream/create_command_stream_impl.cpp
            ${COMPUTE_RUNTIME_DIR}/runtime/dll/linux/allocator_helper.cpp
            ${COMPUTE_RUNTIME_DIR}/runtime/os_interface/device_factory.cpp
            ${COMPUTE_RUNTIME_DIR}/runtime/os_interface/linux/os_library.cpp
            ${COMPUTE_RUNTIME_DIR}/runtime/tbx/tbx_sockets_imp.cpp
            ${COMPUTE_RUNTIME_DIR}/unit_tests/os_interface/linux/options.cpp
    )

    target_link_libraries(compute_runtime_mockable_extra
        dl
    )
endif()

#Put all compute runtime items into the same folder
set_target_properties(compute_runtime_mockable_extra
    PROPERTIES 
        FOLDER "compute runtime"
)
