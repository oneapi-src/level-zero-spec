cmake_minimum_required(VERSION 3.2.0 FATAL_ERROR)
project(level_zero)

if(MSVC)
    string(REPLACE "/MDd" "/MTd" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

    # treat warnings as errors
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX /W3 /we4189")
endif()

# Allow custom third_party folder
if(NOT DEFINED THIRD_PARTY_DIR)
    set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)
endif()

# Option to disable tests
option(${PROJECT_NAME}_build_tests "Build unit tests." ON)

add_subdirectory(${THIRD_PARTY_DIR})

if (${PROJECT_NAME}_build_tests)
    add_subdirectory(tests)
endif()