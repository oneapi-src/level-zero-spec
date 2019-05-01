set(TARGET_NAME xe_intc_loader)

add_library(${TARGET_NAME}
    SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/loader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/core_loader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/extended_loader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tools_loader.cpp
)

target_include_directories(${TARGET_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(${TARGET_NAME}
    PRIVATE
        XE_MAKEDLL
        XE_ENABLE_OCL_INTEROP=0
)