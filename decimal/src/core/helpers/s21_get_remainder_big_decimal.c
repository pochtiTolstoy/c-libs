#include "s21_decimal.h"

uint64_t s21_get_remainder_big_decimal(s21_big_decimal* num) {
  s21_big_decimal temp = {0};
  temp = *num;
  uint64_t remainder = -1;
  if (!(num->bits[0] == 0 && num->bits[1] == 0 && num->bits[2] == 0 &&
        num->bits[3] == 0 && num->bits[4] == 0 && num->bits[5] == 0 &&
        num->bits[6] == 0)) {
    s21_divide_mantissa_by_10_big_decimal(&temp, &remainder);
  }

  return remainder;
}