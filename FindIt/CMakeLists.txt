SET(PKG_PACKAGES_LOCATION D:/DEVELOPMENT/vcpkg/packages)
SET(SQLiteCpp_DIR ${PKG_PACKAGES_LOCATION}/sqlitecpp_x64-windows/share/SQLiteCpp) 
SET(unofficial-sqlite3_DIR ${PKG_PACKAGES_LOCATION}/sqlite3_x64-windows/share/unofficial-sqlite3)

add_executable (FindIt "Main.cpp" "Code.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET FindIt PROPERTY CXX_STANDARD 20)
endif()

find_package(SQLiteCpp CONFIG REQUIRED)

target_include_directories(FindIt PUBLIC ${PKG_PACKAGES_LOCATION}/sqlite3_x64-windows/include)
target_include_directories(FindIt PUBLIC ${PKG_PACKAGES_LOCATION}/sqlitecpp_x64-windows/include)
link_directories(${PKG_PACKAGES_LOCATION}/sqlite3_x64-windows/lib)

target_link_libraries(FindIt Library)
# target_link_libraries(FindIt sqlite3 SQLiteCpp pthread dl)
