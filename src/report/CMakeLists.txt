add_library(report STATIC)

target_sources(report
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/report.hpp
)

target_include_directories(report
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(report
    PRIVATE
        Qt6::Core
        Qt6::Widgets
        Qt6::Charts
        util
)