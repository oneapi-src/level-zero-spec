set(TARGET_NAME xe_api)

add_library(${TARGET_NAME}
    STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/xe_common.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/xe_driver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/xe_context.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/xe_device.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/xe_cmdqueue.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/xe_cmdlist.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/xe_barrier.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/xe_cl_interop.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/xe_copy.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/xe_event.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/xe_fence.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/xe_image.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/xe_memory.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/xe_module.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/xe_residency.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/xe_sampler.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/xe_lib.h
        ${CMAKE_CURRENT_SOURCE_DIR}/xe_lib.cpp
)

target_include_directories(${TARGET_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(${TARGET_NAME}
    PRIVATE
        XE_ENABLE_OCL_INTEROP=0
)