#include <s21_decimal.h>

void s21_set_scale(s21_decimal *num, unsigned int scale_value) {
  if (scale_value <= 28) {
    for (int i = 0; i < BITS_EXP_LEN; i++) {
      num->bits[BITS_EXP_IDX] &= ~(1 << (BITS_EXP_SHIFT + i));
    }
    for (int i = 0; scale_value && i < BITS_EXP_LEN; ++i, scale_value /= 2) {
      ((scale_value % 2 > 0)
           ? (num->bits[BITS_EXP_IDX] |= (1 << (BITS_EXP_SHIFT + i)))
           : (num->bits[BITS_EXP_IDX] &= ~(1 << (BITS_EXP_SHIFT + i))));
    }
  }
}
