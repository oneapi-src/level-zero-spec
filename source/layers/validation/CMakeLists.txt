set(TARGET_NAME ze_validation_layer)

add_library(${TARGET_NAME}
    SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_layer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_layer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_valddi.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zet_valddi.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zes_valddi.cpp
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