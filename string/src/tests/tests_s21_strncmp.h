#ifndef TESTS_S21_STRNCMP_H
#define TESTS_S21_STRNCMP_H
#include "common_header.h"

START_TEST(test_s21_strncmp) {
#include "tests_data/strcmp_data.h"
  for (s21_size_t i = 0; i < size_strbuff1; ++i) {
    for (s21_size_t j = 0; j < size_strbuff2; j++) {
      for (s21_size_t k = 0; k < size_len_buff; k++) {
        int s21_res = s21_strncmp(strbuff1[i], strbuff2[j], lenbuff[k]);
        int orig_res = strncmp(strbuff1[i], strbuff2[j], lenbuff[k]);
        int res =
            ((s21_res > 0 && orig_res > 0) || (s21_res < 0 && orig_res < 0) ||
             (s21_res == 0 && orig_res == 0));
        if (!res) {
          fprintf(stderr,
                  "\n"
                  "[  FAILED  ] s21_strncmp test\n"
                  "[      IN  ] [%s], [%s]\n"
                  "[  EXP     ] %d\n"
                  "[     OUT  ] %d\n\n",
                  strbuff1[i], strbuff2[i], orig_res, s21_res);
        }
        ck_assert(res);
        tests_num++;
      }
    }
  }
  printf("[  TESTS  ] s21_strncmp tests number : %llu\n", tests_num);
}
END_TEST

#endif
