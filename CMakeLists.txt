cmake_minimum_required(VERSION 3.2.0 FATAL_ERROR)
project(level_zero)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

#CXX compiler support
if(NOT MSVC)
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
    CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
    if(COMPILER_SUPPORTS_CXX14)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    elseif(COMPILER_SUPPORTS_CXX0X)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
    else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++14 support.  Please use a different C++ compiler.")
    endif()
endif()

#MSVC compile flags
if(MSVC)
    string(REPLACE "/MDd" "/MTd" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

    # treat warnings as errors
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX /W3 /wd4996")
endif()

# Allow custom third_party folder
if(NOT DEFINED THIRD_PARTY_DIR)
    set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)
endif()

# Add compute runtime support
if(NOT DEFINED COMPUTE_RUNTIME_DIR)
    set(COMPUTE_RUNTIME_DIR ${THIRD_PARTY_DIR}/compute_runtime)
    set(IGC_DIR ${THIRD_PARTY_DIR}/igc)
    set(GMM_SOURCE_DIR ${THIRD_PARTY_DIR}/gmmlib)

    if(NOT UNIX)
        set(WDK_DIR ${THIRD_PARTY_DIR}/wdk)
    endif()
endif()

set(COMPUTE_RUNTIME_SUPPORT TRUE)
if(NOT EXISTS ${COMPUTE_RUNTIME_DIR}/runtime/command_stream)
    set(COMPUTE_RUNTIME_SUPPORT FALSE)
    set(COMPUTE_RUNTIME_DIR "Not found!")
endif() 
message(STATUS "COMPUTE_RUNTIME_DIR = ${COMPUTE_RUNTIME_DIR}")

# Option to disable tests
option(${PROJECT_NAME}_BUILD_TESTS "Build unit tests." ON)

add_subdirectory(${THIRD_PARTY_DIR})
add_subdirectory(core)
#TODO: Re-enable once source files added to extended
#add_subdirectory(extended)

if(COMPUTE_RUNTIME_SUPPORT)
    set(DISABLED_GTPIN_SUPPORT TRUE)
    add_subdirectory(${COMPUTE_RUNTIME_DIR} ${PROJECT_BINARY_DIR}/compute-runtime EXCLUDE_FROM_ALL)

    include(compute_runtime.cmake)
endif(COMPUTE_RUNTIME_SUPPORT)

if (${PROJECT_NAME}_BUILD_TESTS)
    add_subdirectory(tests)
    set_property(
        DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        PROPERTY
            VS_STARTUP_PROJECT ${PROJECT_NAME}_unit_tests
    )
endif()
