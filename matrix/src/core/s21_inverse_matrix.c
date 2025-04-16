#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  CODES err = OK;
  if (s21_is_invalid_matrix(A) || result == NULL) {
    err = INVALID_MATRIX;
  } else if (A->rows != A->columns) {
    err = CALCULATION_ERROR;
  }
  double det = 0.0;
  if (err == OK) {
    err = s21_determinant(A, &det);
  }
  if (err == OK && A->rows == 1) {
    if (det != 0) {
      s21_create_matrix(1, 1, result);
      result->matrix[0][0] = 1.0 / det;
    } else {
      err = CALCULATION_ERROR;
    }
  } else if (err == OK) {
    matrix_t compl = {0};
    matrix_t transp = {0};
    s21_calc_complements(A, &compl );
    if (s21_transpose(&compl, &transp) == OK && det != 0) {
      err = s21_mult_number(&transp, 1.0 / det, result);
    } else if (det == 0.0) {
      err = CALCULATION_ERROR;
    } else {
      err = INVALID_MATRIX;
    }
    s21_remove_matrix(&transp);
    s21_remove_matrix(&compl );
  }
  return err;
}
