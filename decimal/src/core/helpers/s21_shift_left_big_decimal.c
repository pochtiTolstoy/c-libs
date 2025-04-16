#include <s21_decimal.h>

void s21_shift_left_big_decimal(s21_big_decimal* num, int shift_value) {
  int mem = 0;
  for (int i = 0; i < BITS_BIG_DECIMAL_EXP_IDX; i++) {
    unsigned temp = num->bits[i];
    num->bits[i] <<= shift_value;
    num->bits[i] |= mem;
    mem = temp >> (BITS_PER_INT - shift_value);
  }
}