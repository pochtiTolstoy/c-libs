#ifndef TESTS_S21_STRNCPY_H
#define TESTS_S21_STRNCPY_H
#include "common_header.h"

START_TEST(test_s21_strncpy) {
#include "tests_data/strncpy_data.h"
  for (s21_size_t i = 0; i < size_ar_src; i++) {
    for (s21_size_t j = 0; j < size_destinations; j++) {
      char temp_str1[1024] = "";
      char temp_str2[1024] = "";
      strcpy(temp_str1, destinations[i]);
      strcpy(temp_str2, destinations[i]);
      char *s21_res = s21_strncpy(temp_str1, sources[j], n_sizes[i]);
      char *orig_res = strncpy(temp_str2, sources[j], n_sizes[i]);
      int result = (strcmp(s21_res, orig_res) == 0);
      if (!result) {
        fprintf(stderr,
                "\n"
                "[  FAILED  ] s21_strncpy test\n"
                "[      IN  ] [%s], [%s], [%lld], \n"
                "[  EXP     ] %s\n"
                "[     OUT  ] %s\n\n",
                temp_str1, sources[i], n_sizes[i], orig_res, s21_res);
      }
      ck_assert(result);
      test_num++;
    }
  }
  printf("[  TESTS  ] s21_strncpy tests number : %llu\n", test_num);
}

#endif
