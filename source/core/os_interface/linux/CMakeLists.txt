set(L0_SRCS_OS_INTERFACE_LINUX
    ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/os_context_linux.h
    ${CMAKE_CURRENT_SOURCE_DIR}/os_context_linux.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/drm_memory_manager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/drm_memory_manager.cpp

)

if(UNIX)
target_sources(${TARGET_NAME}
    PRIVATE 
        ${L0_SRCS_OS_INTERFACE_LINUX}
)
endif()

# Make our source files visible to parent 
set(L0_SRCS_OS_INTERFACE_LINUX "${L0_SRCS_OS_INTERFACE_LINUX}" CACHE STRING "L0_SRCS_OS_INTERFACE_LINUX" FORCE)
