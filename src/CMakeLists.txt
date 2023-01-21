qt_add_executable(MTOBridge "main.cpp")



add_subdirectory("engine")
add_subdirectory("gui")
add_subdirectory("matlab")

target_link_libraries(MTOBridge
        PUBLIC
        Qt6::Core
        Qt6::Widgets
        Qt6::Charts
        ${Matlab_ROOT_DIR}/extern/lib/win64/libMatlabCppSharedLib.lib
        engine
        gui
        matlab
)

add_custom_command(
        TARGET MTOBridge POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/src/matlab/mtobridge_matlab.ctf
                ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/mtobridge_matlab.ctf)

add_custom_command(
        TARGET MTOBridge POST_BUILD
        COMMAND "${QT_PATH}bin/windeployqt.exe" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})