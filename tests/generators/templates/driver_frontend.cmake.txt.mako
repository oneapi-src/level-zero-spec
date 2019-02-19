# DO NOT EDIT: Generated from "scripts/ult/generators/templates/driver_frontend.cmake.txt.mako"
set(driver_frontend_headers
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/CMakeLists.txt
% for f in driver_headers:
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/${f}
% endfor
)

set(driver_frontend_sources
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/CMakeLists.txt
% for f in driver_sources:
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/${f}
% endfor
)

set(driver_frontend_tests
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/CMakeLists.txt
% for f in driver_tests:
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/${f}
% endfor
)

include_directories(${"${XE_ROOT_DIR}"}/core/include)
include_directories(${"${XE_ROOT_DIR}"}/tests/unit_tests)
include_directories(${"${XE_ROOT_DIR}"}/third_party/googletest/googlemock/include)
include_directories(${"${XE_ROOT_DIR}"}/third_party/googletest/googletest/include)

add_library(driver_frontend ${"${driver_frontend_headers}"} ${"${driver_frontend_sources}"})
add_library(driver_frontend_ult ${"${driver_frontend_tests}"} ${"${driver_frontend_mocks}"})

add_executable(driver_frontend_ult_exe ../../unit_tests/main.cpp ${"${driver_frontend_tests}"} ${"${driver_frontend_mocks}"})
target_link_libraries(driver_frontend_ult_exe driver_frontend)
target_link_libraries(driver_frontend_ult_exe gmock)

