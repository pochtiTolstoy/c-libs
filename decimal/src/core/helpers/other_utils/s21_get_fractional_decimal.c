
#include "s21_decimal.h"

int s21_get_fractional_decimal(s21_decimal value, s21_decimal *result) {
  int ret_code = 0;
  if (!result)
    ret_code = 1;
  else {
    char buffer_value[1024] = {0};
    char buffer_fractional[1024] = {0};
    s21_decimal_to_str(value, buffer_value);
    char *dot_ptr = strchr(buffer_value, '.');
    if (dot_ptr) {
      strcpy(buffer_fractional, dot_ptr + 1);
    } else {
      strcpy(buffer_fractional, "0");
    }

    s21_str_to_decimal(buffer_fractional, result);
    s21_set_sign(result, POS_SIGN);
  }
  return ret_code;
}