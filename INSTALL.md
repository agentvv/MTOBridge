Instructions for installing your software.  You should also include uninstall
instructions.

cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=TRUE -DCMAKE_MODULE_PATH="F:/Qt/6.4.0/mingw_64/lib/cmake" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DQT_DEBUG_FIND_PACKAGE=ON -Sf:/MTOBridge -Bf:/MTOBridge/build -G Ninja





set(CMAKE_PREFIX_PATH="F:/Qt/6.4.0/mingw_64/lib/cmake)

install(TARGETS engine gui ARCHIVE DESTINATION lib)
install(TARGETS MTOBridge RUNTIME DESTINATION bin)

include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_NAME "MTOBridge")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_VERSION_MAJOR 1)
set(CPACK_PACKAGE_VERSION_MINOR 0)
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)
set(CPACK_GENERATOR "ZIP")

include(CPack)