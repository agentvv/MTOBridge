add_library(engine SHARED)

target_sources(engine
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/engine.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/engine.hpp
)

target_include_directories(engine
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(engine
    PRIVATE
        pthread
        Qt6::Core
        Qt6::Widgets
        Qt6::Charts
        ${Matlab_ROOT_DIR}/extern/lib/win64/libMatlabCppSharedLib.lib
        Matlab::MatlabDataArray
)

target_include_directories(engine
    INTERFACE
        ${Matlab_ROOT_DIR}/extern/include/
)