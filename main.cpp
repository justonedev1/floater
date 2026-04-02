#include <floater/bit_representation.hpp>
#include <limits>
#include <print>
#include <sys/types.h>

using sizet = floater::uinteger<sizeof(size_t) * 8>;

void print(const sizet &a, const sizet &b) {
  std::print("{}+{}={}\n", a.buffer.to_ulong(), b.buffer.to_ulong(),
             (a + b).buffer.to_ulong());
}

int main() {
  print(1, 3);
  print(std::numeric_limits<size_t>::max() - 1, 1);
}
