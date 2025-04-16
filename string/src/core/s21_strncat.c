#include "../s21_string.h"
char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t j = s21_strlen(dest);
  for (s21_size_t i = 0; i < n && src[i]; ++i, ++j) {
    dest[j] = src[i];
  }
  dest[j] = '\0';
  return dest;
}
