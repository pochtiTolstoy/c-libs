#include "s21_decimal.h"

void s21_divide_mantissa_by_10_big_decimal(s21_big_decimal* num,
                                           uint64_t* remainder_output) {
  uint64_t remainder = 0;
  for (int i = BITS_BIG_DECIMAL_EXP_IDX - 1; i >= 0; i--) {
    uint64_t value = ((uint64_t)remainder << 32) | num->bits[i];
    num->bits[i] = (uint32_t)(value / 10);
    remainder = value % 10;
  }

  if (remainder_output) {
    *remainder_output = remainder;
  }
}