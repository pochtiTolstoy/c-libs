#include "../arithmetic/arithmetic.h"
#include "s21_decimal.h"

int s21_add_mantissa(const uint32_t *lhs, const uint32_t *rhs, uint32_t *res) {
  int carry = 0;
  for (size_t i = 0; i < 6; ++i) {
    uint64_t value = lhs[i] + rhs[i] + carry;
    carry = value >> BYTE_SHIFT_4;
    res[i] = (uint32_t)value;
  }
  return carry;
}
