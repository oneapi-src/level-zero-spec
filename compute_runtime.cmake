set_target_properties(igdrcl_lib_release
    PROPERTIES 
        PROJECT_LABEL "compute_runtime_lib"
        OUTPUT_NAME "compute_runtime_lib"
        FOLDER "compute runtime"
)

add_library(compute_runtime_lib
    ALIAS
        igdrcl_lib_release 
)

#Extract compute runtime COMPILE_DEFINITIONS
get_property(COMPUTE_RUNTIME_DEFINITIONS
    TARGET compute_runtime_lib
    PROPERTY COMPILE_DEFINITIONS
)

#Append additional definitions
set(COMPUTE_RUNTIME_DEFINITIONS
    ${COMPUTE_RUNTIME_DEFINITIONS}
    CL_TARGET_OPENCL_VERSION=210
    GMM_OCL
    WDDM_VERSION_NUMBER=23
)

#Extract compute runtime INCLUDE_DIRECTORIES
get_property(COMPUTE_RUNTIME_INCLUDES
    TARGET compute_runtime_lib
    PROPERTY INCLUDE_DIRECTORIES
)

configure_file(${COMPUTE_RUNTIME_DIR}/config.h.in ${CMAKE_BINARY_DIR}/config.h)

#Object library to enable each HW platform
add_library(compute_runtime_lib_hw_enable
    OBJECT
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

target_include_directories(compute_runtime_lib_hw_enable
    PUBLIC
        ${COMPUTE_RUNTIME_INCLUDES}
)

target_compile_definitions(compute_runtime_lib_hw_enable
    PUBLIC
        ${COMPUTE_RUNTIME_DEFINITIONS}
)

target_link_libraries(compute_runtime_lib_hw_enable
    compute_runtime_lib
)

add_library(compute_runtime_lib_full
    STATIC
        ${COMPUTE_RUNTIME_DIR}/runtime/aub/aub_stream_interface.cpp
        ${COMPUTE_RUNTIME_DIR}/runtime/dll/create_command_stream.cpp
        ${COMPUTE_RUNTIME_DIR}/runtime/dll/create_deferred_deleter.cpp
        ${COMPUTE_RUNTIME_DIR}/runtime/dll/create_tbx_sockets.cpp
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

target_link_libraries(compute_runtime_lib_full 
    compute_runtime_lib_hw_enable
    dxgi
    ws2_32
)

set_target_properties(compute_runtime_lib_hw_enable 
                      compute_runtime_lib_full
                      elflib
                      biksim
    PROPERTIES 
        FOLDER "compute runtime"
)

