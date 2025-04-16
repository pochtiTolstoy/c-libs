#include "test_s21_matrix.h"

START_TEST(test_s21_mult_number_1) {
  matrix_t matrix = {0};
  matrix_t result = {0};

  s21_create_matrix(2, 2, &matrix);

  matrix.matrix[0][0] = 1;
  matrix.matrix[0][1] = 2;
  matrix.matrix[1][0] = 3;
  matrix.matrix[1][1] = 4;

  int status = s21_mult_number(&matrix, 2, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 2, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 4, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 6, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 8, 1e-7);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}

START_TEST(test_s21_mult_number_2) {
  matrix_t matrix = {0};
  matrix_t result = {0};

  s21_create_matrix(1, 1, &matrix);
  matrix.matrix[0][0] = 42;

  int status = s21_mult_number(&matrix, 0, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 0, 1e-7);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}

START_TEST(test_s21_mult_number_3) {
  matrix_t matrix = {0};
  matrix_t result = {0};

  s21_create_matrix(2, 2, &matrix);

  matrix.matrix[0][0] = 1.5;
  matrix.matrix[0][1] = 2.5;
  matrix.matrix[1][0] = 3.5;
  matrix.matrix[1][1] = 4.5;

  int status = s21_mult_number(&matrix, 2.0, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 3.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 5.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 7.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 9.0, 1e-7);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}

START_TEST(test_s21_mult_number_4) {
  matrix_t matrix = {0};
  matrix_t result = {0};

  s21_create_matrix(2, 2, &matrix);

  matrix.matrix[0][0] = -1;
  matrix.matrix[0][1] = -2;
  matrix.matrix[1][0] = -3;
  matrix.matrix[1][1] = -4;

  int status = s21_mult_number(&matrix, -1, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 1, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 2, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 3, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 4, 1e-7);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}

START_TEST(test_s21_mult_number_5) {
  matrix_t matrix = {0};
  matrix_t result = {0};

  s21_create_matrix(2, 2, &matrix);

  matrix.matrix[0][0] = 1;
  matrix.matrix[0][1] = 2;
  matrix.matrix[1][0] = 3;
  matrix.matrix[1][1] = 4;

  int status = s21_mult_number(&matrix, 0.5, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 0.5, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 1.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 1.5, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 2.0, 1e-7);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}

TCase *tcase_s21_mult_number_new(void) {
  TCase *tc = tcase_create("s21_mult_number_new");
  tcase_add_test(tc, test_s21_mult_number_1);
  tcase_add_test(tc, test_s21_mult_number_2);
  tcase_add_test(tc, test_s21_mult_number_3);
  tcase_add_test(tc, test_s21_mult_number_4);
  tcase_add_test(tc, test_s21_mult_number_5);
  return tc;
}