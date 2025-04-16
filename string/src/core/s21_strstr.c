#include "../s21_string.h"
char *s21_strstr(const char *haystack, const char *needle) {
  char *result = S21_NULL;

  if (*needle == '\0') {
    result = (char *)haystack;
  } else {
    const char *h = haystack;
    s21_size_t needle_len = s21_strlen(needle);

    while (*h) {
      if (s21_strncmp(h, needle, needle_len) == 0) {
        result = (char *)h;
        break;
      }
      h++;
    }
  }

  return result;
}
