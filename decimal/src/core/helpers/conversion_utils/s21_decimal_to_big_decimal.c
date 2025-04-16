#include <s21_decimal.h>

void s21_decimal_to_big_decimal(const s21_decimal* src, s21_big_decimal* dst) {
  for (int i = 0; i < MANTISSA_MAX_BIT + 1; i++) {
    s21_big_decimal_set_bit(dst, i, s21_get_bit(src, i));
  }
  s21_big_decimal_set_scale(dst, s21_get_scale(src));
  s21_big_decimal_set_sign(dst, s21_get_sign(src));
}
