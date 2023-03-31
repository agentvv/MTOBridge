add_library(util STATIC)

target_sources(util
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/data_types.cpp
)

target_include_directories(util 
	PUBLIC
		include
)

target_link_libraries(util
	PUBLIC
		Qt6::Core
)