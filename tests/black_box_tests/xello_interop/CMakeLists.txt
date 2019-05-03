if(UNIX)
    set(OS_SPECIFIC_LIBS pthread)
    set(black_box_datadir ${CMAKE_INSTALL_FULL_DATAROOTDIR}/loki-samples)
    add_definitions(-DOS_DATADIR=${black_box_datadir}/)
else()
    set(OS_SPECIFIC_LIBS "")
endif()

set (TEST_TARGETS
    xello_interop_cl_cmd_queue #MM in XE using a CL command queue
    xello_interop_cl_program   #MM in XE using a CL program
    xello_interop_cl_memory   #MM in XE using a CL memory
)

foreach(TEST ${TEST_TARGETS})
    add_executable(${TEST} ${TEST}.cpp)

    if(MSVC)
        set_target_properties(${TEST}
            PROPERTIES
                VS_DEBUGGER_COMMAND_ARGUMENTS ""
                VS_DEBUGGER_WORKING_DIRECTORY "$(TargetDir)"
        )
    endif()

    include_directories(${COMPUTE_RUNTIME_DIR}/third_party/opencl_headers)

    if(UNIX)
        set_source_files_properties(${TEST}.cpp PROPERTIES COMPILE_FLAGS -Wall)
    endif()

    add_dependencies(${TEST} copy_third_party_files ocloc_shared)
    target_link_libraries(${TEST} level_zero_icd_loader ${OS_SPECIFIC_LIBS})
    target_link_libraries(${TEST} OpenCL ${OS_SPECIFIC_LIBS})

endforeach()

if(UNIX)
    install(TARGETS ${TEST_TARGETS}
        DESTINATION ${CMAKE_INSTALL_FULL_BINDIR}
        COMPONENT loki-samples
    )
    install(
        FILES
            "${CMAKE_CURRENT_SOURCE_DIR}/../../unit_tests/test_files/spv_modules/mat_mult.spv"
        DESTINATION ${black_box_datadir}
        COMPONENT loki-samples
    )
endif()
