add_executable(option_pricing
    main.cpp
)

# Place the executable in the top-level build directory for ease of use
set_target_properties(option_pricing PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

target_include_directories(option_pricing PUBLIC ${PROJECT_SOURCE_DIR}/include)
