cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME hardware_verification)
project(${PROJECT_NAME})

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
set(CMAKE_CXX_STANDARD 17)

if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

find_package(verilator REQUIRED)
find_package(GTest REQUIRED)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_TESTING OFF)
set(HAVE_STD_REGEX 0)
set(HAVE_STEADY_CLOCK 0)
set(HAVE_POSIX_REGEX 0)

enable_testing()

add_subdirectory(tb)