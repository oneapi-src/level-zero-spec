set(TARGET_NAME ze_api_cpp)

add_library(${TARGET_NAME}
    STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_wprapi.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zet_wprapi.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zes_wprapi.cpp
)

target_include_directories(${TARGET_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(${TARGET_NAME}
    PRIVATE
        ZE_ENABLE_OCL_INTEROP=0
)

target_link_libraries(${TARGET_NAME}
    ze_api
    ${CMAKE_DL_LIBS}
)