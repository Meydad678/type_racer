cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Find GTest
find_package(GTest REQUIRED)

# 2. Define your sources
file(GLOB SRC_FILES "src/*.cpp")
file(GLOB TEST_FILES "tests/*.cpp")

# Create a copy of SRC_FILES without main.cpp for the tests
set(SRC_LOGIC ${SRC_FILES})
list(FILTER SRC_LOGIC EXCLUDE REGEX "main.cpp")

# --- DEBUG: This will print in your terminal when you run cmake ---
message(STATUS "Files being linked to tests: ${SRC_LOGIC} ${TEST_FILES}")

# 3. Create the App
add_executable(run_app ${SRC_FILES})
target_include_directories(run_app PRIVATE include)

# 4. Create the Tests
add_executable(run_tests ${TEST_FILES} ${SRC_LOGIC})
target_include_directories(run_tests PRIVATE include)

# Link everything. Order matters, and GTest::Main handles the main() entry point.
target_link_libraries(run_tests 
    GTest::GTest 
    GTest::Main 
    pthread
)