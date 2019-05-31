if(UNIX)
    set(OS_SPECIFIC_LIBS pthread rt)
    set(black_box_datadir ${CMAKE_INSTALL_FULL_DATAROOTDIR}/loki-samples)
    add_definitions(-DOS_DATADIR=${black_box_datadir}/)
else()
    set(OS_SPECIFIC_LIBS "")
endif()

set (TEST_TARGETS
    xello_world #Dynamically thunking xelloWorld application
    xello_copy #Basic example with copy buffer feature
    xello_ipc_copy #Basic example with IPC API and copy buffer feature
    xello_function_pointers #Basic example with function pointers
    xello_image #Basic example with image kernel
    xello_copy_image #Basic example with copy image features
    xello_multidev #Basic example testing multidevice
    xello_world_icd #ICD loader enabled xelloWorld applicaton
    xello_world_icd_clang #ICD loader enabled xelloWorld applicaton using clang in runtime
    xello_spirv #X -> spirV compilation
#    xello_events # Testing basic event APIs. Disable for now as it fails to
                  # output AUB file (SetCommandStreamReceiver=1) but works on Fulsim and Gen9.
)

foreach(TEST ${TEST_TARGETS})
    if(MSVC)
        if(${TEST} STREQUAL  "xello_ipc_copy")
            continue()
        endif()
    endif()

    add_executable(${TEST} ${TEST}.cpp)

    if(MSVC)
        set_target_properties(${TEST}
            PROPERTIES
                VS_DEBUGGER_COMMAND_ARGUMENTS ""
                VS_DEBUGGER_WORKING_DIRECTORY "$(TargetDir)"
        )
    endif()

    if(UNIX)
        set_source_files_properties(${TEST}.cpp PROPERTIES COMPILE_FLAGS -Wall)
    endif()

    add_dependencies(${TEST} copy_third_party_files ocloc_shared)
    target_link_libraries(${TEST} level_zero_icd_loader ${OS_SPECIFIC_LIBS})

    if(MSVC)
        set(RUN_TEST $<TARGET_FILE:${TEST}> --aub)
    else()
        if(NOT ${TEST} STREQUAL  "xello_ipc_copy")
            set(RUN_TEST LD_LIBRARY_PATH=$<TARGET_FILE_DIR:${TEST}> $<TARGET_FILE:${TEST}> --aub)
        endif()
    endif()

    set(TEST_DIR ${CUSTOM_COMMAND_BINARY_DIR}/${TEST}_aub_test_ats)
    add_custom_target(run_${TEST}_aub_ats ALL DEPENDS ${TEST} copy_test_files level_zero)
    add_custom_command(
      TARGET run_${TEST}_aub_ats
      POST_BUILD
      COMMAND echo deleting and re-creating ${TEST_DIR} directory...
      COMMAND ${CMAKE_COMMAND} -E remove_directory ${TEST_DIR}
      COMMAND ${CMAKE_COMMAND} -E make_directory ${TEST_DIR}
      COMMAND ${CMAKE_COMMAND} -E echo "SetCommandStreamReceiver = 1" > ${TEST_DIR}/igdrcl.config
      COMMAND ${CMAKE_COMMAND} -E echo "ProductFamilyOverride = ats" >> ${TEST_DIR}/igdrcl.config
      COMMAND ${CMAKE_COMMAND} -E echo "EnableLocalMemory = 1" >> ${TEST_DIR}/igdrcl.config
      COMMAND ${CMAKE_COMMAND} -E copy_directory "${CUSTOM_COMMAND_BINARY_DIR}/test_files" "${TEST_DIR}/test_files"
      COMMAND echo Running ${RUN_TEST} for ATS in "${CUSTOM_COMMAND_BINARY_DIR}/${TEST}_aub_test"
      COMMAND ${CMAKE_COMMAND} -E chdir ${TEST_DIR} ${CMAKE_COMMAND} -E env SetCommandStreamReceiver=1 ${RUN_TEST}
    )

    set(TEST_DIR ${CUSTOM_COMMAND_BINARY_DIR}/${TEST}_aub_test_skl)
    add_custom_target(run_${TEST}_aub_skl ALL DEPENDS ${TEST} copy_test_files level_zero)
    add_custom_command(
      TARGET run_${TEST}_aub_skl
      POST_BUILD
      COMMAND echo deleting and re-creating ${TEST_DIR} directory...
      COMMAND ${CMAKE_COMMAND} -E remove_directory ${TEST_DIR}
      COMMAND ${CMAKE_COMMAND} -E make_directory ${TEST_DIR}
      COMMAND ${CMAKE_COMMAND} -E echo "SetCommandStreamReceiver = 1" > ${TEST_DIR}/igdrcl.config
      COMMAND ${CMAKE_COMMAND} -E echo "ProductFamilyOverride = skl" >> ${TEST_DIR}/igdrcl.config
      COMMAND ${CMAKE_COMMAND} -E copy_directory "${CUSTOM_COMMAND_BINARY_DIR}/test_files" "${TEST_DIR}/test_files"
      COMMAND echo Running ${RUN_TEST} for SKL in "${CUSTOM_COMMAND_BINARY_DIR}/${TEST}_aub_test"
      COMMAND ${CMAKE_COMMAND} -E chdir ${TEST_DIR} ${CMAKE_COMMAND} -E env SetCommandStreamReceiver=1 ${RUN_TEST}
    )
endforeach()

if(UNIX)
    install(TARGETS ${TEST_TARGETS}
        DESTINATION ${CMAKE_INSTALL_FULL_BINDIR}
        COMPONENT loki-samples
    )
    install(
        FILES
            "${CMAKE_CURRENT_SOURCE_DIR}/../unit_tests/test_files/spv_modules/cstring_module.spv"
            "${CMAKE_CURRENT_SOURCE_DIR}/../unit_tests/test_files/spv_modules/image_kernel.spv"
        DESTINATION ${black_box_datadir}
        COMPONENT loki-samples
    )
endif()

find_library(CL_LIB OpenCL)
if(CL_LIB)
    add_subdirectory(xello_interop)
endif()
