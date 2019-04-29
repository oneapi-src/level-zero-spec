set(TARGET_NAME level_zero)

# Create our shared library/DLL
add_library(${TARGET_NAME}
    SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
        ${COMPUTE_RUNTIME_DIR}/runtime/dll/options.cpp
)

if(AUB_STREAM_SUPPORT)
    target_sources(${TARGET_NAME}
        PRIVATE
            $<TARGET_OBJECTS:aub_stream_all_hw>
    )
endif()

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

if(UNIX)
    target_sources(${TARGET_NAME}
        PRIVATE
            ${COMPUTE_RUNTIME_DIR}/runtime/dll/linux/drm_neo_create.cpp
    )
    set(OS_SPECIFIC_LIBS dl pthread)
    target_include_directories(${TARGET_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/source/os_interface/linux
        ${I915_INCLUDES_DIR}
    )
else()
    set(OS_SPECIFIC_LIBS "")
    target_include_directories(${TARGET_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/source/os_interface/windows
    )
endif()

target_link_libraries(${TARGET_NAME}
    compute_runtime_lib
    compute_runtime_lib_full
    ${OS_SPECIFIC_LIBS}
)

add_subdirectory(include)
add_subdirectory(source)

# Recreate ocloc as shared lib
get_target_property(OCLOC_SOURCES ocloc SOURCES)
get_target_property(OCLOC_INCLUDES ocloc INCLUDE_DIRECTORIES)
get_target_property(OCLOC_LIBRARY_DEPENDENCIES ocloc LINK_LIBRARIES)
get_target_property(OCLOC_COMPILE_DEFINITIONS ocloc COMPILE_DEFINITIONS)

add_library(ocloc_shared SHARED ${OCLOC_SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/source/ocloc_shared.cpp)
target_include_directories(ocloc_shared PRIVATE ${OCLOC_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(ocloc_shared ${OCLOC_LIBRARY_DEPENDENCIES})
target_compile_definitions(ocloc_shared PRIVATE ${OCLOC_COMPILE_DEFINITIONS} -DMOCKABLE_VIRTUAL= CL_USE_DEPRECATED_OPENCL_1_1_APIS CL_USE_DEPRECATED_OPENCL_1_2_APIS CL_USE_DEPRECATED_OPENCL_2_0_APIS CL_TARGET_OPENCL_VERSION=210)

set(OS_SPECIFIC_LIBS ${OS_SPECIFIC_LIBS} PARENT_SCOPE)

if(UNIX)
    install(TARGETS ${TARGET_NAME}
        DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}/level_zero
        COMPONENT loki-core)

    file(GLOB_RECURSE HEADER_FILES "include/*")
    list(REMOVE_ITEM HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/CMakeLists.txt")
    install(FILES ${HEADER_FILES}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/level_zero
        COMPONENT loki-devel
    )

    install(FILES source/ocloc_shared.h
        DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}
        COMPONENT loki-devel)
    install(TARGETS ocloc_shared
        DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
        COMPONENT loki-devel)
    file(GENERATE
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/intel.icd
        CONTENT "${CMAKE_INSTALL_FULL_LIBDIR}/level_zero/$<TARGET_FILE_NAME:${TARGET_NAME}>\n")
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/intel.icd
        DESTINATION /etc/intel/level_zero/icd.d
        COMPONENT loki-core)
endif()
