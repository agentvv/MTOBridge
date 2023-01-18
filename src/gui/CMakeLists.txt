add_library(gui SHARED "")

target_sources(gui
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/window.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/window.hpp
)

target_include_directories(gui
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        ${PROJECT_SOURCE_DIR}/src/engine/
)

target_link_libraries(gui
    PRIVATE
        pthread
        Qt6::Core
        Qt6::Widgets
        Qt6::Charts
        ${Matlab_ROOT_DIR}/extern/lib/win64/libMatlabCppSharedLib.lib
        Matlab::MatlabDataArray
        engine
)

