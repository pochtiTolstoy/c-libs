#include "test_s21_decimal.h"

START_TEST(test_s21_is_valid_decimal_1) {
  s21_decimal number = {0};
  int code = s21_is_valid_decimal(&number);
  ck_assert(code == TRUE);

  printf("[PASSED] %s : %d\n", __func__, 1);
}
END_TEST

START_TEST(test_s21_is_valid_decimal_2) {
  s21_decimal number = {{0, 0, 0, 1}};
  int code = s21_is_valid_decimal(&number);
  ck_assert(code == FALSE);

  printf("[PASSED] %s : %d\n", __func__, 1);
}
END_TEST

START_TEST(test_s21_is_valid_decimal_3) {
  s21_decimal number = {{0, 0, 0, 0}};
  s21_set_sign(&number, NEG_SIGN);
  number.bits[3] |= 29 << 16;
  int code = s21_is_valid_decimal(&number);
  ck_assert(code == FALSE);

  printf("[PASSED] %s : %d\n", __func__, 1);
}
END_TEST

START_TEST(test_s21_is_valid_decimal_4) {
  s21_decimal number = {{0, 0, 0, 0}};
  s21_set_sign(&number, NEG_SIGN);
  number.bits[3] |= 28 << 16;
  int code = s21_is_valid_decimal(&number);
  ck_assert(code == TRUE);

  printf("[PASSED] %s : %d\n", __func__, 1);
}
END_TEST

TCase *tcase_s21_is_valid_decimal(void) {
  TCase *tcase = tcase_create("s21_str_to_decimal");
  tcase_add_test(tcase, test_s21_is_valid_decimal_1);
  tcase_add_test(tcase, test_s21_is_valid_decimal_2);
  tcase_add_test(tcase, test_s21_is_valid_decimal_3);
  tcase_add_test(tcase, test_s21_is_valid_decimal_4);
  return tcase;
}
