#include "../arithmetic//arithmetic.h"
#include "s21_decimal.h"

int s21_is_equal_extended(const uint32_t *rhs, const uint32_t *lhs) {
  int equal = 1;
  for (size_t cell = 0; cell < MANTISSA_EXT_BITS && equal; ++cell) {
    equal = (rhs[cell] == lhs[cell]);
  }
  return equal;
}
