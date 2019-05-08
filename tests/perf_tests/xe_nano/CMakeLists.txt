# Copyright (c) 2019, Intel Corporation
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
# THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
# OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
# ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.
#
if(UNIX)
    set(OS_SPECIFIC_LIBS "")

    set(PAPI_LIB papi)
    find_library(PAPI_LIB_PATH ${PAPI_LIB})
    if(PAPI_LIB_PATH)
      set(XE_NANO_COMMON src/hardware_counter/hardware_counter_support.cpp)
      set(OS_SPECIFIC_LIBS ${OS_SPECIFIC_LIBS} ${PAPI_LIB})
    else()
      message(WARNING
	      "papi library not found. It is required for xe_nano benchmarks.")
      set(XE_NANO_COMMON src/hardware_counter/hardware_counter_stub.cpp)
    endif()
else()
    set(OS_SPECIFIC_LIBS "")
    set(XE_NANO_COMMON src/hardware_counter/hardware_counter_stub.cpp)
endif()

set(CMAKE_CXX_STANDARD "11")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(XE_NANO_COMMON
    ${XE_NANO_COMMON}
    src/xe_app.cpp
    src/api_static_probe.cpp
)

set(XE_NANO_BENCHMARKS
    src/xe_nano.cpp
    src/benchmark.cpp
)

add_executable(xe_nano ${XE_NANO_COMMON} ${XE_NANO_BENCHMARKS})

add_dependencies(xe_nano copy_third_party_files ocloc_shared)

target_link_libraries(xe_nano level_zero_icd_loader ${OS_SPECIFIC_LIBS})

target_include_directories(xe_nano PRIVATE "include")

add_custom_command(
        TARGET xe_nano POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/tests/perf_tests/xe_nano/kernels/xe_nano_benchmarks.spv
                ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/xe_nano_benchmarks.spv)

if(UNIX)
    install(TARGETS xe_nano
        DESTINATION ${CMAKE_INSTALL_FULL_BINDIR}
        COMPONENT loki-xe-nano
    )
    install(
        FILES
            "${CMAKE_CURRENT_SOURCE_DIR}/kernels/xe_nano_benchmarks.spv"
        DESTINATION ${CMAKE_INSTALL_FULL_BINDIR}
        COMPONENT loki-xe-nano
    )
endif()

if(MSVC)
    set_target_properties(xe_nano
        PROPERTIES
            VS_DEBUGGER_COMMAND_ARGUMENTS ""
            VS_DEBUGGER_WORKING_DIRECTORY "$(OutDir)"
    )
endif()
