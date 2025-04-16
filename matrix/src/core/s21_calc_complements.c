#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  CODES err = OK;
  if (s21_is_invalid_matrix(A) || result == NULL) {
    err = INVALID_MATRIX;
  } else if (A->rows == 1 || A->columns == 1 || A->rows != A->columns) {
    err = CALCULATION_ERROR;
  } else {
    err = s21_create_matrix(A->rows, A->columns, result);
  }
  matrix_t minor = {0};
  s21_create_matrix(A->rows - 1, A->rows - 1, &minor);
  for (int row = 0; row < A->rows && err == OK; ++row) {
    for (int col = 0; col < A->columns && err == OK; ++col) {
      s21_create_minor(A, &minor, row, col);
      double det = 0.0;
      if ((err = s21_determinant(&minor, &det)) == OK) {
        result->matrix[row][col] = (row + col) % 2 == 0 ? det : -det;
      }
    }
  }
  s21_remove_matrix(&minor);
  return err;
}
