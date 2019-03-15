target_sources(${TARGET_NAME} PRIVATE
                              ${CMAKE_CURRENT_SOURCE_DIR}/mock_MemcpyBytes_Gen9core.cpp
                              ${CMAKE_CURRENT_SOURCE_DIR}/mock_MemcpyBytes_Gen12HPcore.cpp
                              ${CMAKE_CURRENT_SOURCE_DIR}/mock_Printf_Gen9core.cpp
                              ${CMAKE_CURRENT_SOURCE_DIR}/mock_Printf_Gen12HPcore.cpp
                              ${CMAKE_CURRENT_SOURCE_DIR}/mock_SlmBarrier_Gen9core.cpp
                              ${CMAKE_CURRENT_SOURCE_DIR}/mock_SlmBarrier_Gen12HPcore.cpp)
