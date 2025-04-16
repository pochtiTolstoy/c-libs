
#include <s21_decimal.h>

s21_decimal s21_get_abs(s21_decimal num) {
  s21_set_sign(&num, POS_SIGN);
  return num;
}