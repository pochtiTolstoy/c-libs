#include "test_s21_matrix.h"

START_TEST(test_s21_sub_matrix_1) {
  matrix_t matrix1 = {0};
  matrix_t matrix2 = {0};
  matrix_t result = {0};

  s21_create_matrix(2, 2, &matrix1);
  s21_create_matrix(2, 2, &matrix2);

  matrix1.matrix[0][0] = 5;
  matrix1.matrix[0][1] = 6;
  matrix1.matrix[1][0] = 7;
  matrix1.matrix[1][1] = 8;

  matrix2.matrix[0][0] = 1;
  matrix2.matrix[0][1] = 2;
  matrix2.matrix[1][0] = 3;
  matrix2.matrix[1][1] = 4;

  int status = s21_sub_matrix(&matrix1, &matrix2, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 4, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 4, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 4, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 4, 1e-7);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&result);
}

START_TEST(test_s21_sub_matrix_2) {
  matrix_t matrix1 = {0};
  matrix_t matrix2 = {0};
  matrix_t result = {0};

  s21_create_matrix(1, 1, &matrix1);
  s21_create_matrix(1, 1, &matrix2);

  matrix1.matrix[0][0] = 100;
  matrix2.matrix[0][0] = 58;

  int status = s21_sub_matrix(&matrix1, &matrix2, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 42, 1e-7);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&result);
}

START_TEST(test_s21_sub_matrix_3) {
  matrix_t matrix1 = {0};
  matrix_t matrix2 = {0};
  matrix_t result = {0};

  s21_create_matrix(2, 2, &matrix1);
  s21_create_matrix(2, 3, &matrix2);  // Different dimensions

  int status = s21_sub_matrix(&matrix1, &matrix2, &result);

  ck_assert_int_eq(status, CALCULATION_ERROR);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&result);
}

START_TEST(test_s21_sub_matrix_4) {
  matrix_t matrix1 = {0};
  matrix_t matrix2 = {0};
  matrix_t result = {0};

  s21_create_matrix(2, 2, &matrix1);
  s21_create_matrix(2, 2, &matrix2);

  matrix1.matrix[0][0] = 2.0;
  matrix1.matrix[0][1] = 4.0;
  matrix1.matrix[1][0] = 6.0;
  matrix1.matrix[1][1] = 8.0;

  matrix2.matrix[0][0] = 0.5;
  matrix2.matrix[0][1] = 1.5;
  matrix2.matrix[1][0] = 2.5;
  matrix2.matrix[1][1] = 3.5;

  int status = s21_sub_matrix(&matrix1, &matrix2, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 1.5, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 2.5, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 3.5, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 4.5, 1e-7);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&result);
}

START_TEST(test_s21_sub_matrix_5) {
  matrix_t matrix1 = {0};
  matrix_t matrix2 = {0};
  matrix_t result = {0};

  s21_create_matrix(2, 2, &matrix1);
  s21_create_matrix(2, 2, &matrix2);

  matrix1.matrix[0][0] = 1;
  matrix1.matrix[0][1] = 2;
  matrix1.matrix[1][0] = 3;
  matrix1.matrix[1][1] = 4;

  matrix2.matrix[0][0] = 1;
  matrix2.matrix[0][1] = 2;
  matrix2.matrix[1][0] = 3;
  matrix2.matrix[1][1] = 4;

  int status = s21_sub_matrix(&matrix1, &matrix2, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 0, 1e-7);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&result);
}

TCase *tcase_s21_sub_matrix_new(void) {
  TCase *tc = tcase_create("s21_sub_matrix_new");
  tcase_add_test(tc, test_s21_sub_matrix_1);
  tcase_add_test(tc, test_s21_sub_matrix_2);
  tcase_add_test(tc, test_s21_sub_matrix_3);
  tcase_add_test(tc, test_s21_sub_matrix_4);
  tcase_add_test(tc, test_s21_sub_matrix_5);
  return tc;
}