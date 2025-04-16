#include "../s21_string.h"
char *s21_strrchr(const char *str, int c) {
  int cond_while = 0;
  char *current_pointer = (char *)&str[s21_strlen(str)];
  while (*str) {
    if (*str == (char)c) {
      cond_while = 1;
      current_pointer = (char *)str;
    }
    str++;
  }
  return (c == '\0' || cond_while == 1) ? current_pointer : S21_NULL;
}
