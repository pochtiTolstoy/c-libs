#include "test_s21_matrix.h"

START_TEST(test_s21_eq_matrix_1) {
  matrix_t matrix1 = {0};
  matrix_t matrix2 = {0};

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

  int result = s21_eq_matrix(&matrix1, &matrix2);

  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}

START_TEST(test_s21_eq_matrix_2) {
  matrix_t matrix1 = {0};
  matrix_t matrix2 = {0};

  s21_create_matrix(1, 1, &matrix1);
  s21_create_matrix(1, 1, &matrix2);

  matrix1.matrix[0][0] = 42;
  matrix2.matrix[0][0] = 42;

  int result = s21_eq_matrix(&matrix1, &matrix2);

  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}

START_TEST(test_s21_eq_matrix_3) {
  matrix_t matrix1 = {0};
  matrix_t matrix2 = {0};

  s21_create_matrix(2, 2, &matrix1);
  s21_create_matrix(2, 2, &matrix2);

  matrix1.matrix[0][0] = 1;
  matrix1.matrix[0][1] = 2;
  matrix1.matrix[1][0] = 3;
  matrix1.matrix[1][1] = 4;

  matrix2.matrix[0][0] = 1;
  matrix2.matrix[0][1] = 2;
  matrix2.matrix[1][0] = 3;
  matrix2.matrix[1][1] = 5;  // Different value

  int result = s21_eq_matrix(&matrix1, &matrix2);

  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}

START_TEST(test_s21_eq_matrix_4) {
  matrix_t matrix1 = {0};
  matrix_t matrix2 = {0};

  s21_create_matrix(2, 2, &matrix1);
  s21_create_matrix(2, 3, &matrix2);  // Different dimensions

  int result = s21_eq_matrix(&matrix1, &matrix2);

  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}

START_TEST(test_s21_eq_matrix_5) {
  matrix_t matrix1 = {0};
  matrix_t matrix2 = {0};

  s21_create_matrix(2, 2, &matrix1);
  s21_create_matrix(2, 2, &matrix2);

  matrix1.matrix[0][0] = 1.5;
  matrix1.matrix[0][1] = 2.5;
  matrix1.matrix[1][0] = 3.5;
  matrix1.matrix[1][1] = 4.5;

  matrix2.matrix[0][0] = 1.5;
  matrix2.matrix[0][1] = 2.5;
  matrix2.matrix[1][0] = 3.5;
  matrix2.matrix[1][1] = 4.5;

  int result = s21_eq_matrix(&matrix1, &matrix2);

  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}

TCase *tcase_s21_eq_matrix_new(void) {
  TCase *tc = tcase_create("s21_eq_matrix_new");
  tcase_add_test(tc, test_s21_eq_matrix_1);
  tcase_add_test(tc, test_s21_eq_matrix_2);
  tcase_add_test(tc, test_s21_eq_matrix_3);
  tcase_add_test(tc, test_s21_eq_matrix_4);
  tcase_add_test(tc, test_s21_eq_matrix_5);
  return tc;
}