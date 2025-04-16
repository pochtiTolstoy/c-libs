#include "s21_decimal.h"

void s21_bitwise_sub(s21_big_decimal num1, s21_big_decimal num2,
                     s21_big_decimal* result) {
  s21_big_decimal_set_sign(&num1, POS_SIGN);
  s21_big_decimal_set_sign(&num2, POS_SIGN);
  for (int i = 0; i <= MANTISSA_MAX_BIT_BIG_DECIMAL; i++) {
    int value_1 = s21_big_decimal_get_bit(&num1, i);
    int value_2 = s21_big_decimal_get_bit(&num2, i);

    int res_operation = value_1 - value_2;

    if (res_operation < 0) {
      s21_big_decimal_set_bit(result, i, 1);
      int value_temp = 0;
      for (int j = i + 1; j <= MANTISSA_MAX_BIT_BIG_DECIMAL && !value_temp;
           j++) {
        value_temp = s21_big_decimal_get_bit(&num1, j);
        if (value_temp == 0) {
          s21_big_decimal_set_bit(&num1, j, 1);
        } else {
          s21_big_decimal_set_bit(&num1, j, 0);
        }
      }
    } else {
      s21_big_decimal_set_bit(result, i, res_operation);
    }
  }
  s21_big_decimal_set_scale(result, s21_big_decimal_get_scale(&num1));
}