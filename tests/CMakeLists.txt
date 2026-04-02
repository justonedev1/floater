add_executable(tests_floater
  bit_representation.cpp
)
target_link_libraries(tests_floater PRIVATE floater Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(tests_floater)


