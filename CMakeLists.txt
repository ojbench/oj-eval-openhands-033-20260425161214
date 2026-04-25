
cmake_minimum_required(VERSION 3.10)
project(list_implementation)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the test executable
add_executable(test_code test.cpp)

# For the actual submission, we need to create a main executable
# The OJ will look for a file named "code"
add_executable(code main.cpp)

# Include directories
target_include_directories(test_code PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(code PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
