#include "../s21_string.h"
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const char *p1 = (const char *)str1;
  const char *p2 = (const char *)str2;
  s21_size_t counter = 0;
  int ret_value = 0;
  int cond = 0;
  for (; (counter < n) && !cond; counter++, p1++, p2++) {
    if (*p1 > *p2) {
      ret_value = 1;
      cond = 1;

    } else if (*p2 > *p1) {
      ret_value = -1;
      cond = 1;
    }
  }

  return ret_value;
}
