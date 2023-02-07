add_library(report STATIC)

target_sources(report
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/reportpage.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/reportpage.hpp
)

target_include_directories(report
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(report
    PRIVATE
        Qt6::Core
        Qt6::Widgets
        Qt6::Charts
)

target_link_libraries(report
    INTERFACE
        ${Matlab_ROOT_DIR}/extern/lib/win64/microsoft/libMatlabCppSharedLib.lib
        ${Matlab_ROOT_DIR}/extern/lib/win64/microsoft/libMatlabDataArray.lib
)

