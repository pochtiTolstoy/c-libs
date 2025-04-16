#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  CODES err = OK;
  double det = 0.0;
  if (s21_is_invalid_matrix(A) || result == NULL) {
    err = INVALID_MATRIX;
  } else if (A->rows != A->columns) {
    err = CALCULATION_ERROR;
  }
  if (err == OK) {
    if (A->rows == 1) {
      det = A->matrix[0][0];
    } else if (A->rows == 2) {
      det =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    } else {
      for (int col = 0; col < A->columns && err == OK; ++col) {
        err = s21_get_complement(A, col, &det);
      }
    }
  }
  if (err == OK) {
    *result = det;
  }
  return err;
}
