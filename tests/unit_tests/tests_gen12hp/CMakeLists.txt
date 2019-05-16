if(TESTS_GEN12HP)
  target_sources(${TARGET_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/test_cmdlist_gen12hp.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test_cmdlist_encodedispatchfunction_gen12hp.cpp)
endif()