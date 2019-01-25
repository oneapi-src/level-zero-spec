set(TARGET_NAME xi)
add_library(${TARGET_NAME}
    STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
)

add_subdirectory(include)
add_subdirectory(source)