add_library(engine STATIC)

target_sources(engine
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/engine.cpp
        ${CMAKE_CURRENT_LIST_DIR}/calculationcaller.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/engine.hpp
        ${CMAKE_CURRENT_LIST_DIR}/calculationcaller.hpp
)

target_include_directories(engine
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(engine
    PUBLIC
        Qt6::Core
        Qt6::Widgets
        Qt6::Charts
        util
)

target_link_libraries(engine
    INTERFACE
        ${Matlab_ROOT_DIR}/extern/lib/win64/microsoft/libMatlabCppSharedLib.lib
        ${Matlab_ROOT_DIR}/extern/lib/win64/microsoft/libMatlabDataArray.lib
)

