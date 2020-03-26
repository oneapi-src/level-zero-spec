set(TARGET_NAME ze_loader)

set(loader_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/ze_object.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ze_loader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ze_loader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ze_ldrddi.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ze_ldrddi.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zet_ldrddi.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zet_ldrddi.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zes_ldrddi.h
    ${CMAKE_CURRENT_SOURCE_DIR}/zes_ldrddi.cpp
)
if(ZE_EXPERIMENTAL)
    set(loader_SOURCES ${loader_SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/zex_ldrddi.h
        ${CMAKE_CURRENT_SOURCE_DIR}/zex_ldrddi.cpp
    )
endif()

add_library(${TARGET_NAME}
    SHARED
        ${loader_SOURCES}
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