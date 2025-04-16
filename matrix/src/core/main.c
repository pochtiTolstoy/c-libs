#include <stdio.h>

#include "s21_matrix.h"

int main(void) {
  int result1 = OK, result2 = OK;

  matrix_t A = {0};
  matrix_t res = {0};

  result1 = s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;

  result1 = s21_inverse_matrix(&A, &res);
  printf("%d%d\n", result1, result2);

  s21_remove_matrix(&A);
  s21_remove_matrix(&res);
  return 0;
}
