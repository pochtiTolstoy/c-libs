#include <s21_decimal.h>

int s21_round(s21_decimal value, s21_decimal *result) {
  int ret_code = 0;
  if (!result || !s21_is_valid_decimal(&value)) {
    ret_code = 1;
  } else {
    s21_decimal integer_part = {0};
    s21_decimal fractional_part = {0};
    s21_decimal one = {{1, 0, 0, 0}};
    char fractional_buffer[1024] = {0};

    s21_truncate(value, &integer_part);
    s21_set_sign(&integer_part, POS_SIGN);
    s21_get_fractional_decimal(value, &fractional_part);

    s21_decimal_to_str(fractional_part, fractional_buffer);

    if (fractional_buffer[0] >= '5') {
      s21_add(integer_part, one, &integer_part);
    }

    s21_set_sign(&integer_part, s21_get_sign(&value));

    *result = integer_part;
  }

  return ret_code;
}