#ifndef S21_MATRIX_H_
#define S21_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

typedef enum CODES { OK = 0, INVALID_MATRIX = 1, CALCULATION_ERROR = 2 } CODES;
typedef enum SIGN { POSITIVE = 0, NEGATIVE = 1 } SIGN;

#define SUCCESS 1
#define FAILURE 0

int s21_create_matrix(int rows, int cols, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);

int s21_is_invalid_matrix(matrix_t *A);
int s21_is_eq_size_matrix(matrix_t *A, matrix_t *B);
int s21_add_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result, SIGN sign);
double s21_vector_mult(int row, int col, matrix_t *A, matrix_t *B);
int s21_create_minor(matrix_t *A, matrix_t *minor, int row, int colulmn);
int s21_calc_minor_det(matrix_t *A, int col, double *det);
void s21_unit_matrix(matrix_t *A);
int s21_get_complement(matrix_t *A, int col, double *det);
void s21_initialize_matrix(matrix_t *A, double start, double step);
void s21_print_matrix(matrix_t *A);

#endif
