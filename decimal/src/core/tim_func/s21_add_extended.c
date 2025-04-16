#include "../arithmetic/arithmetic.h"
#include "s21_decimal.h"

void s21_add_extended(uint32_t *lhs, const uint32_t *rhs) {
  uint32_t carry = 0;
  for (size_t cell = 0; cell < MANTISSA_EXT_BITS; ++cell) {
    uint64_t sum = (uint64_t)lhs[cell] + rhs[cell] + carry;
    carry = (uint32_t)(sum >> BYTE_SHIFT_4);
    lhs[cell] = (uint32_t)sum;
  }
}
