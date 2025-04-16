#include <s21_decimal.h>

int s21_big_decimal_get_scale(const s21_big_decimal *num) {
  int number = 0;
  for (int i = 0; i < BYTE_SIZE; i++) {
    number += ((num->bits[BITS_BIG_DECIMAL_EXP_IDX] &
                (1 << (BITS_EXP_SHIFT + i))) != 0
                   ? 1
                   : 0) *
              pow(2, i);
  }
  return number;
}