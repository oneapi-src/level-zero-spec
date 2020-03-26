set(TARGET_NAME ze_api)

set(lib_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/ze_libapi.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ze_libddi.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zet_libapi.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zet_libddi.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zes_libapi.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zes_libddi.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ze_lib.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ze_lib.cpp
)
if(ZE_EXPERIMENTAL)
    set(lib_SOURCES ${lib_SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/zex_libapi.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zex_libddi.cpp
    )
endif()

add_library(${TARGET_NAME}
    STATIC
        ${lib_SOURCES}
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
    ${CMAKE_DL_LIBS}
)