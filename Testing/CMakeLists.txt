SET(PKG_PACKAGES_LOCATION D:/DEVELOPMENT/vcpkg/packages)
SET(GTest_DIR ${PKG_PACKAGES_LOCATION}/gtest_x64-windows/share/gtest) 

add_executable (TestingMain "TestingMain.cpp" "Modules/DriveOperations.cpp" "Modules/FolderTests.cpp" "Modules/DateTime.cpp" "Modules/Misc.cpp" "TestClasses/FilesT.h" "TestClasses/FilesT.cpp" "Modules/ToScanQueue.cpp" "Modules/FolderManager.cpp" "Modules/FileTests.cpp")
find_package(GTest CONFIG REQUIRED)

target_include_directories(TestingMain PUBLIC ${PKG_PACKAGES_LOCATION}/gtest_x64-windows/include)
target_link_libraries(TestingMain PRIVATE Library GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
