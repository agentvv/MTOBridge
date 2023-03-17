add_library(bridge STATIC)

target_sources(bridge
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/bridgeconfig.cpp
        ${CMAKE_CURRENT_LIST_DIR}/bridgevisual.cpp

    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/bridgeconfig.hpp
        ${CMAKE_CURRENT_LIST_DIR}/bridgevisual.hpp
)

target_include_directories(bridge
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(bridge
    PRIVATE
        Qt6::Core
        Qt6::Widgets
        Qt6::Charts
        util
        saver
)