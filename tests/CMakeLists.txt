file(GLOB TEST_SOURCES *.cpp)

add_executable(test_option_pricing ${TEST_SOURCES})
target_include_directories(test_option_pricing PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Register with CTest
add_test(NAME option_pricing_unit_tests COMMAND test_option_pricing)