if(UNIX)
    set(OS_SPECIFIC_LIBS dl pthread)
else()
    set(OS_SPECIFIC_LIBS "")
endif()

#Dynamically thunking xelloWorld applicaton
add_executable(xello_world xello_world.cpp)

if(MSVC)
    set_target_properties(xello_world
        PROPERTIES
            VS_DEBUGGER_COMMAND_ARGUMENTS ""
            VS_DEBUGGER_WORKING_DIRECTORY "$(OutDir)"
    )
endif()

add_dependencies(xello_world copy_third_party_files)
target_link_libraries(xello_world ${OS_SPECIFIC_LIBS})

#ICD loader enabled xelloWorld applicaton
add_executable(xello_world_icd xello_world_icd.cpp)

if(MSVC)
    set_target_properties(xello_world_icd
        PROPERTIES
            VS_DEBUGGER_COMMAND_ARGUMENTS ""
            VS_DEBUGGER_WORKING_DIRECTORY "$(OutDir)"
    )
endif()

add_dependencies(xello_world_icd copy_third_party_files)
target_link_libraries(xello_world_icd level_zero_icd_loader ${OS_SPECIFIC_LIBS})

#ICD loader enabled xelloWorld applicaton using clang in runtime
add_executable(xello_world_icd_clang xello_world_icd_clang.cpp)

if(MSVC)
    set_target_properties(xello_world_icd_clang
        PROPERTIES
            VS_DEBUGGER_COMMAND_ARGUMENTS ""
            VS_DEBUGGER_WORKING_DIRECTORY "$(OutDir)"
    )
endif()

add_dependencies(xello_world_icd_clang copy_third_party_files ocloc_shared)
target_link_libraries(xello_world_icd_clang level_zero_icd_loader ${OS_SPECIFIC_LIBS})

if(MSVC)
    set(RUN_XELLO_WORLD_ICD_AUB_CMD $<TARGET_FILE:xello_world_icd>)
else()
    set(RUN_XELLO_WORLD_ICD_AUB_CMD LD_LIBRARY_PATH=$<TARGET_FILE_DIR:xello_world_icd> $<TARGET_FILE:xello_world_icd>)
endif()

set(TEST_DIR ${CUSTOM_COMMAND_BINARY_DIR}/xello_world_icd_aub_test_ats)
add_custom_target(run_xello_world_icd_aub_ats ALL DEPENDS xello_world_icd copy_test_files level_zero)
add_custom_command(
  TARGET run_xello_world_icd_aub_ats
  POST_BUILD
  COMMAND echo deleting and re-creating ${TEST_DIR} directory...
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${TEST_DIR}
  COMMAND ${CMAKE_COMMAND} -E make_directory ${TEST_DIR}
  COMMAND ${CMAKE_COMMAND} -E echo "SetCommandStreamReceiver = 1" > ${TEST_DIR}/igdrcl.config
  COMMAND ${CMAKE_COMMAND} -E echo "ProductFamilyOverride = ats" >> ${TEST_DIR}/igdrcl.config
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${CUSTOM_COMMAND_BINARY_DIR}/test_files" "${TEST_DIR}/test_files"
  # COMMAND WORKING_DIRECTORY \"${CUSTOM_COMMAND_BINARY_DIR}\"
  COMMAND echo Running ${RUN_XELLO_WORLD_ICD_AUB_CMD} for ATS in "${CUSTOM_COMMAND_BINARY_DIR}/xello_world_icd_aub_test"
  COMMAND ${CMAKE_COMMAND} -E chdir ${TEST_DIR} ${CMAKE_COMMAND} -E env SetCommandStreamReceiver=1 ${RUN_XELLO_WORLD_ICD_AUB_CMD}
)

set(TEST_DIR ${CUSTOM_COMMAND_BINARY_DIR}/xello_world_icd_aub_test_skl)
add_custom_target(run_xello_world_icd_aub_skl ALL DEPENDS xello_world_icd copy_test_files level_zero)
add_custom_command(
  TARGET run_xello_world_icd_aub_skl
  POST_BUILD
  COMMAND echo deleting and re-creating ${TEST_DIR} directory...
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${TEST_DIR}
  COMMAND ${CMAKE_COMMAND} -E make_directory ${TEST_DIR}
  COMMAND ${CMAKE_COMMAND} -E echo "SetCommandStreamReceiver = 1" > ${TEST_DIR}/igdrcl.config
  COMMAND ${CMAKE_COMMAND} -E echo "ProductFamilyOverride = skl" >> ${TEST_DIR}/igdrcl.config
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${CUSTOM_COMMAND_BINARY_DIR}/test_files" "${TEST_DIR}/test_files"
  # COMMAND WORKING_DIRECTORY \"${CUSTOM_COMMAND_BINARY_DIR}\"
  COMMAND echo Running ${RUN_XELLO_WORLD_ICD_AUB_CMD} for SKL in "${CUSTOM_COMMAND_BINARY_DIR}/xello_world_icd_aub_test"
  COMMAND ${CMAKE_COMMAND} -E chdir ${TEST_DIR} ${CMAKE_COMMAND} -E env SetCommandStreamReceiver=1 ${RUN_XELLO_WORLD_ICD_AUB_CMD}
)
