#include "s21_decimal.h"

#define ZERO_PREFIX "0."
#define ZERO_PREFIX_LEN 2

static int s21_div_mantissa_by_10_(s21_decimal *ptr_number) {
  uint64_t remainder = 0;
  for (int i = BITS_EXP_IDX - 1; i >= 0; --i) {
    uint64_t value = (remainder << BITS_PER_INT) | ptr_number->bits[i];
    ptr_number->bits[i] = (uint32_t)(value / 10);
    remainder = value % 10;
  }
  return (int)remainder;
}

static void s21_reverse_str_(char *begin, char *end) {
  for (--end; begin < end; ++begin, --end) {
    char temp = *begin;
    *begin = *end;
    *end = temp;
  }
}

static void s21_shift_str_(const char *begin, char *end, size_t shift) {
  for (--end; begin <= end; --end) {
    end[shift] = *end;
  }
}

int s21_decimal_to_str(s21_decimal number, char *buffer) {
  char *output_iterator = buffer;
  char *backup_iterator = buffer;
  int sign = s21_get_sign(&number);
  int scale = s21_get_scale(&number);

  if (sign && !s21_is_zero(&number)) {
    *output_iterator++ = '-';
    backup_iterator = output_iterator;
  }

  if (s21_is_zero(&number)) {
    *output_iterator++ = '0';
  }
  while (!s21_is_zero(&number)) {
    *output_iterator++ = s21_div_mantissa_by_10_(&number) + '0';
  }
  *output_iterator = '\0';
  s21_reverse_str_(backup_iterator, output_iterator);

  int number_len = output_iterator - backup_iterator;
  if (scale >= number_len) {
    size_t leading_zeros = scale - number_len + ZERO_PREFIX_LEN;
    s21_shift_str_(backup_iterator, output_iterator, leading_zeros);
    for (size_t i = 0; i < leading_zeros; ++i) {
      backup_iterator[i] = '0';
    }
    *(backup_iterator + 1) = '.';
    *(output_iterator + leading_zeros) = '\0';
  }

  if (0 < scale && scale < number_len) {
    size_t shift_frac_part = 1;
    s21_shift_str_(output_iterator - scale, output_iterator, shift_frac_part);
    *(output_iterator - scale) = '.';
    *(output_iterator + shift_frac_part) = '\0';
  }

  return 0;
}
