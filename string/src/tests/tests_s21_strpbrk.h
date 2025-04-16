#ifndef TESTS_S21_STRPBRK_H
#define TESTS_S21_STRPBRK_H

#include "common_header.h"

START_TEST(test_s21_strpbrk) {
#include "tests_data/strpbrk_data.h"
  for (s21_size_t i = 0; i < size_strbuff1; ++i) {
    for (s21_size_t j = 0; j < size_strbuff2; ++j) {
      char* s21_res = s21_strpbrk(strbuff1[i], strbuff2[j]);
      char* orig_res = (char*)strpbrk(strbuff1[i], strbuff2[j]);
      int res = (s21_res == orig_res);
      ++tests_counter;
      if (!res) {
        fprintf(stderr,
                "\n"
                "[  FAILED  ] s21_strpbrk test\n"
                "[      IN  ] [%s], [%s]\n"
                "[  EXP     ] %p\n"
                "[     OUT  ] %p\n\n",
                strbuff1[i], strbuff2[j], orig_res, s21_res);
      }
      ck_assert(res);
    }
  }
  printf("[  TESTS  ] s21_strpbrk tests number : %lld\n", tests_counter);
}
END_TEST

#endif
