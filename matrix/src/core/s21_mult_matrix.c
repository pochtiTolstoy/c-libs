#include "s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  CODES err = OK;
  if (s21_is_invalid_matrix(A) || s21_is_invalid_matrix(B) || result == NULL) {
    err = INVALID_MATRIX;
  } else {
    err = s21_create_matrix(A->rows, B->columns, result);
  }
  if (err == OK && A->columns == B->rows) {
    for (int row = 0; row < A->rows; ++row) {
      for (int col = 0; col < B->columns; ++col) {
        result->matrix[row][col] = s21_vector_mult(row, col, A, B);
      }
    }
  } else if (err == OK) {
    err = CALCULATION_ERROR;
  }
  return err;
}
