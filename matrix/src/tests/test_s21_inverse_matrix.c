#include "test_s21_matrix.h"

START_TEST(test_s21_inverse_matrix_0) {
  matrix_t A = {0};
  matrix_t res = {0};
  double result = 0;

  s21_create_matrix(3, 3, &A);
  s21_determinant(&A, &result);
  int result1 = s21_inverse_matrix(&A, &res);

  ck_assert_int_eq(result1, CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&res);
}

START_TEST(test_s21_inverse_matrix_1) {
  int result1 = OK, result2 = OK;

  matrix_t A = {0};
  matrix_t res = {0};

  result1 = s21_create_matrix(3, 3, &A);

  ck_assert_int_eq(result1, OK);
  ck_assert_int_eq(result2, OK);

  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;

  result1 = s21_inverse_matrix(&A, &res);

  ck_assert_int_eq(result1, OK);

  ck_assert_double_eq(res.matrix[0][0], 1);
  ck_assert_double_eq(res.matrix[0][1], -1);
  ck_assert_double_eq(res.matrix[0][2], 1);
  ck_assert_double_eq(res.matrix[1][0], -38);
  ck_assert_double_eq(res.matrix[1][1], 41);
  ck_assert_double_eq(res.matrix[1][2], -34);
  ck_assert_double_eq(res.matrix[2][0], 27);
  ck_assert_double_eq(res.matrix[2][1], -29);
  ck_assert_double_eq(res.matrix[2][2], 24);

  s21_remove_matrix(&A);
  s21_remove_matrix(&res);
}

TCase *tcase_s21_inverse_matrix(void) {
  TCase *tc = tcase_create("s21_inverse_matrix");
  tcase_add_test(tc, test_s21_inverse_matrix_1);
  tcase_add_test(tc, test_s21_inverse_matrix_0);
  return tc;
}
