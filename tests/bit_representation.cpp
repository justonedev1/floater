#include <cstddef>
#include <cstdint>
#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include <floater/bit_representation/uinteger.hpp>

using sizet = floater::bit_representation::integer<8*sizeof(size_t)>;

using uint8t = floater::bit_representation::integer<8*sizeof(uint8_t)>;

TEST_CASE("addition", "[bit_representation]") {
  REQUIRE((sizet(1) + sizet(2) == sizet(3)));
  REQUIRE((sizet(1) + sizet(3) == sizet(4)));
}

TEST_CASE("subtraction", "[bit_representation]") {
  REQUIRE((sizet(3) - sizet(1) == sizet(2)));
  REQUIRE((sizet(4) - sizet(1) == sizet(3)));
}

TEST_CASE("multiplication", "[bit_representation]") {
  REQUIRE((sizet(3) * sizet(5) == floater::bit_representation::integer<2*sizeof(size_t)>(15)));
  REQUIRE((uint8t(255) * uint8t(255) == floater::bit_representation::integer<2*8*sizeof(uint8_t)>(65025)));
}
