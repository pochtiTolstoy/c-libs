#include "s21_decimal.h"

static void find_mantissa_value(const uint32_t *p, s21_decimal *num_decimal,
                                int start_degree, s21_decimal *one,
                                s21_decimal *two);

static void multiple_mantissa_exponent(int exponent, s21_decimal *multiplicator,
                                       s21_decimal *one, s21_decimal *two,
                                       s21_decimal *num_decimal);

static void remove_extra_numbers(s21_decimal *num_decimal,
                                 int counter_zeros_end, int count_digits,
                                 uint64_t *remainder, s21_decimal *one,
                                 s21_decimal *ten);

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  s21_make_decimal_empty(dst);
  int mistake_code = 0;
  if ((!dst || isinf(src) || isnan(src)) ||
      (fabsf(src) > MAX_FLOAT_TO_CONVERT || fabs(src) < MIN_FLOAT_TO_CONVERT)) {
    mistake_code = 1;
  } else {
    int sign_float = (src >= 0 ? 0 : 1);
    uint32_t p;
    memcpy(&p, &src, sizeof(src));
    int exponent = (int)((p >> 23) & 0xFF) - 127;

    s21_decimal num_decimal = {0}, ten = {{10, 0, 0, 0}}, two = {{2, 0, 0, 0}},
                one = {{1, 0, 0, 0}}, multiplicator = {{2, 0, 0, 0}};
    int start_degree = 0;
    uint64_t remainder = 0;

    find_mantissa_value(&p, &num_decimal, start_degree, &one, &two);
    multiple_mantissa_exponent(exponent, &multiplicator, &one, &two,
                               &num_decimal);

    int count_digits = s21_count_all_digits(num_decimal);
    int counter_zeros_end = count_digits - s21_get_scale(&num_decimal);

    if (count_digits >= 8) {
      remove_extra_numbers(&num_decimal, counter_zeros_end, count_digits,
                           &remainder, &one, &ten);
    }
    s21_set_sign(&num_decimal, sign_float);
    *dst = num_decimal;
  }

  return mistake_code;
}

static void find_mantissa_value(const uint32_t *p, s21_decimal *num_decimal,
                                int start_degree, s21_decimal *one,
                                s21_decimal *two) {
  for (int i = 0; i < 22; i++) {
    s21_decimal temp = *two;
    for (int j = 0; j < start_degree; j++) s21_mul(temp, *two, &temp);
    s21_div(*one, temp, &temp);
    s21_set_scale(&temp, start_degree + 1);

    start_degree++;

    if (((*p & (1 << (22 - i))) != 0 ? 1 : 0))
      s21_add(*num_decimal, temp, num_decimal);
  }
  s21_add(*one, *num_decimal, num_decimal);
}

static void multiple_mantissa_exponent(int exponent, s21_decimal *multiplicator,
                                       s21_decimal *one, s21_decimal *two,
                                       s21_decimal *num_decimal) {
  int was_multiply = 0;
  for (int i = 0; i < abs(exponent) - 1; i++) {
    was_multiply = 1;
    s21_mul(*multiplicator, *two, multiplicator);
  }
  if (was_multiply == 1) {
    if (exponent < 0) s21_div(*one, *multiplicator, multiplicator);
    s21_mul(*num_decimal, *multiplicator, num_decimal);
  }
}

static void remove_extra_numbers(s21_decimal *num_decimal,
                                 int counter_zeros_end, int count_digits,
                                 uint64_t *remainder, s21_decimal *one,
                                 s21_decimal *ten) {
  for (int i = 0; i < count_digits - 8; i++) {
    s21_divide_mantissa_by_10_decimal(num_decimal, NULL);
    s21_set_scale(num_decimal, s21_get_scale(num_decimal) - 1);
  }

  s21_decimal temp = {0};
  temp = *num_decimal;
  s21_divide_mantissa_by_10_decimal(&temp, remainder);
  s21_set_scale(&temp, s21_get_scale(&temp) - 1);
  if (*remainder >= 5) {
    s21_decimal another_temp = {0};
    another_temp = temp;
    s21_set_scale(&another_temp, 0);
    s21_add(another_temp, *one, &another_temp);
    s21_set_scale(&another_temp, s21_get_scale(&temp));
    temp = another_temp;
  }
  *num_decimal = temp;

  temp = *num_decimal;
  *remainder = 0;
  while (*remainder == 0) {
    s21_divide_mantissa_by_10_decimal(&temp, remainder);
    s21_set_scale(&temp, s21_get_scale(&temp) - 1);
    if (*remainder == 0) *num_decimal = temp;
  }
  if (s21_get_scale(num_decimal) == 0) {
    count_digits = s21_count_all_digits(*num_decimal);
    for (int i = 0; i < (counter_zeros_end - count_digits); i++) {
      s21_mul(*num_decimal, *ten, num_decimal);
    }
  }
}
