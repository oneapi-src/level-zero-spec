add_subdirectory(unit_tests)
add_subdirectory(black_box_tests)

if (MSVC)
    add_library(level_zero_icd_loader 
        generated/icd_loader/icd_loader.cpp
    )

    target_include_directories(level_zero_icd_loader 
        PUBLIC 
            generated/icd_loader
    )

    target_compile_definitions(level_zero_icd_loader
        PRIVATE
            XE_MAKEDLL
    )
endif()
