add_library(saver STATIC)

target_sources(saver
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/saver.cpp
        ${CMAKE_CURRENT_LIST_DIR}/loader.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/saver.hpp
        ${CMAKE_CURRENT_LIST_DIR}/loader.hpp
)

target_include_directories(saver
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
      
)

target_link_libraries(saver
    PRIVATE
        Qt6::Core
        Qt6::Widgets
        Qt6::Charts
        
)

target_link_libraries(saver
    INTERFACE
        ${Matlab_ROOT_DIR}/extern/lib/win64/microsoft/libMatlabCppSharedLib.lib
)
