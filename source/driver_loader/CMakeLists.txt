set(TARGET_NAME xe_api)

add_library(${TARGET_NAME}
    STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/loader.h
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
        XE_ENABLE_OCL_INTEROP=0
)