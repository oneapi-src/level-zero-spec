set(TARGET_NAME xello_tracer)

add_executable(${TARGET_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/xello_tracer.cpp
)
    
if(MSVC)
    set_target_properties(${TARGET_NAME}
        PROPERTIES
            VS_DEBUGGER_COMMAND_ARGUMENTS ""
            VS_DEBUGGER_WORKING_DIRECTORY "$(OutDir)"
    )
endif()

if(WIN32)
target_link_libraries(${TARGET_NAME}
    xe_api xet_api
)
else()
target_link_libraries(${TARGET_NAME}
    xe_api xet_api dl
)
endif()
