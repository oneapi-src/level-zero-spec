if(UNIX)
    set(OS_SPECIFIC_LIBS pthread)
else()
    set(OS_SPECIFIC_LIBS "")
endif()

set(CMAKE_CXX_STANDARD "11")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(XE_PEAK_COMMON src/common.cpp src/options.cpp src/xe_peak.cpp)
set(XE_PEAK_BENCHMARKS
    src/global_bw.cpp
    src/kernel_latency.cpp
    src/hp_compute.cpp
    src/sp_compute.cpp
    src/integer_compute.cpp
    src/dp_compute.cpp
    src/transfer_bw.cpp
)

add_executable(xe_peak ${XE_PEAK_COMMON} ${XE_PEAK_BENCHMARKS})

add_dependencies(xe_peak copy_third_party_files ocloc_shared)

target_link_libraries(xe_peak level_zero_icd_loader ${OS_SPECIFIC_LIBS})

target_include_directories(xe_peak PRIVATE "include")

add_custom_command(
        TARGET xe_peak POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/tests/perf_tests/xe_peak/kernels/xe_global_bw.spv
                ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/xe_global_bw.spv
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/tests/perf_tests/xe_peak/kernels/xe_hp_compute.spv
                ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/xe_hp_compute.spv
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/tests/perf_tests/xe_peak/kernels/xe_sp_compute.spv
                ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/xe_sp_compute.spv
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/tests/perf_tests/xe_peak/kernels/xe_int_compute.spv
                ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/xe_int_compute.spv
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/tests/perf_tests/xe_peak/kernels/xe_dp_compute.spv
                ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/xe_dp_compute.spv)


if(UNIX)
    install(TARGETS xe_peak
        DESTINATION ${CMAKE_INSTALL_FULL_BINDIR}
        COMPONENT loki-xe-peak
    )
    install(
        FILES
            "${CMAKE_CURRENT_SOURCE_DIR}/kernels/xe_global_bw.spv"
            "${CMAKE_CURRENT_SOURCE_DIR}/kernels/xe_hp_compute.spv"
            "${CMAKE_CURRENT_SOURCE_DIR}/kernels/xe_sp_compute.spv"
            "${CMAKE_CURRENT_SOURCE_DIR}/kernels/xe_int_compute.spv"
            "${CMAKE_CURRENT_SOURCE_DIR}/kernels/xe_dp_compute.spv"
        DESTINATION ${CMAKE_INSTALL_FULL_BINDIR}
        COMPONENT loki-xe-peak
    )
endif()

if(MSVC)
    set_target_properties(xe_peak
        PROPERTIES
            VS_DEBUGGER_COMMAND_ARGUMENTS ""
            VS_DEBUGGER_WORKING_DIRECTORY "$(OutDir)"
    )
endif()
