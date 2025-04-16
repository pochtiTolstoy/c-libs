#include "s21_decimal.h"

int s21_count_all_digits(s21_decimal num) {
  int counter = 0;
  while (!s21_is_zero(&num)) {
    s21_divide_mantissa_by_10_decimal(&num, NULL);
    counter++;
  }

  return counter;
}