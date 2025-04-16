#include "s21_dtoa.h"

#include "../../s21_string.h"

/* s21_dtoa: returns the number of additional digits after rounding */
int s21_dtoa(char *output_buff, double value, int precision) {
  return (value == 0.0) ? write_zero_float(output_buff, precision)
                        : write_non_zero_float(output_buff, value, precision);
}

int write_zero_float(char *iter, int precision) {
  *(iter++) = '0';
  if (precision > 0) {
    *(iter++) = '.';
    for (int i = 0; i < precision; ++i) {
      *(iter++) = '0';
    }
  }
  *iter = '\0';
  return 0;
}

int write_non_zero_float(char *iter, double value, int precision) {
  output_iterators_t it = {.backup_iter = iter, .curr_iter = iter};
  int digit_to_round = 0;
  long double int_part;
  long double frac_part = modfl(value, &int_part);

  write_int_part(&it, int_part);
  write_frac_part(&it, &frac_part, precision - 1);

  if (precision > 0) {
    frac_part = modfl(frac_part * 10, &int_part);
    digit_to_round = (int)int_part;
  } else if (precision == 0) {
    --it.curr_iter;
    digit_to_round = *it.curr_iter - '0';
  }

  frac_part = modfl(frac_part * 10, &int_part);
  int analyze_digit = (int)int_part;
  if (analyze_digit > 5 || (analyze_digit == 5 && digit_to_round % 2 != 0)) {
    ++digit_to_round;
  } else if (analyze_digit == 5 && digit_to_round % 2 == 0) {
    int found_tail = 0;
    for (int i = 0; i < 50 && !found_tail; ++i) {
      frac_part = modfl(frac_part * 10, &int_part);
      found_tail = ((int)int_part != 0);
    }
    digit_to_round += found_tail;
  }

  *it.curr_iter++ = '0' + (digit_to_round % 10);

  int is_extra_digit = process_rounding(digit_to_round, &it);

  return write_extra_digit(is_extra_digit, &it);
}

int process_rounding(int digit_to_round, output_iterators_t *it) {
  int carry = (digit_to_round >= 10);
  char *backward_iter = it->curr_iter - 2;
  while (carry && it->backup_iter <= backward_iter) {
    if (*backward_iter != '.') {
      int digit = *backward_iter - '0';
      *backward_iter = '0' + ((digit + carry) % 10);
      carry = (digit + carry) / 10;
    }
    --backward_iter;
  }
  return carry;
}

int write_extra_digit(int carry, output_iterators_t *it) {
  if (carry) {
    shift_right(it->backup_iter);
    *it->backup_iter = '1';
    *(it->curr_iter + 1) = '\0';
  } else {
    *it->curr_iter = '\0';
  }
  return carry;
}

void write_int_part(output_iterators_t *it, long double int_part) {
  if (int_part == 0) *it->curr_iter++ = '0';
  while (int_part > 0) {
    *it->curr_iter++ = '0' + ((int)fmod(int_part, 10));
    int_part = floor(int_part / 10);
  }
  *it->curr_iter = '\0';
  s21_strreverse(it->backup_iter);
}

void write_frac_part(output_iterators_t *it, long double *frac_part,
                     int digits_to_write) {
  long double int_part;
  if (digits_to_write >= 0) *it->curr_iter++ = '.';
  for (int i = 0; i < digits_to_write; ++i) {
    *frac_part = modfl(*frac_part * 10, &int_part);
    *it->curr_iter++ = '0' + (int)int_part;
  }
  *it->curr_iter = '\0';
}
