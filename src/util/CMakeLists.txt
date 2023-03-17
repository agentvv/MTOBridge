add_library(util INTERFACE)

target_include_directories(util 
	INTERFACE
		include
)

target_link_libraries(util
	INTERFACE
		Qt6::Core
)