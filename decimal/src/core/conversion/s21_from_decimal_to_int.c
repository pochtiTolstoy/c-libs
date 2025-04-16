#include <s21_decimal.h>

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int mistake_code = 0;
  if (!dst || !s21_is_valid_decimal(&src)) {
    mistake_code = 1;
  } else {
    *dst = 0;

    uint32_t res = 0;
    for (int i = 0; i <= MANTISSA_MAX_BIT && !mistake_code; i++) {
      res += s21_get_bit(&src, i) * pow(2, i);
      if (s21_get_sign(&src) == POS_SIGN) {
        if ((int)res < 0) mistake_code = 1;
      }
    }
    if (!mistake_code) {
      res /= pow(10, s21_get_scale(&src));
      res *= (s21_get_sign(&src) == NEG_SIGN ? -1 : 1);
      *dst = (int)res;
    }
  }
  return mistake_code;
}