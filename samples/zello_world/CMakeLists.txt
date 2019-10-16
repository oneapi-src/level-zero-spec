set(TARGET_NAME zello_world)

add_executable(${TARGET_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/zello_world.cpp
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
    ze_api zex_api
)
else()
target_link_libraries(${TARGET_NAME}
    ze_api zex_api dl
)
endif()
