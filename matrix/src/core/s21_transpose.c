#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  CODES err = OK;
  if (s21_is_invalid_matrix(A) || result == NULL) {
    err = INVALID_MATRIX;
  } else {
    err = s21_create_matrix(A->columns, A->rows, result);
  }
  if (err == OK) {
    for (int row = 0; row < A->rows; ++row) {
      for (int col = 0; col < A->columns; ++col) {
        result->matrix[col][row] = A->matrix[row][col];
      }
    }
  }
  return err;
}
