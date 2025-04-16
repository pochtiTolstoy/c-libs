#include <s21_decimal.h>

int s21_sub(s21_decimal num1, s21_decimal num2, s21_decimal *result) {
  return s21_add_or_sub(&num1, &num2, result, NEG_SIGN);
}
