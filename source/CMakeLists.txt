set(TARGET_NAME ze_test)

add_library(${TARGET_NAME}
    STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_api.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zet_api.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zes_api.cpp
)

target_link_libraries(${TARGET_NAME}
    ${CMAKE_DL_LIBS}
)