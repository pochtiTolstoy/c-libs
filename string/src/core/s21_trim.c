#include "../s21_string.h"
void *s21_trim(const char *src, const char *trim_chars) {
  if (src == S21_NULL || trim_chars == S21_NULL) return S21_NULL;

  const char *start = src;
  while (*start && s21_strchr(trim_chars, *start)) start++;

  const char *end = src + s21_strlen(src);
  while (end > start && s21_strchr(trim_chars, *(end - 1))) end--;

  s21_size_t len = end - start;
  char *result = (char *)malloc(len + 1);
  if (result == S21_NULL) return S21_NULL;

  s21_strncpy(result, start, len);
  result[len] = '\0';
  return result;
}
