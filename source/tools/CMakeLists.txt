# DO NOT EDIT: Generated from "scripts/templates/CMakeLists.cpp.mako"

set(L0_TOOLS_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/gtpin.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/metric.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/power.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/xet_cmdlist.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/xet_common.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/xet_device.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/xet_gtpin.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/xet_metric.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/xet_power.cpp
)

# Make our source files visible to parent 
set(L0_TOOLS_SOURCES "${L0_TOOLS_SOURCES}" CACHE STRING "L0_TOOLS_SOURCES" FORCE)

target_include_directories(${TARGET_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/
)