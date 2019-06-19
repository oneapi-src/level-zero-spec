set(TARGET_NAME xe_validation_layer)

add_library(${TARGET_NAME}
    SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/xe_layer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/xe_layer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/xe_core_layer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/xe_experimental_layer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/xe_tools_layer.cpp
)

target_include_directories(${TARGET_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(${TARGET_NAME}
    PRIVATE
        XE_ENABLE_OCL_INTEROP=0
)