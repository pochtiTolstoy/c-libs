#include "test_s21_matrix.h"

START_TEST(test_s21_eq_matrix_inv_1) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(3, 3, &A);
  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAILURE);
  s21_remove_matrix(&A);
}

START_TEST(test_s21_eq_matrix_1) {
  matrix_t A = {0};
  matrix_t B = {0};
  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAILURE);
}

START_TEST(test_s21_eq_matrix_2) {
  matrix_t A;
  matrix_t B = {0};

  s21_unit_matrix(&A);

  s21_create_matrix(3, 3, &B);
  s21_initialize_matrix(&B, 0, 1);

  int result = s21_eq_matrix(&A, &B);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  ck_assert_int_eq(result, FAILURE);
}

START_TEST(test_s21_eq_matrix_3) {
  matrix_t A = {0};
  matrix_t B = {0};

  s21_unit_matrix(&A);
  s21_unit_matrix(&B);
  int result = s21_eq_matrix(&A, &B);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  ck_assert_int_eq(result, SUCCESS);
}

START_TEST(test_s21_eq_matrix_4) {
  matrix_t A = {0};
  matrix_t B = {0};

  s21_unit_matrix(&A);
  s21_create_matrix(4, 4, &B);
  s21_initialize_matrix(&B, 1, 1);
  int result = s21_eq_matrix(&A, &B);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  ck_assert_int_eq(result, FAILURE);
}

TCase *tcase_s21_eq_matrix(void) {
  TCase *tc = tcase_create("s21_eq_matrix");

  tcase_add_test(tc, test_s21_eq_matrix_inv_1);
  tcase_add_test(tc, test_s21_eq_matrix_1);
  tcase_add_test(tc, test_s21_eq_matrix_2);
  tcase_add_test(tc, test_s21_eq_matrix_3);
  tcase_add_test(tc, test_s21_eq_matrix_4);
  return tc;
}
