cmake_minimum_required(VERSION 3.24)
project(WarehouseSystem VERSION 1.0 LANGUAGES CXX)

# Use modern C++ (C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---------- The program ----------
add_executable(warehouse_app src/main.cpp)

# ---------- Unit tests (GoogleTest) ----------
# CMake downloads GoogleTest automatically the first time you build
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)  # needed on Windows
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)            # we only need GoogleTest
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(warehouse_tests tests/test_sanity.cpp)
target_link_libraries(warehouse_tests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(warehouse_tests)
