
SET(PKG_PACKAGES_LOCATION D:/DEVELOPMENT/vcpkg/packages)
SET(SQLiteCpp_DIR ${PKG_PACKAGES_LOCATION}/sqlitecpp_x64-windows/share/SQLiteCpp) 
SET(unofficial-sqlite3_DIR ${PKG_PACKAGES_LOCATION}/sqlite3_x64-windows/share/unofficial-sqlite3)
SET(cryptopp_DIR ${PKG_PACKAGES_LOCATION}/cryptopp_x64-windows/share/cryptopp)
SET(BOOST_ROOT ${PKG_PACKAGES_LOCATION})
SET(date_DIR ${PKG_PACKAGES_LOCATION}/date_x64-windows/share/date)

#list(APPEND CMAKE_PREFIX_PATH "D:/DEVELOPMENT/vcpkg/packages/boost-headers_x64-windows")
list(APPEND CMAKE_PREFIX_PATH
	${BOOST_ROOT}/boost_x64-windows/share/
	${BOOST_ROOT}/boost-accumulators_x64-windows/share/
	${BOOST_ROOT}/boost-algorithm_x64-windows/share/
	${BOOST_ROOT}/boost-align_x64-windows/share/
	${BOOST_ROOT}/boost-any_x64-windows/share/
	${BOOST_ROOT}/boost-array_x64-windows/share/
	${BOOST_ROOT}/boost-asio_x64-windows/share/
	${BOOST_ROOT}/boost-assert_x64-windows/share/
	${BOOST_ROOT}/boost-assign_x64-windows/share/
	${BOOST_ROOT}/boost-atomic_x64-windows/share/
	${BOOST_ROOT}/boost-beast_x64-windows/share/
	${BOOST_ROOT}/boost-bimap_x64-windows/share/
	${BOOST_ROOT}/boost-bind_x64-windows/share/
	${BOOST_ROOT}/boost-callable-traits_x64-windows/share/
	${BOOST_ROOT}/boost-charconv_x64-windows/share/
	${BOOST_ROOT}/boost-chrono_x64-windows/share/
	${BOOST_ROOT}/boost-circular-buffer_x64-windows/share/
	${BOOST_ROOT}/boost-cmake_x64-windows/share/
	${BOOST_ROOT}/boost-cobalt_x64-windows/share/
	${BOOST_ROOT}/boost-compat_x64-windows/share/
	${BOOST_ROOT}/boost-compatibility_x64-windows/share/
	${BOOST_ROOT}/boost-compute_x64-windows/share/
	${BOOST_ROOT}/boost-concept-check_x64-windows/share/
	${BOOST_ROOT}/boost-config_x64-windows/share/
	${BOOST_ROOT}/boost-container_x64-windows/share/
	${BOOST_ROOT}/boost-container-hash_x64-windows/share/
	${BOOST_ROOT}/boost-context_x64-windows/share/
	${BOOST_ROOT}/boost-contract_x64-windows/share/
	${BOOST_ROOT}/boost-conversion_x64-windows/share/
	${BOOST_ROOT}/boost-convert_x64-windows/share/
	${BOOST_ROOT}/boost-core_x64-windows/share/
	${BOOST_ROOT}/boost-coroutine_x64-windows/share/
	${BOOST_ROOT}/boost-coroutine2_x64-windows/share/
	${BOOST_ROOT}/boost-crc_x64-windows/share/
	${BOOST_ROOT}/boost-date-time_x64-windows/share/
	${BOOST_ROOT}/boost-describe_x64-windows/share/
	${BOOST_ROOT}/boost-detail_x64-windows/share/
	${BOOST_ROOT}/boost-dll_x64-windows/share/
	${BOOST_ROOT}/boost-dynamic-bitset_x64-windows/share/
	${BOOST_ROOT}/boost-endian_x64-windows/share/
	${BOOST_ROOT}/boost-exception_x64-windows/share/
	${BOOST_ROOT}/boost-fiber_x64-windows/share/
	${BOOST_ROOT}/boost-filesystem_x64-windows/share/
	${BOOST_ROOT}/boost-flyweight_x64-windows/share/
	${BOOST_ROOT}/boost-foreach_x64-windows/share/
	${BOOST_ROOT}/boost-format_x64-windows/share/
	${BOOST_ROOT}/boost-function_x64-windows/share/
	${BOOST_ROOT}/boost-function-types_x64-windows/share/
	${BOOST_ROOT}/boost-functional_x64-windows/share/
	${BOOST_ROOT}/boost-fusion_x64-windows/share/
	${BOOST_ROOT}/boost-geometry_x64-windows/share/
	${BOOST_ROOT}/boost-gil_x64-windows/share/
	${BOOST_ROOT}/boost-graph_x64-windows/share/
	${BOOST_ROOT}/boost-hana_x64-windows/share/
	${BOOST_ROOT}/boost-headers_x64-windows/share/
	${BOOST_ROOT}/boost-heap_x64-windows/share/
	${BOOST_ROOT}/boost-histogram_x64-windows/share/
	${BOOST_ROOT}/boost-hof_x64-windows/share/
	${BOOST_ROOT}/boost-icl_x64-windows/share/
	${BOOST_ROOT}/boost-integer_x64-windows/share/
	${BOOST_ROOT}/boost-interprocess_x64-windows/share/
	${BOOST_ROOT}/boost-interval_x64-windows/share/
	${BOOST_ROOT}/boost-intrusive_x64-windows/share/
	${BOOST_ROOT}/boost-io_x64-windows/share/
	${BOOST_ROOT}/boost-iostreams_x64-windows/share/
	${BOOST_ROOT}/boost-iterator_x64-windows/share/
	${BOOST_ROOT}/boost-json_x64-windows/share/
	${BOOST_ROOT}/boost-lambda_x64-windows/share/
	${BOOST_ROOT}/boost-lambda2_x64-windows/share/
	${BOOST_ROOT}/boost-leaf_x64-windows/share/
	${BOOST_ROOT}/boost-lexical-cast_x64-windows/share/
	${BOOST_ROOT}/boost-local-function_x64-windows/share/
	${BOOST_ROOT}/boost-locale_x64-windows/share/
	${BOOST_ROOT}/boost-lockfree_x64-windows/share/
	${BOOST_ROOT}/boost-log_x64-windows/share/
	${BOOST_ROOT}/boost-logic_x64-windows/share/
	${BOOST_ROOT}/boost-math_x64-windows/share/
	${BOOST_ROOT}/boost-metaparse_x64-windows/share/
	${BOOST_ROOT}/boost-move_x64-windows/share/
	${BOOST_ROOT}/boost-mp11_x64-windows/share/
	${BOOST_ROOT}/boost-mpl_x64-windows/share/
	${BOOST_ROOT}/boost-msm_x64-windows/share/
	${BOOST_ROOT}/boost-multi-array_x64-windows/share/
	${BOOST_ROOT}/boost-multi-index_x64-windows/share/
	${BOOST_ROOT}/boost-multiprecision_x64-windows/share/
	${BOOST_ROOT}/boost-mysql_x64-windows/share/
	${BOOST_ROOT}/boost-nowide_x64-windows/share/
	${BOOST_ROOT}/boost-numeric-conversion_x64-windows/share/
	${BOOST_ROOT}/boost-odeint_x64-windows/share/
	${BOOST_ROOT}/boost-optional_x64-windows/share/
	${BOOST_ROOT}/boost-outcome_x64-windows/share/
	${BOOST_ROOT}/boost-parameter_x64-windows/share/
	${BOOST_ROOT}/boost-parameter-python_x64-windows/share/
	${BOOST_ROOT}/boost-pfr_x64-windows/share/
	${BOOST_ROOT}/boost-phoenix_x64-windows/share/
	${BOOST_ROOT}/boost-poly-collection_x64-windows/share/
	${BOOST_ROOT}/boost-polygon_x64-windows/share/
	${BOOST_ROOT}/boost-pool_x64-windows/share/
	${BOOST_ROOT}/boost-predef_x64-windows/share/
	${BOOST_ROOT}/boost-preprocessor_x64-windows/share/
	${BOOST_ROOT}/boost-process_x64-windows/share/
	${BOOST_ROOT}/boost-program-options_x64-windows/share/
	${BOOST_ROOT}/boost-property-map_x64-windows/share/
	${BOOST_ROOT}/boost-property-tree_x64-windows/share/
	${BOOST_ROOT}/boost-proto_x64-windows/share/
	${BOOST_ROOT}/boost-ptr-container_x64-windows/share/
	${BOOST_ROOT}/boost-python_x64-windows/share/
	${BOOST_ROOT}/boost-qvm_x64-windows/share/
	${BOOST_ROOT}/boost-random_x64-windows/share/
	${BOOST_ROOT}/boost-range_x64-windows/share/
	${BOOST_ROOT}/boost-ratio_x64-windows/share/
	${BOOST_ROOT}/boost-rational_x64-windows/share/
	${BOOST_ROOT}/boost-redis_x64-windows/share/
	${BOOST_ROOT}/boost-regex_x64-windows/share/
	${BOOST_ROOT}/boost-safe-numerics_x64-windows/share/
	${BOOST_ROOT}/boost-scope_x64-windows/share/
	${BOOST_ROOT}/boost-scope-exit_x64-windows/share/
	${BOOST_ROOT}/boost-serialization_x64-windows/share/
	${BOOST_ROOT}/boost-signals2_x64-windows/share/
	${BOOST_ROOT}/boost-smart-ptr_x64-windows/share/
	${BOOST_ROOT}/boost-sort_x64-windows/share/
	${BOOST_ROOT}/boost-spirit_x64-windows/share/
	${BOOST_ROOT}/boost-stacktrace_x64-windows/share/
	${BOOST_ROOT}/boost-statechart_x64-windows/share/
	${BOOST_ROOT}/boost-static-assert_x64-windows/share/
	${BOOST_ROOT}/boost-static-string_x64-windows/share/
	${BOOST_ROOT}/boost-stl-interfaces_x64-windows/share/
	${BOOST_ROOT}/boost-system_x64-windows/share/
	${BOOST_ROOT}/boost-test_x64-windows/share/
	${BOOST_ROOT}/boost-thread_x64-windows/share/
	${BOOST_ROOT}/boost-throw-exception_x64-windows/share/
	${BOOST_ROOT}/boost-timer_x64-windows/share/
	${BOOST_ROOT}/boost-tokenizer_x64-windows/share/
	${BOOST_ROOT}/boost-tti_x64-windows/share/
	${BOOST_ROOT}/boost-tuple_x64-windows/share/
	${BOOST_ROOT}/boost-type-erasure_x64-windows/share/
	${BOOST_ROOT}/boost-type-index_x64-windows/share/
	${BOOST_ROOT}/boost-type-traits_x64-windows/share/
	${BOOST_ROOT}/boost-typeof_x64-windows/share/
	${BOOST_ROOT}/boost-ublas_x64-windows/share/
	${BOOST_ROOT}/boost-uninstall_x64-windows/share/
	${BOOST_ROOT}/boost-units_x64-windows/share/
	${BOOST_ROOT}/boost-unordered_x64-windows/share/
	${BOOST_ROOT}/boost-url_x64-windows/share/
	${BOOST_ROOT}/boost-utility_x64-windows/share/
	${BOOST_ROOT}/boost-uuid_x64-windows/share/
	${BOOST_ROOT}/boost-variant_x64-windows/share/
	${BOOST_ROOT}/boost-variant2_x64-windows/share/
	${BOOST_ROOT}/boost-vmd_x64-windows/share/
	${BOOST_ROOT}/boost-wave_x64-windows/share/
	${BOOST_ROOT}/boost-winapi_x64-windows/share/
	${BOOST_ROOT}/boost-xpressive_x64-windows/share/
	${BOOST_ROOT}/boost-yap_x64-windows/share/
)


#SET(Boost_INCLUDE_DIRS "D:/DEVELOPMENT/vcpkg/packages/boost-headers_x64-windows")

find_package(SQLiteCpp CONFIG REQUIRED)
find_package(cryptopp CONFIG REQUIRED)
find_package(Boost COMPONENTS filesystem REQUIRED)
find_package(date CONFIG REQUIRED)

# https://cmake.org/cmake/help/latest/module/FindBoost.html
# find_package() above sets:
# Boost_INCLUDE_DIRS
# Boost_LIBRARY_DIRS
# Boost_LIBRARIES 

link_directories(${BOOST_LIBRARY_DIR})


list(APPEND BUILD_FILES "Entities/Drive.cpp" "Entities/Folder.cpp" "Entities/Category.cpp" "Entities/ToScanQueueItem.cpp") 
# list(APPEND BUILD_FILES "Entities/File.cpp") 
list(APPEND BUILD_FILES "InMemoryDB/Drives.cpp" "InMemoryDB/Categories.cpp" ) 
list(APPEND BUILD_FILES "InMemoryDB/ToScanQueue.cpp" "InMemoryDB/Drives.cpp" "InMemoryDB/Files.cpp" "InMemoryDB/Folders.cpp")
list(APPEND BUILD_FILES "Utils/DateTime.cpp" "Utils/Encryption.cpp")
add_library (Library ${BUILD_FILES} "Db/Operations.cpp" "Utils/DriveOperations.cpp" "Utils/DriveOperations.h" "Entities/File.cpp" "InMemoryDB/FolderManager.h" "InMemoryDB/FolderManager.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Library PROPERTY CXX_STANDARD 20)
endif()


target_include_directories(Library PUBLIC ${PKG_PACKAGES_LOCATION}/sqlite3_x64-windows/include)
target_include_directories(Library PUBLIC ${PKG_PACKAGES_LOCATION}/sqlitecpp_x64-windows/include)
target_include_directories(Library PUBLIC ${PKG_PACKAGES_LOCATION}/cryptopp_x64-windows/include)
target_include_directories(Library PUBLIC ${PKG_PACKAGES_LOCATION}/boost-filesystem_x64-windows/include)
target_include_directories(Library PUBLIC ${PKG_PACKAGES_LOCATION}/boost-system_x64-windows/include)
target_link_libraries(Library sqlite3 SQLiteCpp cryptopp::cryptopp Boost::boost Boost::filesystem date::date date::date-tz)


target_include_directories(Library PUBLIC 
	# this is insanity. there must be an alternative approach.
	# of course, I created the below list using a tool!

	${BOOST_ROOT}/boost_x64-windows/include
	${BOOST_ROOT}/boost-accumulators_x64-windows/include
	${BOOST_ROOT}/boost-algorithm_x64-windows/include
	${BOOST_ROOT}/boost-align_x64-windows/include
	${BOOST_ROOT}/boost-any_x64-windows/include
	${BOOST_ROOT}/boost-array_x64-windows/include
	${BOOST_ROOT}/boost-asio_x64-windows/include
	${BOOST_ROOT}/boost-assert_x64-windows/include
	${BOOST_ROOT}/boost-assign_x64-windows/include
	${BOOST_ROOT}/boost-atomic_x64-windows/include
	${BOOST_ROOT}/boost-beast_x64-windows/include
	${BOOST_ROOT}/boost-bimap_x64-windows/include
	${BOOST_ROOT}/boost-bind_x64-windows/include
	${BOOST_ROOT}/boost-callable-traits_x64-windows/include
	${BOOST_ROOT}/boost-charconv_x64-windows/include
	${BOOST_ROOT}/boost-chrono_x64-windows/include
	${BOOST_ROOT}/boost-circular-buffer_x64-windows/include
	${BOOST_ROOT}/boost-cmake_x64-windows/include
	${BOOST_ROOT}/boost-cobalt_x64-windows/include
	${BOOST_ROOT}/boost-compat_x64-windows/include
	${BOOST_ROOT}/boost-compatibility_x64-windows/include
	${BOOST_ROOT}/boost-compute_x64-windows/include
	${BOOST_ROOT}/boost-concept-check_x64-windows/include
	${BOOST_ROOT}/boost-config_x64-windows/include
	${BOOST_ROOT}/boost-container_x64-windows/include
	${BOOST_ROOT}/boost-container-hash_x64-windows/include
	${BOOST_ROOT}/boost-context_x64-windows/include
	${BOOST_ROOT}/boost-contract_x64-windows/include
	${BOOST_ROOT}/boost-conversion_x64-windows/include
	${BOOST_ROOT}/boost-convert_x64-windows/include
	${BOOST_ROOT}/boost-core_x64-windows/include
	${BOOST_ROOT}/boost-coroutine_x64-windows/include
	${BOOST_ROOT}/boost-coroutine2_x64-windows/include
	${BOOST_ROOT}/boost-crc_x64-windows/include
	${BOOST_ROOT}/boost-date-time_x64-windows/include
	${BOOST_ROOT}/boost-describe_x64-windows/include
	${BOOST_ROOT}/boost-detail_x64-windows/include
	${BOOST_ROOT}/boost-dll_x64-windows/include
	${BOOST_ROOT}/boost-dynamic-bitset_x64-windows/include
	${BOOST_ROOT}/boost-endian_x64-windows/include
	${BOOST_ROOT}/boost-exception_x64-windows/include
	${BOOST_ROOT}/boost-fiber_x64-windows/include
	${BOOST_ROOT}/boost-filesystem_x64-windows/include
	${BOOST_ROOT}/boost-flyweight_x64-windows/include
	${BOOST_ROOT}/boost-foreach_x64-windows/include
	${BOOST_ROOT}/boost-format_x64-windows/include
	${BOOST_ROOT}/boost-function_x64-windows/include
	${BOOST_ROOT}/boost-function-types_x64-windows/include
	${BOOST_ROOT}/boost-functional_x64-windows/include
	${BOOST_ROOT}/boost-fusion_x64-windows/include
	${BOOST_ROOT}/boost-geometry_x64-windows/include
	${BOOST_ROOT}/boost-gil_x64-windows/include
	${BOOST_ROOT}/boost-graph_x64-windows/include
	${BOOST_ROOT}/boost-hana_x64-windows/include
	${BOOST_ROOT}/boost-headers_x64-windows/include
	${BOOST_ROOT}/boost-heap_x64-windows/include
	${BOOST_ROOT}/boost-histogram_x64-windows/include
	${BOOST_ROOT}/boost-hof_x64-windows/include
	${BOOST_ROOT}/boost-icl_x64-windows/include
	${BOOST_ROOT}/boost-integer_x64-windows/include
	${BOOST_ROOT}/boost-interprocess_x64-windows/include
	${BOOST_ROOT}/boost-interval_x64-windows/include
	${BOOST_ROOT}/boost-intrusive_x64-windows/include
	${BOOST_ROOT}/boost-io_x64-windows/include
	${BOOST_ROOT}/boost-iostreams_x64-windows/include
	${BOOST_ROOT}/boost-iterator_x64-windows/include
	${BOOST_ROOT}/boost-json_x64-windows/include
	${BOOST_ROOT}/boost-lambda_x64-windows/include
	${BOOST_ROOT}/boost-lambda2_x64-windows/include
	${BOOST_ROOT}/boost-leaf_x64-windows/include
	${BOOST_ROOT}/boost-lexical-cast_x64-windows/include
	${BOOST_ROOT}/boost-local-function_x64-windows/include
	${BOOST_ROOT}/boost-locale_x64-windows/include
	${BOOST_ROOT}/boost-lockfree_x64-windows/include
	${BOOST_ROOT}/boost-log_x64-windows/include
	${BOOST_ROOT}/boost-logic_x64-windows/include
	${BOOST_ROOT}/boost-math_x64-windows/include
	${BOOST_ROOT}/boost-metaparse_x64-windows/include
	${BOOST_ROOT}/boost-move_x64-windows/include
	${BOOST_ROOT}/boost-mp11_x64-windows/include
	${BOOST_ROOT}/boost-mpl_x64-windows/include
	${BOOST_ROOT}/boost-msm_x64-windows/include
	${BOOST_ROOT}/boost-multi-array_x64-windows/include
	${BOOST_ROOT}/boost-multi-index_x64-windows/include
	${BOOST_ROOT}/boost-multiprecision_x64-windows/include
	${BOOST_ROOT}/boost-mysql_x64-windows/include
	${BOOST_ROOT}/boost-nowide_x64-windows/include
	${BOOST_ROOT}/boost-numeric-conversion_x64-windows/include
	${BOOST_ROOT}/boost-odeint_x64-windows/include
	${BOOST_ROOT}/boost-optional_x64-windows/include
	${BOOST_ROOT}/boost-outcome_x64-windows/include
	${BOOST_ROOT}/boost-parameter_x64-windows/include
	${BOOST_ROOT}/boost-parameter-python_x64-windows/include
	${BOOST_ROOT}/boost-pfr_x64-windows/include
	${BOOST_ROOT}/boost-phoenix_x64-windows/include
	${BOOST_ROOT}/boost-poly-collection_x64-windows/include
	${BOOST_ROOT}/boost-polygon_x64-windows/include
	${BOOST_ROOT}/boost-pool_x64-windows/include
	${BOOST_ROOT}/boost-predef_x64-windows/include
	${BOOST_ROOT}/boost-preprocessor_x64-windows/include
	${BOOST_ROOT}/boost-process_x64-windows/include
	${BOOST_ROOT}/boost-program-options_x64-windows/include
	${BOOST_ROOT}/boost-property-map_x64-windows/include
	${BOOST_ROOT}/boost-property-tree_x64-windows/include
	${BOOST_ROOT}/boost-proto_x64-windows/include
	${BOOST_ROOT}/boost-ptr-container_x64-windows/include
	${BOOST_ROOT}/boost-python_x64-windows/include
	${BOOST_ROOT}/boost-qvm_x64-windows/include
	${BOOST_ROOT}/boost-random_x64-windows/include
	${BOOST_ROOT}/boost-range_x64-windows/include
	${BOOST_ROOT}/boost-ratio_x64-windows/include
	${BOOST_ROOT}/boost-rational_x64-windows/include
	${BOOST_ROOT}/boost-redis_x64-windows/include
	${BOOST_ROOT}/boost-regex_x64-windows/include
	${BOOST_ROOT}/boost-safe-numerics_x64-windows/include
	${BOOST_ROOT}/boost-scope_x64-windows/include
	${BOOST_ROOT}/boost-scope-exit_x64-windows/include
	${BOOST_ROOT}/boost-serialization_x64-windows/include
	${BOOST_ROOT}/boost-signals2_x64-windows/include
	${BOOST_ROOT}/boost-smart-ptr_x64-windows/include
	${BOOST_ROOT}/boost-sort_x64-windows/include
	${BOOST_ROOT}/boost-spirit_x64-windows/include
	${BOOST_ROOT}/boost-stacktrace_x64-windows/include
	${BOOST_ROOT}/boost-statechart_x64-windows/include
	${BOOST_ROOT}/boost-static-assert_x64-windows/include
	${BOOST_ROOT}/boost-static-string_x64-windows/include
	${BOOST_ROOT}/boost-stl-interfaces_x64-windows/include
	${BOOST_ROOT}/boost-system_x64-windows/include
	${BOOST_ROOT}/boost-test_x64-windows/include
	${BOOST_ROOT}/boost-thread_x64-windows/include
	${BOOST_ROOT}/boost-throw-exception_x64-windows/include
	${BOOST_ROOT}/boost-timer_x64-windows/include
	${BOOST_ROOT}/boost-tokenizer_x64-windows/include
	${BOOST_ROOT}/boost-tti_x64-windows/include
	${BOOST_ROOT}/boost-tuple_x64-windows/include
	${BOOST_ROOT}/boost-type-erasure_x64-windows/include
	${BOOST_ROOT}/boost-type-index_x64-windows/include
	${BOOST_ROOT}/boost-type-traits_x64-windows/include
	${BOOST_ROOT}/boost-typeof_x64-windows/include
	${BOOST_ROOT}/boost-ublas_x64-windows/include
	${BOOST_ROOT}/boost-uninstall_x64-windows/include
	${BOOST_ROOT}/boost-units_x64-windows/include
	${BOOST_ROOT}/boost-unordered_x64-windows/include
	${BOOST_ROOT}/boost-url_x64-windows/include
	${BOOST_ROOT}/boost-utility_x64-windows/include
	${BOOST_ROOT}/boost-uuid_x64-windows/include
	${BOOST_ROOT}/boost-variant_x64-windows/include
	${BOOST_ROOT}/boost-variant2_x64-windows/include
	${BOOST_ROOT}/boost-vmd_x64-windows/include
	${BOOST_ROOT}/boost-wave_x64-windows/include
	${BOOST_ROOT}/boost-winapi_x64-windows/include
	${BOOST_ROOT}/boost-xpressive_x64-windows/include
	${BOOST_ROOT}/boost-yap_x64-windows/include
)
