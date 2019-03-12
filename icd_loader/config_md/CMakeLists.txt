if(MSVC)
    # compute-samples require MD, since we can't predict what people will use, provide both
    string(REPLACE "/MTd" "/MDd" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    string(REPLACE "/MT"  "/MD"  CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
    string(REPLACE "/MT"  "/MD"  CMAKE_CXX_FLAGS_RELEASEINTERNAL "${CMAKE_CXX_FLAGS_RELEASEINTERNAL}")
    
    add_library(level_zero_icd_loader_MD
        "${CMAKE_CURRENT_SOURCE_DIR}/../icd_loader.cpp"
    )

    target_include_directories(level_zero_icd_loader_MD
        PUBLIC 
            "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    target_compile_definitions(level_zero_icd_loader_MD
        PRIVATE
            XE_MAKEDLL
    )
endif(MSVC)
