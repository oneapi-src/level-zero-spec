# DO NOT EDIT: Generated from "scripts/templates/CMakeLists.txt.mako"
target_sources(${"${TARGET_NAME}"}
    PRIVATE
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/CMakeLists.txt
% for f in files:
    ${"${CMAKE_CURRENT_SOURCE_DIR}"}/${f}
% endfor
)
