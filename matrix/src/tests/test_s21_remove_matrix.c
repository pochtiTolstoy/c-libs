#include "test_s21_matrix.h"

START_TEST(test_s21_remove_matrix_1) {
  matrix_t matrix = {0};
  int result = s21_create_matrix(3, 3, &matrix);
  ck_assert_int_eq(result, OK);
  s21_remove_matrix(&matrix);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
  ck_assert_ptr_eq(matrix.matrix, NULL);
}

START_TEST(test_s21_remove_matrix_2) {
  matrix_t matrix = {0};
  int result = s21_create_matrix(3, 3, &matrix);
  ck_assert_int_eq(result, OK);
  s21_remove_matrix(&matrix);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
  ck_assert_ptr_eq(matrix.matrix, NULL);
  s21_remove_matrix(&matrix);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
  ck_assert_ptr_eq(matrix.matrix, NULL);
}

TCase *tcase_s21_remove_matrix(void) {
  TCase *tc = tcase_create("s21_remove_matrix");
  tcase_add_test(tc, test_s21_remove_matrix_1);
  tcase_add_test(tc, test_s21_remove_matrix_2);
  return tc;
}
