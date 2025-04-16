#include "test_s21_matrix.h"

START_TEST(test_s21_sum_matrix_1) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t res = {0};

  s21_unit_matrix(&A);
  s21_unit_matrix(&B);

  int result2 = s21_sum_matrix(&A, &B, &res);
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
}

START_TEST(test_s21_sum_matrix_2) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t res = {0};

  s21_unit_matrix(&A);
  s21_create_matrix(3, 3, &B);
  s21_initialize_matrix(&B, 0, 1);

  int result2 = s21_sum_matrix(&A, &B, &res);
  ck_assert_int_eq(result2, OK);

  ck_assert_int_eq(res.matrix[0][0], 1);
  ck_assert_int_eq(res.matrix[0][1], 1);
  ck_assert_int_eq(res.matrix[0][2], 2);
  ck_assert_int_eq(res.matrix[1][0], 3);
  ck_assert_int_eq(res.matrix[1][1], 5);
  ck_assert_int_eq(res.matrix[1][2], 5);
  ck_assert_int_eq(res.matrix[2][0], 6);
  ck_assert_int_eq(res.matrix[2][1], 7);
  ck_assert_int_eq(res.matrix[2][2], 9);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res);
}

START_TEST(test_s21_sum_matrix_3) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t res = {0};

  s21_create_matrix(3, 3, &A);
  s21_initialize_matrix(&A, 0, 1);

  s21_create_matrix(2, 2, &B);
  s21_initialize_matrix(&B, 1, 1);

  int result = s21_sum_matrix(&A, &B, &res);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res);

  ck_assert_int_eq(result, CALCULATION_ERROR);
}

START_TEST(test_s21_sum_matrix_4) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t res = {0};

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = DBL_MAX;
  B.matrix[0][0] = DBL_MAX;

  int result = s21_sum_matrix(&A, &B, &res);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res);

  ck_assert_int_eq(result, OK);
}

START_TEST(test_s21_sub_matrix_1) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t res = {0};

  s21_unit_matrix(&A);
  s21_unit_matrix(&B);

  int result2 = s21_sub_matrix(&A, &B, &res);
  ck_assert_int_eq(result2, OK);

  ck_assert_int_eq(res.matrix[0][0], 0);
  ck_assert_int_eq(res.matrix[0][1], 0);
  ck_assert_int_eq(res.matrix[0][2], 0);
  ck_assert_int_eq(res.matrix[1][0], 0);
  ck_assert_int_eq(res.matrix[1][1], 0);
  ck_assert_int_eq(res.matrix[1][2], 0);
  ck_assert_int_eq(res.matrix[2][0], 0);
  ck_assert_int_eq(res.matrix[2][1], 0);
  ck_assert_int_eq(res.matrix[2][2], 0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res);
}

START_TEST(test_s21_sub_matrix_2) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t res = {0};

  s21_create_matrix(3, 3, &A);
  s21_initialize_matrix(&A, 0, 1);

  s21_create_matrix(2, 2, &B);
  s21_initialize_matrix(&B, 1, 1);

  int result = s21_sub_matrix(&A, &B, &res);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res);

  ck_assert_int_eq(result, CALCULATION_ERROR);
}

START_TEST(test_s21_sub_matrix_3) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t res = {0};

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = DBL_MAX;
  B.matrix[0][0] = -DBL_MAX;

  int result = s21_sub_matrix(&A, &B, &res);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res);

  ck_assert_int_eq(result, OK);
}

START_TEST(test_s21_mult_number_1) {
  matrix_t A = {0};
  matrix_t res = {0};

  s21_unit_matrix(&A);

  int result2 = s21_mult_number(&A, 2, &res);
  ck_assert_int_eq(result2, OK);

  ck_assert_double_eq(res.matrix[0][0], 2);
  ck_assert_double_eq(res.matrix[0][1], 0);
  ck_assert_double_eq(res.matrix[0][2], 0);
  ck_assert_double_eq(res.matrix[1][0], 0);
  ck_assert_double_eq(res.matrix[1][1], 2);
  ck_assert_double_eq(res.matrix[1][2], 0);
  ck_assert_double_eq(res.matrix[2][0], 0);
  ck_assert_double_eq(res.matrix[2][1], 0);
  ck_assert_double_eq(res.matrix[2][2], 2);

  s21_remove_matrix(&A);
  s21_remove_matrix(&res);
}

START_TEST(test_s21_mult_number_2) {
  matrix_t A = {0};
  matrix_t res = {0};

  s21_create_matrix(3, 3, &A);
  s21_initialize_matrix(&A, 0, 1);
  int result = s21_mult_number(&A, 2, &res);

  ck_assert_int_eq(result, OK);

  s21_remove_matrix(&A);
  s21_remove_matrix(&res);
}

START_TEST(test_s21_mult_number_3) {
  matrix_t A = {0};
  matrix_t res = {0};

  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = DBL_MAX;

  int result = s21_mult_number(&A, 2, &res);

  s21_remove_matrix(&A);
  s21_remove_matrix(&res);

  ck_assert_int_eq(result, OK);
}

TCase *tcase_s21_sum_sub_mult_matrix(void) {
  TCase *tc = tcase_create("s21_sum_sub_mult_matrix");
  tcase_add_test(tc, test_s21_sum_matrix_1);
  tcase_add_test(tc, test_s21_sum_matrix_2);
  tcase_add_test(tc, test_s21_sum_matrix_3);
  tcase_add_test(tc, test_s21_sum_matrix_4);
  tcase_add_test(tc, test_s21_sub_matrix_1);
  tcase_add_test(tc, test_s21_sub_matrix_2);
  tcase_add_test(tc, test_s21_sub_matrix_3);
  tcase_add_test(tc, test_s21_mult_number_1);
  tcase_add_test(tc, test_s21_mult_number_2);
  tcase_add_test(tc, test_s21_mult_number_3);

  return tc;
}
