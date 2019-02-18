
add_executable(xello_world xello_world.cpp)

set_target_properties(xello_world
    PROPERTIES
        VS_DEBUGGER_COMMAND_ARGUMENTS "--gtest_filter=* --gtest_catch_exceptions=0"
        VS_DEBUGGER_WORKING_DIRECTORY "$(OutDir)"
)
