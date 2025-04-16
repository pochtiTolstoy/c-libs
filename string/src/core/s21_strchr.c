#include "../s21_string.h"
char *s21_strchr(const char *str, int c) {
  int cond_while = 0;
  while (*str && !cond_while) {
    if (*str == (char)c) {
      cond_while = 1;
      str--;
    }
    str++;
  }
  return (c == '\0' || cond_while == 1) ? (char *)str : S21_NULL;
}
