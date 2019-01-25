add_library(xi
    STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
)

add_subdirectory(include)
add_subdirectory(source)