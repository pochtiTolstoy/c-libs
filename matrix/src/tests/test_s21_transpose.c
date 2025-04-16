#include "test_s21_matrix.h"

START_TEST(test_s21_transpose_1) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t res = {0};

  s21_unit_matrix(&A);
  s21_unit_matrix(&B);

  int result2 = s21_transpose(&A, &res);

  ck_assert_int_eq(result2, OK);

  int result3 = s21_eq_matrix(&res, &B);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res);

  ck_assert_int_eq(result3, SUCCESS);
}

START_TEST(test_s21_transpose_2) {
  matrix_t A = {0};
  matrix_t res = {0};

  s21_create_matrix(3, 3, &A);
  s21_initialize_matrix(&A, 0, 1);

  int result2 = s21_transpose(&A, &res);

  ck_assert_int_eq(result2, OK);

  ck_assert_double_eq(res.matrix[0][0], 0);
  ck_assert_double_eq(res.matrix[0][1], 3);
  ck_assert_double_eq(res.matrix[0][2], 6);
  ck_assert_double_eq(res.matrix[1][0], 1);
  ck_assert_double_eq(res.matrix[1][1], 4);
  ck_assert_double_eq(res.matrix[1][2], 7);
  ck_assert_double_eq(res.matrix[2][0], 2);
  ck_assert_double_eq(res.matrix[2][1], 5);
  ck_assert_double_eq(res.matrix[2][2], 8);

  s21_remove_matrix(&A);
  s21_remove_matrix(&res);
}

START_TEST(test_s21_transpose_3) {
  matrix_t A = {0};
  matrix_t res = {0};

  s21_create_matrix(3, 3, &A);
  s21_initialize_matrix(&A, 0, 1);

  int result2 = s21_transpose(&A, &res);

  s21_remove_matrix(&A);
  s21_remove_matrix(&res);

  ck_assert_int_eq(result2, OK);
}

TCase *tcase_s21_transpose(void) {
  TCase *tc = tcase_create("s21_transpose");
  tcase_add_test(tc, test_s21_transpose_1);
  tcase_add_test(tc, test_s21_transpose_2);
  tcase_add_test(tc, test_s21_transpose_3);
  return tc;
}
