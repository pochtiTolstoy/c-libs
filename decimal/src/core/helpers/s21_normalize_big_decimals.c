#include "s21_decimal.h"

void s21_normalize_big_decimals(s21_big_decimal *num1, s21_big_decimal *num2) {
  int scale1 = s21_big_decimal_get_scale(num1);
  int scale2 = s21_big_decimal_get_scale(num2);
  s21_big_decimal *total_num =
      (scale1 > scale2 ? num2 : ((scale1 < scale2) ? num1 : NULL));
  s21_big_decimal *temp_num = (total_num == num1 ? num2 : num1);

  if (total_num && temp_num) {
    s21_big_decimal temp1;
    s21_big_decimal temp2;
    s21_big_decimal result_add = {0};

    for (int i = 0; i < abs(scale1 - scale2); i++) {
      temp1 = *total_num;
      temp2 = *total_num;
      s21_shift_left_big_decimal(&temp1, 3);
      s21_shift_left_big_decimal(&temp2, 1);
      s21_bitwise_add(&temp1, &temp2, &result_add);
      *total_num = result_add;
    }
    s21_big_decimal_set_scale(total_num, s21_big_decimal_get_scale(temp_num));
  }
}
