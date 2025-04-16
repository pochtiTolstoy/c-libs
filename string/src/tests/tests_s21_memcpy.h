#ifndef TESTS_S21_MEMCPY_H
#define TESTS_S21_MEMCPY_H
#include "common_header.h"

START_TEST(test_s21_memcpy) {
#include "tests_data/memcpy_data.h"

  for (s21_size_t i = 0; i < size_ar_src; i++) {
    for (s21_size_t j = 0; j < size_destinations; j++) {
      for (s21_size_t k = 0; k < size_n_sizes; k++) {
        char temp_str1[1024] = "";
        char temp_str2[1024] = "";
        strcpy(temp_str1, destinations[j]);
        strcpy(temp_str2, destinations[j]);
        char *s21_res = s21_memcpy(temp_str1, sources[i], n_sizes[k]);
        char *orig_res = memcpy(temp_str2, sources[i], n_sizes[k]);
        int result = (strcmp(s21_res, orig_res) == 0);
        if (!result) {
          fprintf(stderr,
                  "\n"
                  "[  FAILED  ] s21_memcpy test\n"
                  "[      IN  ] [%s], [%s], [%lld], \n"
                  "[  EXP     ] %s\n"
                  "[     OUT  ] %s\n\n",
                  temp_str1, sources[i], lenArray[i], orig_res, s21_res);
        }
        ck_assert(result);
        tests_num++;
      }
    }
  }
  printf("[  TESTS  ] s21_memcpy tests number : %llu\n", tests_num);
}
END_TEST

#endif
