add_executable(onion_datetime_demo
    "datetime_demo.cpp"
)

target_link_libraries(onion_datetime_demo
    PRIVATE
        onion::datetime
)

target_compile_features(onion_datetime_demo PRIVATE cxx_std_20)

set_target_properties(onion_datetime_demo PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)
