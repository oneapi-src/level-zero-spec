set(L0_SRCS_OS_INTERFACE_WINDOWS
    ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/os_context_windows.h
    ${CMAKE_CURRENT_SOURCE_DIR}/os_context_windows.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/wddm_event.h
    ${CMAKE_CURRENT_SOURCE_DIR}/wddm_event.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/wddm_memory_manager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/wddm_memory_manager.cpp
)

if(WIN32)
target_sources(${TARGET_NAME}
    PRIVATE 
        ${L0_SRCS_OS_INTERFACE_WINDOWS}
)
endif()

# Make our source files visible to parent 
set(L0_SRCS_OS_INTERFACE_WINDOWS "${L0_SRCS_OS_INTERFACE_WINDOWS}" CACHE STRING "L0_SRCS_OS_INTERFACE_WINDOWS" FORCE)
