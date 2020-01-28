<%
    x=tags['$x']
    X=x.upper()

    TARGET_NAME="${TARGET_NAME}"
    CMAKE_CURRENT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}"

%>set(TARGET_NAME ${n}_api_cpp)

add_library(${TARGET_NAME}
    STATIC
    %for f in files:
        ${CMAKE_CURRENT_SOURCE_DIR}/${f}
    %endfor
)

target_include_directories(${TARGET_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(${TARGET_NAME}
    PRIVATE
        ${X}_ENABLE_OCL_INTEROP=0
)

if(WIN32)
target_link_libraries(${TARGET_NAME}
    ${x}_api ${n}_api
)
else()
target_link_libraries(${TARGET_NAME}
    ${x}_api ${n}_api dl
)
endif()
