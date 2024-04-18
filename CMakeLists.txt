cmake_minimum_required(VERSION 3.1...3.29)
project(israelid VERSION 1.0 LANGUAGES C)
set(CMAKE_C_STANDARD 17)

add_library(israelid israelid.c)
target_include_directories(israelid PUBLIC include)

# Tests
option(ISRAELID_TEST "Build unit tests" OFF)
if (ISRAELID_TEST)
	enable_testing()
	enable_language(CXX)

	include(FetchContent)
	FetchContent_Declare(
		googletest
		GIT_REPOSITORY git@github.com:google/googletest.git
		GIT_TAG "5a37b517ad4ab6738556f0284c256cae1466c5b4"
		GIT_SHALLOW TRUE
		GIT_PROGRESS ON
	)
	set(CMAKE_CXX_STANDARD 14)
	set(CMAKE_CXX_STANDARD_REQUIRED ON)
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
	FetchContent_MakeAvailable(googletest)

	add_executable(tests tests.cpp)
	target_link_libraries(tests PRIVATE israelid GTest::gtest_main)

	include(GoogleTest)
	gtest_discover_tests(tests)
endif()

# Benchmark
option(ISRAELID_BENCH "Build benchmarks" OFF)
if (ISRAELID_BENCH)
	enable_language(CXX)

	include(FetchContent)
	FetchContent_Declare(
		googlebenchmark
		GIT_REPOSITORY git@github.com:google/benchmark.git
		GIT_TAG "bc946b919cac6f25a199a526da571638cfde109f"
		GIT_SHALLOW true
		GIT_PROGRESS ON
		SYSTEM
	)
	set(BENCHMARK_ENABLE_TESTING ${ISRAELID_TEST})
	FetchContent_MakeAvailable(googlebenchmark)

	add_executable(bench bench.cpp)
	target_link_libraries(bench israelid benchmark::benchmark)
endif()
