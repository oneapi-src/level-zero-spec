if(UNIX)
    set(OS_SPECIFIC_LIBS pthread)
else()
    set(OS_SPECIFIC_LIBS "")
endif()

set(CMAKE_CXX_STANDARD "11")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(XE_NANO_COMMON src/xe_app.cpp)
set(XE_NANO_BENCHMARKS
    src/xe_nano.cpp
    src/benchmark_set_parameter.cpp
)

add_executable(xe_nano ${XE_NANO_COMMON} ${XE_NANO_BENCHMARKS})

add_dependencies(xe_nano copy_third_party_files ocloc_shared)

target_link_libraries(xe_nano level_zero_icd_loader ${OS_SPECIFIC_LIBS})

target_include_directories(xe_nano PRIVATE "include")

add_custom_command(
        TARGET xe_nano POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/tests/perf_tests/xe_nano/kernels/xe_nano_benchmarks.spv
                ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/xe_nano_benchmarks.spv)

if(UNIX)
    install(TARGETS xe_nano
        DESTINATION ${CMAKE_INSTALL_FULL_BINDIR}
        COMPONENT loki-xe-nano
    )
    install(
        FILES
            "${CMAKE_CURRENT_SOURCE_DIR}/kernels/xe_nano_benchmarks.spv"
        DESTINATION ${CMAKE_INSTALL_FULL_BINDIR}
        COMPONENT loki-xe-nano
    )
endif()

if(MSVC)
    set_target_properties(xe_nano
        PROPERTIES
            VS_DEBUGGER_COMMAND_ARGUMENTS ""
            VS_DEBUGGER_WORKING_DIRECTORY "$(OutDir)"
    )
endif()
