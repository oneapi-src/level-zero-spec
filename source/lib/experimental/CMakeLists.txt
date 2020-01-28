set(TARGET_NAME zex_api)

add_library(${TARGET_NAME}
    STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/zex_common.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zex_driver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zex_cmdlist.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zex_cmdgraph.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zex_experimental_lib.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zex_lib.h
        ${CMAKE_CURRENT_SOURCE_DIR}/zex_lib.cpp
)

target_include_directories(${TARGET_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${TARGET_NAME}
    ${CMAKE_DL_LIBS}
)
