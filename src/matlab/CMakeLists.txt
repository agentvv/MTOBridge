add_library(matlab INTERFACE)

target_sources(matlab
    INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/mtobridge_matlab.hpp
)

target_link_libraries(matlab
    INTERFACE
        Matlab::MatlabDataArray
        ${Matlab_ROOT_DIR}/extern/lib/win64/libMatlabCppSharedLib.lib
)