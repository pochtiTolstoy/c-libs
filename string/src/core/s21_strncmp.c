#include "../s21_string.h"
int s21_strncmp(const char* str1, const char* str2, s21_size_t n) {
  int res = 0;
  int find_null = 0;
  for (s21_size_t i = 0; i < n && !res && !find_null; ++i) {
    res = str1[i] - str2[i];
    find_null = (!str1[i] || !str2[i]);
  }
  return res;
}
