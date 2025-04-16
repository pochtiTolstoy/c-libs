#include "test_s21_decimal.h"

START_TEST(test_floor) {
  printf(RUN_MSG, "others_tests");

  float float_value = 11.5, res = 0.0;
  s21_decimal decimal = {{0}};
  s21_from_float_to_decimal(float_value, &decimal);
  ck_assert(s21_floor(decimal, &decimal) == 0);
  s21_from_decimal_to_float(decimal, &res);
  float_value = floorf(float_value);
  ck_assert_ldouble_eq(float_value, res);
}
END_TEST

START_TEST(test_floor_negative) {
  float float_value = -11.5, res = 0.0;
  s21_decimal decimal = {{0}};
  s21_from_float_to_decimal(float_value, &decimal);
  ck_assert(s21_floor(decimal, &decimal) == 0);
  s21_from_decimal_to_float(decimal, &res);
  float_value = floorf(float_value);
  ck_assert_ldouble_eq(float_value, res);
}
END_TEST

START_TEST(test_floor_big) {
  s21_decimal value = {{115, 1, 0, 1U << 16}};
  s21_decimal res = {{0}};
  s21_decimal expected_decimal = {{429496741, 0, 0, 0}};
  ck_assert(s21_floor(value, &res) == 0);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal), 1);
}
END_TEST

START_TEST(test_floor_big_negative) {
  s21_decimal value = {{115, 2, 0, (1U << 31) + (1U << 16)}};
  s21_decimal res = {{0}};
  s21_decimal expected_decimal = {{858993471, 0, 0, 1U << 31}};
  ck_assert(s21_floor(value, &res) == 0);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal), 1);
}
END_TEST

START_TEST(test_floor_exp) {
  float float_value = 1.15, res = 0.0;
  s21_decimal decimal = {{0}};
  s21_from_float_to_decimal(float_value, &decimal);
  ck_assert(s21_floor(decimal, &decimal) == 0);
  s21_from_decimal_to_float(decimal, &res);
  float_value = floorf(float_value);
  ck_assert_ldouble_eq(float_value, res);
}
END_TEST

START_TEST(test_floor_no_exp) {
  float float_value = 115.0, res = 0.0;
  s21_decimal decimal = {{0}};
  s21_from_float_to_decimal(float_value, &decimal);
  ck_assert(s21_floor(decimal, &decimal) == 0);
  s21_from_decimal_to_float(decimal, &res);
  float_value = floorf(float_value);
  ck_assert_ldouble_eq(float_value, res);
}

START_TEST(test_round_no_exp) {
  float float_value = 115.0, res = 0.0;
  s21_decimal decimal = {{0}};
  s21_from_float_to_decimal(float_value, &decimal);
  ck_assert(s21_floor(decimal, &decimal) == 0);
  s21_from_decimal_to_float(decimal, &res);
  float_value = roundf(float_value);
  ck_assert_ldouble_eq(float_value, res);
}

START_TEST(test_truncate_no_exp) {
  float float_value = 115.0;
  s21_decimal decimal = {{0}};
  s21_from_float_to_decimal(float_value, &decimal);
  ck_assert(s21_floor(decimal, &decimal) == 0);
  int result = 0;
  s21_from_decimal_to_int(decimal, &result);
  int expected = float_value;
  ck_assert_int_eq(expected, result);
}

START_TEST(test_floor_int_no_exp) {
  int int_value = 115, res = 0;
  s21_decimal decimal = {{0}};
  s21_from_int_to_decimal(int_value, &decimal);
  ck_assert(s21_floor(decimal, &decimal) == 0);
  s21_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(int_value, res);
}

START_TEST(test_round_int_no_exp) {
  int int_value = 115, res = 0;
  s21_decimal decimal = {{0}};
  s21_from_int_to_decimal(int_value, &decimal);
  ck_assert(s21_floor(decimal, &decimal) == 0);
  s21_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(int_value, res);
}

START_TEST(test_truncate_int_no_exp) {
  int int_value = 115, res = 0;
  s21_decimal decimal = {{0}};
  s21_from_int_to_decimal(int_value, &decimal);
  ck_assert(s21_floor(decimal, &decimal) == 0);
  s21_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(int_value, res);
}

START_TEST(test_floor_int_no_exp_neg) {
  int int_value = -115, res = 0;
  s21_decimal decimal = {{0}};
  s21_from_int_to_decimal(int_value, &decimal);
  ck_assert(s21_floor(decimal, &decimal) == 0);
  s21_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(int_value, res);
}

START_TEST(test_round_int_no_exp_neg) {
  int int_value = -115, res = 0;
  s21_decimal decimal = {{0}};
  s21_from_int_to_decimal(int_value, &decimal);
  ck_assert(s21_floor(decimal, &decimal) == 0);
  s21_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(int_value, res);
}

START_TEST(test_truncate_int_no_exp_neg) {
  int int_value = -115, res = 0;
  s21_decimal decimal = {{0}};
  s21_from_int_to_decimal(int_value, &decimal);
  ck_assert(s21_floor(decimal, &decimal) == 0);
  s21_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(int_value, res);
}

START_TEST(test_round) {
  float float_value = 11.5, res = 0.0;
  s21_decimal decimal = {{0}};
  s21_from_float_to_decimal(float_value, &decimal);
  ck_assert(s21_round(decimal, &decimal) == 0);
  s21_from_decimal_to_float(decimal, &res);
  float_value = roundf(float_value);
  ck_assert_ldouble_eq(float_value, res);
}
END_TEST

START_TEST(test_round_negative) {
  float float_value = -11.5, res = 0.0;
  s21_decimal decimal = {{0}};
  s21_from_float_to_decimal(float_value, &decimal);
  ck_assert(s21_round(decimal, &decimal) == 0);
  s21_from_decimal_to_float(decimal, &res);
  float_value = roundf(float_value);
  ck_assert_ldouble_eq(float_value, res);
}
END_TEST

START_TEST(test_round_big) {
  s21_decimal value = {{115, 2, 0, 1U << 16}};
  s21_decimal res = {{0}};
  s21_decimal expected_decimal = {{858993471, 0, 0, 0}};
  ck_assert(s21_round(value, &res) == 0);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal), 1);
}
END_TEST

START_TEST(test_round_zero) {
  float float_value = 0.0, res = 0.0;
  s21_decimal decimal = {{0}};
  s21_from_float_to_decimal(float_value, &decimal);
  ck_assert(s21_round(decimal, &decimal) == 0);
  s21_from_decimal_to_float(decimal, &res);
  float_value = roundf(float_value);
  ck_assert_ldouble_eq(float_value, res);
}
END_TEST

START_TEST(test_round_big_exp) {
  float float_value = 11.555, res = 0.0;
  s21_decimal decimal = {{0}};
  s21_from_float_to_decimal(float_value, &decimal);
  ck_assert(s21_round(decimal, &decimal) == 0);
  s21_from_decimal_to_float(decimal, &res);
  float_value = roundf(float_value);
  ck_assert_ldouble_eq(float_value, res);
}
END_TEST

START_TEST(test_round_sub) {
  float float_value = 12.5, res = 0.0;
  s21_decimal decimal = {{0}};
  s21_from_float_to_decimal(float_value, &decimal);
  ck_assert(s21_round(decimal, &decimal) == 0);
  s21_from_decimal_to_float(decimal, &res);
  float_value = roundf(float_value);
  ck_assert_ldouble_eq(float_value, res);
}
END_TEST

START_TEST(test_round_sub_2) {
  float float_value = 12.3, res = 0.0;
  s21_decimal decimal = {{0}};
  s21_from_float_to_decimal(float_value, &decimal);
  ck_assert(s21_round(decimal, &decimal) == 0);
  s21_from_decimal_to_float(decimal, &res);
  float_value = roundf(float_value);
  ck_assert_ldouble_eq(float_value, res);
}
END_TEST

START_TEST(test_negate_positive_int) {
  s21_decimal value = {{115, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert(s21_negate(value, &res) == 0);
  s21_decimal expected_decimal = {{115, 0, 0, 1U << 31}};
  ck_assert_int_eq(s21_is_equal(res, expected_decimal), 1);
}
END_TEST

START_TEST(test_negate_negative_int) {
  s21_decimal value = {{115, 0, 0, 1U << 31}};
  s21_decimal res = {{0}};
  s21_decimal expected_decimal = {{115, 0, 0, 0}};
  ck_assert(s21_negate(value, &res) == 0);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal), 1);
}
END_TEST

START_TEST(test_negate_positive_float) {
  s21_decimal value = {{115, 0, 0, 1U << 16}};
  s21_decimal res = {{0}};
  s21_decimal expected_decimal = {{115, 0, 0, (1U << 31) + (1U << 16)}};
  ck_assert(s21_negate(value, &res) == 0);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal), 1);
}
END_TEST

START_TEST(test_negate_negative_float) {
  s21_decimal value = {{115, 0, 0, (1U << 31) + (1U << 16)}};
  s21_decimal res = {{0}};
  s21_decimal expected_decimal = {{115, 0, 0, 1 << 16}};
  ck_assert(s21_negate(value, &res) == 0);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal), 1);
}
END_TEST

START_TEST(test_negate_zero) {
  s21_decimal value = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  s21_decimal expected_decimal = {{0, 0, 0, 1U << 31}};
  ck_assert(s21_negate(value, &res) == 0);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal), 1);
}
END_TEST

START_TEST(test_negate_negative_zero) {
  s21_decimal value = {{0, 0, 0, 1U << 31}};
  s21_decimal res = {{0}};
  s21_decimal expected_decimal = {{0, 0, 0, 0}};
  ck_assert(s21_negate(value, &res) == 0);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal), 1);
}
END_TEST

START_TEST(test_truncate) {
  s21_decimal value = {{1, 0, 0, 1U << 16}};
  s21_decimal expected_decimal = {{0}};
  ck_assert(s21_truncate(value, &value) == 0);
  ck_assert_int_eq(s21_is_equal(value, expected_decimal), 1);
}
END_TEST

START_TEST(test_floor_exp_29) {
  s21_decimal value = {{1, 0, 0, 29U << 16}};
  ck_assert(s21_floor(value, &value) == 1);
}
END_TEST

START_TEST(test_round_exp_29) {
  s21_decimal value = {{1, 0, 0, 29U << 16}};
  ck_assert(s21_round(value, &value) == 1);
}
END_TEST

START_TEST(test_truncate_exp_29) {
  s21_decimal value = {{1, 0, 0, 29U << 16}};
  ck_assert(s21_truncate(value, &value) == 1);
}
END_TEST

START_TEST(test_negate_exp_29) {
  s21_decimal value = {{1, 0, 0, 29U << 16}};
  ck_assert(s21_negate(value, &value) == 1);
  printf(PASSED_MSG, "others_tests", (size_t)32);
}
END_TEST

TCase *tcase_s21_other(void) {
  TCase *tcase = tcase_create("s21_others");
  tcase_add_test(tcase, test_floor);
  tcase_add_test(tcase, test_floor_negative);
  tcase_add_test(tcase, test_floor_big);
  tcase_add_test(tcase, test_floor_big_negative);
  tcase_add_test(tcase, test_floor_exp);
  tcase_add_test(tcase, test_floor_no_exp);
  tcase_add_test(tcase, test_round_no_exp);
  tcase_add_test(tcase, test_truncate_no_exp);
  tcase_add_test(tcase, test_floor_int_no_exp);
  tcase_add_test(tcase, test_round_int_no_exp);
  tcase_add_test(tcase, test_truncate_int_no_exp);
  tcase_add_test(tcase, test_floor_int_no_exp_neg);
  tcase_add_test(tcase, test_round_int_no_exp_neg);
  tcase_add_test(tcase, test_truncate_int_no_exp_neg);
  tcase_add_test(tcase, test_round);
  tcase_add_test(tcase, test_round_negative);
  tcase_add_test(tcase, test_round_big);
  tcase_add_test(tcase, test_round_zero);
  tcase_add_test(tcase, test_round_big_exp);
  tcase_add_test(tcase, test_round_sub);
  tcase_add_test(tcase, test_round_sub_2);
  tcase_add_test(tcase, test_negate_positive_int);
  tcase_add_test(tcase, test_negate_negative_int);
  tcase_add_test(tcase, test_negate_positive_float);
  tcase_add_test(tcase, test_negate_negative_float);
  tcase_add_test(tcase, test_negate_zero);
  tcase_add_test(tcase, test_negate_negative_zero);
  tcase_add_test(tcase, test_truncate);
  tcase_add_test(tcase, test_floor_exp_29);
  tcase_add_test(tcase, test_round_exp_29);
  tcase_add_test(tcase, test_truncate_exp_29);
  tcase_add_test(tcase, test_negate_exp_29);

  return tcase;
}
