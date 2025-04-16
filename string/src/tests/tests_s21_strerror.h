#ifndef TESTS_S21_STRERROR_H
#define TESTS_S21_STRERROR_H
#include "common_header.h"
START_TEST(test_s21_strerror) {
  int start = -100;
  int end = 300;

  int tests_number = 0;
  for (int i = start; i <= end; i++) {
    // на оригинальный strerror valgrind жалуется
    char* s21_res = s21_strerror(i);
    char* orig_res = s21_strerror(i);
    int result = (strcmp(s21_res, orig_res) == 0);
    if (!result) {
      fprintf(stderr,
              "\n"
              "[  FAILED  ] s21_strerror test\n"
              "[      IN  ] [%d], \n"
              "[  EXP     ] %s\n"
              "[     OUT  ] %s\n\n",
              i, orig_res, s21_res);
    }
    ck_assert(result);
    ++tests_number;
  }
  printf("[  TESTS  ] s21_strerror tests number : %d\n", tests_number);
}
END_TEST
#endif
