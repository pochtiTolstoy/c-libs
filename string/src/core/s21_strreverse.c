#include "../s21_string.h"
char* s21_strreverse(char* str) {
  s21_size_t str_len = s21_strlen(str);
  for (s21_size_t i = 0; i < str_len / 2; i++) {
    char temp = str[i];
    str[i] = str[str_len - i - 1];
    str[str_len - i - 1] = temp;
  }
  return str;
}
