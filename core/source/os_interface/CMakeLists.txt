set(L0_SRCS_OS_INTERFACE_BASE
    ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/os_context.h
)

target_sources(${TARGET_NAME} PRIVATE
    ${L0_SRCS_OS_INTERFACE_BASE}
    ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
)
set_property(GLOBAL PROPERTY L0_SRCS_OS_INTERFACE_BASE
    ${L0_SRCS_OS_INTERFACE_BASE})

# Make our source files visible to parent 
set(L0_SRCS_OS_INTERFACE_BASE "${L0_SRCS_OS_INTERFACE_BASE}" CACHE STRING "L0_SRCS_OS_INTERFACE_BASE" FORCE)

if(UNIX)
    add_subdirectory(linux)
else()
    add_subdirectory(windows)
endif()
