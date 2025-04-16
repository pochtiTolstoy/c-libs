#include "s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  CODES err = OK;
  if (s21_is_invalid_matrix(A) || result == NULL) {
    err = INVALID_MATRIX;
  } else {
    err = s21_create_matrix(A->rows, A->columns, result);
  }
  if (err == OK) {
    for (int row = 0; row < A->rows; ++row) {
      for (int col = 0; col < A->columns; ++col) {
        result->matrix[row][col] = A->matrix[row][col] * number;
      }
    }
  }
  return err;
}
