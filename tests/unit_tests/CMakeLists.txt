set(TARGET_NAME ${PROJECT_NAME}_unit_tests)

add_executable(${TARGET_NAME}
    main.cpp
)

target_link_libraries(${TARGET_NAME} 
    gmock
)

set_target_properties(${TARGET_NAME}
    PROPERTIES
        VS_DEBUGGER_COMMAND_ARGUMENTS "--gtest_filter=* --gtest_catch_exceptions=0"
)
