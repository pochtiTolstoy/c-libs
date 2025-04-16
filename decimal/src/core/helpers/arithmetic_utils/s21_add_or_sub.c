#include <s21_decimal.h>

int s21_add_or_sub(const s21_decimal* num1, const s21_decimal* num2,
                   s21_decimal* result, int op_sign) {
  int mistake_code = 0, mistake_sign = 0;
  if (s21_is_valid_decimal(num1) && s21_is_valid_decimal(num2) && result) {
    s21_make_decimal_empty(result);
    s21_decimal greatest =
        s21_is_greater_or_equal(s21_get_abs(*num1), s21_get_abs(*num2)) ? *num1
                                                                        : *num2;
    s21_decimal least = s21_is_equal(greatest, *num1) ? *num2 : *num1;

    int real_operation =
        s21_is_add_or_sub(s21_get_sign(num1), s21_get_sign(num2), op_sign);
    int result_sign = s21_get_op_sign_plus_minus(
        s21_get_sign(num1), s21_get_sign(num2), op_sign,
        s21_is_equal(*num1, greatest) ? 1 : 2);

    s21_big_decimal greatest_big = {0};
    s21_big_decimal least_big = {0};
    s21_big_decimal operation_result = {0};

    s21_decimal_to_big_decimal(&greatest, &greatest_big);
    s21_decimal_to_big_decimal(&least, &least_big);

    s21_normalize_big_decimals(&greatest_big, &least_big);
    if (real_operation == POS_SIGN) {
      s21_bitwise_add(&greatest_big, &least_big, &operation_result);
    } else {
      s21_bitwise_sub(greatest_big, least_big, &operation_result);
    }
    mistake_code = bankers_rounding(&operation_result);

    if (mistake_code == 0) {
      s21_big_decimal_to_decimal(&operation_result, result);
    }
    s21_set_sign(result, result_sign);

    mistake_sign = (s21_get_sign(result) == POS_SIGN ? 1 : 2);
    if (s21_is_zero(result)) s21_set_sign(result, POS_SIGN);
  }

  return (mistake_code == 0 ? 0 : mistake_sign);
}