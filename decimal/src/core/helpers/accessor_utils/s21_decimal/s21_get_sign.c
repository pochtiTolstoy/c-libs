#include <s21_decimal.h>

int s21_get_sign(const s21_decimal *num) {
  return (num->bits[BITS_EXP_IDX] >> BITS_SIGN_SHIFT) & 0x1;
}
