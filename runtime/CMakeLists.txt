add_library(runtime
    STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/stub.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/README.md
)

add_subdirectory(include)