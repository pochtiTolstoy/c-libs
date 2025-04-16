#include <s21_decimal.h>

void s21_big_decimal_set_scale(s21_big_decimal *num, unsigned int scale_value) {
  for (int i = 0; i < BITS_EXP_LEN; i++) {
    num->bits[BITS_BIG_DECIMAL_EXP_IDX] &= ~(1 << (BITS_EXP_SHIFT + i));
  }
  for (int i = 0; scale_value && i < BITS_EXP_LEN; ++i, scale_value /= 2) {
    ((scale_value % 2 > 0)
         ? (num->bits[BITS_BIG_DECIMAL_EXP_IDX] |= (1 << (BITS_EXP_SHIFT + i)))
         : (num->bits[BITS_BIG_DECIMAL_EXP_IDX] &=
            ~(1 << (BITS_EXP_SHIFT + i))));
  }
}
