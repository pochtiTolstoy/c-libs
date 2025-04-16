
#include "../arithmetic/arithmetic.h"
#include "s21_decimal.h"

void s21_sub_extended(uint32_t *lhs, const uint32_t *rhs) {
  uint32_t carry = 0;
  for (size_t cell = 0; cell < MANTISSA_EXT_BITS; ++cell) {
    uint32_t temp = lhs[cell];
    lhs[cell] = lhs[cell] - rhs[cell] - carry;
    carry = (uint32_t)(temp - carry < rhs[cell]);
  }
}
