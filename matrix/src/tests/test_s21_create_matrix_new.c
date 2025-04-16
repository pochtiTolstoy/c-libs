#include "test_s21_matrix.h"

START_TEST(test_s21_create_matrix_1) {
  matrix_t matrix = {0};

  int status = s21_create_matrix(2, 2, &matrix);

  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(matrix.rows, 2);
  ck_assert_int_eq(matrix.columns, 2);
  ck_assert_ptr_ne(matrix.matrix, NULL);

  s21_remove_matrix(&matrix);
}

START_TEST(test_s21_create_matrix_2) {
  matrix_t matrix = {0};

  int status = s21_create_matrix(1, 1, &matrix);

  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(matrix.rows, 1);
  ck_assert_int_eq(matrix.columns, 1);
  ck_assert_ptr_ne(matrix.matrix, NULL);

  s21_remove_matrix(&matrix);
}

START_TEST(test_s21_create_matrix_3) {
  matrix_t matrix = {0};

  int status = s21_create_matrix(0, 0, &matrix);

  ck_assert_int_eq(status, INVALID_MATRIX);

  s21_remove_matrix(&matrix);
}

START_TEST(test_s21_create_matrix_4) {
  matrix_t matrix = {0};

  int status = s21_create_matrix(3, -1, &matrix);

  ck_assert_int_eq(status, INVALID_MATRIX);

  s21_remove_matrix(&matrix);
}

START_TEST(test_s21_create_matrix_5) {
  matrix_t matrix = {0};

  int status = s21_create_matrix(100, 100, &matrix);

  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(matrix.rows, 100);
  ck_assert_int_eq(matrix.columns, 100);
  ck_assert_ptr_ne(matrix.matrix, NULL);

  s21_remove_matrix(&matrix);
}

TCase *tcase_s21_create_matrix_new(void) {
  TCase *tc = tcase_create("s21_create_matrix_new");
  tcase_add_test(tc, test_s21_create_matrix_1);
  tcase_add_test(tc, test_s21_create_matrix_2);
  tcase_add_test(tc, test_s21_create_matrix_3);
  tcase_add_test(tc, test_s21_create_matrix_4);
  tcase_add_test(tc, test_s21_create_matrix_5);
  return tc;
}