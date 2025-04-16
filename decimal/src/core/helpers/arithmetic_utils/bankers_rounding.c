#include "s21_decimal.h"

int bankers_rounding(s21_big_decimal* num) {
  uint64_t remainder = 0;
  s21_big_decimal one = {0};
  one.bits[0] = 1;
  while (num->bits[3] != 0) {
    s21_divide_mantissa_by_10_big_decimal(num, &remainder);
    uint64_t next_remainder = s21_get_remainder_big_decimal(num);
    if (remainder > 5) {
      s21_bitwise_add(num, &one, num);
    } else if (remainder == 5) {
      if (next_remainder % 2 != 0) {
        s21_bitwise_add(num, &one, num);
      }
    }
    s21_big_decimal_set_scale(num, s21_big_decimal_get_scale(num) - 1);
  }
  return (s21_big_decimal_get_scale(num) <= 28 &&
          s21_big_decimal_get_scale(num) >= 0)
             ? 0
             : 1;
}
