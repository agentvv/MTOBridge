cmake_minimum_required(VERSION 3.16)

project(test VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -Wextra")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_PREFIX_PATH ${QT_PATH})
set(CMAKE_PREFIX_PATH "${QT_PATH}lib/cmake")
set(CTEST_OUTPUT_ON_FAILURE ON)

find_package(Qt6 REQUIRED COMPONENTS 
    Core
    Widgets
    Charts
    Test
)

enable_testing()

add_subdirectory(engine)

