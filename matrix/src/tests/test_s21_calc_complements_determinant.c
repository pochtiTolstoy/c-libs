#include "test_s21_matrix.h"

START_TEST(test_s21_calc_determinant_1) {
  matrix_t A = {0};
  double result = 0;

  s21_unit_matrix(&A);

  int status = s21_determinant(&A, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq(result, 1);

  s21_remove_matrix(&A);
}

START_TEST(test_s21_calc_determinant_2) {
  matrix_t A = {0};
  double result = 0;

  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  int status = s21_determinant(&A, &result);

  s21_remove_matrix(&A);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq(result, 0);
}

START_TEST(test_s21_calc_determinant_3) {
  matrix_t A = {0};
  matrix_t result = {0};

  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;

  int status = s21_calc_complements(&A, &result);

  ck_assert_int_eq(status, OK);

  ck_assert_double_eq(result.matrix[0][0], 0);
  ck_assert_double_eq(result.matrix[0][1], 10);
  ck_assert_double_eq(result.matrix[0][2], -20);
  ck_assert_double_eq(result.matrix[1][0], 4);
  ck_assert_double_eq(result.matrix[1][1], -14);
  ck_assert_double_eq(result.matrix[1][2], 8);
  ck_assert_double_eq(result.matrix[2][0], -8);
  ck_assert_double_eq(result.matrix[2][1], -2);
  ck_assert_double_eq(result.matrix[2][2], 4);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}

START_TEST(test_s21_calc_determinant_4) {
  matrix_t A = {0};
  matrix_t result = {0};

  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;

  int status = s21_calc_complements(&A, &result);

  ck_assert_int_eq(status, OK);

  ck_assert_double_eq(result.matrix[0][0], 0);
  ck_assert_double_eq(result.matrix[0][1], 10);
  ck_assert_double_eq(result.matrix[0][2], -20);
  ck_assert_double_eq(result.matrix[1][0], 4);
  ck_assert_double_eq(result.matrix[1][1], -14);
  ck_assert_double_eq(result.matrix[1][2], 8);
  ck_assert_double_eq(result.matrix[2][0], -8);
  ck_assert_double_eq(result.matrix[2][1], -2);
  ck_assert_double_eq(result.matrix[2][2], 4);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}

START_TEST(test_s21_calc_determinant_5) {
  matrix_t A = {0};

  s21_create_matrix(3, 2, &A);

  double det;
  int res = s21_determinant(&A, &det);

  s21_remove_matrix(&A);

  ck_assert_int_eq(res, CALCULATION_ERROR);
}

START_TEST(test_s21_calc_determinant_6) {
  matrix_t A = {0};
  matrix_t result = {0};

  s21_create_matrix(3, 3, &A);

  int res = s21_calc_complements(&A, &result);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);

  ck_assert_int_eq(res, OK);
}

TCase *tcase_s21_calc_complements_determinant(void) {
  TCase *tcase = tcase_create("s21_calc_complements_determinant");

  tcase_add_test(tcase, test_s21_calc_determinant_1);
  tcase_add_test(tcase, test_s21_calc_determinant_2);
  tcase_add_test(tcase, test_s21_calc_determinant_3);
  tcase_add_test(tcase, test_s21_calc_determinant_4);
  tcase_add_test(tcase, test_s21_calc_determinant_5);
  tcase_add_test(tcase, test_s21_calc_determinant_6);

  return tcase;
}
