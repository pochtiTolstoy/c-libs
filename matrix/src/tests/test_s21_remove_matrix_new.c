#include "test_s21_matrix.h"

START_TEST(test_s21_remove_matrix_1) {
  matrix_t matrix = {0};

  s21_create_matrix(2, 2, &matrix);
  matrix.matrix[0][0] = 1;
  matrix.matrix[0][1] = 2;
  matrix.matrix[1][0] = 3;
  matrix.matrix[1][1] = 4;

  s21_remove_matrix(&matrix);

  ck_assert_ptr_eq(matrix.matrix, NULL);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
}

START_TEST(test_s21_remove_matrix_2) {
  matrix_t matrix = {0};

  s21_create_matrix(1, 1, &matrix);
  matrix.matrix[0][0] = 42;

  s21_remove_matrix(&matrix);

  ck_assert_ptr_eq(matrix.matrix, NULL);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
}

START_TEST(test_s21_remove_matrix_3) {
  matrix_t matrix = {0};

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

  s21_remove_matrix(&matrix);

  ck_assert_ptr_eq(matrix.matrix, NULL);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
}

START_TEST(test_s21_remove_matrix_4) {
  matrix_t matrix = {0};

  s21_create_matrix(2, 2, &matrix);
  matrix.matrix[0][0] = 1.5;
  matrix.matrix[0][1] = 2.5;
  matrix.matrix[1][0] = 3.5;
  matrix.matrix[1][1] = 4.5;

  s21_remove_matrix(&matrix);

  ck_assert_ptr_eq(matrix.matrix, NULL);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
}

START_TEST(test_s21_remove_matrix_5) {
  matrix_t matrix = {0};

  s21_create_matrix(100, 100, &matrix);
  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 100; j++) {
      matrix.matrix[i][j] = i * 100 + j;
    }
  }

  s21_remove_matrix(&matrix);

  ck_assert_ptr_eq(matrix.matrix, NULL);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
}

TCase *tcase_s21_remove_matrix_new(void) {
  TCase *tc = tcase_create("s21_remove_matrix_new");
  tcase_add_test(tc, test_s21_remove_matrix_1);
  tcase_add_test(tc, test_s21_remove_matrix_2);
  tcase_add_test(tc, test_s21_remove_matrix_3);
  tcase_add_test(tc, test_s21_remove_matrix_4);
  tcase_add_test(tc, test_s21_remove_matrix_5);
  return tc;
}