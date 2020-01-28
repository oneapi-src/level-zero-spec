set(TARGET_NAME ze_null)

add_library(${TARGET_NAME}
    SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_null.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_null.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_core_driver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_experimental_driver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_tools_driver.cpp
)

target_include_directories(${TARGET_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
