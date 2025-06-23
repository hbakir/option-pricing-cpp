add_executable(test_option_pricing test_option_pricing.cpp)

target_include_directories(test_option_pricing PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Register with CTest
add_test(NAME option_pricing_unit_tests COMMAND test_option_pricing)
