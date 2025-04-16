#include "../arithmetic/arithmetic.h"

void s21_remove_trailing_zeros(s21_decimal *value) {
  char buffer[128] = {0};
  s21_decimal_to_str(*value, buffer);
  if (strchr(buffer, '.')) {
    size_t number_len = strlen(buffer);
    int zero_ind = number_len - 1;
    while (zero_ind >= 0 && buffer[zero_ind] == '0') {
      buffer[zero_ind] = '\0';
      --zero_ind;
    }
    if (zero_ind >= 0 && buffer[zero_ind] == '.') {
      buffer[zero_ind] = '\0';
    }
    s21_str_to_decimal(buffer, value);
  }
}
