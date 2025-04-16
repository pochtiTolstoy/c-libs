#include "../s21_string.h"

s21_size_t s21_strcspn(const char* src, const char* template) {
  s21_size_t len = 0;
  for (char match = 0; *src && !match; ++src) {
    for (const char* filter = template; *filter && !match; ++filter) {
      match = (*src == *filter);
    }
    len += !match;
  }
  return len;
}
