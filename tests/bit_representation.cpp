#include <cstddef>
#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include <floater/bit_representation.hpp>

using sizet = floater::uinteger<sizeof(size_t)>;

TEST_CASE("addition", "[bit_representation]") {
  REQUIRE((sizet(1) + sizet(2) == sizet(3)));
  REQUIRE((sizet(1) + sizet(3) == sizet(4)));
}

TEST_CASE("subtraction", "[bit_representation]") {
  REQUIRE((sizet(3) - sizet(1) == sizet(2)));
  REQUIRE((sizet(4) - sizet(1) == sizet(3)));
}
