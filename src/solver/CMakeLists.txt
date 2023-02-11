add_library(solver STATIC)
add_library(solverVisual STATIC)

target_sources(solver
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/solver.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/solver.hpp
)

target_sources(solverVisual
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/solverVisual.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/solverVisual.hpp
)

target_include_directories(solver
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

target_include_directories(solverVisual
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(solver
    PRIVATE
        Qt6::Core
        Qt6::Widgets
        Qt6::Charts
)

target_link_libraries(solverVisual
    PRIVATE
        Qt6::Core
        Qt6::Widgets
        Qt6::Charts
)

target_link_libraries(solver
    INTERFACE
        ${Matlab_ROOT_DIR}/extern/lib/win64/microsoft/libMatlabCppSharedLib.lib
        ${Matlab_ROOT_DIR}/extern/lib/win64/microsoft/libMatlabDataArray.lib
)

target_link_libraries(solverVisual
    INTERFACE
        ${Matlab_ROOT_DIR}/extern/lib/win64/microsoft/libMatlabCppSharedLib.lib
        ${Matlab_ROOT_DIR}/extern/lib/win64/microsoft/libMatlabDataArray.lib
)
