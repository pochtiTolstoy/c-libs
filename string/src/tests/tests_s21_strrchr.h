#ifndef TESTS_S21_STRRCHR_H
#define TESTS_S21_STRRCHR_H
#include "common_header.h"

START_TEST(test_s21_strrchr) {
#include "tests_data/strrchr_data.h"
  for (s21_size_t i = 0; i < size_buffers; i++) {
    for (s21_size_t j = 0; j < size_search_chars; j++) {
      char temp1[1024] = "";
      char temp2[1024] = "";
      strcpy(temp1, buffers[i]);
      strcpy(temp2, buffers[i]);
      char *s21_result = (char *)s21_strrchr(temp1, search_chars[j]);
      char *orig_result = (char *)strrchr(temp2, search_chars[j]);
      if (s21_result == NULL || orig_result == NULL) {
        ck_assert(s21_result == orig_result);
        continue;
      }
      int result = (strcmp(s21_result, orig_result) == 0);
      if (!result) {
        fprintf(stderr,
                "\n"
                "[  FAILED  ] s21_strrchr test\n"
                "[      IN  ] [%s], [%c]\n"
                "[  EXP     ] %s\n"
                "[     OUT  ] %s\n\n",
                temp1, search_chars[j], orig_result, s21_result);
      }
      ck_assert(result);
      test_num++;
    }
  }
  printf("[  TESTS  ] s21_strrchr tests number : %llu\n", test_num);
}
END_TEST

#endif
