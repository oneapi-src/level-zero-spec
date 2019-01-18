# Add GoogleMock if we're building tests
if (${PROJECT_NAME}_build_tests)
    # Add googlemock support if not already added
    if (NOT TARGET gmock)
        #Allow custom googlemock directory
        if (NOT DEFINED GOOGLE_MOCK_DIR)
            set(GOOGLE_MOCK_DIR ${THIRD_PARTY_DIR}/googletest/googlemock)
        endif()
        
        # Ensure googlemock exists
        if (EXISTS "${GOOGLE_MOCK_DIR}/include/gmock")
            message(STATUS "GOOGLE_MOCK_DIR: ${GOOGLE_MOCK_DIR}")
            set(GOOGLETEST_VERSION 1.9.0)
            add_subdirectory(${GOOGLE_MOCK_DIR} EXCLUDE_FROM_ALL)

        else()
            message(STATUS "GOOGLE_MOCK_DIR: NOT FOUND.  Disabling tests.")
            set(${PROJECT_NAME}_build_tests FALSE)
        endif()
    endif()
endif()
