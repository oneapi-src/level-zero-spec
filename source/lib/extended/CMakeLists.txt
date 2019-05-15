set(TARGET_NAME xex_api)

add_library(${TARGET_NAME}
    STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/xex_common.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/xex_device.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/xex_cmdgraph.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/xex_lib.h
        ${CMAKE_CURRENT_SOURCE_DIR}/xex_lib.cpp
)

target_include_directories(${TARGET_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(${TARGET_NAME}
    PRIVATE
        XE_ENABLE_OCL_INTEROP=0
)