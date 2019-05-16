set(TARGET_NAME xe_loader)

add_library(${TARGET_NAME}
    SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/xe_loader.h
        ${CMAKE_CURRENT_SOURCE_DIR}/xe_loader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/xe_core_loader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/xe_extended_loader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/xe_tools_loader.cpp
)

target_include_directories(${TARGET_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(${TARGET_NAME}
    PRIVATE
        XE_ENABLE_OCL_INTEROP=0
)