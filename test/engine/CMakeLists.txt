qt_add_executable(test_calculationcaller test_calculationcaller.cpp)
qt_add_executable(test_engine test_engine.cpp)
add_test(NAME test_calculationcaller COMMAND test_calculationcaller)
add_test(NAME test_engine COMMAND test_engine)

target_link_libraries(test_calculationcaller
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Charts
        Qt::Test
        engine
)

target_link_libraries(test_engine
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Charts
        Qt::Test
        engine
        ${Matlab_ROOT_DIR}/extern/lib/win64/libMatlabCppSharedLib.lib
)

add_custom_command(
        TARGET test_calculationcaller 
        POST_BUILD COMMAND "${QT_PATH}bin/windeployqt.exe" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)
