#include "s21_decimal.h"
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int mistake_code = 0;
  if (!dst || !s21_is_valid_decimal(&src)) {
    mistake_code = 1;
  } else {
    *dst = 0;
    int decimal_sign = s21_get_sign(&src);
    int decimal_scale = s21_get_scale(&src);
    s21_decimal zero_decimal = {0};
    if (!s21_is_valid_decimal(&src)) {
      mistake_code = 1;
    } else if (s21_is_equal(src, zero_decimal)) {
      if (decimal_sign == POS_SIGN)
        *dst = 0.0;
      else
        *dst = -0.0;

    } else {
      *dst = 0.0;
      double temp = 0.0;
      for (int i = 0; i <= MANTISSA_MAX_BIT; i++) {
        if (s21_get_bit(&src, i) != 0) temp += pow(2.0, i);
      }

      temp /= pow(10, decimal_scale);

      if (decimal_sign == NEG_SIGN) temp *= -1.0;
      *dst = (float)temp;
    }
  }
  return mistake_code;
}