#include "s21_matrix.h"

int s21_is_invalid_matrix(matrix_t* A) {
  return (A == NULL || A->matrix == NULL || A->rows <= 0 || A->columns <= 0);
}

int s21_is_eq_size_matrix(matrix_t* A, matrix_t* B) {
  return (A->rows == B->rows && A->columns == B->columns);
}

int s21_add_sub_matrix(matrix_t* A, matrix_t* B, matrix_t* result, SIGN sign) {
  if (s21_is_invalid_matrix(A) || s21_is_invalid_matrix(B) ||
      s21_is_invalid_matrix(result)) {
    return INVALID_MATRIX;
  }
  CODES code = OK;
  int coef = (sign == NEGATIVE) ? -1 : 1;
  if (s21_is_eq_size_matrix(A, B) && s21_is_eq_size_matrix(B, result)) {
    for (int row = 0; row < A->rows; ++row) {
      for (int col = 0; col < A->columns; ++col) {
        result->matrix[row][col] =
            A->matrix[row][col] + coef * B->matrix[row][col];
      }
    }
  } else {
    code = CALCULATION_ERROR;
  }
  return code;
}

double s21_vector_mult(int row, int col, matrix_t* A, matrix_t* B) {
  double res = 0;
  for (int k = 0; k < A->columns; ++k) {
    res += A->matrix[row][k] * B->matrix[k][col];
  }
  return res;
}

int s21_create_minor(matrix_t* A, matrix_t* minor, int row, int colulmn) {
  CODES code = OK;
  if (A == NULL || minor == NULL) {
    code = INVALID_MATRIX;
  } else if (A->rows <= 0 || A->columns <= 0 || minor->rows != A->rows - 1 ||
             minor->columns != A->columns - 1) {
    code = CALCULATION_ERROR;
  }
  int minor_row = 0;
  for (int i = 0; i < A->rows && code == OK; ++i) {
    if (i == row) {
      continue;
    }
    int minor_col = 0;
    for (int j = 0; j < A->columns; ++j) {
      if (j == colulmn) {
        continue;
      }
      minor->matrix[minor_row][minor_col] = A->matrix[i][j];
      ++minor_col;
    }
    ++minor_row;
  }
  return code;
}

int s21_calc_minor_det(matrix_t* A, int col, double* det) {
  matrix_t minor = {0};
  CODES err = s21_create_matrix(A->rows - 1, A->rows - 1, &minor);
  if (err == OK) {
    s21_create_minor(A, &minor, 0, col);
    err = s21_determinant(&minor, det);
    s21_remove_matrix(&minor);
  }
  return err;
}

int s21_get_complement(matrix_t* A, int col, double* det) {
  double minor_det;
  CODES err = s21_calc_minor_det(A, col, &minor_det);
  if (err == OK) {
    double sign = (col % 2) ? -1.0 : 1.0;
    *det += sign * A->matrix[0][col] * minor_det;
  }
  return err;
}

void s21_unit_matrix(matrix_t* A) {
  s21_create_matrix(3, 3, A);
  if (A != NULL && A->matrix != NULL) {
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < A->columns; ++j) {
        A->matrix[i][j] = (i == j);
      }
    }
  }
}

void s21_initialize_matrix(matrix_t* A, double start, double step) {
  if (A != NULL && A->matrix != NULL) {
    double value = start;
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < A->columns; ++j) {
        A->matrix[i][j] = value;
        value += step;
      }
    }
  }
}

void s21_print_matrix(matrix_t* A) {
  if (!s21_is_invalid_matrix(A)) {
    for (int row = 0; row < A->rows; ++row) {
      for (int col = 0; col < A->columns; ++col) {
        printf("%lf ", A->matrix[row][col]);
      }
      printf("\n");
    }
    printf("\n");
  }
}
