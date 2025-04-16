#include <s21_decimal.h>

int s21_floor(s21_decimal value, s21_decimal *result) {
  int ret_code = 0;
  if (!result || !s21_is_valid_decimal(&value)) {
    ret_code = 1;
  } else {
    s21_decimal fractional_part = {0};
    int sign = s21_get_sign(&value);
    s21_truncate(value, result);
    s21_get_fractional_decimal(value, &fractional_part);
    if (sign == NEG_SIGN) {
      s21_set_sign(result, NEG_SIGN);
      s21_decimal one = {{1, 0, 0, 0}};
      if (!s21_is_zero(&fractional_part)) {
        s21_sub(*result, one, result);
      }
    }
  }

  return ret_code;
}
