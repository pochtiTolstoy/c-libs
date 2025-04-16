#include "../s21_string.h"
char *s21_strpbrk(const char *str1, const char *str2) {
  const char *match = S21_NULL;
  for (; *str1 && !match; ++str1) {
    for (const char *filter = str2; *filter && !match; ++filter) {
      match = (*str1 == *filter) ? str1 : S21_NULL;
    }
  }
  return (char *)match;
}
