add_library(PlatoonConfiguration STATIC)

target_sources(PlatoonConfiguration
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/PlatoonConfiguration.cpp
        ${CMAKE_CURRENT_LIST_DIR}/PlatoonVisual.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/PlatoonConfiguration.hpp
        ${CMAKE_CURRENT_LIST_DIR}/PlatoonVisual.hpp
)

target_include_directories(PlatoonConfiguration
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(PlatoonConfiguration
    PRIVATE
        Qt6::Core
        Qt6::Widgets
        Qt6::Charts
        util
        saver
)

