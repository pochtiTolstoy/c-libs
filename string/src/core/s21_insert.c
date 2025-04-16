#include "../s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  if (src == S21_NULL || str == S21_NULL) return S21_NULL;

  s21_size_t src_len = s21_strlen(src);
  s21_size_t str_len = s21_strlen(str);

  if (start_index > src_len) return S21_NULL;

  char *result = (char *)malloc(src_len + str_len + 1);
  if (result == S21_NULL) return S21_NULL;

  s21_strncpy(result, src, start_index);

  s21_strncpy(result + start_index, str, str_len);

  s21_strncpy(result + start_index + str_len, src + start_index,
              src_len - start_index);

  result[src_len + str_len] = '\0';

  return result;
}
