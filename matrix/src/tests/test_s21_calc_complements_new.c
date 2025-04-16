#include "test_s21_matrix.h"

START_TEST(test_s21_calc_complements_1) {
  matrix_t matrix = {0};
  matrix_t result = {0};

  s21_create_matrix(2, 2, &matrix);

  matrix.matrix[0][0] = 1;
  matrix.matrix[0][1] = 2;
  matrix.matrix[1][0] = 3;
  matrix.matrix[1][1] = 4;

  int status = s21_calc_complements(&matrix, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 4, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], -3, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], -2, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 1, 1e-7);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}

START_TEST(test_s21_calc_complements_2) {
  matrix_t matrix = {0};
  matrix_t result = {0};

  s21_create_matrix(1, 1, &matrix);
  matrix.matrix[0][0] = 42;

  int status = s21_calc_complements(&matrix, &result);

  ck_assert_int_eq(status, CALCULATION_ERROR);

  s21_remove_matrix(&matrix);
}

START_TEST(test_s21_calc_complements_3) {
  matrix_t matrix = {0};
  matrix_t result = {0};

  s21_create_matrix(3, 3, &matrix);

  matrix.matrix[0][0] = 1;
  matrix.matrix[0][1] = 2;
  matrix.matrix[0][2] = 3;
  matrix.matrix[1][0] = 4;
  matrix.matrix[1][1] = 5;
  matrix.matrix[1][2] = 6;
  matrix.matrix[2][0] = 7;
  matrix.matrix[2][1] = 8;
  matrix.matrix[2][2] = 9;

  int status = s21_calc_complements(&matrix, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], -3, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 6, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][2], -3, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 6, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], -12, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][2], 6, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][0], -3, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][1], 6, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][2], -3, 1e-7);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}

START_TEST(test_s21_calc_complements_4) {
  matrix_t matrix = {0};
  matrix_t result = {0};

  s21_create_matrix(2, 3, &matrix);  // Non-square matrix

  int status = s21_calc_complements(&matrix, &result);

  ck_assert_int_eq(status, CALCULATION_ERROR);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}

START_TEST(test_s21_calc_complements_5) {
  matrix_t matrix = {0};
  matrix_t result = {0};

  s21_create_matrix(2, 2, &matrix);

  matrix.matrix[0][0] = 1.5;
  matrix.matrix[0][1] = 2.5;
  matrix.matrix[1][0] = 3.5;
  matrix.matrix[1][1] = 4.5;

  int status = s21_calc_complements(&matrix, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 4.5, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], -3.5, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], -2.5, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 1.5, 1e-7);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}

TCase *tcase_s21_calc_complements_new(void) {
  TCase *tc = tcase_create("s21_calc_complements_new");
  tcase_add_test(tc, test_s21_calc_complements_1);
  tcase_add_test(tc, test_s21_calc_complements_2);
  tcase_add_test(tc, test_s21_calc_complements_3);
  tcase_add_test(tc, test_s21_calc_complements_4);
  tcase_add_test(tc, test_s21_calc_complements_5);
  return tc;
}
