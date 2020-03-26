set(TARGET_NAME ze_null)

set(null_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/ze_null.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ze_null.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ze_nullddi.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zet_nullddi.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zes_nullddi.cpp
)
if(ZE_EXPERIMENTAL)
    set(null_SOURCES ${null_SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/zex_nullddi.cpp
    )
endif()

add_library(${TARGET_NAME}
    SHARED
        ${null_SOURCES}
)

target_include_directories(${TARGET_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(${TARGET_NAME}
    PRIVATE
        ZE_ENABLE_OCL_INTEROP=0
)

if(UNIX)
    set(GCC_COVERAGE_COMPILE_FLAGS "-fvisibility=hidden -fvisibility-inlines-hidden")
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
endif()