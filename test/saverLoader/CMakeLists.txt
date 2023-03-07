qt_add_executable(test_saver test_saver.cpp)
add_test(NAME test_saver COMMAND test_saver)

target_link_libraries(test_saver
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Charts
        Qt::Test
        engine
        saver
        ${Matlab_ROOT_DIR}/extern/lib/win64/libMatlabCppSharedLib.lib
)




