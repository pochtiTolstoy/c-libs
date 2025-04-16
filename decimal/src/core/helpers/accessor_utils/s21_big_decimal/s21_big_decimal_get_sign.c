#include <s21_decimal.h>

int s21_big_decimal_get_sign(const s21_big_decimal *num) {
  return (num->bits[BITS_BIG_DECIMAL_EXP_IDX] >> BITS_SIGN_SHIFT) & 0x1;
}
