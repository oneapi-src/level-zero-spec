set(TARGET_NAME xet_api)

add_library(${TARGET_NAME}
    STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/xet_cmdlist.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/xet_common.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/xet_device.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/xet_gtpin.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/xet_metric.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/xet_power.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/xet_sysman.cpp
)

target_include_directories(${TARGET_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(${TARGET_NAME}
    PRIVATE
        XE_ENABLE_OCL_INTEROP=0
)