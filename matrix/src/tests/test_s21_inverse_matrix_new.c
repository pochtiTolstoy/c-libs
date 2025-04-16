#include "test_s21_matrix.h"

START_TEST(test_s21_inverse_matrix_1) {
  matrix_t matrix = {0};
  matrix_t result = {0};

  s21_create_matrix(2, 2, &matrix);

  matrix.matrix[0][0] = 1;
  matrix.matrix[0][1] = 2;
  matrix.matrix[1][0] = 3;
  matrix.matrix[1][1] = 4;

  int status = s21_inverse_matrix(&matrix, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], -2.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 1.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 1.5, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], -0.5, 1e-7);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}

START_TEST(test_s21_inverse_matrix_2) {
  matrix_t matrix = {0};
  matrix_t result = {0};

  s21_create_matrix(1, 1, &matrix);
  matrix.matrix[0][0] = 2;

  int status = s21_inverse_matrix(&matrix, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 0.5, 1e-7);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}

START_TEST(test_s21_inverse_matrix_3) {
  matrix_t matrix = {0};
  matrix_t result = {0};

  s21_create_matrix(2, 2, &matrix);

  matrix.matrix[0][0] = 1;
  matrix.matrix[0][1] = 2;
  matrix.matrix[1][0] = 2;
  matrix.matrix[1][1] = 4;  // Singular matrix (determinant = 0)

  int status = s21_inverse_matrix(&matrix, &result);

  ck_assert_int_eq(status, CALCULATION_ERROR);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}

START_TEST(test_s21_inverse_matrix_4) {
  matrix_t matrix = {0};
  matrix_t result = {0};

  s21_create_matrix(2, 3, &matrix);  // Non-square matrix

  int status = s21_inverse_matrix(&matrix, &result);

  ck_assert_int_eq(status, CALCULATION_ERROR);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}

START_TEST(test_s21_inverse_matrix_5) {
  matrix_t matrix = {0};
  matrix_t result = {0};

  s21_create_matrix(2, 2, &matrix);

  matrix.matrix[0][0] = 1.5;
  matrix.matrix[0][1] = 2.5;
  matrix.matrix[1][0] = 3.5;
  matrix.matrix[1][1] = 4.5;

  int status = s21_inverse_matrix(&matrix, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], -2.25, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 1.25, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 1.75, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], -0.75, 1e-7);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}

TCase *tcase_s21_inverse_matrix_new(void) {
  TCase *tc = tcase_create("s21_inverse_matrix_new");
  tcase_add_test(tc, test_s21_inverse_matrix_1);
  tcase_add_test(tc, test_s21_inverse_matrix_2);
  tcase_add_test(tc, test_s21_inverse_matrix_3);
  tcase_add_test(tc, test_s21_inverse_matrix_4);
  tcase_add_test(tc, test_s21_inverse_matrix_5);
  return tc;
}
