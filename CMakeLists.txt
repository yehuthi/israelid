cmake_minimum_required(VERSION 3.1...3.29)
project(israelid VERSION 1.0 LANGUAGES C)
set(CMAKE_C_STANDARD 17)

add_library(israelid src/israelid.c)
target_include_directories(israelid PUBLIC include)

option(ISRAELID_SIMD "Enable SIMD (SSE 4.1) instructions" ON)
if (ISRAELID_SIMD)
	target_compile_options(israelid PUBLIC "-msse4.1")
endif()

# Binary
option(ISRAELID_BIN "Build the binary" ON)
if (ISRAELID_BIN)
	add_executable(ilid bin.c)
	target_link_libraries(ilid israelid)
endif()

option(ISRAELID_TEST "Build unit tests" OFF)
option(ISRAELID_BENCH "Build benchmarks" OFF)

# Debug information
if (ISRAELID_TEST OR ISRAELID_BENCH)
	target_compile_definitions(israelid PUBLIC ISRAELID_DEV=1)
	target_include_directories(israelid PUBLIC include_dev)
	target_compile_options(israelid PUBLIC "-fno-omit-frame-pointer")
	target_compile_options(israelid PUBLIC "-gdwarf")
endif()

# Tests
if (ISRAELID_TEST)
	enable_testing()
	enable_language(CXX)
	set(CMAKE_CXX_STANDARD 14)
	set(CMAKE_CXX_STANDARD_REQUIRED ON)

	include(FetchContent)
	FetchContent_Declare(
		googletest
		GIT_REPOSITORY git@github.com:google/googletest.git
		GIT_TAG "v1.15.2"
		GIT_SHALLOW TRUE
		GIT_PROGRESS ON
	)
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
	FetchContent_MakeAvailable(googletest)

	add_executable(tests tests.cpp)
	target_link_libraries(tests PRIVATE israelid GTest::gtest_main)

	include(GoogleTest)
	gtest_discover_tests(tests)
endif()

# Benchmark
if (ISRAELID_BENCH)
	enable_language(CXX)

	include(FetchContent)
	FetchContent_Declare(
		googlebenchmark
		GIT_REPOSITORY git@github.com:google/benchmark.git
		GIT_TAG "v1.9.0"
		GIT_SHALLOW true
		GIT_PROGRESS ON
		SYSTEM
	)
	set(BENCHMARK_ENABLE_TESTING ${ISRAELID_TEST})
	FetchContent_MakeAvailable(googlebenchmark)

	add_executable(bench bench.cpp)
	target_link_libraries(bench israelid benchmark::benchmark)
	if (NOT DEFINED CMAKE_BUILD_TYPE OR NOT CMAKE_BUILD_TYPE STREQUAL "Release")
		message(WARNING "benchmarking a non-release build")
	endif()
endif()
