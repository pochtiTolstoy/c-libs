#include "../s21_string.h"
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *p1 = (char *)dest;
  const char *p2 = (const char *)src;
  s21_size_t i = 0;
  for (; i < n; i++, p1++, p2++) {
    *p1 = *p2;
  }

  return dest;
}