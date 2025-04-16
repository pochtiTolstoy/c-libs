#ifndef TESTS_S21_STRSTR_H
#define TESTS_S21_STRSTR_H
#include "common_header.h"

START_TEST(test_s21_strstr) {
#include "tests_data/strstr_data.h"
  for (s21_size_t i = 0; i < size_buffers; i++) {
    for (s21_size_t j = 0; j < size_needles; j++) {
      char str1_school[512] = "";
      char str2_school[512] = "";
      char str1_orig[512] = "";
      char str2_orig[512] = "";
      strcpy(str1_school, haystacks[i]);
      strcpy(str2_school, needles[j]);
      strcpy(str1_orig, haystacks[i]);
      strcpy(str2_orig, needles[j]);
      char *s21_result = (char *)s21_strstr(str1_school, str2_school);
      char *orig_result = (char *)strstr(str1_orig, str2_orig);
      if (s21_result == NULL || orig_result == NULL) {
        ck_assert(s21_result == orig_result);
        continue;
      }
      int result = (strcmp(s21_result, orig_result) == 0);
      if (!result) {
        fprintf(stderr,
                "\n"
                "[  FAILED  ] s21_strstr test\n"
                "[      IN  ] [%s], [%s]\n"
                "[  EXP     ] %s\n"
                "[     OUT  ] %s\n\n",
                str1_school, str2_school, orig_result, s21_result);
      }
      ck_assert(result);
      tests_num++;
    }
  }
  printf("[  TESTS  ] s21_strstr tests number : %llu\n", tests_num);
}
END_TEST

#endif
