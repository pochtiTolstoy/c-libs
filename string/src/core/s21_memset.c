#include "../s21_string.h"
void *s21_memset(void *buf, int ch, s21_size_t count) {
  char *p = (char *)(buf);
  for (s21_size_t i = 0; i < count; i++, p++) {
    *p = ch;
  }

  return buf;
}