# DO NOT EDIT: Generated from "scripts/templates/CMakeLists.cpp.mako"
include(gen9.cmake)
include(gen11.cmake)
include(gen12lp.cmake)
include(gen12hp.cmake)

SET(DEFAULT_PRODUCT_FAMILY  "${"$"}{DEFAULT_PRODUCT_FAMILY}" CACHE STRING "DEFAULT_PRODUCT_FAMILY" FORCE)
set(HW_SOURCES_ULT "${"$"}{HW_SOURCES_ULT}" CACHE STRING "HW_SOURCES_ULT" FORCE)

set(L0_RUNTIME_SOURCES
% for f in files:
    ${"$"}{CMAKE_CURRENT_SOURCE_DIR}/${f}
% endfor
)

# Make our source files visible to parent 
set(L0_RUNTIME_SOURCES "${"$"}{L0_RUNTIME_SOURCES}" CACHE STRING "L0_RUNTIME_SOURCES" FORCE)

target_include_directories(${"$"}{TARGET_NAME}
    PUBLIC
    ${"$"}{CMAKE_CURRENT_SOURCE_DIR}/
)

target_sources(${"$"}{TARGET_NAME}
    PRIVATE
        ${"$"}{L0_RUNTIME_SOURCES}
        ${"$"}{HW_SOURCES}
        ${"$"}{CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
        ${"$"}{CMAKE_CURRENT_SOURCE_DIR}/gen9.cmake
        ${"$"}{CMAKE_CURRENT_SOURCE_DIR}/gen11.cmake
        ${"$"}{CMAKE_CURRENT_SOURCE_DIR}/gen12hp.cmake
        ${"$"}{CMAKE_CURRENT_SOURCE_DIR}/gen12lp.cmake
)
