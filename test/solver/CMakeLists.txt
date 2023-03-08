qt_add_executable(test_solver test_solver.cpp)
add_test(NAME test_solver COMMAND test_solver)

target_link_libraries(test_solver
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Charts
        Qt::Test
        solver
)
