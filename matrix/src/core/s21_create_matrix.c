#include "s21_matrix.h"

int s21_create_matrix(int rows, int cols, matrix_t* result) {
  CODES err = OK;
  if (result == NULL || rows <= 0 || cols <= 0) {
    err = INVALID_MATRIX;
  } else {
    result->matrix = NULL;
    result->rows = rows;
    result->columns = cols;
    size_t row_ptrs_size = rows * sizeof(double*);
    size_t data_size = rows * cols * sizeof(double);
    size_t total_size = row_ptrs_size + data_size;
    char* memory = (char*)calloc(1, total_size);
    if (memory) {
      result->matrix = (double**)memory;
      double* data_begin = (double*)(memory + row_ptrs_size);
      for (int row = 0; row < rows; ++row) {
        result->matrix[row] = data_begin + row * cols;
      }
    } else {
      err = INVALID_MATRIX;
    }
  }
  return err;
}
