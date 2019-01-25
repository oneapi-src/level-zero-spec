cmake_minimum_required(VERSION 3.2.0 FATAL_ERROR)
project(level_zero)

# Add compute runtime support
if(NOT DEFINED COMPUTE_RUNTIME_DIR)
    set(COMPUTE_RUNTIME_DIR ${THIRD_PARTY_DIR}/compute_runtime)
endif()

set(COMPUTE_RUNTIME_SUPPORT TRUE)
if(NOT EXISTS ${COMPUTE_RUNTIME_DIR}/runtime/command_stream)
    set(COMPUTE_RUNTIME_SUPPORT FALSE)
    set(COMPUTE_RUNTIME_DIR "Not found!")
endif() 
message(STATUS "COMPUTE_RUNTIME_DIR = ${COMPUTE_RUNTIME_DIR}")

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

# Option to disable tests
option(${PROJECT_NAME}_build_tests "Build unit tests." ON)

add_subdirectory(${THIRD_PARTY_DIR})

add_subdirectory(core)
add_subdirectory(extended)

if(COMPUTE_RUNTIME_SUPPORT)
    add_subdirectory(${COMPUTE_RUNTIME_DIR} ${PROJECT_BINARY_DIR}/compute-runtime EXCLUDE_FROM_ALL)
endif(COMPUTE_RUNTIME_SUPPORT)

if (${PROJECT_NAME}_build_tests)
    add_subdirectory(tests)
endif()