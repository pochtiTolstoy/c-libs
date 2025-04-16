#include <s21_decimal.h>

void s21_big_decimal_to_decimal(const s21_big_decimal* src, s21_decimal* dst) {
  for (int i = 0; i < MANTISSA_MAX_BIT + 1; i++) {
    s21_set_bit(dst, i, s21_big_decimal_get_bit(src, i));
  }
  s21_set_scale(dst, s21_big_decimal_get_scale(src));
  s21_set_sign(dst, s21_big_decimal_get_sign(src));
}