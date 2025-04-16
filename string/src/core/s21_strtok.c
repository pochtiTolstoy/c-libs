#include "../s21_string.h"
char* s21_strtok(char* str, const char* delims) {
  static char* string_saver = S21_NULL;

  if (str == S21_NULL) {
    str = string_saver;
  }

  for (; str && *str && s21_strchr(delims, *str); ++str);

  char* begin = (str && *str) ? str : S21_NULL;
  for (; str && *str && !s21_strchr(delims, *str); ++str);

  if (str && *str) {
    string_saver = (*(str + 1)) ? str + 1 : S21_NULL;
    *str = '\0';
  } else {
    string_saver = S21_NULL;
  }

  return begin;
}
