# DO NOT EDIT: Generated from "scripts/templates/CMakeLists.txt.mako"
include(gen8.cmake)
include(gen9.cmake)
include(gen10.cmake)
include(gen11.cmake)
include(gen12lp.cmake)
include(gen12hp.cmake)

set(L0_RUNTIME_SOURCES 
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/CMakeLists.txt
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/gen8.cmake
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/gen9.cmake
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/gen10.cmake
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/gen11.cmake
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/gen12hp.cmake
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/gen12lp.cmake
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/cl_interop.h
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/cmdgraph.h
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/cmdlist.cpp
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/cmdlist.h
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/cmdlist_hw.h
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/cmdlist_hw.inl
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/cmdlist_imp.cpp
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/cmdlist_imp.h
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/cmdqueue.cpp
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/cmdqueue.h
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/cmdqueue_hw.h
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/cmdqueue_hw.inl
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/cmdqueue_imp.h
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/common.h
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/copy.h
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/device.cpp
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/device.h
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/driver.cpp
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/driver.h
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/event.cpp
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/event.h
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/fence.cpp
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/fence.h
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/graphics_allocation.cpp
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/graphics_allocation.h
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/host.cpp
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/host.h
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/image.h
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/memory.cpp
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/memory.h
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/memory_manager.cpp
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/memory_manager.h
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/module.cpp
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/module.h
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/residency.h
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/semaphore.h
% for f in files:
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/${f}
% endfor
)

# Make our source files visible to parent 
set(L0_RUNTIME_SOURCES
    ${"${L0_RUNTIME_SOURCES}"}
    PARENT_SCOPE
)

target_sources(${"${TARGET_NAME}"}
    PRIVATE
        ${"${L0_RUNTIME_SOURCES}"}
)
