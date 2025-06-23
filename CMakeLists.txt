cmake_minimum_required(VERSION 3.15)
project(option_pricing_cpp VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_subdirectory(src)

# Enable unit testing with CTest
include(CTest)
enable_testing()

add_subdirectory(tests)