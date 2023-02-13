add_library(bridge STATIC)

target_sources(bridge
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/bridgeconfig.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/bridgeconfig.hpp
)

target_include_directories(bridge
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        ${PROJECT_SOURCE_DIR}/src/engine/
)

target_link_libraries(bridge
    PRIVATE
        Qt6::Core
        Qt6::Widgets
        Qt6::Charts
        engine
)

target_link_libraries(bridge
    INTERFACE
        ${Matlab_ROOT_DIR}/extern/lib/win64/microsoft/libMatlabCppSharedLib.lib
)
