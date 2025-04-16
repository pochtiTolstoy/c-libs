#include "../s21_strerror.h"

#include "../s21_string.h"

char *s21_strerror(int errnum) {
  const char *errors_list[] = S21_LIST_ERRORS;
  static char result[512] = {'\0'};
  if ((errnum < 0) || (errnum > S21_SIZE_LIST_ERRORS - 1)) {
    snprintf(result, sizeof(result), "Unknown error %d", errnum);
  } else {
    s21_strncpy(result, errors_list[errnum], 512);
  }

  return result;
}