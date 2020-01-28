set(TARGET_NAME zex_api_cpp)

add_library(${TARGET_NAME}
    STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/zex_common.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zex_driver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zex_cmdlist.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zex_cmdgraph.cpp
)

target_include_directories(${TARGET_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(${TARGET_NAME}
    PRIVATE
        ZE_ENABLE_OCL_INTEROP=0
)

if(WIN32)
target_link_libraries(${TARGET_NAME}
    ze_api zex_api
)
else()
target_link_libraries(${TARGET_NAME}
    ze_api zex_api dl
)
endif()
