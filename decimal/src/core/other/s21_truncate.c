#include <s21_decimal.h>

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int ret_code = 0;
  if (!result || !s21_is_valid_decimal(&value))
    ret_code = 1;
  else {
    char buffer_value[1024] = {0};
    char buffer_integer[1024] = {0};
    s21_decimal_to_str(value, buffer_value);
    char *dot_ptr = strchr(buffer_value, '.');
    if (dot_ptr) {
      strncpy(buffer_integer, buffer_value, dot_ptr - buffer_value);
    } else {
      strcpy(buffer_integer, buffer_value);
    }

    s21_str_to_decimal(buffer_integer, result);
    s21_set_sign(result, s21_get_sign(&value));
  }
  return ret_code;
}