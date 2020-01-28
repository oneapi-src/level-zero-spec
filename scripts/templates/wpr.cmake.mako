<%
    x=tags['$x']
    X=x.upper()

    TARGET_NAME="${TARGET_NAME}"
    CMAKE_CURRENT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
    CMAKE_DL_LIBS="${CMAKE_DL_LIBS}"

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

target_link_libraries(${TARGET_NAME}
    ${x}_api ${n}_api
    ${CMAKE_DL_LIBS}
)
