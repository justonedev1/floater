#ifndef INCLUDEsrcbit_representationbit_representation_hpp_
#define INCLUDEsrcbit_representationbit_representation_hpp_

#include <bitset>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <type_traits>

namespace floater::bit_representation {

template <size_t WIDTH> struct integer {
  template <typename Integer> struct integer_span {
    Integer *internal;

    uint8_t start;
    uint8_t end;
    uint8_t width;
    constexpr static bool is_const_v = std::is_const<Integer>();

    constexpr integer_span(Integer &full_object, uint8_t start = 0,
                           uint8_t end = WIDTH) noexcept
        : internal(&full_object), start{start}, end{end}, width(end - start) {}

    constexpr bool operator[](size_t idx) const noexcept {
      return internal->buffer[idx + start];
    }

    constexpr auto operator[](size_t idx) noexcept
      requires(!is_const_v)
    {
      return internal->buffer[idx + start];
    }

    constexpr void add_internal(const integer_span &other,
                                integer_span<integer> &result,
                                bool carry = 0) const noexcept {
      assert(width == other.width);
      assert(width == result.width);

      for (size_t i = 0; i != width; ++i) {
        const int8_t this_i = internal->buffer[start + i],
                     other_i = other.internal->buffer[other.start + i];

        result.internal->buffer[result.start + i] = this_i ^ other_i ^ carry;
        carry = (this_i & other_i) | (this_i & carry) | (other_i & carry);
      }
    }
  };

  std::bitset<WIDTH> buffer;

  integer() = default;

  integer(size_t val) noexcept : buffer() {
    // temporary so I can make uints from size_t
    buffer = val;
  }

  integer(const integer &) = default;
  integer &operator=(const integer &) = default;

  template <size_t Other_Width>
  integer(const integer<Other_Width> &other)
    requires(Other_Width < WIDTH)
  {
    for (size_t i{}; i != Other_Width; ++i) {
      this->buffer[i] = other.buffer[i];
    }
  }

  integer operator+(const integer &other) const noexcept {
    return add_internal(other);
  }

  integer operator-(const integer &other) const noexcept {
    // a + (~b + 1)
    integer negated_other = other;
    negated_other.buffer.flip();
    return add_internal(negated_other, 1);
  }

  integer<2 * WIDTH> operator*(const integer &other) const noexcept {
    return multiply_internal(other);
  }

  integer add_internal(const integer &other, bool carry = 0) const noexcept {
    integer result{};
    integer_span result_span(result);
    integer_span other_span(other);
    integer_span(*this).add_internal(other_span, result_span, carry);
    return result;
  }

  // c++ standard differs here as it returns narrowed type of the same width
  constexpr integer<2 * WIDTH>
  multiply_internal(const integer &other) const noexcept {
    integer<2 * WIDTH> result{};
    integer<2 * WIDTH> summand(*this);
    for (size_t i = 0; i != WIDTH; ++i) {
      // can I make some brancheless algorithm?
      if (other.buffer[i]) {
        result = summand + result;
      }
      summand.buffer <<= 1;
    }
    return result;
  }

  bool operator<=>(const integer &other) const noexcept = default;
};

} // namespace floater::bit_representation

#endif // INCLUDEsrcbit_representationbit_representation.hpp_
