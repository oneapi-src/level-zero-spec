set(TARGET_NAME xe_null)

add_library(${TARGET_NAME}
    SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/xe_null.h
        ${CMAKE_CURRENT_SOURCE_DIR}/xe_null.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/xe_core_driver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/xe_extended_driver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/xe_tools_driver.cpp
)

target_include_directories(${TARGET_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(${TARGET_NAME}
    PRIVATE
        XE_ENABLE_OCL_INTEROP=0
)