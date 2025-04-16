#include "test_s21_decimal.h"

START_TEST(test_s21_comparison) {
  size_t tests_in_unit = 30;
  printf(RUN_MSG, __func__);
  {
    s21_decimal value_1 =
        (s21_decimal){{0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0x000F0000}};
    s21_decimal value_2 =
        (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00FF0000}};
    ck_assert_int_eq(s21_is_less(value_1, value_2), 1);
  }
  {
    s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
    s21_decimal value_2 = {{0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
    ck_assert_int_eq(s21_is_less(value_1, value_2), 0);
  }
  {
    s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
    s21_decimal value_2 = {{0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    ck_assert_int_eq(s21_is_less(value_1, value_2), 0);
  }
  {
    s21_decimal value_1 = {{0x0000001C, 0x00000000, 0x00000000, 0x00070000}};
    s21_decimal value_2 = {{0x0000001C, 0x00000000, 0x00000000, 0x00030000}};
    ck_assert_int_eq(s21_is_less(value_1, value_2), 1);
  }
  {
    s21_decimal value_1 = {{0x0000001C, 0x00000000, 0x00000000, 0x00010000}};
    s21_decimal value_2 = {{0x0000001C, 0x00000000, 0x00000000, 0x000E0000}};
    ck_assert_int_eq(s21_is_less(value_1, value_2), 0);
  }
  {
    s21_decimal value_1 = {{0x0000001C, 0x00000000, 0x00000000, 0x000E0000}};
    s21_decimal value_2 = {{0x0000001C, 0x00000000, 0x00000000, 0x000E0000}};
    ck_assert_int_eq(s21_is_less(value_1, value_2), 0);
  }
  {
    s21_decimal value_1 =
        (s21_decimal){{0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0x000F0000}};
    s21_decimal value_2 =
        (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00FF0000}};
    ck_assert_int_eq(s21_is_less_or_equal(value_1, value_2), 1);
  }
  {
    s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
    s21_decimal value_2 = {{0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
    ck_assert_int_eq(s21_is_less_or_equal(value_1, value_2), 0);
  }
  {
    s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
    s21_decimal value_2 = {{0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    ck_assert_int_eq(s21_is_less_or_equal(value_1, value_2), 0);
  }
  {
    s21_decimal value_1 = {{0x0000001C, 0x00000000, 0x00000000, 0x00070000}};
    s21_decimal value_2 = {{0x0000001C, 0x00000000, 0x00000000, 0x00030000}};
    ck_assert_int_eq(s21_is_less_or_equal(value_1, value_2), 1);
  }
  {
    s21_decimal value_1 = {{0x0000001C, 0x00000000, 0x00000000, 0x00010000}};
    s21_decimal value_2 = {{0x0000001C, 0x00000000, 0x00000000, 0x000E0000}};
    ck_assert_int_eq(s21_is_less_or_equal(value_1, value_2), 0);
  }
  {
    s21_decimal value_1 = {{0x0000001C, 0x00000000, 0x00000000, 0x000E0000}};
    s21_decimal value_2 = {{0x0000001C, 0x00000000, 0x00000000, 0x000E0000}};
    ck_assert_int_eq(s21_is_less_or_equal(value_1, value_2), 1);
  }
  {
    s21_decimal a = {{0, 0, 0, 0}};
    s21_decimal b = {{0, 0, 0, 0}};
    ck_assert_int_eq(s21_is_equal(a, b), 1);
    ck_assert_int_eq(s21_is_less(a, b), 0);
    ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
    ck_assert_int_eq(s21_is_greater(a, b), 0);
    ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
    ck_assert_int_eq(s21_is_not_equal(a, b), 0);
  }
  {
    s21_decimal a = {{0, 0, 0, 0x80000000}};
    s21_decimal b = {{0, 0, 0, 0x00000000}};
    ck_assert_int_eq(s21_is_equal(a, b), 1);
    ck_assert_int_eq(s21_is_less(a, b), 0);
    ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
    ck_assert_int_eq(s21_is_greater(a, b), 0);
    ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
    ck_assert_int_eq(s21_is_not_equal(a, b), 0);
  }
  {
    s21_decimal a = {{0, 0, 0, 0x00000000}};
    s21_decimal b = {{0, 0, 0, 0x80000000}};
    ck_assert_int_eq(s21_is_equal(a, b), 1);
    ck_assert_int_eq(s21_is_less(a, b), 0);
    ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
    ck_assert_int_eq(s21_is_greater(a, b), 0);
    ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
    ck_assert_int_eq(s21_is_not_equal(a, b), 0);
  }
  {
    s21_decimal a = {{0, 0, 0, 0x00000000}};
    s21_decimal b = {{0, 0, 0, 0x00010000}};
    ck_assert_int_eq(s21_is_equal(a, b), 1);
    ck_assert_int_eq(s21_is_less(a, b), 0);
    ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
    ck_assert_int_eq(s21_is_greater(a, b), 0);
    ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
    ck_assert_int_eq(s21_is_not_equal(a, b), 0);
  }
  {
    s21_decimal a = {{0, 0, 0, 0x00000000}};
    s21_decimal b = {{0, 0, 0, 0x000A0000}};
    ck_assert_int_eq(s21_is_equal(a, b), 1);
    ck_assert_int_eq(s21_is_less(a, b), 0);
    ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
    ck_assert_int_eq(s21_is_greater(a, b), 0);
    ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
    ck_assert_int_eq(s21_is_not_equal(a, b), 0);
  }
  {
    s21_decimal a = {{0, 0, 0, 0x000A0000}};
    s21_decimal b = {{0, 0, 0, 0x00080000}};
    ck_assert_int_eq(s21_is_equal(a, b), 1);
    ck_assert_int_eq(s21_is_less(a, b), 0);
    ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
    ck_assert_int_eq(s21_is_greater(a, b), 0);
    ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
    ck_assert_int_eq(s21_is_not_equal(a, b), 0);
  }
  {
    s21_decimal a = {{0, 0, 0, 0x800A0000}};
    s21_decimal b = {{0, 0, 0, 0x00080000}};
    ck_assert_int_eq(s21_is_equal(a, b), 1);
    ck_assert_int_eq(s21_is_less(a, b), 0);
    ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
    ck_assert_int_eq(s21_is_greater(a, b), 0);
    ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
    ck_assert_int_eq(s21_is_not_equal(a, b), 0);
  }
  {
    s21_decimal value_1 =
        (s21_decimal){{0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0x000F0000}};
    s21_decimal value_2 =
        (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00FF0000}};
    ck_assert_int_eq(s21_is_greater(value_1, value_2), 0);
  }
  {
    s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
    s21_decimal value_2 = {{0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
    ck_assert_int_eq(s21_is_greater(value_1, value_2), 1);
  }
  {
    s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
    s21_decimal value_2 = {{0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    ck_assert_int_eq(s21_is_greater(value_1, value_2), 1);
  }
  {
    s21_decimal value_1 = {{0x0000001C, 0x00000000, 0x00000000, 0x00070000}};
    s21_decimal value_2 = {{0x0000001C, 0x00000000, 0x00000000, 0x00030000}};
    ck_assert_int_eq(s21_is_greater(value_1, value_2), 0);
  }
  {
    s21_decimal value_1 = {{0x0000001C, 0x00000000, 0x00000000, 0x00010000}};
    s21_decimal value_2 = {{0x0000001C, 0x00000000, 0x00000000, 0x000E0000}};
    ck_assert_int_eq(s21_is_greater(value_1, value_2), 1);
  }
  {
    s21_decimal value_1 = {{0x0000001C, 0x00000000, 0x00000000, 0x000E0000}};
    s21_decimal value_2 = {{0x0000001C, 0x00000000, 0x00000000, 0x000E0000}};
    ck_assert_int_eq(s21_is_greater(value_1, value_2), 0);
  }
  {
    s21_decimal value_1 =
        (s21_decimal){{0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0x000F0000}};
    s21_decimal value_2 =
        (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00FF0000}};
    ck_assert_int_eq(s21_is_greater_or_equal(value_1, value_2), 0);
  }
  {
    s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
    s21_decimal value_2 = {{0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
    ck_assert_int_eq(s21_is_greater_or_equal(value_1, value_2), 1);
  }
  {
    s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
    s21_decimal value_2 = {{0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    ck_assert_int_eq(s21_is_greater_or_equal(value_1, value_2), 1);
  }
  {
    s21_decimal value_1 = {{0x0000001C, 0x00000000, 0x00000000, 0x00070000}};
    s21_decimal value_2 = {{0x0000001C, 0x00000000, 0x00000000, 0x00030000}};
    ck_assert_int_eq(s21_is_greater_or_equal(value_1, value_2), 0);
  }
  {
    s21_decimal value_1 = {{0x0000001C, 0x00000000, 0x00000000, 0x00010000}};
    s21_decimal value_2 = {{0x0000001C, 0x00000000, 0x00000000, 0x000E0000}};
    ck_assert_int_eq(s21_is_greater_or_equal(value_1, value_2), 1);
  }
  {
    s21_decimal value_1 = {{0x0000001C, 0x00000000, 0x00000000, 0x000E0000}};
    s21_decimal value_2 = {{0x0000001C, 0x00000000, 0x00000000, 0x000E0000}};
    ck_assert_int_eq(s21_is_greater_or_equal(value_1, value_2), 1);
  }
  {
    s21_decimal value_1 =
        (s21_decimal){{0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0x000F0000}};
    s21_decimal value_2 =
        (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00FF0000}};
    ck_assert_int_eq(s21_is_equal(value_1, value_2), 0);
  }
  {
    s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
    s21_decimal value_2 = {{0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
    ck_assert_int_eq(s21_is_equal(value_1, value_2), 0);
  }
  {
    s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
    s21_decimal value_2 = {{0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    ck_assert_int_eq(s21_is_equal(value_1, value_2), 0);
  }
  {
    s21_decimal value_1 = {{0x0000001C, 0x00000000, 0x00000000, 0x00070000}};
    s21_decimal value_2 = {{0x0000001C, 0x00000000, 0x00000000, 0x00030000}};
    ck_assert_int_eq(s21_is_equal(value_1, value_2), 0);
  }
  {
    s21_decimal value_1 = {{0x0000001C, 0x00000000, 0x00000000, 0x00010000}};
    s21_decimal value_2 = {{0x0000001C, 0x00000000, 0x00000000, 0x000E0000}};
    ck_assert_int_eq(s21_is_equal(value_1, value_2), 0);
  }
  {
    s21_decimal value_1 = {{0x0000001C, 0x00000000, 0x00000000, 0x000E0000}};
    s21_decimal value_2 = {{0x0000001C, 0x00000000, 0x00000000, 0x000E0000}};
    ck_assert_int_eq(s21_is_equal(value_1, value_2), 1);
  }
  {
    s21_decimal value_1 =
        (s21_decimal){{0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0x000F0000}};
    s21_decimal value_2 =
        (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00FF0000}};
    ck_assert_int_eq(s21_is_not_equal(value_1, value_2), 1);
  }
  {
    s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
    s21_decimal value_2 = {{0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
    ck_assert_int_eq(s21_is_not_equal(value_1, value_2), 1);
  }
  {
    s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
    s21_decimal value_2 = {{0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    ck_assert_int_eq(s21_is_not_equal(value_1, value_2), 1);
  }
  {
    s21_decimal value_1 = {{0x0000001C, 0x00000000, 0x00000000, 0x00070000}};
    s21_decimal value_2 = {{0x0000001C, 0x00000000, 0x00000000, 0x00030000}};
    ck_assert_int_eq(s21_is_not_equal(value_1, value_2), 1);
  }
  {
    s21_decimal value_1 = {{0x0000001C, 0x00000000, 0x00000000, 0x00010000}};
    s21_decimal value_2 = {{0x0000001C, 0x00000000, 0x00000000, 0x000E0000}};
    ck_assert_int_eq(s21_is_not_equal(value_1, value_2), 1);
  }
  {
    s21_decimal value_1 = {{0x0000001C, 0x00000000, 0x00000000, 0x000E0000}};
    s21_decimal value_2 = {{0x0000001C, 0x00000000, 0x00000000, 0x000E0000}};
    ck_assert_int_eq(s21_is_not_equal(value_1, value_2), 0);
  }
  printf(END_MSG, __func__, tests_in_unit);
}
END_TEST

TCase *tcase_s21_comparison(void) {
  TCase *tcase = tcase_create("s21_comparison");
  tcase_add_test(tcase, test_s21_comparison);
  return tcase;
}