cmake_minimum_required(VERSION 3.16)

project(MTOBridge VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -Wextra")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#set(CMAKE_CXX_CLANG_TIDY 
#    clang-tidy;
#    -checks="clang-diagnostic-*,clang-analyzer-*,modernize-*,-modernize-use-trailing-return-type,readability-*,-readability-magic-numbers,concurrency-*";
#    -header-filter="./src/.*"
#)
set(QT_PATH "F:/Qt/6.4.0/msvc2019_64/")
set(CMAKE_PREFIX_PATH ${QT_PATH})
set(CMAKE_PREFIX_PATH "${QT_PATH}lib/cmake")

find_package(Qt6 REQUIRED COMPONENTS 
    Core
    Widgets
    Charts
    Test
)

set(Matlab_ROOT_DIR "F:/Matlab/MATLAB Runtime/R2022b")
include_directories(engine
   ${Matlab_ROOT_DIR}/extern/include/
)

qt_standard_project_setup()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}
)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}
)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}
)

add_subdirectory(src)

enable_testing(true)
add_subdirectory(test)

set_property(
TARGET MTOBridge PROPERTY 
   WIN32_EXECUTABLE true
)
