find_package(GTest CONFIG REQUIRED)

add_executable(test_event
    test_event.cpp
)

target_link_libraries(test_event
    PRIVATE
        AegisCore
        GTest::gtest
        GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(test_event
    DISCOVERY_TIMEOUT 30
)
