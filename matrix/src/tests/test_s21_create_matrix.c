#include "test_s21_matrix.h"

START_TEST(test_s21_create_matrix) {
  int result = s21_create_matrix(3, 3, NULL);
  ck_assert_int_eq(result, INVALID_MATRIX);
}

START_TEST(test_s21_create_matrix_2) {
  matrix_t matrix = {0};
  int result = s21_create_matrix(3, 3, &matrix);
  ck_assert_int_eq(result, OK);
  ck_assert_int_eq(matrix.rows, 3);
  ck_assert_int_eq(matrix.columns, 3);
  ck_assert_ptr_ne(matrix.matrix, NULL);
  s21_remove_matrix(&matrix);
}

START_TEST(test_s21_create_matrix_3) {
  matrix_t matrix = {0};
  int result = s21_create_matrix(0, 0, &matrix);
  ck_assert_int_eq(result, INVALID_MATRIX);
  s21_remove_matrix(&matrix);
}

START_TEST(test_s21_create_matrix_4) {
  matrix_t matrix = {0};
  int result = s21_create_matrix(3, -1, &matrix);
  ck_assert_int_eq(result, INVALID_MATRIX);
  s21_remove_matrix(&matrix);
}

START_TEST(test_s21_create_matrix_5) {
  matrix_t matrix = {0};
  int result = s21_create_matrix(-1, 3, &matrix);
  ck_assert_int_eq(result, INVALID_MATRIX);
  s21_remove_matrix(&matrix);
}

START_TEST(test_s21_create_matrix_6) {
  matrix_t matrix = {0};
  int result = s21_create_matrix(INT32_MAX, 1, &matrix);
  ck_assert_int_eq(result, INVALID_MATRIX);
  s21_remove_matrix(&matrix);
}

TCase *tcase_s21_create_matrix(void) {
  TCase *tc = tcase_create("s21_create_matrix");
  tcase_add_test(tc, test_s21_create_matrix);
  tcase_add_test(tc, test_s21_create_matrix_2);
  tcase_add_test(tc, test_s21_create_matrix_3);
  tcase_add_test(tc, test_s21_create_matrix_4);
  tcase_add_test(tc, test_s21_create_matrix_5);
  tcase_add_test(tc, test_s21_create_matrix_6);
  return tc;
}
