set(TARGET_NAME zet_api)

add_library(${TARGET_NAME}
    STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/zet_common.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zet_driver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zet_device.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zet_cmdlist.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zet_debug.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zet_metric.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zet_module.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zet_pin.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zet_sysman.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zet_tracing.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zet_tools_lib.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zet_lib.h
        ${CMAKE_CURRENT_SOURCE_DIR}/zet_lib.cpp
)

target_include_directories(${TARGET_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${TARGET_NAME}
    ${CMAKE_DL_LIBS}
)
