#include <s21_decimal.h>

int s21_negate(s21_decimal value, s21_decimal *result) {
  int mistake_code = 0;
  if (!result || !s21_is_valid_decimal(&value)) {
    mistake_code = 1;
  } else {
    s21_set_sign(&value, s21_get_sign(&value) ? 0 : 1);
    *result = value;
  }

  return mistake_code;
}
