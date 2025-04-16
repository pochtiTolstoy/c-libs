#include "../arithmetic/arithmetic.h"
#include "s21_decimal.h"

int s21_is_less_extended(const uint32_t *lhs, const uint32_t *rhs) {
  int greater = 0;
  int less = 0;
  for (int cell = MANTISSA_EXT_BITS - 1; cell >= 0 && !less && !greater;
       --cell) {
    less = (lhs[cell] < rhs[cell]);
    greater = (lhs[cell] > rhs[cell]);
  }
  return less;
}
