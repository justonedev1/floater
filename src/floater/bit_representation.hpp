#ifndef INCLUDEsrcbit_representationbit_representation_hpp_
#define INCLUDEsrcbit_representationbit_representation_hpp_

#include <bitset>
#include <cstring>

namespace floater {

template <size_t WIDTH> struct uinteger {
  std::bitset<WIDTH> buffer;

  uinteger() = default;

  uinteger(size_t val) : buffer() {
    static_assert(sizeof(WIDTH) >= sizeof(size_t));
    buffer = val;
  }
  uinteger operator+(const uinteger &other) const noexcept {
    return add_internal(other);
  }

  uinteger operator-(const uinteger &other) const noexcept {
    // a + (~b + 1)
    uinteger negated_other = other;
    negated_other.buffer.flip();
    return add_internal(negated_other, 1);
  }

  uinteger add_internal(const uinteger &other, bool carry = 0) const noexcept {
    uinteger<WIDTH> result{};
    for (size_t i{}; i != WIDTH; ++i) {
      const auto this_i = buffer[i], other_i = other.buffer[i];

      result.buffer[i] = this_i ^ other_i ^ carry;
      carry = (this_i & other_i) | (this_i & carry) | (other_i & carry);
    }
    return result;
  }

  bool operator<=>(const uinteger &other) const noexcept = default;
};

} // namespace floater

#endif // INCLUDEsrcbit_representationbit_representation.hpp_
