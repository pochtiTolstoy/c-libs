#ifndef S21_DTOA_H
#define S21_DTOA_H

#include <math.h>

typedef struct output_iterators_t {
  char *backup_iter;
  char *curr_iter;
} output_iterators_t;

void write_int_part(output_iterators_t *, long double);
void write_frac_part(output_iterators_t *, long double *, int);
int write_non_zero_float(char *, double, int);
int write_zero_float(char *, int);
void shift_right(char *);
int write_extra_digit(int, output_iterators_t *);
int process_rounding(int, output_iterators_t *);

#endif
