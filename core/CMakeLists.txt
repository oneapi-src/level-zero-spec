set(TARGET_NAME xe)

add_library(${TARGET_NAME}
    STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
)

target_include_directories(${TARGET_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(include)
add_subdirectory(source)