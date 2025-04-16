#include <s21_decimal.h>

void s21_set_sign(s21_decimal *num, int sign_value) {
  num->bits[BITS_EXP_IDX] &= ~(1U << BITS_SIGN_SHIFT);
  num->bits[BITS_EXP_IDX] |= ((unsigned)sign_value << BITS_SIGN_SHIFT);
}
