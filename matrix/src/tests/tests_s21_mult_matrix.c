#include "test_s21_matrix.h"

START_TEST(test_s21_mult_matrix_1) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t res = {0};

  s21_unit_matrix(&A);
  s21_unit_matrix(&B);

  int result2 = s21_mult_matrix(&A, &B, &res);
  ck_assert_int_eq(result2, OK);

  ck_assert_int_eq(res.matrix[0][0], 1);
  ck_assert_int_eq(res.matrix[0][1], 0);
  ck_assert_int_eq(res.matrix[0][2], 0);
  ck_assert_int_eq(res.matrix[1][0], 0);
  ck_assert_int_eq(res.matrix[1][1], 1);
  ck_assert_int_eq(res.matrix[1][2], 0);
  ck_assert_int_eq(res.matrix[2][0], 0);
  ck_assert_int_eq(res.matrix[2][1], 0);
  ck_assert_int_eq(res.matrix[2][2], 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res);
}

START_TEST(test_s21_mult_matrix_2) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t res = {0};

  s21_unit_matrix(&A);
  s21_unit_matrix(&B);

  matrix_t mul;
  s21_mult_number(&A, 2, &mul);

  int result2 = s21_mult_matrix(&mul, &B, &res);
  ck_assert_int_eq(result2, OK);

  ck_assert_int_eq(res.matrix[0][0], 2);
  ck_assert_int_eq(res.matrix[0][1], 0);
  ck_assert_int_eq(res.matrix[0][2], 0);
  ck_assert_int_eq(res.matrix[1][0], 0);
  ck_assert_int_eq(res.matrix[1][1], 2);
  ck_assert_int_eq(res.matrix[1][2], 0);
  ck_assert_int_eq(res.matrix[2][0], 0);
  ck_assert_int_eq(res.matrix[2][1], 0);
  ck_assert_int_eq(res.matrix[2][2], 2);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res);
  s21_remove_matrix(&mul);
}

START_TEST(test_s21_mult_matrix_3) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t res = {0};

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = DBL_MAX;
  B.matrix[0][0] = -DBL_MAX;

  int result = s21_mult_matrix(&A, &B, &res);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res);

  ck_assert_int_eq(result, OK);
}

START_TEST(test_s21_mult_matrix_4) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t res = {0};

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  int result = s21_mult_matrix(&A, &B, &res);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res);

  ck_assert_int_eq(result, OK);
}

TCase *tcase_s21_mult_matrix(void) {
  TCase *tcase = tcase_create("s21_mult_matrix");
  tcase_add_test(tcase, test_s21_mult_matrix_1);
  tcase_add_test(tcase, test_s21_mult_matrix_2);
  tcase_add_test(tcase, test_s21_mult_matrix_3);
  tcase_add_test(tcase, test_s21_mult_matrix_4);

  return tcase;
}
