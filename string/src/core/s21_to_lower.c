#include "../s21_string.h"
void *s21_to_lower(const char *str) {
  if (str == S21_NULL) return S21_NULL;
  s21_size_t len = s21_strlen(str);
  char *result = (char *)malloc(len + 1);
  if (result == S21_NULL) return S21_NULL;

  for (s21_size_t i = 0; i < len; i++) {
    result[i] = tolower((unsigned char)str[i]);
  }
  result[len] = '\0';
  return result;
}
