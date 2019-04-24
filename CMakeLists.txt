cmake_minimum_required(VERSION 3.2.0 FATAL_ERROR)
project(level_zero)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

#Define a path for custom commands to work around MSVC
set(CUSTOM_COMMAND_BINARY_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
if(MSVC)
    #MSVC implicitly adds $<CONFIG> to the output path
    set(CUSTOM_COMMAND_BINARY_DIR ${CUSTOM_COMMAND_BINARY_DIR}/$<CONFIG>)
endif()

if(UNIX)
    # Load GNUInstallDirs to determine install targets for Linux packages
    include(GNUInstallDirs)
endif()

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
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -fPIC")
endif()

#MSVC compile flags
if(MSVC)
    string(REPLACE "/MDd" "/MTd" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

    # treat warnings as errors
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX /W3 /wd4996")

    if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /we4189")
    endif()

    # enable multi-process compilation
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

add_definitions(-D_RELEASE_BUILD_WITH_REGKEYS)

set(XE_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

# Allow custom third_party folder
if(NOT DEFINED THIRD_PARTY_DIR)
    set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)
endif()

# Add AubStream support
if(NOT DEFINED AUB_STREAM_DIR)
    set(AUB_STREAM_DIR ${THIRD_PARTY_DIR}/aub_stream)
endif()
if(EXISTS ${AUB_STREAM_DIR}/aub_mem_dump/aub_stream.cpp)
    set(AUB_STREAM_SUPPORT TRUE)
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

if(NOT EXISTS ${COMPUTE_RUNTIME_DIR}/runtime/command_stream)
    message(FATAL_ERROR "COMPUTE_RUNTIME_DIR = Not found!")
endif()
message(STATUS "COMPUTE_RUNTIME_DIR = ${COMPUTE_RUNTIME_DIR}")

#Add I915 include dir
if (UNIX)
    if (NOT DEFINED I915_INCLUDES_DIR)
        get_filename_component(I915_INCLUDES_DIR
            "${COMPUTE_RUNTIME_DIR}/third_party/uapi" ABSOLUTE)
    endif()
endif()
# Option to disable tests
option(${PROJECT_NAME}_BUILD_TESTS "Build unit tests." ON)

add_subdirectory(${THIRD_PARTY_DIR})

include_directories(${COMPUTE_RUNTIME_DIR}/third_party/opencl_headers)

#enable compute_runtime
include(cmake/compute_runtime.cmake)

# Copy third_party_binaries to output BIN folder
add_custom_target(copy_third_party_files)

add_custom_command(
    TARGET copy_third_party_files
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${IGC_DIR}/lib" "${CUSTOM_COMMAND_BINARY_DIR}/"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${GMM_SOURCE_DIR}/lib" "${CUSTOM_COMMAND_BINARY_DIR}/"
    DEPENDS "${IGC_DIR}/lib" "${GMM_SOURCE_DIR}/lib"
)

add_subdirectory(core)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/core/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/core/source)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

if (${PROJECT_NAME}_BUILD_TESTS)
    add_subdirectory(tests)
    set_property(
        DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        PROPERTY
            VS_STARTUP_PROJECT ${PROJECT_NAME}_unit_tests
    )
endif()

add_subdirectory(icd_loader)

if(UNIX)
    include(CMakePackageConfigHelpers)
    configure_package_config_file(
        cmake/LevelZeroConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/LevelZeroConfig.cmake
        INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/level_zero"
        PATH_VARS CMAKE_INSTALL_INCLUDEDIR
        NO_CHECK_REQUIRED_COMPONENTS_MACRO)

    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/LevelZeroConfig.cmake
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/level_zero"
        COMPONENT loki-devel
    )
endif()

if(UNIX)
    if(DEFINED LOKI_CPACK_GENERATOR)
        set(CPACK_GENERATOR ${LOKI_CPACK_GENERATOR})
    else()
        # If generators list was not define build native package for current distro
        if(EXISTS "/etc/debian_version")
            set(CPACK_GENERATOR "DEB")

            set(file_path "/etc/lsb-release")
            if(EXISTS "${file_path}")
                file(STRINGS "${file_path}" data_list REGEX "^(DISTRIB_ID|DISTRIB_CODENAME)=")

                # Look for lines like "DISTRIB_ID="..." and DISTRIB_CODENAME="..."
                foreach(_var ${data_list})
                    if("${_var}" MATCHES "^(DISTRIB_ID)=(.*)$")
                        set(DEB_DISTRIB_ID "${CMAKE_MATCH_2}")
                    elseif("${_var}" MATCHES "^(DISTRIB_CODENAME)=(.*)$")
                        set(DEB_DISTRIB_CODENAME "${CMAKE_MATCH_2}")
                    endif()
                endforeach()
            endif()

        elseif(EXISTS "/etc/redhat-release")
          set(CPACK_GENERATOR "RPM")
        else()
          set(CPACK_GENERATOR "TXZ")
        endif()
    endif()

    set(CPACK_SET_DESTDIR TRUE)
    set(CPACK_PACKAGE_NAME "intel")
    set(CPACK_PACKAGE_CONTACT "Intel Corporation")
    set(CPACK_PACKAGE_ARCHITECTURE "x86_64")
    set(CPACK_PACKAGE_RELOCATABLE FALSE)

    set(CPACK_PACKAGE_VERSION_MAJOR 0)
    set(CPACK_PACKAGE_VERSION_MINOR 1)
    set(CPACK_PACKAGE_VERSION_PATCH 2)
    if(NOT DEFINED LOKI_VERSION_BUILD)
      set(LOKI_VERSION_BUILD 0)
    endif()

    set(CPACK_DEB_COMPONENT_INSTALL ON)
    set(CPACK_RPM_COMPONENT_INSTALL ON)
    set(CPACK_ARCHIVE_COMPONENT_INSTALL ON)

    set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
    # set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "postinst;postrm")
    # set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "http://01.org/compute-runtime")
    set(CPACK_DEBIAN_PACKAGE_RELEASE ${LOKI_VERSION_BUILD})
    set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

    set(CPACK_RPM_COMPRESSION_TYPE "xz")
    set(CPACK_RPM_PACKAGE_ARCHITECTURE "x86_64")
    set(CPACK_RPM_PACKAGE_AUTOREQ OFF)
    set(CPACK_RPM_PACKAGE_GROUP "System Environment/Libraries")
    set(CPACK_RPM_PACKAGE_LICENSE "Intel Confidential")
    set(CPACK_RPM_PACKAGE_RELEASE ${LOKI_VERSION_BUILD})
    set(CPACK_RPM_PACKAGE_RELEASE_DIST ON)
    # set(CPACK_RPM_PACKAGE_URL "http://01.org/compute-runtime")
    # set(CPACK_RPM_POST_INSTALL_SCRIPT_FILE "${IGDRCL_BINARY_DIR}/postinst")
    # set(CPACK_RPM_POST_UNINSTALL_SCRIPT_FILE "${IGDRCL_BINARY_DIR}/postrm")

    set(CPACK_COMPONENTS_ALL loki-core loki-devel loki-samples)

    set(LOKI_CORE_COMPONENT_NAME "${CPACK_PACKAGE_NAME}-loki-core")
    set(LOKI_PACKAGE_VERSION_DEB "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}-${CPACK_DEBIAN_PACKAGE_RELEASE}")
    set(LOKI_PACKAGE_VERSION_RPM "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}-${CPACK_RPM_PACKAGE_RELEASE}")

    if(IGDRCL__GMM_FOUND)
        list(APPEND _external_package_dependencies_deb "intel-gmmlib(=${IGDRCL__GMM_VERSION})")
        list(APPEND _external_package_dependencies_rpm "intel-gmmlib = ${IGDRCL__GMM_VERSION}")
    else()
        list(APPEND _external_package_dependencies_deb "intel-gmmlib")
        list(APPEND _external_package_dependencies_rpm "intel-gmmlib")
    endif()

    if(IGDRCL__IGC_FOUND)
        list(APPEND _external_package_dependencies_deb "intel-igc-opencl(=${IGDRCL__IGC_VERSION})")
        list(APPEND _external_package_dependencies_rpm "intel-igc-opencl = ${IGDRCL__IGC_VERSION}")
    else()
        list(APPEND _external_package_dependencies_deb "intel-igc-opencl")
        list(APPEND _external_package_dependencies_rpm "intel-igc-opencl")
    endif()

    string(REPLACE ";" ", " CPACK_DEBIAN_LOKI-CORE_PACKAGE_DEPENDS "${_external_package_dependencies_deb}")
    string(REPLACE ";" ", " CPACK_RPM_LOKI-CORE_PACKAGE_REQUIRES "${_external_package_dependencies_rpm}")
    set(CPACK_DEBIAN_LOKI-DEVEL_PACKAGE_DEPENDS "intel-loki-core(=${LOKI_PACKAGE_VERSION_DEB}) ")
    set(CPACK_DEBIAN_LOKI-SAMPLES_PACKAGE_DEPENDS "intel-loki-core(=${LOKI_PACKAGE_VERSION_DEB}) ")
    set(CPACK_RPM_LOKI-DEVEL_PACKAGE_REQUIRES "intel-loki-core = ${LOKI_PACKAGE_VERSION_RPM}")
    set(CPACK_RPM_LOKI-SAMPLES_PACKAGE_REQUIRES "intel-loki-core = ${LOKI_PACKAGE_VERSION_RPM}")

    set(CPACK_DEBIAN_LOKI-CORE_FILE_NAME "intel-loki-core_${LOKI_PACKAGE_VERSION_DEB}~${DEB_DISTRIB_CODENAME}_${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}.deb")
    set(CPACK_DEBIAN_LOKI-DEVEL_FILE_NAME "intel-loki-devel_${LOKI_PACKAGE_VERSION_DEB}~${DEB_DISTRIB_CODENAME}_${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}.deb")
    set(CPACK_DEBIAN_LOKI-SAMPLES_FILE_NAME "intel-loki-samples_${LOKI_PACKAGE_VERSION_DEB}~${DEB_DISTRIB_CODENAME}_${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}.deb")
    set(CPACK_RPM_LOKI-CORE_FILE_NAME "intel-loki-core-${LOKI_PACKAGE_VERSION_RPM}%{?dist}.${CPACK_RPM_PACKAGE_ARCHITECTURE}.rpm")
    set(CPACK_RPM_LOKI-DEVEL_FILE_NAME "intel-loki-devel-${CPACK_PACKAGE_VERSION_MAJOR}%{?dist}.${CPACK_RPM_PACKAGE_ARCHITECTURE}.rpm")
    set(CPACK_RPM_LOKI-SAMPLES_FILE_NAME "intel-loki-samples-${CPACK_PACKAGE_VERSION_MAJOR}%{?dist}.${CPACK_RPM_PACKAGE_ARCHITECTURE}.rpm")

    include(CPack)

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/ci/package_info.json.in ${CMAKE_BINARY_DIR}/package_info.json @ONLY)
endif()
