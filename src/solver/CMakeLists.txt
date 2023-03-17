add_library(solver STATIC)

target_sources(solver
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/solver.cpp
        ${CMAKE_CURRENT_LIST_DIR}/solverVisual.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/solver.hpp
        ${CMAKE_CURRENT_LIST_DIR}/solverVisual.hpp
)

target_include_directories(solver
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(solver
    PUBLIC
        Qt6::Core
        Qt6::Widgets
        Qt6::Charts
        util
        engine
        PlatoonConfiguration
        bridge
)
