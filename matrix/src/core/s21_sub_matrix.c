#include "s21_matrix.h"

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  CODES err = OK;
  if (s21_is_invalid_matrix(A) || s21_is_invalid_matrix(B) || result == NULL) {
    err = INVALID_MATRIX;
  } else if (!s21_is_eq_size_matrix(A, B)) {
    err = CALCULATION_ERROR;
  } else {
    err = s21_create_matrix(A->rows, A->columns, result);
  }
  if (err == OK) {
    err = s21_add_sub_matrix(A, B, result, (SIGN)NEGATIVE);
  }
  return err;
}
