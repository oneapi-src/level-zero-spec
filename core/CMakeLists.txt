set(TARGET_NAME level_zero)

# Create our shared library/DLL
add_library(${TARGET_NAME}
    SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
)

target_include_directories(${TARGET_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${COMPUTE_RUNTIME_INCLUDES}
)

target_compile_definitions(${TARGET_NAME}
    PUBLIC
        XE_MAKEDLL
)

target_compile_definitions(${TARGET_NAME}
    PRIVATE
        ${COMPUTE_RUNTIME_DEFINITIONS}
)

target_link_libraries(${TARGET_NAME}
    compute_runtime_lib
    compute_runtime_lib_full
)

add_subdirectory(include)
add_subdirectory(source)