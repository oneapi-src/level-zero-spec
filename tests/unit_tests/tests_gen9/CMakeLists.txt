if(TESTS_GEN9)
  target_sources(${TARGET_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/test_cmdlist_gen9.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test_cmdlist_encodedispatchfunction_gen9.cpp)
endif()