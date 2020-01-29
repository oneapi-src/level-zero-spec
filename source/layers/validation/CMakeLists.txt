set(TARGET_NAME ze_validation_layer)

add_library(${TARGET_NAME}
    SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_layer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_layer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_core_layer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_experimental_layer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_tools_layer.cpp
)

target_include_directories(${TARGET_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(${TARGET_NAME}
    PRIVATE
        ZE_ENABLE_OCL_INTEROP=0
)