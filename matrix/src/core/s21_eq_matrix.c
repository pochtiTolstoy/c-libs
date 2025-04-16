#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  CODES err = OK;
  int cmp = FAILURE;
  if (s21_is_invalid_matrix(A) || s21_is_invalid_matrix(B)) {
    err = INVALID_MATRIX;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    err = CALCULATION_ERROR;
  }
  if (err == OK) {
    cmp = SUCCESS;
    for (int i = 0; i < A->rows && cmp == SUCCESS; i++) {
      for (int j = 0; j < A->columns && cmp == SUCCESS; j++) {
        cmp = (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-7) ? FAILURE : cmp;
      }
    }
  }
  return cmp;
}
